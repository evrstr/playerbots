/// 聊天指令处理策略头文件
#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    /// 策略：监听并响应主人或玩家发送的各类聊天控制指令
    class ChatCommandHandlerStrategy : public PassTroughStrategy
    {
    public:
        ChatCommandHandlerStrategy(PlayerbotAI* ai);
        std::string getName() override { return "chat"; }

        static constexpr const char* CastNcTrigger = "castnc";
        static constexpr const char* CastNcAction = "cast custom nc spell";

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "chat"; } //Must equal internal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() 
        {
            return "This strategy will make bots respond to various chat commands.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { }; }
#endif

    private:
        void InitReactionTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
