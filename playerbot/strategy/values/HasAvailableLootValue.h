// 策略值头文件：HasAvailableLootValue（是否存在可前往拾取的战利品）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 布尔值计算器：当尚未进入直接拾取距离且拾取范围内存在可用战利品时返回 true
    class HasAvailableLootValue : public BoolCalculatedValue
    {
    public:
        HasAvailableLootValue(PlayerbotAI* ai) : BoolCalculatedValue(ai) {}

    public:
        virtual bool Calculate() override
        {
            return !AI_VALUE(bool, "can loot") &&
                    AI_VALUE(LootObjectStack*, "available loot")->CanLoot(ai->GetRange("loot"));
        }
    };
}
