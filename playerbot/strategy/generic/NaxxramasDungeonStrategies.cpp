/// 纳克萨玛斯（Naxxramas）团队副本及首领策略实现

#include "playerbot/playerbot.h"
#include "NaxxramasDungeonStrategies.h"
#include "DungeonMultipliers.h"

using namespace ai;

/// 初始化纳克萨玛斯战斗触发器：激活天启四骑士战斗策略
void NaxxramasDungeonStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "start four horseman fight",
        NextAction::array(0, new NextAction("enable four horseman fight strategy", 100.0f), NULL)));
}

/// 初始化天启四骑士战斗触发器：躲避地面虚空地带
void FourHorsemanFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "void zone too close",
        NextAction::array(0, new NextAction("move away from void zone", 100.0f), NULL)));
}

/// 初始化天启四骑士非战斗触发器：脱战后卸载策略
void FourHorsemanFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end horseman fight",
        NextAction::array(0, new NextAction("disable four horseman fight strategy", 100.0f), NULL)));
}

/// 初始化天启四骑士死亡触发器
void FourHorsemanFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end horseman fight",
        NextAction::array(0, new NextAction("disable four horseman fight strategy", 100.0f), NULL)));
}
