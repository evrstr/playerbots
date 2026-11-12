// 圣骑士 - 神圣圣骑士策略实现文件 (HolyPaladinStrategy.cpp)

#include "playerbot/playerbot.h"
#include "PaladinMultipliers.h"
#include "HolyPaladinStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("lay on hands on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy shock on party", ACTION_MEDIUM_HEAL + 5), 
                             new NextAction("holy light on party", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy shock", ACTION_MEDIUM_HEAL + 2), 
                             new NextAction("holy light", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("divine shield", ACTION_EMERGENCY + 1),
                             new NextAction("holy light", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("flash of light", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of light", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("judgement", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("holy light", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("flash of light", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体策略)
void HolyPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体策略)
void HolyPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体PVE策略)
void HolyPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体PVE策略)
void HolyPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体PVP策略)
void HolyPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体PVP策略)
void HolyPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体团队副本策略)
void HolyPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体团队副本策略)
void HolyPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益Buff策略)
void HolyPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益Buff策略)
void HolyPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益BuffPVE策略)
void HolyPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益BuffPVE策略)
void HolyPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益BuffPVP策略)
void HolyPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益BuffPVP策略)
void HolyPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益Buff团队副本策略)
void HolyPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益Buff团队副本策略)
void HolyPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益策略)
void HolyPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "divine favor",
        NextAction::array(0, new NextAction("divine favor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益策略)
void HolyPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益PVE策略)
void HolyPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益PVE策略)
void HolyPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益PVP策略)
void HolyPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益PVP策略)
void HolyPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益团队副本策略)
void HolyPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益团队副本策略)
void HolyPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)策略)
void HolyPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)策略)
void HolyPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)PVE策略)
void HolyPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)PVE策略)
void HolyPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)PVP策略)
void HolyPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)PVP策略)
void HolyPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)团队副本策略)
void HolyPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)团队副本策略)
void HolyPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化策略)
void HolyPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化策略)
void HolyPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化PVE策略)
void HolyPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化PVE策略)
void HolyPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化PVP策略)
void HolyPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化PVP策略)
void HolyPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化团队副本策略)
void HolyPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化团队副本策略)
void HolyPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环策略)
void HolyPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环策略)
void HolyPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("concentration aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环PVE策略)
void HolyPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环PVE策略)
void HolyPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环PVP策略)
void HolyPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环PVP策略)
void HolyPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环团队副本策略)
void HolyPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环团队副本策略)
void HolyPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福策略)
void HolyPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福策略)
void HolyPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福PVE策略)
void HolyPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福PVE策略)
void HolyPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福PVP策略)
void HolyPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福PVP策略)
void HolyPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福团队副本策略)
void HolyPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福团队副本策略)
void HolyPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("lay on hands on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("divine favor", ACTION_MEDIUM_HEAL + 6), 
                             new NextAction("holy shock on party", ACTION_MEDIUM_HEAL + 5), 
                             new NextAction("holy light on party", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("divine favor", ACTION_MEDIUM_HEAL + 3), 
                             new NextAction("holy shock", ACTION_MEDIUM_HEAL + 2), 
                             new NextAction("holy light", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("divine shield", ACTION_EMERGENCY + 1),
            new NextAction("holy light", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("flash of light", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of light", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("judgement", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("holy light", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("flash of light", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体策略)
void HolyPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体策略)
void HolyPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体PVE策略)
void HolyPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体PVE策略)
void HolyPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体PVP策略)
void HolyPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体PVP策略)
void HolyPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体团队副本策略)
void HolyPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体团队副本策略)
void HolyPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益Buff策略)
void HolyPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益Buff策略)
void HolyPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益BuffPVE策略)
void HolyPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益BuffPVE策略)
void HolyPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益BuffPVP策略)
void HolyPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益BuffPVP策略)
void HolyPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益Buff团队副本策略)
void HolyPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益Buff团队副本策略)
void HolyPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益策略)
void HolyPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "divine illumination",
        NextAction::array(0, new NextAction("divine illumination", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "divine favor",
        NextAction::array(0, new NextAction("divine favor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益策略)
void HolyPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益PVE策略)
void HolyPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益PVE策略)
void HolyPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益PVP策略)
void HolyPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益PVP策略)
void HolyPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益团队副本策略)
void HolyPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益团队副本策略)
void HolyPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)策略)
void HolyPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)策略)
void HolyPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)PVE策略)
void HolyPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)PVE策略)
void HolyPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)PVP策略)
void HolyPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)PVP策略)
void HolyPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)团队副本策略)
void HolyPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)团队副本策略)
void HolyPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化策略)
void HolyPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化策略)
void HolyPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化PVE策略)
void HolyPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化PVE策略)
void HolyPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化PVP策略)
void HolyPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化PVP策略)
void HolyPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化团队副本策略)
void HolyPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化团队副本策略)
void HolyPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环策略)
void HolyPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环策略)
void HolyPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("concentration aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环PVE策略)
void HolyPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环PVE策略)
void HolyPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环PVP策略)
void HolyPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环PVP策略)
void HolyPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环团队副本策略)
void HolyPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环团队副本策略)
void HolyPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福策略)
void HolyPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福策略)
void HolyPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福PVE策略)
void HolyPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福PVE策略)
void HolyPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福PVP策略)
void HolyPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福PVP策略)
void HolyPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福团队副本策略)
void HolyPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福团队副本策略)
void HolyPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("lay on hands on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "hand of sacrifice",
        NextAction::array(0, new NextAction("hand of sacrifice", ACTION_MEDIUM_HEAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("divine favor", ACTION_MEDIUM_HEAL + 6), 
                             new NextAction("holy shock on party", ACTION_MEDIUM_HEAL + 5), 
                             new NextAction("holy light on party", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("divine favor", ACTION_MEDIUM_HEAL + 3), 
                             new NextAction("holy shock", ACTION_MEDIUM_HEAL + 2), 
                             new NextAction("holy light", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("divine shield", ACTION_EMERGENCY + 1),
            new NextAction("holy light", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("flash of light", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of light", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("judgement of light", ACTION_NORMAL + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("holy light", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("flash of light", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "set glyph::Divinity",
        NextAction::array(0, new NextAction("set glyph::Divinity", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "set glyph::Blessing of Wisdom",
        NextAction::array(0, new NextAction("set glyph::Blessing of Wisdom", ACTION_NORMAL + 1), NULL)));
}

// 初始化反应阶段触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士策略)
void HolyPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士PVE策略)
void HolyPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士PVP策略)
void HolyPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣圣骑士团队副本策略)
void HolyPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体策略)
void HolyPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体策略)
void HolyPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体PVE策略)
void HolyPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体PVE策略)
void HolyPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体PVP策略)
void HolyPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体PVP策略)
void HolyPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士AOE群体团队副本策略)
void HolyPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士AOE群体团队副本策略)
void HolyPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益Buff策略)
void HolyPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益Buff策略)
void HolyPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益BuffPVE策略)
void HolyPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益BuffPVE策略)
void HolyPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益BuffPVP策略)
void HolyPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益BuffPVP策略)
void HolyPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士增益Buff团队副本策略)
void HolyPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士增益Buff团队副本策略)
void HolyPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益策略)
void HolyPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "divine illumination",
        NextAction::array(0, new NextAction("divine illumination", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "divine favor",
        NextAction::array(0, new NextAction("divine favor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益策略)
void HolyPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益PVE策略)
void HolyPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益PVE策略)
void HolyPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益PVP策略)
void HolyPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益PVP策略)
void HolyPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士爆发增益团队副本策略)
void HolyPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士爆发增益团队副本策略)
void HolyPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)策略)
void HolyPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)策略)
void HolyPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)PVE策略)
void HolyPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)PVE策略)
void HolyPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)PVP策略)
void HolyPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)PVP策略)
void HolyPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士控制(CC)团队副本策略)
void HolyPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士控制(CC)团队副本策略)
void HolyPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化策略)
void HolyPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化策略)
void HolyPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化PVE策略)
void HolyPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化PVE策略)
void HolyPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化PVP策略)
void HolyPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化PVP策略)
void HolyPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士驱散净化团队副本策略)
void HolyPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士驱散净化团队副本策略)
void HolyPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环策略)
void HolyPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环策略)
void HolyPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("concentration aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环PVE策略)
void HolyPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环PVE策略)
void HolyPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环PVP策略)
void HolyPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环PVP策略)
void HolyPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士光环团队副本策略)
void HolyPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士光环团队副本策略)
void HolyPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福策略)
void HolyPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福策略)
void HolyPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福PVE策略)
void HolyPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福PVE策略)
void HolyPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福PVP策略)
void HolyPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福PVP策略)
void HolyPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣圣骑士祝福团队副本策略)
void HolyPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣圣骑士祝福团队副本策略)
void HolyPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

