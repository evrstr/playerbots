// 策略值头文件：IsBehindValue（判断机器人是否处于目标身后）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 布尔值计算器：检查机器人是否在近战攻击范围内且与目标朝向夹角小于 90 度（处于背后）
    class IsBehindValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsBehindValue(PlayerbotAI* ai) : BoolCalculatedValue(ai), Qualified() {}

        virtual bool Calculate() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));
            if (!target)
                return false;

            float targetOrientation = target->GetOrientation();
            float orientation = bot->GetOrientation();
            return bot->CanReachWithMeleeAttack(target) && abs(targetOrientation - orientation) < M_PI / 2;
        }
    };
}
