// 德鲁伊 - 触发器实现文件 (DruidTriggers.cpp)：定义德鲁伊增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "DruidTriggers.h"
#include "DruidActions.h"

using namespace ai;

// 检查触发条件是否激活 (EntanglingRootsKiteTrigger)
bool EntanglingRootsKiteTrigger::IsActive() 
{ 
    if (!DebuffTrigger::IsActive())
        return false;

    if (AI_VALUE(uint8, "attackers count") > 3)
        return false;

    if (!GetTarget()->HasMana())
        return false;

    std::list<ObjectGuid> attackers = context->GetValue<std::list<ObjectGuid>>("attackers")->Get();
    for (std::list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); i++)
    {
        Unit* unit = ai->GetUnit(*i);
        if (!unit || !sServerFacade.IsAlive(unit))
            continue;

        if (ai->HasMyAura("entangling roots", unit))
            return false;
    }

    return !HasMaxDebuffs();
}

// LifebloomTankTrigger::GetTargetValue 获取相关配置或目标
Value<ObjectGuid>* LifebloomTankTrigger::GetTargetValue()
{
    return context->GetValue<ObjectGuid>("party tank without lifebloom", "lifebloom");
}
