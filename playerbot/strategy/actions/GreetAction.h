#pragma once

#include "playerbot/strategy/Action.h"
#include "QuestAction.h"
#include "UseItemAction.h"

namespace ai
{
    /// 问候动作：遇到附近玩家或新入队成员时发送问候表情或话语
    class GreetAction : public Action
    {
    public:
        /// 构造函数：初始化问候动作
        GreetAction(PlayerbotAI* ai);
        /// 执行动作主逻辑（问候动作）
        virtual bool Execute(Event& event) override;
    };
}
