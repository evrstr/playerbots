// 策略值头文件：LogLevelValue（机器人日志输出级别）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：控制机器人 AI 调试与提示信息的日志等级（默认 LOG_LVL_DEBUG）
    class LogLevelValue : public ManualSetValue<LogLevel>
    {
    public:
        LogLevelValue(PlayerbotAI* ai, std::string name = "log level") :
            ManualSetValue<LogLevel>(ai, LOG_LVL_DEBUG, name) {}
    };
}
