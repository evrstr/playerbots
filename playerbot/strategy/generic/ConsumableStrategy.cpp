/// 消耗品（合剂/药水/卷轴等）使用策略实现
#include "playerbot/playerbot.h"
#include "ConsumableStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：定期检查并使用合适的常驻消耗品
void ConsumableStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use consumable", 2.0f), NULL)));
}

/// 初始化战斗触发器：战斗中定期检查并使用战斗消耗品
void ConsumableStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use consumable", 2.0f), NULL)));
}