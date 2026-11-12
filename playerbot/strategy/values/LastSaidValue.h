// 策略值头文件：LastSaidValue（上次发言与表情动作时间戳）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：按限定符记录机器人上次发送聊天消息的时间戳（默认提前 120 秒以便立即可用）
    class LastSaidValue : public ManualSetValue<time_t>, public Qualified
    {
    public:
        LastSaidValue(PlayerbotAI* ai) : ManualSetValue<time_t>(ai, time(0) - 120, "last said"), Qualified() {}
    };

    // 手动设置值：按限定符记录机器人上次执行表情动作的时间戳
    class LastEmoteValue : public ManualSetValue<time_t>, public Qualified
    {
    public:
        LastEmoteValue(PlayerbotAI* ai) : ManualSetValue<time_t>(ai, time(0) - 120, "last emote"), Qualified() {}
    };
}
