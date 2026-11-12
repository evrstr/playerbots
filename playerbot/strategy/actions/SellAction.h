#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 出售物品指令动作：向附近商人出售背包中的垃圾、指定或多余物品
    class SellAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化出售物品指令动作
        SellAction(PlayerbotAI* ai, std::string name = "sell") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（出售物品指令动作）
        virtual bool Execute(Event& event) override;

        /// 向商人出售指定物品或背包内满足条件的物品
        bool Sell(Player* requester, FindItemVisitor* visitor);
        /// 向商人出售指定物品或背包内满足条件的物品
        bool Sell(Player* requester, Item* item);

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "sell"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make bots sell items to a nearby vendor.\n"
                "Usage: sell qualifier or itemlinks\n"
                "Example: sell vendor (sell based on item use)\n"
                "Example: sell gray\n"
                "Example: sell [itemlink] [itemlink]\n"
                "Example: sell equip \n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs", "item usage" }; }
#endif 
    };
}
