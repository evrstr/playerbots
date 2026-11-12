// 策略值实现：InvalidTargetValue（目标合法性与脱战失效判定）

#include "playerbot/playerbot.h"
#include "InvalidTargetValue.h"
#include "PossibleAttackTargetsValue.h"
#include "EnemyPlayerValue.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

// 检查目标是否在同地图世界内、是否为决斗对象、选中状态是否匹配及攻击合法性
bool InvalidTargetValue::Calculate()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));
    if (!target || !target->IsInWorld() || target->GetMapId() != bot->GetMapId())
    {
        return true;
    }

    Unit* duelTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "duel target"));
    if (duelTarget && duelTarget == target)
    {
        return false;
    }

    if (qualifier == "current target")
    {
        if (target->GetObjectGuid() != bot->GetSelectionGuid())
        {
            return true;
        }
    }

    const bool validTarget = PossibleAttackTargetsValue::IsValid(target, bot);
    if (!validTarget)
    {
        std::list<ObjectGuid> attackers = AI_VALUE(std::list<ObjectGuid>, "possible attack targets");
        if (std::find(attackers.begin(), attackers.end(), target->GetObjectGuid()) != attackers.end())
        {
            return false;
        }
    }

    return !validTarget;
}