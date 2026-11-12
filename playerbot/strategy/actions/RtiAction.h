#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 团队标记指令动作：查询或设置机器人负责攻击/控制的团队目标标记（RTI）
    class RtiAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化团队标记指令动作
        RtiAction(PlayerbotAI* ai) : ChatCommandAction(ai, "rti") {}
        /// 执行动作主逻辑（团队标记指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（团队标记指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 将团队目标标记（RTI）名称或图标文本追加到输出流
        void AppendRti(std::ostringstream & out, std::string type);
    };

    /// 战斗指令目标设置动作：设置机器人当前战斗指令指定的优先目标或坦克对象
    class CombatOrderTargetAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化战斗指令目标设置动作
        CombatOrderTargetAction(PlayerbotAI* ai) : ChatCommandAction(ai, "combat order target") {}
        /// 执行动作主逻辑（战斗指令目标设置动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（战斗指令目标设置动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 自动标记团队目标动作：根据队伍职责或策略自动为当前目标打上团队标记
    class MarkRtiAction : public Action
    {
    public:
        /// 构造函数：初始化自动标记团队目标动作
        MarkRtiAction(PlayerbotAI* ai) : Action(ai, "mark rti") {}
        /// 执行动作主逻辑（自动标记团队目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自动标记团队目标动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
