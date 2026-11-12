/// 原地返回（Return）策略头文件
#pragma once
#include "NonCombatStrategy.h"

namespace ai
{
    /// 策略：脱战静止一段时间后自动回到先前记录的锚点位置
    class ReturnStrategy : public NonCombatStrategy
    {
    public:
        ReturnStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai) {}
        std::string getName() override { return "return"; }

    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
