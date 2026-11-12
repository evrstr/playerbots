// 策略值实现：NearestNonBotPlayersValue（扫描并筛选附近的真人玩家）

#include "playerbot/playerbot.h"
#include "NearestNonBotPlayersValue.h"

#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;
using namespace MaNGOS;

// 扫描反应距离内的所有单位
void NearestNonBotPlayersValue::FindUnits(std::list<Unit*> &targets)
{
    AnyUnitInObjectRangeCheck u_check(bot, range);
    UnitListSearcher<AnyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

// 保留非机器人且非不可见 GM 的真实玩家单位
bool NearestNonBotPlayersValue::AcceptUnit(Unit* unit)
{
    ObjectGuid guid = unit->GetObjectGuid();
#ifdef MANGOS
    return guid.IsPlayer() && !((Player*)unit)->GetPlayerbotAI() && (!((Player*)unit)->isGameMaster() || ((Player*)unit)->isGMVisible());
#endif
#ifdef CMANGOS
    return guid.IsPlayer() && !((Player*)unit)->GetPlayerbotAI() && (!((Player*)unit)->IsGameMaster() || ((Player*)unit)->isGMVisible());
#endif
}
