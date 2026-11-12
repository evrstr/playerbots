/// 测试监听器：通用状态与行为异常断言头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // MonitorState - bot state monitors | 机器人状态监听器
    // =====================================================
    /// 测试组件：监控观测经过的时间是否达到设定值
    class MonitorStateTime : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "time"; }
    };

    /// 测试组件：监控机器人是否死亡
    class MonitorStateDead : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "bot dead"; }
    };

    /// 测试组件：监控机器人所属阵营
    class MonitorStateFaction : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "faction"; }
    };

    /// 测试组件：监控当前小队成员人数
    class MonitorStateGroupSize : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "group size"; }
    };

    /// 测试组件：监控小队成员是否已全部抵达当前地图
    class MonitorStateGroupOnMap : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "group on map"; }
    };

    /// 测试组件：监控机器人当前拾取目标 GUID 状态
    class MonitorStateLootGuid : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "loot guid"; }
    };

    /// 测试组件：监控新手初始装备数量
    class MonitorStateStarterGearCount : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "starter gear count"; }
    };

    /// 测试组件：监控已穿戴装备栏位数量
    class MonitorStateEquippedCount : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "equipped count"; }
    };

    /// 测试组件：监控已穿戴装备的品质等级
    class MonitorStateEquipQuality : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "equip quality"; }
    };

    /// 测试组件：监控机器人等级与当前所在区域等级的差值
    class MonitorStateAreaLevelDiff : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "area level diff"; }
    };

    /// 测试组件：监控任意指定 AI Value 的值是否符合比较表达式
    class MonitorAiValue : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "value"; }
    };

    /// 测试组件：断言拾取对象栈（Loot Stack）未出现意外阻塞或滞留
    class MonitorStateLootStackNever : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "loot stack"; }
    };

    /// 测试组件：断言未发生同动作短时间高频刷屏（Action Spam）
    class MonitorStateActionSpam : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "action spam"; }
    };

    /// 测试组件：监控机器人是否发出了预期内容的聊天/系统消息
    class MonitorOutgoingMessage : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "outgoing message"; }
    };
} // namespace ai