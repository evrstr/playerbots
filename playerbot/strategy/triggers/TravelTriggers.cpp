/// 旅行与传送门触发器实现

#include "playerbot/playerbot.h"
#include "TravelTriggers.h"

#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/TravelMgr.h"
#include "playerbot/ServerFacade.h"
using namespace ai;

/// 检测附近是否有可交互的任务NPC且当前未处于有效旅行任务中
bool HasNearbyQuestTakerTrigger::IsActive()
{
    TravelTarget* target = AI_VALUE(TravelTarget*, "travel target");
    if (target->GetStatus() == TravelStatus::TRAVEL_STATUS_WORK) //We are not currently working on a target. | 当前没有正在执行的目标
        return false;

    if (target->GetExpiredTime() < 2 * MINUTE) //The target was set more than 2 minutes ago. | 目标设定已超过 2 分钟
        return false;

    return AI_VALUE(bool, "has nearby quest taker");
}

/// 检测是否处于诅咒之地黑暗之门区域（Area 72）
bool NearDarkPortalTrigger::IsActive()
{
    return sServerFacade.GetAreaId(bot) == 72;
}

/// 检测是否抵达艾泽拉斯一侧的黑暗之门传送点附近
bool AtDarkPortalAzerothTrigger::IsActive()
{
    if (sServerFacade.GetAreaId(bot) == 72)
    {
        if (sServerFacade.GetDistance2d(bot, -11906.9f, -3208.53f) < 20.0f)
        {
            return true;
        }
    }
    return false;
}

/// 检测是否抵达外域地狱火半岛一侧的黑暗之门传送点附近
bool AtDarkPortalOutlandTrigger::IsActive()
{
    if (sServerFacade.GetAreaId(bot) == 3539)
    {
        if (sServerFacade.GetDistance2d(bot, -248.1939f, 921.919f) < 10.0f)
        {
            return true;
        }
    }
    return false;
}
