/// 附近游荡（Wander）策略头文件

#pragma once
#include "playerbot/strategy/generic/FollowMasterStrategy.h"

namespace ai
{   
    /// 策略：在主人周围 30 码内自由游荡，超出范围则自动跟上
    class WanderStrategy : public FollowMasterStrategy
    {
    public:
        WanderStrategy(PlayerbotAI* ai) : FollowMasterStrategy(ai) {}

        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "wander"; }

#ifdef GenerateBotHelp
        std::string GetHelpName() override { return "wander"; } // Must equal internal name | 必须与内部策略名一致
        std::string GetHelpDescription() override
        {
            return "If bot is farther than 30 yd -> follow master. If within 30 yd -> move freely.";
        }
        std::vector<std::string> GetRelatedStrategies() override
        {
            return { "follow", "free", "stay", "guard" };
        }
#endif

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
