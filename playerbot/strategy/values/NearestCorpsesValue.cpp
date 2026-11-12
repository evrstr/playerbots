// 策略值实现：NearestCorpsesValue（网格搜索附近已死亡单位）

#include "playerbot/playerbot.h"
#include "NearestCorpsesValue.h"

#include "playerbot/ServerFacade.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;
using namespace MaNGOS;

// 网格搜索过滤器：匹配距离内所有非存活状态的 Unit 对象
class AnyDeadUnitInObjectRangeCheck
{
public:
    AnyDeadUnitInObjectRangeCheck(WorldObject const* obj, float range) : i_obj(obj), i_range(range) {}
    WorldObject const& GetFocusObject() const { return *i_obj; }
    bool operator()(Unit* u)
    {
        return !sServerFacade.IsAlive(u) && i_obj->IsWithinDistInMap(u, i_range);
    }
private:
    WorldObject const* i_obj;
    float i_range;
};

// 使用 AnyDeadUnitInObjectRangeCheck 扫描周围死亡单位
void NearestCorpsesValue::FindUnits(std::list<Unit*> &targets)
{
    AnyDeadUnitInObjectRangeCheck u_check(bot,  range);
    UnitListSearcher<AnyDeadUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

// 默认接受所有找到的死亡单位
bool NearestCorpsesValue::AcceptUnit(Unit* unit)
{
    return true;
}
