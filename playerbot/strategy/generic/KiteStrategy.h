/// 风筝（Kite）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：持有当前目标仇恨时边跑边打保持安全风筝距离
    class KiteStrategy : public Strategy
    {
    public:
        KiteStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "kite"; }
    
    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
