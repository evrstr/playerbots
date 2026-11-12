
#include "playerbot/playerbot.h"
#include "AiObject.h"
#include "Entities/Player.h"

// 构造 AI 对象并绑定机器人指针、AI 对象上下文与聊天助手
AiObject::AiObject(PlayerbotAI* ai) :
    PlayerbotAIAware(ai),
    bot(ai->GetBot()),
    context(ai->GetAiObjectContext()),
    chat(ai->GetChatHelper())
{
}

// 获取当前机器人跟随或归属的主人玩家
Player* AiObject::GetMaster()
{
    return ai->GetMaster();
}
