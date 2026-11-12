#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 装备物品指令动作：将背包中指定的装备穿戴到对应装备栏位
    class EquipAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化装备物品指令动作
        EquipAction(PlayerbotAI* ai, std::string name = "equip") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（装备物品指令动作）
        virtual bool Execute(Event& event) override;
        /// 批量解析并穿戴一组指定的装备
        void EquipItems(Player* requester, ItemIds ids);
        /// 按槽位批量装备指定的物品列表
        void EquipItemsToSlot(Player* requester, ItemIds ids, uint8 targetSlot);
        /// 将背包中的指定物品穿戴到合适的装备栏位
        static void EquipItem(PlayerbotAI* ai, Player* requester, Item* item, bool silent = false);
        /// 将指定物品穿戴到指定的装备槽位
        void EquipItemToSlot(Player* requester, Item* item, uint8 targetSlot);
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（装备物品指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

        /// 判断目标物品是否符合当前附魔配方的施法条件
        bool IsEnchantable(Item* item, uint32 spellid);
        /// 为指定装备或背包物品施放附魔配方
        void EnchantItem(Item* item);

        std::vector<EnchantTemplate> enchants;
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "equip"; }
        virtual std::string GetHelpDescription()
        {
            return "This command makes the bot equip a specific item.\n"
                   "Usage: e [itemlink or itemname]\n"
                   "Example: e [Iron Sword] (equips the specified item if available)";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 

    private:
        /// 将背包中的指定物品穿戴到合适的装备栏位
        void EquipItem(Player* requester, FindItemVisitor* visitor);
        /// 按类别或名称汇总列出背包中的物品清单
        void ListItems(Player* requester);
        /// 查找背包中容量最小的容器栏位
        static uint8 GetSmallestBagSlot(Player* bot);
    };

    /// 自动换装升级动作：扫描背包并自动替换穿戴评分更高的升级装备
    class EquipUpgradesAction : public EquipAction
    {
    public:
        /// 构造函数：初始化自动换装升级动作
        EquipUpgradesAction(PlayerbotAI* ai, std::string name = "equip upgrades") : EquipAction(ai, name) {}
        /// 执行动作主逻辑（自动换装升级动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自动换装升级动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "equip upgrades"; }
        virtual std::string GetHelpDescription()
        {
            return "This command makes the bot equip any available upgrades.\n"
                   "Usage: do equip upgrades\n"
                   "It automatically scans inventory for better gear and equips it.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
