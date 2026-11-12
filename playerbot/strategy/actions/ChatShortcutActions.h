#pragma once
#include "MovementActions.h"
#include "GenericActions.h"

namespace ai
{
    /// 返回点重置基类动作：切换移动模式时保存或清除机器人的返回基准点
    class ReturnPositionResetAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化返回点重置基类动作
        ReturnPositionResetAction(PlayerbotAI* ai, std::string name) : ChatCommandAction(ai, name) {}
        /// 重置指定的策略坐标锚点
        void ResetPosition(std::string posName = "return");
        /// 保存当前或指定坐标到命名位置记录
        void SetPosition(WorldPosition pos, std::string posName = "return");
        /// 输出指定状态下的已启用策略列表
        static void PrintStrategies(PlayerbotAI* ai, Event& event);
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（返回点重置基类动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 跟随指令快捷动作：快速切换机器人至跟随主人移动模式
    class FollowChatShortcutAction : public MovementAction
    {
    public:
        /// 构造函数：初始化跟随指令快捷动作
        FollowChatShortcutAction(PlayerbotAI* ai) : MovementAction(ai, "follow chat shortcut") {}
        /// 执行动作主逻辑（跟随指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（跟随指令快捷动作）
        virtual bool isPossible() override { return true; }
        /// 判断当前状态下该动作是否可用/有效（跟随指令快捷动作）
        virtual bool isUseful() override { return true; }
    };

    /// 原地待命指令快捷动作：快速将机器人切换为原地停留策略
    class StayChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化原地待命指令快捷动作
        StayChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "stay chat shortcut") {}
        /// 执行动作主逻辑（原地待命指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（原地待命指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 警戒守卫指令快捷动作：快速切换机器人至定点警戒守卫模式
    class GuardChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化警戒守卫指令快捷动作
        GuardChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "guard chat shortcut") {}
        /// 执行动作主逻辑（警戒守卫指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（警戒守卫指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 自由活动指令快捷动作：解除限制并让机器人进入自由行动模式
    class FreeChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化自由活动指令快捷动作
        FreeChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "free chat shortcut") {}
        /// 执行动作主逻辑（自由活动指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自由活动指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 漫步游荡指令快捷动作：让机器人在当前位置附近随机游荡
    class WanderChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化漫步游荡指令快捷动作
        WanderChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "wander chat shortcut") {}
        /// 执行动作主逻辑（漫步游荡指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（漫步游荡指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 撤退指令快捷动作：命令机器人脱离当前战斗并执行撤退
    class FleeChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化撤退指令快捷动作
        FleeChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "flee chat shortcut") {}
        /// 执行动作主逻辑（撤退指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（撤退指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 解散/避开指令快捷动作：命令机器人远离当前位置或散开站位
    class GoawayChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化解散/避开指令快捷动作
        GoawayChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "runaway chat shortcut") {}
        /// 执行动作主逻辑（解散/避开指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（解散/避开指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 刷怪指令快捷动作：开启自动寻怪练级与打怪策略
    class GrindChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化刷怪指令快捷动作
        GrindChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "grind chat shortcut") {}
        /// 执行动作主逻辑（刷怪指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（刷怪指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 坦克开怪指令快捷动作：命令坦克机器人立即上前攻击目标
    class TankAttackChatShortcutAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化坦克开怪指令快捷动作
        TankAttackChatShortcutAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "tank attack chat shortcut") {}
        /// 执行动作主逻辑（坦克开怪指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（坦克开怪指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 全力输出指令快捷动作：开启最高输出循环策略（max dps）
    class MaxDpsChatShortcutAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化全力输出指令快捷动作
        MaxDpsChatShortcutAction(PlayerbotAI* ai) : ChatCommandAction(ai, "max dps chat shortcut") {}
        /// 执行动作主逻辑（全力输出指令快捷动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（全力输出指令快捷动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
