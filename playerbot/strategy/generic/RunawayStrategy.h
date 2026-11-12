/// 远离逃跑（Runaway）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：战斗中敌人贴近时执行远离逃跑动作
    class RunawayStrategy : public Strategy
    {
    public:
        RunawayStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "runaway"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
