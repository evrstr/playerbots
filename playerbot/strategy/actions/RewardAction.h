#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 选择任务奖励动作：在对话或命令交互中领取指定的任务奖励
    class RewardAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化选择任务奖励动作
        RewardAction(PlayerbotAI* ai) : ChatCommandAction(ai, "reward") {}
        /// 执行动作主逻辑（选择任务奖励动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 提交任务并领取指定的任务奖励
        bool Reward(Player* requester, uint32 itemId, Object* pNpc);
    };
}
