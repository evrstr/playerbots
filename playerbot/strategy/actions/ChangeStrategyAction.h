#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 修改战斗策略指令动作：增删或重置机器人的战斗状态策略（co）
    class ChangeCombatStrategyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化修改战斗策略指令动作
        ChangeCombatStrategyAction(PlayerbotAI* ai, std::string name = "co") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（修改战斗策略指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（修改战斗策略指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 修改非战斗策略指令动作：增删或重置机器人的非战斗策略（nc）
    class ChangeNonCombatStrategyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化修改非战斗策略指令动作
        ChangeNonCombatStrategyAction(PlayerbotAI* ai, std::string name = "nc") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（修改非战斗策略指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（修改非战斗策略指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 修改死亡策略指令动作：增删或重置机器人的死亡状态策略（de）
    class ChangeDeadStrategyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化修改死亡策略指令动作
        ChangeDeadStrategyAction(PlayerbotAI* ai, std::string name = "de") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（修改死亡策略指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（修改死亡策略指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 修改反应策略指令动作：增删或重置机器人的即时反应策略（react）
    class ChangeReactionStrategyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化修改反应策略指令动作
        ChangeReactionStrategyAction(PlayerbotAI* ai, std::string name = "react") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（修改反应策略指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（修改反应策略指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 修改全状态策略指令动作：同时在所有状态下批量更新指定策略
    class ChangeAllStrategyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化修改全状态策略指令动作
        ChangeAllStrategyAction(PlayerbotAI* ai, std::string name = "change strategy from all", std::string strategy = "") : ChatCommandAction(ai, name), strategy(strategy) {}
        /// 执行动作主逻辑（修改全状态策略指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（修改全状态策略指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        std::string strategy;
    };
}
