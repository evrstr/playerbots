/// 非战斗拾取、采集与掷骰（Roll）策略实现

#include "playerbot/playerbot.h"
#include "LootNonCombatStrategy.h"

using namespace ai;

/// 初始化拾取触发器：扫描、接近、打开并拾取周围战利品
void LootNonCombatStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "loot available",
        NextAction::array(0, new NextAction("loot", 6.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "far from loot target",
        NextAction::array(0, new NextAction("move to loot", 7.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "can loot",
        NextAction::array(0, new NextAction("open loot", 8.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("add all loot", 1.0f), NULL)));
}

/// 初始化采集触发器：持续扫描并记录附近矿点/草药等采集目标
void GatherStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "timer",
        NextAction::array(0, new NextAction("add gathering loot", 2.0f), NULL)));
}

/// 初始化取物（Fetch）触发器：前往指定物体处交互采集
void FetchStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "timer",
        NextAction::array(0, new NextAction("fetch object", 7.5f), NULL)));
}

/// 初始化揭示（Reveal）触发器：提示或标记周围可采集物
void RevealStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("reveal gathering item", 50.0f), NULL)));
}

/// 初始化自动掷骰非战斗触发器
void RollStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("auto loot roll", 100.0f), NULL)));
}

/// 初始化自动掷骰战斗触发器
void RollStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RollStrategy::InitNonCombatTriggers(triggers);
}

/// 初始化延迟掷骰非战斗触发器：等待响应队长掷骰后再跟骰
void DelayedRollStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "loot roll",
        NextAction::array(0, new NextAction("loot roll", 100.0f), NULL)));
}

/// 初始化延迟掷骰战斗触发器
void DelayedRollStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DelayedRollStrategy::InitNonCombatTriggers(triggers);
}