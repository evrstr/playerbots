/// 测试监听器：战斗相关状态断言实现
#include "playerbot/playerbot.h"
#include "MonitorCombat.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;

/// 检查机器人当前生命值百分比是否满足比较条件
bool MonitorCombatHp::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    uint8 hp = bot->GetHealthPercent();

    std::string valueName;
    std::string op;
    std::string valueStr;
    std::string parseMessage;
    if (TryParseComparisonValue(monitorStr, valueName, op, valueStr, parseMessage, GetName()) != TestResult::PASS)
        return false;

    uint32 threshold = 0;
    if (TryParseUInt32Strict(valueStr, threshold, parseMessage, GetName()) != TestResult::PASS)
        return false;

    if (op == "<")
        return hp < threshold;

    return hp > threshold;
}

/// 检查机器人是否已脱离战斗状态
bool MonitorNotInCombat::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    if (bot->IsInCombat())
    {
        ctx.combatSeen = true;
        return false;
    }

    return ctx.combatSeen;
}

/// 检查指定 Entry 的怪物是否全部死亡或被击败
bool MonitorCombatMob::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    // monitorStr has "mob" prefix already stripped, e.g. " 11520 is dead => pass ..." | monitorStr 已剥离 "mob" 前缀，例如 " 11520 is dead => pass ..."
    size_t entryEnd = monitorStr.find("is dead");

    if (entryEnd == std::string::npos)
        return false;

    std::string entryStr = monitorStr.substr(0, entryEnd);
    uint32 entryId = atoi(entryStr.c_str());

    // Fast path: if focus mob tracking confirmed this entry dead | 快速路径：若焦点怪物追踪已确认该条目死亡
    if (ctx.focusMobKilled && ctx.focusMobEntry == entryId)
        return true;

    std::list<Creature*> creatures;
    MaNGOS::AnyUnitInObjectRangeCheck checker(bot, 500.0f);
    MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitInObjectRangeCheck> searcher(creatures, checker);
    Cell::VisitAllObjects(bot, searcher, 500.0f);

    bool found = false;
    bool allDead = true;

    for (auto& creature : creatures)
    {
        if (creature->GetEntry() == entryId)
        {
            found = true;
            if (creature->IsAlive())
                allDead = false;
        }
    }

    // Also check map store if not found nearby | 若附近未找到则进一步检查地图对象存储
    if (!found)
    {
        auto& objectStore = bot->GetMap()->GetObjectsStore();
        for (auto itr = objectStore.begin<Creature>(); itr != objectStore.end<Creature>(); ++itr)
        {
            if (Creature* c = itr->second)
            {
                if (c->GetEntry() == entryId)
                {
                    found = true;
                    if (c->IsAlive())
                        allDead = false;
                    break;
                }
            }
        }
    }

    if (found && allDead)   
        return true;

    return false;
}

/// 检查指定怪物是否处于归位点附近且未在战斗中（脱战归位检测）
bool MonitorCombatMobHome::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    size_t entryEnd = monitorStr.find("is home");

    if (entryEnd == std::string::npos)
        return false;

    std::string entryStr = monitorStr.substr(0, entryEnd);
    uint32 entryId = atoi(entryStr.c_str());

    if (!entryId)
        return false;

    float threshold = 5.0f;
    size_t thresholdPos = monitorStr.find_first_not_of(' ', entryEnd + 7);
    if (thresholdPos != std::string::npos)
    {
        float parsed = atof(monitorStr.c_str() + thresholdPos);
        if (parsed > 0.0f)
            threshold = parsed;
    }

    std::list<Creature*> creatures;
    MaNGOS::AnyUnitInObjectRangeCheck checker(bot, 500.0f);
    MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitInObjectRangeCheck> searcher(creatures, checker);
    Cell::VisitAllObjects(bot, searcher, 500.0f);

    auto& objectStore = bot->GetMap()->GetObjectsStore();
    bool found = false;
    bool foundAlive = false;
    bool anyCombat = false;
    bool tooFar = false;

    for (auto& creature : creatures)
    {
        if (creature->GetEntry() != entryId)
            continue;

        found = true;

        if (!creature->IsAlive())
            continue;

        foundAlive = true;

        if (creature->IsInCombat())
        {
            ctx.combatSeen = true;
            anyCombat = true;
        }
        else
        {
            float rx, ry, rz;
            creature->GetRespawnCoord(rx, ry, rz);
            if (creature->GetDistance2d(rx, ry, DIST_CALC_NONE) > threshold * threshold)
                tooFar = true;
        }
    }

    if (!found)
    {
        for (auto itr = objectStore.begin<Creature>(); itr != objectStore.end<Creature>(); ++itr)
        {
            Creature* creature = itr->second;
            if (!creature || creature->GetEntry() != entryId)
                continue;

            found = true;

            if (!creature->IsAlive())
                continue;

            foundAlive = true;

            if (creature->IsInCombat())
            {
                ctx.combatSeen = true;
                anyCombat = true;
            }
            else
            {
                float rx, ry, rz;
                creature->GetRespawnCoord(rx, ry, rz);
                if (creature->GetDistance2d(rx, ry, DIST_CALC_NONE) > threshold * threshold)
                    tooFar = true;
            }
        }
    }

    if (anyCombat || tooFar)
        return false;

    return foundAlive && ctx.combatSeen;
}

/// 检查整个测试小队成员是否全部阵亡（团灭判定）
bool MonitorCombatPartyWiped::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    Group* group = bot->GetGroup();
    if (!group)
        return false;

    uint32 aliveCount = 0;
    for (auto itr = group->GetMemberSlots().begin(); itr != group->GetMemberSlots().end(); ++itr)
    {
        Player* member = sObjectMgr.GetPlayer(itr->guid);
        if (member && member->IsAlive())
            aliveCount++;
    }

    if (aliveCount == 0)
        return true;

    return false;
}

/// 累计统计 300 码范围内已观测到的死亡怪物数量是否达到阈值
bool MonitorCombatDeadMobs::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    // Sweep a wide radius around the bot and latch every dead creature GUID into ctx. A corpse only | 大范围扫描并锁存已发现的死亡生物 GUID，避免尸体被秒拾取后漏计
    // needs to be observed once: bots loot kills almost immediately, so simultaneous-corpses counts
    // collapse to 0-2 in sparse-start instances even though the party is killing continuously.
    std::list<Creature*> creatures;
    // GetDistance(..., DIST_CALC_NONE) returns the SQUARED distance, so the checker range must be | DIST_CALC_NONE 使用距离平方判定，因此 checker 半径参数需平方，VisitAllObjects 仍传线性半径
    // squared too; VisitAllObjects keeps the linear radius for the cell visit.
    MaNGOS::AnyUnitFulfillingConditionInRangeCheck checker(bot, [](Unit* u) { return !u->IsAlive(); }, 300.0f * 300.0f, DIST_CALC_NONE);
    MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitFulfillingConditionInRangeCheck> searcher(creatures, checker);
    Cell::VisitAllObjects(bot, searcher, 300.0f);

    for (auto& creature : creatures)
    {
        if (!creature->IsAlive() && !creature->IsPet() && !creature->IsTotem())
            ctx.observedDeadMobs.insert(creature->GetObjectGuid());
    }

    uint32 deadCount = static_cast<uint32>(ctx.observedDeadMobs.size());

    std::string valueName;
    std::string op;
    std::string valueStr;
    std::string parseMessage;
    if (TryParseComparisonValue(monitorStr, valueName, op, valueStr, parseMessage, GetName()) != TestResult::PASS)
        return false;

    uint32 threshold = 0;
    if (TryParseUInt32Strict(valueStr, threshold, parseMessage, GetName()) != TestResult::PASS)
        return false;

    if (op == ">")
        return deadCount > threshold;

    return deadCount < threshold;

}

/// 统计全队相对于测试基线的累计获得经验值是否达到阈值
bool MonitorCombatPartyXp::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    if (!ctx.partyXpCaptured)
        return false;

    uint64 current = GetPartyXpTotal(bot);
    uint64 start = ctx.partyXpStart;
    // Members can leave (or be logged out) mid-run and drop the summed total below the baseline. | 防止中途退队导致全队经验总和低于基线造成无符号下溢
    uint64 gained = current > start ? current - start : 0;

    std::string valueName;
    std::string op;
    std::string valueStr;
    std::string parseMessage;
    if (TryParseComparisonValue(monitorStr, valueName, op, valueStr, parseMessage, GetName()) != TestResult::PASS)
        return false;

    uint32 threshold = 0;
    if (TryParseUInt32Strict(valueStr, threshold, parseMessage, GetName()) != TestResult::PASS)
        return false;

    if (op == ">")
        return gained > threshold;

    return gained < threshold;
}