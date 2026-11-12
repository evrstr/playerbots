#pragma once
#include "MovementActions.h"
#include "GenericActions.h"

namespace ai
{
    /// 位置控制指令动作：设置、查询或移动至机器人的自定义战术站位点
    class PositionAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化位置控制指令动作
        PositionAction(PlayerbotAI* ai) : ChatCommandAction(ai, "position") {}
        /// 执行动作主逻辑（位置控制指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（位置控制指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 移动到指定位置动作：移动至当前设置的自定义位置锚点
    class MoveToPositionAction : public MovementAction
    {
    public:
        /// 构造函数：初始化移动到指定位置动作
        MoveToPositionAction(PlayerbotAI* ai, std::string name, std::string qualifier, bool idle = false) : MovementAction(ai, name), qualifier(qualifier), idle(idle) {}
        /// 执行动作主逻辑（移动到指定位置动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（移动到指定位置动作）
        virtual bool isUseful() override;

    protected:
        std::string qualifier;
        bool idle;
    };

    /// 警戒守卫位置动作：移动并坚守在配置的警戒守卫点位
    class GuardAction : public MoveToPositionAction
    {
    public:
        /// 构造函数：初始化警戒守卫位置动作
        GuardAction(PlayerbotAI* ai) : MoveToPositionAction(ai, "move to position", "guard") {}
        /// 判断当前状态下该动作是否可用/有效（警戒守卫位置动作）
        virtual bool isUseful() override;
    };

    /// 设置返回点动作：记录机器人当前坐标作为战斗或行动后的返回基准点
    class SetReturnPositionAction : public Action
    {
    public:
        /// 构造函数：初始化设置返回点动作
        SetReturnPositionAction(PlayerbotAI* ai) : Action(ai, "set return position") {}
        /// 执行动作主逻辑（设置返回点动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（设置返回点动作）
        virtual bool isUseful() override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置返回点动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 返回基准点动作：脱离战斗或完成动作后返回先前保存的返回坐标点
    class ReturnAction : public MoveToPositionAction
    {
    public:
        /// 构造函数：初始化返回基准点动作
        ReturnAction(PlayerbotAI* ai) : MoveToPositionAction(ai, "return", "return", true) {}
        /// 判断当前状态下该动作是否可用/有效（返回基准点动作）
        virtual bool isUseful() override;
    };

    /// 返回停留点动作：回到配置的原地停留位置
    class ReturnToStayPositionAction : public MoveToPositionAction
    {
    public:
        /// 构造函数：初始化返回停留点动作
        ReturnToStayPositionAction(PlayerbotAI* ai) : MoveToPositionAction(ai, "move to position", "stay") {}
        /// 判断执行该动作的前置条件是否满足（返回停留点动作）
        virtual bool isPossible() override;
    };

    /// 返回拉怪点动作：在完成拉怪后跑回预设的拉怪集合点
    class ReturnToPullPositionAction : public MoveToPositionAction
    {
    public:
        /// 构造函数：初始化返回拉怪点动作
        ReturnToPullPositionAction(PlayerbotAI* ai) : MoveToPositionAction(ai, "return to pull position", "pull") {}
        /// 判断执行该动作的前置条件是否满足（返回拉怪点动作）
        virtual bool isPossible() override;
    };
}
