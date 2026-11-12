
#include "playerbot/playerbot.h"
#include "ReviveFromCorpseAction.h"
#include "playerbot/PlayerbotFactory.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/FleeManager.h"
#include "playerbot/TravelMgr.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/values/DeadValues.h"

using namespace ai;

/// 执行动作主逻辑（跑尸复活动作）
bool ReviveFromCorpseAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    Player* master = ai->GetGroupMaster();
    Corpse* corpse = bot->GetCorpse();

    // follow master when master revives (主人复活后恢复跟随主人)
    WorldPacket& p = event.getPacket();
    if (!p.empty() && p.GetOpcode() == CMSG_RECLAIM_CORPSE && master && !corpse && sServerFacade.IsAlive(bot))
    {
        if (sServerFacade.IsDistanceLessThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.farDistance))
        {
            std::string defaultMovementStrategy = ai->GetDefaultMovementStrategy();

            if (!ai->HasStrategy(defaultMovementStrategy, BotState::BOT_STATE_NON_COMBAT))
            {
                ai->TellPlayerNoFacing(requester, "Welcome back!", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
                ai->ChangeStrategy("+" + defaultMovementStrategy + ",-stay", BotState::BOT_STATE_NON_COMBAT);
                return true;
            }
        }
    }

    if (!corpse)
        return false;

    if (corpse->GetGhostTime() + bot->GetCorpseReclaimDelay(corpse->GetType() == CORPSE_RESURRECTABLE_PVP) > time(nullptr))
        return false;

    if (master)
    {
        // Revive with master. (跟随主人一同复活。)
        if (bot != master && sServerFacade.UnitIsDead(master) && master->GetCorpse() && sServerFacade.IsDistanceLessThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.farDistance))
            return false;
    }

    sLog.outDetail("Bot #%d %s:%d <%s> revives at body", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());

    ai->StopMoving();
    WorldPacket packet(CMSG_RECLAIM_CORPSE);
    packet << bot->GetObjectGuid();
    bot->GetSession()->HandleReclaimCorpseOpcode(packet);

    sPlayerbotAIConfig.logEvent(ai, "ReviveFromCorpseAction");

    return true;
}

/// 执行动作主逻辑（寻找尸体动作）
bool FindCorpseAction::Execute(Event& event)
{
    if (bot->InBattleGround())
        return false;

    Corpse* corpse = bot->GetCorpse();
    if (!corpse)
        return false;

    Player* master = ai->GetGroupMaster();
    if (master)
    {
        if (!master->GetPlayerbotAI() && sServerFacade.IsDistanceLessThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.farDistance))
        {
            return false;
        }
    }

    WorldPosition botPos(bot), corpsePos(corpse), moveToPos = corpsePos, masterPos(master);
    float reclaimDist = CORPSE_RECLAIM_RADIUS - 5.0f;
    float corpseDist = botPos.distance(corpsePos);

    if (!corpsePos) // Corpse is at 0,0,0,0 (尸体坐标异常位于原点 (0,0,0,0))
        return false;

    // If player fell through terrain move corpse to player position. (若玩家掉落穿模地形，将尸体坐标移动至玩家当前位置。)
    if (bot->isRealPlayer() && botPos.getMapId() == moveToPos.getMapId())
    {
        // Try to correct the position upward. (尝试向上修正坐标高度。)
        if (!moveToPos.ClosestCorrectPoint(5.0f, 500.0f, bot->GetInstanceId()))
        {
            // Revive in place. (原地复活。)
            corpse->Relocate(botPos.getX(), botPos.getY(), botPos.getZ());
            corpsePos = corpse;
            corpseDist = botPos.distance(corpsePos);
        }
        else
        {
            corpse->Relocate(moveToPos.getX(), moveToPos.getY(), moveToPos.getZ());
            corpsePos = corpse;
            corpseDist = botPos.distance(corpsePos);
        }
    }

    int64 deadTime = time(nullptr) - corpse->GetGhostTime();

    bool moveToMaster = master && master != bot && masterPos.fDist(corpsePos) < reclaimDist;

    // Should we ressurect? If so, return false. (若需要优先执行复活流程，则返回 false。)
    if (corpseDist < reclaimDist)
    {
        if (moveToMaster) // We are near master. (当前正位于主人附近。)
        {
            if (botPos.fDist(masterPos) < sPlayerbotAIConfig.spellDistance)
                return false;
        }
        else if (deadTime > 8 * MINUTE) // We have walked too long already. (步行耗时已过长。)
            return false;
        else
        {
            std::list<ObjectGuid> units = AI_VALUE(std::list<ObjectGuid>, "possible targets no los");

            if (botPos.getUnitsAggro(units, bot) == 0) // There are no mobs near. (附近没有敌对怪物。)
                return false;
        }
    }

    // If we are getting close move to a save ressurrection spot instead of just the corpse. (接近尸体时优先寻找安全复活位置而非直接站在尸体正上方。)
    if (corpseDist < sPlayerbotAIConfig.reactDistance)
    {
        if (moveToMaster)
        {
            if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
            {
                std::ostringstream out;
                out << "Moving to revive near master.";
                ai->TellPlayerNoFacing(GetMaster(), out);
            }
            moveToPos = masterPos;
        }
        else
        {
            FleeManager manager(bot, reclaimDist, 0.0, urand(0, 1), moveToPos);

            if (manager.isUseful())
            {
                float rx, ry, rz;
                if (manager.CalculateDestination(&rx, &ry, &rz))
                {
                    if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
                    {
                        std::ostringstream out;
                        out << "Moving to revive some where safe.";
                        ai->TellPlayerNoFacing(GetMaster(), out);
                    }
                    moveToPos = WorldPosition(moveToPos.getMapId(), rx, ry, rz, 0.0);
                }
                else if (!moveToPos.GetReachableRandomPointOnGround(bot, reclaimDist, urand(0, 1)))
                {
                    if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
                    {
                        std::ostringstream out;
                        out << "Moving to revive at corpse.";
                        ai->TellPlayerNoFacing(GetMaster(), out);
                    }
                    moveToPos = corpsePos;
                }
            }
        }
    }
    else
    {
        if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
        {
            std::ostringstream out;
            out << "Moving towards corpse.";
            ai->TellPlayerNoFacing(GetMaster(), out);
        }
    }

    // Actual mobing part. (实际移动执行部分。)
    bool moved = false;

    if (!ai->AllowActivity(DETAILED_MOVE_ACTIVITY) && !ai->HasPlayerNearby(moveToPos))
    {
        uint32 delay = sServerFacade.GetDistance2d(bot, corpse) / bot->GetSpeed(MOVE_RUN); // Time a bot would take to travel to it's corpse. (估算机器人跑回自身尸体所需的耗时。)
        delay = std::min(delay, uint32(10 * MINUTE)); // Cap time to get to corpse at 10 minutes. (将跑尸超时上限设为 10 分钟。)

        if (deadTime > delay)
        {
            bot->GetMotionMaster()->Clear();
            bot->TeleportTo(moveToPos.getMapId(), moveToPos.getX(), moveToPos.getY(), moveToPos.getZ(), 0);
            if (bot->isRealPlayer())
                bot->SendHeartBeat();
        }

        moved = true;
    }
    else
    {
#ifndef MANGOSBOT_ZERO
        if (bot->IsMovingIgnoreFlying())
            moved = true;
#else
        if (bot->IsMoving())
            moved = true;
#endif
        else
        {

            moved = MoveTo(moveToPos.getMapId(), moveToPos.getX(), moveToPos.getY(), moveToPos.getZ(), false, false);

            if (!moved && !ai->HasActivePlayerMaster()) // We could not move to coprse. Try spirithealer instead. (无法跑尸到达尸体位置，改为寻找灵魂医者复活。)
            {
                moved = ai->DoSpecificAction("spirit healer", Event(), true);
            }
        }
    }

    return moved;
}

/// 判断当前状态下该动作是否可用/有效（寻找尸体动作）
bool FindCorpseAction::isUseful()
{
    if (bot->InBattleGround())
        return false;

    return bot->GetCorpse();
}

/// 执行动作主逻辑（灵魂医者复活动作）
bool SpiritHealerAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    Corpse* corpse = bot->GetCorpse();
    if (!corpse)
    {
        ai->TellPlayerNoFacing(requester, "I am not a spirit");
        return false;
    }

    uint32 dCount = AI_VALUE(uint32, "death count");
    GuidPosition grave = AI_VALUE(GuidPosition, "best graveyard");

    // something went wrong (处理过程发生异常)
    if (!grave)
    {
        // prevent doing weird stuff OR GOING TO 0,0,0 (防止异常行为或错误前往原点 (0,0,0))
        sLog.outDetail(
            "ERROR: no graveyard in SpiritHealerAction for bot #%d %s:%d <%s>, evacuating to prevent weird behavior",
            bot->GetGUIDLow(),
            bot->GetTeam() == ALLIANCE ? "A" : "H",
            bot->GetLevel(),
            bot->GetName()
        );
        ai->DoSpecificAction("repop");
        return false;
    }

    if (grave && grave.fDist(bot) < sPlayerbotAIConfig.sightDistance)
    {
        bool foundSpiritHealer = false;
        // 遍历附近 NPC 列表
        std::list<ObjectGuid> npcs = AI_VALUE(std::list<ObjectGuid>, "nearest npcs");
        for (std::list<ObjectGuid>::iterator i = npcs.begin(); i != npcs.end(); i++)
        {
            Unit* unit = ai->GetUnit(*i);
            if (unit && unit->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPIRITHEALER))
            {
                foundSpiritHealer = true;
                break;
            }
        }

        if (!foundSpiritHealer)
        {
            sLog.outDetail("Bot #%d %s:%d <%s> can't find a spirit healer", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());
            ai->TellPlayerNoFacing(requester, "Cannot find any spirit healer nearby");
        }


        sLog.outDetail("Bot #%d %s:%d <%s> revives at spirit healer", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());
        PlayerbotChatHandler ch(bot);
        bot->ResurrectPlayer(0.5f, !ai->HasCheat(BotCheatMask::repair));
        bot->DurabilityLossAll(0.25f, true);

        bot->SpawnCorpseBones();
        bot->SaveToDB();
        context->GetValue<ObjectGuid>("current target")->Set(ObjectGuid());
        bot->SetSelectionGuid(ObjectGuid());
        ai->TellPlayer(requester, BOT_TEXT("hello"), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        sPlayerbotAIConfig.logEvent(ai, "ReviveFromSpiritHealerAction");

        return true;
    }

    bool shouldTeleportToGY = false;

    const int64 deadTime = time(nullptr) - corpse->GetGhostTime();

    // Prevent taking too long to go to corpse (10 mins) (防止跑尸耗时过长（上限 10 分钟）)
    // no need to wait longer, because bot is probably stuck in navigating issues (无需继续等待，机器人可能已陷入寻路卡死)
    shouldTeleportToGY = deadTime > uint32(10 * MINUTE);

    // Check if we can teleport to the graveyard when nobody is looking (检查附近无玩家注视时能否直接传送至墓地)
    if (!shouldTeleportToGY && !ai->AllowActivity(DETAILED_MOVE_ACTIVITY) && !ai->HasPlayerNearby(WorldPosition(grave)))
    {
        // Time a bot would take to travel to it's corpse. (估算机器人跑回自身尸体所需的耗时。)
        uint32 delay = sServerFacade.GetDistance2d(bot, corpse) / bot->GetSpeed(MOVE_RUN);
        // Cap time to get to corpse at 10 minutes. (将跑尸超时上限设为 10 分钟。)
        delay = std::min(delay, uint32(10 * MINUTE));

        shouldTeleportToGY = deadTime > delay;
    }

    if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
    {
        std::ostringstream out;
        out << "Moving towards graveyard.";
        ai->TellPlayerNoFacing(GetMaster(), out);
    }

    if (shouldTeleportToGY)
    {
        bot->GetMotionMaster()->Clear();
        bot->TeleportTo(grave.getMapId(), grave.getX(), grave.getY(), grave.getZ(), 0);
        if (bot->isRealPlayer())
            bot->SendHeartBeat();
        return true;
    }
    else
    {
        return MoveTo(grave.getMapId(), grave.getX(), grave.getY(), grave.getZ(), false, false);
    }
}

/// 判断当前状态下该动作是否可用/有效（灵魂医者复活动作）
bool SpiritHealerAction::isUseful()
{
    if (bot->InBattleGround())
        return false;

    return bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST);
}
