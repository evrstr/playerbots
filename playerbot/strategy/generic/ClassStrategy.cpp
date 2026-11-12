/// 通用职业基础策略、子模块与占位策略跨版本（Vanilla / TBC / WOTLK）实现

#include "playerbot/playerbot.h"
#include "ClassStrategy.h"

using namespace ai;

#ifdef MANGOSBOT_ZERO // Vanilla | 经典旧世（60级）分支

/// [Vanilla] 初始化职业通用战斗触发器（重选目标、坐骑、光束泉、脱困/僵持处理）
void ClassStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "invalid target",
        NextAction::array(0, new NextAction("select new target", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "mounted",
        NextAction::array(0, new NextAction("check mount state", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "combat long stuck",
        NextAction::array(0, new NextAction("unstuck", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "combat stuck",
        NextAction::array(0, new NextAction("unstuck", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "combat standoff",
        NextAction::array(0, new NextAction("drop standoff", 91.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "movement loop stuck",
        NextAction::array(0, new NextAction("release stuck movement", 101.0f), NULL)));
}

/// [Vanilla] 初始化职业通用非战斗触发器
void ClassStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    /*
    triggers.push_back(new TriggerNode(
        "vehicle near",
        NextAction::array(0, new NextAction("enter vehicle", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", 80.0f), NULL)));
    */

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("check mount state", ACTION_IDLE), new NextAction("check values", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "near dark portal",
        NextAction::array(0, new NextAction("move to dark portal", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal azeroth",
        NextAction::array(0, new NextAction("use dark portal azeroth", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal outland",
        NextAction::array(0, new NextAction("move from dark portal", ACTION_IDLE), NULL)));
}

/// [Vanilla] 初始化职业通用状态切换反应触发器（进战/脱战/死亡/复活）
void ClassStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "combat start",
        NextAction::array(0, new NextAction("set combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "combat end",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "death",
        NextAction::array(0, new NextAction("set dead state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "resurrect",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));
}

/// [Vanilla] 初始化职业通用死亡触发器
void ClassStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("free action potion", ACTION_HIGH), NULL)));
}

void ClassPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

/// [Vanilla] 初始化通用 AoE 战斗触发器（如使用工程炸弹/饰品等）
void AoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "melee very high aoe",
        NextAction::array(0, new NextAction("goblin sapper", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("throw grenade", ACTION_HIGH), NULL)));
}

void AoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

/// [Vanilla] 初始化通用爆发策略战斗触发器（主动饰品）
void BoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("use trinket", ACTION_HIGH), NULL)));
}

void BoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}


#endif
#ifdef MANGOSBOT_ONE // TBC | 燃烧的远征（70级）分支

/// [TBC] 初始化职业通用战斗触发器（重选目标、坐骑、光束泉、脱困/僵持处理）
void ClassStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "invalid target",
        NextAction::array(0, new NextAction("select new target", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "mounted",
        NextAction::array(0, new NextAction("check mount state", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "combat long stuck",
        NextAction::array(0, new NextAction("unstuck", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "combat stuck",
        NextAction::array(0, new NextAction("unstuck", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "combat standoff",
        NextAction::array(0, new NextAction("drop standoff", 91.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "movement loop stuck",
        NextAction::array(0, new NextAction("release stuck movement", 101.0f), NULL)));
}

/// [TBC] 初始化职业通用非战斗触发器
void ClassStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    /*
    triggers.push_back(new TriggerNode(
        "vehicle near",
        NextAction::array(0, new NextAction("enter vehicle", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", 80.0f), NULL)));
    */

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("check mount state", ACTION_IDLE), new NextAction("check values", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "near dark portal",
        NextAction::array(0, new NextAction("move to dark portal", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal azeroth",
        NextAction::array(0, new NextAction("use dark portal azeroth", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal outland",
        NextAction::array(0, new NextAction("move from dark portal", ACTION_IDLE), NULL)));
}

/// [TBC] 初始化职业通用状态切换反应触发器（进战/脱战/死亡/复活）
void ClassStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "combat start",
        NextAction::array(0, new NextAction("set combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "combat end",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "death",
        NextAction::array(0, new NextAction("set dead state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "resurrect",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));
}

/// [TBC] 初始化职业通用死亡触发器
void ClassStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

/// [TBC] 初始化通用 AoE 战斗触发器
void AoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "melee very high aoe",
        NextAction::array(0, new NextAction("goblin sapper", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("throw grenade", ACTION_HIGH), NULL)));
}

void AoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

/// [TBC] 初始化通用爆发策略战斗触发器
void BoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("use trinket", ACTION_HIGH), NULL)));
}

void BoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif
#ifdef MANGOSBOT_TWO // WOTLK | 巫妖王之怒（80级）分支

/// [WOTLK] 初始化职业通用战斗触发器（重选目标、坐骑、光束泉、脱困/僵持处理）
void ClassStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "invalid target",
        NextAction::array(0, new NextAction("select new target", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "mounted",
        NextAction::array(0, new NextAction("check mount state", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("use trinket", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "combat long stuck",
        NextAction::array(0, new NextAction("unstuck", static_cast<float>(ACTION_IDLE) - 0.1f), NULL)));

    triggers.push_back(new TriggerNode(
        "combat stuck",
        NextAction::array(0, new NextAction("unstuck", static_cast<float>(ACTION_IDLE) - 0.3f), NULL)));

    triggers.push_back(new TriggerNode(
        "combat standoff",
        NextAction::array(0, new NextAction("drop standoff", 91.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "movement loop stuck",
        NextAction::array(0, new NextAction("release stuck movement", 101.0f), NULL)));
}

/// [WOTLK] 初始化职业通用非战斗触发器
void ClassStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    /*
    triggers.push_back(new TriggerNode(
        "vehicle near",
        NextAction::array(0, new NextAction("enter vehicle", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", 80.0f), NULL)));
    */

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("check mount state", ACTION_IDLE), new NextAction("check values", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "near dark portal",
        NextAction::array(0, new NextAction("move to dark portal", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal azeroth",
        NextAction::array(0, new NextAction("use dark portal azeroth", ACTION_IDLE), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal outland",
        NextAction::array(0, new NextAction("move from dark portal", ACTION_IDLE), NULL)));
}

/// [WOTLK] 初始化职业通用状态切换反应触发器（进战/脱战/死亡/复活）
void ClassStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "combat start",
        NextAction::array(0, new NextAction("set combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "combat end",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "death",
        NextAction::array(0, new NextAction("set dead state", ACTION_PASSTROUGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "resurrect",
        NextAction::array(0, new NextAction("set non combat state", ACTION_PASSTROUGH + 10), NULL)));
}

/// [WOTLK] 初始化职业通用死亡触发器
void ClassStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{

}

void ClassRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{

}

/// [WOTLK] 初始化通用 AoE 战斗触发器
void AoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "melee very high aoe",
        NextAction::array(0, new NextAction("goblin sapper", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("throw grenade", ACTION_HIGH), NULL)));
}

void AoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void AoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void CcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

/// [WOTLK] 初始化通用爆发策略战斗触发器
void BoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("use trinket", ACTION_HIGH), NULL)));
}

void BoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void BoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void StealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

void OffdpsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}


#endif

/// 初始化专精占位策略战斗触发器：按当前场景动态更新 PvE/PvP/Raid 子策略
void SpecPlaceholderStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "in pve",
        NextAction::array(0, new NextAction("update pve strats", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "in pvp",
        NextAction::array(0, new NextAction("update pvp strats", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "in raid fight",
        NextAction::array(0, new NextAction("update raid strats", ACTION_PASSTROUGH), NULL)));
}

/// 初始化专精占位策略非战斗触发器：按当前场景动态更新 PvE/PvP/Raid 子策略
void SpecPlaceholderStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "in pve",
        NextAction::array(0, new NextAction("update pve strats", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "in pvp",
        NextAction::array(0, new NextAction("update pvp strats", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "in raid fight",
        NextAction::array(0, new NextAction("update raid strats", ACTION_PASSTROUGH), NULL)));
}
