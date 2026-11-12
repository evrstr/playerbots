// 策略值头文件：DpsTargetValue（单体及群体输出目标选择）
#pragma once
#include "playerbot/strategy/Value.h"
#include "RtiTargetValue.h"
#include "TargetValue.h"

namespace ai
{
    // 目标值计算器：为 DPS 职责选择优先输出目标（依次按指令、RTI 标记、最低血量）
    class DpsTargetValue : public RtiTargetValue
    {
    public:
        DpsTargetValue(PlayerbotAI* ai, std::string type = "rti", std::string name = "dps target") : RtiTargetValue(ai, type, name) {}

    public:
        ObjectGuid Calculate() override;
    };

    // 目标值计算器：为 AOE 输出选择目标（优先 RTI 标记或血量最高的主目标）
    class DpsAoeTargetValue : public RtiTargetValue
    {
    public:
        DpsAoeTargetValue(PlayerbotAI* ai, std::string type = "rti", std::string name = "dps aoe target") : RtiTargetValue(ai, type, name) {}

    public:
        ObjectGuid Calculate() override;
    };
}
