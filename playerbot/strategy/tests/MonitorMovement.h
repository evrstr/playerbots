/// 测试监听器：移动、距离与寻路断言头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // MonitorMovement - movement-related monitors | 移动相关监听器
    // =====================================================
    /// 测试组件：监控机器人与目标点之间的距离是否满足条件
    class MonitorMovementDistance : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "distance to"; }
    };

    /// 测试组件：监控机器人是否处于指定地图之外
    class MonitorNotOnMap : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "not on map"; }
    };

    /// 测试组件：监控机器人是否掉入地下（Z 轴异常穿模检测）
    class MonitorMovementUnderground : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "underground"; }
    };

    /// 测试组件：监控机器人是否连续多帧无法寻路至节点
    class MonitorMovementCanNotReachNodes : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "can not reach nodes"; }
    };

    /// 测试组件：监控机器人移动速度是否符合预期
    class MonitorMovementSpeed : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "speed"; }
    };

    /// 测试组件：监控生成机器人与主角机器人之间的距离
    class MonitorMovementSpawnDistance : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "spawn distance"; }
    };
}