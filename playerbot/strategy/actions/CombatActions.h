#pragma once

#include "playerbot/strategy/Action.h"
#include "ChangeStrategyAction.h"

namespace ai
{
    /// 切换近战策略动作：将战斗策略切换为近战输出模式
    class SwitchToMeleeAction : public ChangeCombatStrategyAction
    {
    public:
        /// 构造函数：初始化切换近战策略动作
        SwitchToMeleeAction(PlayerbotAI* ai) : ChangeCombatStrategyAction(ai, "-ranged,+close") {}
        /// 判断当前状态下该动作是否可用/有效（切换近战策略动作）
        bool isUseful() override;
        /// 执行动作主逻辑（切换近战策略动作）
        bool Execute(Event& event) override;
    };

    /// 切换远程策略动作：将战斗策略切换为远程输出模式
    class SwitchToRangedAction : public ChangeCombatStrategyAction
    {
    public:
        /// 构造函数：初始化切换远程策略动作
        SwitchToRangedAction(PlayerbotAI* ai) : ChangeCombatStrategyAction(ai, "-close,+ranged") {}
        /// 判断当前状态下该动作是否可用/有效（切换远程策略动作）
        bool isUseful() override;
        /// 执行动作主逻辑（切换远程策略动作）
        bool Execute(Event& event) override;
    };
}
