// 术士 - 毁灭术士策略实现文件 (DestructionWarlockStrategy.cpp)

#include "playerbot/playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "DestructionWarlockStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (毁灭术士策略)
ai::NextAction** DestructionWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "conflagrate",
        NextAction::array(0, new NextAction("conflagrate", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "immolate",
        NextAction::array(0, new NextAction("immolate", ACTION_NORMAL + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体策略)
void DestructionWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体策略)
void DestructionWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体PVE策略)
void DestructionWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体PVE策略)
void DestructionWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体PVP策略)
void DestructionWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体PVP策略)
void DestructionWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体团队副本策略)
void DestructionWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体团队副本策略)
void DestructionWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益Buff策略)
void DestructionWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益Buff策略)
void DestructionWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益BuffPVE策略)
void DestructionWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益BuffPVE策略)
void DestructionWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益BuffPVP策略)
void DestructionWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益BuffPVP策略)
void DestructionWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益Buff团队副本策略)
void DestructionWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益Buff团队副本策略)
void DestructionWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益策略)
void DestructionWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益策略)
void DestructionWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益PVE策略)
void DestructionWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益PVE策略)
void DestructionWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益PVP策略)
void DestructionWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益PVP策略)
void DestructionWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益团队副本策略)
void DestructionWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益团队副本策略)
void DestructionWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)策略)
void DestructionWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)策略)
void DestructionWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)PVE策略)
void DestructionWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)PVE策略)
void DestructionWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)PVP策略)
void DestructionWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)PVP策略)
void DestructionWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)团队副本策略)
void DestructionWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)团队副本策略)
void DestructionWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物策略)
void DestructionWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物策略)
void DestructionWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物PVE策略)
void DestructionWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物PVE策略)
void DestructionWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物PVP策略)
void DestructionWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物PVP策略)
void DestructionWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物团队副本策略)
void DestructionWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物团队副本策略)
void DestructionWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒策略)
void DestructionWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒PVE策略)
void DestructionWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒PVP策略)
void DestructionWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒团队副本策略)
void DestructionWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (毁灭术士策略)
ai::NextAction** DestructionWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("incinerate", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "backlash",
        NextAction::array(0, new NextAction("incinerate", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "conflagrate",
        NextAction::array(0, new NextAction("conflagrate", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "immolate",
        NextAction::array(0, new NextAction("immolate", ACTION_NORMAL + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体策略)
void DestructionWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体策略)
void DestructionWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体PVE策略)
void DestructionWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体PVE策略)
void DestructionWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体PVP策略)
void DestructionWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体PVP策略)
void DestructionWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体团队副本策略)
void DestructionWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体团队副本策略)
void DestructionWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益Buff策略)
void DestructionWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益Buff策略)
void DestructionWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益BuffPVE策略)
void DestructionWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益BuffPVE策略)
void DestructionWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益BuffPVP策略)
void DestructionWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益BuffPVP策略)
void DestructionWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益Buff团队副本策略)
void DestructionWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益Buff团队副本策略)
void DestructionWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益策略)
void DestructionWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益策略)
void DestructionWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益PVE策略)
void DestructionWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益PVE策略)
void DestructionWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益PVP策略)
void DestructionWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益PVP策略)
void DestructionWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益团队副本策略)
void DestructionWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益团队副本策略)
void DestructionWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)策略)
void DestructionWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadowfury interrupt",
        NextAction::array(0, new NextAction("shadowfury", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadowfury on snare target",
        NextAction::array(0, new NextAction("shadowfury on snare target", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)策略)
void DestructionWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)PVE策略)
void DestructionWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)PVE策略)
void DestructionWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)PVP策略)
void DestructionWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)PVP策略)
void DestructionWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)团队副本策略)
void DestructionWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)团队副本策略)
void DestructionWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物策略)
void DestructionWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物策略)
void DestructionWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物PVE策略)
void DestructionWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物PVE策略)
void DestructionWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物PVP策略)
void DestructionWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物PVP策略)
void DestructionWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物团队副本策略)
void DestructionWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物团队副本策略)
void DestructionWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒策略)
void DestructionWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒PVE策略)
void DestructionWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒PVP策略)
void DestructionWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒团队副本策略)
void DestructionWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (毁灭术士策略)
ai::NextAction** DestructionWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("incinerate", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "backlash",
        NextAction::array(0, new NextAction("shadow bolt", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "conflagrate",
        NextAction::array(0, new NextAction("conflagrate", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "immolate",
        NextAction::array(0, new NextAction("immolate", ACTION_NORMAL + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士策略)
void DestructionWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士PVE策略)
void DestructionWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士PVP策略)
void DestructionWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (毁灭术士团队副本策略)
void DestructionWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体策略)
void DestructionWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体策略)
void DestructionWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体PVE策略)
void DestructionWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体PVE策略)
void DestructionWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体PVP策略)
void DestructionWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体PVP策略)
void DestructionWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士AOE群体团队副本策略)
void DestructionWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士AOE群体团队副本策略)
void DestructionWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益Buff策略)
void DestructionWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益Buff策略)
void DestructionWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益BuffPVE策略)
void DestructionWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益BuffPVE策略)
void DestructionWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益BuffPVP策略)
void DestructionWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益BuffPVP策略)
void DestructionWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士增益Buff团队副本策略)
void DestructionWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士增益Buff团队副本策略)
void DestructionWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益策略)
void DestructionWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益策略)
void DestructionWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益PVE策略)
void DestructionWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益PVE策略)
void DestructionWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益PVP策略)
void DestructionWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益PVP策略)
void DestructionWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士爆发增益团队副本策略)
void DestructionWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士爆发增益团队副本策略)
void DestructionWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)策略)
void DestructionWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadowfury interrupt",
        NextAction::array(0, new NextAction("shadowfury", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadowfury on snare target",
        NextAction::array(0, new NextAction("shadowfury on snare target", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)策略)
void DestructionWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)PVE策略)
void DestructionWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)PVE策略)
void DestructionWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)PVP策略)
void DestructionWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)PVP策略)
void DestructionWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士控制(CC)团队副本策略)
void DestructionWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士控制(CC)团队副本策略)
void DestructionWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物策略)
void DestructionWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物策略)
void DestructionWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物PVE策略)
void DestructionWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物PVE策略)
void DestructionWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物PVP策略)
void DestructionWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物PVP策略)
void DestructionWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士宠物团队副本策略)
void DestructionWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (毁灭术士宠物团队副本策略)
void DestructionWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒策略)
void DestructionWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒PVE策略)
void DestructionWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒PVP策略)
void DestructionWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (毁灭术士诅咒团队副本策略)
void DestructionWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DestructionWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
