/// 脱战吃喝回复（Food & Drink）策略实现

#include "playerbot/playerbot.h"
#include "UseFoodStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：血量或法力偏低时自动吃食物或喝水
void UseFoodStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("food", 3.0f), NULL)));
        
    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("food", 3.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "high mana",
        NextAction::array(0, new NextAction("drink", 3.0f), NULL)));
}
