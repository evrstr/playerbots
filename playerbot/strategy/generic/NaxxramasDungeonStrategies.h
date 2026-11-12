/// 纳克萨玛斯（Naxxramas）团队副本策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：纳克萨玛斯副本通用策略
    class NaxxramasDungeonStrategy : public Strategy
    {
    public:
        NaxxramasDungeonStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "naxxramas"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：天启四骑士（Four Horsemen）战斗策略（虚空地带规避）
    class FourHorsemanFightStrategy : public Strategy
    {
    public:
        FourHorsemanFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "four horseman"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };
}