/// 跟随主人、自由行动与跟随跳跃策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：使机器人按队形保持跟随主人或指定跟随目标
    class FollowMasterStrategy : public Strategy
    {
    public:
        FollowMasterStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "follow"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "follow"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot stay near the master";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "stay", "runaway","flee from adds", "guard", "free"}; }
#endif
    protected:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;

        virtual void OnStrategyAdded(BotState state) override;
        virtual void OnStrategyRemoved(BotState state) override;
    };

    /// 策略：允许机器人在场景中自由移动（解除严格跟随约束）
    class FreeStrategy : public Strategy
    {
    public:
        FreeStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "free"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "free"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will allow the bot to move freely";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "follow", "stay", "runaway","flee from adds", "guard" }; }
#endif
    };

    /// 策略：跟随主人移动时伴随同步跳跃动作
    class FollowJumpStrategy : public Strategy
    {
    public:
        FollowJumpStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "follow jump"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "follow jump"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot jump when following.\n";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "follow" }; }
#endif
    };
}
