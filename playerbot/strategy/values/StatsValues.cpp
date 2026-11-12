// 策略值实现：StatsValues（单位生命、资源、背包空间、装备耐久与战斗状态计算）

#include "playerbot/playerbot.h"
#include "StatsValues.h"

#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/actions/CheckMountStateAction.h"

using namespace ai;

// 获取目标单位当前生命值百分比
uint8 HealthValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 100;
    return (static_cast<float> (target->GetHealth()) / target->GetMaxHealth()) * 100;
}

// 检查目标单位是否已死亡
bool IsDeadValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return sServerFacade.GetDeathState(target) != ALIVE;
}

// 查询数据库宠物状态判断是否已有宠物且处于死亡状态
bool PetIsDeadValue::Calculate()
{
#ifdef MANGOSBOT_ZERO
#ifdef MANGOS
    PetDatabaseStatus status = Pet::GetStatusFromDB(bot);
    if (status == PET_DB_DEAD)
#endif
#endif
    if (!bot->GetPet())
    {
        uint32 ownerid = bot->GetGUIDLow();
        auto result = CharacterDatabase.PQuery("SELECT id FROM character_pet WHERE owner = '%u'", ownerid);
        if (!result)
            return false;

        return true;
    }
    if (bot->GetPetGuid() && !bot->GetPet())
        return true;

    return bot->GetPet() && sServerFacade.GetDeathState(bot->GetPet()) != ALIVE;
}

// 检查当前召唤猎人宠物的快乐度是否达到最高档（HAPPY）
bool PetIsHappyValue::Calculate()
{
#ifdef MANGOSBOT_ZERO
#ifndef CMANGOS
    PetDatabaseStatus status = Pet::GetStatusFromDB(bot);
    if (status == PET_DB_DEAD)
        return true;
#endif
#endif

    return !bot->GetPet() || bot->GetPet()->GetHappinessState() == HAPPY;
}


// 读取单位当前怒气值并换算为标准 0-100 刻度
uint8 RageValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 0;
    return (target->GetPower(POWER_RAGE) / 10.0f);
}

// 读取单位当前能量值
uint8 EnergyValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 0;
    return (static_cast<float> (target->GetPower(POWER_ENERGY)));
}

// 计算单位当前法力值百分比
uint8 ManaValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 100;
    return (static_cast<float> (target->GetPower(POWER_MANA)) / target->GetMaxPower(POWER_MANA)) * 100;
}

// 检查单位是否具备法力值上限且未处于无蓝变形状态
bool HasManaValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->GetPower(POWER_MANA);
}


// 读取机器人当前保存的连击点数
uint8 ComboPointsValue::Calculate()
{
    Unit *target = GetTarget();
    if (!target || target->GetObjectGuid() != bot->GetComboTargetGuid())
        return 0;

    return bot->GetComboPoints();
}

// 检查单位是否骑乘或处于德鲁伊飞行形态
bool IsMountedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    if (target->IsMounted())
        return true;

    if (AI_VALUE2(uint32, "current mount speed", getQualifier()))
        return true;

    return false;
}


// 判断单位自身或其队伍成员是否正在战斗中
bool IsInCombatValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    if (sServerFacade.IsInCombat(target)) return true;

    if (target == bot)
    {
        Group* group = bot->GetGroup();
        if (group)
        {
            Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
            for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
            {
                Player *member = sObjectMgr.GetPlayer(itr->guid);
                if (!member || member == bot) continue;

                if (sServerFacade.IsInCombat(member) &&
                    sServerFacade.IsDistanceLessOrEqualThan(sServerFacade.GetDistance2d(member, bot), sPlayerbotAIConfig.reactDistance)) return true;
            }
        }
    }

    return false;
}

// 统计主背包及装备背包总格数与已用格数，返回占用百分比
uint8 BagSpaceValue::Calculate()
{
    uint32 totalused = 0, total = 16;
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        if (bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
            totalused++;
    }

    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
        {
            ItemPrototype const* pBagProto = pBag->GetProto();
            if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
            {
                total += pBag->GetBagSize();
                totalused += pBag->GetBagSize() - pBag->GetFreeSlots();
            }
        }

    }

    return (static_cast<float> (totalused) / total) * 100;
}

// 统计个人银行主栏位及银行背包已用比例
uint8 BankSpaceValue::Calculate()
{
    uint32 totalused = 0, total = 16;
    for (uint8 slot = BANK_SLOT_ITEM_START; slot < BANK_SLOT_ITEM_END; slot++)
    {
        if (bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
            totalused++;
    }

    for (uint8 bag = BANK_SLOT_BAG_START; bag < BANK_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
        {
            ItemPrototype const* pBagProto = pBag->GetProto();
            if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
            {
                total += pBag->GetBagSize();
                totalused += pBag->GetBagSize() - pBag->GetFreeSlots();
            }
        }
    }

    return (static_cast<float>(totalused) / total) * 100;
}

// 统计已装备栏位所有有耐久装备的总当前耐久与最大耐久百分比
uint8 DurabilityValue::Calculate()
{
    uint32 totalMax = 0, total = 0;

    for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        uint16 pos = ((INVENTORY_SLOT_BAG_0 << 8) | i);
        Item* item = bot->GetItemByPos(pos);

        if (!item)
            continue;

        uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
        if (!maxDurability)
            continue;

        totalMax += maxDurability;

        uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

        total += curDurability;
    }

    if (total == 0)
        return 0;

    return (static_cast<float> (total) / totalMax) * 100;
}

// 统计身上及背包内所有可修理物品的总体耐久百分比
uint8 DurabilityInventoryValue::Calculate()
{
    uint32 totalMax = 0, total = 0;

    for (int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
    {
        uint16 pos = ((INVENTORY_SLOT_BAG_0 << 8) | i);
        Item* item = bot->GetItemByPos(pos);

        if (!item)
            continue;

        uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
        if (!maxDurability)
            continue;

        totalMax += maxDurability;

        uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

        total += curDurability;
    }

    if (total == 0)
        return 0;

    return (static_cast<float> (total) / totalMax) * 100;
}

// 查找身上已装备物品中最低的单件耐久百分比
uint8 LowestDurabilityValue::Calculate()
{
    uint32 durabilityPercent, minDurabilityPercent = 100;

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

        durabilityPercent = (static_cast<float> (curDurability) / maxDurability) * 100;

        if (durabilityPercent < minDurabilityPercent)
            minDurabilityPercent = durabilityPercent;
    }

    return minDurabilityPercent;
}

// 计算目标当前地面跑速相对于标准速度（7.0）的百分比
uint8 SpeedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 100;

    return (uint8) (100.0f * target->GetSpeedRate(MOVE_RUN));
}

