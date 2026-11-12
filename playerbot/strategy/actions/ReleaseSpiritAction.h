#pragma once

#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/strategy/values/LastMovementValue.h"
#include "ReviveFromCorpseAction.h"
#include "playerbot/TravelMgr.h"

namespace ai
{
    /// 释放灵魂动作：死亡后向服务端发送释放灵魂请求进入墓地跑尸状态
    class ReleaseSpiritAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化释放灵魂动作
        ReleaseSpiritAction(PlayerbotAI* ai, std::string name = "release") : ChatCommandAction(ai, name) {}

    public:
        /// 执行动作主逻辑（释放灵魂动作）
        virtual bool Execute(Event& event) override
        {
            Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
            if (sServerFacade.IsAlive(bot))
                return false;

            if (bot->GetCorpse() && bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
            {
                ai->TellPlayerNoFacing(requester, "I am already a spirit", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
                return false;
            }

            WorldPacket& p = event.getPacket();
            if (!p.empty() && p.GetOpcode() == CMSG_REPOP_REQUEST)
                ai->TellPlayerNoFacing(requester, "Releasing...", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
            else
                ai->TellPlayerNoFacing(requester, "Meet me at the graveyard", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);

            sLog.outDetail("Bot #%d %s:%d <%s> released", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());

            WorldPacket packet(CMSG_REPOP_REQUEST);
            packet << uint8(0);
            bot->GetSession()->HandleRepopRequestOpcode(packet);

            // add waiting for ress aura (添加等待复活光环状态)
            if (bot->InBattleGround() && !ai->HasAura(2584, bot))
            {
                // cast Waiting for Resurrect (施放等待复活状态)
                bot->CastSpell(bot, 2584, TRIGGERED_OLD_TRIGGERED);
            }

            return true;
        }
    };

    /// 自动释放灵魂动作：在满足自动跑尸条件（如战场或野外死亡）时自动释放灵魂
    class AutoReleaseSpiritAction : public ReleaseSpiritAction 
    {
    public:
        /// 构造函数：初始化自动释放灵魂动作
        AutoReleaseSpiritAction(PlayerbotAI* ai, std::string name = "auto release") : ReleaseSpiritAction(ai, name) {}

        /// 执行动作主逻辑（自动释放灵魂动作）
        virtual bool Execute(Event& event) override
        {
            sLog.outDetail("Bot #%d %s:%d <%s> auto released", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());

            WorldPacket packet(CMSG_REPOP_REQUEST);
            packet << uint8(0);
            bot->GetSession()->HandleRepopRequestOpcode(packet);

            // add waiting for ress aura (添加等待复活光环状态)
            if (bot->InBattleGround() && !ai->HasAura(2584, bot))
            {
                // cast Waiting for Resurrect (施放等待复活状态)
                bot->CastSpell(bot, 2584, TRIGGERED_OLD_TRIGGERED);
            }

            sPlayerbotAIConfig.logEvent(ai, "AutoReleaseSpiritAction");

            return true;
        }

        /// 判断当前状态下该动作是否可用/有效（自动释放灵魂动作）
        virtual bool isUseful() override
        {
            if (!sServerFacade.UnitIsDead(bot))
                return false;

            if (bot->GetCorpse())
                return false;

#ifndef MANGOSBOT_ZERO
            if (bot->InArena())
                return false;
#endif

            if (bot->InBattleGround())
                return !bot->GetCorpse() || !bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST);

            if (bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
                return false;

            if (!bot->GetGroup())
                return true;

            if (!ai->GetGroupMaster())
                return true;

            if (ai->GetGroupMaster() == bot)
                return true;

            if (!ai->HasActivePlayerMaster())
                return true;

            if (ai->HasActivePlayerMaster() && ai->GetGroupMaster()->GetMapId() == bot->GetMapId() && (bot->GetMap()->IsRaid() || bot->GetMap()->IsDungeon()))
                return false;

            if(sServerFacade.UnitIsDead(ai->GetGroupMaster()))
                return true;

            if (sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.sightDistance))
                return true;

            return false;
        }
    };

    /// 复活点重聚动作：引导灵魂状态下的机器人寻找灵魂医者复活
    class RepopAction : public SpiritHealerAction 
    {
    public:
        /// 构造函数：初始化复活点重聚动作
        RepopAction(PlayerbotAI* ai, std::string name = "repop") : SpiritHealerAction(ai, name) {}

    public:
        /// 执行动作主逻辑（复活点重聚动作）
        virtual bool Execute(Event& event) override
        {
            Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

            sLog.outDetail("Repop bot #%d %s:%d <%s>", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());

            SET_AI_VALUE(uint32, "death count", 0);

            if (bot->IsDead())
            {
                bot->ResurrectPlayer(1.0f, false);
                bot->SpawnCorpseBones();
                bot->SaveToDB();
            }

            
            if (!ai->HasRealPlayerMaster())
            {
                if (Group* group = bot->GetGroup())
                {
                    sLog.outDetail("Repop: Removing bot #%d %s:%d <%s> from group", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());
                    group->RemoveMember(bot->GetObjectGuid(), 0);
                }
            }

            RESET_AI_VALUE(ObjectGuid, "old target");
            RESET_AI_VALUE(ObjectGuid, "current target");
            RESET_AI_VALUE(ObjectGuid, "pull target");
            RESET_AI_VALUE(bool, "combat::self target");
            RESET_AI_VALUE(WorldPosition, "current position");

            bot->SetSelectionGuid(ObjectGuid());
            ai->TellPlayer(requester, BOT_TEXT("hello"), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);

            TravelTarget* travelTarget = AI_VALUE(TravelTarget*, "travel target");
            sTravelMgr.SetNullTravelTarget(travelTarget);
            travelTarget->SetStatus(TravelStatus::TRAVEL_STATUS_EXPIRED);
            travelTarget->SetExpireIn(1000);

            PlayerInfo const* defaultPlayerInfo = sObjectMgr.GetPlayerInfo(bot->getRace(), bot->getClass());
            if (defaultPlayerInfo)
            {
                sLog.outDetail("Repop: Teleporting bot #%d %s:%d <%s> to spawn", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());
                // teleport bot to spawn (将机器人传送回出生点)
                bot->TeleportTo(defaultPlayerInfo->mapId, defaultPlayerInfo->positionX, defaultPlayerInfo->positionY, defaultPlayerInfo->positionZ, defaultPlayerInfo->orientation);
                if (bot->isRealPlayer())
                    bot->SendHeartBeat();
            }
            else
            {
                sLog.outDetail("Repop: Teleporting bot #%d %s:%d <%s> to homebind", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());
                // teleport bot to homebind (将机器人传送回炉石绑定点)
                bot->TeleportToHomebind();
                bot->SendHeartBeat();
            }

            sPlayerbotAIConfig.logEvent(ai, "RepopAction");

            return true;
        }

        /// 判断当前状态下该动作是否可用/有效（复活点重聚动作）
        virtual bool isUseful() override
        {
            if (bot->InBattleGround())
                return false;

            if (ai->HasActivePlayerMaster())
                return false;

            return true;
        }
    };

    /// 自我复活动作：使用灵魂石、复生等自身技能在原地复活
    class SelfResurrectAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化自我复活动作
        SelfResurrectAction(PlayerbotAI* ai, std::string name = "self resurrect") : ChatCommandAction(ai, name) {}

    public:
        /// 执行动作主逻辑（自我复活动作）
        bool Execute(Event& event) override
        {
            WorldPacket packet(CMSG_SELF_RES);
            bot->GetSession()->HandleSelfResOpcode(packet);
            return true;
        }

        /// 判断执行该动作的前置条件是否满足（自我复活动作）
        bool isPossible() override
        {
            return ai->IsStateActive(BotState::BOT_STATE_DEAD) && bot->GetUInt32Value(PLAYER_SELF_RES_SPELL);
        }
    };
}
