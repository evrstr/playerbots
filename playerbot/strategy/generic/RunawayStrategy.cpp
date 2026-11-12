/// 远离逃跑（Runaway）策略实现

#include "playerbot/playerbot.h"
#include "RunawayStrategy.h"

using namespace ai;

/// 初始化战斗触发器：敌人过于贴近影响施法时向后退避
void RunawayStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("runaway", 50.0f), NULL)));
}
