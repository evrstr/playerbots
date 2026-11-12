/// 施法时间控制策略头文件
#pragma once
#include "playerbot/strategy/Multiplier.h"
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 乘数：根据目标低血量状态动态降低长读条法术的权重
    class CastTimeMultiplier : public Multiplier
    {
    public:
        CastTimeMultiplier(PlayerbotAI* ai) : Multiplier(ai, "cast time") {}

    public:
        virtual float GetValue(Action* action) override;
    };

    /// 策略：目标残血时避免施放长读条法术
    class CastTimeStrategy : public Strategy
    {
    public:
        CastTimeStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "cast time"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "cast time"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots less likely to cast long casttime spells when the target is at critical health.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { }; }
#endif
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
    };
}
