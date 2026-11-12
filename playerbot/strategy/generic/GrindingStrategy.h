/// 野外刷怪（Grinding）策略头文件
#pragma once
#include "NonCombatStrategy.h"

namespace ai
{
    /// 策略：闲暇无目标时主动寻找附近可击杀怪物练级/刷怪
    class GrindingStrategy : public NonCombatStrategy
    {
    public:
        GrindingStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai) {}
        std::string getName() override { return "grind"; }
        int GetType() override { return STRATEGY_TYPE_DPS; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
