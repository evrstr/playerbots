#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 切换聊天频道指令动作：配置机器人的发言与回复频道设置
    class ChangeChatAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化切换聊天频道指令动作
        ChangeChatAction(PlayerbotAI* ai) : ChatCommandAction(ai, "chat") {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "chat"; }
        virtual std::string GetHelpDescription()
        {
            return "This command changes the bot's chat channel settings.\n"
                   "Usage: chat [channel]\n"
                   "Available channels: party, guild, whisper, general\n"
                   "Example: chat party (switches to party chat)\n"
                   "Example: chat whisper (enables private messaging)";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
        /// 执行动作主逻辑（切换聊天频道指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（切换聊天频道指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
