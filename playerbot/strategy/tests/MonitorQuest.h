/// 测试监听器：任务进度与交付状态断言头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // MonitorQuest - quest-related monitors | 任务相关监听器
    // =====================================================

    // "quest <id> complete" => checks QUEST_STATUS_COMPLETE or QUEST_STATUS_REWARDED | 检查任务是否为已完成或已领奖状态
    /// 测试组件：监控指定任务是否处于完成或已领奖状态
    class MonitorQuestComplete : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "quest complete"; }
    };

    // "quest <id> rewarded" => checks QUEST_STATUS_REWARDED only | 仅检查任务是否处于已领奖状态
    /// 测试组件：监控指定任务是否处于已领奖状态
    class MonitorQuestRewarded : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "quest rewarded"; }
    };

    /// 测试组件：监控指定任务是否已成功交付（不再在任务日志中或已标记完成）
    class MonitorQuestTurnedIn : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "quest turnedin"; }
    };

    // "quest <id> active" => checks bot has the quest in log (any non-NONE status) | 检查机器人任务日志中是否持有该任务
    /// 测试组件：监控指定任务是否处于已接取激活状态
    class MonitorQuestActive : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "quest active"; }
    };

    // "quest <id> objective <n> done" => checks a specific quest objective is satisfied | 检查特定任务子目标是否已达成
    /// 测试组件：监控指定任务的某个子目标是否已达成
    class MonitorQuestObjective : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "quest objective"; }
    };

    // "npc dead <location>" => true when the named creature location has no live unit on the bot's map. | 当指定位置生物在机器人地图上无存活单位时返回真
    // Used to abort (not fail) quest tests whose giver/taker died mid-run. | 用于在 NPC 意外死亡时中止（ABORT）而非判定测试失败（FAIL）
    /// 测试组件：监控任务相关 NPC 是否死亡（用于触发测试中止）
    class MonitorNpcDead : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "npc dead"; }
    };

    // "has item <id>" => checks bot has at least one of item | 检查机器人是否持有至少 1 个指定物品
    /// 测试组件：监控机器人背包中是否拥有指定 ID 的物品
    class MonitorHasItem : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "has item"; }
    };

    // "on map <id>" => checks bot is on specific map | 检查机器人当前是否位于指定地图 ID
    /// 测试组件：监控机器人是否位于指定的地图 ID 上
    class MonitorOnMap : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "on map"; }
    };

    // "has mount" => checks bot has a usable mount | 检查机器人是否拥有可用坐骑
    /// 测试组件：监控机器人是否已学会并拥有可用坐骑
    class MonitorHasMount : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "has mount"; }
    };
}
