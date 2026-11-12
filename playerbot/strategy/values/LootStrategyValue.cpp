// 策略值实现：LootStrategyValue（拾取策略解析与物品拾取许可判定）

#include "playerbot/playerbot.h"
#include "LootStrategyValue.h"
#include "playerbot/strategy/values/ItemUsageValue.h"

using namespace ai;

// 更新拾取策略字符串（兼容旧版数值参数格式）
void LootStrategyValue::Set(std::string newValue)
{
    //Backwards compatibility | 向后兼容旧版拾取策略枚举值
    if (newValue == "normal")
        newValue = "equip,vendor,quest,skill,use";
    if(newValue == "disenchant")
        newValue = "equip,vendor,disenchant,quest,skill,use";
    if (newValue == "gray")
        newValue = "equip,vendor,disenchant,quest,skill,use,vendor";
    if (newValue == "all")
        newValue = "equip,vendor,disenchant,quest,skill,use,vendor,trash";

    SubStrategyValue::Set(newValue);
}

// 根据物品用途及当前启用的拾取策略子项判断是否允许拾取该物品
bool LootStrategyValue::CanLoot(ItemQualifier& itemQualifier, PlayerbotAI* ai)
{
    AiObjectContext* context = ai->GetAiObjectContext();

    ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", itemQualifier.GetQualifier());

    if (usage == ItemUsage::ITEM_USAGE_AMMO)
        return true;

    if(usage == ItemUsage::ITEM_USAGE_GUILD_TASK)
        return true;

    if (usage == ItemUsage::ITEM_USAGE_FORCE_NEED)
       return true;

    if (usage == ItemUsage::ITEM_USAGE_FORCE_GREED)
        return true;

    std::vector<std::string> strategies = StrSplit(AI_VALUE(std::string, "loot strategy"), ",");
    
    for (std::string& strategy : strategies) //equip,quest,skill,disenchant,use,vendor,trash | 按配置项匹配：装备、任务、技能、分解、使用、卖店、垃圾
    {
        if (strategy == "equip" && usage == ItemUsage::ITEM_USAGE_EQUIP)
            return true;
        if (strategy == "quest" && usage == ItemUsage::ITEM_USAGE_QUEST)
            return true;
        if (strategy == "skill" && usage == ItemUsage::ITEM_USAGE_SKILL)
            return true;
        if (strategy == "disenchant" && usage == ItemUsage::ITEM_USAGE_DISENCHANT)
            return true;
        if (strategy == "use" && usage == ItemUsage::ITEM_USAGE_USE)
            return true;
        if (strategy == "vendor" && (usage == ItemUsage::ITEM_USAGE_BAD_EQUIP || usage == ItemUsage::ITEM_USAGE_VENDOR || usage == ItemUsage::ITEM_USAGE_AH || usage == ItemUsage::ITEM_USAGE_BROKEN_AH))
            return true;
        if (strategy == "trash" && usage == ItemUsage::ITEM_USAGE_NONE)
            return true;
    }

    return false;
}