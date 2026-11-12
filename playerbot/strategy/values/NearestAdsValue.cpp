// 策略值实现：NearestAdsValue（过滤排除当前主目标）

#include "playerbot/playerbot.h"
#include "NearestAdsValue.h"

using namespace ai;

// 排除当前正在攻击的目标，其余交由 PossibleTargetsValue 校验
bool NearestAddsValue::AcceptUnit(Unit* unit)
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    return unit != target && PossibleTargetsValue::AcceptUnit(unit);
}
