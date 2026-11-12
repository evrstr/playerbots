// 策略值头文件：NearestAdsValue（逃跑距离内非当前目标的额外敌人）
#pragma once
#include "playerbot/strategy/Value.h"
#include "NearestUnitsValue.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "PossibleTargetsValue.h"

namespace ai
{
    // 目标列表计算器：查找逃跑警戒距离内的附近潜在敌人（排除当前主目标）
    class NearestAddsValue : public PossibleTargetsValue
    {
    public:
        NearestAddsValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.fleeDistance) :
            PossibleTargetsValue(ai, "nearest adds", range, true) {}

    protected:
        bool AcceptUnit(Unit* unit) override;
    };
}
