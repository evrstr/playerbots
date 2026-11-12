/// 拉怪（Pull）策略触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：开始执行拉怪
    class PullStartTrigger : public Trigger
    {
    public:
        PullStartTrigger(PlayerbotAI* ai, std::string name = "pull start") : Trigger(ai, name) {}
        bool IsActive() override;
    };

    /// 触发器：拉怪阶段结束
    class PullEndTrigger : public Trigger
    {
    public:
        PullEndTrigger(PlayerbotAI* ai, std::string name = "pull end") : Trigger(ai, name) {}
        bool IsActive() override;
    };
}
