#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 汇报目标指令动作：告知主人机器人当前选中的目标及其状态
    class TellTargetAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化汇报目标指令动作
        TellTargetAction(PlayerbotAI* ai) : ChatCommandAction(ai, "tell target") {}
        /// 执行动作主逻辑（汇报目标指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（汇报目标指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 汇报攻击者指令动作：列出当前正在攻击机器人或队伍的敌对目标
    class TellAttackersAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化汇报攻击者指令动作
        TellAttackersAction(PlayerbotAI* ai) : ChatCommandAction(ai, "tell attackers") {}
        /// 执行动作主逻辑（汇报攻击者指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（汇报攻击者指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 汇报潜在攻击目标动作：列出附近所有可供选择攻击的敌对单位
    class TellPossibleAttackTargetsAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化汇报潜在攻击目标动作
        TellPossibleAttackTargetsAction(PlayerbotAI* ai) : ChatCommandAction(ai, "tell possible attack targets") {}
        /// 执行动作主逻辑（汇报潜在攻击目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（汇报潜在攻击目标动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
