/// 能源舰（The Mechanar）副本及首领策略实现

#include "playerbot/playerbot.h"
#include "MechanarDungeonStrategies.h"
#include "DungeonMultipliers.h"

using namespace ai;

/// 初始化能源舰战斗触发器：探测灵术师塞佩丝蕾进入战斗时开启对应 Boss 策略
void MechanarDungeonStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "start nethermancer sepethrea fight",
        NextAction::array(0, new NextAction("enable nethermancer sepethrea fight strategy", 100.0f), NULL)));
}

/// 初始化灵术师塞佩丝蕾战斗触发器：远离狂怒烈焰（火元素）危险范围
void NethermancerSepethreaFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "raging flames too close",
        NextAction::array(0, new NextAction("move away from raging flames", 100.0f), NULL)));
}

/// 初始化灵术师塞佩丝蕾非战斗触发器：脱战后卸载策略
void NethermancerSepethreaFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end nethermancer sepethrea fight",
        NextAction::array(0, new NextAction("disable nethermancer sepethrea fight strategy", 100.0f), NULL)));
}

/// 初始化灵术师塞佩丝蕾死亡触发器
void NethermancerSepethreaFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end nethermancer sepethrea fight",
        NextAction::array(0, new NextAction("disable nethermancer sepethrea fight strategy", 100.0f), NULL)));
}
