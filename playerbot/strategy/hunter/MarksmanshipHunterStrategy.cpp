// 猎人 - 射击猎人策略实现文件 (MarksmanshipHunterStrategy.cpp)

#include "playerbot/playerbot.h"
#include "HunterMultipliers.h"
#include "MarksmanshipHunterStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体策略)
void MarksmanshipHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体策略)
void MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体PVE策略)
void MarksmanshipHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体PVE策略)
void MarksmanshipHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体PVP策略)
void MarksmanshipHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体PVP策略)
void MarksmanshipHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体团队副本策略)
void MarksmanshipHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体团队副本策略)
void MarksmanshipHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益Buff策略)
void MarksmanshipHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益Buff策略)
void MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "trueshot aura",
        NextAction::array(0, new NextAction("trueshot aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (射击猎人增益BuffPVE策略)
void MarksmanshipHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益BuffPVE策略)
void MarksmanshipHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益BuffPVP策略)
void MarksmanshipHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益BuffPVP策略)
void MarksmanshipHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益Buff团队副本策略)
void MarksmanshipHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益Buff团队副本策略)
void MarksmanshipHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益策略)
void MarksmanshipHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益策略)
void MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益PVE策略)
void MarksmanshipHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益PVE策略)
void MarksmanshipHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益PVP策略)
void MarksmanshipHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益PVP策略)
void MarksmanshipHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益团队副本策略)
void MarksmanshipHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益团队副本策略)
void MarksmanshipHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)策略)
void MarksmanshipHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)策略)
void MarksmanshipHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)PVE策略)
void MarksmanshipHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)PVE策略)
void MarksmanshipHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)PVP策略)
void MarksmanshipHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)PVP策略)
void MarksmanshipHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)团队副本策略)
void MarksmanshipHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)团队副本策略)
void MarksmanshipHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺策略)
void MarksmanshipHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺PVE策略)
void MarksmanshipHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺PVP策略)
void MarksmanshipHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺团队副本策略)
void MarksmanshipHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护策略)
void MarksmanshipHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护策略)
void MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护PVE策略)
void MarksmanshipHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护PVE策略)
void MarksmanshipHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护PVP策略)
void MarksmanshipHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护PVP策略)
void MarksmanshipHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护团队副本策略)
void MarksmanshipHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护团队副本策略)
void MarksmanshipHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体策略)
void MarksmanshipHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体策略)
void MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体PVE策略)
void MarksmanshipHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体PVE策略)
void MarksmanshipHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体PVP策略)
void MarksmanshipHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体PVP策略)
void MarksmanshipHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体团队副本策略)
void MarksmanshipHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体团队副本策略)
void MarksmanshipHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益Buff策略)
void MarksmanshipHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益Buff策略)
void MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "trueshot aura",
        NextAction::array(0, new NextAction("trueshot aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (射击猎人增益BuffPVE策略)
void MarksmanshipHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益BuffPVE策略)
void MarksmanshipHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益BuffPVP策略)
void MarksmanshipHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益BuffPVP策略)
void MarksmanshipHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益Buff团队副本策略)
void MarksmanshipHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益Buff团队副本策略)
void MarksmanshipHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益策略)
void MarksmanshipHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益策略)
void MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益PVE策略)
void MarksmanshipHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益PVE策略)
void MarksmanshipHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益PVP策略)
void MarksmanshipHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益PVP策略)
void MarksmanshipHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益团队副本策略)
void MarksmanshipHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益团队副本策略)
void MarksmanshipHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)策略)
void MarksmanshipHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "silencing shot",
        NextAction::array(0, new NextAction("silencing shot", ACTION_INTERRUPT + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "silencing shot on enemy healer",
        NextAction::array(0, new NextAction("silencing shot on enemy healer", ACTION_INTERRUPT + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)策略)
void MarksmanshipHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)PVE策略)
void MarksmanshipHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)PVE策略)
void MarksmanshipHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)PVP策略)
void MarksmanshipHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)PVP策略)
void MarksmanshipHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)团队副本策略)
void MarksmanshipHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)团队副本策略)
void MarksmanshipHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺策略)
void MarksmanshipHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺PVE策略)
void MarksmanshipHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺PVP策略)
void MarksmanshipHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺团队副本策略)
void MarksmanshipHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护策略)
void MarksmanshipHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护策略)
void MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护PVE策略)
void MarksmanshipHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护PVE策略)
void MarksmanshipHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护PVP策略)
void MarksmanshipHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护PVP策略)
void MarksmanshipHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护团队副本策略)
void MarksmanshipHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护团队副本策略)
void MarksmanshipHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "chimera shot",
        NextAction::array(0, new NextAction("chimera shot", ACTION_NORMAL + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人策略)
void MarksmanshipHunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人PVE策略)
void MarksmanshipHunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人PVP策略)
void MarksmanshipHunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitCombatTriggers(triggers);
    HunterRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitNonCombatTriggers(triggers);
    HunterRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitReactionTriggers(triggers);
    HunterRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (射击猎人团队副本策略)
void MarksmanshipHunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStrategy::InitDeadTriggers(triggers);
    HunterRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体策略)
void MarksmanshipHunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体策略)
void MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体PVE策略)
void MarksmanshipHunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体PVE策略)
void MarksmanshipHunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体PVP策略)
void MarksmanshipHunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体PVP策略)
void MarksmanshipHunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人AOE群体团队副本策略)
void MarksmanshipHunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人AOE群体团队副本策略)
void MarksmanshipHunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAoeStrategy::InitNonCombatTriggers(triggers);
    HunterAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益Buff策略)
void MarksmanshipHunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益Buff策略)
void MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "trueshot aura",
        NextAction::array(0, new NextAction("trueshot aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (射击猎人增益BuffPVE策略)
void MarksmanshipHunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益BuffPVE策略)
void MarksmanshipHunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益BuffPVP策略)
void MarksmanshipHunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益BuffPVP策略)
void MarksmanshipHunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人增益Buff团队副本策略)
void MarksmanshipHunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人增益Buff团队副本策略)
void MarksmanshipHunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBuffStrategy::InitNonCombatTriggers(triggers);
    HunterBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益策略)
void MarksmanshipHunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益策略)
void MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益PVE策略)
void MarksmanshipHunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益PVE策略)
void MarksmanshipHunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益PVP策略)
void MarksmanshipHunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益PVP策略)
void MarksmanshipHunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人爆发增益团队副本策略)
void MarksmanshipHunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人爆发增益团队副本策略)
void MarksmanshipHunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterBoostStrategy::InitNonCombatTriggers(triggers);
    HunterBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)策略)
void MarksmanshipHunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "silencing shot",
        NextAction::array(0, new NextAction("silencing shot", ACTION_INTERRUPT + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "silencing shot on enemy healer",
        NextAction::array(0, new NextAction("silencing shot on enemy healer", ACTION_INTERRUPT + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)策略)
void MarksmanshipHunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)PVE策略)
void MarksmanshipHunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)PVE策略)
void MarksmanshipHunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)PVP策略)
void MarksmanshipHunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)PVP策略)
void MarksmanshipHunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人控制(CC)团队副本策略)
void MarksmanshipHunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitCombatTriggers(triggers);
    HunterCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人控制(CC)团队副本策略)
void MarksmanshipHunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterCcStrategy::InitNonCombatTriggers(triggers);
    HunterCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺策略)
void MarksmanshipHunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterStingStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺PVE策略)
void MarksmanshipHunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺PVP策略)
void MarksmanshipHunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人钉刺团队副本策略)
void MarksmanshipHunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterStingStrategy::InitCombatTriggers(triggers);
    HunterStingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护策略)
void MarksmanshipHunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护策略)
void MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HunterAspectStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护PVE策略)
void MarksmanshipHunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护PVE策略)
void MarksmanshipHunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护PVP策略)
void MarksmanshipHunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护PVP策略)
void MarksmanshipHunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (射击猎人守护团队副本策略)
void MarksmanshipHunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (射击猎人守护团队副本策略)
void MarksmanshipHunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MarksmanshipHunterAspectStrategy::InitNonCombatTriggers(triggers);
    HunterAspectRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
