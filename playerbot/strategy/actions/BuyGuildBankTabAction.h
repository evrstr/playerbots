#pragma once
#include "GenericActions.h"

namespace ai
{
#ifndef MANGOSBOT_ZERO
    /// 购买公会银行标签页动作：公会会长自动购买可用公会银行页
    class BuyGuildBankTabAction : public Action
    {
    public:
        /// 构造函数：初始化购买公会银行标签页动作
        BuyGuildBankTabAction(PlayerbotAI* ai) : Action(ai, "buy guild bank tab") {}
        /// 执行动作主逻辑（购买公会银行标签页动作）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（购买公会银行标签页动作）
        virtual bool isPossible() override;
        /// 判断当前状态下该动作是否可用/有效（购买公会银行标签页动作）
        virtual bool isUseful() override;
    };
#endif
}
