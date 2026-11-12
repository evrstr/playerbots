// 策略值实现：AttackersValue（攻击者发现、复用缓存、有效性校验与过滤逻辑）

#include "playerbot/playerbot.h"
#include "AttackersValue.h"
#include "PossibleTargetsValue.h"
#include "EnemyPlayerValue.h"

using namespace ai;
using namespace MaNGOS;

// 计算机器人或队伍的战斗攻击者列表（优先尝试复用附近友方机器人的有效计算结果）
std::list<ObjectGuid> AttackersValue::Calculate()
{
    std::list<ObjectGuid> result;
    if (!ai->AllowActivity(ALL_ACTIVITY))
        return result;

    if (!bot->IsInWorld())
        return result;

    if (bot->IsBeingTeleported())
        return result;

    if (bot->IsFlying() && WorldPosition(bot).currentHeight() > 10.0f)
        return result;

    // lost control, e.g. BG ended | 失去控制，例如战场已结束
    if (bot->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CLIENT_CONTROL_LOST))
        return result;

    if (ai->HasStrategy("focus rti targets", BotState::BOT_STATE_COMBAT))
    {
        Unit* rtiTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "rti target"));

        if (rtiTarget && rtiTarget->IsInWorld() && rtiTarget->GetMapId() == bot->GetMapId())
        {
            return { rtiTarget->GetObjectGuid() };
        }

        return result;
    }

    if (sPlayerbotAIConfig.shareTargets)
    {
        // Try to get the value from nearby friendly bots. | 尝试从附近友方机器人复用该数值
        std::list<ObjectGuid> nearGuids = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid> >("nearest friendly players")->Get();
        for (auto& i : nearGuids)
        {
            Player* player = sObjectMgr.GetPlayer(i);

            if (!player)
                continue;

            if (player == bot)
                continue;

            if (!ai->IsSafe(player))
                continue;

            if (sServerFacade.GetDistance2d(bot, player) > 10.0f)
                continue;

            PlayerbotAI* botAi = player->GetPlayerbotAI();

            if (!botAi)
                continue;

            std::string valueName = "attackers" + !qualifier.empty() ? "::" + qualifier : "";

            // Ignore bots without the value. | 忽略尚未计算该值的机器人
            if (!PHAS_AI_VALUE(valueName))
                continue;

            UntypedValue* pValue = botAi->GetAiObjectContext()->GetUntypedValue(valueName);

            AttackersValue* pAttackersValue = dynamic_cast<AttackersValue*>(pValue);

            if (!pAttackersValue)
                continue;

            // Ignore expired values. | 忽略已过期的缓存值
            if (pAttackersValue->Expired())
                continue;

            if (pAttackersValue->calculatePos.sqDistance2d(bot) > 100.0f)
                continue;

            // Make the value expire at the same time as the copied value. | 使本地缓存的过期时间与复制来源保持一致
            lastCheckTime = pAttackersValue->lastCheckTime;

            calculatePos = pAttackersValue->calculatePos;

            result = PAI_VALUE(std::list<ObjectGuid>, valueName);

            std::vector<std::string> specificTargetNames = { "current target","old target","attack target","pull target" };
            Unit* target;

            //Remove bot specific targets of the other bot. | 移除对方机器人特有的目标
            for (auto& targetName : specificTargetNames)
            {
                target = ai->GetUnit(PAI_VALUE(ObjectGuid, targetName));
                if (target)
                    result.remove(target->GetObjectGuid());
            }

            //Add bot specific targets of this bot. | 补充当前机器人特有的目标
            for (auto& targetName : specificTargetNames)
            {
                target = ai->GetUnit(PAI_VALUE(ObjectGuid, targetName));
                if (target)
                    result.push_back(target->GetObjectGuid());
            }

            //Validate these targets. | 逐一验证目标有效性
            std::list<ObjectGuid> filter;

            for (auto& guid : result)
            {
                target = ai->GetUnit(guid);

                if (!IsValid(target, bot, bot))
                    filter.push_back(guid);
            }

            for(auto& guid : filter)
                result.remove(guid);

            return result;
        }
    }
    
    calculatePos = bot;

    std::set<Unit*> targets;

    // Check if we only need one attacker | 检查是否只需获取单个攻击者
    bool getOne = false;
    if (!qualifier.empty())
    {
        getOne = stoi(qualifier);
    }

    std::set<ObjectGuid> invalidTargets;

    // Add the targets of the bot | 添加机器人自身的攻击目标
    AddTargetsOf(bot, targets, invalidTargets, getOne);

    // Don't check for group member targets if we only need one | 若只需单个目标则跳过队友目标检查
    if (targets.empty() || !getOne)
    {
        // Add the targets of the members of the group | 添加小队成员或跟随主控的攻击目标
        Group* group = bot->GetGroup();
        if (group && !bot->InBattleGround())
        {
            AddTargetsOf(group, targets, invalidTargets, getOne);
        }

        Player* master = GetMaster();
        if (master && !bot->InBattleGround() && (!group || master->GetGroup() != group))
            AddTargetsOf(master, targets, invalidTargets, getOne);
    }

    // Convert the targets to guids | 将目标集合转换为 GUID 列表
    for (Unit* target : targets)
    {
        result.push_back(target->GetObjectGuid());
    }

    return result;
}

// 遍历小队成员并收集附近存活队友的战斗目标
void AttackersValue::AddTargetsOf(Group* group, std::set<Unit*>& targets, std::set<ObjectGuid>& invalidTargets, bool getOne)
{
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        // Only add group member targets that are alive and near the player | 仅添加存活且在附近的小队成员目标
        Player* member = sObjectMgr.GetPlayer(itr->guid);
        if (member && (member != bot) &&
           sServerFacade.IsAlive(member) &&
           member->IsInWorld() &&
           !member->IsBeingTeleported() &&
           (member->GetMapId() == bot->GetMapId()) && 
           (sServerFacade.GetDistance2d(bot, member) <= GetRange()))
        {
            AddTargetsOf(member, targets, invalidTargets, getOne);

            // Finish early if we only need one target | 若只需一个目标则提前结束
            if (getOne && !targets.empty())
            {
                break;
            }
        }
    }
}

// 收集指定玩家及其宠物相关的有效战斗目标
void AttackersValue::AddTargetsOf(Player* player, std::set<Unit*>& targets, std::set<ObjectGuid>& invalidTargets, bool getOne)
{
    // If the player is available | 若玩家单位有效且在世界中
    if (ai->IsSafe(player))
    {
        std::set<Unit*> units;

        // If the player is a bot | 若玩家由 Playerbot 控制
        PlayerbotAI* playerBot = player->GetPlayerbotAI();
        if (playerBot)
        {
            // Get all the units around the player | 获取玩家周围的所有潜在单位
            // NOTE: We don't validate the value here because it will be validated later on | 注意：此处暂不校验，留待后续统一验证
            const std::string ignoreValidate = std::to_string(true);
            const std::string range = std::to_string((int32)GetRange());
            const std::vector<std::string> qualifiers = { range, ignoreValidate };
            const std::list<ObjectGuid> possibleTargets = PAI_VALUE2(std::list<ObjectGuid>, "possible targets no los", Qualified::MultiQualify(qualifiers, ":"));
            for (const ObjectGuid& guid : possibleTargets)
            {
                if (Unit* unit = ai->GetUnit(guid))
                {
                    units.insert(unit);
                }
            }

            // Add the current target | 加入当前目标
            Unit* currentTarget = ai->GetUnit(PAI_VALUE(ObjectGuid, "current target"));
            if (currentTarget)
            {
                units.insert(currentTarget);
            }

            // Add the previous target | 加入上一个目标
            Unit* oldTarget = ai->GetUnit(PAI_VALUE(ObjectGuid, "old target"));
            
            if (oldTarget)
            {
                units.insert(oldTarget);
            }

            // Add the pull and attack targets (Only consider the owner bot) | 加入拉怪目标与进攻目标（仅限所属机器人）
            if (bot == player)
            {
                Unit* attackTarget = playerBot->GetUnit(PAI_VALUE(ObjectGuid, "attack target"));
                if (attackTarget)
                {
                    units.insert(attackTarget);
                }

                Unit* pullTarget = ai->GetUnit(PAI_VALUE(ObjectGuid, "pull target"));
                if (pullTarget)
                {
                    units.insert(pullTarget);
                }
            }
        }

        // Get the current attackers of the player | 加入当前正攻击该玩家的单位
        for (Unit* attacker : player->getAttackers())
        {
            units.insert(attacker);
        }

        // Add the duel opponent (Only consider the owner bot) | 加入决斗对手（仅限所属机器人）
        if (bot == player && bot->duel && bot->duel->opponent)
        {
            units.insert(bot->duel->opponent);
        }

        // Add the pet attackers (if nearby) | 加入附近宠物的攻击目标及攻击宠物的敌人
        Pet* pet = player->GetPet();
        if (pet && sServerFacade.GetDistance2d(bot, pet) <= GetRange())
        {
            for (Unit* attacker : pet->getAttackers())
            {
                units.insert(attacker);
            }
        }

        // Filter the units that are valid | 筛选出符合条件的有效战斗目标
        for (Unit* unit : units)
        {
            if (!ai->IsSafe(unit))
                continue;

            // Prevent checking a target that has already been validated | 跳过已验证过的目标
            if((targets.find(unit) == targets.end()))
            {
                // Prevent checking a target that has already been invalidated | 跳过已判定无效的目标
                if(InCombat(unit, player) || (invalidTargets.find(unit->GetObjectGuid()) == invalidTargets.end()))
                {
                    if (IsValid(unit, player, bot))
                    {
                        // Add the target to the list of combat targets | 将目标加入战斗目标集合
                        targets.insert(unit);

                        // Add the target's pet/guardian too | 同步加入目标的宠物与守护者
                        unit->CallForAllControlledUnits(AddGuardiansHelper(targets), CONTROLLED_PET | CONTROLLED_GUARDIANS | CONTROLLED_CHARM | CONTROLLED_MINIPET | CONTROLLED_TOTEMS);

                        if (getOne)
                        {
                            break;
                        }
                    }
                    else
                    {
                        invalidTargets.insert(unit->GetObjectGuid());
                    }
                }
            }
        }
    }
}

// 判断目标是否正在攻击玩家或其宠物，或是否为拉怪目标
bool AttackersValue::InCombat(Unit* target, Player* player, bool checkPullTargets)
{
    // Check if the the target is attacking the player | 检查目标是否在攻击该玩家
    bool inCombat = (target->getThreatManager().getThreat(player) > 0.0f) ||
                    (target->GetVictim() && (target->GetVictim() == player));

    // Check if the target is attacking the player's pet | 检查目标是否在攻击该玩家的宠物
    if(!inCombat)
    {
        Pet* pet = player->GetPet();
        if (pet)
        {
            inCombat = (target->getThreatManager().getThreat(pet) > 0.0f) ||
                       (target->GetVictim() && (target->GetVictim() == pet));
        }
    }

    if(!inCombat && checkPullTargets && player->GetPlayerbotAI())
    {
        inCombat = (PAI_VALUE(ObjectGuid, "attack target") == target->GetObjectGuid()) ||
                   (PAI_VALUE(ObjectGuid, "pull target") == target->GetObjectGuid());
    }

    return inCombat;
}

// 综合校验目标（玩家/NPC）是否满足有效攻击者条件（距离、可达性、PvP策略、脱离状态等）
bool AttackersValue::IsValid(Unit* target, Player* player, Player* owner, bool checkInCombat, bool validatePossibleTarget)
{
    Player* playerToCheckAgainst = owner != nullptr ? owner : player;

    // Validate possible target | 先校验是否为合法的潜在目标
    if (validatePossibleTarget && !PossibleTargetsValue::IsValid(target, playerToCheckAgainst))
    {
        return false;
    }

    // This will be used on both enemy player and npc checks | 后续将用于敌对玩家与 NPC 的通用检测
    const bool inPvPProhibitedZone = sPlayerbotAIConfig.IsInPvpProhibitedZone(sServerFacade.GetAreaId(target));

    // If the target is a player | 目标为玩家时的校验逻辑
    Player* enemyPlayer = dynamic_cast<Player*>(target);
    if (enemyPlayer)
    {
        // Don't consider enemy players if pvp strategy is not set | 未开启 PvP 策略时不将敌对玩家视为攻击者
        if (playerToCheckAgainst->GetPlayerbotAI() && !playerToCheckAgainst->GetPlayerbotAI()->HasStrategy("pvp", BotState::BOT_STATE_COMBAT))
        {
            return false;
        }

        // If the enemy player is in a PVP Prohibited zone | 若敌对玩家处于禁止 PvP 区域则忽略
        if (inPvPProhibitedZone)
        {
            return false;
        }

        // Don't check distance on duel opponents | 决斗对手不做视距检查
        if (!player->duel || (player->duel && (player->duel->opponent != target)))
        {
            // If the enemy player is not within sight distance | 敌对玩家超出最大攻击距离则忽略
            if (!enemyPlayer->IsWithinDist(playerToCheckAgainst, EnemyPlayerValue::GetMaxAttackDistance(playerToCheckAgainst), false))
            {
                return false;
            }

            // If the enemy player can't be reached (e.g. under the map) | 敌对玩家不可达（如在地下/模型外）则忽略
            if (!EnemyPlayersValue::IsReachable(enemyPlayer, playerToCheckAgainst))
            {
                return false;
            }
        }
    }
    // If the target is a NPC | 目标为 NPC 时的校验逻辑
    else
    {
        // If the target is not fighting the player (and if the owner bot is not pulling the target) | 若目标未在战斗中（且非所属机器人正在拉怪的目标）则忽略
        if (checkInCombat && !InCombat(target, player, (player == owner)))
        {
            bool isRtiTarget = false;
            if (player->GetPlayerbotAI() && !player->GetPlayerbotAI()->HasActivePlayerMaster())
            {
                Unit* rtiTarget = player->GetPlayerbotAI()->GetUnit(PAI_VALUE(ObjectGuid, "rti target"));
                if (target == rtiTarget)
                    isRtiTarget = true;
            }

            if(!isRtiTarget)
                return false;
        }

        // If the target is a player's pet and in a PvP prohibited zone | 若目标是处于禁 PvP 区的玩家宠物则忽略
        if (target->GetObjectGuid().IsPet() && inPvPProhibitedZone)
        {
            return false;
        }

        // If the target is evading | 若目标处于脱战闪避状态则忽略
        const Creature* creature = dynamic_cast<Creature*>(target);
        if (creature)
        {
            if (creature->GetCombatManager().IsInEvadeMode())
            {
                return false;
            }
        }        
    }

    if (IgnoreTarget(target, playerToCheckAgainst))
        return false;

    return true;
}

// 判断是否应忽略特定目标（如非战斗跑路时的高等级怪、特定任务/木桩过滤等）
bool AttackersValue::IgnoreTarget(Unit* target, Player* playerToCheckAgainst)
{
    if (!playerToCheckAgainst->GetPlayerbotAI())
        return false; 

    PlayerbotAI* ai = playerToCheckAgainst->GetPlayerbotAI();
    AiObjectContext* context = ai->GetAiObjectContext();

    //Ignore Hard hostiles while not already fighting. | 非战斗状态下忽略高于自身 5 级以上的高危敌人
    if (target->GetLevel() > (playerToCheckAgainst->GetLevel() + 5) && ai->GetState() == BotState::BOT_STATE_NON_COMBAT)
    {
        //When traveling a long distance. | 长途旅行中忽略高危目标
        if (AI_VALUE(bool, "travel target traveling") && AI_VALUE2(float, "distance", "travel target") > sPlayerbotAIConfig.reactDistance)
            return true;

        //When moving to master far away. | 向距离较远的主控移动时忽略高危目标
        if ((ai->HasStrategy("follow", BotState::BOT_STATE_NON_COMBAT) ||
            ai->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT)) &&
            AI_VALUE2(bool, "trigger active", "out of react range"))
            return true;

        if (ai->GetMaster() && !ai->HasActivePlayerMaster())
        {
            Player* player = ai->GetMaster();

            //When master is traveling a long distance. | 当主控处于长途移动中时忽略高危目标
            if (PAI_VALUE(bool, "travel target traveling") && PAI_VALUE2(float, "distance", "travel target") > sPlayerbotAIConfig.reactDistance)
                return true;
        }
    }

    Player* enemyPlayer = dynamic_cast<Player*>(target);

    if (!enemyPlayer)
    {
        bool isDummy = false;


        if (WorldPosition(playerToCheckAgainst).isOverworld() && target->AI() && target->AI()->IsPreventingDeath())
        {

            isDummy = true;
        }

        uint32 entry = target->GetEntry();

#define TRAINING_DUMMY_NPC_ENTRY1 190013
#define TRAINING_DUMMY_NPC_ENTRY2 190014
#define TRAINING_DUMMY_NPC_ENTRY3 190015
#define THERAMORE_COMBAT_DUMMY 4952
#define NAXXRAMAS_COMBAT_DUMMY 16211
#ifdef MANGOSBOT_TWO  
#define INITATES_TRAINING_DUMMY 32541
#endif

        switch (entry)
        {
        case TRAINING_DUMMY_NPC_ENTRY1:
        case TRAINING_DUMMY_NPC_ENTRY2:
        case TRAINING_DUMMY_NPC_ENTRY3:
        case THERAMORE_COMBAT_DUMMY:
        case NAXXRAMAS_COMBAT_DUMMY:
#ifdef MANGOSBOT_TWO     
        case INITATES_TRAINING_DUMMY:
#endif
            isDummy = true;
        }

        if (isDummy && ai->GetFixedBotNumber(BotTypeNumber::DUMMY_ATTACK_NUMBER, 10, 0.2f)) //90% of bots, cycle every 5 min. | 90% 机器人在 5 分钟周期内过滤训练假人
            return true;
    }

    return false;
}

// 将当前攻击者列表格式化为可读名称字符串
std::string AttackersValue::Format()
{
    std::ostringstream out;

    for (auto& target : value)
    {
        if(target != value.front())
        out << ",";

        WorldObject* wo = ai->GetWorldObject(target);

        if (wo)
            out << wo->GetName();
        else
            out << target;      
    }

    return out.str();
}

// 过滤攻击者列表，返回当前目标指向机器人本体的单位
std::list<ObjectGuid> AttackersTargetingMeValue::Calculate()
{
    std::list<ObjectGuid> result;

    const std::list<ObjectGuid>& attackers = AI_VALUE(std::list<ObjectGuid>, "attackers");
    for (const ObjectGuid& attackerGuid : attackers)
    {
        Unit* attacker = ai->GetUnit(attackerGuid);
        if (attacker && (attacker->GetTarget() == bot || attacker->GetVictim() == bot))
        {
            result.push_back(attackerGuid);
        }
    }

    return result;
}
