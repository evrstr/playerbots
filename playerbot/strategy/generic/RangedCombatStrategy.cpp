/// 远程战斗（Ranged Combat）策略实现

#include "playerbot/playerbot.h"
#include "RangedCombatStrategy.h"

using namespace ai;

/// 初始化战斗触发器：敌人贴脸影响施法时触发后撤拉开距离
void RangedCombatStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("flee", ACTION_MOVE), NULL)));
}
