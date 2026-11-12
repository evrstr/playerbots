/// 测试命令：测试脚本流程控制命令实现
#include "playerbot/playerbot.h"
#include "CommandFlow.h"
#include "TestAction.h"
#include "TestRegistry.h"

using namespace ai;

/// 执行 observe 命令：进入持续观察期，开始评估所有已注册监听器
TestResult CommandFlowObserve::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    ctx.observing = true;
    return TestResult::PASS;
}

/// 执行 preconditions 命令：标记或检查前置条件阶段
TestResult CommandFlowPreconditions::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    return TestResult::PASS;
}

/// 执行 monitor 命令：将一条监听器规则字符串添加到当前上下文监听列表
TestResult CommandFlowMonitor::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    ctx.monitors.push_back(params);
    return TestResult::PASS;
}

/// 执行 wait 命令：阻塞测试脚本前进直到指定等待秒数结束
TestResult CommandFlowWait::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    if (!ctx.waitTime)
        ctx.waitTime = WorldTimer::getMSTime();

    // Scripts are written as "wait <seconds>" (e.g. "wait 5"). The older spelling is still accepted | 脚本格式为 "wait <seconds>"，同时兼容旧语法
    // as "wait time <seconds>". | "wait time <seconds>"。
    std::string value = params;
    if (value.find("time ") == 0)
        value = value.substr(5);

    uint32 waitSeconds = 0;
    if (TryParseUInt32Strict(value, waitSeconds, message, GetName()) != TestResult::PASS)
        return TestResult::IMPOSSIBLE;

    if (WorldTimer::getMSTimeDiff(ctx.waitTime, WorldTimer::getMSTime()) >= waitSeconds * 1000)
    {
        ctx.waitTime = 0;
        return TestResult::PASS;
    }
    
    return TestResult::PENDING;
}

/// 执行 wait destination 命令：等待机器人抵达目标坐标指定距离内，或在超时后失败
TestResult CommandFlowWaitDestination::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    if (ctx.destinationPosition.distance(bot) < 10.0f)
        return TestResult::PASS;

    if (!ctx.waitTime)
        ctx.waitTime = WorldTimer::getMSTime();

    // Seconds, like "wait" - scripts use "wait destination 600" to mean ten minutes. | 参数为秒数（例如 "wait destination 600" 表示等待 10 分钟）。
    // Optional trailing distance: "wait destination 600 4" passes within 4 yd instead of the | 可选尾部距离参数（如 "wait destination 600 4" 表示 4 码内通过，默认 10 码）；
    // default 10. Rpg injection must happen inside INTERACTION_DISTANCE (~5.5 yd), otherwise | RPG 注入必须在交互距离（~5.5 码）内完成，否则
    // the far-from-rpg-target machinery drops the injected target again. | 远离 RPG 目标检测逻辑会自动放弃注入的目标。
    std::string value = params;
    if (value.find("time ") == 0)
        value = value.substr(5);

    float arriveDistance = 10.0f;
    size_t space = value.rfind(' ');
    if (space != std::string::npos)
    {
        if (TryParseFloatStrict(value.substr(space + 1), arriveDistance, message, GetName()) != TestResult::PASS)
            return TestResult::IMPOSSIBLE;
        value = value.substr(0, space);
    }

    uint32 waitSeconds = 0;
    if (TryParseUInt32Strict(value, waitSeconds, message, GetName()) != TestResult::PASS)
        return TestResult::IMPOSSIBLE;

    if (ctx.destinationPosition.distance(bot) < arriveDistance)
        return TestResult::PASS;

    if (WorldTimer::getMSTimeDiff(ctx.waitTime, WorldTimer::getMSTime()) >= waitSeconds * 1000)
    {
        ctx.waitTime = 0;
        return TestResult::PASS;
    }

    return TestResult::PENDING;
}

/// 执行 wait group 命令：等待队伍成员数量达到预期人数或超时失败
TestResult CommandFlowWaitGroup::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string value = params;
    size_t space = value.find(' ');

    std::string sizePart = space == std::string::npos ? value : value.substr(0, space);
    std::string timeoutPart = space == std::string::npos ? std::string() : value.substr(space + 1);

    uint32 expected = 0;
    if (TryParseUInt32Strict(sizePart, expected, message, GetName()) != TestResult::PASS)
        return TestResult::IMPOSSIBLE;

    uint32 waitSeconds = 180;
    if (!timeoutPart.empty() && TryParseUInt32Strict(timeoutPart, waitSeconds, message, GetName()) != TestResult::PASS)
        return TestResult::IMPOSSIBLE;

    if (!ctx.waitTime)
        ctx.waitTime = WorldTimer::getMSTime();

    Group* group = bot->GetGroup();

    if (group && group->GetMembersCount() >= expected)
    {
        ctx.waitTime = 0;
        return TestResult::PASS;
    }

    uint32 elapsed = WorldTimer::getMSTimeDiff(ctx.waitTime, WorldTimer::getMSTime());
    if (elapsed >= waitSeconds * 1000)
    {
        ctx.waitTime = 0;
        return TestResult::PASS;
    }

    return TestResult::PENDING;
}

/// 执行 repeat 命令：将程序计数器跳转至第 1 步（或指定行）循环重跑测试
TestResult CommandFlowRepeat::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    if (params.empty())
    {
        ctx.pc = 0;
        return TestResult::PENDING;
    }

    uint32 pc = 0;
    if (TryParseUInt32Strict(params, pc, message, GetName()) != TestResult::PASS)
        return TestResult::IMPOSSIBLE;

    ctx.pc = static_cast<int>(pc);

    return TestResult::PENDING;
}