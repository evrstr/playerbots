/// 测试框架基础组件接口（TextComponent / TestMonitor / TestCommand）头文件
#pragma once

#include <string>
#include "TestContext.h"

class Player;
class PlayerbotAI;

namespace ai
{
    class TestContext;

    // Summed XP total (level floor + current XP) over all in-world group members, or just the bot | 统计处于游戏世界中所有小队成员的总经验值（当前等级基础经验 + 当前经验）；未组队时仅算自身
    // when ungrouped. Monotonic per member; callers measure the delta against a captured baseline. | 每个成员单调递增；调用方通过与基线差值计算经验增长量
    uint32 GetPartyXpTotal(Player* bot);

    /// 测试文本组件基类：提供命令与监控表达式的前缀匹配及严格参数解析工具
    class TextComponent
    {
    public:
        virtual bool Matches(const std::string& monitorStr) const { return monitorStr.find(GetName()) == 0; }
        uint32 GetNameSize() const { return GetName().size() + 1; }
    protected:
        static TestResult TrySplitOnce(const std::string& input, const std::string& delimiter,
            std::string& left, std::string& right, std::string& message,
            const std::string& componentName, bool allowEmptyRight = false);
        static TestResult TryExtractBetween(const std::string& input, const std::string& beginDelimiter,
            const std::string& endDelimiter, std::string& value, std::string& message,
            const std::string& componentName);
        static TestResult TryParseComparisonValue(const std::string& input, std::string& valueName, std::string& op, std::string& valueToCompareTo,
            std::string& message, const std::string& componentName);
        static TestResult TryParseUInt32Strict(const std::string& input, uint32& outValue,
            std::string& message, const std::string& componentName);
        static TestResult TryParseUInt64Strict(const std::string& input, uint64& outValue,
            std::string& message, const std::string& componentName);
        static TestResult TryParseFloatStrict(const std::string& input, float& outValue,
            std::string& message, const std::string& componentName);
        virtual std::string GetName() const = 0;
    };

    /// 测试监听器基类：定义条件检查接口，返回 PASS / FAIL / PENDING
    class TestMonitor : public TextComponent
    {
    public:
        virtual TestResult Check(const std::string& monitorStr, Player* bot, TestContext& ctx, std::string& message) const;
    protected:
        virtual bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const = 0;
    };

    /// 测试命令基类：定义测试步骤执行接口
    class TestCommand : public TextComponent
    {
    public:
        virtual TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) = 0;
    };

    /// 测试前置需求命令基类：校验环境或角色要求，不满足时返回 IMPOSSIBLE / ABORT
    class TestRequire : public TestCommand
    {
    public:
    };

    /// 测试清理命令基类：测试结束后执行的资源回收命令
    class TestCleanup : public TestCommand
    {
    public:
    };
}