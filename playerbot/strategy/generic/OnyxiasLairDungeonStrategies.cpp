/// 奥妮克希亚的巢穴副本及首领策略实现

#include "playerbot/playerbot.h"
#include "OnyxiasLairDungeonStrategies.h"

using namespace ai;

/// 初始化奥妮克希亚巢穴战斗触发器：开战后启用奥妮克希亚专项战斗策略
void OnyxiasLairDungeonStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "start onyxia fight",
        NextAction::array(0, new NextAction("enable onyxia fight strategy", 100.0f), NULL)));
}

/// 初始化奥妮克希亚战斗触发器
void OnyxiaFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    // ...
}

/// 初始化奥妮克希亚非战斗触发器：脱战后卸载策略
void OnyxiaFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end onyxia fight",
        NextAction::array(0, new NextAction("disable onyxia fight strategy", 100.0f), NULL)));
}

/// 初始化奥妮克希亚死亡触发器
void OnyxiaFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end onyxia fight",
        NextAction::array(0, new NextAction("disable onyxia fight strategy", 100.0f), NULL)));
}

/// 初始化奥妮克希亚反应触发器
void OnyxiaFightStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    // ...
}
