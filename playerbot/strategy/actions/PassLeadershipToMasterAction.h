#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 移交队长给主人动作：将队伍队长权限移交给机器人主人
    class PassLeadershipToMasterAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化移交队长给主人动作
        PassLeadershipToMasterAction(PlayerbotAI* ai, std::string name = "leader", std::string message = "Passing leader to you!") : ChatCommandAction(ai, name), message(message) {}

        /// 将队伍队长权限移交给指定玩家
        virtual Player* PassLeaderTo(Event& event) { return GetMaster(); };

        /// 执行动作主逻辑（移交队长给主人动作）
        virtual bool Execute(Event& event) override
        {
            Player* passLeaderTo = PassLeaderTo(event);
            if (passLeaderTo && passLeaderTo != bot && bot->GetGroup() && bot->GetGroup()->IsMember(passLeaderTo->GetObjectGuid()))
            {
                WorldPacket p(SMSG_GROUP_SET_LEADER, 8);
                p << passLeaderTo->GetObjectGuid();
                bot->GetSession()->HandleGroupSetLeaderOpcode(p);
                
                if (!message.empty())
                    ai->TellPlayerNoFacing(passLeaderTo, message);

                if (sRandomPlayerbotMgr.IsRandomBot(bot))
                {
                    ai->ResetStrategies();
                    ai->Reset();
                }
                
                return true;
            }

            return false;
        }

        /// 判断当前状态下该动作是否可用/有效（移交队长给主人动作）
        virtual bool isUseful() override
        {
            return ai->IsAlt() && bot->GetGroup() && bot->GetGroup()->IsLeader(bot->GetObjectGuid());
        }

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（移交队长给主人动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    protected:
        std::string message;
    };

    /// 移交队长动作：在特定条件（如进入未知副本）下将队长权限移交给队友
    class GiveLeaderAction : public PassLeadershipToMasterAction 
    {
    public:
        /// 构造函数：初始化移交队长动作
        GiveLeaderAction(PlayerbotAI* ai, std::string message = "Lead the way!") : PassLeadershipToMasterAction(ai, "give leader", message) {}

        /// 将队伍队长权限移交给指定玩家
        virtual Player* PassLeaderTo(Event& event) { return event.getOwner(); };

        /// 判断当前状态下该动作是否可用/有效（移交队长动作）
        virtual bool isUseful() override
        {
            return bot->GetGroup() && bot->GetGroup()->IsLeader(bot->GetObjectGuid());
        }        
    };    
}
