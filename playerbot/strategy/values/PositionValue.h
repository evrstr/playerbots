// 策略值头文件：PositionValue（坐标点存储、当前位置历史、主控位置与自定义标记点）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 命名坐标点结构：保存地图 ID 与三维坐标及是否已设置标记
    class PositionEntry
    {
    public:
        PositionEntry() : valueSet(false), x(0), y(0), z(0), mapId(0) {}
        PositionEntry(float x, float y, float z, uint32 mapId, bool valueSet = true) : valueSet(valueSet), x(x), y(y), z(z), mapId(mapId) {}
        PositionEntry(const PositionEntry& other) : valueSet(other.valueSet), x(other.x), y(other.y), z(other.z), mapId(other.mapId) {}
        PositionEntry(const WorldPosition& pos) : valueSet(pos), x(pos.coord_x), y(pos.coord_y), z(pos.coord_z), mapId(pos.mapid) {}
        void Set(float x, float y, float z, uint32 mapId) { this->x = x; this->y = y; this->z = z; this->mapId = mapId; this->valueSet = true; }
        void Set(WorldPosition pos) { this->x = pos.coord_x; this->y = pos.coord_y; this->z = pos.coord_z; this->mapId = pos.mapid; this->valueSet = true; }
        WorldPosition Get() { return WorldPosition(mapId, x, y, z); }
        void Reset() { valueSet = false; }
        bool isSet() { return valueSet; }

    public:
        float x, y, z;
        bool valueSet;
        uint32 mapId;
    };

    typedef std::map<std::string, PositionEntry> PositionMap;

    // 手动设置值：管理机器人保存的命名坐标字典，支持存档读取
    class PositionValue : public ManualSetValue<PositionMap&>
    {
    public:
        PositionValue(PlayerbotAI* ai, std::string name = "position");
        virtual std::string Save() override;
        virtual bool Load(std::string value) override;

    private:
        PositionMap positions;
    };

    // 位置计算器：读取/设置/重置指定名称的单个坐标点（如拉怪点/集合点）
    class SinglePositionValue : public CalculatedValue<PositionEntry>, public Qualified
    {
    public: 
        SinglePositionValue(PlayerbotAI* ai, std::string name = "pos") : CalculatedValue(ai, name), Qualified() {};
        virtual PositionEntry Calculate() override;
        virtual void Set(PositionEntry value) override;
        virtual void Reset() override;
    };

    // 日志位置计算器：定期记录机器人当前世界坐标位置
    class CurrentPositionValue : public LogCalculatedValue<WorldPosition>
    {
    public:
        CurrentPositionValue(PlayerbotAI* ai, std::string name = "current position", uint32 checkInterval = 1) : LogCalculatedValue<WorldPosition>(ai, name, checkInterval) { minChangeInterval = 60;  logLength = 30; };
        virtual bool EqualToLast(WorldPosition value) override { return value.fDist(lastValue) < sPlayerbotAIConfig.tooCloseDistance; }
        virtual WorldPosition Calculate() override { return WorldPosition(bot); };
    };  

    // 记忆位置计算器：记录并返回主控玩家最近的世界坐标
    class MasterPositionValue : public MemoryCalculatedValue<WorldPosition>
    {
    public:
        MasterPositionValue(PlayerbotAI* ai, std::string name = "master position", uint32 checkInterval = 1) : MemoryCalculatedValue<WorldPosition>(ai, name, checkInterval) { minChangeInterval = 1; };
        virtual bool EqualToLast(WorldPosition value) override { return value.fDist(lastValue) < sPlayerbotAIConfig.proximityDistance; }
        virtual WorldPosition Calculate() override { Player* master = GetMaster();  if (master) return WorldPosition(master); return WorldPosition(); };
    };

    // 手动设置值：存储支持限定符的自定义世界坐标
    class CustomPositionValue : public ManualSetValue<WorldPosition>, public Qualified
    {
    public:
        CustomPositionValue(PlayerbotAI* ai, std::string name = "custom position") : ManualSetValue<WorldPosition>(ai, WorldPosition(), name), Qualified() { };
        virtual WorldPosition Calculate() { return WorldPosition(bot); };
    };
}
