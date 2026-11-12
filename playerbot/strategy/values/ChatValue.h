// 策略值头文件：ChatValue（机器人当前默认聊天频道类型）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：保存机器人发送消息使用的默认频道（初始为密语 CHAT_MSG_WHISPER）
    class ChatValue : public ManualSetValue<ChatMsg>
    {
    public:
        ChatValue(PlayerbotAI* ai, std::string name = "chat") : ManualSetValue<ChatMsg>(ai, CHAT_MSG_WHISPER, name) {}
    };
}
