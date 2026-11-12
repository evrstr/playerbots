// 策略值头文件：RandomBotUpdateValue（随机机器人周期更新触发标志）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：标记随机机器人是否需要执行周期性状态刷新或重置
    class RandomBotUpdateValue : public ManualSetValue<bool>
    {
    public:
        RandomBotUpdateValue(PlayerbotAI* ai, std::string name = "random bot update") : ManualSetValue<bool>(ai, false, name) {}
    };
}
