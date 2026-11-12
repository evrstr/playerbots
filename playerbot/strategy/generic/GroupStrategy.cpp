/// 野生机器人自动组队与退队策略实现

#include "playerbot/playerbot.h"
#include "GroupStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：自动邀请附近/同公会玩家，并在距离过远或队长 AFK 时离队
void GroupStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("invite nearby", 4.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("invite guild", 4.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "seldom",
        NextAction::array(0, new NextAction("leave far away", 4.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leader is afk",
        NextAction::array(0, new NextAction("leave far away", 4.0f), NULL)));

    /*triggers.push_back(new TriggerNode(
        "seldom",
        NextAction::array(0, new NextAction("reset instances", 1.0f), NULL)));*/
}

/// 初始化死亡触发器：死亡状态下若距队伍过远或队长 AFK 则离队
void GroupStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "seldom",
        NextAction::array(0, new NextAction("leave far away", 4.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leader is afk",
        NextAction::array(0, new NextAction("leave far away", 4.0f), NULL)));
}