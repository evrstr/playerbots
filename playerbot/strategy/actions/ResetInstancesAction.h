#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 重置副本指令动作：在副本外时重置机器人当前的所有普通地下城副本进度
    class ResetInstancesAction : public Action 
    {
    public:
        /// 构造函数：初始化重置副本指令动作
        ResetInstancesAction(PlayerbotAI* ai) : Action(ai, "reset instances") {}
        /// 执行动作主逻辑（重置副本指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（重置副本指令动作）
        virtual bool isUseful() override { return ai->GetGroupMaster() == bot; };
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（重置副本指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 重置团队副本指令动作：重置机器人团队副本或特定副本冷却状态
    class ResetRaidsAction : public Action
    {
    public:
        /// 构造函数：初始化重置团队副本指令动作
        ResetRaidsAction(PlayerbotAI* ai) : Action(ai, "reset raids") {}
        /// 执行动作主逻辑（重置团队副本指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（重置团队副本指令动作）
        virtual bool isUseful() override { return true; };
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（重置团队副本指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
