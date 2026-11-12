/// 测试命令：记录外发消息命令头文件
#pragma once
#include "TestComponent.h"

namespace ai
{
    /// 测试组件：开启或快照记录机器人对外发送的聊天/系统消息
    class CommandRecordMessages : public TestCommand
    {
    public:
        std::string GetName() const override { return "record messages"; }
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    };
}
