#include "playerbot/playerbot.h"
#include "GuildShareItemAction.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

/// 判断当前状态下该动作是否可用/有效（公会共享物品动作）
bool GuildShareItemAction::isUseful()
{
    if (!bot->GetGuildId())
        return false;

    if (bot->IsInCombat())
        return false;

    return AI_VALUE(GuildShareTarget, "guild share target").IsValid();
}

/// 执行动作主逻辑（公会共享物品动作）
bool GuildShareItemAction::Execute(Event& event)
{
    GuildShareTarget shareTarget = AI_VALUE(GuildShareTarget, "guild share target");
    if (!shareTarget.IsValid())
        return false;

    Player* receiver = shareTarget.receiver;
    uint32 itemId = shareTarget.itemId;
    uint32 shareAmount = shareTarget.amount; // 0 = give all (existing behavior) (0 = 全部给予（现有默认行为）)

    PlayerbotAI* receiverAi = receiver->GetPlayerbotAI();
    if (!receiverAi)
        return false;

    std::vector<Item*> items = ai->GetInventoryItems();
    for (Item* item : items)
    {
        if (item->GetProto()->ItemId != itemId)
            continue;

        uint32 stackCount = item->GetCount();
        uint32 giveCount = (shareAmount > 0 && shareAmount < stackCount) ? shareAmount : stackCount;

        if (giveCount == stackCount)
        {
            ItemPosCountVec dest;
            uint8 bagSlot;
            InventoryResult msg = receiver->CanStoreItem(NULL_BAG, NULL_SLOT, dest, item, bagSlot, false);
            if (msg != EQUIP_ERR_OK)
            {
                sLog.outDetail("Bot #%d <%s> cannot give %s to %s - bags full",
                    bot->GetGUIDLow(), bot->GetName(), item->GetProto()->Name1, receiver->GetName());
                return false;
            }

            bot->MoveItemFromInventory(item->GetBagSlot(), item->GetSlot(), true);
            item->SetOwnerGuid(receiver->GetObjectGuid());
            receiver->MoveItemToInventory(dest, item, true);

            std::ostringstream receiverOut;
            receiverOut << "Got " << chat->formatItem(item, giveCount) << " from guild member " << bot->GetName();
            receiverAi->TellPlayerNoFacing(receiverAi->GetMaster(), receiverOut.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        }
        else
        {
            ItemPosCountVec dest;
            InventoryResult msg = receiver->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, giveCount);
            if (msg != EQUIP_ERR_OK)
            {
                sLog.outDetail("Bot #%d <%s> cannot give %s to %s - bags full",
                    bot->GetGUIDLow(), bot->GetName(), item->GetProto()->Name1, receiver->GetName());
                return false;
            }

            // SetCount and StoreItem do not update the quest item counters, unlike (SetCount 与 StoreItem 不会自动更新任务物品计数，不同于)
            // MoveItemFromInventory and MoveItemToInventory for a whole stack. (对整组堆叠物品执行背包移出与移入操作。)
            bot->ItemRemovedQuestCheck(itemId, giveCount);
            item->SetCount(stackCount - giveCount);
            item->SetState(ITEM_CHANGED, bot);
            bot->SaveInventoryAndGoldToDB();

            Item* newItem = Item::CreateItem(itemId, giveCount, receiver);
            if (!newItem)
                return false;

            receiver->ItemAddedQuestCheck(itemId, giveCount);
            receiver->StoreItem(dest, newItem, true);

            std::ostringstream receiverOut;
            receiverOut << "Got " << chat->formatItem(newItem, giveCount) << " from guild member " << bot->GetName();
            receiverAi->TellPlayerNoFacing(receiverAi->GetMaster(), receiverOut.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        }

        return true;
    }

    return false;
}
