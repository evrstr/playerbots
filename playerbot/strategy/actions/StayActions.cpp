
#include "playerbot/playerbot.h"
#include "StayActions.h"

#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/values/LastMovementValue.h"

using namespace ai;

/// 停止机器人当前所有移动并保持原地待命
bool StayActionBase::Stay(Player* requester)
{
    AI_VALUE(LastMovement&, "last movement").Set(NULL);

    //if (!urand(0, 10)) ai->PlaySound(TEXTEMOTE_YAWN);

    MotionMaster &mm = *bot->GetMotionMaster();
#ifdef CMANGOS
    if (mm.GetCurrentMovementGeneratorType() == TAXI_MOTION_TYPE || bot->IsTaxiFlying())
#endif
#ifdef MANGOS
    if (mm.GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE || bot->IsFlying())
#endif
    {
        if (verbose) ai->TellError(requester, "I can not stay, I'm flying!");
        return false;
    } 

    uint32 sitDelay = sPlayerbotAIConfig.sitDelay / 1000;
    time_t stayTime = AI_VALUE(time_t, "stay time");
    time_t now = time(0);
    if (!stayTime)
    {
        stayTime = now - urand(0, sitDelay / 2);
        context->GetValue<time_t>("stay time")->Set(stayTime);
    }

    if (!sServerFacade.isMoving(bot))
        return false;

    ai->StopMoving();
    bot->clearUnitState(UNIT_STAT_CHASE);
    bot->clearUnitState(UNIT_STAT_FOLLOW);

    return true;
}

/// 执行动作主逻辑（原地待命动作）
bool StayAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    return Stay(requester);
}

/// 判断当前状态下该动作是否可用/有效（原地待命动作）
bool StayAction::isUseful()
{
    return !AI_VALUE2(bool, "moving", "self target");
}

/// 执行动作主逻辑（坐下休息动作）
bool SitAction::Execute(Event& event)
{
    if (sServerFacade.isMoving(bot))
        return false;

    bot->SetStandState(UNIT_STAND_STATE_SIT);
    return true;
}

/// 判断当前状态下该动作是否可用/有效（坐下休息动作）
bool SitAction::isUseful()
{
    return !AI_VALUE2(bool, "moving", "self target");
}
