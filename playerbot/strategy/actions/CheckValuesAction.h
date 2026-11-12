#pragma once

#include "playerbot/strategy/Action.h"
#include "QuestAction.h"

namespace ai
{
    /// 检查状态值动作：周期性检查并触发机器人各状态值的更新或调试输出
    class CheckValuesAction : public Action
    {
    public:
        /// 构造函数：初始化检查状态值动作
        CheckValuesAction(PlayerbotAI* ai);
        /// 执行动作主逻辑（检查状态值动作）
        virtual bool Execute(Event& event) override;
    };
}
