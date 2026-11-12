// 策略值头文件：VendorValues（全服商人商品索引、卖家查询及商人有用物品判断）
#pragma once

#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/NamedObjectContext.h"

class PlayerbotAI;

namespace ai
{      
    //                              itemId, entry | 映射结构：物品 ID -> 出售商人的生物 Entry
    typedef std::unordered_multimap<uint32, int32> VendorMap;

    //Returns the vendor map of all entries | 返回全服所有商人与商品的全局映射表
    // 单例值计算器：构建“物品 ID -> 出售该物品的 NPC 商人 Entry”全局索引表
    class VendorMapValue : public SingleCalculatedValue<VendorMap*>
    {
    public:
        VendorMapValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "vendor map") {}

        virtual VendorMap* Calculate() override;
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "vendor map"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "item"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns all creatures and game objects and the items they sell.";
        }
        virtual std::vector<std::string> GetUsedValues() { return {  }; }
#endif 
    };

    //Returns the entries that sell a specific item | 返回出售指定物品的所有商人 Entry 列表
    // 值计算器：查询出售指定物品 ID 的所有非限量 NPC 商人 Entry 列表
    class ItemVendorListValue : public SingleCalculatedValue<std::list<int32>>, public Qualified
    {
    public:
        ItemVendorListValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "item vendor list"), Qualified() {}

        virtual std::list<int32> Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "item vendor list"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "item"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns all vendors that sell a specific item.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "vendor map" }; }
#endif 
    };

    // 布尔值计算器：判断指定 NPC 商人是否出售机器人当前需要且买得起的有用物品
    class VendorHasUsefulItemValue : public BoolCalculatedValue, public Qualified
    {
    public:
        VendorHasUsefulItemValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "vendor has useful item",2), Qualified() {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "vendor has useful item"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "item"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns true if the specified vendor sells a usefull item.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "item usage" }; }
#endif 
    };
}

