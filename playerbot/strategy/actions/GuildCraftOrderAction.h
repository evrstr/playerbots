#pragma once
#include "playerbot/strategy/Action.h"
#include "playerbot/strategy/values/GuildValues.h"

namespace ai
{
    /// 公会制造委托动作：响应并执行公会成员提交的专业制造代工订单
    class GuildCraftOrderAction : public Action
    {
    public:
        /// 构造函数：初始化公会制造委托动作
        GuildCraftOrderAction(PlayerbotAI* ai) : Action(ai, "guild craft order") {}

        /// 执行动作主逻辑（公会制造委托动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（公会制造委托动作）
        bool isUseful() override;

    private:
        /// 查找能够制作指定目标物品的专业技能法术
        uint32 FindCraftSpell(uint32 itemId);
    };
}
