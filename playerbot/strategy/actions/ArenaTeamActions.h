#pragma once
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 接受竞技场战队邀请动作：自动响应并接受竞技场战队邀请
    class ArenaTeamAcceptAction : public Action 
    {
    public:
        /// 构造函数：初始化接受竞技场战队邀请动作
        ArenaTeamAcceptAction(PlayerbotAI* ai) : Action(ai, "arena team accept") {}
        /// 执行动作主逻辑（接受竞技场战队邀请动作）
        virtual bool Execute(Event& event) override;
    };
}
