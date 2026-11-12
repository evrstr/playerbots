// 猎人 - 动作实现文件 (HunterActions.cpp)：定义猎人专用技能施放与战斗动作

#include "playerbot/playerbot.h"
#include "playerbot/strategy/actions/GenericActions.h"
#include "HunterActions.h"

using namespace ai;

// 检查动作当前是否有效/可用 (CastSerpentStingAction)
bool CastSerpentStingAction::isUseful()
{
    return CastRangedDebuffSpellAction::isUseful() && AI_VALUE2(uint8, "health", GetTargetName()) > 50 && (!(AI_VALUE2(uint8, "mana", GetTargetName()) >= 10) || (ai->HasStrategy("sting serpent", BotState::BOT_STATE_COMBAT)));
}

// 检查动作当前是否有效/可用 (CastViperStingAction)
bool CastViperStingAction::isUseful()
{
    return CastRangedDebuffSpellAction::isUseful() && AI_VALUE2(uint8, "mana", GetTargetName()) >= 10;
}

// 执行动作逻辑 (FeedPetAction)
bool FeedPetAction::Execute(Event& event)
{
    Pet* pet = bot->GetPet();
    if (pet && pet->getPetType() == HUNTER_PET && pet->GetHappinessState() != HAPPY)
        pet->SetPower(POWER_HAPPINESS, HAPPINESS_LEVEL_SIZE * 2);

    return true;
}

// 检查动作当前是否有效/可用 (CastAutoShotAction)
bool CastAutoShotAction::isUseful()
{
    if (ai->IsInVehicle() && !ai->IsInVehicle(false, false, true))
        return false;

    return ai->HasStrategy("ranged", BotState::BOT_STATE_COMBAT) && AI_VALUE(uint32, "active spell") != AI_VALUE2(uint32, "spell id", getName());
}

// 执行动作逻辑 (HunterEquipAmmoAction)
bool HunterEquipAmmoAction::Execute(Event& event)
{
    // Get ranged weapon
    Item* ranged = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
    if (!ranged)
        return false;

    uint32 ammoClass = ITEM_CLASS_PROJECTILE;
    uint32 subClass = 0;

    switch (ranged->GetProto()->SubClass)
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

    uint32 currentAmmoId = bot->GetUInt32Value(PLAYER_AMMO_ID);
    const ItemPrototype* bestAmmoProto = nullptr;

    // Scan inventory for best ammo
    for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
    {
        if (Bag* bag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            for (uint32 j = 0; j < bag->GetBagSize(); ++j)
            {
                if (Item* item = bag->GetItemByPos(j))
                {
                    const ItemPrototype* proto = item->GetProto();
                    if (!proto)
                        continue;

                    if (proto->Class == ammoClass && proto->SubClass == subClass)
                    {
                        if (!bestAmmoProto || proto->ItemLevel > bestAmmoProto->ItemLevel)
                            bestAmmoProto = proto;
                    }
                }
            }
        }
    }

    // Equip best ammo if not already equipped
    if (bestAmmoProto && currentAmmoId != bestAmmoProto->ItemId)
    {
        bot->SetUInt32Value(PLAYER_AMMO_ID, bestAmmoProto->ItemId);
        bot->UpdateDamagePhysical(RANGED_ATTACK);
        return true;
    }

    return false;
}

// 执行动作逻辑 (CastAutoShotAction)
bool CastAutoShotAction::Execute(Event& event)
{
    if (!bot->IsStopped())
    {
        ai->StopMoving();
    }

    return CastSpellAction::Execute(event);
}

// 执行动作逻辑 (CastSteadyShotAction)
bool CastSteadyShotAction::Execute(Event& event)
{
    if (CastSpellAction::Execute(event))
    {
        const Item* equippedWeapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
        if (equippedWeapon)
        {
            SetDuration(GetDuration() + sPlayerbotAIConfig.globalCoolDown);
        }

        return true;
    }

    return false;
}
