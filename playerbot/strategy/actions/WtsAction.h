#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 出售喊话指令动作：在交易或世界频道发送机器人背包物品的出售喊话信息
    class WtsAction : public ChatCommandAction 
    {
    public:
        /// 构造函数：初始化出售喊话指令动作
        WtsAction(PlayerbotAI* ai) : ChatCommandAction(ai, "wts") {}
        /// 执行动作主逻辑（出售喊话指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（出售喊话指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
