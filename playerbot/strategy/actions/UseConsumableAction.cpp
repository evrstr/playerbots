#include "playerbot/playerbot.h"
#include "UseConsumableAction.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/AiFactory.h"

using namespace ai;

// Flasks vanilla (经典旧世合剂)
const std::vector<uint32> UseConsumableAction::knownFlaskAuras = {
    17626,  // Flask of the Titans (泰坦合剂)
    17627,  // Flask of Distilled Wisdom (精炼智慧合剂)
    17628,  // Flask of Supreme Power (超级能量合剂)
    17629,  // Flask of Chromatic Resistance (多重抗性合剂)
    17624,  // Flask of Petrification (化石合剂)
};

// Food buffs vanilla (经典旧世食物增益)
const std::vector<uint32> UseConsumableAction::knownFoodBuffAuras = {
    18230,  // Grilled Squid (烤鱿鱼)
    25660,  // Dirge's Kickin' Chimaerok Chops (迪尔格的超美味奇美拉肉片)
    24800,  // Smoked Desert Dumplings (沙漠肉丸)
    18233,  // Nightfin Soup (夜鳞鱼汤)
    22731,  // Runn Tum Tuber Surprise (洛恩塔姆薯块)
    18140,  // Blessed Sunfruit Juice (神圣太阳果汁)
    18124,  // Blessed Sunfruit (神圣太阳果)
    18191,  // Increased Stamina (耐力提升)
};

const std::vector<uint32> UseConsumableAction::alcoholItemIds = {
    21151,
};

// Never use these items (绝不使用这些物品)
const std::vector<uint32> UseConsumableAction::excludedItemIds = {
    13455,  // Greater Stoneshield Potion (强效石盾药水)
    13461,  // Mighty Rage Potion (强效怒气药水)
    5634,   // Free Action Potion (自由行动药水)
    13457,  // Greater Fire Protection Potion (强效火焰防护药水)
    13456,  // Greater Frost Protection Potion (强效冰霜防护药水)
    13460,  // Greater Holy Protection Potion (强效神圣防护药水)
    13458,  // Greater Nature Protection Potion (强效自然防护药水)
    13459,  // Greater Shadow Protection Potion (强效暗影防护药水)
    13462,  // Greater Arcane Protection Potion (强效奥术防护药水)
};

/// 判断物品是否为元素防护药水类消耗品
bool UseConsumableAction::IsProtectionConsumable(const ItemPrototype* proto) const
{
    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        uint32 spellId = proto->Spells[i].SpellId;
        if (!spellId)
            continue;

        const SpellEntry* spellInfo = sServerFacade.LookupSpellInfo(spellId);
        if (!spellInfo)
            continue;

        for (int j = 0; j < 3; ++j)
        {
            if (spellInfo->EffectApplyAuraName[j] == SPELL_AURA_SCHOOL_ABSORB)
                return true;
        }

        bool hasResistance = false;
        bool hasOtherBuff = false;
        for (int j = 0; j < 3; ++j)
        {
            if (spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_RESISTANCE)
                hasResistance = true;
            else if (spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_STAT ||
                spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_ATTACK_POWER ||
                spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_DAMAGE_DONE ||
                spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_HIT_CHANCE ||
                spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_CRIT_PERCENT ||
                spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_POWER_REGEN ||
                spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_HEALING_DONE)
                hasOtherBuff = true;
        }

        if (hasResistance && !hasOtherBuff)
            return true;
    }
    return false;
}

/// 判断物品是否属于共享药水冷却的药水类消耗品
bool UseConsumableAction::IsPotionLike(const ItemPrototype* proto) const
{
    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        uint32 spellId = proto->Spells[i].SpellId;
        if (!spellId)
            continue;

        if (proto->Spells[i].SpellCategory == 4)
            return true;

        const SpellEntry* spellInfo = sServerFacade.LookupSpellInfo(spellId);
        if (spellInfo && spellInfo->Category == 4)
            return true;
    }
    return false;
}

/// 判断物品原型是否为恢复生命或法力的食物/饮水
bool UseConsumableAction::IsFoodOrDrink(const ItemPrototype* proto) const
{
    if (proto->Class != ITEM_CLASS_CONSUMABLE)
        return false;

    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        if (proto->Spells[i].SpellId &&
            (proto->Spells[i].SpellCategory == 11 || proto->Spells[i].SpellCategory == 59))
            return true;
    }
    return false;
}

/// 判断法术是否为提供基础属性加成的增益法术
bool UseConsumableAction::IsStatBuffSpell(uint32 spellId) const
{
    const SpellEntry* spellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (!spellInfo)
        return false;

    for (int j = 0; j < 3; ++j)
    {
        if (spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_STAT ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_ATTACK_POWER ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_DAMAGE_DONE ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_HIT_CHANCE ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_CRIT_PERCENT ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_POWER_REGEN ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_HEALING_DONE ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_RESISTANCE)
        {
            if (spellInfo->SpellName[0])
            {
                std::string name = spellInfo->SpellName[0];
                if (name == "Food" || name == "Drink")
                    continue;
            }
            return true;
        }

        if (spellInfo->EffectTriggerSpell[j])
        {
            const SpellEntry* triggered = sServerFacade.LookupSpellInfo(spellInfo->EffectTriggerSpell[j]);
            if (triggered)
            {
                if (triggered->SpellName[0])
                {
                    std::string tname = triggered->SpellName[0];
                    if (tname == "Food" || tname == "Drink")
                        continue;
                }

                for (int k = 0; k < 3; ++k)
                {
                    if (triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_STAT ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_ATTACK_POWER ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_DAMAGE_DONE ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_HIT_CHANCE ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_CRIT_PERCENT ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_POWER_REGEN ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_HEALING_DONE ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_RESISTANCE)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

/// 将增益法术 ID 解析为其实际生效的光环 Spell ID
uint32 UseConsumableAction::ResolveBuffAuraSpellId(uint32 spellId) const
{
    const SpellEntry* spellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (!spellInfo)
        return spellId;

    for (int j = 0; j < 3; ++j)
    {
        if (spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_STAT ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_ATTACK_POWER ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_DAMAGE_DONE ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_HIT_CHANCE ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_CRIT_PERCENT ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_POWER_REGEN ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_HEALING_DONE ||
            spellInfo->EffectApplyAuraName[j] == SPELL_AURA_MOD_RESISTANCE)
        {
            return spellId;
        }

        if (spellInfo->EffectTriggerSpell[j])
        {
            const SpellEntry* triggered = sServerFacade.LookupSpellInfo(spellInfo->EffectTriggerSpell[j]);
            if (triggered)
            {
                for (int k = 0; k < 3; ++k)
                {
                    if (triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_STAT ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_ATTACK_POWER ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_DAMAGE_DONE ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_HIT_CHANCE ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_CRIT_PERCENT ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_POWER_REGEN ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_HEALING_DONE ||
                        triggered->EffectApplyAuraName[k] == SPELL_AURA_MOD_RESISTANCE)
                    {
                        return spellInfo->EffectTriggerSpell[j];
                    }
                }
            }
        }
    }

    return spellId;
}

/// 收集给定技能或消耗品可能施加的所有光环 Spell ID
void UseConsumableAction::CollectPossibleAuraIds(uint32 spellId, std::vector<uint32>& outIds) const
{
    outIds.push_back(spellId);

    const SpellEntry* spellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (!spellInfo)
        return;

    for (int j = 0; j < 3; ++j)
    {
        if (spellInfo->EffectTriggerSpell[j] && spellInfo->EffectTriggerSpell[j] != spellId)
            outIds.push_back(spellInfo->EffectTriggerSpell[j]);
    }
}

/// 将背包物品分类为生命药水、法力药水、食物、绷带等消耗品类型
bool UseConsumableAction::ClassifyConsumable(const ItemPrototype* proto, ConsumableType& outType, uint32& outSpellId) const
{
    if (!proto || proto->Class != ITEM_CLASS_CONSUMABLE)
        return false;

    if (proto->SubClass == ITEM_SUBCLASS_POTION)
        return false;

    for (uint32 id : excludedItemIds)
    {
        if (proto->ItemId == id)
            return false;
    }

    for (uint32 id : alcoholItemIds)
    {
        if (proto->ItemId == id)
        {
            for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
            {
                if (proto->Spells[i].SpellId)
                {
                    outSpellId = proto->Spells[i].SpellId;
                    outType = ConsumableType::Alcohol;
                    return true;
                }
            }
            return false;
        }
    }

    if (proto->SubClass == ITEM_SUBCLASS_FLASK)
    {
        bool isRealFlask = false;
        uint32 firstSpellId = 0;
        for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            uint32 spellId = proto->Spells[i].SpellId;
            if (!spellId)
                continue;

            if (!firstSpellId)
                firstSpellId = spellId;

            std::vector<uint32> possibleAuras;
            CollectPossibleAuraIds(spellId, possibleAuras);
            for (uint32 auraId : possibleAuras)
            {
                for (uint32 flaskAura : knownFlaskAuras)
                {
                    if (auraId == flaskAura)
                    {
                        isRealFlask = true;
                        break;
                    }
                }
                if (isRealFlask)
                    break;
            }
            if (isRealFlask)
                break;
        }

        if (!firstSpellId)
            return false;

        if (isRealFlask)
        {
            outSpellId = firstSpellId;
            outType = ConsumableType::Flask;
            return true;
        }

        if (IsPotionLike(proto))
            return false;

        if (IsProtectionConsumable(proto))
            return false;

        outSpellId = firstSpellId;
        outType = ConsumableType::Elixir;
        return true;
    }

    if (proto->SubClass == ITEM_SUBCLASS_ELIXIR)
    {
        if (IsProtectionConsumable(proto))
            return false;

        for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            uint32 spellId = proto->Spells[i].SpellId;
            if (!spellId)
                continue;

            outSpellId = spellId;
            outType = ConsumableType::Elixir;
            return true;
        }
        return false;
    }

    if (proto->SubClass == ITEM_SUBCLASS_FOOD ||
        proto->SubClass == ITEM_SUBCLASS_CONSUMABLE ||
        proto->SubClass == ITEM_SUBCLASS_CONSUMABLE_OTHER)
    {
        if (IsProtectionConsumable(proto))
            return false;

        if (IsPotionLike(proto))
            return false;

        for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            uint32 spellId = proto->Spells[i].SpellId;
            if (!spellId)
                continue;

            const SpellEntry* spellInfo = sServerFacade.LookupSpellInfo(spellId);
            if (!spellInfo)
                continue;

            if (proto->Spells[i].SpellCategory == 11 || proto->Spells[i].SpellCategory == 59)
            {
                if (IsStatBuffSpell(spellId))
                {
                    outSpellId = ResolveBuffAuraSpellId(spellId);
                    outType = ConsumableType::FoodBuff;
                    return true;
                }
                continue;
            }

            if (IsStatBuffSpell(spellId))
            {
                outSpellId = ResolveBuffAuraSpellId(spellId);
                outType = ConsumableType::FoodBuff;
                return true;
            }
        }
        return false;
    }

    if (proto->SubClass == ITEM_SUBCLASS_SCROLL)
    {
        for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            if (proto->Spells[i].SpellId)
            {
                outSpellId = proto->Spells[i].SpellId;
                outType = ConsumableType::Scroll;
                return true;
            }
        }
        return false;
    }

    return false;
}

/// 检查机器人当前是否已拥有合剂类持续增益效果
bool UseConsumableAction::HasActiveFlask() const
{
    for (uint32 id : knownFlaskAuras)
        if (ai->HasAura(id, bot))
            return true;
    return false;
}

/// 检查机器人当前是否已拥有进食增益（如充分进食）
bool UseConsumableAction::HasActiveFoodBuff() const
{
    for (uint32 id : knownFoodBuffAuras)
        if (ai->HasAura(id, bot))
            return true;

    // Well-fed (充分进食)
    if (ai->HasAura(19705, bot))
        return true;

    if (ai->HasAura("well fed", bot))
        return true;

    if (bot->IsNonMeleeSpellCasted(false, false, true))
        return true;

    return false;
}

/// 检查目标是否已存在任一候选增益光环
bool UseConsumableAction::HasAnyCandidateAura(const ConsumableCandidate& candidate) const
{
    std::vector<uint32> auraIds;
    CollectPossibleAuraIds(candidate.spellId, auraIds);

    const ItemPrototype* proto = candidate.item->GetProto();
    if (proto)
    {
        for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            uint32 itemSpellId = proto->Spells[i].SpellId;
            if (itemSpellId)
            {
                CollectPossibleAuraIds(itemSpellId, auraIds);
            }
        }
    }

    for (uint32 id : auraIds)
    {
        if (ai->HasAura(id, bot))
            return true;
    }
    return false;
}

/// 根据天赋与策略确定机器人的战斗角色定位（坦克/治疗/近战/法系）
BotConsumableRole UseConsumableAction::GetBotRole() const
{
    const uint8 cls = bot->getClass();
    const int tab = AiFactory::GetPlayerSpecTab(bot);

    switch (cls)
    {
        // --- Warrior ----------------------------------------------------------- (战士相关)
    case CLASS_WARRIOR:
        if (tab == 2)                           // Protection (防护)
            return BotConsumableRole::Tank;
        return BotConsumableRole::MeleeDps;     // Arms / Fury (武器 / 狂怒)

        // --- Paladin ----------------------------------------------------------- (圣骑士相关)
    case CLASS_PALADIN:
        if (tab == 0)                           // Holy (神圣)
            return BotConsumableRole::Healer;
        if (tab == 1)                           // Protection (防护)
            return BotConsumableRole::Tank;
        return BotConsumableRole::MeleeDps;     // Retribution (惩戒)

        // --- Hunter ------------------------------------------------------------ (猎人相关)
    case CLASS_HUNTER:
        return BotConsumableRole::RangedPhysDps; // All specs (全专精)

        // --- Rogue ------------------------------------------------------------- (潜行者相关)
    case CLASS_ROGUE:
        return BotConsumableRole::MeleeDps;     // All specs (全专精)

        // --- Priest ------------------------------------------------------------ (牧师相关)
    case CLASS_PRIEST:
        if (tab == 2)                           // Shadow (暗影)
            return BotConsumableRole::CasterDps;
        return BotConsumableRole::Healer;       // Discipline / Holy (戒律 / 神圣)

        // --- Shaman ------------------------------------------------------------ (萨满祭司相关)
    case CLASS_SHAMAN:
        if (tab == 0)                           // Elemental (元素)
            return BotConsumableRole::CasterDps;
        if (tab == 1)                           // Enhancement (增强)
            return BotConsumableRole::MeleeDps;
        return BotConsumableRole::Healer;       // Restoration (恢复)

        // --- Mage -------------------------------------------------------------- (法师相关)
    case CLASS_MAGE:
        return BotConsumableRole::CasterDps;    // All specs (全专精)

        // --- Warlock ----------------------------------------------------------- (术士相关)
    case CLASS_WARLOCK:
        return BotConsumableRole::CasterDps;    // All specs (全专精)

        // --- Druid ------------------------------------------------------------- (德鲁伊相关)
    case CLASS_DRUID:
        if (tab == 0)                           // Balance (平衡)
            return BotConsumableRole::CasterDps;
        if (tab == 1)                           // Feral (野性战斗)
        {
            // Thick Hide / feral tank talents → tank; otherwise melee DPS (若点出厚皮或熊坦天赋则判定为坦克；否则判定为近战输出)
            if (ai->IsTank(bot))
                return BotConsumableRole::Tank;
            return BotConsumableRole::MeleeDps;
        }
        return BotConsumableRole::Healer;       // Restoration (恢复)

    default:
        return BotConsumableRole::MeleeDps;
    }
}

/// 根据机器人职业定位计算各属性（力量/敏捷/耐力/智力/精神等）权重
float UseConsumableAction::GetStatWeight(uint32 statType) const
{
    const BotConsumableRole role = GetBotRole();

    //                              STR   AGI   STA   INT   SPI (力量  敏捷  耐力  智力  精神)
    // MeleeDps  — wants str/agi  1.0   1.0   0.3   0.1   0.05 (近战输出 — 侧重力量/敏捷权重)
    // RangedPhysDps — agi focus  0.1   1.0   0.3   0.3   0.05 (远程物理输出 — 侧重敏捷权重)
    // CasterDps — int/sp         0.05  0.05  0.3   1.0   0.4 (法系输出 — 侧重智力/法伤权重)
    // Healer    — int/spi/+heal  0.05  0.05  0.3   1.0   0.6 (治疗定位 — 侧重智力/精神/治疗加成权重)
    // Tank      — sta/str/agi    0.6   0.8   1.0   0.1   0.05 (坦克定位 — 侧重耐力/力量/敏捷权重)

    switch (statType)
    {
    case 0: // Strength (力量)
        switch (role)
        {
        case BotConsumableRole::MeleeDps:       return 1.0f;
        case BotConsumableRole::RangedPhysDps:  return 0.1f;
        case BotConsumableRole::CasterDps:      return 0.05f;
        case BotConsumableRole::Healer:         return 0.05f;
        case BotConsumableRole::Tank:           return 0.6f;
        }
        break;

    case 1: // Agility (敏捷)
        switch (role)
        {
        case BotConsumableRole::MeleeDps:       return 1.0f;
        case BotConsumableRole::RangedPhysDps:  return 1.0f;
        case BotConsumableRole::CasterDps:      return 0.05f;
        case BotConsumableRole::Healer:         return 0.05f;
        case BotConsumableRole::Tank:           return 0.8f;
        }
        break;

    case 2: // Stamina (耐力)
        switch (role)
        {
        case BotConsumableRole::MeleeDps:       return 0.3f;
        case BotConsumableRole::RangedPhysDps:  return 0.3f;
        case BotConsumableRole::CasterDps:      return 0.3f;
        case BotConsumableRole::Healer:         return 0.3f;
        case BotConsumableRole::Tank:           return 1.0f;
        }
        break;

    case 3: // Intellect (智力)
        switch (role)
        {
        case BotConsumableRole::MeleeDps:       return 0.1f;
        case BotConsumableRole::RangedPhysDps:  return 0.3f;
        case BotConsumableRole::CasterDps:      return 1.0f;
        case BotConsumableRole::Healer:         return 1.0f;
        case BotConsumableRole::Tank:           return 0.1f;
        }
        break;

    case 4: // Spirit (精神)
        switch (role)
        {
        case BotConsumableRole::MeleeDps:       return 0.05f;
        case BotConsumableRole::RangedPhysDps:  return 0.05f;
        case BotConsumableRole::CasterDps:      return 0.4f;
        case BotConsumableRole::Healer:         return 0.6f;
        case BotConsumableRole::Tank:           return 0.05f;
        }
        break;
    }

    return 0.1f;
}

/// 根据职业属性权重为技能或装备附带属性评分
float UseConsumableAction::ScoreSpellStats(uint32 spellId) const
{
    const SpellEntry* spellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (!spellInfo)
        return 0.0f;

    const BotConsumableRole role = GetBotRole();
    float score = 0.0f;

    for (int i = 0; i < 3; ++i)
    {
        float amount = (float)spellInfo->EffectBasePoints[i];
        if (amount <= 0)
            continue;

        switch (spellInfo->EffectApplyAuraName[i])
        {
        case SPELL_AURA_MOD_STAT:
        {
            int32 stat = spellInfo->EffectMiscValue[i];
            if (stat == -1) // all stats (全属性)
            {
                for (uint32 s = 0; s < 5; ++s)
                    score += amount * GetStatWeight(s);
            }
            else if (stat >= 0 && stat <= 4)
            {
                score += amount * GetStatWeight((uint32)stat);
            }
            break;
        }
        case SPELL_AURA_MOD_ATTACK_POWER:
        {
            float w;
            switch (role)
            {
            case BotConsumableRole::MeleeDps:       w = 1.0f;  break;
            case BotConsumableRole::RangedPhysDps:  w = 0.8f;  break;
            case BotConsumableRole::Tank:           w = 0.5f;  break;
            default:                                w = 0.05f; break;
            }
            score += amount * w;
            break;
        }
        case SPELL_AURA_MOD_DAMAGE_DONE:
        {
            float w;
            switch (role)
            {
            case BotConsumableRole::CasterDps:      w = 1.0f;  break;
            case BotConsumableRole::Healer:         w = 0.3f;  break;
            default:                                w = 0.1f;  break;
            }
            score += amount * w;
            break;
        }
        case SPELL_AURA_MOD_HIT_CHANCE:
        case SPELL_AURA_MOD_CRIT_PERCENT:
        {
            score += amount * 10.0f;
            break;
        }
        case SPELL_AURA_MOD_HEALING_DONE:
        {
            float w = (role == BotConsumableRole::Healer) ? 1.0f : 0.05f;
            score += amount * w;
            break;
        }
        case SPELL_AURA_MOD_POWER_REGEN:
        {
            float w;
            switch (role)
            {
            case BotConsumableRole::Healer:         w = 3.0f; break;
            case BotConsumableRole::CasterDps:      w = 2.0f; break;
            default:                                w = 0.5f; break;
            }
            score += amount * w;
            break;
        }
        case SPELL_AURA_MOD_RESISTANCE:
        {
            score += amount * 0.2f;
            break;
        }
        default:
            score += amount * 0.1f;
            break;
        }
    }

    return score;
}

/// 按角色定位、恢复量与冷却效率为消耗品候选项评分
float UseConsumableAction::ScoreCandidate(const ConsumableCandidate& candidate) const
{
    float base = ScoreSpellStats(candidate.spellId);

    // Priority: Flask -> Elixir -> Scroll -> Food -> Alcohol
    switch (candidate.type)
    {
    case ConsumableType::Flask:    base += 1000.0f; break;
    case ConsumableType::Elixir:   base += 500.0f;  break;
    case ConsumableType::Scroll:   base += 300.0f;  break;
    case ConsumableType::FoodBuff: base += 200.0f;  break;
    case ConsumableType::Alcohol:  base += 100.0f;  break;
    default: break;
    }

    return base;
}

/// 扫描背包收集所有符合条件的可用消耗品候选列表
std::vector<ConsumableCandidate> UseConsumableAction::CollectCandidates()
{
    std::vector<ConsumableCandidate> results;

    for (int bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        Bag* pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (!pBag)
            continue;

        for (uint32 slot = 0; slot < pBag->GetBagSize(); ++slot)
        {
            Item* item = bot->GetItemByPos(bag, slot);
            if (!item)
                continue;

            const ItemPrototype* proto = item->GetProto();
            if (!proto || proto->Class != ITEM_CLASS_CONSUMABLE)
                continue;

            if (bot->CanUseItem(proto) != EQUIP_ERR_OK)
                continue;

            ConsumableType type;
            uint32 spellId;
            if (!ClassifyConsumable(proto, type, spellId))
                continue;

            ConsumableCandidate c;
            c.item = item;
            c.spellId = spellId;
            c.type = type;
            c.score = 0.0f;
            results.push_back(c);
        }
    }

    for (uint32 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; ++slot)
    {
        Item* item = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!item)
            continue;

        const ItemPrototype* proto = item->GetProto();
        if (!proto || proto->Class != ITEM_CLASS_CONSUMABLE)
            continue;

        if (bot->CanUseItem(proto) != EQUIP_ERR_OK)
            continue;

        ConsumableType type;
        uint32 spellId;
        if (!ClassifyConsumable(proto, type, spellId))
            continue;

        ConsumableCandidate c;
        c.item = item;
        c.spellId = spellId;
        c.type = type;
        c.score = 0.0f;
        results.push_back(c);
    }

    return results;
}

/// 判断执行该动作的前置条件是否满足（智能使用消耗品动作）
bool UseConsumableAction::isPossible()
{
    return !bot->InBattleGround() && !bot->IsTaxiFlying();
}

/// 判断当前状态下该动作是否可用/有效（智能使用消耗品动作）
bool UseConsumableAction::isUseful()
{
    if (bot->IsInCombat())
        return false;

    if (ai->HasCheat(BotCheatMask::item))
        return false;

    if (bot->IsTaxiFlying() || bot->InBattleGround())
        return false;

    if (bot->GetLevel() < 5)
        return false;

    return true;
}

/// 执行动作主逻辑（智能使用消耗品动作）
bool UseConsumableAction::Execute(Event& event)
{
    selectedItemId = 0;

    if (bot->IsNonMeleeSpellCasted(false, false, true))
        return false;

    std::vector<ConsumableCandidate> candidates = CollectCandidates();
    if (candidates.empty())
        return false;

    for (auto& c : candidates)
        c.score = ScoreCandidate(c);

    std::sort(candidates.begin(), candidates.end(), [](const ConsumableCandidate& a, const ConsumableCandidate& b)
        {
            return a.score > b.score;
        });

    bool hasFlask = HasActiveFlask();
    bool hasFoodBuff = HasActiveFoodBuff();

    for (const auto& c : candidates)
    {
        if (HasAnyCandidateAura(c))
            continue;

        switch (c.type)
        {
        case ConsumableType::Flask:
        {
            if (hasFlask)
                continue;

            selectedItemId = c.item->GetProto()->ItemId;
            break;
        }
        case ConsumableType::Elixir:
        {
            selectedItemId = c.item->GetProto()->ItemId;
            break;
        }
        case ConsumableType::Alcohol:
        {
            selectedItemId = c.item->GetProto()->ItemId;
            break;
        }
        case ConsumableType::FoodBuff:
        {
            if (hasFoodBuff)
                continue;

            if (IsFoodOrDrink(c.item->GetProto()))
                ai->StopMoving();

            selectedItemId = c.item->GetProto()->ItemId;
            break;
        }
        case ConsumableType::Scroll:
        {
            selectedItemId = c.item->GetProto()->ItemId;
            break;
        }
        default:
            continue;
        }

        if (selectedItemId)
            break;
    }

    if (!selectedItemId)
        return false;

    return UseItemIdAction::Execute(event);
}
