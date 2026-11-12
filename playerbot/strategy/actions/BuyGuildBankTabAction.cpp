
#include "playerbot/playerbot.h"
#include "BuyGuildBankTabAction.h"
#include "Guilds/Guild.h"
#include "Guilds/GuildMgr.h"

using namespace ai;

#ifndef MANGOSBOT_ZERO
/// 判断执行该动作的前置条件是否满足（购买公会银行标签页动作）
bool BuyGuildBankTabAction::isPossible()
{
    return bot->GetGuildId() != 0;
}

/// 判断当前状态下该动作是否可用/有效（购买公会银行标签页动作）
bool BuyGuildBankTabAction::isUseful()
{
    if (!bot->GetGuildId())
        return false;

    Guild* guild = sGuildMgr.GetGuildById(bot->GetGuildId());
    if (!guild)
        return false;

    // Only guild leader should buy tabs (仅公会会长可购买公会银行页)
    if (guild->GetLeaderGuid() != bot->GetObjectGuid())
        return false;

    // Only buy the first tab (仅购买第一个标签页)
    if (guild->GetPurchasedTabs() > 0)
        return false;

    uint32 tabCost = GetGuildBankTabPrice(0) * GOLD;
    if (bot->GetMoney() < tabCost)
        return false;

    return true;
}

/// 执行动作主逻辑（购买公会银行标签页动作）
bool BuyGuildBankTabAction::Execute(Event& event)
{
    if (!bot->GetGuildId())
        return false;

    Guild* guild = sGuildMgr.GetGuildById(bot->GetGuildId());
    if (!guild)
        return false;

    if (guild->GetLeaderGuid() != bot->GetObjectGuid())
        return false;

    uint8 nextTab = guild->GetPurchasedTabs();
    if (nextTab >= GUILD_BANK_MAX_TABS)
        return false;

    uint32 tabCost = GetGuildBankTabPrice(nextTab) * GOLD;
    if (bot->GetMoney() < tabCost)
        return false;

    // Buy the tab (购买该银行标签页)
    guild->CreateNewBankTab();
    bot->ModifyMoney(-int32(tabCost));

    // Set permissions for all ranks (为所有公会阶级配置权限)
    uint32 rankCount = guild->GetRanksSize();
    for (uint32 rankId = 0; rankId < rankCount; ++rankId)
    {
        if (rankId == GR_GUILDMASTER)
        {
            // Guild master gets full rights (公会会长拥有全部权限)
            guild->SetBankRightsAndSlots(rankId, nextTab, GUILD_BANK_RIGHT_FULL, WITHDRAW_SLOT_UNLIMITED, true);
        }
        else if (rankId == 1) // Officer rank (官员阶级)
        {
            guild->SetBankRightsAndSlots(rankId, nextTab, GUILD_BANK_RIGHT_FULL, WITHDRAW_SLOT_UNLIMITED, true);
        }
        else
        {
            // Regular members get deposit rights with limited daily withdrawals (普通成员拥有存入权限与受限的每日提取额度)
            uint32 dailySlots = (rankId <= 2) ? 10 : 5;
            guild->SetBankRightsAndSlots(rankId, nextTab, GUILD_BANK_RIGHT_DEPOSIT_ITEM, dailySlots, true);
        }
    }

    return true;
}
#endif
