// 策略值头文件：SelfTargetValue（机器人自身目标 GUID）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：始终返回机器人自身的 ObjectGuid
    class SelfTargetValue : public UnitCalculatedValue
    {
    public:
        SelfTargetValue(PlayerbotAI* ai, std::string name = "self target") : UnitCalculatedValue(ai, name) {}

        virtual ObjectGuid Calculate() override { return ai->GetBot() ? ai->GetBot()->GetObjectGuid() : ObjectGuid(); }
    };
}
