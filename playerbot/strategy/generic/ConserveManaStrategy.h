/// 省蓝（Conserve / Save Mana）策略头文件
#pragma once
#include "playerbot/strategy/Multiplier.h"
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 乘数：低法力时限制部分消耗法力的增益施放
    class ConserveManaMultiplier : public Multiplier
    {
    public:
        ConserveManaMultiplier(PlayerbotAI* ai) : Multiplier(ai, "conserve mana") {}

    public:
        virtual float GetValue(Action* action) override;
    };

    /// 乘数：按省蓝等级拉长高耗蓝法术的施放间隔
    class SaveManaMultiplier : public Multiplier
    {
    public:
        SaveManaMultiplier(PlayerbotAI* ai) : Multiplier(ai, "save mana") {}

    public:
        virtual float GetValue(Action* action) override;
    };

    /// 策略：节省法力值，避免非必要耗蓝操作
    class ConserveManaStrategy : public Strategy
    {
    public:
        ConserveManaStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "conserve mana"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "conserve mana"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots wait longer between casting the same spell twice.\n"
                   "the delay is based on [h:value|mana save level].";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { }; }
#endif
    private:
        void InitCombatMultipliers(std::list<Multiplier*> &multipliers) override;
    };
}
