// 策略值头文件：CurrentCcTargetValue（当前已被控场的目标）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
   
    // 目标值计算器：查找当前身上带有指定控场光环的敌对目标
    class CurrentCcTargetValue : public TargetValue, public Qualified
    {
    public:
        CurrentCcTargetValue(PlayerbotAI* ai, std::string name = "current cc target") : TargetValue(ai, name), Qualified() {}

    public:
        ObjectGuid Calculate() override;
    };
}
