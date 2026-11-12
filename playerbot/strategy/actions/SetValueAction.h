#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 设置策略值指令动作：通过聊天命令直接读取或修改机器人 AI 黑板值
    class SetValueAction: public ChatCommandAction
    {
    public:
        /// 构造函数：初始化设置策略值指令动作
        SetValueAction(PlayerbotAI* ai) : ChatCommandAction(ai, "set value") {}
        /// 执行动作主逻辑（设置策略值指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置策略值指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
