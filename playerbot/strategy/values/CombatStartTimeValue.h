// 策略值头文件：CombatStartTimeValue（战斗开始时间戳）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：记录机器人进入战斗状态的时间戳
    class CombatStartTimeValue : public ManualSetValue<time_t>, public Qualified
    {
    public:
        CombatStartTimeValue(PlayerbotAI* ai) : ManualSetValue<time_t>(ai, 0), Qualified() {}
    };
}
