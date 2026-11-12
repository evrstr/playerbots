#pragma once
#include "playerbot/LootObjectStack.h"
#include "GenericActions.h"

namespace ai
{
    /// 移动风格指令动作：配置机器人的移动模式与走位习惯（如寻路、跟随方式）
    class MoveStyleAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化移动风格指令动作
        MoveStyleAction(PlayerbotAI* ai) : ChatCommandAction(ai, "move style") {}
        /// 执行动作主逻辑（移动风格指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（移动风格指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
