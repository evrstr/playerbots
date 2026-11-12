/// 测试命令：调试开关与录制/读取命令实现
#include "CommandDebug.h"

using namespace ai;

/// 执行 debug 命令：设置 TestContext::debug 标志以开启或关闭详细调试日志
TestResult CommandDebug::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    ctx.debug = true;
    return TestResult::PASS;
}

/// 执行 record 命令：录制测试机器人状态快照至目标文件
TestResult CommandRecord::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    ai->RecordMessages(true, !params.empty());
    return TestResult::PASS;
}

/// 执行 read 命令：回放并输出指定名称的已记录消息
TestResult CommandRead::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    for (auto& msg : ai->GetRecordedMessages())
    {
        ai->TellPlayer(bot, std::string("[Recorded Message] ") + msg);
        sLog.outString("[TestAction] Bot %s outgoing %s", bot->GetName(), msg.c_str());
    }
    return TestResult::PASS;
}