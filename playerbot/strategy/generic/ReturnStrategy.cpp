/// 原地返回（Return）策略实现

#include "playerbot/playerbot.h"
#include "ReturnStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：闲置超时后记录或返回最初停驻位置
void ReturnStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "return",
        NextAction::array(0, 
            new NextAction("set return position", 1.5f),
            new NextAction("return", 1.0f), NULL)));
}