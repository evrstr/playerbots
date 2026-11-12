// 策略值实现：ItemUsageValue（物品用途优先级决策树、装备对比与拍卖行估值）

#include "playerbot/playerbot.h"
#include "ItemUsageValue.h"
#include "CraftValues.h"
#include "MountValues.h"
#include "BudgetValues.h"
#include "GuildValues.h"

#include "playerbot/RandomItemMgr.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

std::unordered_map<uint32, std::unordered_set<uint32>> ItemUsageValue::m_reagentItemIdsForCraftingSkills;
std::unordered_set<uint32> ItemUsageValue::m_allReagentItemIdsForCraftingSkills;
std::vector<uint32> ItemUsageValue::m_allReagentItemIdsForCraftingSkillsVector;

std::unordered_map<uint32, std::vector<std::pair<uint32, uint32>>> ItemUsageValue::m_craftingReagentItemIdsForCraftableItem;

std::unordered_set<uint32> ItemUsageValue::m_allItemIdsSoldByAnyVendors;
std::unordered_set<uint32> ItemUsageValue::m_itemIdsSoldByAnyVendorsWithLimitedMaxCount;

// 构造函数：解析物品链接或冒号分隔限定符中的物品 ID 与附魔/宝石/随机属性
ItemQualifier::ItemQualifier(std::string qualifier, bool linkQualifier) : itemId(0), enchantId(0), randomPropertyId(0), gem1(0), gem2(0), gem3(0), gem4(0), proto(nullptr) {
    std::vector<std::string> numbers = Qualified::getMultiQualifiers(qualifier, ":");

    if (numbers.empty())
        return;

    if (!std::all_of(numbers[0].begin(), numbers[0].end(), ::isdigit))
        return;

    itemId = stoi(numbers[0]);

#ifdef MANGOSBOT_ZERO
    uint32 propertyPosition = linkQualifier ? 2 : 6;
#else
    uint32 propertyPosition = linkQualifier ? 6 : 6;
#endif

    if (numbers.size() > 1 && !numbers[1].empty())
        enchantId = stoi(numbers[1]);

    if (numbers.size() > propertyPosition && !numbers[propertyPosition].empty())
        randomPropertyId = stoi(numbers[propertyPosition]);

#ifndef MANGOSBOT_ZERO
    uint8 gemPosition = linkQualifier ? 2 : 2;

    if (numbers.size() > gemPosition + 3)
    {
        if (!numbers[gemPosition].empty())
            gem1 = stoi(numbers[gemPosition]);
        if (!numbers[gemPosition + 1].empty())
            gem2 = stoi(numbers[gemPosition + 1]);
        if (!numbers[gemPosition + 2].empty())
            gem3 = stoi(numbers[gemPosition + 2]);
        if (!numbers[gemPosition + 3].empty())
            gem4 = stoi(numbers[gemPosition + 3]);
    }
#endif
}

// 读取物品指定宝石插槽已镶嵌的宝石 ID
uint32 ItemQualifier::GemId(Item* item, uint8 gemSlot)
{
#ifdef MANGOSBOT_ZERO
    return 0;
#else
    uint32 enchantId = item->GetEnchantmentId(EnchantmentSlot(SOCK_ENCHANTMENT_SLOT + gemSlot));

    if (!enchantId)
        return 0;

    return enchantId;
#endif
}

// 按优先级顺序（强制标记>公会需求>炉石/灵魂碎片>专业>消耗品>装备>分解>任务>弹药>银行>拍卖/卖店）判定物品用途
ItemUsage ItemUsageValue::Calculate()
{
    ItemQualifier itemQualifier(qualifier, false);
    uint32 itemId = itemQualifier.GetId();
    if (!itemId)
        return ItemUsage::ITEM_USAGE_NONE;

    const ItemPrototype* proto = sObjectMgr.GetItemPrototype(itemId);
    if (!proto)
        return ItemUsage::ITEM_USAGE_NONE;

    //FORCE | 优先处理玩家手动设置的强制物品用途
    ForceItemUsage forceUsage = AI_VALUE2_EXISTS(ForceItemUsage, "force item usage", proto->ItemId, ForceItemUsage::FORCE_USAGE_NONE);

    if (forceUsage == ForceItemUsage::FORCE_USAGE_GREED)
        return ItemUsage::ITEM_USAGE_FORCE_GREED;

    if (forceUsage == ForceItemUsage::FORCE_USAGE_NEED)
        return ItemUsage::ITEM_USAGE_FORCE_NEED;

    if (forceUsage == ForceItemUsage::FORCE_USAGE_KEEP)
    {
        ItemUsage equip = QueryItemUsageForEquip(itemQualifier, bot);
        if (equip == ItemUsage::ITEM_USAGE_EQUIP || equip == ItemUsage::ITEM_USAGE_BAD_EQUIP || equip == ItemUsage::ITEM_USAGE_BROKEN_EQUIP)
            return equip;
        return ItemUsage::ITEM_USAGE_KEEP;
    }

    if (forceUsage == ForceItemUsage::FORCE_USAGE_EQUIP)
    {
        ItemUsage equip = QueryItemUsageForEquip(itemQualifier, bot);
        if (equip == ItemUsage::ITEM_USAGE_EQUIP || equip == ItemUsage::ITEM_USAGE_BAD_EQUIP || equip == ItemUsage::ITEM_USAGE_BROKEN_EQUIP)
            return equip;
        if (bot->CanUseItem(proto) == EQUIP_ERR_OK && proto->InventoryType != INVTYPE_NON_EQUIP)
            return ItemUsage::ITEM_USAGE_EQUIP;
        return ItemUsage::ITEM_USAGE_KEEP;
    }

    if (forceUsage == ForceItemUsage::FORCE_USAGE_BAG)
        return ItemUsage::ITEM_USAGE_KEEP;

    if (bot->GetGuildId())
    {
        std::vector<GuildShareItemEntry> shareList = AI_VALUE(std::vector<GuildShareItemEntry>, "guild share list");
        if (!shareList.empty())
        {
            for (const auto& entry : shareList)
            {
                if (entry.itemId == itemId)
                    return ItemUsage::ITEM_USAGE_KEEP;

                ItemPrototype const* craftProto = sObjectMgr.GetItemPrototype(entry.itemId);
                if (craftProto)
                {
                    std::vector<std::pair<uint32, uint32>> reagents = GetAllReagentItemIdsForCraftingItem(craftProto);
                    for (const auto& [reagentId, reagentCount] : reagents)
                    {
                        if (reagentId == itemId)
                            return ItemUsage::ITEM_USAGE_KEEP;
                    }
                }
            }
        }
    }

    //KEEP HEARTHSTONE/SCOURGESTONE | 保留炉石、银色黎明委任徽章与部落/联盟勋章
    if (proto->ItemId == 6948 || proto->ItemId == 40582)
        return ItemUsage::ITEM_USAGE_KEEP;

    //WARLOCKS GOT TO KEEP SOULSHARDS (keep at least 10) | 术士至少保留 10 个灵魂碎片
    if (bot->getClass() == CLASS_WARLOCK && proto->ItemId == 6265 && CurrentStacks(ai, proto) <= 10)
        return ItemUsage::ITEM_USAGE_KEEP;

    //SKILL | 专业技能相关物品评估
    if (ai->HasActivePlayerMaster())
    {
        if (IsItemUsefulForSkill(proto))
            return ItemUsage::ITEM_USAGE_SKILL;

        if (IsItemNeededForSkill(proto))
        {
            float stacks = CurrentStacks(ai, proto);
            if (stacks < 1)
                return ItemUsage::ITEM_USAGE_SKILL; //Buy more.
            else if (stacks == 1)
                return ItemUsage::ITEM_USAGE_KEEP; //Keep in inventory.
        }
    }
    else
    {
        bool needItem = false;

        if (IsItemNeededForSkill(proto))
        {
            float stacks = CurrentStacks(ai, proto);
            if (stacks < 1)
                return ItemUsage::ITEM_USAGE_SKILL; //Buy more.
            else if (stacks == 1)
                return ItemUsage::ITEM_USAGE_KEEP; //Keep in inventory.
        }
        else
        {
            bool lowBagSpace = AI_VALUE(uint8, "bag space") > 50;

            if (proto->Class == ITEM_CLASS_TRADE_GOODS || proto->Class == ITEM_CLASS_MISC || proto->Class == ITEM_CLASS_REAGENT)
                needItem =!ai->HasCheat(BotCheatMask::item) && IsItemNeededForUsefullCraft(proto, lowBagSpace);
            else if (proto->Class == ITEM_CLASS_RECIPE)
            {
                if (bot->HasSpell(GetRecipeSpell(proto)))
                    needItem = false;
                else
                    needItem = bot->CanUseItem(proto) == EQUIP_ERR_OK;
            }
        }

        if (needItem)
        {
            float stacks = CurrentStacks(ai, proto);

            if (proto->Class == ITEM_CLASS_RECIPE && stacks > 0) //Only buy one recipe.
                return ItemUsage::ITEM_USAGE_KEEP;

            if (stacks < 1)
                return ItemUsage::ITEM_USAGE_SKILL; //Buy more.
            else if (stacks == 1)
                return ItemUsage::ITEM_USAGE_KEEP; //Do not buy more.
        }
    }

    //USE | 消耗品与可使用物品评估
    if (proto->Class == ITEM_CLASS_KEY)
        return ItemUsage::ITEM_USAGE_USE;

    if (proto->Class == ITEM_CLASS_CONSUMABLE && !ai->HasCheat(BotCheatMask::item))
    {
        std::string foodType = "";

        if (IsHpFoodOrDrink(proto))
        {
            foodType = "food";
        }
        else if (IsManaFoodOrDrink(proto))
        {
            foodType = "drink";
        }
        else if (IsHealingPotion(proto))
        {
            foodType = "healing potion";
        }
        else if (IsManaPotion(proto))
        {
            foodType = "mana potion";
        }
        else if (IsBandage(proto))
        {
            foodType = "bandage";
        }

        bool botHasHealingSpells = bot->getClass() == CLASS_PALADIN || bot->getClass() == CLASS_PRIEST || bot->getClass() == CLASS_DRUID || bot->getClass() == CLASS_SHAMAN;

        //itemlevel 1 consumables are mostly level-independent | 1 级消耗品大多不受等级限制
        bool isAppropriateConsumableLevel = proto->RequiredLevel <= bot->GetLevel()
            && (proto->ItemLevel == 1 || proto->ItemLevel >= bot->GetLevel());

        bool isAppropriateConsumable = isAppropriateConsumableLevel
            && (IsHpFoodOrDrink(proto) || IsHealingPotion(proto) || (IsBandage(proto) && !botHasHealingSpells) || (bot->HasMana() && (IsManaFoodOrDrink(proto) || IsManaPotion(proto))));

        if (isAppropriateConsumable && bot->CanUseItem(proto) == EQUIP_ERR_OK)
        {
            float stacks = BetterStacks(proto, foodType);

            if (stacks < 1)
            {
                stacks += CurrentStacks(ai, proto);

                if (stacks < 1)
                    return ItemUsage::ITEM_USAGE_USE; //Buy some to get to 1 stack
                else if (stacks < 2)       
                    return ItemUsage::ITEM_USAGE_KEEP; //Keep the item if less than 2 stack
            }
        }
    }

    if (proto->Class == ITEM_CLASS_REAGENT && SpellsUsingItem(proto->ItemId, bot).size())
    {
        float stacks = CurrentStacks(ai, proto);

        if (stacks < 1)
            return ItemUsage::ITEM_USAGE_USE;
        else if (stacks < 2)
            return ItemUsage::ITEM_USAGE_KEEP;
    }

    //EQUIP | 坐骑、雕文与可穿戴装备评估
    if (MountValue::GetMountSpell(itemId) && bot->CanUseItem(proto) == EQUIP_ERR_OK && MountValue::GetSpeed(MountValue::GetMountSpell(itemId)))
    {
        std::vector<MountValue> mounts = AI_VALUE(std::vector<MountValue>, "mount list");

        if (mounts.empty())
            return ItemUsage::ITEM_USAGE_EQUIP;

        uint32 newSpeed[2] = { MountValue::GetSpeed(MountValue::GetMountSpell(itemId), false), MountValue::GetSpeed(MountValue::GetMountSpell(itemId), true) };

        bool hasBetterMount = false, hasSameMount = false;

        for (auto& mount : mounts)
        {
            for (bool canFly : {true, false})
            {
                if (!newSpeed[canFly])
                    continue;

                uint32 currentSpeed = mount.GetSpeed(canFly);

                if (currentSpeed > newSpeed[canFly])
                    hasBetterMount = true;
                else if (currentSpeed == newSpeed[canFly])
                    hasSameMount = true;
            }

            if (hasBetterMount)
                break;
        }

        if (!hasBetterMount)
            return hasSameMount ? ItemUsage::ITEM_USAGE_KEEP : ItemUsage::ITEM_USAGE_EQUIP;
    }

    ItemUsage equip = QueryItemUsageForEquip(itemQualifier, bot);
    if (equip != ItemUsage::ITEM_USAGE_NONE)
        return equip;

#ifdef MANGOSBOT_TWO
    if (proto->Class == ITEM_CLASS_GLYPH)
        if (!ai->HasCheat(BotCheatMask::glyph) && AI_VALUE2(bool, "glyph is upgrade", itemId))
            return ItemUsage::ITEM_USAGE_EQUIP;
#endif

    if (forceUsage == ForceItemUsage::FORCE_USAGE_EQUIP)
        return ItemUsage::ITEM_USAGE_KEEP;

    //DISENCHANT | 附魔分解评估
    if ((proto->Class == ITEM_CLASS_ARMOR || proto->Class == ITEM_CLASS_WEAPON) && proto->Bonding != BIND_WHEN_PICKED_UP &&
        ai->HasSkill(SKILL_ENCHANTING) && proto->Quality >= ITEM_QUALITY_UNCOMMON)
    {
        if (proto->DisenchantID)
        {

#ifndef MANGOSBOT_ZERO
            // 2.0.x addon: Check player enchanting level against the item disenchanting requirements
            int32 item_disenchantskilllevel = proto->RequiredDisenchantSkill;
            if (item_disenchantskilllevel <= int32(bot->GetSkillValue(SKILL_ENCHANTING)))
            {
#endif
                Item* item = CurrentItem(proto, bot);

                //Bot has budget to replace the item it wants to disenchant. | 确保机器人有预算替换拟分解的装备
                if (!item || !sRandomPlayerbotMgr.IsRandomBot(bot) || AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::tradeskill) > proto->BuyPrice)
                    return ItemUsage::ITEM_USAGE_DISENCHANT;

#ifndef MANGOSBOT_ZERO
            }
#endif
        }
    }

    //QUEST | 任务需求物品评估
    if (!ai->GetMaster() || !sPlayerbotAIConfig.syncQuestWithPlayer || !IsNeededForQuest(ai->GetMaster(), itemId))
    {
        if (IsNeededForQuest(bot, itemId))
            return ItemUsage::ITEM_USAGE_QUEST;
        else if (IsNeededForQuest(bot, itemId, true) && CurrentStacks(ai, proto) < 2) //Do not sell quest items unless selling a full stack will stil keep enough in inventory. | 至少保留不到两组的任务关联物品以免误卖
            return ItemUsage::ITEM_USAGE_KEEP;
    }

    // AMMO | 猎人箭矢/子弹评估
if ((proto->Class == ITEM_CLASS_PROJECTILE || 
     (proto->Class == ITEM_CLASS_WEAPON && proto->SubClass == ITEM_SUBCLASS_WEAPON_THROWN)) &&
    bot->CanUseItem(proto) == EQUIP_ERR_OK)
{
    if ((bot->getClass() == CLASS_HUNTER && proto->Class != ITEM_CLASS_WEAPON) ||
        bot->getClass() == CLASS_ROGUE ||
        bot->getClass() == CLASS_WARRIOR)
    {
        Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
        if (pItem)
        {
            uint32 ammoClass = ITEM_CLASS_PROJECTILE;
            uint32 subClass = 0;

            switch (pItem->GetProto()->SubClass)
            {
                case ITEM_SUBCLASS_WEAPON_GUN:
                    subClass = ITEM_SUBCLASS_BULLET;
                    break;
                case ITEM_SUBCLASS_WEAPON_BOW:
                case ITEM_SUBCLASS_WEAPON_CROSSBOW:
                    subClass = ITEM_SUBCLASS_ARROW;
                    break;
                case ITEM_SUBCLASS_WEAPON_THROWN:
                    ammoClass = ITEM_CLASS_WEAPON;
                    subClass = ITEM_SUBCLASS_WEAPON_THROWN;
                    break;
            }

            if (proto->Class == ammoClass && proto->SubClass == subClass)
            {
                uint32 currentAmmoId = bot->GetUInt32Value(PLAYER_AMMO_ID);
                const ItemPrototype* currentAmmoProto = nullptr;
                if (currentAmmoId)
                    currentAmmoProto = sObjectMgr.GetItemPrototype(currentAmmoId);

                float betterAmmoStacks = BetterStacks(proto, "ammo"); // how much better ammo we have
                float needAmmo = (bot->getClass() == CLASS_HUNTER) ? 8 : 2;

                if (ai->HasCheat(BotCheatMask::item))
                    needAmmo = 1;

                                    // fallback: equip any ammo if no ammo equipped
                if (!currentAmmoId)
                {
                                    // check if this proto exists in bags
                if (ai->HasItemInInventory(proto->ItemId))
                return ItemUsage::ITEM_USAGE_EQUIP;
                }

                // If no better ammo exists
                if (betterAmmoStacks <= 0)
                {
                    // Equip this ammo if not already equipped
                    if (currentAmmoId != proto->ItemId)
                        return ItemUsage::ITEM_USAGE_EQUIP;
                }

                // If this ammo is already equipped or after equipping
                float totalStacks = betterAmmoStacks + CurrentStacks(ai, proto);

                if (totalStacks < needAmmo)            // Not enough ammo, buy more
                    return ItemUsage::ITEM_USAGE_AMMO;
                else if (totalStacks < needAmmo + 1)   // Enough ammo, but keep it
                    return ItemUsage::ITEM_USAGE_KEEP;
            }
        }
    }
}

    //KEEP | 保留当前及未来升级/制造有用的物品
    if (proto->Quality >= ITEM_QUALITY_EPIC && sPlayerbotAIConfig.botsSaveEpics && !sRandomPlayerbotMgr.IsRandomBot(bot))
        return ItemUsage::ITEM_USAGE_KEEP;

    //BANK - items for future use | 适合存入个人银行留待将来使用的物品
    if (!ai->HasActivePlayerMaster() && sRandomPlayerbotMgr.IsFreeBot(bot))
    {
        if (IsItemUsefulForFutureEquip(proto))
            return ItemUsage::ITEM_USAGE_BANK;

        if (IsItemUsefulForFutureCraft(proto))
            return ItemUsage::ITEM_USAGE_BANK;
    }

    if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE)
    {
        uint8 maxExpansionCharacterLevel = 60;
#ifdef MANGOSBOT_ONE
        maxExpansionCharacterLevel = 70;
#endif
#ifdef MANGOSBOT_TWO
        maxExpansionCharacterLevel = 80;
#endif

        //keep relevant class consumables (e.g. rogue poisons)
        if (proto->AllowableClass == bot->getClass() && proto->RequiredLevel + 6 >= bot->GetLevel())
        {
            if (bot->GetLevel() == maxExpansionCharacterLevel && proto->RequiredLevel + 6 >= bot->GetLevel())
            {
                return ItemUsage::ITEM_USAGE_USE;
            }

            if (bot->GetLevel() == maxExpansionCharacterLevel && proto->RequiredLevel + 10 >= bot->GetLevel())
            {
                return ItemUsage::ITEM_USAGE_USE;
            }
        }
    }

    uint32 ahPrice = 0;

    //VENDOR/AH | 出售给 NPC 商人或挂入拍卖行评估
    if (proto->SellPrice > 0 || AI_VALUE2_EXISTS(int, "manual int", "expected ah sell price for " + std::to_string(itemId),-1) != 0)
    {
        ItemUsage sellUsage = ItemUsage::ITEM_USAGE_VENDOR;

        if (!ai->HasActivePlayerMaster())
        {
            uint32 maxSellPrice = proto->SellPrice;

            if (proto->Stackable)
                maxSellPrice *= proto->Stackable;

            uint32 minimumSellPrice = bot->GetMoney() / 1000;

            if (maxSellPrice < minimumSellPrice) //Do not loot items less than 0.1% of bot's gold per stack. 
                sellUsage = ItemUsage::ITEM_USAGE_NONE;
        }

#ifdef MANGOSBOT_TWO
        if(bot->GetMapId() == 609)
            return sellUsage;
#endif

        //if item value is significantly higher than its vendor sell price and we actually have money to place the item on ah. | 若物品估值明显高于卖店价且资金充足则考虑上架拍卖行
        uint32 ahMoney = AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::ah);

        if(!ahMoney && AI_VALUE(uint8, "bag space") > 80)
            return sellUsage;

        if (!IsMoreProfitableToSellToAHThanToVendor(proto, bot))
            return sellUsage;

        Item* item = CurrentItem(proto, bot);
        uint32 count = item ? item->GetCount() : 1;

        uint32 sellPrice = proto->SellPrice * count;

        uint32 depositCost = GetAhDepositCost(proto, count);
        
        uint32 ahPrice = ItemUsageValue::GetBotSellPrice(proto, bot) * count;

        if(proto->SellPrice == 0)
            SET_AI_VALUE2(int, "manual int", "expected ah sell price for " + std::to_string(itemId), ahPrice);

        if (ahPrice < depositCost)
            return sellUsage; //The AH desposit is higher than the money gained.

        if (ahPrice - depositCost < sellPrice)
            return sellUsage; //It costs more to AH then sell.

        if (ahPrice - depositCost - sellPrice < bot->GetMoney() / 500)
            return sellUsage; //Do not move to AH for items with less than 0.2% of bots gold markup.

        if(depositCost > ahMoney && AI_VALUE(uint8, "bag space") > 80) 
            return sellUsage; //We simply do not have the money to put this on AH.

        if(!item) 
            return ItemUsage::ITEM_USAGE_AH;   //We can't determine if this item is soulboud (yet) or broken so we assume we can AH this.      

        bool soulBound = (proto->Bonding == BIND_WHEN_EQUIPPED) && item->IsSoulBound();

        if (soulBound)
            return sellUsage; //Item is soulbound so can't AH.

        uint32 repairCost = RepairCostValue::RepairCost(item);

        if (ahPrice < proto->SellPrice + repairCost)
            return sellUsage;  //Repairing costs more than the AH profit.

        if (repairCost > 0)
            return ItemUsage::ITEM_USAGE_BROKEN_AH; //Keep until repaired so we can AH later.

        return ItemUsage::ITEM_USAGE_AH;
    }

    //NONE | 无可用用途（丢弃或忽略）
    return ItemUsage::ITEM_USAGE_NONE;
}

// 判断物品是否可装备，并与当前槽位已装备物品进行装等、品质和属性权重对比
ItemUsage ItemUsageValue::QueryItemUsageForEquip(ItemQualifier& itemQualifier, Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    AiObjectContext* context = ai->GetAiObjectContext();
    ChatHelper* chat = ai->GetChatHelper();
    ItemPrototype const* itemProto = itemQualifier.GetProto();

    if (bot->CanUseItem(itemProto) != EQUIP_ERR_OK)
        return ItemUsage::ITEM_USAGE_NONE;

    if (itemProto->InventoryType == INVTYPE_NON_EQUIP)
        return ItemUsage::ITEM_USAGE_NONE;

    uint16 dest;

    std::list<Item*> items = AI_VALUE2(std::list<Item*>, "inventory items", chat->formatItem(itemQualifier));
    InventoryResult result;
    if (!items.empty())
    {
        result = bot->CanEquipItem(NULL_SLOT, dest, items.front(), true, false);
    }
    else
    {
        result = RandomPlayerbotMgr::CanEquipUnseenItem(bot, NULL_SLOT, dest, itemProto->ItemId);
    }

    if (result != EQUIP_ERR_OK)
        return ItemUsage::ITEM_USAGE_NONE;

    if (itemProto->Class == ITEM_CLASS_QUIVER)
    {
        Item* equippedRangedWeapon = bot->GetWeaponForAttack(WeaponAttackType::RANGED_ATTACK, false, false);

        if (bot->getClass() == CLASS_HUNTER && equippedRangedWeapon)
        {
            ItemPrototype const* rangedWeaponItemProto = equippedRangedWeapon->GetProto();
            if (!rangedWeaponItemProto)
                return ItemUsage::ITEM_USAGE_NONE;

            bool isCorrectQuiverTypeForCurrentWeapon = false;

            if (itemProto->SubClass == ITEM_SUBCLASS_AMMO_POUCH)
            {
                if (rangedWeaponItemProto->SubClass == ItemSubclassWeapon::ITEM_SUBCLASS_WEAPON_GUN)
                {
                    isCorrectQuiverTypeForCurrentWeapon = true;
                }
            }
            else {
                if (rangedWeaponItemProto->SubClass == ItemSubclassWeapon::ITEM_SUBCLASS_WEAPON_BOW
                    || rangedWeaponItemProto->SubClass == ItemSubclassWeapon::ITEM_SUBCLASS_WEAPON_CROSSBOW)
                {
                    isCorrectQuiverTypeForCurrentWeapon = true;
                }
            }

            if (!isCorrectQuiverTypeForCurrentWeapon)
                return ItemUsage::ITEM_USAGE_NONE;

            std::vector<Bag*> equippedQuivers = bot->GetPlayerbotAI()->GetEquippedQuivers();

            for (auto quiver : equippedQuivers)
            {
                if (quiver->GetProto()->ItemLevel < itemProto->ItemLevel)
                {
                    return ItemUsage::ITEM_USAGE_EQUIP;
                }

                if (quiver->GetProto()->ItemLevel == itemProto->ItemLevel && quiver->GetProto()->Quality < itemProto->Quality)
                {
                    return ItemUsage::ITEM_USAGE_EQUIP;
                }

                //no need to check for quiver container slots size, higher ilvl/quality checks is enough | 箭袋无需比较格子数，装等与品质已足够判断
            }
        }

        return ItemUsage::ITEM_USAGE_NONE;
    }

    if (itemProto->Class == ITEM_CLASS_CONTAINER)
    {
        if (itemProto->SubClass != ITEM_SUBCLASS_CONTAINER)
            return ItemUsage::ITEM_USAGE_NONE; //Todo add logic for non-bag containers. We want to look at professions/class and only replace if non-bag is larger than bag.

        if (GetSmallestBagSize(bot) >= itemProto->ContainerSlots)
            return ItemUsage::ITEM_USAGE_NONE;

        return ItemUsage::ITEM_USAGE_EQUIP;
    }

    bool shouldEquip = false;

    uint32 specId = sRandomItemMgr.GetPlayerSpecId(bot);

    uint32 statWeight = sRandomItemMgr.ItemStatWeight(bot, itemQualifier);
    if (statWeight)
        shouldEquip = true;

    if (itemProto->Class == ITEM_CLASS_WEAPON && !sRandomItemMgr.ShouldEquipWeaponForSpec(bot->getClass(), specId, itemProto))
        shouldEquip = false;
    if (itemProto->Class == ITEM_CLASS_ARMOR && !sRandomItemMgr.ShouldEquipArmorForSpec(bot->getClass(), specId, itemProto))
        shouldEquip = false;

    Item* oldItem = bot->GetItemByPos(dest);
    uint8 slot = dest & 255;

    ai->TellDebug(ai->GetMaster(), "Checking equip: " + chat->formatItem(itemProto) + " to " + chat->formatSlot(slot) + " vs " + (oldItem ? chat->formatItem(oldItem->GetProto()) : "empty"), "debug equip");

    if (itemProto->Class == ITEM_CLASS_WEAPON &&
        !sRandomItemMgr.ShouldEquipWeaponForSpec(bot->getClass(), specId, itemProto))
    {
        if (oldItem)
            return ItemUsage::ITEM_USAGE_NONE;
    }


    //No item equiped | 对应槽位当前未穿戴装备
    if (!oldItem)
    {
        if (shouldEquip)
            return ItemUsage::ITEM_USAGE_EQUIP;
        else
            return ItemUsage::ITEM_USAGE_BAD_EQUIP;
    }

    const ItemPrototype* oldItemProto = oldItem->GetProto();

    if(MustEquipForQuest(itemProto, bot) && !MustEquipForQuest(oldItemProto, bot))
        return ItemUsage::ITEM_USAGE_EQUIP;

    if (MustEquipForQuest(oldItemProto, bot))
        return ItemUsage::ITEM_USAGE_KEEP;

    if (itemProto->Class == ITEM_CLASS_ARMOR && itemProto->InventoryType == INVTYPE_TABARD)
    {
        uint32 currentStacks = CurrentStacks(ai, itemProto);

        if (currentStacks > 0)
        {
            if (itemProto->ItemId != oldItemProto->ItemId && urand(1, 100) <= 10) //Not equiped. Random 10% equip it.
                return ItemUsage::ITEM_USAGE_EQUIP;

            return ItemUsage::ITEM_USAGE_KEEP;
        }

        return ItemUsage::ITEM_USAGE_EQUIP; //Do not have it yet. Buy/get it.
    }

    if (AI_VALUE2_EXISTS(ForceItemUsage, "force item usage", oldItemProto->ItemId, ForceItemUsage::FORCE_USAGE_NONE) == ForceItemUsage::FORCE_USAGE_EQUIP) //Current equip is forced. Do not unequip.
    {
        if (AI_VALUE2_EXISTS(ForceItemUsage, "force item usage", itemProto->ItemId, ForceItemUsage::FORCE_USAGE_NONE) == ForceItemUsage::FORCE_USAGE_EQUIP)
            return ItemUsage::ITEM_USAGE_KEEP;
        else
            return ItemUsage::ITEM_USAGE_NONE;
    }

    uint32 oldStatWeight = sRandomItemMgr.ItemStatWeight(bot, oldItem);
    if (statWeight && oldStatWeight)
    {
        shouldEquip = statWeight >= oldStatWeight;
    }
    else
    {
        shouldEquip = itemProto->Quality >= oldItemProto->Quality && itemProto->ItemLevel > oldItemProto->ItemLevel;
    }

    if (AI_VALUE2_EXISTS(ForceItemUsage, "force item usage", itemProto->ItemId, ForceItemUsage::FORCE_USAGE_NONE) == ForceItemUsage::FORCE_USAGE_EQUIP) //New item is forced. Always equip it.
        return ItemUsage::ITEM_USAGE_EQUIP;

    bool existingShouldEquip = true;
    if (oldItemProto->Class == ITEM_CLASS_WEAPON && !oldStatWeight)
        existingShouldEquip = false;
    if (oldItemProto->Class == ITEM_CLASS_ARMOR && !oldStatWeight)
        existingShouldEquip = false;

    //Compare items based on item level, quality. | 综合对比新旧装备的装等、品质与属性评分
    bool isBetter = false;
    if (statWeight > oldStatWeight)
        isBetter = true;
    else if (statWeight == oldStatWeight && itemProto->Quality > oldItemProto->Quality)
        isBetter = true;
    else if (statWeight == oldStatWeight && itemProto->Quality == oldItemProto->Quality && itemProto->ItemLevel > oldItemProto->ItemLevel)
        isBetter = true;

    Item* item = CurrentItem(itemProto, bot);
    bool itemIsBroken = item && item->GetUInt32Value(ITEM_FIELD_DURABILITY) == 0 && item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY) > 0;
    bool oldItemIsBroken = oldItem->GetUInt32Value(ITEM_FIELD_DURABILITY) == 0 && oldItem->GetUInt32Value(ITEM_FIELD_MAXDURABILITY) > 0;
    if (itemProto->ItemId != oldItemProto->ItemId && (shouldEquip || !existingShouldEquip) && isBetter)
    {
        switch (itemProto->Class)
        {
        case ITEM_CLASS_ARMOR:
            if (oldItemProto->SubClass <= itemProto->SubClass) {
                if (itemIsBroken && !oldItemIsBroken)
                    return ItemUsage::ITEM_USAGE_BROKEN_EQUIP;
                else
                    if (shouldEquip)
                        return ItemUsage::ITEM_USAGE_EQUIP;
                    else
                        return ItemUsage::ITEM_USAGE_BAD_EQUIP;
            }
            break;
        default:
            if (itemIsBroken && !oldItemIsBroken)
                return ItemUsage::ITEM_USAGE_BROKEN_EQUIP;
            else
                if (shouldEquip)
                    return ItemUsage::ITEM_USAGE_EQUIP;
                else
                    return ItemUsage::ITEM_USAGE_BAD_EQUIP;
        }
    }
    //Item is not better but current item is broken and new one is not. | 新物品属性未超越但当前装备已破损时，暂用新物品替换
    if (oldItemIsBroken && !itemIsBroken)
        return ItemUsage::ITEM_USAGE_EQUIP;

    return ItemUsage::ITEM_USAGE_NONE;
}

//Return smaltest bag size equipped | 返回已装备背包中的最小格数
// 返回当前已装备背包槽位中的最小容量（含空槽返回 0）
uint32 ItemUsageValue::GetSmallestBagSize(Player* bot)
{
    int8 curSlot = 0;
    uint32 curSlots = 0;
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
        {
            if (curSlot > 0 && curSlots < pBag->GetBagSize())
                continue;

            curSlot = pBag->GetSlot();
            curSlots = pBag->GetBagSize();
        }
        else
            return 0;
    }

    return curSlots;
}

// 生成解释机器人为何需要或处置该物品的格式化提示文本
std::string ItemUsageValue::ReasonForNeed(ItemUsage usage, ItemQualifier qualifier, uint32 count, Player* bot)
{
    std::map<std::string, std::string> placeholders;
    placeholders["%item"] = ChatHelper::formatItem(qualifier);

    switch (usage)
    {
    case ItemUsage::ITEM_USAGE_EQUIP:
    {
        if (!qualifier || !bot)
            return BOT_TEXT2("for equiping as upgrade.", placeholders);

        Item* currentItem = ItemUsageValue::CurrentItemInSlot(qualifier.GetProto(), bot);
        if (!currentItem)
            return BOT_TEXT2("for equiping as upgrade because the slot is empty.", placeholders);

        placeholders["%current"] = ChatHelper::formatItem(currentItem);

        if (currentItem->GetUInt32Value(ITEM_FIELD_DURABILITY) == 0 && currentItem->GetUInt32Value(ITEM_FIELD_MAXDURABILITY) > 0)
            return BOT_TEXT2("for equiping as a replacement of %current because it is broken.", placeholders);

        uint32 currentStatWeight = sRandomItemMgr.ItemStatWeight(bot, currentItem);
        uint32 newStatWeight = sRandomItemMgr.ItemStatWeight(bot, qualifier);
        placeholders["%cPower"] = std::to_string(currentStatWeight);
        placeholders["%nPower"] = std::to_string(newStatWeight);
        if (newStatWeight && currentStatWeight)
            return BOT_TEXT2("for equiping as a replacement of %current (%cPower) because it is stronger (%nPower).", placeholders);

        return BOT_TEXT2("for equiping as a replacement of %current because it has a higher level or quality.", placeholders);     
    }
    case ItemUsage::ITEM_USAGE_BAD_EQUIP:
        return BOT_TEXT2("for equiping until I can find something better.", placeholders);
    case ItemUsage::ITEM_USAGE_USE:
        return BOT_TEXT2("to use it when I need it.", placeholders);
    case ItemUsage::ITEM_USAGE_SKILL:
    case ItemUsage::ITEM_USAGE_DISENCHANT:
        return BOT_TEXT2("to use it for my profession.", placeholders);
    case ItemUsage::ITEM_USAGE_AMMO:
        return BOT_TEXT2("to use as ammo.", placeholders);
    case ItemUsage::ITEM_USAGE_QUEST:
        return BOT_TEXT2("to complete an objective for a quest.", placeholders);
    case ItemUsage::ITEM_USAGE_AH:
        if (!qualifier)
            return BOT_TEXT2("to repost on AH.", placeholders);

        placeholders["%price_min"] = ChatHelper::formatMoney(ItemUsageValue::GetBotSellPrice(qualifier.GetProto(), bot) * 0.75 * count);
        placeholders["%price_max"] = ChatHelper::formatMoney(ItemUsageValue::GetBotSellPrice(qualifier.GetProto(), bot) * count);
        return BOT_TEXT2("to repost on AH for %price_min to %price_max.", placeholders);
    case ItemUsage::ITEM_USAGE_VENDOR:
        if (!qualifier)
            return BOT_TEXT2("to sell to a vendor.", placeholders);

        placeholders["%price"] = ChatHelper::formatMoney(qualifier.GetProto()->SellPrice * count);
        return BOT_TEXT2("to sell to a vendor for %price.", placeholders);
    case ItemUsage::ITEM_USAGE_FORCE_NEED:
    case ItemUsage::ITEM_USAGE_FORCE_GREED:
        return BOT_TEXT2("because I was told to get this item.", placeholders);
    case ItemUsage::ITEM_USAGE_BANK:
        return BOT_TEXT2("to bank for future use.", placeholders);
    }

    return "";
}

// 计算物品在拍卖行上架所需的保证金费用
uint32 ItemUsageValue::GetAhDepositCost(ItemPrototype const* proto, uint32 count)
{
    uint32 time;
#ifdef MANGOSBOT_ZERO
    time = 8 * HOUR;
#else
    time = 12 * HOUR;
#endif

    float deposit = float(proto->SellPrice * count * (time / MIN_AUCTION_TIME));

    deposit = deposit * 15 * 3.0f / 100.0f;

    float min_deposit = float(sWorld.getConfig(CONFIG_UINT32_AUCTION_DEPOSIT_MIN));

    if (deposit < min_deposit)
        deposit = min_deposit;

    deposit *= sWorld.getConfig(CONFIG_FLOAT_RATE_AUCTION_DEPOSIT);

    return deposit;
}

// 查询特定转化/重铸物品对应的前置源物品 ID
uint32 ItemUsageValue::ItemCreatedFrom(uint32 wantItemId)
{
    switch (wantItemId) {
    case 38631: //Runebladed Sword  | 符文利剑（由破损的剑转化）
        return 38607; //Battle-worn Sword | 破损的剑
    default:
        return 0;
    }

    return 0;
}

// 检查物品是否为机器人当前未完成任务所需的任务物品或接取/交互触发物品
bool ItemUsageValue::IsNeededForQuest(Player* player, uint32 itemId, bool ignoreInventory)
{
    if (!itemId)
        return false;

    for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        uint32 entry = player->GetQuestSlotQuestId(slot);
        Quest const* quest = sObjectMgr.GetQuestTemplate(entry);
        if (!quest)
            continue;

        QuestStatusData& qData = player->getQuestStatusMap()[quest->GetQuestId()];
        if (qData.m_status != QUEST_STATUS_INCOMPLETE)
            continue;

        for (int i = 0; i < 4; i++)
        {
            if (!quest->ReqItemCount[i])
                continue;

            if (quest->ReqItemId[i] != itemId && ItemCreatedFrom(quest->ReqItemId[i]) != itemId)
                continue;

            if (!ignoreInventory && player->GetItemCount(itemId, false) >= quest->ReqItemCount[i])
                continue;

            return true;
        }
    }

    return false;
}

// 判断物品是否为矿锄、铁匠锤、附魔棒、剥皮刀或鱼竿等专业必备工具
bool ItemUsageValue::IsItemNeededForSkill(ItemPrototype const* proto)
{
    switch (proto->ItemId)
    {
    case 2901: //Mining pick
        return ai->HasSkill(SKILL_MINING);
    case 5956: //Blacksmith Hammer
        return ai->HasSkill(SKILL_BLACKSMITHING) || ai->HasSkill(SKILL_ENGINEERING);
    case 6219: //Arclight Spanner
        return ai->HasSkill(SKILL_ENGINEERING);
    case 6218: //Runed copper rod
        return ai->HasSkill(SKILL_ENCHANTING);
    case 6339: //Runed silver rod
        return ai->HasSkill(SKILL_ENCHANTING);
    case 11130: //Runed golden rod
        return ai->HasSkill(SKILL_ENCHANTING);
    case 11145: //Runed truesilver rod
        return ai->HasSkill(SKILL_ENCHANTING);
    case 16207: //Runed Arcanite Rod
        return ai->HasSkill(SKILL_ENCHANTING);
    case 7005: //Skinning Knife
        return ai->HasSkill(SKILL_SKINNING);
    case 4471: //Flint and Tinder
        return ai->HasSkill(SKILL_COOKING);
    case 4470: //Simple Wood
        return ai->HasSkill(SKILL_COOKING);
    case 6256: //Fishing Rod
        return ai->HasSkill(SKILL_FISHING);
    }

    return false;
}


// 判断物品是否对机器人已学会的制造或采集专业有用
bool ItemUsageValue::IsItemUsefulForSkill(ItemPrototype const* proto)
{
    switch (proto->Class)
    {
    case ITEM_CLASS_TRADE_GOODS:
    case ITEM_CLASS_MISC:
    case ITEM_CLASS_REAGENT:
    {
        if (ai->HasSkill(SKILL_TAILORING) && IsItemUsedBySkill(proto, SKILL_TAILORING))
            return true;
        if (ai->HasSkill(SKILL_LEATHERWORKING) && IsItemUsedBySkill(proto, SKILL_LEATHERWORKING))
            return true;
        if (ai->HasSkill(SKILL_ENGINEERING) && IsItemUsedBySkill(proto, SKILL_ENGINEERING))
            return true;
        if (ai->HasSkill(SKILL_BLACKSMITHING) && IsItemUsedBySkill(proto, SKILL_BLACKSMITHING))
            return true;
        if (ai->HasSkill(SKILL_ALCHEMY) && IsItemUsedBySkill(proto, SKILL_ALCHEMY))
            return true;
        if (ai->HasSkill(SKILL_ENCHANTING) && IsItemUsedBySkill(proto, SKILL_ENCHANTING))
            return true;
        if (ai->HasSkill(SKILL_FISHING) && IsItemUsedBySkill(proto, SKILL_FISHING))
            return true;
        if (ai->HasSkill(SKILL_FIRST_AID) && IsItemUsedBySkill(proto, SKILL_FIRST_AID))
            return true;
        if (ai->HasSkill(SKILL_COOKING) && IsItemUsedBySkill(proto, SKILL_COOKING))
            return true;
#ifndef MANGOSBOT_ZERO
        if (ai->HasSkill(SKILL_JEWELCRAFTING) && IsItemUsedBySkill(proto, SKILL_JEWELCRAFTING))
            return true;
#endif
        if (ai->HasSkill(SKILL_MINING) &&
            (
                IsItemUsedBySkill(proto, SKILL_MINING)// ||
                //IsItemUsedBySkill(proto, SKILL_BLACKSMITHING) ||
#ifndef MANGOSBOT_ZERO
                //IsItemUsedBySkill(proto, SKILL_JEWELCRAFTING) ||
#endif
                //IsItemUsedBySkill(proto, SKILL_ENGINEERING)
                ))
            return true;
        if (ai->HasSkill(SKILL_SKINNING) &&
            (IsItemUsedBySkill(proto, SKILL_SKINNING)))// || IsItemUsedBySkill(proto, SKILL_LEATHERWORKING)))
            return true;
        if (ai->HasSkill(SKILL_HERBALISM) &&
            (IsItemUsedBySkill(proto, SKILL_HERBALISM)))// || IsItemUsedBySkill(proto, SKILL_ALCHEMY)))
            return true;
        break;
    }
    case ITEM_CLASS_RECIPE:
    {
        if (bot->HasSpell(GetRecipeSpell(proto)))
            break;

        switch (proto->SubClass)
        {
        case ITEM_SUBCLASS_LEATHERWORKING_PATTERN:
            return ai->HasSkill(SKILL_LEATHERWORKING);
        case ITEM_SUBCLASS_TAILORING_PATTERN:
            return ai->HasSkill(SKILL_TAILORING);
        case ITEM_SUBCLASS_ENGINEERING_SCHEMATIC:
            return ai->HasSkill(SKILL_ENGINEERING);
        case ITEM_SUBCLASS_BLACKSMITHING:
            return ai->HasSkill(SKILL_BLACKSMITHING);
        case ITEM_SUBCLASS_COOKING_RECIPE:
            return ai->HasSkill(SKILL_COOKING);
        case ITEM_SUBCLASS_ALCHEMY_RECIPE:
            return ai->HasSkill(SKILL_ALCHEMY);
        case ITEM_SUBCLASS_FIRST_AID_MANUAL:
            return ai->HasSkill(SKILL_FIRST_AID);
        case ITEM_SUBCLASS_ENCHANTING_FORMULA:
            return ai->HasSkill(SKILL_ENCHANTING);
        case ITEM_SUBCLASS_FISHING_MANUAL:
            return ai->HasSkill(SKILL_FISHING);
        }
    }
    }
    return false;
}

// 检查该材料是否可用于机器人当前需要/有用的配方制作
bool ItemUsageValue::IsItemNeededForUsefullCraft(ItemPrototype const* proto, bool checkAllReagents)
{
    std::vector<uint32> spellIds = AI_VALUE(std::vector<uint32>, "craft spells");

    for (uint32 spellId : spellIds)
    {
        const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);

        if (!pSpellInfo)
            continue;

        bool isReagentFor = false;
        bool hasOtherReagents = true;

        for (uint8 i = 0; i < MAX_SPELL_REAGENTS; i++)
        {
            if (!pSpellInfo->ReagentCount[i] || !pSpellInfo->Reagent[i])
                continue;

            if (pSpellInfo->Reagent[i] == proto->ItemId)
            {
                isReagentFor = true;
            }
            else if (checkAllReagents)
            {
                const ItemPrototype* reqProto = sObjectMgr.GetItemPrototype(pSpellInfo->Reagent[i]);

                uint32 count = AI_VALUE2(uint32, "item count", reqProto->Name1);

                if (count < pSpellInfo->ReagentCount[i])
                    hasOtherReagents = false;
            }
        }

        if (!isReagentFor || !hasOtherReagents)
            continue;

        if (!AI_VALUE2(bool, "should craft spell", spellId))
            continue;

        return true;
    }

    return false;
}

// 从背包或装备中查找与指定物品原型匹配的实例
Item* ItemUsageValue::CurrentItem(ItemPrototype const* proto, Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    AiObjectContext* context = ai->GetAiObjectContext();
    ChatHelper* chat = ai->GetChatHelper();
    Item* bestItem = nullptr;
    std::list<Item*> found = AI_VALUE2(std::list < Item*>, "inventory items", chat->formatItem(proto));

    for (auto item : found)
    {
        if (bestItem && item->GetUInt32Value(ITEM_FIELD_DURABILITY) < bestItem->GetUInt32Value(ITEM_FIELD_DURABILITY))
            continue;

        if (bestItem && item->GetCount() < bestItem->GetCount())
            continue;

        bestItem = item;
    }

    return bestItem;
}

// 查找该物品将要装备的对应槽位上当前已穿戴的物品
Item* ItemUsageValue::CurrentItemInSlot(ItemPrototype const* proto, Player* bot)
{
    uint16 dest;

    InventoryResult result;
    result = RandomPlayerbotMgr::CanEquipUnseenItem(bot, NULL_SLOT, dest, proto->ItemId);

    if (result != EQUIP_ERR_OK)
        return nullptr;

    return bot->GetItemByPos(dest);    
}

// 计算机器人当前持有的指定物品堆叠总组数
float ItemUsageValue::CurrentStacks(PlayerbotAI* ai, ItemPrototype const* proto)
{
    uint32 maxStack = proto->GetMaxStackSize();

    AiObjectContext* context = ai->GetAiObjectContext();
    ChatHelper* chat = ai->GetChatHelper();

    std::list<Item*> found = AI_VALUE2(std::list<Item*>, "inventory items", chat->formatItem(proto));

    float itemCount = 0;

    for (auto stack : found)
    {
        itemCount += stack->GetCount();
    }

    return itemCount / maxStack;
}

// 统计背包中比指定物品更高级的同类型物品（如食物/药水/弹药）组数
float ItemUsageValue::BetterStacks(ItemPrototype const* proto, std::string itemType)
{
    std::list<Item*> items = AI_VALUE2(std::list<Item*>, "inventory items", itemType);

    float stacks = 0;

    for (auto& otherItem : items)
    {
        const ItemPrototype* otherProto = otherItem->GetProto();

        if (otherProto->Class != proto->Class || otherProto->SubClass != proto->SubClass)
            continue;

        if (otherProto->ItemLevel < proto->ItemLevel)
            continue;

        if (otherProto->ItemId == proto->ItemId)
            continue;

        stacks += CurrentStacks(ai, otherProto);
    }

    return stacks;
}


// 查找机器人已学会且需要消耗指定物品施放的法术列表
std::vector<uint32> ItemUsageValue::SpellsUsingItem(uint32 itemId, Player* bot)
{
    std::vector<uint32> retSpells;

    PlayerSpellMap const& spellMap = bot->GetSpellMap();

    for (auto& spell : spellMap)
    {
        uint32 spellId = spell.first;

        if (spell.second.state == PLAYERSPELL_REMOVED || spell.second.disabled || IsPassiveSpell(spellId))
            continue;

        const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
        if (!pSpellInfo)
            continue;

        for (uint8 i = 0; i < MAX_SPELL_REAGENTS; i++)
            if (pSpellInfo->ReagentCount[i] > 0 && pSpellInfo->Reagent[i] == itemId)
                retSpells.push_back(spellId);
    }

    return retSpells;
}

// 判断物品是否为恢复生命值的食物或饮料
bool ItemUsageValue::IsHpFoodOrDrink(ItemPrototype const* proto)
{
    if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE
        && (proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_FOOD
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE_OTHER))
    {
        for (auto spell : proto->Spells)
        {
            if (spell.SpellCategory == 11)
            {
                return true;
            }
        }
    }

    return false;
}

// 判断物品是否为恢复法力值的食物或饮料
bool ItemUsageValue::IsManaFoodOrDrink(ItemPrototype const* proto)
{
    if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE
        && (proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_FOOD
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE_OTHER))
    {
        for (auto spell : proto->Spells)
        {
            if (spell.SpellCategory == 59)
            {
                return true;
            }
        }
    }

    return false;
}

// 判断物品是否为治疗药水
bool ItemUsageValue::IsHealingPotion(ItemPrototype const* proto)
{
    if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE &&
        (proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_POTION
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_FLASK
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE_OTHER))
    {
        for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
        {
            const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(proto->Spells[j].SpellId);
            if (spellInfo)
                for (int i = 0; i < 3; i++)
                {
                    if (spellInfo->Effect[i] == SPELL_EFFECT_HEAL)
                        return true;
                }
        }
    }

    return false;
}

// 判断物品是否为法力药水
bool ItemUsageValue::IsManaPotion(ItemPrototype const* proto)
{
    if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE &&
        (proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_POTION
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_FLASK
            || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE_OTHER))
    {
        for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
        {
            const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(proto->Spells[j].SpellId);
            if (spellInfo)
                for (int i = 0; i < 3; i++)
                {
                    if (spellInfo->Effect[i] == SPELL_EFFECT_ENERGIZE && spellInfo->EffectMiscValue[i] == POWER_MANA)
                        return true;
                }
        }
    }

    return false;
}

// 判断物品是否为急救绷带
bool ItemUsageValue::IsBandage(ItemPrototype const* proto)
{
    if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE
        && proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_BANDAGE)
    {
        return true;
    }

    return false;
}

// 判断物品是否为解毒类抗毒药剂
bool ItemUsageValue::IsAntiVenom(ItemPrototype const* proto)
{
    if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE)
    {
        for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
        {
            const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(proto->Spells[j].SpellId);
            if (spellInfo)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (spellInfo->Effect[i] == SPELL_EFFECT_DISPEL && spellInfo->EffectMiscValue[i] == DISPEL_POISON)
                        return true;
                }
            }
        }
    }

    return false;
}

// 从配方/图纸物品原型中提取其教授的制造法术 ID
uint32 ItemUsageValue::GetRecipeSpell(ItemPrototype const* proto)
{
#ifndef MANGOSBOT_ZERO
    if (proto->Spells[0].SpellId == SPELL_ID_GENERIC_LEARN && proto->Spells[1].SpellTrigger == ITEM_SPELLTRIGGER_LEARN_SPELL_ID)
        return proto->Spells[1].SpellId;
#endif

    if (proto->Spells[2].SpellId)
        return proto->Spells[2].SpellId;

    for (uint8 i = 0; i < 4; i++)
    {
        if (proto->Spells[i].SpellId)
        {
            const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(proto->Spells[i].SpellId);

            if (!pSpellInfo)
                return 0;

            for (int j = 0; j < 3; ++j)
            {
                if (pSpellInfo->Effect[j] == SPELL_EFFECT_LEARN_SPELL)
                {
                    if (pSpellInfo->EffectTriggerSpell[j])
                        return pSpellInfo->EffectTriggerSpell[j];
                }
            }
        }
    }
    return 0;
}

// 初始化缓存全游戏各专业制造/采集关联的材料物品 ID 表
void ItemUsageValue::PopulateProfessionReagentIds()
{
    m_allReagentItemIdsForCraftingSkillsVector.clear();

    for (uint32 i = 0; i < sSkillLineStore.GetNumRows(); ++i)
    {
        SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(i);
        if (!skillInfo)
            continue;

        if (skillInfo->categoryId == SKILL_CATEGORY_PROFESSION || skillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
        {
            for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
            {
                SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
                if (!skillLine)
                    continue;

                // wrong skill | 非对应专业技能则跳过
                if (skillLine->skillId != skillInfo->id)
                    continue;

                SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(skillLine->spellId);
                if (spellInfo)
                {
                    bool isReagentFor = false;

                    for (uint8 i = 0; i < MAX_SPELL_REAGENTS; i++)
                    {
                        if (!spellInfo->ReagentCount[i] || !spellInfo->Reagent[i])
                            continue;

                        m_reagentItemIdsForCraftingSkills[skillLine->skillId].insert(spellInfo->Reagent[i]);
                        m_allReagentItemIdsForCraftingSkills.insert(spellInfo->Reagent[i]);
                        m_allReagentItemIdsForCraftingSkillsVector.push_back(spellInfo->Reagent[i]);
                    }
                }
            }
        }
    }
}

// 初始化缓存每个可制造物品对应的材料配方表
void ItemUsageValue::PopulateReagentItemIdsForCraftableItemIds()
{
    m_craftingReagentItemIdsForCraftableItem.clear();
    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine)
            continue;

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(skillLine->spellId);
        if (spellInfo)
        {
            for (int i = 0; i < 3; ++i)
            {
                if (spellInfo->Effect[i] == SPELL_EFFECT_CREATE_ITEM)
                {
                    uint32 craftedItemId = spellInfo->EffectItemType[i];

                    if (craftedItemId)
                    {
                        for (uint32 x = 0; x < MAX_SPELL_REAGENTS; ++x)
                        {
                            if (spellInfo->Reagent[x] <= 0)
                            {
                                continue;
                            }

                            uint32 reagentItemId = spellInfo->Reagent[x];
                            uint32 reagentsRequiredCount = spellInfo->ReagentCount[x];
                            if (reagentItemId && ObjectMgr::GetItemPrototype(reagentItemId))
                            {
                                m_craftingReagentItemIdsForCraftableItem[craftedItemId].push_back({ reagentItemId , reagentsRequiredCount });
                            }
                        }
                    }
                }
            }
        }
    }
}

// 初始化缓存所有 NPC 商人及阵营模板出售的物品与限量物品集合
void ItemUsageValue::PopulateSoldByVendorItemIds()
{
    if (auto result = WorldDatabase.PQuery("%s", "SELECT distinct item FROM npc_vendor"))
    {
        BarGoLink bar(result->GetRowCount());
        do
        {
            bar.step();
            Field* fields = result->Fetch();
            uint32 entry = fields[0].GetUInt32();
            if (!entry)
                continue;

            if (!ObjectMgr::GetItemPrototype(entry))
                continue;

            m_allItemIdsSoldByAnyVendors.insert(fields[0].GetUInt32());
        } while (result->NextRow());
    }

    if (auto result = WorldDatabase.PQuery("%s", "SELECT distinct item FROM npc_vendor WHERE maxcount > 0"))
    {
        BarGoLink bar(result->GetRowCount());
        do
        {
            bar.step();
            Field* fields = result->Fetch();
            uint32 entry = fields[0].GetUInt32();
            if (!entry)
                continue;

            if (!ObjectMgr::GetItemPrototype(entry))
                continue;

            m_itemIdsSoldByAnyVendorsWithLimitedMaxCount.insert(fields[0].GetUInt32());
        } while (result->NextRow());
    }
}

// 返回所有专业相关材料物品 ID 的扁平向量
std::vector<uint32> ItemUsageValue::GetAllReagentItemIdsForCraftingSkillsVector()
{
    return m_allReagentItemIdsForCraftingSkillsVector;
}

// 返回制造指定物品所需的全部材料及其数量列表
std::vector<std::pair<uint32, uint32>> ItemUsageValue::GetAllReagentItemIdsForCraftingItem(ItemPrototype const* proto)
{
    auto items = m_craftingReagentItemIdsForCraftableItem.find(proto->ItemId);

    if (items == m_craftingReagentItemIdsForCraftableItem.end())
        return {};

    return items->second;
}

// 判断物品是否可在任意 NPC 商人处购得
bool ItemUsageValue::IsItemSoldByAnyVendor(ItemPrototype const* proto)
{
    return m_allItemIdsSoldByAnyVendors.count(proto->ItemId) > 0;
}

// 判断任务是否要求装备该物品（如黑翼斗篷等）
bool ItemUsageValue::MustEquipForQuest(ItemPrototype const* proto, Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    AiObjectContext* context = ai->GetAiObjectContext();

    switch (proto->ItemId)
    {
    case 39371:
        return AI_VALUE2(bool, "need quest objective", 12720);
    }

    return false;
}

// 判断物品是否仅由限量刷新商人出售
bool ItemUsageValue::IsItemSoldByAnyVendorButHasLimitedMaxCount(ItemPrototype const* proto)
{
    return m_itemIdsSoldByAnyVendorsWithLimitedMaxCount.count(proto->ItemId) > 0;
}

// 判断物品是否被指定专业技能作为材料使用
bool ItemUsageValue::IsItemUsedBySkill(ItemPrototype const* proto, SkillType skillType)
{
    return m_reagentItemIdsForCraftingSkills[skillType].count(proto->ItemId) > 0;
}

// 判断物品是否为任意配方所需的制造材料
bool ItemUsageValue::IsItemUsedToCraftAnything(ItemPrototype const* proto)
{
    return m_allReagentItemIdsForCraftingSkills.count(proto->ItemId) > 0;
}

// 计算拍卖行当前在售该物品的单价中位数
uint32 ItemUsageValue::GetAHMedianBuyoutPricePerItem(ItemPrototype const* proto)
{
    if (sPlayerbotAIConfig.shouldQueryAHListingsOutsideOfAH)
    {
        std::vector<float> prices;

        for (auto& auction : sRandomPlayerbotMgr.GetAhPrices(proto->ItemId))
        {
            prices.push_back((float)auction.buyout / (float)auction.itemCount);
        }

        if (prices.empty())
            return 0;

        size_t n = prices.size() / 2;
        std::nth_element(prices.begin(), prices.begin() + n, prices.end());
        return prices[n];
    }

    return 0;
}

// 查询拍卖行当前在售该物品的最低一口价单价
uint32 ItemUsageValue::GetAHListingLowestBuyoutPricePerItem(ItemPrototype const* proto)
{
    if (sPlayerbotAIConfig.shouldQueryAHListingsOutsideOfAH)
    {
        float minPrice = 0;
        uint32 minBuyout = 0;

        for (auto& auction : sRandomPlayerbotMgr.GetAhPrices(proto->ItemId))
        {            
            if (!minBuyout || minBuyout > auction.buyout)
            {
                minBuyout = auction.buyout;
                minPrice = (float)auction.buyout / (float)auction.itemCount;
            }
        }
       
        return minBuyout;
        // 注释：已弃用的直接查询数据库拍卖表逻辑
        /*
        auto query = CharacterDatabase.PQuery(
            "SELECT buyoutprice / item_count"
            " FROM auction"
            " WHERE item_template = '%u'"
            " ORDER BY buyoutprice ASC"
            " LIMIT 1",
            proto->ItemId
        );
        if (query)
        {
            do
            {
                Field* fields = query->Fetch();

                uint32 lowestBuyoutPrice = (fields[0].GetUInt32());

                return lowestBuyoutPrice;
            } while (query->NextRow());
        }
        */
    }

    return 0;
}

// 判断拍卖行最低一口价是否已跌破保底收购价
bool ItemUsageValue::AreCurrentAHListingsTooCheap(ItemPrototype const* proto)
{
    uint32 lowestAhItemListingBuyoutPrice = GetAHListingLowestBuyoutPricePerItem(proto);
    uint32 lowestAcceptapleAhBuyoutPrice = GetBotAHSellMinPrice(proto);

    //check if AH listings are already at the bottom price (with a 1% margin for possible calculation errors and is generally better) | 检查拍卖行当前最低价是否已接近底价（预留 1% 误差空间）
    if (lowestAhItemListingBuyoutPrice > 0 && lowestAhItemListingBuyoutPrice <= lowestAcceptapleAhBuyoutPrice + (lowestAcceptapleAhBuyoutPrice * 0.01f))
    {
        return true;
    }

    return false;
}

// 判断将物品挂上拍卖行是否比直接卖给 NPC 商人更有利可图
bool ItemUsageValue::IsMoreProfitableToSellToAHThanToVendor(ItemPrototype const* proto, Player* bot)
{
    if (proto->Bonding == ItemBondingType::BIND_WHEN_PICKED_UP)
    {
        return false;
    }

    if (AreCurrentAHListingsTooCheap(proto))
    {
        return false;
    }

    for (auto itemId : sPlayerbotAIConfig.ahOverVendorItemIds)
    {
        if (itemId == proto->ItemId)
        {
            return true;
        }
    }

    for (auto itemId : sPlayerbotAIConfig.vendorOverAHItemIds)
    {
        if (itemId == proto->ItemId)
        {
            return false;
        }
    }

    //exceptions | 拍卖评估例外情况处理
    //cool consumeables?
    if (proto->ItemId == 2662) //noggerfogger
        return true;

    if (proto->Class == ItemClass::ITEM_CLASS_QUEST)
    {
        return true;
    }

    if (IsItemUsedToCraftAnything(proto) && !IsItemSoldByAnyVendor(proto))
    {
        return true;
    }

    if (IsItemSoldByAnyVendorButHasLimitedMaxCount(proto) && !(proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE && proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_SCROLL))
    {
        return true;
    }

    switch (proto->Quality)
    {
    case ItemQualities::ITEM_QUALITY_POOR:
    {
        //gray items usually are only worth as much as their vendor sell price | 灰色品质物品通常只值卖店价
        return false;
    }
    case ItemQualities::ITEM_QUALITY_NORMAL:
    {
        if (proto->Class == ItemClass::ITEM_CLASS_WEAPON)
        {
            //white weapons is trash
            return false;
        }

        if (proto->Class == ItemClass::ITEM_CLASS_ARMOR)
        {
            //shirts are nice to AH (or other cosmetics something?), also avoid something super cheap like starter boots
            if (proto->SubClass == ItemSubclassArmor::ITEM_SUBCLASS_ARMOR_MISC && GetItemBaseValue(proto) > 10)
            {
                return true;
            }

            //white armor is trash
            return false;
        }

        if (proto->Class == ItemClass::ITEM_CLASS_PROJECTILE)
        {
            //white projectile class is trash
            return false;
        }

        if (proto->Class == ItemClass::ITEM_CLASS_REAGENT)
        {
            //most reagents are sold by vendors
            return !IsItemSoldByAnyVendor(proto);
        }

        if (proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE)
        {
            if (proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_SCROLL)
            {
                //scrolls are trash
                return false;
            }

            //food & drinks
            if ((proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_CONSUMABLE || proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_FOOD))
            {

                return !IsItemSoldByAnyVendor(proto);
            }
        }

        return true;
    }
    //UNCOMMON+ are usually all worth at least the "buy from vendor" price | 绿色（优秀）及以上品质通常至少值商人收购价
    case ItemQualities::ITEM_QUALITY_UNCOMMON:
    case ItemQualities::ITEM_QUALITY_RARE:
    case ItemQualities::ITEM_QUALITY_EPIC:
    case ItemQualities::ITEM_QUALITY_LEGENDARY:
    case ItemQualities::ITEM_QUALITY_ARTIFACT:
    {
        return true;
    }
    default:
        break;
    }

    return false;
}

// 评估从商人处购买物品转手挂拍卖行倒卖是否划算
bool ItemUsageValue::IsWorthBuyingFromVendorToResellAtAH(ItemPrototype const* proto, bool isLimitedSupply)
{
    if (proto->Bonding == ItemBondingType::BIND_WHEN_PICKED_UP)
    {
        return false;
    }

    if (AreCurrentAHListingsTooCheap(proto))
    {
        return false;
    }

    for (auto itemId : sPlayerbotAIConfig.vendorOverAHItemIds)
    {
        if (itemId == proto->ItemId)
        {
            return false;
        }
    }

    //exceptions
    //cool consumeables?
    if (proto->ItemId == 2662) //noggerfogger
        return true;

    //copper rod
    if (proto->ItemId == 6217)
        return false;

    //do not buy items that require reputation to use
    if (proto->RequiredReputationFaction > 0 || proto->RequiredReputationRank > 0)
    {
        return false;
    }

    //do not buy items that require honor to use
    if (proto->RequiredHonorRank > 0)
    {
        return false;
    }

    if (GetAHMedianBuyoutPricePerItem(proto) > static_cast<uint32>(proto->BuyPrice * 1.1f))
    {
        return true;
    }

    if (isLimitedSupply && !(proto->Class == ItemClass::ITEM_CLASS_CONSUMABLE && proto->SubClass == ItemSubclassConsumable::ITEM_SUBCLASS_SCROLL))
    {
        return true;
    }

    //do not buy items that require skill to use, unless limited supply or recipe (just in case)
    if (proto->RequiredSkill > 0 && !(proto->Class == ItemClass::ITEM_CLASS_RECIPE))
    {
        return false;
    }

    switch (proto->Quality)
    {
    case ItemQualities::ITEM_QUALITY_POOR:
    {
        return false;
    }
    case ItemQualities::ITEM_QUALITY_NORMAL:
    {
        //some white items may be worth it

        if (proto->Class == ItemClass::ITEM_CLASS_RECIPE)
        {
            if (proto->SubClass == ItemSubclassRecipe::ITEM_SUBCLASS_BOOK)
            {
                return true;
            }
        }

        return false;
    }
    //UNCOMMON+ are usually all worth it
    case ItemQualities::ITEM_QUALITY_UNCOMMON:
    case ItemQualities::ITEM_QUALITY_RARE:
    case ItemQualities::ITEM_QUALITY_EPIC:
    case ItemQualities::ITEM_QUALITY_LEGENDARY:
    case ItemQualities::ITEM_QUALITY_ARTIFACT:
    {
        return true;
    }
    default:
        break;
    }

    return false;
}

// 评估从拍卖行低价扫货并高价转卖是否具备套利空间
bool ItemUsageValue::IsWorthBuyingFromAhToResellAtAH(ItemPrototype const* proto, uint32 totalCost, uint32 itemCount)
{
    uint32 pricePerItem = totalCost / itemCount;

    //bottom half is probably always worth buying? That should reduce oversupply | 低于中位数半价的商品通常值得扫货以减少低价积压
    return pricePerItem <= GetBotAHSellMinPrice(proto) + ((GetBotAHSellMaxPrice(proto) - GetBotAHSellMinPrice(proto)) / 2);
}

// 根据物品稀有度（品质）返回价格估值倍率
double ItemUsageValue::GetRarityPriceMultiplier(ItemPrototype const* proto)
{
    float x = sRandomItemMgr.GetItemRarity(proto->ItemId);
    if (x < 0.001) return 1.0f;
    return 0.75 + exp((140 - x) / 50) / 6;
}

// 根据物品等级或需求等级返回价格估值倍率
double ItemUsageValue::GetLevelPriceMultiplier(ItemPrototype const* proto)
{
    float x = 0.1f + proto->ItemLevel;
    return 0.5 + exp(x / 60) / 2;
}

// 基于材料成本、品质与等级综合计算物品基准估值
uint32 ItemUsageValue::GetItemBaseValue(ItemPrototype const* proto, uint8 maxReagentLevel)
{
    if (proto->Quality == ItemQualities::ITEM_QUALITY_POOR)
    {
        return proto->SellPrice;
    }

    if (IsItemSoldByAnyVendor(proto))
    {
        //if item is sold by a vendor - price can never be lower than BuyPrice, because bots may buy from vendor to resell | 若商人有售，基准价不低于购买价以防低买高卖套利错乱
        return proto->BuyPrice;
    }

    //calculate total value of reagents if the item is craftable | 若物品可制造则累计其材料总价值
    if (maxReagentLevel > 0 && GetAllReagentItemIdsForCraftingItem(proto).size() > 0)
    {
        maxReagentLevel--;
        uint32 totalReagentsValue = 0;

        for (auto idCountPair : GetAllReagentItemIdsForCraftingItem(proto))
        {
            ItemPrototype const* reagentProto = ObjectMgr::GetItemPrototype(idCountPair.first);
            totalReagentsValue += GetItemBaseValue(reagentProto, maxReagentLevel) * idCountPair.second;
        }

        if (totalReagentsValue > 0)
        {
            return totalReagentsValue;
        }
    }

    //some items, which are not sold by vendors, have very low or very high vendor buy price, can't rely on it, need to adjust SellPrice | 部分非商店出售物品的 BuyPrice 异常，需基于 SellPrice 修正
    return static_cast<uint32>(proto->SellPrice * GetRarityPriceMultiplier(proto) * GetLevelPriceMultiplier(proto) * 1.5f);
}

// 计算机器人愿意出价收购或竞拍该物品的价格
uint32 ItemUsageValue::GetBotBuyPrice(ItemPrototype const* proto, Player* bot)
{
    return static_cast<uint32>(GetItemBaseValue(proto) * sRandomPlayerbotMgr.GetBuyMultiplier(bot));
}

// 计算机器人在拍卖行出售该物品的目标参考价（不低于卖店价）
uint32 ItemUsageValue::GetBotSellPrice(ItemPrototype const* proto, Player* bot)
{
    //should never sell for less than sell to vendor price | 拍卖底价绝不能低于直接卖给 NPC 商人的价格
    return std::max(
        static_cast<uint32>((GetItemBaseValue(proto) + 1) * sRandomPlayerbotMgr.GetSellMultiplier(bot)),
        static_cast<uint32>(proto->SellPrice * 1.1f)
    );
}

// 计算拍卖行挂单底价（基准估值 75%）
uint32 ItemUsageValue::GetBotAHSellMinPrice(ItemPrototype const* proto)
{
    return static_cast<uint32>(GetItemBaseValue(proto) * 2.00f);
}

// 计算拍卖行挂单最高参考价（基准估值 150%）
uint32 ItemUsageValue::GetBotAHSellMaxPrice(ItemPrototype const* proto)
{
    return static_cast<uint32>(GetItemBaseValue(proto) * 2.5f);
}

// 估算委托制造该物品的基准手工费
uint32 ItemUsageValue::GetCraftingFee(ItemPrototype const* proto)
{
    uint32 fixedMinCraftingFee = 100;
    uint32 level = std::max(proto->ItemLevel, proto->RequiredLevel);
    return fixedMinCraftingFee * level * level / 40;
}

// 结合拍卖行当前最低价和市场竞争压价计算实际挂拍单价
uint32 ItemUsageValue::DesiredPricePerItem(Player* bot, const ItemPrototype* proto, uint32 count, uint32 priceModifier)
{
    AuctionEntry lowestPrice;

    lowestPrice.Id = 0;

    std::vector<AuctionEntry> auctions;

    for (auto& auction : sRandomPlayerbotMgr.GetAhPrices(proto->ItemId))
    {
        float pricePerItem = float(auction.buyout) / float(auction.itemCount);

        if (auction.itemCount != count)
            continue;

        if (lowestPrice.Id == 0 || pricePerItem < float(lowestPrice.buyout) / float(lowestPrice.itemCount))
            lowestPrice = auction;
    }

    uint32 lowestBuyoutItemPricePerItem = float(lowestPrice.buyout) / float(lowestPrice.itemCount);

    uint32 maxAhPrice = GetBotAHSellMaxPrice(proto);
    uint32 minAhPrice = GetBotAHSellMinPrice(proto);

    if (!maxAhPrice)
    {
        minAhPrice = lowestBuyoutItemPricePerItem;
        maxAhPrice = GetAHMedianBuyoutPricePerItem(proto) * 1.5f;
        if (!maxAhPrice)
            maxAhPrice = minAhPrice * 1.5f;
    }

    uint32 desiredPricePerItem = minAhPrice + static_cast<uint32>((maxAhPrice - minAhPrice) * priceModifier / 100);

    if (lowestBuyoutItemPricePerItem > 0 && lowestPrice.owner != bot->GetDbGuid())
    {
        uint32 undercutByMoney = std::max(static_cast<uint32>(1), static_cast<uint32>(lowestBuyoutItemPricePerItem * frand(0.0f, 0.1f)));

        if (undercutByMoney < lowestBuyoutItemPricePerItem)
        {
            desiredPricePerItem = lowestBuyoutItemPricePerItem - undercutByMoney;
        }
        else
        {
            desiredPricePerItem = lowestBuyoutItemPricePerItem - 1;
        }
    }

    desiredPricePerItem = std::max(minAhPrice, desiredPricePerItem);

    return desiredPricePerItem;
}

// 判断当前等级尚不能穿戴的装备在未来 10 级内是否具备升级价值
bool ItemUsageValue::IsItemUsefulForFutureEquip(ItemPrototype const* proto)
{
    if (proto->InventoryType == INVTYPE_NON_EQUIP)
        return false;

    if (proto->Quality < ITEM_QUALITY_UNCOMMON)
        return false;

    if (proto->Bonding == BIND_WHEN_PICKED_UP)
        return false;

    if (proto->RequiredLevel <= bot->GetLevel())
        return false;

    if (proto->RequiredLevel > bot->GetLevel() + 10)
        return false;

    if (bot->CanUseItem(proto) == EQUIP_ERR_OK)
        return false; // can already use, should be handled by equip logic | 当前已可使用，应由常规装备逻辑处理

    // Check class restriction | 检查职业限制
    if (proto->AllowableClass && !(proto->AllowableClass & bot->getClassMask()))
        return false;

    // Check race restriction | 检查种族限制
    if (proto->AllowableRace && !(proto->AllowableRace & bot->getRaceMask()))
        return false;

    return true;
}

// 判断材料是否可用于机器人当前专业未来的高阶配方
bool ItemUsageValue::IsItemUsefulForFutureCraft(ItemPrototype const* proto)
{
    if (proto->Class != ITEM_CLASS_TRADE_GOODS && proto->Class != ITEM_CLASS_MISC && proto->Class != ITEM_CLASS_REAGENT)
        return false;

    if (proto->Quality < ITEM_QUALITY_NORMAL)
        return false;

    if (IsItemNeededForUsefullCraft(proto, false))
        return false; // already needed now, handled by SKILL usage | 当前已急需，交由 SKILL 用途处理

    // Check if this is a crafting reagent for any recipe the bot's professions use | 检查是否为机器人专业配方所需的制作材料
    if (!m_allReagentItemIdsForCraftingSkills.count(proto->ItemId))
        return false;

    // Check bot has a profession that uses this reagent | 检查机器人是否拥有使用该材料的专业技能
    for (auto& [skillId, reagentSet] : m_reagentItemIdsForCraftingSkills)
    {
        if (!reagentSet.count(proto->ItemId))
            continue;

        if (bot->HasSkill(skillId))
            return true;
    }

    return false;
}
