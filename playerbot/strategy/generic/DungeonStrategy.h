/// 副本策略自动启停调度器头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：根据当前所在副本地图 ID 自动加载或卸载对应团队/五人本专属策略
    class DungeonStrategy : public Strategy
    {
    public:
        DungeonStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "dungeon"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dungeon"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription()
        {
            return "This strategy will enable and disable various dungeon and raid specific strategies as the bot enters and leaves.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {"onyxias lair", "molten core" }; }
#endif

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}