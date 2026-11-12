/// 被动（Passive）策略实现

#include "playerbot/playerbot.h"
#include "PassiveStrategy.h"
#include "playerbot/strategy/PassiveMultiplier.h"

using namespace ai;

/// 初始化非战斗乘数：挂载 PassiveMultiplier 屏蔽主动攻击/移动行为
void PassiveStrategy::InitNonCombatMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new PassiveMultiplier(ai));
}

/// 初始化战斗乘数：复用非战斗被动乘数
void PassiveStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    InitNonCombatMultipliers(multipliers);
}