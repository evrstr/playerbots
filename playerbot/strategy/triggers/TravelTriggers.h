/// 旅行与传送门触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：附近有任务发布/交付NPC
    class HasNearbyQuestTakerTrigger : public Trigger
    {
    public:
        HasNearbyQuestTakerTrigger(PlayerbotAI* ai) : Trigger(ai, "has nearby quest taker", 30) {}

        virtual bool IsActive() override;
    };

    /// 触发器：处于黑暗之门附近区域
    class NearDarkPortalTrigger : public Trigger
    {
    public:
        NearDarkPortalTrigger(PlayerbotAI* ai) : Trigger(ai, "near dark portal", 10) {}

        virtual bool IsActive() override;
    };

    /// 触发器：位于艾泽拉斯黑暗之门前
    class AtDarkPortalAzerothTrigger : public Trigger
    {
    public:
        AtDarkPortalAzerothTrigger(PlayerbotAI* ai) : Trigger(ai, "at dark portal azeroth", 10) {}

        virtual bool IsActive() override;
    };

    /// 触发器：位于外域黑暗之门前
    class AtDarkPortalOutlandTrigger : public Trigger
    {
    public:
        AtDarkPortalOutlandTrigger(PlayerbotAI* ai) : Trigger(ai, "at dark portal outland", 10) {}

        virtual bool IsActive() override;
    };
}
