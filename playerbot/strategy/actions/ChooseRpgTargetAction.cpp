
#include "playerbot/playerbot.h"
#include "ChooseRpgTargetAction.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/values/PossibleRpgTargetsValue.h"
#include "playerbot/TravelMgr.h"
#include "playerbot/strategy/values/BudgetValues.h"
#include "GuildCreateActions.h"
#include "RpgSubActions.h"
#include "playerbot/strategy/values/ItemUsageValue.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "playerbot/strategy/values/TravelValues.h"
#include "playerbot/strategy/values/FreeMoveValues.h"
#include <iomanip>

using namespace ai;

/// 判断两个单位是否正在攻击相同的目标
bool ChooseRpgTargetAction::HasSameTarget(ObjectGuid guid, uint32 max, std::list<ObjectGuid>& nearGuids)
{
    if (ai->HasRealPlayerMaster())
        return false;

    uint32 num = 0;

    for (auto& i : nearGuids)
    {
        Player* player = sObjectMgr.GetPlayer(i);

        if (!player)
            continue;

        if (!ai->IsSafe(player))
            continue;

        PlayerbotAI* ai = player->GetPlayerbotAI();

        if (!ai)
            continue;

        if (!ai->AllowActivity(GRIND_ACTIVITY))
            continue;

        if (PAI_VALUE(GuidPosition,"rpg target") != guid)
            continue;

        num++;

        if (num >= max)
            return true;
    }

    return false;
}

#define SkipRpgTarget(reason){ if(debug) debugTargets[guidP] = reason; continue;}

std::unordered_map<ObjectGuid, float> ChooseRpgTargetAction::GetTargets(Player* requester, bool debug)
{
    TravelTarget* travelTarget = AI_VALUE(TravelTarget*, "travel target");
    focusQuestTravelList focusList = AI_VALUE(focusQuestTravelList, "focus travel target");

    GuidPosition masterRpgTarget;
    if (requester && ai->IsSafe(requester) && requester->GetPlayerbotAI())
    {
        Player* player = requester;
        masterRpgTarget = PAI_VALUE(GuidPosition, "rpg target");
    }

    std::unordered_map<ObjectGuid, float> targets;
    std::vector<ObjectGuid> targetList;

    // Gather all nearby npc's (+some creatures), game objects and players. (收集附近所有 NPC（及部分生物）、游戏对象和玩家。)
    std::list<ObjectGuid> possibleTargets = AI_VALUE(std::list<ObjectGuid>, "possible rpg targets");
    std::list<ObjectGuid> possibleObjects = bot->GetMap()->IsDungeon() ? AI_VALUE(std::list<ObjectGuid>, "nearest game objects") : AI_VALUE(std::list<ObjectGuid>, "nearest game objects no los");
    std::list<ObjectGuid> possiblePlayers = AI_VALUE(std::list<ObjectGuid>, "nearest friendly players");

    // List of targets that we rpg'ed with before and should be ignored. (此前已交互过且应暂时忽略的 RPG 目标列表。)
    std::set<ObjectGuid>& ignoreList = AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target");

    // Add all targets with an initial priority of 0. (以初始优先级 0 添加所有候选目标。)
    for (auto target : possibleTargets)
        targets[target] = -1.0f;

    for (auto target : possibleObjects)
        targets[target] = -1.0f;

    // Add up to 5 random players. (最多添加 5 名随机玩家。)
    for (uint32 i = 0; i < 5 && possiblePlayers.size(); i++)
    {
        auto p = possiblePlayers.begin();
        std::advance(p, urand(0, possiblePlayers.size() - 1));
        if (ignoreList.find(*p) != ignoreList.end())
            continue;

        targets[*p] = -1.0f;
        possiblePlayers.erase(p);
    }

    if (targets.empty())
        return targets;

    uint32 ignored = 0;

    // 1 in 10 chance to skip the ignore list. Otherwise remove targets that should be ignored. (有 1/10 概率跳过忽略列表；否则移除应被忽略的目标。)
    if (urand(0, 9))
    {
        for (auto target : ignoreList)
        {
            targets.erase(target);
            ignored++;
        }
    }

    if (debug || ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
    {
        std::ostringstream out;
        out << "Rpg: found ";
        out << std::to_string(possibleTargets.size()) + " targets,";
        out << std::to_string(possibleObjects.size()) + " objects,";
        out << std::to_string(possiblePlayers.size()) + " players.";
        out << " Of which " + std::to_string(ignored) + " are ignored.";
        ai->TellPlayerNoFacing(requester, out);
    }

    // Force RpgTrigger to be active even if we aren't currently close to the rpg target. (即使当前未靠近 RPG 目标也强制激活 RPG 触发器。)
    SET_AI_VALUE(std::string, "next rpg action", this->getName());

    bool hasGoodRelevance = false;
    rgpActionReason.clear();

    // Shuffle the target list to randomly process it each time. (打乱目标列表顺序以实现每次随机处理。)
    for (auto& target : targets)
        targetList.push_back(target.first);

    std::shuffle(targetList.begin(), targetList.end(), *GetRandomGenerator());

    // Only check up to 50 targets. Selfbots and bots with a real master can check more. (最多检查 50 个目标；带真实玩家的机器人可检查更多。)
    uint16 checked = 0, sametarget = 0, maxCheck = 50;
    if (ai->HasRealPlayerMaster())
        maxCheck = 500;

    std::unordered_map<ObjectGuid, std::string> debugTargets;

    for (auto& guid : targetList)
    {
        GuidPosition guidP(guid, bot->GetMapId(), bot->GetInstanceId());        

        if (!guidP)
            SkipRpgTarget("not found on map/instance.");       

        int32 travelEntry = guidP.IsGameObject() ? -(int32)guidP.GetEntry() : (int32)guidP.GetEntry();
        bool isTravelTarget = (travelEntry == travelTarget->GetEntry());

        // Stop to save peformance. (提前终止以节省性能开销。)
        if (checked >= maxCheck && !isTravelTarget)
            continue;

        // Check if we are allowed to move to this position. This is based on movement strategies follow, free, guard, stay. Bots are limited to finding targets near the center of those movement strategies. (检查当前移动策略（跟随/自由/警戒/原地）是否允许移动到该位置，机器人寻敌范围受策略中心点限制。)
        // For bots with real players they are also slightly limited in range unless the player stands still for a while. See free move values. (带真实玩家的机器人受限在较小自由移动半径内，除非玩家长时间站立不动（见自由移动范围值）。)
        if (guidP.GetWorldObject(bot->GetInstanceId()) && !CanFreeMoveValue::CanFreeMoveTo(ai, guidP))
            SkipRpgTarget("Can not free move to.");

        if (guidP.IsGameObject())
        {
            // Ignore game objects that are not spawned or being used by others. (忽略尚未刷新或正被他人使用的游戏对象。)
            GameObject* go = guidP.GetGameObject(bot->GetInstanceId());
            if (!go || !sServerFacade.isSpawned(go)
                || go->IsInUse()
                || go->GetGoState() != GO_STATE_READY)
                SkipRpgTarget("Go is not spawned, ready or is in use.");

            // Ignore objects that are too high or low compared to the bot. (忽略与机器人高度差过大的对象。)
            if (fabs(go->GetPositionZ() - bot->GetPositionZ()) > 20.f)
                SkipRpgTarget("Go is too high/low compared to bot.");
        }
        else if (guidP.IsPlayer())
        {
            Player* player = guidP.GetPlayer();

            // Ignore players that can not be found. (忽略无法查找到的玩家。)
            if (!player)
                SkipRpgTarget("Can not find player.");

            // Ignore yourself. (忽略机器人自身。)
            if (player == bot)
                SkipRpgTarget("Player is bot.");

            if (!ai->IsSafe(player))
                SkipRpgTarget("Player is not safe.");

            if (player->GetPlayerbotAI())
            {
                GuidPosition guidPP = PAI_VALUE(GuidPosition, "rpg target");

                // Ignore bots that are rpg'ing with another player. This is to prevent two bots rpg-ing with eachother. (忽略正在与其他玩家进行 RPG 交互的机器人，避免两个机器人相互卡在对话中。)
                if (guidPP.IsPlayer())
                    SkipRpgTarget("Player has bot as rpg target.");

                // Leaders are not allowed to rpg with groupmembers to prevent follow from making members run away. (禁止队长与队友进行 RPG 交互，防止触发跟随导致队伍成员乱跑。)
                if (bot->GetGroup() && player->GetGroup() == bot->GetGroup() && bot->GetGroup()->IsLeader(bot->GetObjectGuid()))
                    SkipRpgTarget("Player is group member and I am leader of same group.");
            }
        }

        // Limit the amount of bots that can rpg with 1 target. Only if the calculation doesn't involve checking 200+ players. (限制同时与同一目标进行 RPG 交互的机器人数量（仅在周围玩家少于 200 人时启用检查）。)
        if (possiblePlayers.size() < 200 && HasSameTarget(guidP, urand(5, 15), possiblePlayers))
        {
            sametarget++;
            SkipRpgTarget("Too many bots are rpging with this npc.");
        }

        // For all rpg actions that are triggered/possible for this target get the highest relevance. (获取该目标所有可触发的 RPG 动作中的最高相关性评分。)
        float relevance = getMaxRelevance(guidP);

        bool travelHasQuest = false;
        if (isTravelTarget && guidP.GetEntry())
        {
            int32 qEntry = guidP.IsGameObject() ? -(int32)guidP.GetEntry() : (int32)guidP.GetEntry();
            travelHasQuest = AI_VALUE2(bool, "can accept quest npc", qEntry)
                || AI_VALUE2(bool, "can accept quest low level npc", qEntry)
                || AI_VALUE2(bool, "can turn in quest npc", qEntry);
        }

        // If this rpg target is our travel target increase the relevance by 50% to make it more likely to be picked. (若该 RPG 目标恰好是当前旅行目标，则将其相关性提高 50% 以优先选中。)
        if (isTravelTarget)
        {
            if (focusList.empty() && !travelHasQuest)
                relevance *= 1.5f;
            else
                relevance *= 10.0f;
        }

        // If we already had a different target with a relevance above 1 and this only has 1 (trivial) skip this target. (若已找到相关性大于 1 的目标而当前目标仅为 1（低优先级），则跳过。)
        if (!hasGoodRelevance || relevance > 1.0f)
        {
            float newRelevance = relevance;

            // Scale relevance based on distance (根据距离对相关性评分进行衰减缩放)
            hasGoodRelevance = true;

            bool skipDistanceScaling = isTravelTarget && (!focusList.empty() || travelHasQuest);
            if (!skipDistanceScaling)
            {
                newRelevance = newRelevance / (1 + sqrt(guidP.sqDistance(bot)) / 30);

                if (relevance > 1.0f && newRelevance <= 1.0f)
                    newRelevance = 1.01f;
            }

            targets[guidP] = newRelevance;
        }

        checked++;
    }

    if (debug)
    {
        std::sort(targetList.begin(), targetList.end(), [targets](ObjectGuid i, ObjectGuid j) {return targets.at(i) < targets.at(j); });

        for (auto& target : targetList)
        {
            GuidPosition guidP(target, bot->GetMapId(), bot->GetInstanceId());
            std::ostringstream out;
            out << chat->formatGuidPosition(guidP, bot) << " " << targets.at(target) << " ";

            if (debugTargets[target].empty())
                out << rgpActionReason[target];
            else
                out << debugTargets[target];

            ai->TellPlayerNoFacing(requester, out);
        }
    }

    return targets;
}

// This method will temporary set the rpg target and finds the highest rpg action relevance that 'could' be triggered when near the target. (该方法临时设定 RPG 目标并计算靠近该目标时可触发的最高动作相关性。)
float ChooseRpgTargetAction::getMaxRelevance(GuidPosition guidP)
{
    GuidPosition currentRpgTarget = AI_VALUE(GuidPosition, "rpg target");
    SET_AI_VALUE(GuidPosition, "rpg target", guidP);

    Strategy* rpgStrategy;

    std::list<TriggerNode*> triggerNodes;

    float maxRelevance = 0.0f;

    // Loop over all strategies containing rpg that are enabled. (遍历所有已启用的包含 rpg 的策略。)
    std::set<std::string> strategies;
    ai->GetAiObjectContext()->GetSupportedStrategies(strategies);
    for (auto& strategy : strategies)
    {
        if (strategy.find("rpg") == std::string::npos)
            continue;

        if (!ai->HasStrategy(strategy, BotState::BOT_STATE_NON_COMBAT))
            continue;

        rpgStrategy = ai->GetAiObjectContext()->GetStrategy(strategy);

        rpgStrategy->InitTriggers(triggerNodes, BotState::BOT_STATE_NON_COMBAT);

        // Loop over all triggers of this strategy. (遍历该策略下的所有触发器。)
        for (auto& triggerNode : triggerNodes)
        {
            Trigger* trigger = context->GetTrigger(triggerNode->getName());

            if (trigger)
            {
                triggerNode->setTrigger(trigger);

                if (triggerNode->getFirstRelevance() < maxRelevance || triggerNode->getFirstRelevance() > 2.0f)
                    continue;

                Trigger* trigger = triggerNode->getTrigger();

                if (!trigger->IsActive())
                    continue;

                NextAction** nextActions = triggerNode->getHandlers();

                bool isRpg = false;

                // Loop over all actions triggered by this trigger and check if any is an 'rpg action'. (遍历该触发器触发的所有动作，检查其中是否包含 RPG 动作。)
                for (int32 i = 0; i < NextAction::size(nextActions); i++)
                {
                    NextAction* nextAction = nextActions[i];

                    Action* action = ai->GetAiObjectContext()->GetAction(nextAction->getName());

                    if (dynamic_cast<RpgEnabled*>(action))
                        isRpg = true;

                    RpgSubAction* subAction = dynamic_cast<RpgSubAction*>(action);

                    if (subAction)
                        rgpActionReason[guidP] = subAction->GetRpgActionName();
                }
                NextAction::destroy(nextActions);

                // Note the highest relevance of this node and the reason it triggers. (记录该节点的最高相关性评分及触发原因。)
                if (isRpg)
                {
                    maxRelevance = triggerNode->getFirstRelevance();
                    if (rgpActionReason[guidP].empty())
                        rgpActionReason[guidP] = triggerNode->getName();
                }
            }
        }

        for (std::list<TriggerNode*>::iterator i = triggerNodes.begin(); i != triggerNodes.end(); i++)
        {
            TriggerNode* trigger = *i;
            delete trigger;
        }

        triggerNodes.clear();
    }

    SET_AI_VALUE(GuidPosition,"rpg target", currentRpgTarget);

    if (!maxRelevance)
        return 0.0;

    // Normalize the relevances from normal engine level to rpg level for better comparison with distance. (将常规引擎动作的相关性权重归一化到 RPG 层级，以便与距离进行综合比较。)
    // Ie. trivial actions have 1.001f => 1, normal actions have 1.050f => 50. (即低优先级动作 1.001f 映射为 1，常规动作 1.050f 映射为 50。)
    return floor((maxRelevance - 1.0) * 1000.0f);
}

/// 执行动作主逻辑（选择 RPG 目标动作）
bool ChooseRpgTargetAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    std::unordered_map<ObjectGuid, float> targets = GetTargets(requester);

    if (targets.empty())
        return false;

    GuidPosition masterRpgTarget;
    if (requester && ai->IsSafe(requester) && requester->GetPlayerbotAI())
    {
        Player* player = requester;
        masterRpgTarget = PAI_VALUE(GuidPosition, "rpg target");
    }

    // Enable range check for rpg triggers. (为 RPG 触发器启用距离检查。)
    SET_AI_VALUE(std::string, "next rpg action", "");

    bool hasGoodRelevance = false;
    for (auto& [target, relevance] : targets)
    {
        if (relevance > 1.0f)
        {
            hasGoodRelevance = true;
            break;
        }
    }

    uint32 checked = 0;
    for (auto it = begin(targets); it != end(targets);)
    {        
        if (it->second >= 0)
            checked++;

        bool shouldErase = false;
        if (it->second <= 0) // Remove empty targets. (清理空目标。)
            shouldErase = true;
        else if (hasGoodRelevance && it->second <= 1.0)  // Remove useless targets if there's any good ones. (若存在高价值目标则剔除无关的低优先级目标。)
            shouldErase = true;
        else if (!hasGoodRelevance && requester && requester != bot && (!masterRpgTarget || it->first != masterRpgTarget)) // Remove useless targets if it's not masters target. This prevents group members running all over the place to emote with random npc's which aren't near the master. (若非主人当前目标则移除无关目标，防止队友满场乱跑去与远处 NPC 互动。)
            shouldErase = true;

        if (shouldErase)
            it = targets.erase(it);
        else
            ++it;
    }

    // We have no targets. Quit. (当前没有可用目标，退出处理。)
    if (targets.empty())
    {
        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            std::ostringstream out;
            out << "found: no targets, " << checked << " checked.";
            ai->TellPlayerNoFacing(requester, out);
        }
        RESET_AI_VALUE(std::set<ObjectGuid>&,"ignore rpg target");
        RESET_AI_VALUE(GuidPosition, "rpg target");
        return false;
    }

    // Report the list of potential targets and their relevance and reason for interaction. (汇报潜在交互目标列表及其相关性评分与触发原因。)
    if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
    {
        std::vector<std::pair<ObjectGuid, float>> sortedTargets(targets.begin(), targets.end());

        std::sort(sortedTargets.begin(), sortedTargets.end(), [](std::pair<ObjectGuid, float>i, std::pair<ObjectGuid, float> j) {return i.second > j.second; });

        ai->TellPlayerNoFacing(requester, "------" + std::to_string(targets.size()) + "------");

        uint32 checked = 0;

        for (auto target : sortedTargets)
        {
            GuidPosition guidP(target.first, bot->GetMapId(), bot->GetInstanceId());

            if (!guidP.GetWorldObject(bot->GetInstanceId()))
                continue;

            std::ostringstream out;
            out << chat->formatWorldobject(guidP.GetWorldObject(bot->GetInstanceId()));

            out << std::fixed << std::setprecision(2);
            out << " " << rgpActionReason[guidP] << " " << target.second;

            ai->TellPlayerNoFacing(requester, out);

            checked++;

            if (checked >= 10)
            {
                std::ostringstream out;
                out << "and " << (sortedTargets.size()-checked) << " more...";
                ai->TellPlayerNoFacing(requester, out);
                break;
            }
        }
    }

    std::set<ObjectGuid>& ignoreList = AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target");

    std::vector<ObjectGuid> guidps;
    std::vector<float> relevances;

    // If we have only trivial targets ignore them all the next time we look for a new target. (若仅剩低优先级目标，将它们加入忽略以便下次寻找新目标。)
    for (auto& target : targets)
    {
        if (!target.second || target.second < 0)
            continue;

        guidps.push_back(target.first);
        relevances.push_back(target.second);

        if (target.second == 1)
            ignoreList.insert(target.first);
    }

    // If we can't find a target clear ignore list and try again later. (若找不到任何有效目标，则清空忽略列表以便稍后重试。)
    if (guidps.empty())
    {
        RESET_AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target");
        RESET_AI_VALUE(GuidPosition, "rpg target");
        return false;
    }

    // We pick a random target from the list with targets having a higher relevance of being picked. (从候选列表中按相关性权重随机抽取一个交互目标。)
    std::mt19937 gen(time(0));
    WeightedShuffle(guidps.begin(), guidps.end(), relevances.begin(), relevances.end(), gen);
    GuidPosition guidP(guidps.front(),bot->GetMapId(), bot->GetInstanceId());

    // If we can't find a target clear ignore list and try again later. (若找不到任何有效目标，则清空忽略列表以便稍后重试。)
    if (!guidP)
    {
        RESET_AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target");
        RESET_AI_VALUE(GuidPosition, "rpg target");
        return false;
    }

    // Report the target that was found. (汇报查找到的目标。)
    if ((ai->HasStrategy("debug", BotState::BOT_STATE_NON_COMBAT) || ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT)) && guidP.GetWorldObject(bot->GetInstanceId()))
    {
        std::ostringstream out;
        out << "found: ";
        out << chat->formatWorldobject(guidP.GetWorldObject(bot->GetInstanceId()));

        out << std::fixed << std::setprecision(2);
        out << " " << rgpActionReason[guidP] << " " << targets[guidP];

        ai->TellPlayerNoFacing(requester, out);
    }

    // Save the current rpg target and the ignorelist. (保存当前 RPG 目标与忽略列表。)
    SET_AI_VALUE(GuidPosition, "rpg target", guidP);
    ignoreList.clear();

    return true;
}

/// 判断当前状态下该动作是否可用/有效（选择 RPG 目标动作）
bool ChooseRpgTargetAction::isUseful()
{
    if (!ai->AllowActivity(RPG_ACTIVITY))
        return false;

    GuidPosition guidP = AI_VALUE(GuidPosition, "rpg target");

    if (guidP && guidP.distance(bot) < sPlayerbotAIConfig.reactDistance * 2)
        return false;

    if (AI_VALUE(bool, "travel target traveling"))
        return false;

    if (AI_VALUE(std::list<ObjectGuid>, "possible rpg targets").empty())
        return false;

    // Not stay, not guard, not combat, not trading and group ready. (非停留、非警戒、非战斗、非交易且队伍已就绪。)
    if (!AI_VALUE(bool, "can move around"))
        return false;

    // Check if nearby rpg targets (max rpg distance) can be inside the free move range at al. (检查最大 RPG 距离内的交互目标是否处于自由移动允许范围内。)
    float range = AI_VALUE(float, "free move range");
    if(range)
    {
        GuidPosition center(AI_VALUE(GuidPosition, "free move center"));

        if (center.getMapId() != bot->GetMapId())
            return false;

        if (center.sqDistance2d(bot) > range * range + sPlayerbotAIConfig.rpgDistance * sPlayerbotAIConfig.rpgDistance)
            return false;
    }

    return true;
}
