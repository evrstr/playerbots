/// 切换目标播报（Tell Target）策略实现

#include "playerbot/playerbot.h"
#include "TellTargetStrategy.h"

using namespace ai;

/// 初始化战斗触发器：攻击目标变更时在频道中播报新目标
void TellTargetStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "target changed",
        NextAction::array(0, new NextAction("tell target", 51.0f), NULL)));
}
