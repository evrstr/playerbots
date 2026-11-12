// 策略值实现：NearestFriendlyPlayersValue（扫描并筛选附近友方玩家）

#include "playerbot/playerbot.h"
#include "NearestFriendlyPlayersValue.h"

#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;
using namespace MaNGOS;

// 使用 AnyFriendlyUnitInObjectRangeCheck 扫描范围内的友方单位
void NearestFriendlyPlayersValue::FindUnits(std::list<Unit*> &targets)
{
    AnyFriendlyUnitInObjectRangeCheck u_check(bot, range);
    UnitListSearcher<AnyFriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

// 仅保留非机器人自身的玩家单位
bool NearestFriendlyPlayersValue::AcceptUnit(Unit* unit)
{
    ObjectGuid guid = unit->GetObjectGuid();
    return guid.IsPlayer() && guid != ai->GetBot()->GetObjectGuid();
}
