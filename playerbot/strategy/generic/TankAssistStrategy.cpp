/// 坦克辅助（Tank Assist）策略实现

#include "playerbot/playerbot.h"
#include "TankAssistStrategy.h"

using namespace ai;

/// 初始化战斗触发器：响应 tank assist 触发器协助坦克拉怪或集火
void TankAssistStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "tank assist",
        NextAction::array(0, new NextAction("tank assist", 60.0f), NULL)));
}
