#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 传送指令动作：使用传送门、炉石或法术将机器人传送至指定地点或主城
    class TeleportAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化传送指令动作
        TeleportAction(PlayerbotAI* ai) : ChatCommandAction(ai, "teleport") {}
        /// 执行动作主逻辑（传送指令动作）
        virtual bool Execute(Event& event) override;
    };
}
