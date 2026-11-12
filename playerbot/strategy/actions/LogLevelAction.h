#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 日志级别指令动作：动态调整机器人的调试日志输出级别
    class LogLevelAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化日志级别指令动作
        LogLevelAction(PlayerbotAI* ai) : ChatCommandAction(ai, "log") {}
        /// 执行动作主逻辑（日志级别指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（日志级别指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    public:
        /// 将日志级别枚举值转换为对应的字符串名称
        static std::string logLevel2string(LogLevel level);
        /// 将字符串名称解析为对应的日志级别枚举值
        static LogLevel string2logLevel(std::string level);
    };
}
