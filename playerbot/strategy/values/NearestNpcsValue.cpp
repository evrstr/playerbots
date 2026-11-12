// 策略值实现：NearestNpcsValue（附近友方/中立 NPC 及可用载具筛选）

#include "playerbot/playerbot.h"
#include "NearestNpcsValue.h"

#include "playerbot/ServerFacade.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"
#ifdef MANGOSBOT_TWO
#include "Entities/Vehicle.h"
#endif

using namespace ai;
using namespace MaNGOS;

// 扫描指定距离内的所有单位
void NearestNpcsValue::FindUnits(std::list<Unit*> &targets)
{
    AnyUnitInObjectRangeCheck u_check(bot, range);
    UnitListSearcher<AnyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

// 保留对机器人非敌对且非玩家的 NPC 单位
bool NearestNpcsValue::AcceptUnit(Unit* unit)
{
    return !sServerFacade.IsHostileTo(unit, bot) && !dynamic_cast<Player*>(unit);
}

// 扫描指定距离内的所有单位用于载具筛选
void NearestVehiclesValue::FindUnits(std::list<Unit*>& targets)
{
    AnyUnitInObjectRangeCheck u_check(bot, range);
    UnitListSearcher<AnyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

// 筛选存活且允许当前机器人登乘的载具（仅 MANGOSBOT_TWO）
bool NearestVehiclesValue::AcceptUnit(Unit* unit)
{
#ifdef MANGOSBOT_TWO
    if (!unit || !unit->IsVehicle() || !unit->IsAlive())
        return false;

    VehicleInfo* veh = unit->GetVehicleInfo();
    if (!veh->CanBoard(bot))
        return false;

    return true;
#endif

    return false;
}
