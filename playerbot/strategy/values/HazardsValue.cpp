// 策略值实现：HazardsValue（危险区域生命周期管理、坐标解析与过期清理）

#include "playerbot/playerbot.h"
#include "HazardsValue.h"
#include "playerbot/strategy/AiObjectContext.h"
#include "MotionGenerators/PathFinder.h"

using namespace ai;

// 默认构造函数：初始化无效的危险区域对象
Hazard::Hazard()
: position(WorldPosition())
, expirationTime(0)
, guid(ObjectGuid())
, radius(0.0f)
, hazardNavmeshArea(0)
, previousNavmeshArea(0)
{

}

// 构造函数：创建基于固定世界坐标的危险区域
Hazard::Hazard(const WorldPosition& inPosition, uint64 inExpiration, float inRadius)
: position(inPosition)
, expirationTime(time(0) + inExpiration)
, guid(ObjectGuid())
, radius(inRadius)
, hazardNavmeshArea(14)
, previousNavmeshArea(11)
{

}

// 构造函数：创建追踪指定世界对象 GUID 的危险区域
Hazard::Hazard(const ObjectGuid& inGuid, uint64 inExpiration, float inRadius)
: position(WorldPosition())
, expirationTime(time(0) + inExpiration)
, guid(inGuid)
, radius(inRadius)
, hazardNavmeshArea(14)
, previousNavmeshArea(11)
{

}

// 比较两个危险区域是否指向同一位置或同一对象
bool Hazard::operator==(const Hazard& other) const
{
    if (!guid.IsEmpty())
    {
        return (guid == other.guid);
    }
    else if (position)
    {
        return position == other.position;
    }

    return false;
}

// 按过期时间先后排序危险区域
bool Hazard::operator<(const Hazard& other) const
{
    return radius < other.radius;
}

// 解析并返回危险区域当前所在的世界坐标（支持动态对象实时追踪）
bool Hazard::GetPosition(PlayerbotAI* ai, WorldPosition& outPosition)
{
    const WorldObject* object = GetObject(ai);
    if (object)
    {
        outPosition = position = WorldPosition(object);
        return true;
    }
    else if(position)
    {
        outPosition = position;
        return true;
    }

    return false;
}

// 检查危险区域是否已超过预设的持续时间
bool Hazard::IsExpired() const
{
    return time(0) > expirationTime;
}

// 检查危险区域是否未过期且在当前地图有效
bool Hazard::IsValid(PlayerbotAI* ai) const
{
    const WorldObject* object = GetObject(ai);
    return (object || position) && !IsExpired();
}

// 根据 GUID 从机器人所在地图获取对应生物或动态对象
const WorldObject* Hazard::GetObject(PlayerbotAI* ai) const
{
    if (!guid.IsEmpty())
    {
        if (guid.IsUnit())
        {
            return ai->GetUnit(guid);
        }
        else if (guid.IsGameObject())
        {
            return ai->GetGameObject(guid);
        }
    }

    return nullptr;
}

// 将新危险区域去重加入 stored hazards 缓存列表
void AddHazardValue::Set(Hazard hazard)
{
    AiObjectContext* context = ai->GetAiObjectContext();
    std::list<Hazard> storedHazards = AI_VALUE(std::list<Hazard>, "stored hazards");

    // Check if the hazard already exists | 检查该危险区域是否已存在于缓存中
    auto it = std::find(storedHazards.begin(), storedHazards.end(), hazard);
    if (it == storedHazards.end())
    {
        storedHazards.emplace_back(std::move(hazard));
        SET_AI_VALUE(std::list<Hazard>, "stored hazards", storedHazards);
    }
}

// 遍历并刷新 stored hazards，剔除失效项后返回有效危险坐标列表
std::list<HazardPosition> HazardsValue::Calculate()
{
    AiObjectContext* context = ai->GetAiObjectContext();
    std::list<Hazard> storedHazards = AI_VALUE(std::list<Hazard>, "stored hazards");

    // Create an updated hazard positions list | 构建最新的有效危险位置列表
    bool hazardsUpdated = false;
    std::list<HazardPosition> hazards;
    for (auto it = storedHazards.begin(); it != storedHazards.end();)
    {
        // Check if the hazard is valid | 校验危险区域是否仍然有效
        bool validHazard = false;
        Hazard& hazard = (*it);
        if (hazard.IsValid(ai))
        {
            // Try to retrieve the hazard position | 尝试获取危险区域的实时坐标
            WorldPosition hazardPosition;
            if (hazard.GetPosition(ai, hazardPosition))
            {
                hazards.emplace_back(std::make_pair(hazardPosition, hazard.GetRadius()));
                validHazard = true;
            }
        }

        // Remove the invalid hazards | 从缓存中移除已失效的危险区域
        if (!validHazard)
        {
            it = storedHazards.erase(it);
            hazardsUpdated = true;
        }
        else
        {
            ++it;
        }
    }

    if (hazardsUpdated)
    {
        SET_AI_VALUE(std::list<Hazard>, "stored hazards", storedHazards);
    }

    return hazards;
}