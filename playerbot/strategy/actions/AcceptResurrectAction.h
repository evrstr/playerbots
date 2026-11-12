#pragma once

#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 接受复活动作：死亡状态下收到玩家复活请求时回复接受复活封包
    class AcceptResurrectAction : public Action {
    public:
        /// 构造函数：初始化接受复活动作
        AcceptResurrectAction(PlayerbotAI* ai) : Action(ai, "accept resurrect") {}

        /// 执行动作主逻辑（接受复活动作）
        virtual bool Execute(Event& event) override
        {
            if (!sServerFacade.IsAlive(bot))
            {
                WorldPacket p(event.getPacket());
                p.rpos(0);
                ObjectGuid guid;
                p >> guid;

                WorldPacket packet(CMSG_RESURRECT_RESPONSE, 8+1);
                packet << guid;
                packet << uint8(1);                                       // accept (接受)
                bot->GetSession()->HandleResurrectResponseOpcode(packet); // queue the packet to get around race condition (将封包入队处理以避免竞态条件)
                return true;
            }

            return false;
        }
        
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "accept resurrect"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action clicks the accept button asked if it wants to be resurrected by a player.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

}
