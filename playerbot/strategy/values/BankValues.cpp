// 策略值实现：BankValues（银行及公会银行存取判断逻辑）

#include "playerbot/playerbot.h"
#include "BankValues.h"
#include "ItemCountValue.h"
#include "Guilds/Guild.h"
#include "Guilds/GuildMgr.h"
#include "playerbot/strategy/values/GuildValues.h"

using namespace ai;

// 检查背包中标记为 BANK 用途的物品数量是否大于 0
bool ShouldBankDepositValue::Calculate()
{
    if (AI_VALUE(uint8, "bank space") > 80)
        return false;

    // Check if we have items worth banking | 检查是否有值得存入银行的物品
    uint32 toBankCount = AI_VALUE2(uint32, "item count", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_BANK));

    if (toBankCount == 0)
        return false;

    return true;
}

// 检查个人银行中非保留用途的物品（未达银行保留数量）是否需要取出
bool ShouldBankWithdrawValue::Calculate()
{
    if (AI_VALUE(uint8, "bag space") > 80)
        return false;

    uint32 inBankCount = AI_VALUE2(uint32, "bank item count", "all");
    uint32 stayInBankCount = AI_VALUE2(uint32, "bank item count", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_BANK));

    if (inBankCount == stayInBankCount)
        return false;    

    return true;
}

#ifndef MANGOSBOT_ZERO
// 检查公会权限并筛选适合存入公会银行的商业材料、消耗品及拍卖行多余商品
bool ShouldGuildBankDepositValue::Calculate()
{
    if (!bot->GetGuildId())
        return false;

    Guild* guild = sGuildMgr.GetGuildById(bot->GetGuildId());
    if (!guild)
        return false;

    if (guild->GetPurchasedTabs() == 0)
        return false;

    if (!guild->IsMemberHaveRights(bot->GetGUIDLow(), 0, GUILD_BANK_RIGHT_DEPOSIT_ITEM))
        return false;

    // Look for surplus crafting materials and consumables we can share | 查找可分享的多余制作材料与消耗品
    std::list<Item*> items = AI_VALUE2(std::list<Item*>, "inventory items", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_VENDOR));
    for (auto item : items)
    {
        if (!item)
            continue;

        ItemPrototype const* proto = item->GetProto();
        if (!proto)
            continue;

        // Only deposit trade goods and reagents to guild bank | 仅向公会银行存入商品和施法材料
        if (proto->Class == ITEM_CLASS_TRADE_GOODS || proto->Class == ITEM_CLASS_REAGENT)
        {
            if (proto->Quality >= ITEM_QUALITY_NORMAL && proto->Bonding != BIND_WHEN_PICKED_UP)
                return true;
        }
    }

    // Also deposit items tagged for AH that are trade goods (guild members might need them) | 同步将标记为拍卖行的商品类物品存入公会银行（供公会成员使用）
    std::list<Item*> ahItems = AI_VALUE2(std::list<Item*>, "inventory items", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_AH));
    for (auto item : ahItems)
    {
        if (!item)
            continue;

        ItemPrototype const* proto = item->GetProto();
        if (!proto)
            continue;

        if (proto->Class == ITEM_CLASS_TRADE_GOODS || proto->Class == ITEM_CLASS_REAGENT)
        {
            if (proto->Quality >= ITEM_QUALITY_NORMAL && proto->Bonding != BIND_WHEN_PICKED_UP)
                return true;
        }
    }

    return false;
}

// 检查公会银行提取权限，遍历第 0 页栏位寻找可装备或用于技能提升的物品
bool ShouldGuildBankWithdrawValue::Calculate()
{
    if (!bot->GetGuildId())
        return false;

    if (AI_VALUE(uint8, "bag space") > 80)
        return false;

    Guild* guild = sGuildMgr.GetGuildById(bot->GetGuildId());
    if (!guild)
        return false;

    if (guild->GetPurchasedTabs() == 0)
        return false;

    // Check if bot has rights to view/withdraw from tab 0 | 检查机器人是否拥有第 0 页公会银行的查看和提取权限
    if (!guild->IsMemberHaveRights(bot->GetGUIDLow(), 0, GUILD_BANK_RIGHT_VIEW_TAB))
        return false;

    // Check guild bank for items the bot can use | 遍历公会银行物品判断机器人是否需要
    for (uint8 tabId = 0; tabId < guild->GetPurchasedTabs(); ++tabId)
    {
        if (!guild->IsMemberHaveRights(bot->GetGUIDLow(), tabId, GUILD_BANK_RIGHT_VIEW_TAB))
            continue;

        for (uint8 slotId = 0; slotId < GUILD_BANK_MAX_SLOTS; ++slotId)
        {
            GuildAccess* guildAccess = static_cast<GuildAccess*>(guild);
            Item* item = guildAccess->GetGuildItem(tabId, slotId);

            if (!item)
                continue;

            ItemPrototype const* proto = item->GetProto();
            if (!proto)
                continue;

            // Check if we can equip this item | 检查是否可装备该物品
            if (proto->InventoryType != INVTYPE_NON_EQUIP && bot->CanUseItem(proto) == EQUIP_ERR_OK)
            {
                ItemQualifier qualifier(item);
                ItemUsage equipUsage = ItemUsageValue::QueryItemUsageForEquip(qualifier, bot);
                if (equipUsage == ItemUsage::ITEM_USAGE_EQUIP)
                    return true;
            }

            // Check if we need this for crafting | 检查专业制作或技能是否需要该物品
            if (proto->Class == ITEM_CLASS_TRADE_GOODS || proto->Class == ITEM_CLASS_REAGENT)
            {
                ItemQualifier qualifier(item);
                std::string qualStr = qualifier.GetQualifier();
                ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", qualStr);
                if (usage == ItemUsage::ITEM_USAGE_SKILL)
                    return true;
            }
        }
    }

    return false;
}
#endif