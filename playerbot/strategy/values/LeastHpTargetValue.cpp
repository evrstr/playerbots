// 策略值实现：LeastHpTargetValue（最低血量目标查找）

#include "playerbot/playerbot.h"
#include "LeastHpTargetValue.h"
#include "TargetValue.h"

using namespace ai;

// 应用 FindLeastHpTargetStrategy 查找当前血量最少的有效敌对单位
ObjectGuid LeastHpTargetValue::Calculate()
{
    FindLeastHpTargetStrategy strategy(ai);
    Unit* target = FindTarget(&strategy);
    return target ? target->GetObjectGuid() : ObjectGuid();
}
