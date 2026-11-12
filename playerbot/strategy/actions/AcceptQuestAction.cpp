
#include "playerbot/playerbot.h"
#include "AcceptQuestAction.h"

using namespace ai;

/// 处理单个任务发布对象的任务接取或交付逻辑（接受全部任务动作）
bool AcceptAllQuestsAction::ProcessQuest(Player* requester, Quest const* quest, WorldObject* questGiver)
{
    if (AcceptQuest(requester, quest, questGiver->GetObjectGuid()))
    {
        if (sPlayerbotAIConfig.globalSoundEffects)
            bot->PlayDistanceSound(620);
        return true;
    }

    return false;
}

/// 执行动作主逻辑（接受指定任务动作）
bool AcceptQuestAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    Player *bot = ai->GetBot();
    uint64 guid = 0;
    uint32 quest = 0;

    std::string text = event.getParam();
    PlayerbotChatHandler ch(requester);
    quest = ch.extractQuestId(text);

    bool hasAccept = false;

    // 无网络封包事件：通过聊天指令或周围对象主动触发
    if (event.getPacket().empty())
    {
        // 遍历附近 NPC 列表
        std::list<ObjectGuid> npcs = AI_VALUE(std::list<ObjectGuid>, "nearest npcs");
        for (std::list<ObjectGuid>::iterator i = npcs.begin(); i != npcs.end(); i++)
        {
            Unit* unit = ai->GetUnit(*i);
            if (unit && quest && unit->HasQuest(quest))
            {
                guid = unit->GetObjectGuid().GetRawValue();
                break;
            }
            if (unit && text == "*" && bot->GetDistance(unit) <= INTERACTION_DISTANCE)
                hasAccept |= QuestAction::ProcessQuests(unit);
        }
        // 遍历附近游戏对象列表
        std::list<ObjectGuid> gos = AI_VALUE(std::list<ObjectGuid>, "nearest game objects no los");
        for (std::list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); i++)
        {
            GameObject* go = ai->GetGameObject(*i);
            if (go && quest && go->HasQuest(quest))
            {
                guid = go->GetObjectGuid().GetRawValue();
                break;
            }
            if (go && text == "*" && bot->GetDistance(go) <= INTERACTION_DISTANCE)
                hasAccept |= QuestAction::ProcessQuests(go);
        }
    }
    else
    {
        // 解析事件携带的网络封包数据
        WorldPacket& p = event.getPacket();
        p.rpos(0);
        p >> guid >> quest;
    }

    if (!quest || !guid)
        return false;

    Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);
    if (!qInfo)
        return false;

    hasAccept |= AcceptQuest(requester, qInfo, guid);

    if (hasAccept)
        sPlayerbotAIConfig.logEvent(ai, "AcceptQuestAction", qInfo->GetTitle(), std::to_string(qInfo->GetQuestId()));

    return hasAccept;
}

/// 执行动作主逻辑（接受共享任务动作）
bool AcceptQuestShareAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    Player* bot = ai->GetBot();

    if (!ai->IsSafe(requester))
        requester = bot;

    // 解析事件携带的网络封包数据
    WorldPacket& p = event.getPacket();
    p.rpos(0);
    uint32 quest;
    p >> quest;
    Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);

    if (!qInfo || !bot->GetDividerGuid())
        return false;

    quest = qInfo->GetQuestId();
    if( !bot->CanTakeQuest( qInfo, false ) )
    {
        // can't take quest (无法接取该任务)
        bot->SetDividerGuid( ObjectGuid() );
        ai->TellError(requester, BOT_TEXT("quest_cant_take"));

        return false;
    }

    if( !bot->GetDividerGuid().IsEmpty() )
    {
        // send msg to quest giving player (向共享任务的玩家发送提示消息)
        requester->SendPushToPartyResponse( bot, QUEST_PARTY_MSG_ACCEPT_QUEST );
        bot->SetDividerGuid( ObjectGuid() );
    }

    if( bot->CanAddQuest( qInfo, false ) )
    {
        bot->AddQuest( qInfo, requester);

        sPlayerbotAIConfig.logEvent(ai, "AcceptQuestShareAction", qInfo->GetTitle(), std::to_string(qInfo->GetQuestId()));

        if( bot->CanCompleteQuest( quest ) )
            bot->CompleteQuest( quest );

        // Runsttren: did not add typeid switch from WorldSession::HandleQuestgiverAcceptQuestOpcode! (注：此处未照搬 WorldSession::HandleQuestgiverAcceptQuestOpcode 中的 typeid 分支判断)
        // I think it's not needed, cause typeid should be TYPEID_PLAYER - and this one is not handled (此处无需处理，因为对象类型应为 TYPEID_PLAYER 而原逻辑未包含)
        // there and there is no default case also. (且该处没有 default 分支。)

        if( qInfo->GetSrcSpell() > 0 )
        {
            bot->CastSpell( bot, qInfo->GetSrcSpell(),
#ifdef MANGOS
                    true
#endif
#ifdef CMANGOS
                    (uint32)0
#endif
            );
        }

        ai->TellPlayer(requester, BOT_TEXT("quest_accept"), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }

    return false;
}

/// 执行动作主逻辑（确认任务动作）
bool ConfirmQuestAction::Execute(Event& event)
{
    Player *bot = ai->GetBot();
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    // 解析事件携带的网络封包数据
    WorldPacket& p = event.getPacket();
    p.rpos(0);
    uint32 quest;
    p >> quest;
    Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);
    
    if (!qInfo)
        return false;

    quest = qInfo->GetQuestId();
    if( !bot->CanTakeQuest( qInfo, false ) )
    {
        // can't take quest (无法接取该任务)
        ai->TellError(requester, BOT_TEXT("quest_cant_take"));
        return false;
    }

    if( bot->CanAddQuest( qInfo, false ) )
    {
        if (qInfo->HasQuestFlag(QUEST_FLAGS_PARTY_ACCEPT))
            bot->AddQuest(qInfo, nullptr); // prevent double dbscript call if player is doing it (若玩家正在交互则防止重复触发 DB 脚本)
        else
            bot->AddQuest( qInfo, requester );

        if( bot->CanCompleteQuest( quest ) )
            bot->CompleteQuest( quest );

        if( qInfo->GetSrcSpell() > 0 )
        {
            bot->CastSpell( bot, qInfo->GetSrcSpell(),
#ifdef MANGOS
                    true
#endif
#ifdef CMANGOS
                    (uint32)0
#endif
            );
        }

        ai->TellPlayer(requester, BOT_TEXT("quest_accept"), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }

    return false;
}

/// 执行动作主逻辑（任务详情确认动作）
bool QuestDetailsAction::Execute(Event& event)
{
    Player* bot = ai->GetBot();
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    // 解析事件携带的网络封包数据
    WorldPacket& p = event.getPacket();
    p.rpos(0);
    ObjectGuid guid;
    uint32 quest;
    p >> guid;
    p >> quest;
    Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);

    if (!qInfo)
        return false;

    quest = qInfo->GetQuestId();
    if (!bot->CanTakeQuest(qInfo, false))
    {
        // can't take quest (无法接取该任务)
        ai->TellError(requester, BOT_TEXT("quest_cant_take"));
        return false;
    }

    if (bot->CanAddQuest(qInfo, false))
    {
        bot->AddQuest(qInfo, requester);

        if (bot->CanCompleteQuest(quest))
            bot->CompleteQuest(quest);

        if (qInfo->GetSrcSpell() > 0)
        {
            bot->CastSpell(bot, qInfo->GetSrcSpell(),
#ifdef MANGOS
                true
#endif
#ifdef CMANGOS
                (uint32)0
#endif
            );
        }

        ai->TellPlayer(requester, BOT_TEXT("quest_accept"), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }

    return false;
}
