/// 战斗喊话提示（Say）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：根据自身血蓝与战斗危急情况向队伍发送自动状态提示喊话
    class SayStrategy : public Strategy
    {
    public:
        SayStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "say"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
