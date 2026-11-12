/// 机器人状态切换触发器头文件
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：战斗开始
    class CombatStartTrigger : public Trigger
    {
    public:
        CombatStartTrigger(PlayerbotAI* ai) : Trigger(ai, "combat start") {}
        virtual bool IsActive() override;
    };

    /// 触发器：战斗结束
    class CombatEndTrigger : public Trigger
    {
    public:
        CombatEndTrigger(PlayerbotAI* ai) : Trigger(ai, "combat end") {}
        virtual bool IsActive() override;
    };

    /// 触发器：角色死亡
    class DeathTrigger : public Trigger
    {
    public:
        DeathTrigger(PlayerbotAI* ai) : Trigger(ai, "death") {}
        virtual bool IsActive() override;
    };

    /// 触发器：角色复活
    class ResurrectTrigger : public Trigger
    {
    public:
        ResurrectTrigger(PlayerbotAI* ai) : Trigger(ai, "resurrect") {}
        virtual bool IsActive() override;
    };
}