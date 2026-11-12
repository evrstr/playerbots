/// 仇恨控制（Threat）策略头文件
#pragma once
#include "playerbot/strategy/Multiplier.h"
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 乘数：在队伍战斗中仇恨过高时抑制高威胁动作以防 OT
    class ThreatMultiplier : public Multiplier
    {
    public:
        ThreatMultiplier(PlayerbotAI* ai) : Multiplier(ai, "threat") {}

    public:
        float GetValue(Action* action) override;
    };

    /// 策略：自动监控并控制仇恨值避免抢走坦克目标
    class ThreatStrategy : public Strategy
    {
    public:
        ThreatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "threat"; }

    private:
        void InitCombatMultipliers(std::list<Multiplier*> &multipliers) override;
    };
}
