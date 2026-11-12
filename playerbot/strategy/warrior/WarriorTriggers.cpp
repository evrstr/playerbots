// 战士 - 触发器实现文件 (WarriorTriggers.cpp)：定义战士增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "WarriorTriggers.h"
#include "WarriorActions.h"

using namespace ai;

// 检查触发条件是否激活 (BloodrageBuffTrigger)
bool BloodrageBuffTrigger::IsActive()
{
    return AI_VALUE2(uint8, "health", "self target") >= sPlayerbotAIConfig.mediumHealth &&
        AI_VALUE2(uint8, "rage", "self target") < 20;
}

// 检查触发条件是否激活 (SunderArmorDebuffTrigger)
bool SunderArmorDebuffTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    if (ai->IsTank(bot) && !target->IsPlayer())
        return true;

    return !ai->HasAura("sunder armor", target, true) && !HasMaxDebuffs();
}

// 检查触发条件是否激活 (CommandingShoutTrigger)
bool CommandingShoutTrigger::IsActive()
{
    uint32 comShout = AI_VALUE2(uint32, "spell id", "commanding shout");
    uint32 batShout = AI_VALUE2(uint32, "spell id", "battle shout");
    if (!(comShout || batShout))
        return false;

    if (bot->HasSpell(comShout))
        return !ai->HasAura("commanding shout", bot);

    if (bot->HasSpell(batShout))
        return !ai->HasAura("battle shout", bot);

    return false;
}
