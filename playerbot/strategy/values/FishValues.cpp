// 策略值实现：FishValues（钓鱼能力、引导状态与完成状态检测）

#include "playerbot/playerbot.h"
#include "FishValues.h"

using namespace ai;

// 检查是否拥有钓鱼技能及鱼竿物品
bool CanFishValue::Calculate()
{
    if (!bot->GetSkill(SKILL_FISHING, false, false)) //Unable to fish. | 未学习钓鱼技能，无法钓鱼
        return false;

    std::list<Item*> poles = AI_VALUE2(std::list<Item*>, "inventory items", "fishing pole");

    if (poles.empty()) //No fishing pole. | 缺少鱼竿
        return false;

    return true;
}

// 检查当前引导法术是否为 Fishing
bool CanOpenFishingDobberValue::Calculate()
{
    if (!bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
        return false;

    std::string spellName = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL)->m_spellInfo->SpellName[0];
    if (spellName.find("Fishing") != 0)
        return false;

    return true;
}

// 检查主手是否装备鱼竿且当前未在引导钓鱼法术
bool DoneFishingValue::Calculate()
{
    if (!bot->GetSkill(SKILL_FISHING, false, false)) //Unable to fish. | 未学习钓鱼技能，无法钓鱼
        return false;

    Item* mhItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

    //Does not have fishing pole equiped. | 主手未装备鱼竿
    if (!mhItem || mhItem->GetProto()->Class != ITEM_CLASS_WEAPON || mhItem->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_FISHING_POLE)
        return false;

    if (bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
    {
        std::string spellName = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL)->m_spellInfo->SpellName[0];
        if (spellName.find("Fishing") == 0)
            return false;
    }

    return true;
}


