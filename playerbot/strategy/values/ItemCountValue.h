// 策略值头文件：ItemCountValue（背包、装备与银行物品数量及列表查询）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/ItemVisitors.h"

namespace ai
{
    // 值计算器：统计背包和已装备栏中匹配限定符的物品总数量
    class ItemCountValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        ItemCountValue(PlayerbotAI* ai, std::string name = "item count") : Uint32CalculatedValue(ai, name), Qualified() {}
        virtual uint32 Calculate() override;
    };

    // 列表计算器：获取背包和已装备栏中匹配限定符的物品指针列表
    class InventoryItemValue : public CalculatedValue<std::list<Item*> >, public Qualified
    {
    public:
        InventoryItemValue(PlayerbotAI* ai, std::string name = "inventory items") : CalculatedValue<std::list<Item*> >(ai, name), Qualified() {}
        virtual std::list<Item*> Calculate() override;
    };

    // 值计算器：统计银行中匹配限定符的物品总数量
    class BankItemCountValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        BankItemCountValue(PlayerbotAI* ai, std::string name = "bank item count") : Uint32CalculatedValue(ai, name), Qualified() {}
        virtual uint32 Calculate() override;
    };

    // 列表计算器：获取银行中匹配限定符的物品指针列表
    class BankItemValue : public CalculatedValue<std::list<Item*>>,
                               public Qualified
    {
    public:
        BankItemValue(PlayerbotAI* ai, std::string name = "bank items") : CalculatedValue<std::list<Item*>>(ai, name), Qualified() {}
        virtual std::list<Item*> Calculate() override;
    };

    // 列表计算器：获取背包及已装备物品匹配限定符的模板 ID 列表
    class InventoryItemIdValue : public CalculatedValue<std::list<uint32> >, public Qualified
    {
    public:
        InventoryItemIdValue(PlayerbotAI* ai, std::string name = "inventory item ids") : CalculatedValue<std::list<uint32> >(ai, name), Qualified() {}
        virtual std::list<uint32> Calculate() override { std::list<uint32> retVal;  for (auto& item : AI_VALUE2(std::list<Item*>, "inventory items", getQualifier())) { ItemPrototype const* proto = item->GetProto();  retVal.push_back(proto->ItemId);} return retVal;};
    };

    // 列表计算器：获取当前已装备且自带可使用法术（非被动饰品）的饰品列表
    class EquipedUsableTrinketValue : public CalculatedValue<std::list<Item*> >, public Qualified
    {
    public:
        EquipedUsableTrinketValue(PlayerbotAI* ai) : CalculatedValue<std::list<Item*> >(ai), Qualified() {}
        virtual std::list<Item*> Calculate() override;
    };
}
