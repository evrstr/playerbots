/// 切换目标播报（Tell Target）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：战斗中更换当前目标时向主人通报
    class TellTargetStrategy : public Strategy
    {
    public:
        TellTargetStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "tell target"; }
    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
