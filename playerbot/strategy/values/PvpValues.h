// 策略值头文件：PvpValues（战场类型、竞技场类型、战场军官与扛旗手目标）
#pragma once

#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/AiObjectContext.h"

namespace ai
{
    // 手动设置值：保存机器人当前排队或参与的战场类型 ID
    class BgTypeValue : public ManualSetValue<uint32>
    {
    public:
        BgTypeValue(PlayerbotAI* ai) : ManualSetValue<uint32>(ai, 0, "bg type") {}
    };

    // 手动设置值：保存机器人当前参与的竞技场赛制类型
    class ArenaTypeValue : public ManualSetValue<uint32>
    {
    public:
        ArenaTypeValue(PlayerbotAI* ai) : ManualSetValue<uint32>(ai, 0, "arena type") {}
    };

    // 手动设置值：保存机器人在战场中的职责角色（如旗手/支援/进攻）
    class BgRoleValue : public ManualSetValue<uint32>
    {
    public:
        BgRoleValue(PlayerbotAI* ai) : ManualSetValue<uint32>(ai, 0, "bg role") {}
    };

    // 单例值计算器：缓存指定战场类型对应本阵营的全部战场军官坐标数据
    class BgMastersValue : public SingleCalculatedValue<std::list<CreatureDataPair const*>>, public Qualified
    {
    public:
        BgMastersValue(PlayerbotAI* ai) : SingleCalculatedValue<std::list<CreatureDataPair const*>>(ai, "bg masters"), Qualified() {}
        virtual std::list<CreatureDataPair const*> Calculate() override;
    };

    // 值计算器：寻找距离机器人最近且安全的己方阵营战场军官
    class BgMasterValue : public CDPairCalculatedValue, public Qualified
    {
    public:
        BgMasterValue(PlayerbotAI* ai) : CDPairCalculatedValue(ai, "bg master", 60), Qualified() {}
        virtual CreatureDataPair const* Calculate() override;
        virtual CreatureDataPair const* NearestBm(bool allowDead = true);
    };

    // 值计算器：为当前未排队的机器人随机挑选一个可用的战场类型
    class RpgBgTypeValue : public CalculatedValue<BattleGroundTypeId>
    {
    public:
        RpgBgTypeValue(PlayerbotAI* ai) : CalculatedValue(ai, "rpg bg type") {}

        virtual BattleGroundTypeId Calculate() override;
    };

    // 目标值计算器：获取战歌峡谷或风暴之眼当前战场旗帜持有者的 GUID
    class FlagCarrierValue : public UnitCalculatedValue
    {
    public:
        FlagCarrierValue(PlayerbotAI* ai, bool sameTeam = false, bool ignoreRange = false) :
            UnitCalculatedValue(ai), sameTeam(sameTeam), ignoreRange(ignoreRange) {}

        virtual ObjectGuid Calculate() override;

    private:
        bool sameTeam;
        bool ignoreRange;
    };
}
