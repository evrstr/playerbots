#include "WorldSquare.h"
#include "TravelMgr.h"


using namespace ai;
// 以 WKT 格式输出点或包围盒多边形用于可视化调试
void WorldPointContainer::printWKT(std::ostringstream& out, bool squares) const
{
    if (!squares)
    {
        for (auto& p : points)
            out << p->getDisplayX() << " " << p->getDisplayY() << ",";
    }
    {
        for (auto& p : GetSquare())
            out << p.getDisplayX() << " " << p.getDisplayY() << ",";
    }
}

// 计算目标点到地图包围盒的距离平方（跨地图时经由传送点中转估算）
float MapWpSquare::sqOutDistance(const WorldPosition& point) const
{
    if (point.mapid != mapId)
    {
        float minSqDist = FLT_MAX;
        //distance = point -> portal (on map of square)
        for (auto& [portal, distance] : sTravelMgr.sqMapTransDistances(point, mapId))
        {
            float sqDist = distance + sqDistance(portal); //Add sqDistance = portal -> square.
            if (sqDist < minSqDist)
                minSqDist = sqDist;
        }

        return minSqDist;
    }

    return WorldPointSquareContainer::sqOutDistance(point);
}

// 查找距离目标点最近的地图 ID
uint32 WorldWpSquare::ClosestMapId(const WorldPosition& point) const
{
    uint32 closetMapId = 999;
    float minsqDistance = FLT_MAX;
    for (auto& mapId : GetSubSquareIds())
    {
        float sqDistance = GetSubSquare(mapId).sqDistance(point);

        if (sqDistance < minsqDistance)
        {
            closetMapId = mapId;
            minsqDistance = sqDistance;
        }
    }

    return closetMapId;
}
