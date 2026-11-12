#include "playerbot/playerbot.h"
#include "ImbueAction.h"
#include "playerbot/PlayerbotAI.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

/// 执行动作主逻辑（磨刀石/平衡石武器附魔动作）
bool ImbueWithStoneAction::Execute(Event& event)
{
    Player* requester = event.getOwner();
    if (bot->IsInCombat() || bot->GetLevel() > 70)
        return false;

    // remove stealth (取消潜行状态)
    if (bot->HasAura(SPELL_AURA_MOD_STEALTH))
        bot->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

    // hp check (生命值检查)
    if (bot->getStandState() != UNIT_STAND_STATE_STAND)
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    bool allowMainhand = true;

#ifndef MANGOSBOT_TWO
    // Check if shaman +30 lvl (non-WOTLK) (检查是否为 30 级以上萨满（非 WLK 版本）)

    if (bot->getClass() == CLASS_SHAMAN && bot->GetLevel() > 30)
        allowMainhand = false;

    if (bot->GetGroup())
    {
        Group* group = bot->GetGroup();
        for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
        {
            Player* member = ref->getSource();
            if (!member || member == bot || !member->IsInWorld() || !group->SameSubGroup(bot, member))
                continue;

            if (member->getClass() == CLASS_SHAMAN && member->GetLevel() > 32)
            {
                allowMainhand = false;
                break;
            }
        }
    }
#endif

    // Mainhand (主手)
    if (allowMainhand)
    {
        Item* mainWeapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
        if (mainWeapon && mainWeapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0)
        {
            Item* stone = ai->FindStoneFor(mainWeapon);
            // Do not use Elemental Sharpening Stone outside instances (副本外不要使用元素磨刀石)
            if (stone && stone->GetProto())
            {
                if (stone->GetProto()->DisplayInfoID == ELEMENTAL_SHARPENING_DISPLAYID && bot->GetInstanceId() == 0)
                    stone = nullptr;
            }

            if (stone)
                return UseItem(requester, stone->GetEntry(), mainWeapon);
        }
    }

    // Offhand (副手)
    Item* secondaryWeapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
    if (secondaryWeapon && secondaryWeapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0)
    {
        Item* stone = ai->FindStoneFor(secondaryWeapon);
        // Do not use Elemental Sharpening Stone outside instances (副本外不要使用元素磨刀石)
        if (stone && stone->GetProto())
        {
            if (stone->GetProto()->DisplayInfoID == ELEMENTAL_SHARPENING_DISPLAYID && bot->GetInstanceId() == 0)
                stone = nullptr;
        }

        if (stone)
            return UseItem(requester, stone->GetEntry(), secondaryWeapon);
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（磨刀石/平衡石武器附魔动作）
bool ImbueWithStoneAction::isUseful()
{
    bool allowMainhand = true;

    if (bot->GetLevel() > 70)
        return false;

#ifndef MANGOSBOT_TWO
    // Deny mainhand stone use if bot is a Shaman over 30 or grouped with one over 32 (TBC/Vanilla only) (若机器人为 30 级以上萨满或队中有 32 级以上萨满（仅经典/TBC），禁止对主手使用磨刀石)
    if (bot->getClass() == CLASS_SHAMAN && bot->GetLevel() > 30)
        allowMainhand = false;

    if (bot->GetGroup())
    {
        Group* group = bot->GetGroup();
        for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
        {
            Player* member = ref->getSource();
            if (!member || member == bot || !member->IsInWorld() || !group->SameSubGroup(bot, member))
                continue;

            if (member->getClass() == CLASS_SHAMAN && member->GetLevel() > 32)
            {
                allowMainhand = false;
                break;
            }
        }
    }
#endif

    // Check Offhand always (始终检查副手武器)
    Item* secondaryWeapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
    if (secondaryWeapon && secondaryWeapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0)
    {
        Item* stone = ai->FindStoneFor(secondaryWeapon);
        if (stone && stone->GetProto())
        {
            if (stone->GetProto()->DisplayInfoID == ELEMENTAL_SHARPENING_DISPLAYID && bot->GetInstanceId() == 0)
                stone = nullptr;
        }

        if (stone)
            return true;
    }

    // Check mainhand only if allowed (仅在允许时检查主手武器)
    if (allowMainhand)
    {
        Item* mainWeapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
        if (mainWeapon && mainWeapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0)
        {
            Item* stone = ai->FindStoneFor(mainWeapon);
            if (stone && stone->GetProto())
            {
                if (stone->GetProto()->DisplayInfoID == ELEMENTAL_SHARPENING_DISPLAYID && bot->GetInstanceId() == 0)
                    stone = nullptr;
            }

            if (stone)
                return true;
        }
    }

    return false;
}

/// 执行动作主逻辑（巫师之油/法力之油武器附魔动作）
bool ImbueWithOilAction::Execute(Event& event)
{
    Player* requester = event.getOwner();
    if (bot->IsInCombat() || bot->GetLevel() > 70)
        return false;

    // remove stealth (取消潜行状态)
    if (bot->HasAura(SPELL_AURA_MOD_STEALTH))
        bot->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

    // hp check (生命值检查)
    if (bot->getStandState() != UNIT_STAND_STATE_STAND)
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    // Search and apply oil to weapons (查找武器油并涂抹到武器上)
    Item* weapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
    if (weapon && weapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0)
    {
        Item* oil = ai->FindOilFor(weapon);
        if (oil)
        {
            return UseItem(requester, oil->GetEntry(), weapon);
        }
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（巫师之油/法力之油武器附魔动作）
bool ImbueWithOilAction::isUseful()
{
    if (bot->GetLevel() > 70)
        return false;
    
    Item* weapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
    if (weapon && weapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0)
    {
        if (ai->FindOilFor(weapon))
        {
            return true;
        }
    }

    return false;
}

/// 执行动作主逻辑（紧急自保动作）
bool TryEmergencyAction::Execute(Event& event)
{
    // Do not use consumable if bot can heal self or is prehealing (若机器人可自我治疗或正在预治疗，则不使用消耗品)
    if (ai->IsHeal(bot) && (ai->GetManaPercent() > 10 || ai->HasStrategy("preheal", BotState::BOT_STATE_COMBAT)))
        return false;

    // If bot does not have aggro: use bandage instead of potion/stone/crystal (若机器人未建立仇恨：优先使用绷带而非药水/治疗石/水晶)
    if (!(AI_VALUE(uint8, "my attacker count") >= 1) && !bot->HasAura(11196)) // Recently bandaged (最近刚刚使用过绷带（存在新近绷带减益）)
    {
        Item* bandage = ai->FindBandage();
        if (bandage)
        {
            ai->ImbueItem(bandage, bot);
            SetDuration(sPlayerbotAIConfig.globalCoolDown);
            return true;
        }
    }

    // Else loop over the list of health consumable to pick one (否则遍历生命恢复消耗品列表挑选可用项)
    Item* healthItem = nullptr;
    for (uint8 i = 0; i < countof(uPriorizedHealingItemIds); ++i)
    {
        healthItem = ai->FindConsumable(uPriorizedHealingItemIds[i]);
        if (healthItem)
        {
            ai->ImbueItem(healthItem);
            return true;
        }
    }

    return false;
}
