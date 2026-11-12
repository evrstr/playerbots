#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 邀请组队指令动作：邀请指定玩家或选中目标加入机器人所在队伍
    class InviteToGroupAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化邀请组队指令动作
        InviteToGroupAction(PlayerbotAI* ai, std::string name = "invite") : ChatCommandAction(ai, name) {}

        /// 执行动作主逻辑（邀请组队指令动作）
        virtual bool Execute(Event& event) override
        {
            Player* master = event.getOwner();
            std::string param = event.getParam();
            
            Player* target = nullptr;
            if (!param.empty())
            {
                target = sObjectMgr.GetPlayer(param.c_str());
            }
            
            if (!target)
            {
                target = master;
            }
            
            return Invite(bot, target);
        }

        /// 向指定玩家发送队伍或团队邀请
        virtual bool Invite(Player* inviter, Player* player);
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（邀请组队指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 申请入队动作：主动向指定玩家或队伍发起入队请求
    class JoinGroupAction : public InviteToGroupAction
    {
    public:
        /// 构造函数：初始化申请入队动作
        JoinGroupAction(PlayerbotAI* ai, std::string name = "join") : InviteToGroupAction(ai, name) {}
        /// 执行动作主逻辑（申请入队动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（申请入队动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 自动寻队邀请动作：在随机机器人中寻找合适队友并发送组队邀请
    class LfgAction : public InviteToGroupAction
    {
    public:
        /// 构造函数：初始化自动寻队邀请动作
        LfgAction(PlayerbotAI* ai, std::string name = "lfg") : InviteToGroupAction(ai, name) {}

        static std::unordered_map<uint8, std::unordered_map<BotRoles, uint32>> AllowedClassRoleNr(uint8 groupSize = 5);
        static std::unordered_map<uint8, std::unordered_map<BotRoles, uint32>> AllowedClassRoleNr(Player* player, uint8 groupSize = 5);

        /// 执行动作主逻辑（自动寻队邀请动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自动寻队邀请动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 邀请附近玩家组队动作：扫描附近满足条件的玩家或机器人邀请组队
    class InviteNearbyToGroupAction : public InviteToGroupAction
    {
    public:
        /// 构造函数：初始化邀请附近玩家组队动作
        InviteNearbyToGroupAction(PlayerbotAI* ai, std::string name = "invite nearby") : InviteToGroupAction(ai, name) {}
        /// 执行动作主逻辑（邀请附近玩家组队动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（邀请附近玩家组队动作）
        virtual bool isUseful() override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（邀请附近玩家组队动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    // Generic guid member finder (通用成员 GUID 查找逻辑)
    class FindGuildMembers
    {
    public:
        /// 构造函数：初始化公会成员遍历辅助类
        FindGuildMembers() {};

        void operator()(Player* player) { data.push_back(player); };
        /// 获取操作或检查的执行结果
        std::vector<Player*> const GetResult() { return data; };
    private:
        std::vector<Player*> data;
    };

    /// 邀请公会成员组队动作：邀请附近同公会成员加入队伍或团队
    class InviteGuildToGroupAction : public InviteNearbyToGroupAction
    {
    public:
        /// 构造函数：初始化邀请公会成员组队动作
        InviteGuildToGroupAction(PlayerbotAI* ai, std::string name = "invite guild") : InviteNearbyToGroupAction(ai, name) {}
        /// 执行动作主逻辑（邀请公会成员组队动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（邀请公会成员组队动作）
        virtual bool isUseful() override { return bot->GetGuildId() && InviteNearbyToGroupAction::isUseful(); };

    private:
        /// 获取并筛选当前在线的同公会成员列表
        std::vector<Player*> getGuildMembers();
    };
}
