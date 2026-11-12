// 策略值实现：MasterTargetValue（获取主控目标 GUID）

#include "playerbot/playerbot.h"
#include "MasterTargetValue.h"
#include "TargetValue.h"

using namespace ai;

// 返回 ai->GetGroupMaster() 的 GUID
ObjectGuid MasterTargetValue::Calculate()
{
    return ai->GetGroupMaster() ? ai->GetGroupMaster()->GetObjectGuid() : ObjectGuid();
}