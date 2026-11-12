/// 熔火之心（MC）团队副本及首领策略实现

#include "playerbot/playerbot.h"
#include "MoltenCoreDungeonStrategies.h"
#include "DungeonMultipliers.h"

using namespace ai;

/// 初始化熔火之心战斗触发器：开战玛格曼达时启用对应 Boss 策略
void MoltenCoreDungeonStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "start magmadar fight",
        NextAction::array(0, new NextAction("enable magmadar fight strategy", 100.0f), NULL)));
}

/// 初始化熔火之心非战斗触发器：寻找并熄灭 MC 符文以及补充火抗药水
void MoltenCoreDungeonStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    /*
    triggers.push_back(new TriggerNode(
        "val::and::{"
        "action possible::use id::17333,"
        "has object::go usable filter::go trapped filter::entry filter::{gos in sight,mc runes},"
        "not::has object::entry filter::{gos close,mc runes}"
        "}",
        NextAction::array(0, new NextAction("move to::entry filter::{gos in sight,mc runes}", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "val::has object::go usable filter::entry filter::{gos close,mc runes}",
        NextAction::array(0, new NextAction("use id::{17333,entry filter::{gos close,mc runes}}", 1.0f), NULL)));
        */

    triggers.push_back(new TriggerNode(
        "mc rune in sight",
        NextAction::array(0, new NextAction("move to mc rune", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mc rune close",
        NextAction::array(0,
            new NextAction("douse mc rune eternal", 2.0f),
            new NextAction("douse mc rune aqual", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "fire protection potion ready",
        NextAction::array(0, new NextAction("fire protection potion", 100.0f), NULL)));
}

/// 初始化玛格曼达战斗触发器：远程/治疗保持安全距离并喝火抗药水
void MagmadarFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    Player* bot = ai->GetBot();
    if (ai->IsRanged(bot) || ai->IsHeal(bot))
    {
        triggers.push_back(new TriggerNode(
            "magmadar too close",
            NextAction::array(0, new NextAction("move away from magmadar", 100.0f), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "fire protection potion ready",
        NextAction::array(0, new NextAction("fire protection potion", 100.0f), NULL)));
}

/// 初始化玛格曼达非战斗触发器：脱战后卸载策略
void MagmadarFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end magmadar fight",
        NextAction::array(0, new NextAction("disable magmadar fight strategy", 100.0f), NULL)));
}

/// 初始化玛格曼达死亡触发器
void MagmadarFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end magmadar fight",
        NextAction::array(0, new NextAction("disable magmadar fight strategy", 100.0f), NULL)));
}

/// 初始化玛格曼达反应触发器：躲避熔岩炸弹地面危险区
void MagmadarFightStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "magmadar lava bomb",
        NextAction::array(0, new NextAction("move away from hazard", 100.0f), NULL)));
}

/// 注册玛格曼达战斗乘数：防止远程/治疗靠近施法后立即触发远离机制导致反复横跳
void MagmadarFightStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    Player* bot = ai->GetBot();
    if (ai->IsRanged(bot) || ai->IsHeal(bot))
    {
        multipliers.push_back(new PreventMoveAwayFromCreatureOnReachToCastMultiplier(ai));
    }
}
