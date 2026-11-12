// 策略值头文件：LastPotionUsedTimeValue（上次使用药水时间戳）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：记录机器人上一次饮用药水的时间戳（用于冷却/间隔控制）
    class LastPotionUsedTimeValue : public ManualSetValue<time_t>
    {
    public:
        LastPotionUsedTimeValue(PlayerbotAI* ai) : ManualSetValue<time_t>(ai, 0) {}
    };
}
