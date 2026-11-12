// 策略值头文件：GroupValues（队伍成员列表、跟随状态与全队就绪判定）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标列表计算器：获取当前小队或团队的所有玩家成员 GUID（含自身）
    class GroupMembersValue : public ObjectGuidListCalculatedValue
    {
    public:
        GroupMembersValue(PlayerbotAI* ai) : ObjectGuidListCalculatedValue(ai, "group members",2) {}
        virtual std::list<ObjectGuid> Calculate() override;
    };

    // 布尔值计算器：判断机器人当前是否处于跟随队伍或漫游状态
    class IsFollowingPartyValue : public BoolCalculatedValue
    {
    public:
        IsFollowingPartyValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "following party") {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断机器人是否在队长或主控的跟随范围内
    class IsNearLeaderValue : public BoolCalculatedValue
    {
    public:
        IsNearLeaderValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "near leader") {}
        virtual bool Calculate() override;
    };

    // 数值计算器：统计队伍中满足指定布尔 AI 值的成员人数
    class GroupBoolCountValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        GroupBoolCountValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "group count"), Qualified() {}
        virtual uint32 Calculate() override;
    };
    
    // 布尔值计算器：判断队伍中所有成员是否全部满足指定布尔 AI 值（逻辑与）
    class GroupBoolANDValue : public BoolCalculatedValue, public Qualified
    {
    public:
        GroupBoolANDValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "group bool and"), Qualified() {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断队伍中是否至少有一名成员满足指定布尔 AI 值（逻辑或）
    class GroupBoolORValue : public BoolCalculatedValue, public Qualified
    {
    public:
        GroupBoolORValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "group bool or"), Qualified() {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：检查范围内跟随队友是否均已存活且恢复至安全血蓝状态
    class GroupReadyValue : public BoolCalculatedValue, public Qualified
    {
    public:
        GroupReadyValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "group ready", 2), Qualified() {}
        virtual bool Calculate() override;
    };
}
