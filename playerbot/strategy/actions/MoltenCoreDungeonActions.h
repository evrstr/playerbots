#pragma once
#include "DungeonActions.h"
#include "ChangeStrategyAction.h"
#include "UseItemAction.h"

namespace ai
{
    /// 启用熔火之心副本策略动作：开启熔火之心团队副本专用战术策略
    class MoltenCoreEnableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用熔火之心副本策略动作
        MoltenCoreEnableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable molten core strategy", "+molten core") {}
    };

    /// 禁用熔火之心副本策略动作：关闭熔火之心团队副本专用战术策略
    class MoltenCoreDisableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用熔火之心副本策略动作
        MoltenCoreDisableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable molten core strategy", "-molten core") {}
    };

    /// 启用玛格曼达战斗策略动作：开启熔火之心玛格曼达首领战策略
    class MagmadarEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用玛格曼达战斗策略动作
        MagmadarEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable magmadar fight strategy", "+magmadar") {}
    };

    /// 禁用玛格曼达战斗策略动作：关闭玛格曼达首领战策略
    class MagmadarDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用玛格曼达战斗策略动作
        MagmadarDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable magmadar fight strategy", "-magmadar") {}
    };

    /// 远离玛格曼达熔岩炸弹动作：躲避玛格曼达喷吐到地面的灼烧熔岩区域
    class MagmadarMoveAwayFromLavaBombAction : public MoveAwayFromHazard
    {
    public:
        /// 构造函数：初始化远离玛格曼达熔岩炸弹动作
        MagmadarMoveAwayFromLavaBombAction(PlayerbotAI* ai) : MoveAwayFromHazard(ai, "move away from magmadar lava bomb") {}
    };

    /// 远离玛格曼达动作：在需要避开首领正面喷吐或狂暴时拉开距离
    class MagmadarMoveAwayAction : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离玛格曼达动作
        MagmadarMoveAwayAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from magmadar", 11982, 31.0f) {}
    };

    /// 前往熔火之心符文动作：引导机器人移动至需要熄灭的熔火之心守护符文处
    class MoveToMCRuneAction : public MoveToAction
    {
    public:
        /// 构造函数：初始化前往熔火之心符文动作
        MoveToMCRuneAction(PlayerbotAI* ai) : MoveToAction(ai, "move to mc rune") { qualifier = "entry filter::{gos in sight,mc runes}"; }
    };

    /// 使用水之精萃熄灭符文动作：使用一次性水之精萃浇灭熔火之心符文
    class DouseMCRuneActionAqual : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用水之精萃熄灭符文动作
        DouseMCRuneActionAqual(PlayerbotAI* ai) : UseItemIdAction(ai, "douse mc rune aqual") { qualifier = "{17333,entry filter::{gos close,mc runes}}"; }
    };

    /// 使用永恒水之精萃熄灭符文动作：使用可重复使用的永恒水之精萃浇灭熔火之心符文
    class DouseMCRuneActionEternal : public UseItemIdAction
    {
    public:
        /// 构造函数：初始化使用永恒水之精萃熄灭符文动作
        DouseMCRuneActionEternal(PlayerbotAI* ai) : UseItemIdAction(ai, "douse mc rune eternal") { qualifier = "{22754,entry filter::{gos close,mc runes}}"; }
    };
}
