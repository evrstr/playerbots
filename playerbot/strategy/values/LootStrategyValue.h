// 策略值头文件：LootStrategyValue（拾取策略子开关配置）
#pragma once
#include "playerbot/LootObjectStack.h"
#include "playerbot/strategy/Value.h"
#include "SubStrategyValue.h"

namespace ai
{
    // 子策略值：控制机器人允许拾取的物品类别（装备/任务/专业/分解/消耗品/售卖/垃圾）
    class LootStrategyValue : public SubStrategyValue
    {
    public:
        LootStrategyValue(PlayerbotAI* ai, std::string defaultValue = "equip,quest,skill,disenchant,use,vendor", std::string name = "loot strategy", std::string allowedValues = "equip,quest,skill,disenchant,use,vendor,trash") : SubStrategyValue(ai, defaultValue, name, allowedValues) {}

        virtual void Set(std::string newValue) override;

        static bool CanLoot(ItemQualifier& itemQualifier, PlayerbotAI* ai);
    };
}
