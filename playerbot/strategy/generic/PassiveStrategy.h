/// 被动（Passive）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：被动模式，抑制机器人的主动攻击与自主决策行为
    class PassiveStrategy : public Strategy
    {
    public:
        PassiveStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "passive"; }

    private:
        void InitNonCombatMultipliers(std::list<Multiplier*> &multipliers) override;
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
    };
}
