/// 拾取相关触发器实现

#include "playerbot/playerbot.h"
#include "LootTriggers.h"
#include "playerbot/LootObjectStack.h"
#include "playerbot/strategy/values/FreeMoveValues.h"

#include "playerbot/ServerFacade.h"
using namespace ai;

/// 检测是否有可拾取战利品（且不在战斗/骑乘中，并处于交互距离或无目标）
bool LootAvailableTrigger::IsActive()
{
    return AI_VALUE(bool, "has available loot") &&
            (
                    sServerFacade.IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "loot target"), INTERACTION_DISTANCE) ||
                    AI_VALUE(std::list<ObjectGuid>, "all targets").empty()
            ) &&
            !AI_VALUE2(bool, "combat", "self target") &&
            !AI_VALUE2(bool, "mounted", "self target");
}

/// 检测是否距离当前战利品目标过远且可自由移动前往
bool FarFromCurrentLootTrigger::IsActive()
{
    LootObject loot = AI_VALUE(LootObject, "loot target");

    if (!loot.IsLootPossible(bot))
        return false;

    if (WorldObject* wo = loot.GetWorldObject(bot))
    {
        if (!CanFreeMoveValue::CanFreeMoveTo(ai, WorldPosition(wo)))
            return false;
    }

    return AI_VALUE2(float, "distance", "loot target") > INTERACTION_DISTANCE;
}

/// 检测机器人当前是否处于可拾取状态
bool CanLootTrigger::IsActive()
{
    return AI_VALUE(bool, "can loot");
}
