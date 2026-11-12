// 策略值头文件：DuelTargetValue（决斗对手目标）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
    // 目标值计算器：获取机器人当前决斗对手的 GUID
    class DuelTargetValue : public TargetValue
    {
    public:
        DuelTargetValue(PlayerbotAI* ai, std::string name = "duel target") : TargetValue(ai, name) {}

    public:
        ObjectGuid Calculate() override;
    };
}
