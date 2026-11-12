/// 攻击敌对玩家（PvP）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：自动侦测并攻击附近的敌对阵营玩家
    class AttackEnemyPlayersStrategy : public Strategy
    {
    public:
        AttackEnemyPlayersStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "pvp"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "pvp"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy detect nearby enemy players and makes the bot attack them.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
