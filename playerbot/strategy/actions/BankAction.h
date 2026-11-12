#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 银行存取指令动作：与银行管理员交互以查看、存入或取出物品
    class BankAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化银行存取指令动作
        BankAction(PlayerbotAI* ai) : ChatCommandAction(ai, "bank") {}
        /// 执行动作主逻辑（银行存取指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（银行存取指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bank"; }
        virtual std::string GetHelpDescription()
        {
            return "This command allows the bot to interact with the bank:\n"
                "Usage: bank [command] [itemlink/itemid]\n"
                "Example: bank ? (lists items in bank)\n"
                "Example: bank -[itemlink] (withdraws item)\n"
                "Example: bank [itemlink] (deposits specified item)";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 

    private:
        /// 解析并执行聊天指令子命令（银行存取指令动作）
        bool ExecuteCommand(Player* requester, const std::string& text, Unit* bank);
        /// 按类别或名称汇总列出背包中的物品清单
        void ListItems(Player* requester);
        /// 从个人银行或公会银行取出指定物品
        bool Withdraw(Player* requester, const uint32 itemid);
        /// 将指定物品存入个人银行或公会银行
        bool Deposit(Player* requester, Item* pItem);
        /// 在银行及银行背包栏位中查找指定物品
        Item* FindItemInBank(uint32 ItemId);

    public:
        /// 自动将背包中适合存放的多余物资存入银行或公会银行
        bool AutoDeposit();
        /// 自动从银行或公会银行提取当前所需的物资或消耗品
        bool AutoWithdraw();
    };
}
