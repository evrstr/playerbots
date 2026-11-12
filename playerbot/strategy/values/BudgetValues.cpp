// 策略值实现：BudgetValues（装备修理费用及多用途预算计算）
#include "playerbot/playerbot.h"
#include "BudgetValues.h"
#include "ItemUsageValue.h"
#include "MountValues.h"

using namespace ai;

// 计算单件物品的修理花费（支持按当前耐久损失或按完全损坏全额计算）
uint32 RepairCostValue::RepairCost(const Item* item, bool fullCost)
{
    uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
    if (!maxDurability)
        return 0;

    uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

    uint32 LostDurability = maxDurability;
        
    if (!fullCost)
    {
        LostDurability = LostDurability - curDurability;

        if (LostDurability == 0)
            return 0;
    }

    ItemPrototype const* ditemProto = item->GetProto();

    DurabilityCostsEntry const* dcost = sDurabilityCostsStore.LookupEntry(ditemProto->ItemLevel);
    if (!dcost)
        return 0;

    uint32 dQualitymodEntryId = (ditemProto->Quality + 1) * 2;
    DurabilityQualityEntry const* dQualitymodEntry = sDurabilityQualityStore.LookupEntry(dQualitymodEntryId);
    if (!dQualitymodEntry)
        return 0;

    uint32 dmultiplier = dcost->multiplier[ItemSubClassToDurabilityMultiplierId(ditemProto->Class, ditemProto->SubClass)];

    return uint32(LostDurability * dmultiplier * double(dQualitymodEntry->quality_mod));
}

// 遍历已装备及背包物品，累计总修理费用
uint32 RepairCostValue::Calculate()
{
    uint32 TotalCost = 0;
    for (int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
    {
        uint16 pos = ((INVENTORY_SLOT_BAG_0 << 8) | i);
        
        Item* item = bot->GetItemByPos(pos);

        if (!item)
            continue;

        TotalCost += RepairCost(item);
    }

    return TotalCost;
}

// 按全额耐久损失计算全身装备和受损物品的最大修理预算
uint32 MaxGearRepairCostValue::Calculate()
{
    uint32 TotalCost = 0;
    for (int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
    {
        uint16 pos = ((INVENTORY_SLOT_BAG_0 << 8) | i);
        Item* item = bot->GetItemByPos(pos);

        if (!item)
            continue;

        uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
        if (!maxDurability)
            continue;

        uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

        if (i >= EQUIPMENT_SLOT_END && curDurability >= maxDurability) //Only count items equiped or already damanged. | 仅统计已装备或已有耐久损耗的物品
            continue;        

        TotalCost += RepairCost(item, true);
    }

    return TotalCost;
}

// 优先返回主手/远程/副手最核心受损装备的修理费
uint32 MinRepairCostValue::Calculate()
{
    std::vector<uint8> importantSlots = { EQUIPMENT_SLOT_MAINHAND , EQUIPMENT_SLOT_RANGED, EQUIPMENT_SLOT_OFFHAND };
    for (uint32 slot : importantSlots)
    {
        uint16 pos = ((INVENTORY_SLOT_BAG_0 << 8) | slot);
        Item* item = bot->GetItemByPos(pos);

        if (!item)
            continue;

        uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
        if (!maxDurability)
            continue;

        uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

        if (curDurability > 0)
            continue;

        return RepairCost(item); //The cost to repair the most important broken item. | 修理最重要受损装备所需的费用
    }

    return RepairCostValue::Calculate();
}



// 按用途枚举分项估算所需铜币（如弹药、旅行、拍卖行押金、骑术及坐骑购买等）
uint32 MoneyNeededForValue::Calculate()
{
    NeedMoneyFor needMoneyFor = NeedMoneyFor(stoi(getQualifier()));

    PlayerbotAI* ai = bot->GetPlayerbotAI();
    AiObjectContext* context = ai->GetAiObjectContext();

    uint32 moneyWanted = 0;

    uint32 level = bot->GetLevel();

    switch (needMoneyFor)
    {
    case NeedMoneyFor::none:
        moneyWanted = 0;
        break;
    case NeedMoneyFor::repair:
        moneyWanted = AI_VALUE(uint32, "max repair cost");
        break;
    case NeedMoneyFor::ammo:
        moneyWanted = (bot->getClass() == CLASS_HUNTER) ? (level * level * level) / 10 : 0; //Or level^3 (1s @ lvl10, 30s @ lvl30, 2g @ lvl60, 5g @ lvl80): Todo replace (should be best ammo buyable x 8 stacks cost) | 暂按等级立方折算（待替换为实际可购 8 组最佳弹药花费）
        break;
    case NeedMoneyFor::spells:
        moneyWanted = AI_VALUE2(uint32, "train cost", TRAINER_TYPE_CLASS);
        break;
    case NeedMoneyFor::travel:
        moneyWanted = bot->isTaxiCheater() ? 0 : 1500; //15s for traveling half a continent. Todo: Add better calculation (Should be ???) | 跨半块大陆飞行预留 15 银（待完善精确计算）
        break;
    case NeedMoneyFor::gear:
        moneyWanted = level * level * level; //Or level^3 (10s @ lvl10, 3g @ lvl30, 20g @ lvl60, 50g @ lvl80): Todo replace (Should be ~total cost of all >green gear equiped) | 暂按等级立方折算（待替换为绿装以上全身装备估值）
        break;
    case NeedMoneyFor::consumables:
        moneyWanted = (level * level * level) / 10; //Or level^3 (1s @ lvl10, 30s @ lvl30, 2g @ lvl60, 5g @ lvl80): Todo replace (Should be best food/drink x 2 stacks cost) | 暂按等级立方折算（待替换为 2 组最佳食物饮水花费）
        break;
    case NeedMoneyFor::guild:
        if (ai->HasStrategy("guild", BotState::BOT_STATE_NON_COMBAT))
        {
            if (bot->GetGuildId() && bot->GetLevel() > 20)
                moneyWanted = AI_VALUE2(uint32, "item count", chat->formatQItem(5976)) ? 0 : 10000; //1g (tabard) | 公会战袍 1 金
            else if (bot->GetLevel() > 10)
                moneyWanted = AI_VALUE2(uint32, "item count", chat->formatQItem(5863)) ? 0 : 1000; //10s (guild charter) | 公会注册表 10 银
        }
        break;
    case NeedMoneyFor::skilltraining:
        moneyWanted = AI_VALUE2(uint32, "train cost", TRAINER_TYPE_TRADESKILLS);
        break;
    case NeedMoneyFor::tradeskill:
        moneyWanted = (level * level * level); //Or level^3 (10s @ lvl10, 3g @ lvl30, 20g @ lvl60, 50g @ lvl80): Todo replace (Should be buyable reagents that combined allow crafting of usefull items) | 暂按等级立方折算（待替换为可制作实用物品的材料成本）
        break;
    case NeedMoneyFor::ah:
    {
        //Save deposit needed for all items the bot wants to AH. | 预留待上架拍卖行物品所需的保证金
        uint32 time;
#ifdef MANGOSBOT_ZERO
        time = 8 * HOUR;
#else
        time = 12 * HOUR;
#endif
        float totalDeposit = 0;
        for (auto item : AI_VALUE2(std::list<Item*>, "inventory items", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_AH)))
        {
            float deposit = float(item->GetProto()->SellPrice * item->GetCount() * (time / MIN_AUCTION_TIME));

            deposit = deposit * 15 * 3.0f / 100.0f;

            float min_deposit = float(sWorld.getConfig(CONFIG_UINT32_AUCTION_DEPOSIT_MIN));

            if (deposit < min_deposit)
                deposit = min_deposit;

            deposit *= sWorld.getConfig(CONFIG_FLOAT_RATE_AUCTION_DEPOSIT);

            totalDeposit += deposit;
        }

        for (auto item : AI_VALUE2(std::list<Item*>, "inventory items", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_BROKEN_AH)))
        {
            float deposit = float(item->GetProto()->SellPrice * item->GetCount() * (time / MIN_AUCTION_TIME));

            deposit = deposit * 15 * 3.0f / 100.0f;

            float min_deposit = float(sWorld.getConfig(CONFIG_UINT32_AUCTION_DEPOSIT_MIN));

            if (deposit < min_deposit)
                deposit = min_deposit;

            deposit *= sWorld.getConfig(CONFIG_FLOAT_RATE_AUCTION_DEPOSIT);

            totalDeposit += deposit;

            uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
            if (!maxDurability)
                continue;

            uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

            uint32 LostDurability = maxDurability - curDurability;

            if (LostDurability == 0)
                continue;

            ItemPrototype const* ditemProto = item->GetProto();

            DurabilityCostsEntry const* dcost = sDurabilityCostsStore.LookupEntry(ditemProto->ItemLevel);
            if (!dcost)
                continue;

            uint32 dQualitymodEntryId = (ditemProto->Quality + 1) * 2;
            DurabilityQualityEntry const* dQualitymodEntry = sDurabilityQualityStore.LookupEntry(dQualitymodEntryId);
            if (!dQualitymodEntry)
                continue;

            uint32 dmultiplier = dcost->multiplier[ItemSubClassToDurabilityMultiplierId(ditemProto->Class, ditemProto->SubClass)];
            uint32 costs = uint32(LostDurability * dmultiplier * double(dQualitymodEntry->quality_mod));

            totalDeposit += costs;
        }

        return totalDeposit;
        break;
    }
    case NeedMoneyFor::mount:
    {
        uint32 maxMountSpeed = 0;
        uint32 maxFlyMountSpeed = 0;

        moneyWanted = AI_VALUE2(uint32, "train cost", TRAINER_TYPE_MOUNTS);

        for (auto& mount : AI_VALUE(std::vector<MountValue>, "mount list"))
        {
            if (mount.GetSpeed(false) > maxMountSpeed)
            {
                maxMountSpeed = mount.GetSpeed(false);
                maxFlyMountSpeed = mount.GetSpeed(true);
            }
        }

#ifdef MANGOSBOT_ZERO
        const uint8 basicRidingLevel = 40;
        const uint8 epicRidingLevel = 60;
        const uint8 basicFlyingRidingLevel = 0;
        const uint8 EpicFlyingRidingLevel = 0;
        const uint32 basicMountCost = 40 * GOLD;
        const uint32 epicMountCost = 1000 * GOLD;
        const uint32 flyingMountCost = 0;
        const uint32 epicFlyingMountCost = 0;
#endif
#ifdef MANGOSBOT_ONE
        const uint8 basicRidingLevel = 30;
        const uint8 epicRidingLevel = 60;
        const uint8 basicFlyingRidingLevel = 70;
        const uint8 EpicFlyingRidingLevel = 70;
        const uint32 basicMountCost = 950 * SILVER;
        const uint32 epicMountCost = 40 * GOLD;
        const uint32 flyingMountCost = 100 * GOLD;
        const uint32 epicFlyingMountCost = 200 * GOLD;
#endif
#ifdef MANGOSBOT_TWO
        const uint8 basicRidingLevel = 20;
        const uint8 epicRidingLevel = 40;
        const uint8 basicFlyingRidingLevel = 60;
        const uint8 EpicFlyingRidingLevel = 70;
        const uint32 basicMountCost = 90 * SILVER;
        const uint32 epicMountCost = 9 * GOLD;
        const uint32 flyingMountCost = 40 * GOLD;
        const uint32 epicFlyingMountCost = 80 * GOLD;
#endif

        if (level >= basicRidingLevel && maxMountSpeed < 59)
                moneyWanted += basicMountCost;
        if (level >= epicRidingLevel && maxMountSpeed < 99)
                moneyWanted += epicMountCost;
        if (level >= flyingMountCost && maxFlyMountSpeed < 99)
                moneyWanted += basicFlyingRidingLevel;
        if(level >= epicFlyingMountCost && maxFlyMountSpeed < 279)
                moneyWanted += EpicFlyingRidingLevel;
        //todo Wotlk frozen weather flying. | 待处理：WLK 寒冷天气飞行骑术费用
        break;
    }
    }

    return moneyWanted;
};

// 累加预留清单中排在指定用途及之前的所有资金需求
uint32 TotalMoneyNeededForValue::Calculate()
{
    NeedMoneyFor needMoneyFor = NeedMoneyFor(stoi(getQualifier()));

    uint32 moneyWanted = AI_VALUE2(uint32, "money needed for", (uint32)needMoneyFor);

    auto needPtr = std::find(saveMoneyFor.begin(), saveMoneyFor.end(), needMoneyFor);

    while (needPtr != saveMoneyFor.begin())
    {
        needPtr--;

        NeedMoneyFor alsoNeed = *needPtr;

        moneyWanted = moneyWanted + AI_VALUE2(uint32, "money needed for", (uint32)alsoNeed);
    }

    return moneyWanted;
}

// 判断金币作弊标记或当前金钱是否满足总资金需求
bool HasAllMoneyForValue::Calculate()
{
    uint32 money = bot->GetMoney();

    if (ai->HasCheat(BotCheatMask::gold))
        return true;

    uint32 needMoney;

    if (ai->HasActivePlayerMaster())
        needMoney = AI_VALUE2(uint32, "money needed for", getQualifier());
    else
        needMoney = AI_VALUE2(uint32, "total money needed for", getQualifier());

    if (needMoney <= money)
        return true;

    return false;
}


// 计算扣除优先级更高用途的预留资金后，剩余可供消费的金额
uint32 FreeMoneyForValue::Calculate() 
{
    uint32 money = bot->GetMoney();

    if (ai->HasCheat(BotCheatMask::gold))
        return 10000000;

    if (ai->HasActivePlayerMaster())
        return money;

    uint32 savedMoney = AI_VALUE2(uint32, "total money needed for", getQualifier()) - AI_VALUE2(uint32, "money needed for", getQualifier());

    if (savedMoney > money)
        return 0;

    return money - savedMoney;
};