// 潜行者 - 战斗潜行者策略实现文件 (CombatRogueStrategy.cpp)

#include "playerbot/playerbot.h"
#include "CombatRogueStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "riposte",
        NextAction::array(0, new NextAction("riposte", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "slice and dice",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "eviscerate",
        NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "rupture",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "sinister strike",
        NextAction::array(0, new NextAction("sinister strike", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体策略)
void CombatRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体策略)
void CombatRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体PVE策略)
void CombatRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体PVE策略)
void CombatRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体PVP策略)
void CombatRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体PVP策略)
void CombatRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体团队副本策略)
void CombatRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体团队副本策略)
void CombatRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益Buff策略)
void CombatRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益Buff策略)
void CombatRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益BuffPVE策略)
void CombatRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益BuffPVE策略)
void CombatRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益BuffPVP策略)
void CombatRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益BuffPVP策略)
void CombatRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益Buff团队副本策略)
void CombatRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益Buff团队副本策略)
void CombatRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益策略)
void CombatRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益策略)
void CombatRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "adrenaline rush",
        NextAction::array(0, new NextAction("adrenaline rush", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "blade flurry",
        NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益PVE策略)
void CombatRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益PVE策略)
void CombatRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益PVP策略)
void CombatRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益PVP策略)
void CombatRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益团队副本策略)
void CombatRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益团队副本策略)
void CombatRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)策略)
void CombatRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)策略)
void CombatRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)PVE策略)
void CombatRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)PVE策略)
void CombatRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)PVP策略)
void CombatRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)PVP策略)
void CombatRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)团队副本策略)
void CombatRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)团队副本策略)
void CombatRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行策略)
void CombatRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行策略)
void CombatRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行PVE策略)
void CombatRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行PVE策略)
void CombatRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行PVP策略)
void CombatRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行PVP策略)
void CombatRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行团队副本策略)
void CombatRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行团队副本策略)
void CombatRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药策略)
void CombatRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药策略)
void CombatRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药PVE策略)
void CombatRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药PVE策略)
void CombatRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药PVP策略)
void CombatRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药PVP策略)
void CombatRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药团队副本策略)
void CombatRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药团队副本策略)
void CombatRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "riposte",
        NextAction::array(0, new NextAction("riposte", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "slice and dice",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "eviscerate",
        NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "rupture",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "sinister strike",
        NextAction::array(0, new NextAction("sinister strike", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体策略)
void CombatRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH + 4), NULL)));

    //triggers.push_back(new TriggerNode(
        //"melee light aoe",
        //NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 4), NULL)));
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体策略)
void CombatRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体PVE策略)
void CombatRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体PVE策略)
void CombatRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体PVP策略)
void CombatRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体PVP策略)
void CombatRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体团队副本策略)
void CombatRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体团队副本策略)
void CombatRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益Buff策略)
void CombatRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益Buff策略)
void CombatRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益BuffPVE策略)
void CombatRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益BuffPVE策略)
void CombatRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益BuffPVP策略)
void CombatRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益BuffPVP策略)
void CombatRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益Buff团队副本策略)
void CombatRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益Buff团队副本策略)
void CombatRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益策略)
void CombatRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益策略)
void CombatRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "adrenaline rush",
        NextAction::array(0, new NextAction("adrenaline rush", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "blade flurry",
        NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益PVE策略)
void CombatRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益PVE策略)
void CombatRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益PVP策略)
void CombatRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益PVP策略)
void CombatRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益团队副本策略)
void CombatRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益团队副本策略)
void CombatRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)策略)
void CombatRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)策略)
void CombatRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)PVE策略)
void CombatRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)PVE策略)
void CombatRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)PVP策略)
void CombatRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)PVP策略)
void CombatRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)团队副本策略)
void CombatRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)团队副本策略)
void CombatRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行策略)
void CombatRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行策略)
void CombatRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行PVE策略)
void CombatRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行PVE策略)
void CombatRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行PVP策略)
void CombatRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行PVP策略)
void CombatRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行团队副本策略)
void CombatRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行团队副本策略)
void CombatRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药策略)
void CombatRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药策略)
void CombatRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药PVE策略)
void CombatRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药PVE策略)
void CombatRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药PVP策略)
void CombatRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药PVP策略)
void CombatRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药团队副本策略)
void CombatRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药团队副本策略)
void CombatRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "riposte",
        NextAction::array(0, new NextAction("riposte", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "slice and dice",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "eviscerate",
        NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "rupture",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "sinister strike",
        NextAction::array(0, new NextAction("sinister strike", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者策略)
void CombatRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者PVE策略)
void CombatRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者PVP策略)
void CombatRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战斗潜行者团队副本策略)
void CombatRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体策略)
void CombatRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH + 4), NULL)));

    //triggers.push_back(new TriggerNode(
        //"melee light aoe",
        //NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 4), NULL)));
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体策略)
void CombatRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体PVE策略)
void CombatRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体PVE策略)
void CombatRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体PVP策略)
void CombatRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体PVP策略)
void CombatRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者AOE群体团队副本策略)
void CombatRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者AOE群体团队副本策略)
void CombatRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益Buff策略)
void CombatRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益Buff策略)
void CombatRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益BuffPVE策略)
void CombatRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益BuffPVE策略)
void CombatRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益BuffPVP策略)
void CombatRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益BuffPVP策略)
void CombatRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者增益Buff团队副本策略)
void CombatRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者增益Buff团队副本策略)
void CombatRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益策略)
void CombatRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益策略)
void CombatRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "adrenaline rush",
        NextAction::array(0, new NextAction("adrenaline rush", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "blade flurry",
        NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "killing spree",
        NextAction::array(0, new NextAction("killing spree", ACTION_HIGH + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益PVE策略)
void CombatRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益PVE策略)
void CombatRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益PVP策略)
void CombatRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益PVP策略)
void CombatRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者爆发增益团队副本策略)
void CombatRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者爆发增益团队副本策略)
void CombatRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)策略)
void CombatRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)策略)
void CombatRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)PVE策略)
void CombatRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)PVE策略)
void CombatRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)PVP策略)
void CombatRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)PVP策略)
void CombatRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者控制(CC)团队副本策略)
void CombatRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者控制(CC)团队副本策略)
void CombatRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行策略)
void CombatRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行策略)
void CombatRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行PVE策略)
void CombatRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行PVE策略)
void CombatRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行PVP策略)
void CombatRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行PVP策略)
void CombatRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者潜行团队副本策略)
void CombatRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者潜行团队副本策略)
void CombatRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药策略)
void CombatRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药策略)
void CombatRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药PVE策略)
void CombatRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药PVE策略)
void CombatRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药PVP策略)
void CombatRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药PVP策略)
void CombatRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战斗潜行者毒药团队副本策略)
void CombatRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战斗潜行者毒药团队副本策略)
void CombatRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CombatRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
