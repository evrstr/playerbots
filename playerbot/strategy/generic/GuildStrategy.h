/// 公会社交与自动管理策略头文件
#pragma once
#include "NonCombatStrategy.h"

namespace ai
{
    /// 策略：管理随机机器人的公会创建、成员维护、订单协作与物资共享行为
    class GuildStrategy : public NonCombatStrategy
    {
    public:
        GuildStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai) {}
        std::string getName() override { return "guild"; }
        int GetType() override { return STRATEGY_TYPE_GENERIC; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
