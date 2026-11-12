#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 设置重点治疗目标动作：配置治疗机器人优先关注的重点治疗玩家列表
    class SetFocusHealTargetsAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化设置重点治疗目标动作
        SetFocusHealTargetsAction(PlayerbotAI* ai, std::string name = "focus heal targets") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（设置重点治疗目标动作）
        bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置重点治疗目标动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 设置等待开怪时间动作：配置坦克开怪后输出职业等待建立仇恨的延迟秒数
    class SetWaitForAttackTimeAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化设置等待开怪时间动作
        SetWaitForAttackTimeAction(PlayerbotAI* ai, std::string name = "wait for attack time") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（设置等待开怪时间动作）
        bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置等待开怪时间动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 设置跟随目标动作：指定机器人跟随模式的目标玩家
    class SetFollowTargetAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化设置跟随目标动作
        SetFollowTargetAction(PlayerbotAI* ai, std::string name = "follow target") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（设置跟随目标动作）
        bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置跟随目标动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 设置法术目标基类动作：通过命令配置特定法术（激活/复活/增益等）的指定施法目标
    class SetSpellTargetAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化设置法术目标基类动作
        SetSpellTargetAction(PlayerbotAI* ai, std::string name) : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（设置法术目标基类动作）
        bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置法术目标基类动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 设置激活/灌注目标动作：配置德鲁伊激活、牧师能量灌注等辅助技能的优先目标
    class SetBoostTargetsAction : public SetSpellTargetAction
    {
    public:
        /// 构造函数：初始化设置激活/灌注目标动作
        SetBoostTargetsAction(PlayerbotAI* ai) : SetSpellTargetAction(ai, "boost targets") {}
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置激活/灌注目标动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 设置复活优先目标动作：配置战斗中战复或战后复活的优先目标列表
    class SetReviveTargetsAction : public SetSpellTargetAction
    {
    public:
        /// 构造函数：初始化设置复活优先目标动作
        SetReviveTargetsAction(PlayerbotAI* ai) : SetSpellTargetAction(ai, "revive targets") {}
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置复活优先目标动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 设置单体增益目标动作：配置需要单独施放特定增益法术的玩家目标列表
    class SetBuffTargetsAction : public SetSpellTargetAction
    {
    public:
        /// 构造函数：初始化设置单体增益目标动作
        SetBuffTargetsAction(PlayerbotAI* ai) : SetSpellTargetAction(ai, "buff targets") {}
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（设置单体增益目标动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
