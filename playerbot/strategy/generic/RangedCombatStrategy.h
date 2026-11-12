/// 远程战斗（Ranged Combat）策略头文件
#include "CombatStrategy.h"
#pragma once

namespace ai
{
    /// 策略：远程施法/射击职业的基础战斗保持距离策略
    class RangedCombatStrategy : public CombatStrategy
    {
    public:
        RangedCombatStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "ranged"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
