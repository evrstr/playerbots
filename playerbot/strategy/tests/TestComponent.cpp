/// 测试框架基础组件接口（TextComponent / TestMonitor / TestCommand）实现
#include "TestComponent.h"
#include "playerbot/WorldPosition.h"
#include "playerbot/PlayerbotTextMgr.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <limits>

using namespace ai;

// =====================================================
// TestMonitor implementation | TestMonitor 基类实现
// =====================================================

namespace
{
/// 判断字符串是否仅包含空白字符
    bool IsWhitespaceOnly(const std::string& value)
    {
        return value.find_first_not_of(" \t\r\n") == std::string::npos;
    }

/// 去除字符串首尾空白字符
    std::string Trim(const std::string& value)
    {
        const size_t begin = value.find_first_not_of(" \t\r\n");
        if (begin == std::string::npos)
            return "";

        const size_t end = value.find_last_not_of(" \t\r\n");
        return value.substr(begin, end - begin + 1);
    }

/// 检查 C 字符串指针之后是否仅剩空白字符
    bool HasOnlyTrailingWhitespace(const char* cursor)
    {
        while (*cursor)
        {
            if (*cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                return false;
            ++cursor;
        }

        return true;
    }

/// 统计机器人指定半径范围内死亡生物的数量
    uint32 CountNearbyDeadMobs(Player* bot, float radius)
    {
        std::list<Creature*> creatures;
        // GetDistance(..., DIST_CALC_NONE) returns the SQUARED distance, so the checker range must | DIST_CALC_NONE 使用距离平方判定，因此 checker 半径需平方
        // be squared too; VisitAllObjects keeps the linear radius for the cell visit.
        MaNGOS::AnyUnitFulfillingConditionInRangeCheck checker(bot, [](Unit* u) { return !u->IsAlive(); }, radius * radius, DIST_CALC_NONE);
        MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitFulfillingConditionInRangeCheck> searcher(creatures, checker);
        Cell::VisitAllObjects(bot, searcher, radius);

        uint32 deadCount = 0;
        for (Creature* creature : creatures)
        {
            if (!creature->IsAlive() && !creature->IsPet() && !creature->IsTotem())
                ++deadCount;
        }

        return deadCount;
    }
}

/// 统计全队（或未组队时仅机器人自身）的累计总经验值
uint32 ai::GetPartyXpTotal(Player* bot)
{
    if (!bot || !bot->IsInWorld())
        return 0;

    uint64 total = 0;
    if (Group* group = bot->GetGroup())
    {
        for (auto itr = group->GetMemberSlots().begin(); itr != group->GetMemberSlots().end(); ++itr)
        {
            Player* member = sObjectMgr.GetPlayer(itr->guid);
            if (!member || !member->IsInWorld())
                continue;

            total += sObjectMgr.GetXPForLevel(member->GetLevel()) + member->GetUInt32Value(PLAYER_XP);
        }
    }
    else
    {
        total += sObjectMgr.GetXPForLevel(bot->GetLevel()) + bot->GetUInt32Value(PLAYER_XP);
    }

    return static_cast<uint32>(total > UINT32_MAX ? UINT32_MAX : total);
}

/// 按分隔符首次出现位置将输入字符串拆分为左右两部分
TestResult TextComponent::TrySplitOnce(const std::string& input, const std::string& delimiter,
    std::string& left, std::string& right, std::string& message,
    const std::string& componentName, bool allowEmptyRight)
{
    const size_t pos = input.find(delimiter);
    if (pos == std::string::npos)
    {
        message = "Invalid format in " + componentName + ": " + input;
        return TestResult::IMPOSSIBLE;
    }

    left = Trim(input.substr(0, pos));
    right = Trim(input.substr(pos + delimiter.size()));
    if (!allowEmptyRight && right.empty())
    {
        message = "Invalid format in " + componentName + ": " + input;
        return TestResult::IMPOSSIBLE;
    }

    return TestResult::PASS;
}

/// 提取起止分隔符之间的子串内容
TestResult TextComponent::TryExtractBetween(const std::string& input, const std::string& beginDelimiter,
    const std::string& endDelimiter, std::string& value, std::string& message,
    const std::string& componentName)
{
    const size_t beginPos = input.find(beginDelimiter);
    if (beginPos == std::string::npos)
    {
        message = "Invalid format in " + componentName + ": " + input;
        return TestResult::IMPOSSIBLE;
    }

    const size_t contentStart = beginPos + beginDelimiter.size();
    const size_t endPos = input.find(endDelimiter, contentStart);
    if (endPos == std::string::npos || endPos < contentStart)
    {
        message = "Invalid format in " + componentName + ": " + input;
        return TestResult::IMPOSSIBLE;
    }

    value = input.substr(contentStart, endPos - contentStart);
    return TestResult::PASS;
}

/// 解析形如 "<名称> <比较符> <值>" 的比较表达式
TestResult TextComponent::TryParseComparisonValue(const std::string& input, std::string& valueName, std::string& op, std::string& valueToCompareTo, std::string& message, const std::string& componentName)
{
    std::string leftSide;
    std::string rightSide;
    const TestResult splitResult = TrySplitOnce(input, "=>", leftSide, rightSide, message, componentName, true);
    if (splitResult != TestResult::PASS)
        return splitResult;

    std::vector<std::string> validOps = {"<", ">", "==", "!="};

    for (auto& validOp : validOps)
    {
        size_t opPos = leftSide.find(validOp);
        if (opPos != std::string::npos)
        {
            op = validOp;
            valueName = Trim(leftSide.substr(0, opPos));
            valueToCompareTo = Trim(leftSide.substr(opPos + op.size()));

            return TestResult::PASS;
        }
    }

    message = "Invalid format in " + componentName + ": " + input;
    return TestResult::IMPOSSIBLE;
}

/// 严格解析无符号 32 位整数（不允许溢出或多余尾随字符）
TestResult TextComponent::TryParseUInt32Strict(const std::string& input, uint32& outValue,
    std::string& message, const std::string& componentName)
{
    errno = 0;
    char* endPtr = nullptr;
    const unsigned long parsed = std::strtoul(input.c_str(), &endPtr, 10);
    if (endPtr == input.c_str() || !HasOnlyTrailingWhitespace(endPtr) || errno == ERANGE ||
        parsed > std::numeric_limits<uint32>::max())
    {
        message = "Invalid numeric value in " + componentName + ": " + input;
        return TestResult::IMPOSSIBLE;
    }

    outValue = static_cast<uint32>(parsed);
    return TestResult::PASS;
}

/// 严格解析无符号 64 位整数（不允许溢出或多余尾随字符）
TestResult TextComponent::TryParseUInt64Strict(const std::string& input, uint64& outValue,
    std::string& message, const std::string& componentName)
{
    errno = 0;
    char* endPtr = nullptr;
    const unsigned long long parsed = std::strtoull(input.c_str(), &endPtr, 10);
    if (endPtr == input.c_str() || !HasOnlyTrailingWhitespace(endPtr) || errno == ERANGE)
    {
        message = "Invalid numeric value in " + componentName + ": " + input;
        return TestResult::IMPOSSIBLE;
    }

    outValue = static_cast<uint64>(parsed);
    return TestResult::PASS;
}

/// 严格解析单精度浮点数
TestResult TextComponent::TryParseFloatStrict(const std::string& input, float& outValue,
    std::string& message, const std::string& componentName)
{
    errno = 0;
    char* endPtr = nullptr;
    const float parsed = std::strtof(input.c_str(), &endPtr);
    if (endPtr == input.c_str() || !HasOnlyTrailingWhitespace(endPtr) || errno == ERANGE || !std::isfinite(parsed))
    {
        message = "Invalid numeric value in " + componentName + ": " + input;
        return TestResult::IMPOSSIBLE;
    }

    outValue = parsed;
    return TestResult::PASS;
}

/// 评估监听条件表达式，条件满足时替换消息占位符并返回对应 TestResult
TestResult TestMonitor::Check(const std::string& monitorStr, Player* bot, TestContext& ctx, std::string& message) const
{
    if (IsConditionMet(monitorStr, bot, ctx))
    {
        std::string leftSide;
        std::string rightSide;
        TestResult splitResult = TrySplitOnce(monitorStr, "=>", leftSide, rightSide, message, GetName());
        if (splitResult != TestResult::PASS)
            return splitResult;

        const size_t quoteStart = rightSide.find('"');
        if (quoteStart == std::string::npos)
        {
            message = "Invalid format in " + GetName() + ": " + monitorStr;
            return TestResult::IMPOSSIBLE;
        }

        std::string quotedMessage;
        splitResult = TryExtractBetween(rightSide.substr(quoteStart), "\"", "\"", quotedMessage, message, GetName());
        if (splitResult != TestResult::PASS)
            return splitResult;

        message = quotedMessage;

        // Replace dynamic placeholders in message | 替换结果提示消息中的动态占位符
        std::map<std::string, std::string> placeholders;
        if (bot->IsInWorld())
        {
            WorldPosition pos(bot);
            placeholders["<current position>"] = pos.print(2, true) + " m" + std::to_string(pos.getMapId());

            if (ctx.testStartPosition)
                placeholders["<distance traveled>"] = std::to_string(static_cast<uint32>(ctx.testStartPosition.distance(pos))) + "m";

            placeholders["<mobs killed>"] = std::to_string(static_cast<uint32>(ctx.observedDeadMobs.size()));
        }

        if (ctx.testStartPosition && ctx.destinationPosition)
            placeholders["<distance wanted>"] = std::to_string(static_cast<uint32>(ctx.testStartPosition.distance(WorldPosition(ctx.destinationPosition)))) + "m";

        placeholders["<time elapsed>"] = std::to_string((WorldTimer::getMSTime() - ctx.testStartTime) / 1000) + "s";
        
        if (!placeholders.empty())
        {
            PlayerbotTextMgr::ReplacePlaceholders(message, placeholders);
        }

        std::string resultType = Trim(rightSide.substr(0, quoteStart));

        if (resultType == "pass")
            return TestResult::PASS;
        else if (resultType == "fail")
            return TestResult::FAIL;
        else if (resultType == "impossible")
            return TestResult::IMPOSSIBLE;
        else if (resultType == "abort")
            return TestResult::ABORT;
        else
        {
            message = "Invalid format in " + GetName() + ": " + monitorStr;
            return TestResult::IMPOSSIBLE;
        }
    }
    
    return TestResult::PENDING;
}