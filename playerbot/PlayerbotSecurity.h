#ifndef _PlayerbotSecurity_H
#define _PlayerbotSecurity_H

/// 机器人交互安全权限等级枚举（拒绝/仅聊天/允许公会邀请/允许组队邀请/完全允许）
enum class PlayerbotSecurityLevel : uint8
{
    PLAYERBOT_SECURITY_DENY_ALL = 0,
    PLAYERBOT_SECURITY_TALK = 1,
    PLAYERBOT_SECURITY_GUILD = 2, //Intermediate level: Bot can't be invited to group but can accept guild invites.
    PLAYERBOT_SECURITY_INVITE = 3,
    PLAYERBOT_SECURITY_ALLOW_ALL = 4
};

/// 拒绝外部玩家请求的具体原因枚举
enum class DenyReason : uint8
{
    PLAYERBOT_DENY_NONE,
    PLAYERBOT_DENY_LOW_LEVEL,
    PLAYERBOT_DENY_GEARSCORE,
    PLAYERBOT_DENY_NOT_YOURS,
    PLAYERBOT_DENY_IS_BOT,
    PLAYERBOT_DENY_OPPOSING,
    PLAYERBOT_DENY_DEAD,
    PLAYERBOT_DENY_FAR,
    PLAYERBOT_DENY_INVITE,
    PLAYERBOT_DENY_FULL_GROUP,
    PLAYERBOT_DENY_NOT_LEADER,
    PLAYERBOT_DENY_IS_LEADER,
    PLAYERBOT_DENY_BG,
    PLAYERBOT_DENY_LFG
};

/// 机器人安全权限校验器，判定其他玩家是否有权对机器人发指令或组队
class PlayerbotSecurity
{
    public:
        PlayerbotSecurity(Player* const bot);

    public:
        PlayerbotSecurityLevel LevelFor(Player* from, DenyReason* reason = NULL, bool ignoreGroup = false);
        bool CheckLevelFor(PlayerbotSecurityLevel level, bool silent, Player* from, bool ignoreGroup = false);

    private:
        Player* const bot;
        uint32 account;
        std::map<uint64, std::map<std::string, time_t> > whispers;
};

#endif
