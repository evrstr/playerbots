// 猎人 - 野兽控制猎人策略实现文件 (BeastMasteryHunterStrategy.cpp)

#include "playerbot/playerbot.h"
#include "HunterMultipliers.h"
#include "BeastMasteryHunterStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体策略)
void BeastMasteryHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体策略)
void BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体PVE策略)
void BeastMasteryHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体PVE策略)
void BeastMasteryHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体PVP策略)
void BeastMasteryHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体PVP策略)
void BeastMasteryHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体团队副本策略)
void BeastMasteryHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体团队副本策略)
void BeastMasteryHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益Buff策略)
void BeastMasteryHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益Buff策略)
void BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益BuffPVE策略)
void BeastMasteryHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益BuffPVE策略)
void BeastMasteryHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益BuffPVP策略)
void BeastMasteryHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益BuffPVP策略)
void BeastMasteryHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益Buff团队副本策略)
void BeastMasteryHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益Buff团队副本策略)
void BeastMasteryHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益策略)
void BeastMasteryHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bestial wrath",
        NextAction::array(0, new NextAction("bestial wrath", ACTION_HIGH + 6), NULL)));
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益策略)
void BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益PVE策略)
void BeastMasteryHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益PVE策略)
void BeastMasteryHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益PVP策略)
void BeastMasteryHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益PVP策略)
void BeastMasteryHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益团队副本策略)
void BeastMasteryHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益团队副本策略)
void BeastMasteryHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)策略)
void BeastMasteryHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)策略)
void BeastMasteryHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)PVE策略)
void BeastMasteryHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)PVE策略)
void BeastMasteryHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)PVP策略)
void BeastMasteryHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)PVP策略)
void BeastMasteryHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)团队副本策略)
void BeastMasteryHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)团队副本策略)
void BeastMasteryHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺策略)
void BeastMasteryHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺PVE策略)
void BeastMasteryHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺PVP策略)
void BeastMasteryHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺团队副本策略)
void BeastMasteryHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护策略)
void BeastMasteryHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护策略)
void BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护PVE策略)
void BeastMasteryHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护PVE策略)
void BeastMasteryHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护PVP策略)
void BeastMasteryHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护PVP策略)
void BeastMasteryHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护团队副本策略)
void BeastMasteryHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护团队副本策略)
void BeastMasteryHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体策略)
void BeastMasteryHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体策略)
void BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体PVE策略)
void BeastMasteryHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体PVE策略)
void BeastMasteryHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体PVP策略)
void BeastMasteryHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体PVP策略)
void BeastMasteryHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体团队副本策略)
void BeastMasteryHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体团队副本策略)
void BeastMasteryHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益Buff策略)
void BeastMasteryHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益Buff策略)
void BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益BuffPVE策略)
void BeastMasteryHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益BuffPVE策略)
void BeastMasteryHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益BuffPVP策略)
void BeastMasteryHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益BuffPVP策略)
void BeastMasteryHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益Buff团队副本策略)
void BeastMasteryHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益Buff团队副本策略)
void BeastMasteryHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益策略)
void BeastMasteryHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bestial wrath",
        NextAction::array(0, new NextAction("bestial wrath", ACTION_HIGH + 6), NULL)));
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益策略)
void BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益PVE策略)
void BeastMasteryHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益PVE策略)
void BeastMasteryHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益PVP策略)
void BeastMasteryHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益PVP策略)
void BeastMasteryHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益团队副本策略)
void BeastMasteryHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益团队副本策略)
void BeastMasteryHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)策略)
void BeastMasteryHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)策略)
void BeastMasteryHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)PVE策略)
void BeastMasteryHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)PVE策略)
void BeastMasteryHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)PVP策略)
void BeastMasteryHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)PVP策略)
void BeastMasteryHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)团队副本策略)
void BeastMasteryHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)团队副本策略)
void BeastMasteryHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺策略)
void BeastMasteryHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺PVE策略)
void BeastMasteryHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺PVP策略)
void BeastMasteryHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺团队副本策略)
void BeastMasteryHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护策略)
void BeastMasteryHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护策略)
void BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护PVE策略)
void BeastMasteryHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护PVE策略)
void BeastMasteryHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护PVP策略)
void BeastMasteryHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护PVP策略)
void BeastMasteryHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护团队副本策略)
void BeastMasteryHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护团队副本策略)
void BeastMasteryHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人策略)
void BeastMasteryHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人PVE策略)
void BeastMasteryHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人PVP策略)
void BeastMasteryHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (野兽控制猎人团队副本策略)
void BeastMasteryHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体策略)
void BeastMasteryHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体策略)
void BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体PVE策略)
void BeastMasteryHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体PVE策略)
void BeastMasteryHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体PVP策略)
void BeastMasteryHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体PVP策略)
void BeastMasteryHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人AOE群体团队副本策略)
void BeastMasteryHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人AOE群体团队副本策略)
void BeastMasteryHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益Buff策略)
void BeastMasteryHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益Buff策略)
void BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益BuffPVE策略)
void BeastMasteryHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益BuffPVE策略)
void BeastMasteryHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益BuffPVP策略)
void BeastMasteryHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益BuffPVP策略)
void BeastMasteryHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人增益Buff团队副本策略)
void BeastMasteryHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人增益Buff团队副本策略)
void BeastMasteryHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益策略)
void BeastMasteryHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bestial wrath",
        NextAction::array(0, new NextAction("bestial wrath", ACTION_HIGH + 6), NULL)));
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益策略)
void BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益PVE策略)
void BeastMasteryHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益PVE策略)
void BeastMasteryHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益PVP策略)
void BeastMasteryHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益PVP策略)
void BeastMasteryHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人爆发增益团队副本策略)
void BeastMasteryHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人爆发增益团队副本策略)
void BeastMasteryHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)策略)
void BeastMasteryHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)策略)
void BeastMasteryHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)PVE策略)
void BeastMasteryHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)PVE策略)
void BeastMasteryHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)PVP策略)
void BeastMasteryHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)PVP策略)
void BeastMasteryHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人控制(CC)团队副本策略)
void BeastMasteryHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人控制(CC)团队副本策略)
void BeastMasteryHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺策略)
void BeastMasteryHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺PVE策略)
void BeastMasteryHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺PVP策略)
void BeastMasteryHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人钉刺团队副本策略)
void BeastMasteryHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护策略)
void BeastMasteryHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护策略)
void BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护PVE策略)
void BeastMasteryHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护PVE策略)
void BeastMasteryHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护PVP策略)
void BeastMasteryHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护PVP策略)
void BeastMasteryHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (野兽控制猎人守护团队副本策略)
void BeastMasteryHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (野兽控制猎人守护团队副本策略)
void BeastMasteryHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BeastMasteryHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
