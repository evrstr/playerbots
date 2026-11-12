
#include "playerbot/playerbot.h"
#include "ArenaTeamActions.h"
#ifndef MANGOSBOT_ZERO
#ifdef CMANGOS
#include "Arena/ArenaTeam.h"
#endif
#ifdef MANGOS
#include "ArenaTeam.h"
#endif
#endif

using namespace ai;

/// 执行动作主逻辑（接受竞技场战队邀请动作）
bool ArenaTeamAcceptAction::Execute(Event& event)
{
#ifndef MANGOSBOT_ZERO
    // 解析事件携带的网络封包数据
    WorldPacket p(event.getPacket());
    p.rpos(0);
    Player* inviter = nullptr;
    std::string Invitedname;
    p >> Invitedname;

    if (normalizePlayerName(Invitedname))
        inviter = ObjectAccessor::FindPlayerByName(Invitedname.c_str());

    if (!inviter)
        return false;

    ArenaTeam* at = sObjectMgr.GetArenaTeamById(bot->GetArenaTeamIdInvited());
    if (!at)
        return false;

    bool accept = true;

    if (bot->GetArenaTeamId(at->GetSlot()))
    {
        // bot is already in an arena team (机器人已经处于竞技场战队中)
        bot->Say("Sorry, I am already in such team", LANG_UNIVERSAL);
        accept = false;
    }

    if (accept)
    {
        WorldPacket data(CMSG_ARENA_TEAM_ACCEPT);
        bot->GetSession()->HandleArenaTeamAcceptOpcode(data);
        bot->Say("Thanks for the invite!", LANG_UNIVERSAL);
        sLog.outDetail("Bot #%d <%s> accepts Arena Team invite", bot->GetGUIDLow(), bot->GetName());
        return true;
    }
    else
    {
        WorldPacket data(CMSG_ARENA_TEAM_DECLINE);
        bot->GetSession()->HandleArenaTeamDeclineOpcode(data);
        sLog.outDetail("Bot #%d <%s> declines Arena Team invite", bot->GetGUIDLow(), bot->GetName());
        return false;
    }
#endif
    return false;
}
