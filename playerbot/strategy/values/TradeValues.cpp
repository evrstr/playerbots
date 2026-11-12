// 策略值实现：TradeValues（交易赠送物品与附魔目标物品匹配）

#include "playerbot/playerbot.h"
#include "TradeValues.h"
#include "ItemUsageValue.h"
#include "playerbot/TravelMgr.h"
#include "playerbot/RandomItemMgr.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

// 检查指定模板 ID 的物品是否已放入当前交易窗口
bool ItemsUsefulToGiveValue::IsTradingItem(uint32 entry)
{
    TradeData* trade = bot->GetTradeData();

    if (!trade)
        return false;

    for (uint8 i = 0; i < TRADE_SLOT_TRADED_COUNT; i++)
    {
        Item* tradeItem = trade->GetItem(TradeSlots(i));

        if (tradeItem && tradeItem->GetEntry() == entry)
            return true;;
    }

    return false;
}

// 遍历自身闲置物品（无用/卖店/拍卖/分解），排除灵魂绑定与重复项，筛选对目标玩家有价值的物品
std::list<Item*> ItemsUsefulToGiveValue::Calculate()
{
    GuidPosition guidP = AI_VALUE(GuidPosition, "rpg target");
    
    Player* player = guidP.GetPlayer();

    if (!ai->IsSafe(player))
        return {};

    std::list<Item*> giveItems;

    if (ai->HasActivePlayerMaster() || !player->GetPlayerbotAI())
        return giveItems;

    std::list<ItemUsage> myUsages = { ItemUsage::ITEM_USAGE_NONE , ItemUsage::ITEM_USAGE_VENDOR, ItemUsage::ITEM_USAGE_AH, ItemUsage::ITEM_USAGE_BROKEN_AH, ItemUsage::ITEM_USAGE_DISENCHANT };

    for (auto& myUsage : myUsages)
    {
        std::list<Item*> myItems = AI_VALUE2(std::list<Item*>, "inventory items", "usage " + std::to_string((uint8)myUsage));
        myItems.reverse();

        for (auto& item : myItems)
        {
            if (!item->CanBeTraded())
                continue;

            // do not trade equipped items | 不交易已装备在身上的物品
            if (item->IsEquipped())
                continue;

            TradeData* trade = bot->GetTradeData();

            if (trade)
            {

                if (trade->HasItem(item->GetObjectGuid())) //This specific item isn't being traded. | 跳过已放入交易栏的该物品实例
                    continue;

                if (IsTradingItem(item->GetEntry())) //A simular item isn't being traded. | 跳过同模板 ID 已在交易中的物品
                    continue;

                if (std::any_of(giveItems.begin(), giveItems.end(), [item](Item* i) {return i->GetEntry() == item->GetEntry(); })) //We didn't already add a simular item to this list. | 防止向候选列表重复添加同类物品
                    continue;
            }

            ItemUsage otherUsage = PAI_VALUE2(ItemUsage, "item usage", ItemQualifier(item).GetQualifier());

            if (std::find(myUsages.begin(), myUsages.end(), otherUsage) == myUsages.end())
                giveItems.push_back(item);
        }
    }

    return giveItems;
}

// 匹配已学会的附魔技能与指定目标的已装备物品，返回可进行交易附魔的装备列表
std::list<Item*> ItemsUsefulToEnchantValue::Calculate()
{
    GuidPosition guidP = AI_VALUE(GuidPosition, "rpg target");

    Player* player = guidP.GetPlayer();

    std::list<Item*> enchantItems;

    if (ai->HasActivePlayerMaster() || !player->GetPlayerbotAI() || !ai->IsSafe(player))
        return enchantItems;

    std::vector<uint32> enchantSpells = AI_VALUE(std::vector<uint32>, "enchant spells");

    for (auto& spellId : enchantSpells)
    {
        const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);

        if (!pSpellInfo)
            continue;

        uint32 castCount = AI_VALUE2(uint32, "has reagents for", spellId);

        if (!castCount)
            continue;

        Item* item = PAI_VALUE2(Item*, "item for spell", spellId);

        if (!item)
            continue;

        if (PHAS_AI_VALUE2("force item usage", item->GetProto()->ItemId))
            continue;

        // Only trade equipped items | 仅对目标已穿戴在身上的装备进行代附魔评估
        if (!item->IsEquipped())
            continue;

        TradeData* trade = bot->GetTradeData();

        if (trade)
        {

            if (trade->HasItem(item->GetObjectGuid())) //This specific item isn't being traded. | 跳过已放入交易栏的物品
                continue;

            if (std::any_of(enchantItems.begin(), enchantItems.end(), [item](Item* i) {return i->GetEntry() == item->GetEntry(); })) //We didn't already add a simular item to this list. | 避免重复添加相同模板的待附魔装备
                continue;
        }

        uint32 enchant_id = pSpellInfo->EffectMiscValue[0];

        uint32 currentEnchnatWeight = 0;
        if (item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT))
            currentEnchnatWeight = sRandomItemMgr.CalculateEnchantWeight(bot->getClass(), sRandomItemMgr.GetPlayerSpecId(bot), item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT));

        uint32 newEnchantWeight = sRandomItemMgr.CalculateEnchantWeight(bot->getClass(), sRandomItemMgr.GetPlayerSpecId(bot), enchant_id);

        if (!item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) || currentEnchnatWeight >= newEnchantWeight)
            continue;

        enchantItems.push_back(item);
    }

    return enchantItems;
}