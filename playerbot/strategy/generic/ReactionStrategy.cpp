/// 机器人状态反应（Reaction）核心切换策略实现

#include "playerbot/playerbot.h"
#include "playerbot/ServerFacade.h"
#include "ReactionStrategy.h"

using namespace ai;

/// 初始化反应触发器：在进战、脱战、死亡和复活时立即切换 BotState 状态
void ReactionStrategy::InitReactionTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "combat start",
        NextAction::array(0, new NextAction("set combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "combat end",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "death",
        NextAction::array(0, new NextAction("set dead state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "resurrect",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));
}