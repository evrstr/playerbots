/// 战斗喊话提示（Say）策略实现

#include "playerbot/playerbot.h"
#include "SayStrategy.h"

using namespace ai;

/// 初始化战斗触发器：在危急血量、低血低蓝、群嘲或高密度 AoE 时发送战斗喊话
void SayStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("say::critical health", 99.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("say::low health", 99.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("say::low mana", 99.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "tank aoe",
        NextAction::array(0, new NextAction("say::taunt", 99.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("say::aoe", 99.0f), NULL)));
}
