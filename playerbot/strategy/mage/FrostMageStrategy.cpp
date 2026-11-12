// 法师 - 冰霜法师策略实现文件 (FrostMageStrategy.cpp)

#include "playerbot/playerbot.h"
#include "MageMultipliers.h"
#include "FrostMageStrategy.h"

using namespace ai;

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (冰霜法师策略)
NextAction** FrostMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("frostbolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体策略)
void FrostMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("blizzard", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "frost spells locked",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体策略)
void FrostMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体PVE策略)
void FrostMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体PVE策略)
void FrostMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体PVP策略)
void FrostMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体PVP策略)
void FrostMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体团队副本策略)
void FrostMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体团队副本策略)
void FrostMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益Buff策略)
void FrostMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice barrier",
        NextAction::array(0, new NextAction("ice barrier", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益Buff策略)
void FrostMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益BuffPVE策略)
void FrostMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益BuffPVE策略)
void FrostMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益BuffPVP策略)
void FrostMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益BuffPVP策略)
void FrostMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益Buff团队副本策略)
void FrostMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益Buff团队副本策略)
void FrostMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益策略)
void FrostMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cold snap",
        NextAction::array(0, new NextAction("cold snap", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益策略)
void FrostMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益PVE策略)
void FrostMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益PVE策略)
void FrostMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益PVP策略)
void FrostMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益PVP策略)
void FrostMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益团队副本策略)
void FrostMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益团队副本策略)
void FrostMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)策略)
void FrostMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)策略)
void FrostMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)PVE策略)
void FrostMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)PVE策略)
void FrostMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)PVP策略)
void FrostMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)PVP策略)
void FrostMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)团队副本策略)
void FrostMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)团队副本策略)
void FrostMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化策略)
void FrostMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化策略)
void FrostMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化PVE策略)
void FrostMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化PVE策略)
void FrostMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化PVP策略)
void FrostMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化PVP策略)
void FrostMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化团队副本策略)
void FrostMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化团队副本策略)
void FrostMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (冰霜法师策略)
NextAction** FrostMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("frostbolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice lance",
        NextAction::array(0, new NextAction("ice lance", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体策略)
void FrostMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("blizzard", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "frost spells locked",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体策略)
void FrostMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体PVE策略)
void FrostMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体PVE策略)
void FrostMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体PVP策略)
void FrostMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体PVP策略)
void FrostMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体团队副本策略)
void FrostMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体团队副本策略)
void FrostMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益Buff策略)
void FrostMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice barrier",
        NextAction::array(0, new NextAction("ice barrier", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益Buff策略)
void FrostMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益BuffPVE策略)
void FrostMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mage armor",
        NextAction::array(0, new NextAction("mage armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益BuffPVE策略)
void FrostMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mage armor",
        NextAction::array(0, new NextAction("mage armor", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (冰霜法师增益BuffPVP策略)
void FrostMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益BuffPVP策略)
void FrostMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益Buff团队副本策略)
void FrostMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益Buff团队副本策略)
void FrostMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益策略)
void FrostMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cold snap",
        NextAction::array(0, new NextAction("cold snap", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "summon water elemental",
        NextAction::array(0, new NextAction("summon water elemental", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "icy veins",
        NextAction::array(0, new NextAction("icy veins", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益策略)
void FrostMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益PVE策略)
void FrostMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益PVE策略)
void FrostMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益PVP策略)
void FrostMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益PVP策略)
void FrostMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益团队副本策略)
void FrostMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益团队副本策略)
void FrostMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)策略)
void FrostMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)策略)
void FrostMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)PVE策略)
void FrostMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)PVE策略)
void FrostMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)PVP策略)
void FrostMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)PVP策略)
void FrostMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)团队副本策略)
void FrostMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)团队副本策略)
void FrostMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化策略)
void FrostMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化策略)
void FrostMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化PVE策略)
void FrostMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化PVE策略)
void FrostMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化PVP策略)
void FrostMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化PVP策略)
void FrostMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化团队副本策略)
void FrostMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化团队副本策略)
void FrostMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (冰霜法师策略)
NextAction** FrostMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("frostbolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "free fireball",
        NextAction::array(0, new NextAction("frostfire bolt", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "fingers of frost",
        NextAction::array(0, new NextAction("deep freeze", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ice lance",
        NextAction::array(0, new NextAction("ice lance", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师策略)
void FrostMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师PVE策略)
void FrostMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师PVP策略)
void FrostMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (冰霜法师团队副本策略)
void FrostMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体策略)
void FrostMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("blizzard", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "frost spells locked",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体策略)
void FrostMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体PVE策略)
void FrostMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体PVE策略)
void FrostMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体PVP策略)
void FrostMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体PVP策略)
void FrostMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师AOE群体团队副本策略)
void FrostMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师AOE群体团队副本策略)
void FrostMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益Buff策略)
void FrostMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice barrier",
        NextAction::array(0, new NextAction("ice barrier", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益Buff策略)
void FrostMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益BuffPVE策略)
void FrostMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益BuffPVE策略)
void FrostMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益BuffPVP策略)
void FrostMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益BuffPVP策略)
void FrostMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师增益Buff团队副本策略)
void FrostMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师增益Buff团队副本策略)
void FrostMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益策略)
void FrostMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cold snap",
        NextAction::array(0, new NextAction("cold snap", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "summon water elemental",
        NextAction::array(0, new NextAction("summon water elemental", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "icy veins",
        NextAction::array(0, new NextAction("icy veins", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益策略)
void FrostMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益PVE策略)
void FrostMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益PVE策略)
void FrostMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益PVP策略)
void FrostMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益PVP策略)
void FrostMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师爆发增益团队副本策略)
void FrostMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师爆发增益团队副本策略)
void FrostMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)策略)
void FrostMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)策略)
void FrostMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)PVE策略)
void FrostMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)PVE策略)
void FrostMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)PVP策略)
void FrostMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)PVP策略)
void FrostMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师控制(CC)团队副本策略)
void FrostMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师控制(CC)团队副本策略)
void FrostMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化策略)
void FrostMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化策略)
void FrostMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化PVE策略)
void FrostMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化PVE策略)
void FrostMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化PVP策略)
void FrostMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化PVP策略)
void FrostMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (冰霜法师驱散净化团队副本策略)
void FrostMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (冰霜法师驱散净化团队副本策略)
void FrostMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FrostMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
