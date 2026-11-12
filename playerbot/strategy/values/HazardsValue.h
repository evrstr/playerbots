// 策略值头文件：HazardsValue（危险区域记录与实时避险位置列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/WorldPosition.h"

namespace ai
{
    // 危险区域对象：支持静态坐标或动态对象 GUID 绑定，包含失效时间戳与危险半径
    class Hazard
    {
    public:
        Hazard();
        Hazard(const WorldPosition& position, uint64 expiration, float radius);
        Hazard(const ObjectGuid& guid, uint64 expiration, float radius);
        bool operator==(const Hazard& other) const;
        bool operator<(const Hazard& other) const;

        bool GetPosition(PlayerbotAI* ai, WorldPosition& outPosition);
        float GetRadius() const { return radius; }

        bool IsValid(PlayerbotAI* ai) const;
        bool IsExpired() const;

        uint32 GetNavmeshArea() const { return hazardNavmeshArea; }
        uint32 GetPreviousNavmeshArea() const { return previousNavmeshArea; }

    private:
        const WorldObject* GetObject(PlayerbotAI* ai) const;

    private:
        WorldPosition position;
        time_t expirationTime;
        ObjectGuid guid;
        float radius;

        uint32 hazardNavmeshArea;
        uint32 previousNavmeshArea;
    };

    // Hazard position, Hazard radius | 危险区域坐标与危险半径
    // 危险区域坐标与半径对（位置, 半径）
    typedef std::pair<WorldPosition, float> HazardPosition;

    // DO NOT USE. Value to store hazards which the bot must avoid when moving around | 请勿直接使用；用于底层存储移动时需躲避的危险区域
    // 手动设置值：内部存储尚未清理的危险区域列表（请勿直接使用，改用 hazards）
    class StoredHazardsValue : public ManualSetValue<std::list<Hazard>>
    {
    public:
        StoredHazardsValue(PlayerbotAI* ai, std::string name = "stored hazards") : ManualSetValue<std::list<Hazard>>(ai, {}, name) {}
    };

    // Value to add hazards which the bot must avoid when moving around | 用于添加机器人移动时需规避的危险区域
    // 手动设置值：重写 Set 方法以向危险区域列表去重添加新的避险目标
    class AddHazardValue : public ManualSetValue<Hazard>
    {
    public:
        AddHazardValue(PlayerbotAI* ai, std::string name = "add hazard") : ManualSetValue<Hazard>(ai, Hazard(), name) {}

    private:
        void Set(Hazard hazard) override;
    };

    // Value to get hazards position and radius which the bot must avoid when moving around | 用于获取机器人移动时需规避的危险位置与半径列表
    // 位置列表计算器：过滤过期/无效危险源并输出当前需要规避的危险位置与半径列表
    class HazardsValue : public CalculatedValue<std::list<HazardPosition>>
    {
    public:
        HazardsValue(PlayerbotAI* ai, std::string name = "hazards") : CalculatedValue<std::list<HazardPosition>>(ai, name, 1) {}

    private:
        std::list<HazardPosition> Calculate() override;
    };
}
