/// RPG 城镇与NPC交互触发器实现

#include "playerbot/playerbot.h"
#include "RpgTriggers.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/actions/GuildCreateActions.h"
#include "Social/SocialMgr.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/values/ItemUsageValue.h"
#include "playerbot/strategy/values/QuestValues.h"
#include "playerbot/TravelMgr.h"
#include "AI/ScriptDevAI/ScriptDevAIMgr.h"

using namespace ai;

/// 检测 RPG 交互基类是否满足激活条件（自由机器人或当前目标匹配旅行目标）
bool RpgTrigger::IsActive() 
{ 
    if (!ai->HasRealPlayerMaster())
        return true;


    if (AI_VALUE(GuidPosition, "rpg target").GetEntry())
    {
        if (AI_VALUE(GuidPosition, "rpg target").GetEntry() == AI_VALUE(TravelTarget*, "travel target")->GetEntry())
            return true;
    }

    return false;
};

/// 检测当前 RPG 目标是否为飞行管理员且存在已解锁可达航线
bool RpgTaxiTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_FLIGHTMASTER))
        return false;

    uint32 node = sObjectMgr.GetNearestTaxiNode(guidP.getX(), guidP.getY(), guidP.getZ(), guidP.getMapId(), bot->GetTeam());

    if (!node)
        return false;

    if (!bot->m_taxi.IsTaximaskNodeKnown(node))
        return false;

    std::vector<uint32> nodes;
    for (uint32 i = 0; i < sTaxiPathStore.GetNumRows(); ++i)
    {
        TaxiPathEntry const* entry = sTaxiPathStore.LookupEntry(i);
        if (entry && entry->from == node && (bot->m_taxi.IsTaximaskNodeKnown(entry->to) || bot->isTaxiCheater()))
        {
            return true;
        }
    }

    return false;
}

/// 检测当前 RPG 目标是否为尚未解锁飞行点的飞行管理员
bool RpgDiscoverTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_FLIGHTMASTER))
        return false;

    if (bot->isTaxiCheater())
        return false;

    uint32 node = sObjectMgr.GetNearestTaxiNode(guidP.getX(), guidP.getY(), guidP.getZ(), guidP.getMapId(), bot->GetTeam());

    if (bot->m_taxi.IsTaximaskNodeKnown(node))
        return false;

    return true;
}

/// 检测当前 RPG 目标是否可接取任务（检查任务栏空位、阵营与等级）
bool RpgStartQuestTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (AI_VALUE(uint8, "free quest log slots") == 0)
        return false;

    if (!guidP.IsCreature() && !guidP.IsGameObject())
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (guidP.IsUnit())
    {
        Unit* unit = guidP.GetUnit(bot->GetInstanceId());
        if (unit && !unit->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
            return false;
    }

    int32 entry = guidP.IsCreature() ? guidP.GetEntry() : -1 * (int32)guidP.GetEntry();

    if (AI_VALUE(bool, "can fight equal"))
    {
        if (AI_VALUE2(bool, "can accept quest npc", entry))
            return true;

        if (!AI_VALUE2(bool, "can accept quest low level npc", entry) )
            return false;

        if (entry == AI_VALUE(TravelTarget*, "travel target")->GetEntry())
            return true;
    }
    else
    {
        if (AI_VALUE2(bool, "can accept quest low level npc", entry))
            return true;
    }

    return false;
}

/// 检测当前 RPG 目标是否可交付已完成任务
bool RpgEndQuestTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.IsCreature() && !guidP.IsGameObject())
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    int32 entry = guidP.IsCreature() ? guidP.GetEntry() : -1 * (int32)guidP.GetEntry();

    if (AI_VALUE2(bool, "can turn in quest npc", entry))
        return true;

    return false;
}

/// 检测当前 RPG 目标是否可接取可重复任务
bool RpgRepeatQuestTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (AI_VALUE(uint8, "free quest log slots") < 10)
        return false;

    if (!guidP.IsCreature() && !guidP.IsGameObject())
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (AI_VALUE2(bool, "can repeat quest npc", guidP.GetEntry()))
        return true;

    return false;
}

/// 检测当前 RPG 商人是否售卖机器人所需的有用物品
bool RpgBuyTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_VENDOR))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (!AI_VALUE(bool, "can buy"))
        return false;

    if (!AI_VALUE2(bool, "vendor has useful item", guidP.GetEntry()))
        return false;

    return true;
}

/// 检测当前 RPG 商人是否可以出售背包物品
bool RpgSellTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_VENDOR))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (!AI_VALUE(bool, "can sell"))
        return false;

    return true;
}

/// 检测当前 RPG 拍卖师是否可以进行拍卖出售
bool RpgAHSellTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_AUCTIONEER))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (GuidPosition(bot).IsHostileTo(guidP, bot->GetInstanceId()))
        return false;

    if (!AI_VALUE(bool, "can ah sell"))
        return false;

    return true;
}

/// 检测当前 RPG 拍卖师是否可以进行拍卖购买
bool RpgAHBuyTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_AUCTIONEER))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (GuidPosition(bot).IsHostileTo(guidP, bot->GetInstanceId()))
        return false;

    if (!AI_VALUE(bool, "can ah buy"))
        return false;

    return true;
}

/// 检测当前 RPG 目标是否为邮箱且有待收取邮件
bool RpgGetMailTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.isGoType(GAMEOBJECT_TYPE_MAILBOX))
        return false;

    if (!AI_VALUE(bool, "can get mail"))
        return false;

    return true;
}

/// 检测当前 RPG 目标是否为修理NPC且自身或队友需要修理
bool RpgRepairTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_REPAIR))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (bot->GetGroup() && bot->GetGroup()->IsLeader(bot->GetObjectGuid()) && AI_VALUE2_LAZY(bool, "group or", "can repair,following party,near leader"))
        return true;

    if (AI_VALUE(bool, "can repair"))
        return true;

    return false;
}

/// 判定指定生物信息是否为该玩家可用的训练师类型（职业/宠物/骑术/商业技能）
bool RpgTrainTrigger::IsTrainerOf(CreatureInfo const* cInfo, Player* pPlayer)
{

    switch (cInfo->TrainerType)
    {
    case TRAINER_TYPE_CLASS:
        if (pPlayer->getClass() != cInfo->TrainerClass)
        {
            return false;
        }
        break;
    case TRAINER_TYPE_PETS:
        if (pPlayer->getClass() != CLASS_HUNTER)
        {
            return false;
        }
        break;
    case TRAINER_TYPE_MOUNTS:
        if (cInfo->TrainerRace && pPlayer->getRace() != cInfo->TrainerRace)
        {
            // Allowed to train if exalted | 若声望达到崇拜则允许学习跨种族骑术
            if (FactionTemplateEntry const* faction_template = sFactionTemplateStore.LookupEntry(cInfo->Faction))
            {
                if (pPlayer->GetReputationRank(faction_template->faction) == REP_EXALTED)
                    return true;
            }
            return false;
        }
        break;
    case TRAINER_TYPE_TRADESKILLS:
        if (cInfo->TrainerSpell && !pPlayer->HasSpell(cInfo->TrainerSpell))
        {
            return false;
        }
        break;
    default:
        return false;                                   // checked and error output at creature_template loading | 已在生物模板加载时验证并记录错误
    }
    return true;
}

/// 检测当前训练师是否有机器人可学习且金币充足的法术/技能
bool RpgTrainTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_TRAINER))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    CreatureInfo const* cInfo = guidP.GetCreatureTemplate();

    if (!IsTrainerOf(cInfo, bot))
        return false;

    // check present spell in trainer spell list | 检查训练师法术列表中的当前法术
    TrainerSpellData const* cSpells = sObjectMgr.GetNpcTrainerSpells(guidP.GetEntry());

    uint32 trainerId = cInfo->TrainerTemplateId;
    TrainerSpellData const* tSpells = trainerId ? sObjectMgr.GetNpcTrainerTemplateSpells(trainerId) : nullptr;

    if (!cSpells && !tSpells)
    {
        return false;
    }

    FactionTemplateEntry const* factionTemplate = sFactionTemplateStore.LookupEntry(cInfo->Faction);
    float fDiscountMod = bot->GetReputationPriceDiscount(factionTemplate);

    TrainerSpellMap trainer_spells;
    if (cSpells)
        trainer_spells.insert(cSpells->spellList.begin(), cSpells->spellList.end());
    if (tSpells)
        trainer_spells.insert(tSpells->spellList.begin(), tSpells->spellList.end());

    for (TrainerSpellMap::const_iterator itr = trainer_spells.begin(); itr != trainer_spells.end(); ++itr)
    {
        TrainerSpell const* tSpell = &itr->second;

        if (!tSpell)
            continue;

        uint32 reqLevel = 0;

        reqLevel = tSpell->isProvidedReqLevel ? tSpell->reqLevel : std::max(reqLevel, tSpell->reqLevel);
        TrainerSpellState state = bot->GetTrainerSpellState(tSpell, reqLevel);
        if (state != TRAINER_SPELL_GREEN)
            continue;

        uint32 spellId = tSpell->spell;
        const SpellEntry* const pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
        if (!pSpellInfo)
            continue;

#ifdef MANGOSBOT_ZERO
        if (tSpell->learnedSpell)
        {
            bool learned = true;
            if (bot->HasSpell(tSpell->learnedSpell))
            {
                learned = false;
            }
            else
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (pSpellInfo->Effect[j] == SPELL_EFFECT_LEARN_SPELL)
                    {
                        learned = false;
                        uint32 learnedSpell = pSpellInfo->EffectTriggerSpell[j];

                        if (!bot->HasSpell(learnedSpell))
                        {
                            learned = true;
                            break;
                        }
                    }
                }
            }
            if (!learned)
                continue;
        }
#else
        if (!tSpell->learnedSpell.empty())
        {
            bool anySpellLearned = false;
            for (auto& learnedSpell : tSpell->learnedSpell)
            {
                bool learned = true;
                if (bot->HasSpell(learnedSpell))
                {
                    learned = false;
                }
                else
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        if (pSpellInfo->Effect[j] == SPELL_EFFECT_LEARN_SPELL)
                        {
                            learned = false;
                            uint32 learnedSpell = pSpellInfo->EffectTriggerSpell[j];

                            if (!bot->HasSpell(learnedSpell))
                            {
                                learned = true;
                                break;
                            }
                        }
                    }
                }
                if (learned)
                    anySpellLearned = true;
            }
            if (!anySpellLearned)
                continue;
        }
#endif

        NeedMoneyFor budgetType = NeedMoneyFor::spells;

        switch (cInfo->TrainerType)
        {
        case TRAINER_TYPE_CLASS:
            budgetType = NeedMoneyFor::spells;
            break;
        case TRAINER_TYPE_PETS:
            budgetType = NeedMoneyFor::anything;
            break;
        case TRAINER_TYPE_MOUNTS:
            budgetType = NeedMoneyFor::mount;
            break;
        case TRAINER_TYPE_TRADESKILLS:
            budgetType = NeedMoneyFor::skilltraining;
            break;
        default:
            budgetType = NeedMoneyFor::anything;
            break;
        }

        uint32 cost = uint32(floor(tSpell->spellCost * fDiscountMod));
        if (cost > AI_VALUE2(uint32, "free money for", (uint32)budgetType))
            continue;

        return true;
    }
    return false;
}

/// 检测当前 RPG 友方生物是否受伤且需要治疗
bool RpgHealTrigger::IsActive()
{
    if (!ai->IsHeal(bot))
        return false;

    GuidPosition guidP(getGuidP());

    if (guidP.IsPlayer())
        return false;

    Unit* unit = guidP.GetUnit(bot->GetInstanceId());

    if (!unit)
        return false;

    if (!unit->IsFriend(bot))
        return false;

    if (unit->IsDead() || unit->GetHealthPercent() >= 100)
        return false;

    return true;
}

/// 检测是否应与当前旅店老板重新绑定炉石位置
bool RpgHomeBindTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_INNKEEPER))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    //Do not update for realplayers/always online when at max level. | 真人玩家或满级常驻在线小号不自动更改炉石绑定
    if ((ai->IsRealPlayer() || sPlayerbotAIConfig.IsFreeAltBot(bot)) && bot->GetLevel() == DEFAULT_MAX_LEVEL)
        return false;

    WorldPosition currentBind = AI_VALUE(WorldPosition, "home bind");
    WorldPosition newBind = (guidP.sqDistance2d(bot) > INTERACTION_DISTANCE * INTERACTION_DISTANCE) ? guidP : bot;

    //Do not update if there's almost not change. | 若新旧绑定点距离过近则不更新
    if (newBind.fDist(currentBind) < INTERACTION_DISTANCE * 2) 
        return false;

    //Update if the new bind is closer to the group leaders bind than the old one. | 若新绑定点比旧绑定点更接近队长炉石位置，则更新
    if (bot->GetGroup() && !ai->IsGroupLeader() && ai->GetGroupMaster() && ai->GetGroupMaster()->GetPlayerbotAI())
    {
        Player* player = ai->GetGroupMaster();

        if (!ai->IsSafe(player))
            return false;

        WorldPosition leaderBind = PAI_VALUE(WorldPosition, "home bind");

        float newBindDistanceToMasterBind = newBind.fDist(leaderBind);
        float oldBindDistanceToMasterBind = currentBind.fDist(leaderBind);

        return newBindDistanceToMasterBind < oldBindDistanceToMasterBind;
    }

    //Do not update if the new bind is pretty close already. | 若当前炉石绑定点距离已经很近则不更新
    if (currentBind.fDist(bot) < 500.0f)
        return false;

    return true;
}

/// 检测主城军官是否满足加入战场队列条件
bool RpgQueueBGTrigger::IsActive()
{
    // skip bots not in continents | 跳过不在大世界大陆上的机器人
    if (!WorldPosition(bot).isOverworld()) // bg, raid, dungeon | 如战场、团队副本、地下城
        return false;

    GuidPosition guidP(getGuidP());

    if (!guidP.IsCreature())
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (bot->GetGroup() && !bot->GetGroup()->IsLeader(bot->GetObjectGuid()))
        return false;

    if (AI_VALUE(BattleGroundTypeId, "rpg bg type") == BATTLEGROUND_TYPE_NONE)
        return false;

    Action* action = context->GetAction("free bg join");

    if (!action->isUseful())
        return false;

    return true;
}

/// 检测公会注册员处是否可购买公会签名表
bool RpgBuyPetitionTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_PETITIONER))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (!BuyPetitionAction::canBuyPetition(bot))
        return false;

    return true;
}

/// 检测游戏对象类型是否属于可交互类别（门、按钮、箱子、钓鱼点等）
bool RpgUseTrigger::IsActive()
{
    if (ai->HasActivePlayerMaster())
        return false;

    GuidPosition guidP(getGuidP());

    if (!guidP.IsGameObject())
        return false;

    GameObjectInfo const* goInfo = guidP.GetGameObjectInfo();

    switch (goInfo->type) {
    case GAMEOBJECT_TYPE_DOOR:                          // 0
    case GAMEOBJECT_TYPE_BUTTON:                        // 1
    case GAMEOBJECT_TYPE_QUESTGIVER:                    // 2
    case GAMEOBJECT_TYPE_CHEST:                         // 3
    case GAMEOBJECT_TYPE_GENERIC:                       // 5
    case GAMEOBJECT_TYPE_TRAP:                          // 6
    case GAMEOBJECT_TYPE_CHAIR:                         // 7 Sitting: Wooden bench, chairs
    case GAMEOBJECT_TYPE_SPELL_FOCUS:                   // 8
    case GAMEOBJECT_TYPE_GOOBER:                        // 10
    case GAMEOBJECT_TYPE_CAMERA:                        // 13
    case GAMEOBJECT_TYPE_FISHINGNODE:                   // 17 fishing bobber
    case GAMEOBJECT_TYPE_SUMMONING_RITUAL:              // 18
#ifndef MANGOSBOT_TWO
    case GAMEOBJECT_TYPE_AUCTIONHOUSE:
    case GAMEOBJECT_TYPE_LOTTERY_KIOSK:
#endif
    case GAMEOBJECT_TYPE_SPELLCASTER:                   // 22
    case GAMEOBJECT_TYPE_MEETINGSTONE:                  // 23
    case GAMEOBJECT_TYPE_FLAGSTAND:                     // 24
    case GAMEOBJECT_TYPE_FISHINGHOLE:                   // 25
    case GAMEOBJECT_TYPE_FLAGDROP:                      // 26
        return true;
    default:
        return false;
    }   
}

/// 检测是否需要针对当前目标执行任务物品或任务对象交互
bool RpgQuestUseTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP)
        return false;

    if (RpgUseTrigger::IsActive())
    {
        switch (guidP.GetEntry())
        {
        case 190767: return AI_VALUE2(bool, "need quest objective", "12701"); //Only when we need "Inconspicuous mine car" | 仅当需要任务“不起眼的矿车”（12701）目标时触发
        }
    }

    if (guidP.IsUnit())
        return CanUseItemOn::HasQuestItemForEntry(bot->GetPlayerbotAI(), (int32)guidP.GetEntry());

    return false;
}

/// 检测是否启用 LLM 且满足概率及周围玩家条件以触发 AI 闲聊
bool RpgAIChatTrigger::IsActive()
{
    if (sPlayerbotAIConfig.llmEnabled == 0)
        return false;

    if (FarFromRpgTargetTrigger::IsActive())
        return false;    

    if (!ai->HasStrategy("ai chat", BotState::BOT_STATE_NON_COMBAT) && sPlayerbotAIConfig.llmEnabled < 3)
        return false;

    if (!sPlayerbotAIConfig.llmRpgAIChatChance || !(urand(0, 99) < sPlayerbotAIConfig.llmRpgAIChatChance))
        return false;

    if (!ai->HasPlayerNearby(sWorld.getConfig(CONFIG_FLOAT_LISTEN_RANGE_SAY)))
        return false;

    GuidPosition guidP(getGuidP());
 
    if (guidP.IsPlayer())
    {
        Player* player = guidP.GetPlayer();

        if (!player || player->isRealPlayer())
            return false;
    }

    return true;
};

/// 以随机概率触发闲暇 RPG 施法
bool RpgSpellTrigger::IsActive()
{
    //GuidPosition guidP(getGuidP()); | 获取 RPG 目标位置信息

    return (!urand(0, 10));
}

/// 检测背包空间及制作法术/施法焦点（如铁砧、熔炉）条件，判断是否可执行制造
bool RpgCraftTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (AI_VALUE(uint8, "bag space") > 80)
        return false;

    if (ai->HasCheat(BotCheatMask::item) && AI_VALUE(uint8, "bag space") > 60)
        return false;

    if (!guidP.GetWorldObject(bot->GetInstanceId()))
        return false;

    std::vector<uint32> spellIds = AI_VALUE(std::vector<uint32>, "craft spells");

    for (uint32 spellId : spellIds)
    {
        const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);

        if (pSpellInfo->RequiresSpellFocus)
        {
            if (!guidP.IsGameObject())
                continue;

            if (guidP.GetGameObjectInfo()->type != GAMEOBJECT_TYPE_SPELL_FOCUS)
                continue;

            if (guidP.GetGameObjectInfo()->spellFocus.focusId != pSpellInfo->RequiresSpellFocus)
                continue;
        }

        if (!AI_VALUE2(bool, "can craft spell", spellId))
            continue;

        if (!AI_VALUE2(bool, "should craft spell", spellId))
            continue;

        return true;
    }

    return false;
}

/// 判断玩家是否为可交易/附魔的友好目标（小号、同公会、同队或随机概率）
bool RpgTradeUsefulTrigger::isFriend(Player* player)
{
    if (ai->IsAlt() && GetMaster() == player)
        return true;

    if (player->GetPlayerbotAI() && player->GetPlayerbotAI()->GetMaster() == bot && player->GetPlayerbotAI()->IsAlt())
        return true;

    if (player->GetGuildId() && player->GetGuildId() == bot->GetGuildId())
        return true;

    if (bot->GetGroup() == player->GetGroup() && !urand(0, 5))
        return true;

    if (!urand(0, 20))
        return true;

    return false;
}

/// 检测是否满足条件与目标玩家交易有用物品
bool RpgTradeUsefulTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.IsPlayer())
        return false;

    Player* player = guidP.GetPlayer();


    if (!player)
        return false;

    if (player->GetTrader() == bot && bot->GetTrader() == player) //Continue trading please. | 若已在交易中则继续交易
        return true;

    if (!isFriend(player))
        return false;

    if (!player->IsWithinLOSInMap(bot))
        return false;

    //Trading with someone else | 对方或自身正在与其他玩家交易
    if (player->GetTrader() && player->GetTrader() != bot)
        return false;

    if (bot->GetTrader() && bot->GetTrader() != player)
        return false;

    if (AI_VALUE(std::list<Item*>, "items useful to give").empty())
        return false;

    return true;
}

/// 检测是否满足条件为目标玩家装备进行附魔
bool RpgEnchantTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.IsPlayer())
        return false;

    Player* player = guidP.GetPlayer();


    if (!player)
        return false;

    //if (player->GetTrader() == bot && bot->GetTrader() == player) //Continue trading please.
    //    return true;

    if (!isFriend(player))
        return false;

    if (!player->IsWithinLOSInMap(bot))
        return false;

    //Trading with someone else
    //if (player->GetTrader() && player->GetTrader() != bot)
     //   return false;

    //if (bot->GetTrader() && bot->GetTrader() != player)
    //    return false;

    if (AI_VALUE(std::list<Item*>, "items useful to enchant").empty())
        return false;

    return true;
}

/// 检测当前区域、等级差及血量是否允许向目标玩家发起决斗
bool RpgDuelTrigger::IsActive()
{
    if(!ai->HasStrategy("start duel", BotState::BOT_STATE_NON_COMBAT))
        return false;

    // Less spammy duels | 避免低等级频繁发起无意义决斗
    if (bot->GetLevel() < 3)
        return false;

    if (ai->HasRealPlayerMaster())
    {
        // do not auto duel if master is not afk | 若真人主人未暂离（AFK），则不主动发起决斗
        if (ai->GetMaster() && !ai->GetMaster()->isAFK())
            return false;
    }

    // do not auto duel with low hp | 生命值过低时不自动发起决斗
    if (AI_VALUE2(uint8, "health", "self target") < 90)
        return false;

    GuidPosition guidP(getGuidP());

    if (!guidP.IsPlayer())
        return false;

    Player* player = guidP.GetPlayer();

    if (!player)
        return false;

    if (player->GetLevel() > bot->GetLevel() + 3)
        return false;

    if (bot->GetLevel() > player->GetLevel() + 10)
        return false;

    // caster or target already have requested duel | 自身或目标已在决斗中，或被对方屏蔽
    if (bot->duel || player->duel || !player->GetSocial() || player->GetSocial()->HasIgnore(bot->GetObjectGuid()))
        return false;

    AreaTableEntry const* targetAreaEntry = GetAreaEntryByAreaID(sServerFacade.GetAreaId(player));
    if (targetAreaEntry && !(targetAreaEntry->flags & AREA_FLAG_DUEL))
    {
        // Dueling isn't allowed here | 当前区域禁止决斗
        return false;
    }

    if (!AI_VALUE(std::list<ObjectGuid>, "all targets").empty())
        return false;

    return true;
}

/// 检测背包中是否有可对当前 RPG 目标使用的任务物品
bool RpgItemTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (guidP.IsPlayer())
        return false;

    std::list<Item*> questItems = AI_VALUE2(std::list<Item*>, "inventory items", "quest");

    for (auto item : questItems)
    {
        if (AI_VALUE2(bool, "can use item on", Qualified::MultiQualify({ std::to_string(item->GetProto()->ItemId),guidP.to_string() }, ",")))
            return true;
    }

    return false;
}

/// 检测附近有玩家时是否触发随机跳跃
bool RandomJumpTrigger::IsActive()
{
    return bot->IsInWorld() && ai->HasPlayerNearby() && !ai->IsJumping() && frand(0.0f, 1.0f) < sPlayerbotAIConfig.jumpRandomChance;
}

/// 检测目标是否支持 SpellClick 交互（排除天灾狮鹫及已乘载具状态）
bool RpgSpellClickTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

#ifdef MANGOSBOT_TWO
    if (!guidP.IsCreatureOrVehicle())
        return false;

    switch(guidP.GetEntry())
    {
    case 29488: //Scourge gryphon
    case 29501:
        return false;
    }

    if (TransportInfo* transportInfo = bot->GetTransportInfo())
    {
        if (transportInfo && transportInfo->IsOnVehicle())
            return false;
    }
#endif   

    return ai->CanSpellClick(guidP);
}

/// 检测目标生物是否拥有有效 Gossip 对话菜单项
bool RpgGossipTalkTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.IsCreature())
        return false;

    GossipMenuItemsMapBounds pMenuItemBounds = sObjectMgr.GetGossipMenuItemsMapBounds(guidP.GetCreatureTemplate()->GossipMenuId);
    if (pMenuItemBounds.first == pMenuItemBounds.second)
        return false;

    Creature* creature = guidP.GetCreature(bot->GetInstanceId());

    if (!creature)
        return false;

    if (!creature->isGossip())
        return false;

#ifdef MANGOSBOT_TWO
    switch (guidP.GetEntry())
    {
    case 28653: //Salanar the Horseman | 骑手萨拉纳尔
        return AI_VALUE2(bool, "need quest objective", "12687,0"); //Only when we need "Into the Realm of Shadows" | 仅当需要任务“进入暗影界”（12687）目标时触发
    case 35365: //Behsten (xp gain disable) Maybe add back later for some bots? | 贝斯腾（关闭经验Npc）
    case 35364: //Slahtz | 斯拉兹
        return false;
    }
#endif

    if (!sScriptDevAIMgr.OnGossipHello(bot, creature))
    {
        bot->PrepareGossipMenu(creature, creature->GetDefaultGossipMenuId());
    }

    if (!bot->GetPlayerMenu())
        return false;

    GossipMenu& menu = bot->GetPlayerMenu()->GetGossipMenu();

    if (!menu.MenuItemCount())
        return false;

    return true;
}

/// 检测目标银行职员处是否需要存物
bool RpgBankDepositTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_BANKER))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (!AI_VALUE(bool, "should bank deposit"))
        return false;

    return true;
}

/// 检测目标银行职员处是否需要取物
bool RpgBankWithdrawTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.HasNpcFlag(UNIT_NPC_FLAG_BANKER))
        return false;

    if (guidP.IsHostileTo(bot))
        return false;

    if (!AI_VALUE(bool, "should bank withdraw"))
        return false;

    return true;
}

#ifndef MANGOSBOT_ZERO
/// 检测目标公会银行处是否需要存物
bool RpgGuildBankDepositTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.isGoType(GAMEOBJECT_TYPE_GUILD_BANK))
        return false;

    if (!bot->GetGuildId())
        return false;

    if (!AI_VALUE(bool, "should guild bank deposit"))
        return false;

    return true;
}

/// 检测目标公会银行处是否需要取物
bool RpgGuildBankWithdrawTrigger::IsActive()
{
    GuidPosition guidP(getGuidP());

    if (!guidP.isGoType(GAMEOBJECT_TYPE_GUILD_BANK))
        return false;

    if (!bot->GetGuildId())
        return false;

    if (!AI_VALUE(bool, "should guild bank withdraw"))
        return false;

    return true;
}
#endif