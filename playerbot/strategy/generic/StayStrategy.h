/// 原地停留（Stay）与坐下休息（Sit）策略头文件
#pragma once
#include "NonCombatStrategy.h"

namespace ai
{
    /// 策略：使机器人停留在指定位置并在偏离后自动归位
    class StayStrategy : public Strategy
    {
    public:
        StayStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "stay"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        NextAction** GetDefaultNonCombatActions() override;
        NextAction** GetDefaultCombatActions() override;
        virtual void OnStrategyAdded(BotState state) override;
    };

    /// 策略：脱战原地停留超时后自动坐下休息
    class SitStrategy : public NonCombatStrategy
    {
    public:
        SitStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai) {}
        std::string getName() override { return "sit"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
