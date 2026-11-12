#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 接受公会邀请动作：收到公会邀请时自动接受加入并初始化公会备注
    class GuildAcceptAction : public Action {
    public:
        /// 构造函数：初始化接受公会邀请动作
        GuildAcceptAction(PlayerbotAI* ai) : Action(ai, "guild accept") {}
        /// 执行动作主逻辑（接受公会邀请动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（接受公会邀请动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
