/// 黑翼之巢（BWL）团队副本策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：黑翼之巢副本通用策略（处理压制装置交互）
    class BlackwingLairDungeonStrategy : public Strategy
    {
    public:
        BlackwingLairDungeonStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "blackwing lair"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：勒什雷尔前陷阱房（Suppression Room）盗贼专属拆陷阱策略
    class SuppressionRoomStrategy : public Strategy
    {
    public:
        SuppressionRoomStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "suppression room"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitNonCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void OnStrategyAdded(BotState state) override;
    };
}