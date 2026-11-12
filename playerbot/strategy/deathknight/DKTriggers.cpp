// 死亡骑士 - 触发器实现文件 (DKTriggers.cpp)：定义死亡骑士增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "DKTriggers.h"
#include "DKActions.h"

using namespace ai;

// 检查触发条件是否激活 (DKPresenceTrigger)
bool DKPresenceTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("blood presence", target) &&
        !ai->HasAura("unholy presence", target) &&
        !ai->HasAura("frost presence", target);
}
