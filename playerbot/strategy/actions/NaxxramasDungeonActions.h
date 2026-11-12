#pragma once
#include "DungeonActions.h"
#include "ChangeStrategyAction.h"
#include "UseItemAction.h"

namespace ai
{
    /// 启用纳克萨玛斯副本策略动作：开启纳克萨玛斯团队副本专用战术策略
    class NaxxramasEnableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用纳克萨玛斯副本策略动作
        NaxxramasEnableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable naxxramas strategy", "+naxxramas") {}
    };

    /// 禁用纳克萨玛斯副本策略动作：关闭纳克萨玛斯团队副本专用战术策略
    class NaxxramasDisableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用纳克萨玛斯副本策略动作
        NaxxramasDisableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable naxxramas strategy", "-naxxramas") {}
    };

    /// 启用天启四骑士战斗策略动作：开启纳克萨玛斯天启四骑士首领战换坦换位策略
    class FourHorsemanEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用天启四骑士战斗策略动作
        FourHorsemanEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable four horseman fight strategy", "+four horseman") {}
    };

    /// 禁用天启四骑士战斗策略动作：关闭天启四骑士首领战策略
    class FourHorsemanDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用天启四骑士战斗策略动作
        FourHorsemanDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable four horseman fight strategy", "-four horseman") {}
    };
}
