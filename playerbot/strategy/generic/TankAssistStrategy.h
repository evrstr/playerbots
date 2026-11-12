/// 坦克辅助（Tank Assist）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：协助主坦克接管或攻击坦克当前目标
    class TankAssistStrategy : public Strategy
    {
    public:
        TankAssistStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "tank assist"; }
        int GetType() override { return STRATEGY_TYPE_TANK; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
