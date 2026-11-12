// 策略值头文件：AttackerWithoutAuraTargetValue（缺少指定光环的攻击目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：在施法范围内查找缺少指定光环（Debuff/Aura）的非当前目标敌人
    class AttackerWithoutAuraTargetValue : public UnitCalculatedValue, public Qualified
    {
    public:
        AttackerWithoutAuraTargetValue(PlayerbotAI* ai) : UnitCalculatedValue(ai, "attacker without aura"), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };
}
