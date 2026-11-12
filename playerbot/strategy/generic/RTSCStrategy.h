/// RTSC（即时战略群体控制）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：启用 RTSC 即时战略指挥控制模式
    class RTSCStrategy : public Strategy
    {
    public:
        RTSCStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "rtsc"; }
    };

    /// 策略：响应 RTSC 定向跳跃指令
    class RTSCSJumptrategy : public Strategy
    {
    public:
        RTSCSJumptrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "rtsc jump"; }

    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
