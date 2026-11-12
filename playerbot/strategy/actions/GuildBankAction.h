#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 公会银行指令动作：查看或存取公会银行指定标签页中的物品与金币
    class GuildBankAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化公会银行指令动作
        GuildBankAction(PlayerbotAI* ai) : ChatCommandAction(ai, "guild bank") {}
        /// 执行动作主逻辑（公会银行指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（公会银行指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 执行动作主逻辑（公会银行指令动作）
        bool Execute(std::string text, GameObject* bank, Player* requester);
        /// 将角色背包中的物品移动到银行栏位
        bool MoveFromCharToBank(Item* item, GameObject* bank, Player* requester);

    public:
        /// 自动将背包中适合存放的多余物资存入银行或公会银行
        bool AutoDeposit(GameObject* bank);
        /// 自动从银行或公会银行提取当前所需的物资或消耗品
        bool AutoWithdraw(GameObject* bank);
    };
}
