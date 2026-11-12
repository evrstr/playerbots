/// PvP、战场与载具相关触发器实现

#include "playerbot/playerbot.h"
#include "PvpTriggers.h"
#include "playerbot/ServerFacade.h"
#include "BattleGround/BattleGroundWS.h"
#include "playerbot/strategy/values/PositionValue.h"
#ifndef MANGOSBOT_ZERO
#include "BattleGround/BattleGroundEY.h"
#endif

using namespace ai;

/// 检测附近是否存在更优的敌对玩家攻击目标
bool EnemyPlayerNear::IsActive()
{
    // Check if we have any enemy players to attack | 检查是否有可攻击的敌对玩家目标
    if(AI_VALUE(bool, "has enemy player targets"))
    {
        Unit* currentTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
        if (currentTarget)
        {
            // Check if we have a better enemy player to attack | 检查是否有更适合攻击的敌对玩家目标
            Player* currentPlayerTarget = dynamic_cast<Player*>(currentTarget);
            if(currentPlayerTarget)
            {
                return currentPlayerTarget != ai->GetUnit(AI_VALUE(ObjectGuid, "enemy player target"));
            }
        }

        return true;
    }

    return false;
}

/// 检测在战歌峡谷中机器人是否未持有旗帜
bool PlayerHasNoFlag::IsActive()
{
#ifdef MANGOS
    if (ai->GetBot()->InBattleGround())
    {
        if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
        {
            BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();
            if (!(bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_PLAYER))
                return true;
            if (bot->GetObjectGuid() == bg->GetAllianceFlagCarrierGuid() || bot->GetObjectGuid() == bg->GetHordeFlagCarrierGuid())
            {
                return false;
            }
            return true;
        }
        return false;
    }
#endif
    return false;
}

/// 检测机器人当前是否在战场内
bool PlayerIsInBattleground::IsActive()
{
    return ai->GetBot()->InBattleGround();
}

/// 检测战场状态是否为等待玩家加入（STATUS_WAIT_JOIN）
bool BgWaitingTrigger::IsActive()
{
    if (bot->InBattleGround())
    {
        if (bot->GetBattleGround() && bot->GetBattleGround()->GetStatus() == STATUS_WAIT_JOIN)
            return true;
    }
    return false;
}

/// 检测战场状态是否为进行中（STATUS_IN_PROGRESS）
bool BgActiveTrigger::IsActive()
{
    if (bot->InBattleGround())
    {
        if (bot->GetBattleGround() && bot->GetBattleGround()->GetStatus() == STATUS_IN_PROGRESS)
            return true;
    }
    return false;
}

/// 检测机器人是否已收到战场队列邀请
bool BgInviteActiveTrigger::IsActive()
{
    if (bot->InBattleGround() || !bot->InBattleGroundQueue())
    {
        return false;
    }

    for (int i = 0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
    {
        BattleGroundQueueTypeId queueTypeId = bot->GetBattleGroundQueueTypeId(i);
        if (queueTypeId == BATTLEGROUND_QUEUE_NONE)
            continue;
#ifdef MANGOSBOT_TWOx
        BattleGroundQueue& bgQueue = sServerFacade.bgQueue(queueTypeId);
        GroupQueueInfo ginfo;
        if (bgQueue.GetPlayerGroupInfoData(bot->GetObjectGuid(), &ginfo))
        {
            if (ginfo.isInvitedToBgInstanceGuid && ginfo.removeInviteTime)
            {
                sLog.outDetail("Bot #%d <%s> (%u %s) : Invited to BG but not in BG", bot->GetGUIDLow(), bot->GetName(), bot->GetLevel(), bot->GetTeam() == ALLIANCE ? "A" : "H");
                return true;
            }
        }
#endif
#ifndef MANGOSBOT_ZERO
        if (bot->IsInvitedForBattleGroundQueueType(queueTypeId))
            return true;
#endif
    }
    return false;
}

/// 检测战场状态是否为已结束（STATUS_WAIT_LEAVE）
bool BgEndedTrigger::IsActive()
{
    if (bot->InBattleGround())
    {
        if (bot->GetBattleGround() && bot->GetBattleGround()->GetStatus() == STATUS_WAIT_LEAVE)
            return true;
    }
    return false;
}

/// 检测机器人处于战场但未扛旗
bool PlayerIsInBattlegroundWithoutFlag::IsActive()
{
#ifdef MANGOS
    if (ai->GetBot()->InBattleGround())
    {
        if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
        {
            BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();
            if (!(bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_PLAYER))
                return true;
            if (bot->GetGUIDLow() == bg->GetAllianceFlagCarrierGuid() || bot->GetGUIDLow() == bg->GetHordeFlagCarrierGuid())
            {
                return false;
            }
        }
        return true;
    }
#endif
    return false;
}

/// 检测在战歌峡谷或风暴之眼中机器人自身是否正在扛旗
bool PlayerHasFlag::IsActive()
{
    ai::PositionEntry pos = context->GetValue<ai::PositionMap&>("position")->Get()["bg objective"];
    if (bot->InBattleGround())
    {
        if (bot->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
        {
            if (pos.isSet() && sServerFacade.GetDistance2d(bot, pos.x, pos.y) < 10.0f)
                return false;

            BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();

            if (!bg)
                return false;

            if (bot->GetObjectGuid() == bg->GetFlagCarrierGuid(TEAM_INDEX_ALLIANCE) || bot->GetObjectGuid() == bg->GetFlagCarrierGuid(TEAM_INDEX_HORDE))
            {
                return true;
            }
        }
#ifndef MANGOSBOT_ZERO
        if (bot->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_EY)
        {
            BattleGroundEY* bg = (BattleGroundEY*)ai->GetBot()->GetBattleGround();
            return bot->GetObjectGuid() == bg->GetFlagCarrierGuid();
        }
#endif
        return false;
    }
    return false;
}

/// 检测我方其他队友是否正在扛着敌方旗帜
bool TeamHasFlag::IsActive()
{
#ifdef MANGOS
    if (ai->GetBot()->InBattleGround())
    {
        if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
        {
            BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();

            if (bot->GetObjectGuid() == bg->GetAllianceFlagCarrierGuid() || bot->GetObjectGuid() == bg->GetHordeFlagCarrierGuid())
            {
                return false;
            }

            if (bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_PLAYER)
                return true;
        }
        return false;
    }
#endif
    return false;
}

/// 检测敌方是否正在扛着我方旗帜
bool EnemyTeamHasFlag::IsActive()
{
    if (ai->GetBot()->InBattleGround())
    {
        if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
        {
            BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();

            if (!bg)
                return false;

            if (bot->GetTeam() == HORDE)
            {
                if (!bg->GetFlagCarrierGuid(TEAM_INDEX_HORDE).IsEmpty())
                    return true;
            }
            else
            {
                if (!bg->GetFlagCarrierGuid(TEAM_INDEX_ALLIANCE).IsEmpty())
                    return true;
            }
        }
        return false;
    }
    return false;
}

/// 检测敌方扛旗手是否处于小范围视野内
bool EnemyFlagCarrierNear::IsActive()
{
    Unit* carrier = ai->GetUnit(AI_VALUE(ObjectGuid, "enemy flag carrier"));
    return carrier && sServerFacade.IsDistanceLessOrEqualThan(sServerFacade.GetDistance2d(bot, carrier), VISIBILITY_DISTANCE_SMALL);
}

/// 检测友方扛旗手是否处于小范围视野内
bool TeamFlagCarrierNear::IsActive()
{
    Unit* carrier = ai->GetUnit(AI_VALUE(ObjectGuid, "team flag carrier"));
    return carrier && sServerFacade.IsDistanceLessOrEqualThan(sServerFacade.GetDistance2d(bot, carrier), VISIBILITY_DISTANCE_SMALL);
}

/// 检测机器人是否不在战场且可以加入新的战场队列
bool PlayerWantsInBattlegroundTrigger::IsActive()
{
    if (bot->InBattleGround())
        return false;

    if (bot->GetBattleGround() && bot->GetBattleGround()->GetStatus() == STATUS_WAIT_JOIN)
        return false;

    if (bot->GetBattleGround() && bot->GetBattleGround()->GetStatus() == STATUS_IN_PROGRESS)
        return false;

    if (!bot->CanJoinToBattleground())
        return false;

    return true;
};

/// 检测附近是否存在载具 NPC
bool VehicleNearTrigger::IsActive()
{
    std::list<ObjectGuid> npcs = AI_VALUE(std::list<ObjectGuid>, "nearest vehicles");
    return npcs.size();
}

/// 检测机器人是否处于符合限定条件（Qualifier）的载具中
bool InVehicleTrigger::IsActive()
{
    return ai->IsInVehicle(false,false,false,false,false, getQualifier());
}
