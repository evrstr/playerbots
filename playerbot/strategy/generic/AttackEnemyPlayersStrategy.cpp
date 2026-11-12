/// 攻击敌对玩家（PvP）策略实现

#include "playerbot/playerbot.h"
#include "AttackEnemyPlayersStrategy.h"

using namespace ai;

/// 初始化战斗触发器：附近发现敌对玩家时以紧急优先级切换攻击
void AttackEnemyPlayersStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy player near",
        NextAction::array(0, new NextAction("attack enemy player", ACTION_EMERGENCY), NULL)));
}