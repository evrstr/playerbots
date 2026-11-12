#pragma once
#include "GenericActions.h"
#include "playerbot/strategy/values/ItemUsageValue.h"

namespace ai
{
    // UsageBoughtList[usage][itemId]=count (按用途记录已购买物品数量：UsageBoughtList[用途][物品ID]=数量)
    using BoughtList = std::unordered_map<uint32, uint32>;
    using UsageBoughtList = std::unordered_map<ItemUsage, BoughtList>;

    /// 购买物品指令动作：向附近商人购买指定物品、消耗品或弹药
    class BuyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化购买物品指令动作
        BuyAction(PlayerbotAI* ai, std::string name = "buy") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（购买物品指令动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 向商人 NPC 购买指定数量和 ID 的物品
        bool BuyItem(Player* requester, VendorItemData const* tItems, ObjectGuid vendorguid, const ItemPrototype* proto, UsageBoughtList& bought, ItemUsage usage = ItemUsage::ITEM_USAGE_NONE);

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "buy"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make bots buy items from a nearby vendor.\n"
                "Usage: buy [itemlink]\n"
                "Example: buy usefull (buy based on item use)\n"
                "Example: buy [itemlink]\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return { "equip upgrades" }; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs", "item count", "item usage", "free money for"}; }
#endif 
    };

    /// 回购物品动作：从商人处购回此前误卖出的物品
    class BuyBackAction : public BuyAction
    {
    public:
        /// 构造函数：初始化回购物品动作
        BuyBackAction(PlayerbotAI* ai, std::string name = "buyback") : BuyAction(ai, name) {}
        /// 执行动作主逻辑（回购物品动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "buyback"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make bots retrieve items after being sold.\n"
                "Usage: buyback [itemlink]\n"
                "Example: buyback all (try to get all items back)\n"
                "Example: buyback [itemlink] (get a specific item back)\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return { "" }; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs", "item count", "bag space"}; }
#endif 
    };
}
