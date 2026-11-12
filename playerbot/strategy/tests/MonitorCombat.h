/// 测试监听器：战斗相关状态断言头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // MonitorCombat - combat-related monitors | 战斗相关监听器
    // =====================================================
    /// 测试组件：监控机器人生命值百分比是否满足比较条件
    class MonitorCombatHp : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "hp"; }
    };

    /// 测试组件：监控机器人是否脱离战斗状态
    class MonitorNotInCombat : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "not in combat"; }
    };

    /// 测试组件：监控指定生物的状态（存活/死亡/血量）
    class MonitorCombatMob : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "mob"; }
    };

    /// 测试组件：监控指定生物是否在重生/归位点附近
    class MonitorCombatMobHome : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "mob"; }
    };

    /// 测试组件：监控测试小队是否发生团灭
    class MonitorCombatPartyWiped : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "party wiped"; }
    };

    /// 测试组件：累计统计测试过程中击杀的怪物尸体数量
    class MonitorCombatDeadMobs : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "dead mobs"; }
    };

    /// 测试组件：监控全队累计获得的经验值增量
    class MonitorCombatPartyXp : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "party xp"; }
    };
}