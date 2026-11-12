#pragma once
#include "QueryItemUsageAction.h"

namespace ai
{
    /// 交易状态响应动作：处理服务端交易状态更新封包并自动配合完成交易流程
    class TradeStatusAction : public QueryItemUsageAction
    {
    public:
        /// 构造函数：初始化交易状态响应动作
        TradeStatusAction(PlayerbotAI* ai) : QueryItemUsageAction(ai, "accept trade") {}
        /// 执行动作主逻辑（交易状态响应动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 向目标玩家发起交易窗口请求
        void BeginTrade();
        /// 校验当前交易窗口状态及双方放置的物品是否符合条件
        bool CheckTrade();
        /// 计算购买、修理或制造所需的总金币花费
        int32 CalculateCost(Player *player, bool sell);
    };
}
