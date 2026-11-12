/// 测试命令：调试开关与录像回放命令头文件
#pragma once
#include "TestComponent.h"

namespace ai
{
    /// 测试组件：开启或关闭测试上下文详细调试日志输出
    class CommandDebug : public TestCommand
    {
    public:
        std::string GetName() const override { return "debug"; }
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    };

    /// 测试组件：录制机器人状态/动作序列至测试文件
    class CommandRecord : public TestCommand
    {
    public:
        std::string GetName() const override { return "record"; }
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    };

    /// 测试组件：读取并加载录制的测试脚本数据
    class CommandRead : public TestCommand
    {
    public:
        std::string GetName() const override { return "read"; }
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    };
}
