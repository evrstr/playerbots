#pragma once
#include "DungeonActions.h"
#include "ChangeStrategyAction.h"

namespace ai
{
    /// 启用奥妮克希亚巢穴策略动作：开启奥妮克希亚巢穴副本战术策略
    class OnyxiasLairEnableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用奥妮克希亚巢穴策略动作
        OnyxiasLairEnableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable onyxias lair strategy", "+onyxias lair") {}
    };

    /// 禁用奥妮克希亚巢穴策略动作：关闭奥妮克希亚巢穴副本战术策略
    class OnyxiasLairDisableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用奥妮克希亚巢穴策略动作
        OnyxiasLairDisableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable onyxias lair strategy", "-onyxias lair") {}
    };

    /// 启用奥妮克希亚战斗策略动作：开启黑龙公主首领战阶段应对策略
    class OnyxiaEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用奥妮克希亚战斗策略动作
        OnyxiaEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable onyxia fight strategy", "+onyxia") {}
    };

    /// 禁用奥妮克希亚战斗策略动作：关闭黑龙公主首领战策略
    class OnyxiaDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用奥妮克希亚战斗策略动作
        OnyxiaDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable onyxia fight strategy", "-onyxia") {}
    };
}
