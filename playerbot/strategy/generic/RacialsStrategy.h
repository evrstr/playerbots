/// 通用种族天赋（Racials）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：根据战斗/控制/血量触发条件自动使用各角色对应的种族主动技能
    class RacialsStrategy : public Strategy
    {
    public:
        RacialsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "racials"; }
    
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}