/// 消耗品（合剂/药水/卷轴等）使用策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：在非战斗和战斗状态下自动使用增益类消耗品
    class ConsumableStrategy : public Strategy
    {
    public:
        ConsumableStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "consumables"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}