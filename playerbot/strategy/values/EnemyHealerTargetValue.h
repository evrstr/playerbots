// 策略值头文件：EnemyHealerTargetValue（敌方正在施放治疗/增益法术的目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：查找施法范围内正在施放可打断正向法术（治疗/增益）的非当前目标敌人
    class EnemyHealerTargetValue : public UnitCalculatedValue, public Qualified
    {
    public:
        EnemyHealerTargetValue(PlayerbotAI* ai) : UnitCalculatedValue(ai, "enemy healer target"), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };
}
