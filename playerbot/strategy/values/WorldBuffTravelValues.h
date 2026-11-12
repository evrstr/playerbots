// 策略值头文件：WorldBuffTravelValues（世界增益收集旅行当前阶段步骤）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：记录机器人当前正在进行的世界 Buff 收集旅行流程步骤编号
    class WorldBuffTravelStepValue : public ManualSetValue<uint8>
    {
    public:
        WorldBuffTravelStepValue(PlayerbotAI* ai)
            : ManualSetValue<uint8>(ai, 0, "world buff travel step") {}
    };
}