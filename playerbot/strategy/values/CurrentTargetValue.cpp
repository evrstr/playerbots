// 策略值实现：CurrentTargetValue（当前目标读写与视距有效性检查）

#include "playerbot/playerbot.h"
#include "CurrentTargetValue.h"

#include "playerbot/ServerFacade.h"
using namespace ai;

// 获取当前选中目标，若单位无效或超出同地图视距则返回空 GUID
ObjectGuid CurrentTargetValue::Get()
{
    if (selection.IsEmpty())
        return ObjectGuid();

    Unit* unit = sObjectAccessor.GetUnit(*bot, selection);
    if (unit && !bot->IsWithinDistInMap(unit, sPlayerbotAIConfig.sightDistance))
        return ObjectGuid();

    return unit ? unit->GetObjectGuid() : ObjectGuid();
}

// 更新机器人当前选中的目标 GUID
void CurrentTargetValue::Set(ObjectGuid unitGuid)
{
    selection = unitGuid;
}
