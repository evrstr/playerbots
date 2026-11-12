/// 测试命令：清理测试小队与生成机器人头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // CleanupParty - cleanup spawned bots/party | 清理测试机器人与队伍
    // =====================================================
    /// 测试组件：清理测试期间生成的所有机器人并解散测试小队
    class CleanupParty : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "cleanup"; }
    };
}