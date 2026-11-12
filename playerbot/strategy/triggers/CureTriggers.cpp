/// 驱散与世界增益触发器实现

#include "playerbot/playerbot.h"
#include "GenericTriggers.h"
#include "CureTriggers.h"
#include "playerbot/strategy/actions/WorldBuffAction.h"

using namespace ai;

/// 检测目标是否拥有可被当前驱散类型清除的光环
bool NeedCureTrigger::IsActive() 
{
    Unit* target = GetTarget();
    return target && ai->HasAuraToDispel(target, dispelType);
}

/// 获取需要驱散的小队成员目标
Value<ObjectGuid>* PartyMemberNeedCureTrigger::GetTargetValue()
{
    return context->GetValue<ObjectGuid>("party member to dispel", dispelType);
}

/// 检测机器人是否缺少所需世界增益
bool NeedWorldBuffTrigger::IsActive()
{
    return !WorldBuffAction::NeedWorldBuffs(bot).empty();   
}
