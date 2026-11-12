// 策略值头文件：BankValues（个人银行与公会银行存取需求判断）
#pragma once
#include "playerbot/strategy/Value.h"
#include "ItemUsageValue.h"

namespace ai
{
    // 布尔值计算器：判断背包内是否有需要存入个人银行的物品
    class ShouldBankDepositValue : public BoolCalculatedValue
    {
    public:
        ShouldBankDepositValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should bank deposit", 5) {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断个人银行内是否有需要取出的物品
    class ShouldBankWithdrawValue : public BoolCalculatedValue
    {
    public:
        ShouldBankWithdrawValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should bank withdraw", 5) {}
        virtual bool Calculate() override;
    };

#ifndef MANGOSBOT_ZERO
    // 布尔值计算器：判断背包内是否有适合存入公会银行共享的材料或物品
    class ShouldGuildBankDepositValue : public BoolCalculatedValue
    {
    public:
        ShouldGuildBankDepositValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should guild bank deposit", 5) {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断公会银行第 0 页是否有机器人可装备或制作所需的物品
    class ShouldGuildBankWithdrawValue : public BoolCalculatedValue
    {
    public:
        ShouldGuildBankWithdrawValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should guild bank withdraw", 5) {}
        virtual bool Calculate() override;
    };
#endif
}
