/// PvP、战场与载具相关触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：附近存在可攻击的敌对玩家
    class EnemyPlayerNear : public Trigger
    {
    public:
        EnemyPlayerNear(PlayerbotAI* ai) : Trigger(ai, "enemy player near") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：战场中玩家未持有旗帜
    class PlayerHasNoFlag : public Trigger
    {
    public:
        PlayerHasNoFlag(PlayerbotAI* ai) : Trigger(ai, "player has no flag") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：玩家当前携带战场旗帜
    class PlayerHasFlag : public Trigger
    {
    public:
        PlayerHasFlag(PlayerbotAI* ai) : Trigger(ai, "player has flag") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：敌方扛旗手在附近
    class EnemyFlagCarrierNear : public Trigger
    {
    public:
        EnemyFlagCarrierNear(PlayerbotAI* ai) : Trigger(ai, "enemy flagcarrier near") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：友方扛旗手在附近
    class TeamFlagCarrierNear : public Trigger
    {
    public:
        TeamFlagCarrierNear(PlayerbotAI* ai) : Trigger(ai, "team flagcarrier near") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：我方队伍正在持有敌方旗帜
    class TeamHasFlag : public Trigger
    {
    public:
        TeamHasFlag(PlayerbotAI* ai) : Trigger(ai, "team has flag") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：敌方队伍正在持有我方旗帜
    class EnemyTeamHasFlag : public Trigger
    {
    public:
        EnemyTeamHasFlag(PlayerbotAI* ai) : Trigger(ai, "enemy team has flag") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：机器人正处于战场中
    class PlayerIsInBattleground : public Trigger
    {
    public:
        PlayerIsInBattleground(PlayerbotAI* ai) : Trigger(ai, "in battleground") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：战场处于等待开局阶段
    class BgWaitingTrigger : public Trigger
    {
    public:
        BgWaitingTrigger(PlayerbotAI* ai) : Trigger(ai, "bg waiting", 30) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：战场正在进行中
    class BgActiveTrigger : public Trigger
    {
    public:
        BgActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "bg active", 1) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：收到战场进入邀请
    class BgInviteActiveTrigger : public Trigger
    {
    public:
        BgInviteActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "bg invite active", 10) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：战场已结束等待离开
    class BgEndedTrigger : public Trigger
    {
    public:
        BgEndedTrigger(PlayerbotAI* ai) : Trigger(ai, "bg ended", 10) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：处于战歌等战场中但未持有旗帜
    class PlayerIsInBattlegroundWithoutFlag : public Trigger
    {
    public:
        PlayerIsInBattlegroundWithoutFlag(PlayerbotAI* ai) : Trigger(ai, "in battleground without flag") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：机器人符合条件且希望加入战场队列
    class PlayerWantsInBattlegroundTrigger : public Trigger
    {
    public:
        PlayerWantsInBattlegroundTrigger(PlayerbotAI* ai) : Trigger(ai, "wants in bg") {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：附近存在可乘坐的载具
    class VehicleNearTrigger : public Trigger
    {
    public:
        VehicleNearTrigger(PlayerbotAI* ai) : Trigger(ai, "vehicle near", 10) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：机器人当前正位于载具内
    class InVehicleTrigger : public Trigger, public Qualified
    {
    public:
        InVehicleTrigger(PlayerbotAI* ai) : Trigger(ai, "in vehicle"), Qualified() {}

    public:
        virtual bool IsActive() override;
    };
}
