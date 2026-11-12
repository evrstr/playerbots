#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 安全权限校验动作：在执行交互或接收封包前检查请求者的安全权限等级
    class SecurityCheckAction : public Action
    {
    public:
        /// 构造函数：初始化安全权限校验动作
        SecurityCheckAction(PlayerbotAI* ai) : Action(ai, "security check") {}
        /// 判断当前状态下该动作是否可用/有效（安全权限校验动作）
        virtual bool isUseful() override;
        /// 执行动作主逻辑（安全权限校验动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（安全权限校验动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
