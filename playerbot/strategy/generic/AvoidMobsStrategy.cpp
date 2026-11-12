/// 规避怪物（Avoid Mobs）策略实现

#include "playerbot/playerbot.h"
#include "AvoidMobsStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：高频刷新并标记需要绕行的危险怪物区域
void AvoidMobsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("set avoid area", ACTION_NORMAL), NULL)));
}

/// 初始化战斗触发器：复用非战斗避怪区域更新逻辑
void AvoidMobsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AvoidMobsStrategy::InitNonCombatTriggers(triggers);
}
