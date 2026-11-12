// 策略值头文件：CcTargetValue（群体控制目标选择）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
   
    // 目标值计算器：根据控场法术限定符选择最合适的控制（CC）目标
    class CcTargetValue : public TargetValue, public Qualified
    {
    public:
        CcTargetValue(PlayerbotAI* ai, std::string name = "cc target") : TargetValue(ai, name), Qualified() {}

    public:
        ObjectGuid Calculate() override;
    };
}
