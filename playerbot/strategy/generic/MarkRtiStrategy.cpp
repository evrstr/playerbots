/// 自动团队目标标记（Mark RTI）策略实现

#include "playerbot/playerbot.h"
#include "MarkRtiStrategy.h"

using namespace ai;

/// 初始化战斗触发器：场上缺少团队标记目标时自动打上标记
void MarkRtiStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no rti target",
        NextAction::array(0, new NextAction("mark rti", ACTION_EMERGENCY), NULL)));
}