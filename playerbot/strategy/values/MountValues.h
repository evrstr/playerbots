// 策略值头文件：MountValues（坐骑速度解析、坐骑列表、骑术等级与购买/学习条件）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 坐骑封装类：统一表示坐骑物品或法术，提供地面/飞行速度计算及当前区域合法性检查
    class MountValue
    {
    public:
        MountValue(uint32 spellId) : spellId(spellId) {};
        MountValue(const ItemPrototype* proto) : proto(proto) { spellId = GetMountSpell(proto->ItemId); };
        MountValue(Item* item) { spellId = GetMountSpell(item->GetProto()->ItemId); proto = item->GetProto(); };
        MountValue(const MountValue& mount) : spellId(mount.spellId), proto(mount.proto) {};

        bool IsItem() { return proto; }
        const ItemPrototype* GetItemProto() { return proto; }
        uint32 GetSpellId() { return spellId; }
        uint32 GetSpeed(bool canFly) { return GetSpeed(spellId, canFly); }
        static uint32 IsMountSpell(uint32 spellId) { return GetSpeed(spellId, false) || GetSpeed(spellId, true); }
        static uint32 GetSpeed(uint32 spellId, bool canFly);
        static uint32 GetSpeed(uint32 spellId) { return std::max(GetSpeed(spellId, false), GetSpeed(spellId, true)); };
        static uint32 GetMountSpell(uint32 itemId);
        bool IsValidLocation(Player* bot);

    private:
        const ItemPrototype* proto = nullptr;
        uint32 spellId = 0;
    };

    // 值计算器：查询指定目标当前处于骑乘状态时的移动速度加成百分比
    class CurrentMountSpeedValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        CurrentMountSpeedValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "current mount speed", 1), Qualified() {}
        virtual uint32 Calculate() override;
    };

    // 单例值计算器：收集全游戏所有合法坐骑物品及坐骑法术清单
    class FullMountListValue : public SingleCalculatedValue<std::vector<MountValue>>
    {
    public:
        FullMountListValue(PlayerbotAI* ai) : SingleCalculatedValue<std::vector<MountValue>>(ai, "full mount list") {}
        virtual std::vector<MountValue> Calculate() override;
    };

    // 值计算器：列出机器人背包内及已学会的所有可用坐骑
    class MountListValue : public CalculatedValue<std::vector<MountValue>>
    {
    public:
        MountListValue(PlayerbotAI* ai) : CalculatedValue<std::vector<MountValue>>(ai, "mount list", 10) {}
        virtual std::vector<MountValue> Calculate() override;
        virtual std::string Format() override;
    };   

    // 值计算器：计算机器人当前拥有坐骑所能提供的最高地面或飞行速度
    class MaxMountSpeedValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        MaxMountSpeedValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "max mount speed", 1), Qualified() {}
        virtual uint32 Calculate() override;
    };

    // 值计算器：根据地图和等级判断机器人当前可学或最高所需的骑术等级
    class MountSkillTypeValue : public CalculatedValue<uint32>
    {
    public:
        MountSkillTypeValue(PlayerbotAI* ai) : CalculatedValue<uint32>(ai, "mount skilltype", 10) {}

        virtual uint32 Calculate() override;
    };

    // 值计算器：列出销售适合当前机器人购买升级坐骑的商人 Entry 列表
    class AvailableMountVendors : public CalculatedValue<std::vector<int32>>
    {
    public:
        AvailableMountVendors(PlayerbotAI* ai) : CalculatedValue<std::vector<int32>>(ai, "available mount vendors", 10) {}

        virtual std::vector<int32> Calculate() override;
    };

    // 布尔值计算器：判断机器人是否有足够资金及条件前往训练师学习更高级骑术
    class CanTrainMountValue : public BoolCalculatedValue
    { 
    public:
        CanTrainMountValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can train mount", 10) {}

        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断机器人是否满足资金、背包条件并需要购买更好的坐骑
    class CanBuyMountValue : public BoolCalculatedValue
    {
    public:
        CanBuyMountValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can buy mount", 10) {}

        virtual bool Calculate() override;
    };
}
