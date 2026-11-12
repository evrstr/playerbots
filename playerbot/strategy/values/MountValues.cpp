// 策略值实现：MountValues（坐骑速度判定、地图可用性检查、骑术与商人筛选）
#include "MountValues.h"
#include "playerbot/ChatHelper.h"
#include "playerbot/strategy/AiObjectContext.h"
#include "BudgetValues.h"
#include "SharedValueContext.h"

using namespace ai;

// 根据法术光环计算坐骑提供的地面或飞行移速加成（未解锁飞行则返回 0）
uint32 MountValue::GetSpeed(uint32 spellId, bool canFly)
{
#ifdef MANGOSBOT_ZERO
    if (canFly)
        return 0;
#endif

    const SpellEntry* const spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);

    if (!spellInfo)
        return 0;

    switch (spellInfo->Id) //Aura's hard coded in spell.cpp | 以下法术的速度光环逻辑在核心 spell.cpp 中硬编码处理
    {
    case 783:  //travel form | 德鲁伊旅行形态
    case 2645: //ghost wolf    | 萨满幽魂之狼
        if(!canFly)
        return 39;
        break;
    case 33943: //flight form | 德鲁伊飞行形态
        if (canFly)
            return 59;
        break;
    case 40120: //swift flight form | 德鲁伊迅捷飞行形态
        if (canFly)
            return 279;
        break;
    case 26656: //Black AQ mount | 黑色其拉作战坦克
        if (!canFly)
            return 99;
    }

    bool isMount = false;
    for (int i = 0; i < 3; i++)
    {
        if (spellInfo->EffectApplyAuraName[i] == SPELL_AURA_MOUNTED)
        {
            isMount = true;
            break;
        }
    }

    if(!isMount)
        return 0;

#ifndef MANGOSBOT_ZERO
    //This part stops bots from mounting flying mounts when they can't fly. This should be tweaked if bots ever are able to normally ride flying mounts in the old-world. | 阻止机器人在无法飞行的地区误用飞行坐骑
    if (isMount && !canFly)
    {
        for (int i = 0; i < 3; i++)
        {
            if (spellInfo->EffectApplyAuraName[i] == SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED)
            {
                return 0;
            }
        }
    }
#endif

#ifdef MANGOSBOT_ZERO
    uint32 effect = SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED;
#else
    uint32 effect = canFly ? SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED : SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED; //If we can fly only look at flight speed. Normal mounts then don't get any speed. | 若允许飞行则仅检查飞行速度，地面坐骑此时不计飞行速度
#endif

    if (isMount)
    {
        for (int i = 0; i < 3; i++)
        {
            if (spellInfo->EffectApplyAuraName[i] == effect)
            {
                return spellInfo->EffectBasePoints[i];
            }
        }
    }

    return 0;
}

// 从坐骑物品原型中提取其召唤坐骑的法术 ID
uint32 MountValue::GetMountSpell(uint32 itemId)
{
    const ItemPrototype* proto = sObjectMgr.GetItemPrototype(itemId);

    if (!proto)
        return 0;

    uint32 speed = 0;
    for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
    {
        if (GetSpeed(proto->Spells[j].SpellId))
            return proto->Spells[j].SpellId;

        if (GetSpeed(proto->Spells[j].SpellId, true))
            return proto->Spells[j].SpellId;
    }

    return 0;
}

// 校验当前地图与区域（外域/诺森德/安其拉等）是否允许召唤该坐骑
bool MountValue::IsValidLocation(Player* bot)
{
    if (GetSpeed(true)) //Flying mount | 飞行坐骑需检测当前是否位于可飞行区域
    {
        if (bot->GetMapId() != 530 && bot->GetMapId() != 571)
            return false;

#ifdef MANGOSBOT_ONE
        uint32 zone, area;
        bot->GetZoneAndAreaId(zone, area);
        uint32 v_map = GetVirtualMapForMapAndZone(bot->GetMapId(), zone);
        MapEntry const* mapEntry = sMapStore.LookupEntry(v_map);
        if (!mapEntry || mapEntry->addon < 1 || !mapEntry->IsContinent())
            return false;
#endif
#ifdef MANGOSBOT_TWO
        uint32 zone, area;
        bot->GetZoneAndAreaId(zone, area);
        if (!bot->CanStartFlyInArea(bot->GetMapId(), zone, area, false))
            return false;
#endif
    }

    const SpellEntry* const spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);

    bool isAQ40Mounted = false;

    switch (spellInfo->Id)
    {
    case 25863:    // spell used by ingame item for Black Qiraji mount (legendary reward) | 黑色其拉共振水晶触发的坐骑法术（传说奖励）
    case 26655:    // spells also related to Black Qiraji mount but use/trigger unknown | 与黑色其拉坐骑相关的备用触发法术
    case 26656:
    case 31700:
        if (bot->GetMapId() == 531)
            isAQ40Mounted = true;
        break;
    case 25953:    // spells of the 4 regular AQ40 mounts | 4 种常规安其拉神殿内部其拉作战坦克法术
    case 26054:
    case 26055:
    case 26056:
        if (bot->GetMapId() == 531)
        {
            isAQ40Mounted = true;
            break;
        }
        else
            return false; //SPELL_FAILED_NOT_HERE; | 当前区域禁止使用该坐骑
    default:
        break;
    }

    // Ignore map check if spell have AreaId. AreaId already checked and this prevent special mount spells | 若法术绑定了特定 AreaId 则已通过区域检测，跳过常规地图检查
    if (bot->GetTypeId() == TYPEID_PLAYER &&
        !isAQ40Mounted &&   // [-ZERO] && !m_spellInfo->AreaId) | 跳过安其拉坐骑或专属区域坐骑的通用地图禁用检查
        !bot->GetMap()->IsMountAllowed())
    {
        return false;  //SPELL_FAILED_NO_MOUNTS_ALLOWED; | 该地图/副本禁止骑乘
    }

    if (bot->GetAreaId() == 35)
        return false; //SPELL_FAILED_NO_MOUNTS_ALLOWED; | 该区域禁止骑乘

    return true;
}

// 检查目标身上的坐骑速度光环，返回当前最高骑乘速度加成
uint32 CurrentMountSpeedValue::Calculate()
{
    Unit* unit = ai->GetUnit(AI_VALUE(ObjectGuid, getQualifier()));

    if (!unit)
        return 0;

    uint32 mountSpeed = 0;

    for (uint32 auraType = SPELL_AURA_BIND_SIGHT; auraType < TOTAL_AURAS; auraType++)
    {
        Unit::AuraList const& auras = unit->GetAurasByType((AuraType)auraType);

        if (auras.empty())
            continue;

        for (Unit::AuraList::const_iterator i = auras.begin(); i != auras.end(); ++i)
        {
            Aura* aura = *i;
            if (!aura)
                continue;

            SpellEntry const* auraSpell = aura->GetSpellProto();

            uint32 auraSpeed = MountValue::GetSpeed(auraSpell->Id);

            if (auraSpeed < mountSpeed)
                continue;

            mountSpeed = auraSpeed;
        }
    }

    return mountSpeed;
}

// 扫描全库物品与法术，建立完整的坐骑目录缓存
std::vector<MountValue> FullMountListValue::Calculate()
{
    std::vector<MountValue> mounts;

    for (uint32 id = 0; id < sItemStorage.GetMaxEntry(); ++id)
    {
        ItemPrototype const* pProto = sItemStorage.LookupEntry<ItemPrototype>(id);
        if (!pProto)
            continue;

        if (!MountValue::GetMountSpell(pProto->ItemId))
            continue;

        mounts.push_back(MountValue(pProto));

        GAI_VALUE2(std::list<int32>, "item vendor list", pProto->ItemId);
    }

    for (uint32 id = 0; id < sSpellTemplate.GetMaxEntry(); ++id)
    {
        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(id);
        if (!spellInfo)
            continue;

        if (!MountValue::IsMountSpell(spellInfo->Id))
            continue;

        mounts.push_back(MountValue(spellInfo->Id));
    }

    return mounts;
}

// 收集机器人背包内坐骑物品与法术书内已学坐骑法术
std::vector<MountValue> MountListValue::Calculate()
{
    std::vector<MountValue> mounts;

    for (auto& mount : AI_VALUE2(std::list<Item*>, "inventory items", "mount"))
        mounts.push_back(MountValue(mount));

    for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
        if (itr->second.state != PLAYERSPELL_REMOVED && !itr->second.disabled && !IsPassiveSpell(itr->first))
            if(MountValue::IsMountSpell(itr->first))
                mounts.push_back(MountValue(itr->first));

    return mounts;
}

// 遍历已拥有坐骑列表计算可达到的最大移速加成
uint32 MaxMountSpeedValue::Calculate()
{
    bool canFly = !qualifier.empty();

    std::vector<MountValue> mounts = AI_VALUE(std::vector<MountValue>, "mount list");

    uint32 maxSpeed = 0;

    for (auto& mount : mounts)
        maxSpeed = std::max(maxSpeed, mount.GetSpeed(canFly));

    return maxSpeed;
}

// 将可用坐骑及速度信息格式化为聊天可读字符串
std::string MountListValue::Format()
{
    std::ostringstream out; out << "{";
    for (auto& mount : this->Calculate())
    {
        std::string speed = std::to_string(mount.GetSpeed(false) + 1) + "%" + (mount.GetSpeed(true) ? ("/" + (std::to_string(mount.GetSpeed(true) + 1) + "%")) : "");

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(mount.GetSpellId());
        if (spellInfo && !spellInfo->SpellName[LOCALE_enUS])
            spellInfo = nullptr;

        out << (mount.IsItem() ? "(item)" : "(spell)") << (spellInfo ? chat->formatSpell(spellInfo) : std::string()) << "(" << speed << "),";
    }
    out << "}";
    return out.str();
}

// 结合角色等级与所属资料片状态计算对应的骑术技能需求阶段
uint32 MountSkillTypeValue::Calculate()
{
#ifdef MANGOSBOT_ZERO
    switch (bot->getRace())
    {
    case RACE_HUMAN:
        return SKILL_RIDING_HORSE;
    case RACE_ORC:
        return SKILL_RIDING_WOLF;
        break;
    case RACE_NIGHTELF:
        return SKILL_RIDING_TIGER;
        break;
    case RACE_DWARF:
        return SKILL_RIDING_RAM;
        break;
    case RACE_TROLL:
        return SKILL_RIDING_RAPTOR;
        break;
    case RACE_GNOME:
        return SKILL_RIDING_MECHANOSTRIDER;
        break;
    case RACE_UNDEAD:
        return SKILL_RIDING_UNDEAD_HORSE;
        break;
    case RACE_TAUREN:
        return SKILL_RIDING_KODO;
        break;
    default:
        return SKILL_RIDING;
        break;
    }
#else
    return SKILL_RIDING;
#endif
}

// 从全局坐骑列表中筛选机器人可装备升级且有商人出售的坐骑卖家
std::vector<int32> AvailableMountVendors::Calculate()
{
    std::vector<int32> mountVendors;
    std::vector<MountValue> mountList = GAI_VALUE(std::vector<MountValue>, "full mount list");
    
    for (auto& mount : mountList)
    {
        if (!mount.IsItem())
            continue;

        uint32 itemId = mount.GetItemProto()->ItemId;

        ItemUsage usage = AI_VALUE2_LAZY(ItemUsage, "item usage", itemId);

        if (usage != ItemUsage::ITEM_USAGE_EQUIP)
            continue;

        for (auto& vendor : GAI_VALUE2(std::list<int32>, "item vendor list", itemId))
            if(std::find(mountVendors.begin(), mountVendors.end(), vendor) == mountVendors.end())
                mountVendors.push_back(vendor);
    }

    return mountVendors;
}

// 判断金币预算是否足够学习下一级骑术
bool CanTrainMountValue::Calculate()
{
    if (bot->GetSkill(AI_VALUE(uint32, "mount skilltype"), true, true) >= bot->GetSkill(AI_VALUE(uint32, "mount skilltype"), true, true, true))
        return false;

    if (AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::mount) < AI_VALUE2(uint32, "total money needed for", (uint32)NeedMoneyFor::mount))
        return false;

    return true;
}

// 综合判断坐骑资金预算、商人可用性与技能等级是否满足购骑需求
bool CanBuyMountValue::Calculate()
{
#ifdef MANGOSBOT_ZERO
    uint8 minRidingLevel = 40;
#endif
#ifdef MANGOSBOT_ONE
    uint8 minRidingLevel = 30;
#endif
#ifdef MANGOSBOT_TWO
    uint8 minRidingLevel = 20;
#endif
    if (bot->GetLevel() < minRidingLevel)
        return false;

    if (!AI_VALUE(bool, "can buy"))
        return false;

    if (AI_VALUE2(uint32, "money needed for", (uint32)NeedMoneyFor::mount) == 0)
        return false;

    if (AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::mount) < AI_VALUE2(uint32, "total money needed for", (uint32)NeedMoneyFor::mount))
        return false;

    return true;
}