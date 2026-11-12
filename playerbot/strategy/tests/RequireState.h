/// 测试前置条件：角色职业/状态与装备要求头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    /// 测试组件：校验测试执行机器人是否符合指定的职业、等级、阵营或形态条件
    class RequireBotIs : public TestRequire
    {
    public:
        virtual TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "require bot is"; }
    };

    /// 测试组件：校验测试执行机器人是否已穿戴符合要求的装备
    class RequireEquip : public TestRequire
    {
    public:
        virtual TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "require equip"; }
    };
}