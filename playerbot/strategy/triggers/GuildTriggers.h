/// 公会管理触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{    
    /// 触发器：满足条件可提交公会签名表
    class PetitionTurnInTrigger : public Trigger {
    public:
        PetitionTurnInTrigger(PlayerbotAI* ai) :
            Trigger(ai, "petition turn in trigger", 5) {}

        bool IsActive() override { return AI_VALUE(bool, "can hand in petition"); };
    };

    /// 触发器：可以购买公会战袍
    class BuyTabardTrigger : public Trigger {
    public:
        BuyTabardTrigger(PlayerbotAI* ai) :
            Trigger(ai, "buy tabard trigger", 5) {}

        bool IsActive() override { return AI_VALUE(bool, "can buy tabard"); };
    };

    /// 触发器：需要离开规模过大的随机公会
    class LeaveLargeGuildTrigger : public Trigger {
    public:
        LeaveLargeGuildTrigger(PlayerbotAI* ai) :
            Trigger(ai, "leave large guild trigger", 10) {}

        bool IsActive();
    };
}