/// 能源舰（The Mechanar）副本及首领策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：能源舰副本总控策略
    class MechanarDungeonStrategy : public Strategy
    {
    public:
        MechanarDungeonStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "mechanar"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：灵术师塞佩丝蕾战斗策略（规避狂怒烈焰追踪）
    class NethermancerSepethreaFightStrategy : public Strategy
    {
    public:
        NethermancerSepethreaFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "nethermancer sepethrea"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };
}