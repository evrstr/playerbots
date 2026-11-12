/// 逃跑与躲避 Add 策略实现

#include "playerbot/playerbot.h"
#include "FleeStrategy.h"

using namespace ai;

/// 初始化逃跑战斗触发器：处于濒危恐慌或以寡敌众时触发紧急逃离
void FleeStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "panic",
        NextAction::array(0, new NextAction("flee", ACTION_EMERGENCY + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "outnumbered",
        NextAction::array(0, new NextAction("flee", ACTION_EMERGENCY + 9), NULL)));
}

/// 初始化远离 Add 战斗触发器：附近有未进战额外怪物时主动拉开距离
void FleeFromAddsStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "has nearest adds",
        NextAction::array(0, new NextAction("runaway", 50.0f), NULL)));
}
