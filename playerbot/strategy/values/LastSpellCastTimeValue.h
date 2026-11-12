// 策略值头文件：LastSpellCastTimeValue（上次施放特定法术的时间戳）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：按法术限定符记录上一次施放该法术的时间戳
    class LastSpellCastTimeValue : public ManualSetValue<time_t>, public Qualified
    {
    public:
        LastSpellCastTimeValue(PlayerbotAI* ai) : ManualSetValue<time_t>(ai, 0), Qualified() {}
    };
}
