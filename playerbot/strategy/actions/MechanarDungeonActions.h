#pragma once
#include "DungeonActions.h"
#include "ChangeStrategyAction.h"
#include "UseItemAction.h"

namespace ai
{
    /// 启用能源舰副本策略动作：开启能源舰副本专用战术策略
    class MechanarEnableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用能源舰副本策略动作
        MechanarEnableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable mechanar strategy", "+mechanar") {}
    };

    /// 禁用能源舰副本策略动作：关闭能源舰副本专用战术策略
    class MechanarDisableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用能源舰副本策略动作
        MechanarDisableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable mechanar strategy", "-mechanar") {}
    };

    /// 启用灵术师塞佩丝蕾战斗策略动作：开启能源舰灵术师首领战策略
    class NethermancerSepethreaEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用灵术师塞佩丝蕾战斗策略动作
        NethermancerSepethreaEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable nethermancer sepethrea fight strategy", "+nethermancer sepethrea") {}
    };

    /// 禁用灵术师塞佩丝蕾战斗策略动作：关闭能源舰灵术师首领战策略
    class NethermancerSepethreaDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用灵术师塞佩丝蕾战斗策略动作
        NethermancerSepethreaDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable nethermancer sepethrea fight strategy", "-nethermancer sepethrea") {}
    };

    /// 远离狂暴烈焰动作：在灵术师战斗中迅速躲避追击自己的火元素（狂暴烈焰）
    class RagingFlamesMoveAwayAction : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离狂暴烈焰动作
        RagingFlamesMoveAwayAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from raging flames", 20481, 21.0f) {}
    };
}
