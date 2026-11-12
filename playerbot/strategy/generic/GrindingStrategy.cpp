/// 野外刷怪（Grinding）策略实现

#include "playerbot/playerbot.h"
#include "GrindingStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：当前无目标时自动搜寻并攻击周围合适怪物
void GrindingStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no target",
        NextAction::array(0,
        new NextAction("attack anything", 5.0f), NULL)));
}