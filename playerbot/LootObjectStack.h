#pragma once
#include "playerbot.h"

namespace ai
{
    class ItemQualifier;

    /// 可拾取目标对象描述类（尸体、剥皮、草药/矿点/宝箱及所需技能/钥匙信息）
    class LootObject
    {
    public:
        LootObject() : skillId(0), reqSkillValue(0), reqItem(0) {}
        LootObject(Player* bot, ObjectGuid guid);
        LootObject(const LootObject& other);

    public:
        bool IsEmpty() { return !guid; }
        bool IsLootPossible(Player* bot);
        void Refresh(Player* bot, ObjectGuid guid, bool debug = false);
        WorldObject* GetWorldObject(Player* bot);
        ObjectGuid guid;

        uint32 skillId;
        uint32 reqSkillValue;
        uint32 reqItem;
    };

    /// 拾取目标集合元素，记录目标 GUID 与加入时间
    class LootTarget
    {
    public:
        LootTarget(ObjectGuid guid);
        LootTarget(LootTarget const& other);

    public:
        LootTarget& operator=(LootTarget const& other);
        bool operator< (const LootTarget& other) const;

    public:
        ObjectGuid guid;
        time_t asOfTime;
    };

    /// 带过期清理功能的拾取目标集合
    class LootTargetList : public std::set<LootTarget>
    {
    public:
        void shrink(time_t fromTime);
    };

    /// 机器人可拾取目标栈管理器，按距离排序并返回最近可拾取对象
    class LootObjectStack
    {
    public:
        LootObjectStack(Player* bot) : bot(bot) {}

    public:
        bool Add(ObjectGuid guid);
        void Remove(ObjectGuid guid);
        void Clear();
        bool CanLoot(float maxDistance);
        LootObject GetLoot(float maxDistance = 0);

    private:
        std::vector<LootObject> OrderByDistance(float maxDistance = 0);

    private:
        Player* bot;
        LootTargetList availableLoot;
    };

};
