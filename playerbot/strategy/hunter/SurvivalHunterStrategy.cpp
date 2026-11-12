// 猎人 - 生存猎人策略实现文件 (SurvivalHunterStrategy.cpp)

#include "playerbot/playerbot.h"
#include "HunterMultipliers.h"
#include "SurvivalHunterStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体策略)
void SurvivalHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体策略)
void SurvivalHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体PVE策略)
void SurvivalHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体PVE策略)
void SurvivalHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体PVP策略)
void SurvivalHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体PVP策略)
void SurvivalHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体团队副本策略)
void SurvivalHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体团队副本策略)
void SurvivalHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益Buff策略)
void SurvivalHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益Buff策略)
void SurvivalHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益BuffPVE策略)
void SurvivalHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益BuffPVE策略)
void SurvivalHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益BuffPVP策略)
void SurvivalHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益BuffPVP策略)
void SurvivalHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益Buff团队副本策略)
void SurvivalHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益Buff团队副本策略)
void SurvivalHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益策略)
void SurvivalHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益策略)
void SurvivalHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益PVE策略)
void SurvivalHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益PVE策略)
void SurvivalHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益PVP策略)
void SurvivalHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益PVP策略)
void SurvivalHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益团队副本策略)
void SurvivalHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益团队副本策略)
void SurvivalHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)策略)
void SurvivalHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)策略)
void SurvivalHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)PVE策略)
void SurvivalHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)PVE策略)
void SurvivalHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)PVP策略)
void SurvivalHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)PVP策略)
void SurvivalHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)团队副本策略)
void SurvivalHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)团队副本策略)
void SurvivalHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺策略)
void SurvivalHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺PVE策略)
void SurvivalHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺PVP策略)
void SurvivalHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺团队副本策略)
void SurvivalHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护策略)
void SurvivalHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护策略)
void SurvivalHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护PVE策略)
void SurvivalHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护PVE策略)
void SurvivalHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护PVP策略)
void SurvivalHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护PVP策略)
void SurvivalHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护团队副本策略)
void SurvivalHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护团队副本策略)
void SurvivalHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体策略)
void SurvivalHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体策略)
void SurvivalHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体PVE策略)
void SurvivalHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体PVE策略)
void SurvivalHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体PVP策略)
void SurvivalHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体PVP策略)
void SurvivalHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体团队副本策略)
void SurvivalHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体团队副本策略)
void SurvivalHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益Buff策略)
void SurvivalHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益Buff策略)
void SurvivalHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益BuffPVE策略)
void SurvivalHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益BuffPVE策略)
void SurvivalHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益BuffPVP策略)
void SurvivalHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益BuffPVP策略)
void SurvivalHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益Buff团队副本策略)
void SurvivalHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益Buff团队副本策略)
void SurvivalHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益策略)
void SurvivalHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益策略)
void SurvivalHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益PVE策略)
void SurvivalHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益PVE策略)
void SurvivalHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益PVP策略)
void SurvivalHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益PVP策略)
void SurvivalHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益团队副本策略)
void SurvivalHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益团队副本策略)
void SurvivalHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)策略)
void SurvivalHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)策略)
void SurvivalHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)PVE策略)
void SurvivalHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)PVE策略)
void SurvivalHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)PVP策略)
void SurvivalHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)PVP策略)
void SurvivalHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)团队副本策略)
void SurvivalHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)团队副本策略)
void SurvivalHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺策略)
void SurvivalHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺PVE策略)
void SurvivalHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺PVP策略)
void SurvivalHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺团队副本策略)
void SurvivalHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护策略)
void SurvivalHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护策略)
void SurvivalHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护PVE策略)
void SurvivalHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护PVE策略)
void SurvivalHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护PVP策略)
void SurvivalHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护PVP策略)
void SurvivalHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护团队副本策略)
void SurvivalHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护团队副本策略)
void SurvivalHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "black arrow",
        NextAction::array(0, new NextAction("black arrow", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "black arrow on snare target",
        NextAction::array(0, new NextAction("black arrow", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "explosive shot",
        NextAction::array(0, new NextAction("explosive shot", ACTION_NORMAL + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人策略)
void SurvivalHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人PVE策略)
void SurvivalHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人PVP策略)
void SurvivalHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (生存猎人团队副本策略)
void SurvivalHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体策略)
void SurvivalHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体策略)
void SurvivalHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体PVE策略)
void SurvivalHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体PVE策略)
void SurvivalHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体PVP策略)
void SurvivalHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体PVP策略)
void SurvivalHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人AOE群体团队副本策略)
void SurvivalHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人AOE群体团队副本策略)
void SurvivalHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益Buff策略)
void SurvivalHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益Buff策略)
void SurvivalHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益BuffPVE策略)
void SurvivalHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益BuffPVE策略)
void SurvivalHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益BuffPVP策略)
void SurvivalHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益BuffPVP策略)
void SurvivalHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人增益Buff团队副本策略)
void SurvivalHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人增益Buff团队副本策略)
void SurvivalHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益策略)
void SurvivalHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益策略)
void SurvivalHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益PVE策略)
void SurvivalHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益PVE策略)
void SurvivalHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益PVP策略)
void SurvivalHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益PVP策略)
void SurvivalHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人爆发增益团队副本策略)
void SurvivalHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人爆发增益团队副本策略)
void SurvivalHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)策略)
void SurvivalHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)策略)
void SurvivalHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)PVE策略)
void SurvivalHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)PVE策略)
void SurvivalHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)PVP策略)
void SurvivalHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)PVP策略)
void SurvivalHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人控制(CC)团队副本策略)
void SurvivalHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人控制(CC)团队副本策略)
void SurvivalHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺策略)
void SurvivalHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺PVE策略)
void SurvivalHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺PVP策略)
void SurvivalHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人钉刺团队副本策略)
void SurvivalHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护策略)
void SurvivalHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护策略)
void SurvivalHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护PVE策略)
void SurvivalHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护PVE策略)
void SurvivalHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护PVP策略)
void SurvivalHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护PVP策略)
void SurvivalHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (生存猎人守护团队副本策略)
void SurvivalHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (生存猎人守护团队副本策略)
void SurvivalHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SurvivalHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
