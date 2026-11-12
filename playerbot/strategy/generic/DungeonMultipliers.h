/// 副本动作协调乘数头文件
#pragma once

#include "playerbot/strategy/Multiplier.h"

class Action;

namespace ai
{
    /// 乘数：在刚移动接近目标准备施法后，防止立即被远离危险动作打断导致来回拉扯
    class PreventMoveAwayFromCreatureOnReachToCastMultiplier : public Multiplier
    {
    public:
        PreventMoveAwayFromCreatureOnReachToCastMultiplier(PlayerbotAI* ai) : Multiplier(ai, "cast spell after reach") {}

    public:
        virtual float GetValue(Action* action) override;
    };
}
