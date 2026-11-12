#pragma once
#include "GenericActions.h"
#include "Guilds/GuildMgr.h"

namespace ai
{
    /// 公会管理基类动作：解析公会成员管理命令并校验权限
    class GuidManageAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化公会管理基类动作
        GuidManageAction(PlayerbotAI* ai, std::string name = "guild manage", uint16 opcode = CMSG_GUILD_INVITE) : ChatCommandAction(ai, name), opcode(opcode) {}
        /// 执行动作主逻辑（公会管理基类动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（公会管理基类动作）
        virtual bool isUseful() override { return false; }
    
    protected:
        /// 构造并返回待发送的网络封包
        virtual WorldPacket GetPacket(Player* player) { WorldPacket data(Opcodes(opcode), 8); data << player->GetName(); return data; }
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data, Event event) {};
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data) { Event event = Event();  SendPacket(data, event); };
        /// 根据名称或参数查找在线玩家指针
        virtual Player* GetPlayer(Event event);
        /// 校验玩家指针是否有效、在线且满足交互条件
        virtual bool PlayerIsValid(Player* member) { return !member->GetGuildId(); };
        /// 解析并返回指定的公会阶级索引
        virtual uint8 GetRankId(Player* member) { return sGuildMgr.GetGuildById(member->GetGuildId())->GetMemberSlot(member->GetObjectGuid())->RankId; }
        /// 判断当前公会成员人数是否已达上限
        virtual bool GuildIsFull(uint32 GuildId) { Guild* guild = sGuildMgr.GetGuildById(GuildId); return  guild->GetMemberSize() >= 1000; }

        uint16 opcode;
    };

    /// 邀请加入公会动作：邀请指定玩家或机器人加入当前公会
    class GuildInviteAction : public GuidManageAction 
    {
    public:
        /// 构造函数：初始化邀请加入公会动作
        GuildInviteAction(PlayerbotAI* ai, std::string name = "guild invite", uint16 opcode = CMSG_GUILD_INVITE) : GuidManageAction(ai, name, opcode) {}
        /// 判断当前状态下该动作是否可用/有效（邀请加入公会动作）
        virtual bool isUseful() override { return bot->GetGuildId() && sGuildMgr.GetGuildById(bot->GetGuildId())->HasRankRight(bot->GetRank(), GR_RIGHT_INVITE) && !GuildIsFull(bot->GetGuildId()); }
    
    protected:
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data, Event event) override { bot->GetSession()->HandleGuildInviteOpcode(data); };
        /// 校验玩家指针是否有效、在线且满足交互条件
        virtual bool PlayerIsValid(Player* member) override { return !member->GetGuildId(); };
    };

    /// 申请/加入公会动作：处理加入指定公会的指令操作
    class GuildJoinAction : public GuidManageAction 
    {
    public:
        /// 构造函数：初始化申请/加入公会动作
        GuildJoinAction(PlayerbotAI* ai, std::string name = "guild join", uint16 opcode = CMSG_GUILD_INVITE) : GuidManageAction(ai, name, opcode) {}
        /// 判断当前状态下该动作是否可用/有效（申请/加入公会动作）
        virtual bool isUseful() override { return !bot->GetGuildId(); }
    
    protected:
        /// 构造并返回待发送的网络封包
        virtual WorldPacket GetPacket(Player* player) override { WorldPacket data(Opcodes(opcode), 8); data << bot->GetName(); return data; }
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data, Event event) override { if(GetPlayer(event)) GetPlayer(event)->GetSession()->HandleGuildInviteOpcode(data); };
        /// 校验玩家指针是否有效、在线且满足交互条件
        virtual bool PlayerIsValid(Player* member) override { return !bot->GetGuildId() && member->GetGuildId() && sGuildMgr.GetGuildById(member->GetGuildId())->HasRankRight(member->GetRank(), GR_RIGHT_INVITE) && !GuildIsFull(member->GetGuildId()); };
    };

    /// 提升公会阶级动作：将指定公会成员的会阶提升一级
    class GuildPromoteAction : public GuidManageAction 
    {
    public:
        /// 构造函数：初始化提升公会阶级动作
        GuildPromoteAction(PlayerbotAI* ai, std::string name = "guild promote", uint16 opcode = CMSG_GUILD_PROMOTE) : GuidManageAction(ai, name, opcode) {}
        /// 判断当前状态下该动作是否可用/有效（提升公会阶级动作）
        virtual bool isUseful() override { return bot->GetGuildId() && sGuildMgr.GetGuildById(bot->GetGuildId())->HasRankRight(bot->GetRank(), GR_RIGHT_PROMOTE); }
    
    protected:
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data, Event event) override { bot->GetSession()->HandleGuildPromoteOpcode(data); };
        /// 校验玩家指针是否有效、在线且满足交互条件
        virtual bool PlayerIsValid(Player* member) override { return member->GetGuildId() == bot->GetGuildId() && GetRankId(bot) < GetRankId(member) - 1; };
    };

    /// 降低公会阶级动作：将指定公会成员的会阶降低一级
    class GuildDemoteAction : public GuidManageAction 
    {
    public:
        /// 构造函数：初始化降低公会阶级动作
        GuildDemoteAction(PlayerbotAI* ai, std::string name = "guild demote", uint16 opcode = CMSG_GUILD_DEMOTE) : GuidManageAction(ai, name, opcode) {}
        /// 判断当前状态下该动作是否可用/有效（降低公会阶级动作）
        virtual bool isUseful() override { return bot->GetGuildId() && sGuildMgr.GetGuildById(bot->GetGuildId())->HasRankRight(bot->GetRank(), GR_RIGHT_DEMOTE); }
    
    protected:
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data, Event event) override { bot->GetSession()->HandleGuildDemoteOpcode(data); };
        /// 校验玩家指针是否有效、在线且满足交互条件
        virtual bool PlayerIsValid(Player* member) override { return member->GetGuildId() == bot->GetGuildId() && GetRankId(bot) < GetRankId(member); };
    };

    /// 移交公会会长动作：将公会会长权限移交给指定成员
    class GuildLeaderAction : public GuidManageAction 
    {
    public:
        /// 构造函数：初始化移交公会会长动作
        GuildLeaderAction(PlayerbotAI* ai, std::string name = "guild leader", uint16 opcode = CMSG_GUILD_LEADER) : GuidManageAction(ai, name, opcode) {}
        /// 判断当前状态下该动作是否可用/有效（移交公会会长动作）
        virtual bool isUseful() override { return bot->GetGuildId() && sGuildMgr.GetGuildById(bot->GetGuildId())->GetLeaderGuid() == bot->GetObjectGuid(); }
    
    protected:
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data, Event event) override { bot->GetSession()->HandleGuildLeaderOpcode(data); };
        /// 校验玩家指针是否有效、在线且满足交互条件
        virtual bool PlayerIsValid(Player* member) override { return member->GetGuildId() == bot->GetGuildId() && GetRankId(bot) < GetRankId(member) - 1; };
    };
    
    /// 移出公会动作：将指定成员踢出公会
    class GuildRemoveAction : public GuidManageAction 
    {
    public:
        /// 构造函数：初始化移出公会动作
        GuildRemoveAction(PlayerbotAI* ai, std::string name = "guild remove", uint16 opcode = CMSG_GUILD_REMOVE) : GuidManageAction(ai, name, opcode) {}
        /// 判断当前状态下该动作是否可用/有效（移出公会动作）
        virtual bool isUseful() override { return bot->GetGuildId() && sGuildMgr.GetGuildById(bot->GetGuildId())->HasRankRight(bot->GetRank(), GR_RIGHT_REMOVE); }
    
    protected:
        /// 向服务端或客户端发送构造好的网络封包
        virtual void SendPacket(WorldPacket data, Event event) override { bot->GetSession()->HandleGuildRemoveOpcode(data); };
        /// 校验玩家指针是否有效、在线且满足交互条件
        virtual bool PlayerIsValid(Player* member) override { return member->GetGuildId() == bot->GetGuildId() && GetRankId(bot) < GetRankId(member); };
    };

    /// 附近公会成员管理动作：对附近公会成员执行随机或批量的晋升/降级维护
    class GuildManageNearbyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化附近公会成员管理动作
        GuildManageNearbyAction(PlayerbotAI* ai) : ChatCommandAction(ai, "guild manage nearby") {}
        /// 执行动作主逻辑（附近公会成员管理动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（附近公会成员管理动作）
        virtual bool isUseful() override;
    };

    /// 退出公会动作：使机器人退出当前所属公会
    class GuildLeaveAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化退出公会动作
        GuildLeaveAction(PlayerbotAI* ai) : ChatCommandAction(ai, "guild leave") {}
        /// 执行动作主逻辑（退出公会动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（退出公会动作）
        virtual bool isUseful() override { return bot->GetGuildId(); }
    };
}
