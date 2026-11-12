/// 近战战斗、绕背与追击跳跃策略实现

#include "playerbot/playerbot.h"
#include "MeleeCombatStrategy.h"

using namespace ai;

/// 初始化近战战斗触发器：超出近战距离时靠近目标，贴身重叠时微调拉开
void MeleeCombatStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", static_cast<float>(ACTION_NORMAL) + 8.0f), NULL)));
}

/// 初始化绕背战斗触发器（默认禁用，由职业战斗姿态管理绕背）
void SetBehindCombatStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    /* Disabled by default. Bots can use proper 'combat stances' to position themselves behind targets.
    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("set behind", ACTION_HIGH), NULL)));
    */
}

/// 初始化追击跳跃非战斗触发器：追击远处目标时伴随跳跃
void ChaseJumpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("jump::chase", static_cast<float>(ACTION_MOVE) + 9.0f), NULL)));
}

/// 初始化追击跳跃战斗触发器
void ChaseJumpStrategy::InitCombatTriggers(std::list<TriggerNode *> &triggers)
{
    InitNonCombatTriggers(triggers);
}

/// 初始化追击跳跃反应触发器
void ChaseJumpStrategy::InitReactionTriggers(std::list<TriggerNode *> &triggers)
{
    InitNonCombatTriggers(triggers);
}
