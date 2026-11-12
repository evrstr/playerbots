// 策略值头文件：LineTargetValue（纵队阵型跟随的前驱目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：计算队伍纵队中排在机器人正前方的跟随对象 GUID
    class LineTargetValue : public UnitCalculatedValue
    {
    public:
        LineTargetValue(PlayerbotAI* ai, std::string name = "line target") : UnitCalculatedValue(ai, name) {}

    public:
        virtual ObjectGuid Calculate() override;
    };
}
