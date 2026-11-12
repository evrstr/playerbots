/// 脱战吃喝回复（Food & Drink）策略头文件
#pragma once

namespace ai
{
    /// 策略：脱战后生命或法力值不足时自动使用食物和魔法水回复
    class UseFoodStrategy : public Strategy
    {
    public:
        UseFoodStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "food"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
