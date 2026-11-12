#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"

namespace ai
{
    /// 跟随目标动作：控制机器人按阵型与设定距离跟随主人或指定目标
    class FollowAction : public MovementAction {
    public:
        /// 构造函数：初始化跟随目标动作
        FollowAction(PlayerbotAI* ai, std::string name = "follow") : MovementAction(ai, name) {}
        /// 执行动作主逻辑（跟随目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（跟随目标动作）
        virtual bool isUseful() override;
        /// 判断死亡灵魂状态下是否允许继续跟随主人
        virtual bool CanDeadFollow(Unit* target);
    };

    /// 停止跟随动作：停止当前跟随移动生成器并保持原地
    class StopFollowAction : public MovementAction {
    public:
        /// 构造函数：初始化停止跟随动作
        StopFollowAction(PlayerbotAI* ai, std::string name = "stop follow") : MovementAction(ai, name) {}
        /// 执行动作主逻辑（停止跟随动作）
        virtual bool Execute(Event& event) override { ai->StopMoving(); return true; }
        /// 判断当前状态下该动作是否可用/有效（停止跟随动作）
        virtual bool isUseful() override;
    };

    /// 逃向主人动作：遇到危险时向主人所在位置撤退靠拢
    class FleeToMasterAction : public FollowAction {
    public:
        /// 构造函数：初始化逃向主人动作
        FleeToMasterAction(PlayerbotAI* ai) : FollowAction(ai, "flee to master") {}

        /// 执行动作主逻辑（逃向主人动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（逃向主人动作）
        virtual bool isUseful() override;
    };

}
