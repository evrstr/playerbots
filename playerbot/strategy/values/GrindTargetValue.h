// 策略值头文件：GrindTargetValue（刷怪练级目标选择）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
   
    // 目标值计算器：在非战斗状态下挑选最合适的刷怪/任务击杀目标
    class GrindTargetValue : public TargetValue
    {
    public:
        GrindTargetValue(PlayerbotAI* ai, std::string name = "grind target") : TargetValue(ai, name, 2) {}

    public:
        ObjectGuid Calculate() override;

    private:
        int GetTargetingPlayerCount(Unit* unit);
        Unit* FindTargetForGrinding(int assistCount);
    };
}
