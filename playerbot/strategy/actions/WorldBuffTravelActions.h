#pragma once
#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "UseMeetingStoneAction.h"
#include "playerbot/strategy/generic/WorldBuffTravelStrategy.h"

namespace ai
{
    /// 世界增益旅行自动套用动作：到达世界增益节点后触发对应世界 Buff 获取逻辑
    class WorldBuffTravelApplyAction : public Action
    {
    public:
        /// 构造函数：初始化世界增益旅行自动套用动作
        WorldBuffTravelApplyAction(PlayerbotAI* ai)
            : Action(ai, "world buff travel apply") {
        }

        /// 执行动作主逻辑（世界增益旅行自动套用动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（世界增益旅行自动套用动作）
        bool isUseful() override { return true; }

    private:
        /// 为世界增益旅行当前阶段施加对应的世界增益 Buff
        void ApplyBuffsForStep(WorldBuffTravelStep step);
        /// 为自身以及队伍中的真实玩家同步施加指定增益效果
        void ApplyBuffToSelfAndRealPlayers(uint32 spellId);
        /// 跟随主人同步搭乘飞行坐骑航线
        bool TakeFlightFromMaster(uint32 npcEntry, uint32 destTaxiNode);
        /// 推进世界增益旅行流程至下一阶段步骤
        void AdvanceStep();

        /// 在集合步骤中尝试使用术士召唤距离过远的队友
        bool TrySummonFarAwayMembers(WorldBuffTravelStep step);
    };

    /// 世界增益旅行设定目标动作：根据当前行程阶段设置下一个世界增益收集旅行目的地
    class WorldBuffTravelSetTargetAction : public MovementAction
    {
    public:
        /// 构造函数：初始化世界增益旅行设定目标动作
        WorldBuffTravelSetTargetAction(PlayerbotAI* ai)
            /// 构造函数：初始化移动动作基类
            : MovementAction(ai, "world buff travel set target") {
        }

        /// 执行动作主逻辑（世界增益旅行设定目标动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（世界增益旅行设定目标动作）
        bool isUseful() override { return true; }
    };

    /// 获取轻歌花增益动作：前往费伍德森林寻找并采集净化的轻歌花获取暴击全属性增益
    class WorldBuffTravelSongflowerAction : public MovementAction
    {
    public:
        /// 构造函数：初始化获取轻歌花增益动作
        WorldBuffTravelSongflowerAction(PlayerbotAI* ai)
            /// 构造函数：初始化移动动作基类
            : MovementAction(ai, "world buff travel songflower") {
        }

        /// 执行动作主逻辑（获取轻歌花增益动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（获取轻歌花增益动作）
        bool isUseful() override { return true; }

    private:
        /// 为自身以及队伍中的真实玩家同步施加指定增益效果
        void ApplyBuffToSelfAndRealPlayers(uint32 spellId);
    };

    /// 厄运之槌增益获取确认动作：检测厄运北完美贡品 Buff 是否获取成功
    class WorldBuffTravelDMBuffedAction : public Action
    {
    public:
        /// 构造函数：初始化厄运之槌增益获取确认动作
        WorldBuffTravelDMBuffedAction(PlayerbotAI* ai)
            : Action(ai, "world buff travel dm buffed") {
        }

        /// 执行动作主逻辑（厄运之槌增益获取确认动作）
        bool Execute(Event& event) override;
    };

    /// 厄运之槌撤离完成确认动作：确认机器人已成功退出厄运之槌副本
    class WorldBuffTravelDMExitedAction : public Action
    {
    public:
        /// 构造函数：初始化厄运之槌撤离完成确认动作
        WorldBuffTravelDMExitedAction(PlayerbotAI* ai)
            : Action(ai, "world buff travel dm exited") {
        }

        /// 执行动作主逻辑（厄运之槌撤离完成确认动作）
        bool Execute(Event& event) override;
    };

    /// 厄运之槌法师开门动作：法师在厄运之槌出口处开启返回主城的传送门
    class WorldBuffTravelDMCastPortalAction : public Action
    {
    public:
        /// 构造函数：初始化厄运之槌法师开门动作
        WorldBuffTravelDMCastPortalAction(PlayerbotAI* ai)
            : Action(ai, "world buff travel dm cast portal") {
        }

        /// 执行动作主逻辑（厄运之槌法师开门动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（厄运之槌法师开门动作）
        bool isUseful() override;
    };

    /// 厄运之槌乘传送门动作：队伍成员点击并使用法师开启的传送门离开厄运区域
    class WorldBuffTravelDMTakePortalAction : public MovementAction
    {
    public:
        /// 构造函数：初始化厄运之槌乘传送门动作
        WorldBuffTravelDMTakePortalAction(PlayerbotAI* ai)
            /// 构造函数：初始化移动动作基类
            : MovementAction(ai, "world buff travel dm take portal") {
        }

        /// 执行动作主逻辑（厄运之槌乘传送门动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（厄运之槌乘传送门动作）
        bool isUseful() override { return true; }
    };

    /// 世界增益法师开门动作：在主城或集合点为队伍开启前往下一世界增益站点的传送门
    class WorldBuffTravelCastPortalAction : public Action
    {
    public:
        /// 构造函数：初始化世界增益法师开门动作
        WorldBuffTravelCastPortalAction(PlayerbotAI* ai)
            : Action(ai, "world buff travel cast portal") {
        }

        /// 执行动作主逻辑（世界增益法师开门动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（世界增益法师开门动作）
        bool isUseful() override;
    };

    /// 世界增益乘传送门动作：队伍成员点击法师开启的传送门前往下一站
    class WorldBuffTravelTakePortalAction : public MovementAction
    {
    public:
        /// 构造函数：初始化世界增益乘传送门动作
        WorldBuffTravelTakePortalAction(PlayerbotAI* ai)
            /// 构造函数：初始化移动动作基类
            : MovementAction(ai, "world buff travel take portal") {
        }

        /// 执行动作主逻辑（世界增益乘传送门动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（世界增益乘传送门动作）
        bool isUseful() override { return true; }
    };

    /// 完成世界增益行程动作：所有世界增益收集完毕后结束行程并恢复常规策略
    class WorldBuffTravelFinishAction : public Action
    {
    public:
        /// 构造函数：初始化完成世界增益行程动作
        WorldBuffTravelFinishAction(PlayerbotAI* ai)
            : Action(ai, "world buff travel finish") {
        }

        /// 执行动作主逻辑（完成世界增益行程动作）
        bool Execute(Event& event) override;
    };
}
