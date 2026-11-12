// 策略值头文件：SnareTargetValue（需要施加减速/诱捕效果的敌人目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：在可攻击目标中查找正在移动且尚未被减速的敌人（适合风筝或防逃跑）
    class SnareTargetValue : public UnitCalculatedValue, public Qualified
    {
    public:
        SnareTargetValue(PlayerbotAI* ai) :
            UnitCalculatedValue(ai, "snare target"), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };
}
