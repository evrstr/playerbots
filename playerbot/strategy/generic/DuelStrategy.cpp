/// 决斗（Duel）策略实现

#include "playerbot/playerbot.h"
#include "DuelStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：接受决斗邀请并在无目标时主动攻击决斗对手
void DuelStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    PassTroughStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "duel requested",
        NextAction::array(0, new NextAction("accept duel", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "no attackers",
        NextAction::array(0, new NextAction("attack duel opponent", 70.0f), NULL)));
}

/// 初始化战斗触发器：复用非战斗决斗逻辑
void DuelStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    InitNonCombatTriggers(triggers);
}