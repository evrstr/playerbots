// 策略值头文件：IsMovingValue（单位移动与游泳状态检测）
#pragma once
#include "playerbot/strategy/Value.h"
#include "MotionGenerators/TargetedMovementGenerator.h"

namespace ai
{
    // 布尔值计算器：判断指定目标单位当前是否正在移动（非停止状态）
    class IsMovingValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsMovingValue(PlayerbotAI* ai, std::string name = "is moving") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));

            if (!target)
                return false;

            return !target->IsStopped();
        }
    };

    // 布尔值计算器：判断指定目标单位当前是否处于水下或可游泳水域中
    class IsSwimmingValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsSwimmingValue(PlayerbotAI* ai, std::string name = "is swimming") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));

            if (!target)
                return false;

            return sServerFacade.IsUnderwater(target) || target->IsInSwimmableWater();
        }
    };
}
