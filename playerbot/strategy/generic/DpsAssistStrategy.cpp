/// DPS 集火协助与 AoE 目标切换策略实现

#include "playerbot/playerbot.h"
#include "DpsAssistStrategy.h"

using namespace ai;

/// 初始化单体 DPS 协助战斗触发器：目标偏离时切换至队伍最优单体目标
void DpsAssistStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "not dps target active",
        NextAction::array(0, new NextAction("dps assist", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "dps assist",
        NextAction::array(0, new NextAction("dps assist", 60.0f), NULL)));
}

/// 初始化 AoE DPS 战斗触发器：目标偏离时切换至最优群攻目标
void DpsAoeStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "not dps aoe target active",
        NextAction::array(0, new NextAction("dps aoe", 60.0f), NULL)));
}