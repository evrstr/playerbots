// 策略值实现：MaintenanceValues（拍卖行提前清理与邮件收取时机判断）

#include "MaintenanceValues.h"
#include "Mails/Mail.h"
#include "playerbot/strategy/values/GuildValues.h"

using namespace ai;

// 检查背包空间或是否存在修理代价较高且待拍卖的受损装备
bool ShouldAHSellValue::Calculate() 
{
    if (ShouldSellValue::Calculate()) //We need space so we want to try to AH items anyway. | 背包空间不足，无论如何都应先去清理拍卖
        return true;

    std::list<Item*> items = AI_VALUE2(std::list<Item*>, "inventory items", "inventory");

    for (auto& item : items)
    {
        if (!item->GetUInt32Value(ITEM_FIELD_DURABILITY)) //Does the item need to be repaired? | 检查物品是否存在耐久损耗
            continue;

        uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);

        ItemPrototype const* ditemProto = item->GetProto();

        DurabilityCostsEntry const* dcost = sDurabilityCostsStore.LookupEntry(ditemProto->ItemLevel);
        if (!dcost)
            continue;

        uint32 dQualitymodEntryId = (ditemProto->Quality + 1) * 2;
        DurabilityQualityEntry const* dQualitymodEntry = sDurabilityQualityStore.LookupEntry(dQualitymodEntryId);
        if (!dQualitymodEntry)
            continue;

        uint32 dmultiplier = dcost->multiplier[ItemSubClassToDurabilityMultiplierId(ditemProto->Class, ditemProto->SubClass)];
        uint32 costs = uint32(maxDurability * dmultiplier * double(dQualitymodEntry->quality_mod));

        if (bot->GetMoney() && (costs * 100) / bot->GetMoney() <= 1) //Would repairing this item use more than 1% of our current gold? | 在野外修理此物品是否超过当前金币的 1%
            continue;

        if (!WorldPosition(bot).HasAreaFlag(AREA_FLAG_CAPITAL)) //We are not in a city so not easy to repair now. | 不在主城中不便随时修理

        if (bot->GetMoney() && (costs * 100) / bot->GetMoney() <= 10) //Would repairing this item use more than 10% of our current gold? | 在主城修理此物品是否超过当前金币的 10%
                continue;

        ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", ItemQualifier(item).GetQualifier());

        if (usage != ItemUsage::ITEM_USAGE_AH && usage != ItemUsage::ITEM_USAGE_BROKEN_AH) //Do we want to AH this item? | 检查该物品是否标记为拍卖行出售用途
            continue;

        return true; //We have an item that can be damaged (and gives significant repair cost) that we want to auction. We should auction it now! | 持有可损坏且修理昂贵的待拍卖物品，应尽快去拍卖
    }

    return false;
}


// 检查邮箱中是否存在未过期且可由机器人收取的邮件（含任务/普通/拍卖邮件）
bool CanGetMailValue::Calculate() {
    if (!ai->HasStrategy("rpg vendor", BotState::BOT_STATE_NON_COMBAT))
        return false;

    if (AI_VALUE(bool, "should sell"))
        return false;

    time_t cur_time = time(0);

    for (PlayerMails::iterator itr = bot->GetMailBegin(); itr != bot->GetMailEnd(); ++itr)
    {
        if ((*itr)->state == MAIL_STATE_DELETED || cur_time < (*itr)->deliver_time)
            continue;

        if ((*itr)->has_items || (*itr)->money)
        {
            return true;
        }
    }

    return false;
}

// 根据邮件滞留时长、是否含物品/金币及公会共享拍卖状态决定是否立刻去收信
bool ShouldGetMailValue::Calculate() {
    time_t cur_time = time(0);

    bool hasGuildShareList = !AI_VALUE(std::vector<GuildShareItemEntry>, "guild share list").empty();

    for (PlayerMails::iterator itr = bot->GetMailBegin(); itr != bot->GetMailEnd(); ++itr)
    {
        if ((*itr)->state == MAIL_STATE_DELETED || cur_time < (*itr)->deliver_time)
            continue;

        int32 waitingInBoxTime = cur_time - (*itr)->deliver_time;

        if (!hasGuildShareList && waitingInBoxTime < HOUR) //Let mail sit in the inbox for atleast 1 hour | 普通无公会共享时让邮件在信箱暂留至少 1 小时
        {
            return false;
        }

        if ((*itr)->has_items && waitingInBoxTime > HOUR * 4) //Items are allowed to sit in the mail for max 4 hours. | 附件物品最多在信箱保留 4 小时后必须取出
        {
            return true;
        }

        if (hasGuildShareList && (*itr)->has_items && (*itr)->stationery == MAIL_STATIONERY_AUCTION && waitingInBoxTime > MINUTE) //If bot has guild share list and mail is from AH, take mail immediately. | 若启用公会共享且收到拍卖行物品邮件超过 1 分钟则尽快提取
        {
            return true;
        }

        if ((*itr)->money && AI_VALUE(bool, "should get money")) //We need money so we should get it. | 邮件含金币且机器人缺钱时立即提取
        {
            return true;
        }
    }

    return false;
}