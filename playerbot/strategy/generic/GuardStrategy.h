/// 原地守卫（Guard）策略头文件
#pragma once
#include "NonCombatStrategy.h"

namespace ai
{
    /// 策略：使机器人驻守在指定防线位置，直到发现可攻击敌人后再出击
    class GuardStrategy : public NonCombatStrategy
    {
    public:
        GuardStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai) {}
        std::string getName() override { return "guard"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "guard"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This a position strategy that will make the bot stay in a location until they have something to attack.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "follow", "stay", "runaway", "flee from adds", "free" }; }
#endif
    private:
        NextAction** GetDefaultNonCombatActions() override;
        NextAction** GetDefaultCombatActions() override;
    };
}
