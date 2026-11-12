#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 任务奖励查询指令动作：列出并选择当前可交付任务的奖励物品
    class QuestRewardAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化任务奖励查询指令动作
        QuestRewardAction(PlayerbotAI* ai) : ChatCommandAction(ai, "quest reward") {}
        /// 执行动作主逻辑（任务奖励查询指令动作）
        virtual bool Execute(Event& event) override;
    };
}
