#pragma once
#include "playerbot/RandomPlayerbotMgr.h"
#include "GenericActions.h"

namespace ai
{
    /// 离开队伍指令动作：让机器人退出当前队伍或团队
    class LeaveGroupAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化离开队伍指令动作
        LeaveGroupAction(PlayerbotAI* ai, std::string name = "leave") : ChatCommandAction(ai, name) {}

        /// 执行动作主逻辑（离开队伍指令动作）
        virtual bool Execute(Event& event) override
        {            
            Player* master = event.getOwner();

            return Leave(master);
        }

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（离开队伍指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

        /// 离开当前战场或 LFG 队列
        virtual bool Leave(Player* player);
    };

    /// 队伍控制指令动作：处理对队伍成员的通用管理命令（如解散、踢出等）
    class PartyCommandAction : public LeaveGroupAction 
    {
    public:
        /// 构造函数：初始化队伍控制指令动作
        PartyCommandAction(PlayerbotAI* ai) : LeaveGroupAction(ai, "party command") {}

        /// 执行动作主逻辑（队伍控制指令动作）
        virtual bool Execute(Event& event) override
        {
            WorldPacket& p = event.getPacket();
            p.rpos(0);
            uint32 operation;
            std::string member;

            p >> operation >> member;

            if (operation != PARTY_OP_LEAVE)
                return false;

            Player* master = GetMaster();
            if (master && member == master->GetName())
                return Leave(bot);

            return false;
        }
    };

    /// 踢出队伍动作：将指定玩家或机器人从队伍中移出
    class UninviteAction : public LeaveGroupAction 
    {
    public:
        /// 构造函数：初始化踢出队伍动作
        UninviteAction(PlayerbotAI* ai) : LeaveGroupAction(ai, "uninvite") {}

        /// 执行动作主逻辑（踢出队伍动作）
        virtual bool Execute(Event& event) override
        {
            WorldPacket& p = event.getPacket();

            if (p.GetOpcode() == CMSG_GROUP_UNINVITE)
            {
                p.rpos(0);
                std::string membername;
                p >> membername;

                // player not found (未找到指定玩家)
                if (!normalizePlayerName(membername))
                {
                    return false;
                }

                if (bot->GetName() == membername)
                    return Leave(bot);
            }

            if (p.GetOpcode() == CMSG_GROUP_UNINVITE_GUID)
            {
                p.rpos(0);
                ObjectGuid guid;
                p >> guid;

                if (bot->GetObjectGuid() == guid)
                    return Leave(bot);
            }

            return false;
        }
    };

    /// 距离过远离队动作：当机器人与队伍成员距离过远且长时间无法汇合时自动离队
    class LeaveFarAwayAction : public LeaveGroupAction 
    {
    public:
        /// 构造函数：初始化距离过远离队动作
        LeaveFarAwayAction(PlayerbotAI* ai) : LeaveGroupAction(ai, "leave far away") {}

        /// 执行动作主逻辑（距离过远离队动作）
        virtual bool Execute(Event& event) override
        {
            return Leave(ai->GetGroupMaster());
        }

        /// 判断当前状态下该动作是否可用/有效（距离过远离队动作）
        virtual bool isUseful() override;

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（距离过远离队动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
