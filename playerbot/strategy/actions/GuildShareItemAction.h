#pragma once
#include "playerbot/strategy/Action.h"
#include "playerbot/strategy/values/GuildValues.h"

namespace ai
{
    /// 公会共享物品动作：将多余的可共享物品通过公会银行或邮寄共享给公会成员
    class GuildShareItemAction : public Action
    {
    public:
        /// 构造函数：初始化公会共享物品动作
        GuildShareItemAction(PlayerbotAI* ai) : Action(ai, "guild share item") {}

        /// 执行动作主逻辑（公会共享物品动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（公会共享物品动作）
        bool isUseful() override;
    };
}
