/// 自动团队目标标记（Mark RTI）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：在战斗中自动为当前主攻或需要控制的目标添加团队图标标记
    class MarkRtiStrategy : public Strategy
    {
    public:
        MarkRtiStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "mark rti"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
