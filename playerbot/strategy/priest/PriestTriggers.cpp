// 牧师 - 触发器实现文件 (PriestTriggers.cpp)：定义牧师增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "PriestTriggers.h"
#include "PriestActions.h"

using namespace ai;

// 检查触发条件是否激活 (InnerFireTrigger)
bool InnerFireTrigger::IsActive()
{
    Unit* target = GetTarget();
    return SpellTrigger::IsActive() && !ai->HasAura(spell, target);
}

// 检查触发条件是否激活 (ShadowformTrigger)
bool ShadowformTrigger::IsActive()
{
    return !ai->HasAura("shadowform", bot);
}

// 检查触发条件是否激活 (ShadowfiendTrigger)
bool ShadowfiendTrigger::IsActive()
{
    return BoostTrigger::IsActive() && bot->IsSpellReady(34433);
}

// 检查触发条件是否激活 (InnerFocusTrigger)
bool InnerFocusTrigger::IsActive()
{
    return BoostTrigger::IsActive() && bot->IsSpellReady(14751);
}
