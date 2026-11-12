/// 奥妮克希亚的巢穴副本策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：奥妮克希亚的巢穴副本通用策略
    class OnyxiasLairDungeonStrategy : public Strategy
    {
    public:
        OnyxiasLairDungeonStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "onyxias lair"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：奥妮克希亚（Onyxia）首领战策略
    class OnyxiaFightStrategy : public Strategy
    {
    public:
        OnyxiaFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "onyxia"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };
}