// 策略值头文件：NearestGameObjects（附近游戏对象与动态法术对象列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 视线检查模式枚举（忽略视线、仅忽略忽略视线标志的对象、完整视线检查）
    enum LineOfSight
    {
        LOS_IGNORE = 0,
        LOS_STATIC = 1,
        LOS_FULL   = 2,
    };

    // 网格搜索过滤器：匹配范围内已刷新且在视野距离内的任意游戏对象
    class AnyGameObjectInObjectRangeCheck
    {
    public:
        AnyGameObjectInObjectRangeCheck(WorldObject const* obj, float range) : i_obj(obj), i_range(range) {}
        WorldObject const& GetFocusObject() const { return *i_obj; }
        bool operator()(GameObject* u);
    private:
        WorldObject const* i_obj;
        float i_range;
    };

    // 网格搜索过滤器：按距离和可选 IgnoreLos 标志筛选游戏对象
    class GameObjectsInObjectRangeCheck
    {
    public:
        GameObjectsInObjectRangeCheck(WorldObject const* obj, float range, uint32 gameObjectID) : i_obj(obj), i_range(range), i_gameObjectID(gameObjectID) {}
        WorldObject const& GetFocusObject() const { return *i_obj; }
        bool operator()(GameObject* u);
    private:
        WorldObject const* i_obj;
        float i_range;
        uint32 i_gameObjectID;
    };

    // 对象列表计算器：获取周围可见或满足视线要求的游戏对象 GUID 列表
    class NearestGameObjects : public ObjectGuidListCalculatedValue, public Qualified
    {
    public:
        NearestGameObjects(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance, LineOfSight lineOfSight = LOS_FULL, std::string name = "nearest game objects") :
            ObjectGuidListCalculatedValue(ai, name), range(range), lineOfSight(lineOfSight), Qualified() {}

    protected:
        virtual std::list<ObjectGuid> Calculate() override;

    private:
        float range;
        LineOfSight lineOfSight;
    };

    // 对象列表计算器：获取周围地面动态法术对象（如陷阱、区域法术）GUID 列表
    class NearestDynamicObjects : public ObjectGuidListCalculatedValue
    {
    public:
        NearestDynamicObjects(PlayerbotAI* ai, float range = sPlayerbotAIConfig.farDistance, LineOfSight lineOfSight = LOS_FULL, std::string name = "nearest dynamic objects") :
            ObjectGuidListCalculatedValue(ai, name), range(range), lineOfSight(lineOfSight) {}

    protected:
        virtual std::list<ObjectGuid> Calculate() override;

    private:
        float range;
        LineOfSight lineOfSight;
    };
}
