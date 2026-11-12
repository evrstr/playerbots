/// 风筝（Kite）策略实现

#include "playerbot/playerbot.h"
#include "KiteStrategy.h"

using namespace ai;

/// 初始化战斗触发器：获得仇恨时触发奔跑风筝动作
void KiteStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("runaway", 51.0f), NULL)));
}
