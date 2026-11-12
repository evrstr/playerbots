// 策略值头文件：TradeValues（可赠送队友的闲置物品与可附魔装备列表）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 物品列表计算器：筛选机器人背包中自身不需要但指定交易对象可以使用或需要的非绑定物品
    class ItemsUsefulToGiveValue : public CalculatedValue< std::list<Item*>>, public Qualified
    {
    public:
        ItemsUsefulToGiveValue(PlayerbotAI* ai, std::string name = "useful to give") : CalculatedValue(ai, name), Qualified() {}
        std::list<Item*> Calculate() override;

    private:
        bool IsTradingItem(uint32 entry);
    };

    // 物品列表计算器：筛选交易对象身上或自己背包中适合当前机器人附魔的装备
    class ItemsUsefulToEnchantValue : public CalculatedValue< std::list<Item*>>, public Qualified
    {
    public:
        ItemsUsefulToEnchantValue(PlayerbotAI* ai, std::string name = "useful to enchant") : CalculatedValue(ai, name), Qualified() {}
        std::list<Item*> Calculate() override;
    };
}