// 策略值实现：ItemCountValue（按物品访问器统计背包、银行物品与可用饰品）
#include "playerbot/playerbot.h"
#include "ItemCountValue.h"
#include "Entities/Item.h"
#include "Entities/ItemPrototype.h"
#include "Entities/Player.h"
#include <unordered_map>
#include <ctime>

using namespace ai;

// 内部辅助函数：使用 FindItemVisitor 在指定容器掩码范围内搜索匹配物品
static std::list<Item*> Find(PlayerbotAI* ai, std::string qualifier, IterateItemsMask mask = IterateItemsMask((uint8)IterateItemsMask::ITERATE_ITEMS_IN_EQUIP | (uint8)IterateItemsMask::ITERATE_ITEMS_IN_BAGS))
{
    std::list<Item*> result;
    Player* bot = ai->GetBot();    
    result = ai->InventoryParseItems(qualifier, mask);
    return result;
}

// 累加背包和已装备匹配物品的总堆叠数量
uint32 ItemCountValue::Calculate()
{
    uint32 count = 0;
    std::list<Item*> items = Find(ai, qualifier);
    for (Item* item : items)
        count += item->GetCount();
    
    return count;
}

// 返回背包和已装备匹配物品列表
std::list<Item*> InventoryItemValue::Calculate()
{
    return Find(ai, qualifier);
}

// 累加银行中匹配物品的总堆叠数量
uint32 BankItemCountValue::Calculate()
{
    uint32 count = 0;
    std::list<Item*> items = Find(ai, qualifier, IterateItemsMask(IterateItemsMask::ITERATE_ITEMS_IN_BANK));
    for (Item* item : items)
        count += item->GetCount();

    return count;
}

// 返回银行中匹配物品列表
std::list<Item*> BankItemValue::Calculate()
{
    return Find(ai, qualifier, IterateItemsMask(IterateItemsMask::ITERATE_ITEMS_IN_BANK));
}

// 筛选两个饰品栏中带有 USE 触发法术的已装备饰品
std::list<Item*> EquipedUsableTrinketValue::Calculate()
{
    std::list<Item*> trinkets;
    std::list<Item*> result;

    Player* bot = ai->GetBot();

    if (Item* trinket1 = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET1))
        trinkets.push_back(trinket1);

    if (Item* trinket2 = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET2))
        trinkets.push_back(trinket2);

    if (trinkets.empty())
        return result;

    for (Item * item : trinkets)
    {
        ItemPrototype const* proto = item->GetProto();

        for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_USE &&
                proto->Spells[i].SpellId > 0 &&
                bot->IsSpellReady(proto->Spells[i].SpellId, proto))
            {
                result.push_back(item);
            }
        }
    }

    return result;
}