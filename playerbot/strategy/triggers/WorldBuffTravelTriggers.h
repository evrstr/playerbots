/// 世界增益自动旅行（World Buff Travel）触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"
#include "playerbot/strategy/generic/WorldBuffTravelStrategy.h"

namespace ai
{
    /// 触发器：已抵达世界增益目标区域
    class WorldBuffTravelZoneReachedTrigger : public Trigger
    {
    public:
        WorldBuffTravelZoneReachedTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel zone reached", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：需要向世界增益目标地点移动
    class WorldBuffTravelNeedMoveTrigger : public Trigger
    {
    public:
        WorldBuffTravelNeedMoveTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel need move", 3) {
        }

        bool IsActive() override;
    };

    /// 触发器：已在厄运之槌（DM）获取全部厄运 Buff
    class WorldBuffTravelDMBuffedTrigger : public Trigger
    {
    public:
        WorldBuffTravelDMBuffedTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel dm buffed", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：已走出厄运之槌副本
    class WorldBuffTravelDMExitedTrigger : public Trigger
    {
    public:
        WorldBuffTravelDMExitedTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel dm exited", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：在厄运之槌外需要施放传送门
    class WorldBuffTravelDMPortalCastTrigger : public Trigger
    {
    public:
        WorldBuffTravelDMPortalCastTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel dm portal cast", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：可以使用传送门离开厄运区域
    class WorldBuffTravelDMPortalUseTrigger : public Trigger
    {
    public:
        WorldBuffTravelDMPortalUseTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel dm portal use", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：到达费伍德森林轻歌花位置准备拾取
    class WorldBuffTravelSongflowerTrigger : public Trigger
    {
    public:
        WorldBuffTravelSongflowerTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel songflower", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：处于使用传送门步骤
    class WorldBuffTravelPortalStepTrigger : public Trigger
    {
    public:
        WorldBuffTravelPortalStepTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel portal step", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：交互传送门前往下一个地点
    class WorldBuffTravelUsePortalTrigger : public Trigger
    {
    public:
        WorldBuffTravelUsePortalTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel use portal", 2) {
        }

        bool IsActive() override;
    };

    /// 触发器：所有计划中的世界增益收集完成
    class WorldBuffTravelDoneTrigger : public Trigger
    {
    public:
        WorldBuffTravelDoneTrigger(PlayerbotAI* ai)
            : Trigger(ai, "world buff travel done", 2) {
        }

        bool IsActive() override;
    };
}