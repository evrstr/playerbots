#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 拍卖行动作基类：前往附近拍卖师处寄售物品或处理拍卖指令
    class AhAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化拍卖行动作基类
        AhAction(PlayerbotAI* ai, std::string name = "ah") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（拍卖行动作基类）
        virtual bool Execute(Event& event) override;

    protected:
        /// 获取拍卖上架的默认持续时间配置
        static uint32 GetPostTime();
        /// 将背包内物品发布到拍卖行挂单出售
        bool PostItem(Player* requester, Item* item, uint32 price, Unit* auctioneer, uint32 time);

    private:
        /// 解析并执行聊天指令子命令（拍卖行动作基类）
        virtual bool ExecuteCommand(Player* requester, std::string text, Unit* auctioneer);

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "ah"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make bots auction items to a nearby auction houses.\n"
                "Usage: ah [itemlink] <money>\n"
                "Example: ah vendor (post items based on item use)\n"
                "Example: ah [itemlink] 5g\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs", "inventory items", "item usage", "free money for" }; }
#endif
    };

    /// 拍卖行竞拍动作：在预算范围内对指定拍卖行物品进行出价竞拍
    class AhBidAction : public AhAction
    {
    public:
        /// 构造函数：初始化拍卖行竞拍动作
        AhBidAction(PlayerbotAI* ai) : AhAction(ai, "ah bid") {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "ah bid"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make bots bid on a specific item with a specific budget on a nearby auctionhouse.\n"
                "The highest item/gold auction will be used that falls below the given budget.\n"
                "Usage: ah bid [itemlink] <money>\n"
                "Example: ah bid vendor (bid on items based on item use)\n"
                "Example: ah bid [itemlink] 5g\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs", "item usage", "free money for" }; }
#endif 
    private:
        /// 解析并执行聊天指令子命令（拍卖行竞拍动作）
        virtual bool ExecuteCommand(Player* requester, std::string text, Unit* auctioneer);
        /// 对指定的拍卖行物品进行竞拍出价
        bool BidItem(Player* requester, AuctionEntry* auction, uint32 price, Unit* auctioneer, bool isBuyout, std::string reason = "");
    };

    /// 拍卖管理指令动作：列出、发布或取消机器人自身的拍卖行挂单
    class AuctionCommandAction : public AhAction
    {
    public:
        /// 构造函数：初始化拍卖管理指令动作
        AuctionCommandAction(PlayerbotAI* ai) : AhAction(ai, "auction") {}
        /// 执行动作主逻辑（拍卖管理指令动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "auction"; }
        virtual std::string GetHelpDescription()
        {
            return "This command lists, posts or cancels the bot's own auctions.\n"
                "Usage: auction (list own auctions in every auction house)\n"
                "Usage: auction add [itemlink] <money> (post at a nearby auctioneer, money is the stack buyout)\n"
                "Usage: auction remove [itemlink] or auction remove <auction id> (cancel at a nearby auctioneer)\n"
                "Example: auction add [itemlink] 5g\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs", "inventory items" }; }
#endif

    private:
        /// 在附近区域搜寻可用的拍卖师 NPC
        Unit* FindAuctioneer();
        /// 列出机器人当前已挂出的拍卖行订单
        bool ListAuctions(Player* requester);
        /// 在拍卖行创建并上架新的拍卖物品
        bool AddAuction(Player* requester, const std::string& param, Unit* auctioneer);
        /// 取消并撤回满足条件的自身拍卖挂单
        bool RemoveAuctions(Player* requester, const std::string& param, Unit* auctioneer);
    };
}
