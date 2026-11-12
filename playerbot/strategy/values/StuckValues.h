// 策略值头文件：StuckValues（卡位检测：AI 值未变化时长与历史移动距离）
#pragma once
#include "playerbot/strategy/Value.h"


namespace ai
{
    // 值计算器：获取指定限定符对应的 AI 值距离上次发生变化经过的秒数
    class TimeSinceLastChangeValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        TimeSinceLastChangeValue(PlayerbotAI* ai, std::string name = "time since last change") : Uint32CalculatedValue(ai, name), Qualified() {}
        
        virtual uint32 Calculate() override;
    };

    // 值计算器：计算在给定秒数窗口内机器人移动过的最大直线距离（用于检测原地卡死）
    class DistanceMovedSinceValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        DistanceMovedSinceValue(PlayerbotAI* ai, std::string name = "distance moved since") : Uint32CalculatedValue(ai, name) {}
        virtual uint32 Calculate() override;
    };
}
