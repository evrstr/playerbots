/// 原地守卫（Guard）策略实现

#include "playerbot/playerbot.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "GuardStrategy.h"

using namespace ai;

/// 获取非战斗默认动作：检查坐骑状态并驻守警戒点
NextAction** GuardStrategy::GetDefaultNonCombatActions()
{
    return NextAction::array(0, new NextAction("check mount state", 4.0f), new NextAction("guard", 4.0f), NULL);
}


/// 获取战斗默认动作：复用守卫警戒默认动作
NextAction** GuardStrategy::GetDefaultCombatActions()
{
    return GuardStrategy::GetDefaultNonCombatActions();
}
