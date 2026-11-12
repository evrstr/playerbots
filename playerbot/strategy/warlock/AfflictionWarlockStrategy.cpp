// 术士 - 痛苦术士策略实现文件 (AfflictionWarlockStrategy.cpp)

#include "playerbot/playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "AfflictionWarlockStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (痛苦术士策略)
ai::NextAction** AfflictionWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("dark pact", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "siphon life",
        NextAction::array(0, new NextAction("siphon life", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体策略)
void AfflictionWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "siphon life on attacker",
        NextAction::array(0, new NextAction("siphon life on attacker", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体策略)
void AfflictionWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体PVE策略)
void AfflictionWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体PVE策略)
void AfflictionWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体PVP策略)
void AfflictionWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体PVP策略)
void AfflictionWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体团队副本策略)
void AfflictionWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体团队副本策略)
void AfflictionWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益Buff策略)
void AfflictionWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益Buff策略)
void AfflictionWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益BuffPVE策略)
void AfflictionWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益BuffPVE策略)
void AfflictionWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益BuffPVP策略)
void AfflictionWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益BuffPVP策略)
void AfflictionWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益Buff团队副本策略)
void AfflictionWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益Buff团队副本策略)
void AfflictionWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益策略)
void AfflictionWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益策略)
void AfflictionWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益PVE策略)
void AfflictionWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益PVE策略)
void AfflictionWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益PVP策略)
void AfflictionWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益PVP策略)
void AfflictionWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益团队副本策略)
void AfflictionWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益团队副本策略)
void AfflictionWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)策略)
void AfflictionWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)策略)
void AfflictionWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)PVE策略)
void AfflictionWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)PVE策略)
void AfflictionWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)PVP策略)
void AfflictionWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("curse of exhaustion", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)PVP策略)
void AfflictionWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)团队副本策略)
void AfflictionWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)团队副本策略)
void AfflictionWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物策略)
void AfflictionWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物策略)
void AfflictionWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物PVE策略)
void AfflictionWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物PVE策略)
void AfflictionWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物PVP策略)
void AfflictionWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物PVP策略)
void AfflictionWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物团队副本策略)
void AfflictionWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物团队副本策略)
void AfflictionWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒策略)
void AfflictionWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒PVE策略)
void AfflictionWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒PVP策略)
void AfflictionWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒团队副本策略)
void AfflictionWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (痛苦术士策略)
ai::NextAction** AfflictionWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("dark pact", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "unstable affliction",
        NextAction::array(0, new NextAction("unstable affliction", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "siphon life",
        NextAction::array(0, new NextAction("siphon life", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体策略)
void AfflictionWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "unstable affliction on attacker",
        NextAction::array(0, new NextAction("unstable affliction on attacker", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "siphon life on attacker",
        NextAction::array(0, new NextAction("siphon life on attacker", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体策略)
void AfflictionWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体PVE策略)
void AfflictionWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体PVE策略)
void AfflictionWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体PVP策略)
void AfflictionWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体PVP策略)
void AfflictionWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体团队副本策略)
void AfflictionWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体团队副本策略)
void AfflictionWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益Buff策略)
void AfflictionWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益Buff策略)
void AfflictionWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益BuffPVE策略)
void AfflictionWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益BuffPVE策略)
void AfflictionWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益BuffPVP策略)
void AfflictionWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益BuffPVP策略)
void AfflictionWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益Buff团队副本策略)
void AfflictionWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益Buff团队副本策略)
void AfflictionWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益策略)
void AfflictionWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益策略)
void AfflictionWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益PVE策略)
void AfflictionWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益PVE策略)
void AfflictionWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益PVP策略)
void AfflictionWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益PVP策略)
void AfflictionWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益团队副本策略)
void AfflictionWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益团队副本策略)
void AfflictionWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)策略)
void AfflictionWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)策略)
void AfflictionWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)PVE策略)
void AfflictionWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)PVE策略)
void AfflictionWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)PVP策略)
void AfflictionWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("curse of exhaustion", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)PVP策略)
void AfflictionWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)团队副本策略)
void AfflictionWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)团队副本策略)
void AfflictionWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物策略)
void AfflictionWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物策略)
void AfflictionWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物PVE策略)
void AfflictionWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物PVE策略)
void AfflictionWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物PVP策略)
void AfflictionWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物PVP策略)
void AfflictionWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物团队副本策略)
void AfflictionWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物团队副本策略)
void AfflictionWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒策略)
void AfflictionWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒PVE策略)
void AfflictionWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒PVP策略)
void AfflictionWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒团队副本策略)
void AfflictionWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (痛苦术士策略)
ai::NextAction** AfflictionWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("dark pact", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "unstable affliction",
        NextAction::array(0, new NextAction("unstable affliction", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "siphon life",
        NextAction::array(0, new NextAction("siphon life", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士策略)
void AfflictionWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士PVE策略)
void AfflictionWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士PVP策略)
void AfflictionWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (痛苦术士团队副本策略)
void AfflictionWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体策略)
void AfflictionWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "unstable affliction on attacker",
        NextAction::array(0, new NextAction("unstable affliction on attacker", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "siphon life on attacker",
        NextAction::array(0, new NextAction("siphon life on attacker", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体策略)
void AfflictionWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体PVE策略)
void AfflictionWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体PVE策略)
void AfflictionWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体PVP策略)
void AfflictionWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体PVP策略)
void AfflictionWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士AOE群体团队副本策略)
void AfflictionWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士AOE群体团队副本策略)
void AfflictionWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益Buff策略)
void AfflictionWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益Buff策略)
void AfflictionWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益BuffPVE策略)
void AfflictionWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益BuffPVE策略)
void AfflictionWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益BuffPVP策略)
void AfflictionWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益BuffPVP策略)
void AfflictionWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士增益Buff团队副本策略)
void AfflictionWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士增益Buff团队副本策略)
void AfflictionWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益策略)
void AfflictionWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益策略)
void AfflictionWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益PVE策略)
void AfflictionWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益PVE策略)
void AfflictionWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益PVP策略)
void AfflictionWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益PVP策略)
void AfflictionWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士爆发增益团队副本策略)
void AfflictionWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士爆发增益团队副本策略)
void AfflictionWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)策略)
void AfflictionWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)策略)
void AfflictionWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)PVE策略)
void AfflictionWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)PVE策略)
void AfflictionWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)PVP策略)
void AfflictionWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("curse of exhaustion", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)PVP策略)
void AfflictionWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士控制(CC)团队副本策略)
void AfflictionWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士控制(CC)团队副本策略)
void AfflictionWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物策略)
void AfflictionWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物策略)
void AfflictionWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物PVE策略)
void AfflictionWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物PVE策略)
void AfflictionWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物PVP策略)
void AfflictionWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物PVP策略)
void AfflictionWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士宠物团队副本策略)
void AfflictionWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (痛苦术士宠物团队副本策略)
void AfflictionWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒策略)
void AfflictionWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒PVE策略)
void AfflictionWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒PVP策略)
void AfflictionWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (痛苦术士诅咒团队副本策略)
void AfflictionWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AfflictionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
