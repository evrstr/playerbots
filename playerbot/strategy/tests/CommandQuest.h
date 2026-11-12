/// 测试命令：任务状态配置与通用聊天命令执行头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // CommandQuest - quest setup commands for tests | 测试用任务状态设置命令
    // =====================================================

    // "accept quest <id>" - Force-accept a quest by ID | 按任务 ID 强制接取任务
    /// 测试组件：强制使机器人接取指定 ID 的任务
    class CommandSetupAcceptQuest : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "accept quest"; }
    };

    // "complete quest <id>" - Force-complete all objectives of a quest (like AutoComplete) | 强制完成任务全部目标（类似 AutoComplete）
    /// 测试组件：强制完成指定任务的所有目标条件
    class CommandSetupForceCompleteQuest : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "complete quest"; }
    };

    // "reward quest <id>" - Force-reward a quest (complete + reward, skipping turn-in) | 强制结算任务奖励（完成并领奖，跳过交任务步骤）
    /// 测试组件：强制直接结算任务奖励（跳过交付流程）
    class CommandSetupRewardQuest : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "reward quest"; }
    };

    // "force objectives <id> except <objIndex>" - Force-complete all objectives of an active quest | 强制完成指定任务除 objIndex 之外的全部目标
    // except the given one (used by the quest-clear test flavor so a single objective can be tested | （用于任务清理类测试，以便单独验证某一特定目标）；
    // in isolation). objIndex must parse as a number ('' empties to: satisfy every objective). | objIndex 须解析为数字（空值表示满足所有目标）。
    /// 测试组件：强制完成除指定索引外的所有任务目标，用于隔离测试单一目标
    class CommandSetupForceObjectives : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "force objectives"; }
    };

    // "do <chatcommand>" - Execute any bot chat command | 执行任意机器人聊天控制指令
    /// 测试组件：以聊天指令方式直接触发机器人 AI 动作
    class CommandSetupDo : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "do"; }
    };
}
