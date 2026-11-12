/// 野生机器人自动组队与退队策略头文件
#pragma once
#include "NonCombatStrategy.h"

namespace ai
{
    /// 策略：控制随机机器人的自主邀请组队与脱离失联队伍行为
    class GroupStrategy : public NonCombatStrategy
    {
    public:
        GroupStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai) {}
        std::string getName() override { return "group"; }
        int GetType() override { return STRATEGY_TYPE_GENERIC; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
