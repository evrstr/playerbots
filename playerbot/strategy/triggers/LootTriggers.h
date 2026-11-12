/// 拾取相关触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 触发器：附近有可拾取战利品
    class LootAvailableTrigger : public Trigger
    {
    public:
        LootAvailableTrigger(PlayerbotAI* ai) : Trigger(ai, "loot available") {}

        virtual bool IsActive() override;
    };

    /// 触发器：距离当前选定的战利品目标过远
    class FarFromCurrentLootTrigger : public Trigger
    {
    public:
        FarFromCurrentLootTrigger(PlayerbotAI* ai) : Trigger(ai, "far from current loot") {}

        virtual bool IsActive() override;
    };

    /// 触发器：满足拾取条件
    class CanLootTrigger : public Trigger
    {
    public:
        CanLootTrigger(PlayerbotAI* ai) : Trigger(ai, "can loot") {}

        virtual bool IsActive() override;
    };
}
