
#include "playerbot/playerbot.h"
#include "UpdateGearAction.h"
#include "playerbot/RandomPlayerbotMgr.h"
#include "playerbot/AiFactory.h"
#include <set>

using namespace ai;

/// 构造函数：初始化自动更新装备动作
UpdateGearAction::UpdateGearAction(PlayerbotAI* ai): Action(ai, "update gear")
{
    enchants.clear();
}

/// 执行动作主逻辑（自动更新装备动作）
bool UpdateGearAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    // Get bot class and spec (获取机器人职业与专精)
    const uint8 cls = bot->getClass();
    uint8 spec = AiFactory::GetPlayerSpecTab(bot);

    // Spec is overridden by bot role (专精选择已被机器人职责设定覆盖)
    if (cls == CLASS_WARRIOR)
    {
        if (ai->IsTank(bot))
        {
            spec = 2;
        }
    }
    else if (cls == CLASS_PALADIN)
    {
        if (ai->IsHeal(bot))
        {
            spec = 0;
        }
        else if (ai->IsTank(bot))
        {
            spec = 1;
        }
    }
    else if (cls == CLASS_PRIEST)
    {
        if (ai->IsHeal(bot))
        {
            spec = 1;
        }
    }
    else if (cls == CLASS_SHAMAN)
    {
        if (ai->IsHeal(bot))
        {
            spec = 2;
        }
    }
    else if (cls == CLASS_DRUID)
    {
        if (ai->IsHeal(bot))
        {
            spec = 2;
        }
        else if (ai->IsTank(bot))
        {
            spec = 3;
        }
    }

    const uint8 avgProgressionLevel = GetMasterAverageProgressionLevel();

    // Get gear for the progression level (按当前进度等级获取对应装备)
    for (uint8 slot = 0; slot < SLOT_EMPTY; slot++)
    {
        // Get the master item phase for this slot (获取主人该装备槽位对应的装备阶段)
        const uint8 itemProgressionLevel = GetMasterItemProgressionLevel(slot, avgProgressionLevel);

        // Retrieve the desired item from the progression levels (从装备进度阶段表中获取目标装备)
        const int32 itemId = sPlayerbotAIConfig.gearProgressionSystemItems[itemProgressionLevel][cls][spec][slot];
        if (itemId >= 0)
        {
            const uint32 pItemId = (uint32)itemId;
            Item* oldItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
            if (oldItem)
            {
                // Ignore this item as it is already equipped (该物品已装备，跳过处理)
                if (oldItem->GetEntry() == pItemId)
                {
                    continue;
                }

                // Destroy the old item (销毁旧物品)
                bot->DestroyItem(oldItem->GetBagSlot(), oldItem->GetSlot(), true);
            }

            if (pItemId > 0)
            {
                // Try to equip and enchant the item (尝试穿戴该物品并为其附魔)
                uint16 eDest;
                if (RandomPlayerbotMgr::CanEquipUnseenItem(bot, slot, eDest, pItemId) == EQUIP_ERR_OK)
                {
                    Item* pItem = bot->EquipNewItem(eDest, pItemId, true);
                    if (pItem)
                    {
                        pItem->SetOwnerGuid(bot->GetObjectGuid());
                        EnchantItem(pItem);
                    }
                }
                else
                {
                    std::ostringstream ss;
                    ss << "Failed to equip item " << std::to_string(pItemId) << " specified in AiPlayerbot.GearProgressionSystem." << std::to_string(itemProgressionLevel) << "." << std::to_string(cls) << "." << std::to_string(spec) << "." << std::to_string(slot);
                    ai->TellError(requester, ss.str());
                }
            }
        }
        else
        {
            // -1 表示未配置该槽位，仅对每个 (phase, cls, spec, slot) 组合报告一次缺失，防止每个机器人重复刷屏
            static std::set<uint32> reportedMissing;
            uint32 const key = ((((uint32)itemProgressionLevel * MAX_CLASSES + (uint32)cls) * 4 + (uint32)spec) * SLOT_EMPTY) + (uint32)slot;
            if (reportedMissing.insert(key).second)
            {
                std::ostringstream ss;
                ss << "Missing configuration for AiPlayerbot.GearProgressionSystem." << std::to_string(itemProgressionLevel) << "." << std::to_string(cls) << "." << std::to_string(spec) << "." << std::to_string(slot);
                ai->TellError(requester, ss.str());
            }
        }

    }

    return true;
}

/// 判断当前状态下该动作是否可用/有效（自动更新装备动作）
bool UpdateGearAction::isUseful()
{
    if (sPlayerbotAIConfig.gearProgressionSystemEnabled)
    {
        // Only for max level random bots that are playing with a real player (仅适用于与真实玩家同玩的满级随机机器人)
        Player* master = GetMaster();
        if (master && master->isRealPlayer() && bot->IsInGroup(master) && sRandomPlayerbotMgr.IsRandomBot(bot))
        {
            return bot->GetLevel() >= DEFAULT_MAX_LEVEL;
        }
    }

    return false;
}

/// 获取机器人当前等级对应的装备进度阶段
uint8 UpdateGearAction::GetProgressionLevel(uint32 itemLevel)
{
    uint8 itemProgressionLevel = 0;
    for (uint8 progressionLevel = 1; progressionLevel < MAX_GEAR_PROGRESSION_LEVEL; progressionLevel++)
    {
        const uint32 minIlvl = sPlayerbotAIConfig.gearProgressionSystemItemLevels[progressionLevel][0];
        const uint32 maxIlvl = sPlayerbotAIConfig.gearProgressionSystemItemLevels[progressionLevel][1];
        if (itemLevel >= minIlvl && itemLevel < maxIlvl)
        {
            itemProgressionLevel = progressionLevel;
            break;
        }
    }

    return itemProgressionLevel;
}

/// 获取主人全身装备的平均装等或进度等级
uint8 UpdateGearAction::GetMasterAverageProgressionLevel()
{
    return GetProgressionLevel(ai->GetEquipGearScore(ai->GetMaster(), false, false));
}

/// 获取主人指定槽位装备的进度等级
uint8 UpdateGearAction::GetMasterItemProgressionLevel(uint8 slot, uint8 avgProgressionLevel)
{
    // If checking weapons or ranged weapons use the average item lvl (检查主副手或远程武器时使用平均装等)
    if (slot == EQUIPMENT_SLOT_MAINHAND ||
        slot == EQUIPMENT_SLOT_OFFHAND || 
        slot == EQUIPMENT_SLOT_RANGED || 
        slot == EQUIPMENT_SLOT_TRINKET1 ||
        slot == EQUIPMENT_SLOT_TRINKET2 ||
        slot == EQUIPMENT_SLOT_BODY ||
        slot == EQUIPMENT_SLOT_TABARD)
    {
        return avgProgressionLevel;
    }
    else
    {
        uint32 itemLevel = 0;
        const Item* item = GetMaster()->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (item)
        {
            itemLevel = item->GetProto()->ItemLevel;
        }

        uint8 itemProgressionLevel = GetProgressionLevel(itemLevel);

        /*
        // TO DO: Check if a player has a item with low item lvl in purpose even if he is on a different progression level
        // Use average progression level if the item progression level is lower than the average progression level
        if (itemProgressionLevel < averageProgressionLevel)
        {
            itemProgressionLevel = averageProgressionLevel;
        }
        */

        return itemProgressionLevel;
    }
}

/// 为指定装备或背包物品施放附魔配方
void UpdateGearAction::EnchantItem(Item* item)
{
    if (item)
    {
        int tab = AiFactory::GetPlayerSpecTab(bot);
        uint32 tempId = uint32((uint32)bot->getClass() * (uint32)10);
        uint8 spec = tempId += (uint32)tab;

        if (enchants.empty())
        {
            auto result = WorldDatabase.PQuery("SELECT class, spec, spellid, slotid FROM ai_playerbot_enchants");
            if (result)
            {
                do
                {
                    Field* fields = result->Fetch();

                    EnchantTemplate pEnchant;
                    pEnchant.ClassId = fields[0].GetUInt8();
                    pEnchant.SpecId = fields[1].GetUInt8();
                    pEnchant.SpellId = fields[2].GetUInt32();
                    pEnchant.SlotId = fields[3].GetUInt8();
                    enchants.push_back(pEnchant);
                } 
                while (result->NextRow());
            }
        }

        for (const auto& enchant : enchants)
        {
            if (enchant.ClassId == bot->getClass() && enchant.SpecId == spec)
            {
                ai->EnchantItemT(enchant.SpellId, enchant.SlotId, item);
            }
        }
    }
}
