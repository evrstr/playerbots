// 潜行者 - 触发器实现文件 (RogueTriggers.cpp)：定义潜行者增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "RogueTriggers.h"
#include "RogueActions.h"

using namespace ai;

// 检查触发条件是否激活 (RiposteCastTrigger)
bool RiposteCastTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    bool isMelee = true;
    if (target->IsPlayer())
    {
        isMelee = !ai->IsRanged((Player*)target);
    }

    return SpellCanBeCastedTrigger::IsActive() && isMelee;
}
