#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 交易指令动作：发起或响应与目标玩家的交易窗口操作（放物品/金币/确认交易）
    class TradeAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化交易指令动作
        TradeAction(PlayerbotAI* ai) : ChatCommandAction(ai, "trade") {}
        /// 执行动作主逻辑（交易指令动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 将指定物品放入交易窗口槽位
        bool TradeItem(const Item& item, int8 slot);

    private:
        static std::map<std::string, uint32> slots;
    };
}
