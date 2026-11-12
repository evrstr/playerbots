/// 战斗药水、治疗石与绷带使用策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：战斗危急时自动使用治疗石、生命/法力药水、绷带与抗毒药剂
    class UsePotionsStrategy : public Strategy
    {
    public:
        UsePotionsStrategy(PlayerbotAI* ai);
        std::string getName() override { return "potions"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
