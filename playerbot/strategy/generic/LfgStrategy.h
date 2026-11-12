/// 地下城查找器（LFG）策略头文件
#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    /// 策略：控制机器人自动参与 LFG 地下城匹配排队与副本组队管理
    class LfgStrategy : public PassTroughStrategy
    {
    public:
        LfgStrategy(PlayerbotAI* ai) : PassTroughStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "lfg"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override {}
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override {}
    };
}
