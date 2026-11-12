/// 角色日常维护（Maintenance）策略头文件
#pragma once
#include "NonCombatStrategy.h"

namespace ai
{
    /// 策略：执行背包整理、拆解/附魔、垃圾清理、卡死脱离与自动任务共享维护
    class MaintenanceStrategy : public NonCombatStrategy
    {
    public:
        MaintenanceStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai) {}
        std::string getName() override { return "maintenance"; }
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
