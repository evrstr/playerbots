#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 接受决斗动作：根据等级与生命值条件接受或拒绝决斗邀请
    class AcceptDuelAction : public Action
    {
    public:
        /// 构造函数：初始化接受决斗动作
        AcceptDuelAction(PlayerbotAI* ai) : Action(ai, "accept duel")
        {}

        /// 执行动作主逻辑（接受决斗动作）
        virtual bool Execute(Event& event) override
        {
            WorldPacket p(event.getPacket());

            ObjectGuid flagGuid;
            p >> flagGuid;
            ObjectGuid playerGuid;
            p >> playerGuid;

            // do not auto duel with low hp or below certain level (低生命值或低于最低等级时不自动接受决斗)
            if (bot->GetLevel() < sPlayerbotAIConfig.botAcceptDuelMinimumLevel
                || ((!ai->HasRealPlayerMaster() || (ai->GetMaster() && ai->GetMaster()->GetObjectGuid() != playerGuid)) && AI_VALUE2(uint8, "health", "self target") < 90))
            {
                WorldPacket packet(CMSG_DUEL_CANCELLED, 8);
                packet << flagGuid;
                bot->GetSession()->HandleDuelCancelledOpcode(packet);
            }

            WorldPacket packet(CMSG_DUEL_ACCEPTED, 8);
            packet << flagGuid;
            bot->GetSession()->HandleDuelAcceptedOpcode(packet);

            ai->ResetStrategies();
            return true;
        }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "accept duel"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action accepts or declines duel invitations based on conditions.\n"
                "The bot will decline if below minimum level or low health (unless from master).\n"
                "After accepting, combat strategies are reset for the duel.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

}
