/// 逃跑与躲避 Add 策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：在血蓝危急或敌众我寡时尝试脱离战斗逃跑
    class FleeStrategy : public Strategy
    {
    public:
        FleeStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "flee"; };
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "flee"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot flee when it is in danger.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "flee from adds" }; }
#endif
    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：战斗中自动与附近未引到的潜在怪物保持安全距离
    class FleeFromAddsStrategy : public Strategy
    {
    public:
        FleeFromAddsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "flee from adds"; };
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "flee from adds"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This a position strategy that will make the bot try to avoid adds the prevent aggro.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "flee", "follow", "stay", "runaway", "guard", "free" }; }
#endif
    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
