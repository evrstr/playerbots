/// 测试命令：测试脚本流程控制命令头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // CommandFlow - flow control commands | 流程控制命令
    // =====================================================
    /// 测试组件：进入观察模式（Observe），持续监控条件直至通过、失败或超时
    class CommandFlowObserve : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "observe"; }
    };

    /// 测试组件：检查脚本前置条件是否满足
    class CommandFlowPreconditions : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "preconditions"; }
    };

    /// 测试组件：向测试上下文注册一个持续性状态监听器（Monitor）
    class CommandFlowMonitor : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "monitor"; }
    };

    /// 测试组件：等待指定的秒数后再继续执行后续脚本
    class CommandFlowWait : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        // Scripts are written as "wait <seconds>". Registered AFTER CommandFlowWaitDestination so | 脚本格式为 "wait <seconds>"；注册在 CommandFlowWaitDestination 之后，
        // that "wait destination <n>" still resolves to the destination variant. | 以确保 "wait destination <n>" 优先匹配目的地等待变体。
        std::string GetName() const override { return "wait"; }
    };

    /// 测试组件：等待机器人抵达预设的移动目的地
    class CommandFlowWaitDestination : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "wait destination"; }
    };

    /// 测试组件：等待所有生成的队友机器人集结或完成就绪
    class CommandFlowWaitGroup : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "wait group"; }
    };

    /// 测试组件：重复执行前面的脚本命令序列
    class CommandFlowRepeat : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "repeat"; }
    };
}