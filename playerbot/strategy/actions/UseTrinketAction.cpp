
#include "playerbot/playerbot.h"
#include "UseTrinketAction.h"
#include "Entities/Item.h"
#include "Entities/ItemPrototype.h"
#include "Entities/Player.h"

using namespace ai;

/// 执行动作主逻辑（使用饰品动作）
bool UseTrinketAction::Execute(Event& event)
{
    Player* requester = event.getOwner();
    std::list<Item*> trinkets = AI_VALUE(std::list<Item*>, "trinkets on use");
    for (Item* item : trinkets)
    {
        const ItemPrototype* proto = item->GetProto();
        if (proto->InventoryType == INVTYPE_TRINKET && item->IsEquipped())
        {
            if (bot->CanUseItem(item) == EQUIP_ERR_OK && !item->IsInTrade())
            {
                return UseItem(requester, item->GetEntry());
            }
        }
    }

    return false;
}

/// 判断执行该动作的前置条件是否满足（使用饰品动作）
bool UseTrinketAction::isPossible()
{
    return !AI_VALUE(std::list<Item*>, "trinkets on use").empty();
}
