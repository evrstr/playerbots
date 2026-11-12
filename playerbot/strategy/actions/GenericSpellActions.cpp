
#include "playerbot/playerbot.h"
#include "GenericActions.h"
#include "UseItemAction.h"

using namespace ai;

/// 构造函数：初始化施放法术基类动作
CastSpellAction::CastSpellAction(PlayerbotAI* ai, std::string spell)
: Action(ai, spell)
, range(ai->GetRange("spell"))
{
    SetSpellName(spell);

    float spellRange;
    if (ai->GetSpellRange(spell, &spellRange))
    {
        range = spellRange;
    }
}

/// 执行动作主逻辑（施放法术基类动作）
bool CastSpellAction::Execute(Event& event)
{
    bool executed = false;
    uint32 spellDuration = sPlayerbotAIConfig.globalCoolDown;
    if (spellName == "conjure food" || spellName == "conjure water")
    {
        uint32 castId = 0;
        for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
        {
            uint32 spellId = itr->first;

            const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
            if (!pSpellInfo)
                continue;

            std::string namepart = pSpellInfo->SpellName[0];
            strToLower(namepart);

            if (namepart.find(spellName) == std::string::npos)
                continue;

            if (pSpellInfo->Effect[0] != SPELL_EFFECT_CREATE_ITEM)
                continue;

            uint32 itemId = pSpellInfo->EffectItemType[0];
            ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
            if (!proto)
                continue;

            if (bot->CanUseItem(proto) != EQUIP_ERR_OK)
                continue;

            if (pSpellInfo->Id > castId)
                castId = pSpellInfo->Id;
        }

        executed = ai->CastSpell(castId, bot, nullptr, false, &spellDuration);
    }
    else
    {
        if (GetTargetName() == "current target" && (!bot->GetCurrentSpell(CURRENT_MELEE_SPELL) && !bot->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL)))
        {
            if (bot->getClass() == CLASS_HUNTER && spellName != "auto shot" && sServerFacade.GetDistance2d(bot, GetTarget()) > 5.0f)
                ai->CastSpell("auto shot", GetTarget());
        }

        executed = ai->CastSpell(spellName, GetTarget(), nullptr, false, &spellDuration);
    }

    if (executed)
    {
        if (ai->HasCheat(BotCheatMask::attackspeed))
            spellDuration = 1;

        SetDuration(spellDuration);
    }

    return executed;
}

/// 判断执行该动作的前置条件是否满足（施放法术基类动作）
bool CastSpellAction::isPossible()
{
    if (spellName == "mount")
    {
        if (!bot->IsMounted() && !bot->IsInCombat())
        {
            return true;
        }
        if (bot->IsInCombat())
        {
            ai->Unmount();
            return false;
        }
    }

    Unit* spellTarget = GetTarget();
    if (!spellTarget)
        return false;

    bool canReach = false;
    if (spellTarget == bot)
    {
        canReach = true;
    }
    else
    {
        float dist = bot->GetDistance(spellTarget, true, ai->IsRanged(bot) ? DIST_CALC_COMBAT_REACH : DIST_CALC_COMBAT_REACH_WITH_MELEE);
        if (range == ATTACK_DISTANCE) 
        {
            canReach = bot->CanReachWithMeleeAttack(spellTarget);
        }
        else 
        {
            canReach = dist <= (range + sPlayerbotAIConfig.contactDistance);
            if (!spellId)
                return false;

            const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
            if (!pSpellInfo)
                return false;

            if (range != ATTACK_DISTANCE && pSpellInfo->rangeIndex != SPELL_RANGE_IDX_COMBAT && pSpellInfo->rangeIndex != SPELL_RANGE_IDX_SELF_ONLY && pSpellInfo->rangeIndex != SPELL_RANGE_IDX_ANYWHERE)
            {
                float max_range, min_range;
                if (ai->GetSpellRange(GetSpellName(), &max_range, &min_range))
                {
                    canReach = dist < max_range && dist >= min_range;
                }
            }
        }
    }

    if(!canReach)
    {
        return false;
    }
    
    // Check if the spell can be casted (检查该法术当前是否可以施放)
    return ai->CanCastSpell(spellName, spellTarget, 0, nullptr, true);
}

/// 判断当前状态下该动作是否可用/有效（施放法术基类动作）
bool CastSpellAction::isUseful()
{
    if (ai->IsInVehicle() && !ai->IsInVehicle(false, false, true))
        return false;

    if(!AI_VALUE2(bool, "spell cast useful", spellName))
        return false;

    Unit* spellTarget = GetTarget();
    if (!spellTarget)
        return false;

    if (!spellTarget->IsInWorld() || spellTarget->GetMapId() != bot->GetMapId())
        return false;

    const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (pSpellInfo)
    {
        // check if the damage we'd take from damage shields is too harmful, only for melee spells (检查近战法术攻击反伤护盾目标时承受的反伤是否过高)
        if (range == ATTACK_DISTANCE)
        {
            std::set<Aura*> alreadyDone;
            Unit::AuraList const& vDamageShields = spellTarget->GetAurasByType(SPELL_AURA_DAMAGE_SHIELD);
            for (Unit::AuraList::const_iterator i = vDamageShields.begin(); i != vDamageShields.end();)
            {
                if (alreadyDone.find(*i) == alreadyDone.end())
                {
                    alreadyDone.insert(*i);
                    uint32 damage = (*i)->GetModifier()->m_amount;

                    // If the damage shield does at least 10% of our max hp on each hit we do, we shouldn't cast a melee spell (若反伤护盾每次反伤超过最大生命值的 10%，则不施放近战法术)
                    if (damage >= bot->GetMaxHealth() * 0.10f)
                    {
                        bot->AttackStop();
                        return false;
                    }

                    i = vDamageShields.begin();
                }
                else
                    ++i;
            }
        }

        // If target is more likely than not to reflect and our spell is reflectable, don't cast (若目标大概率具有法术反射且当前法术可被反射，则放弃施法)
        if (spellTarget->GetReflectChance(GetSpellSchoolMask(pSpellInfo)) > 50.0f && IsReflectableSpell(pSpellInfo))
            return false;
    }

    return true;
}

/// 获取执行本动作前需要优先执行的前置动作列表
NextAction** CastSpellAction::getPrerequisites()
{
    // Set the reach action as the cast spell prerequisite when needed (需要时将接近动作设为施法前置动作)
    const std::string reachAction = GetReachActionName();
    if (!reachAction.empty())
    {
        const std::string targetName = GetTargetName();

        // No need for a reach action when target is self (目标为自身时无需执行接近目标动作)
        if (targetName != "self target")
        {
            const std::string spellName = GetSpellName();
            const std::string targetQualifier = GetTargetQualifier();

            // Generate the reach action with qualifiers (生成附带限定符的接近目标动作)
            std::vector<std::string> qualifiers = { spellName, targetName };
            if (!targetQualifier.empty())
            {
                qualifiers.push_back(targetQualifier);
            }

            const std::string qualifiersStr = Qualified::MultiQualify(qualifiers, "::");
            return NextAction::merge(NextAction::array(0, new NextAction(reachAction + "::" + qualifiersStr), NULL), Action::getPrerequisites());
        }
    }

    return Action::getPrerequisites();
}

/// 设置动作关联的法术名称并解析对应的法术 ID
void CastSpellAction::SetSpellName(const std::string& name, std::string spellIDContextName /*= "spell id"*/, bool force)
{
    if (force || spellName != name)
    {
        spellName = name;
        spellId = ai->GetAiObjectContext()->GetValue<uint32>(spellIDContextName, name)->Get();

        float spellRange;
        if (ai->GetSpellRange(spellName, &spellRange))
        {
            range = spellRange;
        }
    }
}

/// 获取当前动作的目标单位（施放法术基类动作）
Unit* CastSpellAction::GetTarget()
{
    std::string targetName = GetTargetName();
    std::string targetNameQualifier = GetTargetQualifier();
    return targetNameQualifier.empty() ? ai->GetUnit(AI_VALUE(ObjectGuid, targetName)) : ai->GetUnit(AI_VALUE2(ObjectGuid, targetName, targetNameQualifier));
}

/// 判断执行该动作的前置条件是否满足（施放宠物法术动作）
bool CastPetSpellAction::isPossible()
{
    Unit* spellTarget = GetTarget();
    if (!spellTarget)
        return false;

    Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
    if (pet && ai->IsSafe(pet))
    {
        const uint32& spellId = GetSpellID();
        if (pet->HasSpell(spellId) && pet->IsSpellReady(spellId))
        {
            // Check if the pet is not too far from the owner (检查宠物与主人之间的距离是否未过远)
            if (bot->GetDistance(pet) <= sPlayerbotAIConfig.sightDistance)
            {
                bool canReach = false;
                const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
                if (pSpellInfo)
                {
                    const float dist = pet->GetDistance(spellTarget, true, DIST_CALC_COMBAT_REACH);
                    canReach = dist <= (range + sPlayerbotAIConfig.contactDistance);

                    if (pSpellInfo->rangeIndex != SPELL_RANGE_IDX_COMBAT && pSpellInfo->rangeIndex != SPELL_RANGE_IDX_SELF_ONLY && pSpellInfo->rangeIndex != SPELL_RANGE_IDX_ANYWHERE)
                    {
                        float max_range, min_range;
                        if (ai->GetSpellRange(GetSpellName(), &max_range, &min_range))
                        {
                            canReach = dist < max_range&& dist >= min_range;
                        }
                    }
                }

                if (canReach)
                {
                    return ai->CanCastSpell(spellId, spellTarget, 0, true);
                }
            }
        }
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（施放光环法术基类动作）
bool CastAuraSpellAction::isUseful()
{
    return CastSpellAction::isUseful() && !ai->HasAura(GetSpellName(), GetTarget(), false, isOwner);
}

/// 判断当前状态下该动作是否可用/有效（施放近战范围技能动作）
bool CastMeleeAoeSpellAction::isUseful()
{
    return CastSpellAction::isUseful() && sServerFacade.IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", GetTargetName()), radius);
}

/// 判断执行该动作的前置条件是否满足（施放物品附魔动作）
bool CastEnchantItemAction::isPossible()
{
    if (!CastSpellAction::isPossible())
        return false;

    return GetSpellID() && AI_VALUE2(Item*, "item for spell", GetSpellID());
}

/// 判断当前状态下该动作是否可用/有效（施放群体治疗法术动作）
bool CastAoeHealSpellAction::isUseful()
{
    return CastSpellAction::isUseful();
}

/// 判断当前状态下该动作是否可用/有效（对队友施放持续治疗动作）
bool HealHotPartyMemberAction::isUseful()
{
    return HealPartyMemberAction::isUseful() && !ai->HasAura(GetSpellName(), GetTarget());
}

/// 判断执行该动作的前置条件是否满足（施放载具技能基类动作）
bool CastVehicleSpellAction::isPossible()
{
    return ai->CanCastVehicleSpell(GetSpellID(), GetTarget());
}

/// 判断当前状态下该动作是否可用/有效（施放载具技能基类动作）
bool CastVehicleSpellAction::isUseful()
{
    return ai->IsInVehicle(false, true);
}

/// 执行动作主逻辑（施放载具技能基类动作）
bool CastVehicleSpellAction::Execute(Event& event)
{
    return ai->CastVehicleSpell(GetSpellID(), GetTarget(), speed, needTurn);
}

/// 判断执行该动作的前置条件是否满足（冰冻死亡箭载具技能动作）
bool CastFrozenDeathboltAction::isPossible()
{
    Unit* target = GetTarget();

    if (!target)
        return false;

    if (target->GetDistance(bot) > range)
        return false;

    return CastVehicleSpellAction::isPossible();
}

/// 判断当前状态下该动作是否可用/有效（施放战争践踏动作）
bool CastWarStompAction::isUseful()
{
    // ignore distance check in pvp or duel (PvP 或决斗期间忽略距离限制检查)
    if (!ai->HasStrategy("pvp", BotState::BOT_STATE_COMBAT) &&
        !ai->HasStrategy("duel", BotState::BOT_STATE_COMBAT))
    {
        Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
        if (target)
            return AI_VALUE2(float, "distance", "current target") <= 8.0f;
        return false;
    }

    return true;
}

/// 判断执行该动作的前置条件是否满足（吞噬人形生物载具技能动作）
bool CastDevourHumanoidAction::isPossible()
{
    Unit* target = GetTarget();

    if (!target)
        return false;

    if (target->GetDistance(bot) > range)
        return false;

    return CastVehicleSpellAction::isPossible();
}

/// 判断执行该动作的前置条件是否满足（施放远程射击/魔杖动作）
bool CastShootAction::isPossible()
{
    // Check if the bot has a ranged weapon equipped and has ammo (检查机器人是否装备了远程武器并携带弹药)
    UpdateWeaponInfo();
    if (rangedWeapon && !needsAmmo)
    {
        // Check if the target exist and it can be shot (检查目标是否存在且可被远程射击)
        Unit* target = GetTarget();
        if (target && sServerFacade.IsWithinLOSInMap(bot, target))
        {
            return CastSpellAction::isPossible();
        }
    }

    return false;
}

/// 执行动作主逻辑（施放远程射击/魔杖动作）
bool CastShootAction::Execute(Event& event)
{
    bool succeeded = false;

    UpdateWeaponInfo();
    if (rangedWeapon && !needsAmmo)
    {
        // Prevent calling the shoot spell when already active (自动射击已激活时避免重复施放射击法术)
        Spell* autoRepeatSpell = ai->GetBot()->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL);
        if (autoRepeatSpell && (autoRepeatSpell->m_spellInfo->Id == GetSpellID()))
        {
            succeeded = true;
        }
        else if (CastSpellAction::Execute(event))
        {
            succeeded = true;
        }

        if (succeeded)
        {
            SetDuration(weaponDelay);
        }
    }

    return succeeded;
}

/// 刷新并记录主副手武器及远程武器状态参数
void CastShootAction::UpdateWeaponInfo()
{
    // Check if we have a new ranged weapon equipped (检查是否刚刚装备了新的远程武器)
    const Item* equippedWeapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
    if (equippedWeapon)
    {
        if (equippedWeapon != rangedWeapon)
        {
            std::string spellName = "shoot";
            bool isRangedWeapon = false;

#ifdef MANGOSBOT_ZERO
            needsAmmo = true;
#endif

            const ItemPrototype* itemPrototype = equippedWeapon->GetProto();
            switch (itemPrototype->SubClass)
            {
                case ITEM_SUBCLASS_WEAPON_GUN:
                {
                    isRangedWeapon = true;
#ifdef MANGOSBOT_ZERO
                    spellName += " gun";
#endif
                    break;
                }
                case ITEM_SUBCLASS_WEAPON_BOW:
                {
                    isRangedWeapon = true;
#ifdef MANGOSBOT_ZERO
                    spellName += " bow";
#endif
                    break;
                }
                case ITEM_SUBCLASS_WEAPON_CROSSBOW:
                {
                    isRangedWeapon = true;
#ifdef MANGOSBOT_ZERO
                    spellName += " crossbow";
#endif
                    break;
                }
                case ITEM_SUBCLASS_WEAPON_WAND:
                {
                    isRangedWeapon = true;
#ifdef MANGOSBOT_ZERO
                    needsAmmo = false;
#endif
                    break;
                }
                case ITEM_SUBCLASS_WEAPON_THROWN:
                {
                    isRangedWeapon = true;
                    spellName = "throw";
                    break;
                }

                default: break;
            }

            // Set the new weapon parameters (更新记录新的武器参数)
            if (isRangedWeapon)
            {
                SetSpellName(spellName);
                rangedWeapon = equippedWeapon;
                weaponDelay = itemPrototype->Delay + sPlayerbotAIConfig.globalCoolDown;
            }
        }

        // Check the ammunition (检查远程弹药储备)
#ifdef MANGOSBOT_ZERO
        needsAmmo = (GetSpellName() != "shoot") ? (AI_VALUE2(uint32, "item count", "ammo") <= 0) : false;
#endif
    }
    else
    {
        rangedWeapon = nullptr;
    }
}

/// 判断当前状态下该动作是否可用/有效（移除自身增益动作）
bool RemoveBuffAction::isUseful()
{
    return ai->HasAura(name, bot);
}

/// 执行动作主逻辑（移除自身增益动作）
bool RemoveBuffAction::Execute(Event& event)
{
    ai->RemoveAura(name);
    return !ai->HasAura(name, bot);
}

/// 判断当前状态下该动作是否可用/有效（中断当前施法动作）
bool InterruptCurrentSpellAction::isUseful()
{
    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_CHANNELED_SPELL; type++)
    {
        Spell* currentSpell = bot->GetCurrentSpell((CurrentSpellTypes)type);
        if (currentSpell && currentSpell->CanBeInterrupted())
            return true;
    }
    return false;
}

/// 执行动作主逻辑（中断当前施法动作）
bool InterruptCurrentSpellAction::Execute(Event& event)
{
    bool interrupted = false;
    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_CHANNELED_SPELL; type++)
    {
        Spell* currentSpell = bot->GetCurrentSpell((CurrentSpellTypes)type);
        if (currentSpell && currentSpell->CanBeInterrupted())
        {
            bot->InterruptSpell((CurrentSpellTypes)type);
            ai->SpellInterrupted(currentSpell->m_spellInfo->Id);
            interrupted = true;
        }
    }
    return interrupted;
}

/// 获取当前动作的目标单位（对指定目标施法动作）
Unit* CastSpellTargetAction::GetTarget()
{
    // Check for assigned targets (检查是否已分配指定目标)
    const std::list<ObjectGuid>& possibleTargets = AI_VALUE(std::list<ObjectGuid>, targetsValue);
    if (!possibleTargets.empty())
    {
        for (const ObjectGuid& possibleTargetGuid : possibleTargets)
        {
            Unit* possibleTarget = ai->GetUnit(possibleTargetGuid);
            if (IsTargetValid(possibleTarget))
            {
                return possibleTarget;
            }
        }
    }
    else
    {
        // Check for the default target (检查默认目标)
        Unit* possibleTarget = CastSpellAction::GetTarget();
        if (IsTargetValid(possibleTarget))
        {
            return possibleTarget;
        }
    }

    return nullptr;
}

/// 检查目标单位是否存活、在视野内且满足攻击/施法合法性
bool CastSpellTargetAction::IsTargetValid(Unit* target)
{
    return target &&
           ai->IsSafe(target) &&
           (bot == target || sServerFacade.GetDistance2d(bot, target) < sPlayerbotAIConfig.sightDistance) &&
           bot->IsInGroup(target) &&
           (!aliveCheck || !target->IsDead()) &&
           (!auraCheck || !ai->HasAura(GetSpellID(), target));
}

/// 检查目标单位是否存活、在视野内且满足攻击/施法合法性
bool CastItemTargetAction::IsTargetValid(Unit* target)
{
    if (CastSpellTargetAction::IsTargetValid(target))
    {
        if (itemAuraCheck)
        {
            const uint32 itemId = GetItemId();
            const ItemPrototype* proto = sObjectMgr.GetItemPrototype(itemId);
            if (proto)
            {
                for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
                {
#ifdef MANGOSBOT_ZERO
                    if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_USE || proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_NO_DELAY_USE)
#else
                    if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_USE)
#endif
                    {
                        if (proto->Spells[i].SpellId > 0 && ai->HasAura(proto->Spells[i].SpellId, target))
                        {
                            return false;
                        }
                    }
                }

                return true;
            }
        }
        else
        {
            return true;
        }
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（对物品目标施法动作）
bool CastItemTargetAction::isUseful()
{
    const ItemPrototype* proto = sObjectMgr.GetItemPrototype(GetItemId());
    if (proto)
    {
        std::set<uint32>& skipSpells = AI_VALUE(std::set<uint32>&, "skip spells list");
        if (!skipSpells.empty())
        {
            for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
            {
                const _Spell& spellData = proto->Spells[i];
                if (spellData.SpellId)
                {
                    if (skipSpells.find(spellData.SpellId) != skipSpells.end())
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    return false;
}

/// 判断执行该动作的前置条件是否满足（对物品目标施法动作）
bool CastItemTargetAction::isPossible()
{
    uint32 itemId = GetItemId();
    if (!itemId)
        return false;

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);

    if (!proto)
        return false;

    if (HasSpellCooldown(itemId))
        return false;

    if (!ai->HasCheat(BotCheatMask::item) && !bot->HasItemCount(itemId, 1))
        return false;

    uint32 spellCount = 0;

    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        _Spell const& spellData = proto->Spells[i];

        // no spell (无法术)
        if (!spellData.SpellId)
            continue;

        // wrong triggering type (触发器类型不匹配)
#ifdef MANGOSBOT_ZERO
        if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE && spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_NO_DELAY_USE)
#else
        if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE)
#endif
            continue;

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellData.SpellId);
        if (!spellInfo)
        {
            continue;
        }

        spellCount++;
    }

    return spellCount;
}

/// 执行动作主逻辑（对物品目标施法动作）
bool CastItemTargetAction::Execute(Event& event)
{
    uint32 itemId = GetItemId();
    Unit* target = GetTarget();
    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);

    if (!proto)
        return false;

    Item* item = nullptr;

    if (!ai->HasCheat(BotCheatMask::item)) // If bot has no item cheat it needs an item to cast. (若机器人未开启物品作弊，则需要实际拥有对应物品才可施放。)
    {
        // 查找背包中匹配的物品
        std::list<Item*> items = AI_VALUE2(std::list<Item*>, "inventory items", chat->formatQItem(itemId));

        if (items.empty())
            return false;

        item = items.front();
    }

    SpellCastTargets targets;
    if (target)
    {
        targets.setUnitTarget(target);
        targets.setDestination(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
    }
    else
        targets.m_targetMask = TARGET_FLAG_SELF;

    // use triggered flag only for items with many spell casts and for not first cast (仅对多段施法物品的后续施法使用 triggered 标志)
    int count = 0;

    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        _Spell const& spellData = proto->Spells[i];

        // no spell (无法术)
        if (!spellData.SpellId)
            continue;

        // wrong triggering type (触发器类型不匹配)
#ifdef MANGOSBOT_ZERO
        if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE && spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_NO_DELAY_USE)
#else
        if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_ON_USE)
#endif
            continue;

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellData.SpellId);
        if (!spellInfo)
        {
            continue;
        }

        if (spellInfo->Targets & TARGET_FLAG_DEST_LOCATION)
            targets.m_targetMask = TARGET_FLAG_DEST_LOCATION;

        BotUseItemSpell* spell = new BotUseItemSpell(bot, spellInfo, (count > 0) ? TRIGGERED_OLD_TRIGGERED : TRIGGERED_NONE);

        Item* tItem = nullptr;

        if (item)
        {
            spell->SetCastItem(item);
            item->SetUsedInSpell(true);
        }

        spell->m_clientCast = true;

        bool result = (spell->ForceSpellStart(&targets) == SPELL_CAST_OK);

        if (!result)
            return false;

        if (ai->HasCheat(BotCheatMask::item))
        {
            if (!HasSpellCooldown(itemId))
            {
                bot->RemoveSpellCooldown(*spellInfo, false);
                bot->AddCooldown(*spellInfo, proto, false);
            }
        }

        ++count;
    }

    return count;
}

/// 检查指定法术是否正处于冷却时间中
bool CastItemTargetAction::HasSpellCooldown(uint32 itemId)
{
    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);

    if (!proto)
        return false;

    uint32 spellId = 0;
    for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        if (proto->Spells[i].SpellTrigger != ITEM_SPELLTRIGGER_ON_USE)
        {
            continue;
        }

        if (proto->Spells[i].SpellId > 0)
        {
            if (!sServerFacade.IsSpellReady(bot, proto->Spells[i].SpellId))
                return true;

            if (!sServerFacade.IsSpellReady(bot, proto->Spells[i].SpellId, itemId))
                return true;
        }
    }

    return false;
}
