#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 雇佣机器人指令动作：处理玩家雇佣或解雇自由机器人的命令与费用结算
    class HireAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化雇佣机器人指令动作
        HireAction(PlayerbotAI* ai) : ChatCommandAction(ai, "hire") {}
        /// 执行动作主逻辑（雇佣机器人指令动作）
        virtual bool Execute(Event& event) override;
    };
}
