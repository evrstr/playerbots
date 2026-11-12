/// 测试命令：组队与机器人生成管理命令头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // CommandParty - party management commands | 队伍管理测试命令
    // =====================================================
    /// 测试组件：在测试现场生成一个指定职业/专精的辅助机器人
    class CommandPartySpawnBot : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "spawn"; }
    };

    /// 测试组件：销毁或下线已生成的测试机器人
    class CommandPartyDespawnBot : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "despawn"; }
    };

    /// 测试组件：将测试机器人与已生成机器人组成小队或团队
    class CommandPartyForm : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "form"; }
    };

    /// 测试组件：批量生成一组预设配置的小队机器人
    class CommandPartySpawnGroup : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "mgroup"; }
    };
}