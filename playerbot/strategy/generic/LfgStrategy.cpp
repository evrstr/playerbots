/// 地下城查找器（LFG）策略实现

#include "playerbot/playerbot.h"
#include "LfgStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：自动排队/离开 LFG 队列并在未知副本交出队长
void LfgStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("lfg join", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "seldom",
        NextAction::array(0, new NextAction("lfg leave", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "unknown dungeon",
        NextAction::array(0, new NextAction("give leader in dungeon", relevance), NULL)));
}