#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 汇报声望指令动作：查询并向主人输出机器人与各阵营的声望等级
    class TellReputationAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化汇报声望指令动作
        TellReputationAction(PlayerbotAI* ai) : ChatCommandAction(ai, "reputation") {}
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（汇报声望指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 执行动作主逻辑（汇报声望指令动作）
        bool Execute(Event& event) override;
    };
}
