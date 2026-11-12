/// DPS 集火协助与 AoE 策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：单体输出集火协助（跟随坦克或团队标记选择攻击目标）
    class DpsAssistStrategy : public Strategy
    {
    public:
        DpsAssistStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "dps assist"; }
        int GetType() override { return STRATEGY_TYPE_DPS; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dps assist"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot assist others when picking a target to attack.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "dps aoe" }; }
#endif
    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：多目标群体伤害（AoE）目标选择策略
    class DpsAoeStrategy : public Strategy
    {
    public:
        DpsAoeStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "dps aoe"; }
        int GetType() override { return STRATEGY_TYPE_DPS; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dps aoe"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot use aoe abilities when multiple targets are close to eachother.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "dps assist" }; }
#endif
    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
