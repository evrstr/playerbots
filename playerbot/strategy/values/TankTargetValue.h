// 策略值头文件：TankTargetValue（坦克拉怪目标选择）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"
#include "RtiTargetValue.h"

namespace ai
{
    // 目标值计算器：为坦克职责选取需要建立或夺回仇恨的优先目标（依次按指令、RTI 标记、低仇恨）
    class TankTargetValue : public RtiTargetValue
    {
    public:
        TankTargetValue(PlayerbotAI* ai, std::string type = "rti", std::string name = "tank target") : RtiTargetValue(ai, type, name) {}

    public:
        ObjectGuid Calculate() override;
    };
}
