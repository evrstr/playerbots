// 萨满祭司 - 触发器头文件 (ShamanTriggers.h)：定义萨满祭司增益、减益、冷却及状态检查触发条件
#pragma once
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    // 触发器：石化武器
    class ShamanWeaponTrigger : public BuffTrigger 
    {
    public:
        ShamanWeaponTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "rockbiter weapon") {}
        virtual bool IsActive() override;
    private:
        static std::list<std::string> spells;
    };

    // 触发器：准备收回图腾
    class ReadyToRemoveTotemsTrigger : public Trigger
    {
    public:
        ReadyToRemoveTotemsTrigger(PlayerbotAI* ai) : Trigger(ai, "ready to remove totems", 10) {}

        virtual bool IsActive() override
        {
            bool totemIsNear = false;
            std::list<ObjectGuid> units = *context->GetValue<std::list<ObjectGuid>>("nearest npcs");
            for (std::list<ObjectGuid>::iterator i = units.begin(); i != units.end(); i++)
            {
                Unit* unit = ai->GetUnit(*i);
                if (!unit)
                    continue;

                Creature* totem = dynamic_cast<Creature*>(unit);
                if (!totem || !totem->IsTotem())
                    continue;

                Unit* totemOwner = totem->GetCreator(totem);
                if (!totemOwner || totemOwner != bot)
                    continue;

                const bool totemIsInRange = sServerFacade.GetDistance2d(totemOwner, totem) <= ai->GetRange("spell");

                if (totemIsInRange) 
                {
                    totemIsNear = true;
                    break;
                }
            }
            // Avoid removing any of the big cooldown totems.
            return AI_VALUE(bool, "have any totem")
                && !totemIsNear
                && !AI_VALUE2(bool, "has totem", "mana tide totem")
                && !AI_VALUE2(bool, "has totem", "earth elemental totem")
                && !AI_VALUE2(bool, "has totem", "fire elemental totem");
        }
    };

    // 触发器：未召唤图腾
    class TotemsAreNotSummonedTrigger : public Trigger 
    {
    public:
        TotemsAreNotSummonedTrigger(PlayerbotAI* ai) : Trigger(ai, "no totems summoned", 5) {}

        virtual bool IsActive() override
        {
            return !AI_VALUE(bool, "have any totem");
        }
    };

    // 触发器：萨满图腾存在检查
    class TotemTrigger : public Trigger 
    {
    public:
        TotemTrigger(PlayerbotAI* ai, std::string spell, int attackerCount = 0) : Trigger(ai, spell), attackerCount(attackerCount) {}

        virtual bool IsActive() override
        {
            return AI_VALUE(uint8, "attackers count") >= attackerCount && !AI_VALUE2(bool, "has totem", name);
        }

    protected:
        int attackerCount;
    };

    // 触发器：触发专精对应的火系图腾
    class FireTotemTrigger : public Trigger 
    {
    public:
        FireTotemTrigger(PlayerbotAI* ai, bool inMovement = true) : Trigger(ai, "trigger spec appropriate fire totem", 5), inMovement(inMovement) {}

        virtual bool IsActive() override
        {
            if (!inMovement && bot->IsMoving() && bot->GetMotionMaster() && bot->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE)
            {
                return false;
            }

            if (ai->HasStrategy("totem fire nova", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "fire nova totem");
            }
            else if (ai->HasStrategy("totem fire flametongue", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "flametongue totem");
            }
            else if (ai->HasStrategy("totem fire resistance", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "frost resistance totem");
            }
            else if (ai->HasStrategy("totem fire magma", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "magma totem");
            }
            else if (ai->HasStrategy("totem fire searing", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "searing totem");
            }
            else
            {
                return !AI_VALUE2(bool, "has totem", "searing totem") &&
                       !AI_VALUE2(bool, "has totem", "magma totem") &&
                       !AI_VALUE2(bool, "has totem", "frost resistance totem") &&
                       !AI_VALUE2(bool, "has totem", "flametongue totem") &&
                       !AI_VALUE2(bool, "has totem", "totem of wrath") &&
                       !AI_VALUE2(bool, "has totem", "fire elemental totem");
            }
        }

    private:
        bool inMovement;
    };

    // 触发器：触发专精对应的AOE火系图腾
    class FireTotemAoeTrigger : public Trigger 
    {
    public:
        FireTotemAoeTrigger(PlayerbotAI* ai) : Trigger(ai, "trigger spec appropriate fire totem aoe", 2) {}
        virtual bool IsActive() override
        {
            return AI_VALUE(uint8, "attackers count") >= 3 &&
                !AI_VALUE2(bool, "has totem", "searing totem") &&
                !AI_VALUE2(bool, "has totem", "magma totem") &&
                !AI_VALUE2(bool, "has totem", "frost resistance totem") &&
                !AI_VALUE2(bool, "has totem", "flametongue totem") &&
                !AI_VALUE2(bool, "has totem", "totem of wrath") &&
                !AI_VALUE2(bool, "has totem", "fire elemental totem");
        }
    };

    // 触发器：触发专精对应的土系图腾
    class EarthTotemTrigger : public Trigger 
    {
    public:
        EarthTotemTrigger(PlayerbotAI* ai, bool inMovement = true) : Trigger(ai, "trigger spec appropriate earth totem", 5), inMovement(inMovement) {}

        virtual bool IsActive() override
        {
            if (!inMovement && bot->IsMoving() && bot->GetMotionMaster() && bot->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE)
            {
                return false;
            }

            if (ai->HasStrategy("totem earth stoneclaw", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "stoneclaw totem");
            }
            else if (ai->HasStrategy("totem earth stoneskin", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "stoneskin totem");
            }
            else if (ai->HasStrategy("totem earth earthbind", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "earthbind totem");
            }
            else if (ai->HasStrategy("totem earth strength", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "strength of earth totem");
            }
            else if (ai->HasStrategy("totem earth tremor", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "tremor totem");
            }
            else
            {
                return !AI_VALUE2(bool, "has totem", "earthbind totem") &&
                       !AI_VALUE2(bool, "has totem", "stoneskin totem") &&
                       !AI_VALUE2(bool, "has totem", "stoneclaw totem") &&
                       !AI_VALUE2(bool, "has totem", "strength of earth totem") &&
                       !AI_VALUE2(bool, "has totem", "tremor totem") &&
                       !AI_VALUE2(bool, "has totem", "earth elemental totem");
            }
        }

    private:
        bool inMovement;
    };

    // 触发器：触发专精对应的风系图腾
    class AirTotemTrigger : public Trigger 
    {
    public:
        AirTotemTrigger(PlayerbotAI* ai, bool inMovement = true) : Trigger(ai, "trigger spec appropriate air totem", 5), inMovement(inMovement) {}

        virtual bool IsActive() override
        {
            if (!inMovement && bot->IsMoving() && bot->GetMotionMaster() && bot->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE)
            {
                return false;
            }

            if (ai->HasStrategy("totem air grace", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "grace of air totem");
            }
            else if (ai->HasStrategy("totem air grounding", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "grounding totem");
            }
            else if (ai->HasStrategy("totem air resistance", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "nature resistance totem");
            }
            else if (ai->HasStrategy("totem air tranquil", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "tranquil air totem");
            }
            else if (ai->HasStrategy("totem air windfury", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "windfury totem");
            }
            else if (ai->HasStrategy("totem air windwall", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "windwall totem");
            }
            else if (ai->HasStrategy("totem air wrath", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "wrath of air totem");
            }
            else
            {
                return !AI_VALUE2(bool, "has totem", "grace of air totem") &&
                       !AI_VALUE2(bool, "has totem", "windwall totem") &&
                       !AI_VALUE2(bool, "has totem", "tranquil air totem") &&
                       !AI_VALUE2(bool, "has totem", "windfury totem") &&
                       !AI_VALUE2(bool, "has totem", "grounding totem") &&
                       !AI_VALUE2(bool, "has totem", "sentry totem") &&
                       !AI_VALUE2(bool, "has totem", "nature resistance totem") &&
                       !AI_VALUE2(bool, "has totem", "wrath of air totem");
            }
        }

    private:
        bool inMovement;
    };

    // 触发器：触发专精对应的水系图腾
    class WaterTotemTrigger : public Trigger 
    {
    public:
        WaterTotemTrigger(PlayerbotAI* ai, bool inMovement = true) : Trigger(ai, "trigger spec appropriate water totem", 5), inMovement(inMovement) {}

        virtual bool IsActive() override
        {
            if (!inMovement && bot->IsMoving() && bot->GetMotionMaster() && bot->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE)
            {
                return false;
            }

            if (ai->HasStrategy("totem water cleansing", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "disease cleansing totem");
            }
            else if (ai->HasStrategy("totem water resistance", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "fire resistance totem");
            }
            else if (ai->HasStrategy("totem water healing", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "healing stream totem");
            }
            else if (ai->HasStrategy("totem water mana", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "mana spring totem");
            }
            else if (ai->HasStrategy("totem water poison", BotState::BOT_STATE_COMBAT))
            {
                return !AI_VALUE2(bool, "has totem", "poison cleansing totem");
            }
            else
            {
                return !AI_VALUE2(bool, "has totem", "healing stream totem") &&
                       !AI_VALUE2(bool, "has totem", "mana spring totem") &&
                       !AI_VALUE2(bool, "has totem", "poison cleansing totem") &&
                       !AI_VALUE2(bool, "has totem", "disease cleansing totem") &&
                       !AI_VALUE2(bool, "has totem", "mana tide totem") &&
                       !AI_VALUE2(bool, "has totem", "fire resistance totem");
            }
        }

    private:
        bool inMovement;
    };

    // 触发器：风剪
    class WindShearInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        WindShearInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "wind shear") {}
    };

    // 触发器：水之盾
    class WaterShieldTrigger : public BuffTrigger
    {
    public:
        WaterShieldTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "water shield") {}
    };

    // 触发器：闪电之盾
    class LightningShieldTrigger : public BuffTrigger
    {
    public:
        LightningShieldTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "lightning shield") {}
    };

    // 触发器：净化术
    class PurgeTrigger : public TargetAuraDispelTrigger
    {
    public:
        PurgeTrigger(PlayerbotAI* ai) : TargetAuraDispelTrigger(ai, "purge", DISPEL_MAGIC, 3) {}
        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if (!target)
                return false;

            if (sServerFacade.IsFriendlyTo(bot, target))
                return false;

            for (uint32 type = SPELL_AURA_NONE; type < TOTAL_AURAS; ++type)
            {
                Unit::AuraList const& auras = target->GetAurasByType((AuraType)type);
                for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                {
                    const Aura* aura = *itr;
                    const SpellEntry* entry = aura->GetSpellProto();
                    uint32 spellId = entry->Id;
                    if (!IsPositiveSpell(spellId) || !IsPositiveAuraEffect(entry, aura->GetEffIndex()))
                        continue;

                    std::vector<uint32> ignoreSpells;
                    ignoreSpells.push_back(17627);
                    ignoreSpells.push_back(24382);
                    ignoreSpells.push_back(22888);
                    ignoreSpells.push_back(24425);
                    ignoreSpells.push_back(16609);
                    ignoreSpells.push_back(22818);
                    ignoreSpells.push_back(22820);
                    ignoreSpells.push_back(15366);
                    ignoreSpells.push_back(15852);
                    ignoreSpells.push_back(22817);
                    ignoreSpells.push_back(17538);
                    ignoreSpells.push_back(11405);
                    ignoreSpells.push_back(7396);
                    ignoreSpells.push_back(17539);

                    if (find(ignoreSpells.begin(), ignoreSpells.end(), spellId) != ignoreSpells.end())
                        continue;

                    /*if (sPlayerbotAIConfig.dispelAuraDuration && aura->GetAuraDuration() && aura->GetAuraDuration() < (int32)sPlayerbotAIConfig.dispelAuraDuration)
                        return false;*/

                    if (ai->canDispel(entry, DISPEL_MAGIC))
                        return true;
                }
            }
            return false;
        }
    };

    // 触发器：水上行走
    class WaterWalkingTrigger : public BuffTrigger 
    {
    public:
        WaterWalkingTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "water walking", 7) {}

        virtual bool IsActive() override
        {
            return BuffTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
        }
    };

    // 触发器：水下呼吸
    class WaterBreathingTrigger : public BuffTrigger 
    {
    public:
        WaterBreathingTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "water breathing", 5) {}

        virtual bool IsActive() override
        {
            return BuffTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
        }
    };

    // 触发器：对队友施放水上行走
    class WaterWalkingOnPartyTrigger : public BuffOnPartyTrigger 
    {
    public:
        WaterWalkingOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "water walking on party", 7) {}

        virtual bool IsActive() override
        {
            return BuffOnPartyTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
        }
    };

    // 触发器：对队友施放水下呼吸
    class WaterBreathingOnPartyTrigger : public BuffOnPartyTrigger 
    {
    public:
        WaterBreathingOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "water breathing on party", 2) {}

        virtual bool IsActive() override
        {
            return BuffOnPartyTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
        }
    };

    // 触发器：净化灵魂
    class CleanseSpiritPoisonTrigger : public NeedCureTrigger
    {
    public:
        CleanseSpiritPoisonTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse spirit", DISPEL_POISON) {}
    };

    // 触发器：净化灵魂
    class PartyMemberCleanseSpiritPoisonTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCleanseSpiritPoisonTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse spirit", DISPEL_POISON) {}
    };

    // 触发器：净化灵魂
    class CleanseSpiritCurseTrigger : public NeedCureTrigger
    {
    public:
        CleanseSpiritCurseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse spirit", DISPEL_CURSE) {}
    };

    // 触发器：净化灵魂
    class PartyMemberCleanseSpiritCurseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCleanseSpiritCurseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse spirit", DISPEL_CURSE) {}
    };

    // 触发器：净化灵魂
    class CleanseSpiritDiseaseTrigger : public NeedCureTrigger
    {
    public:
        CleanseSpiritDiseaseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse spirit", DISPEL_DISEASE) {}
    };

    // 触发器：净化灵魂
    class PartyMemberCleanseSpiritDiseaseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCleanseSpiritDiseaseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse spirit", DISPEL_DISEASE) {}
    };

    // 触发器：大地震击
    class ShockTrigger : public DebuffTrigger 
    {
    public:
        ShockTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "earth shock") {}
        virtual bool IsActive() override;
    };

    // 触发器：烈焰震击
    class FlameShockTrigger : public DebuffTrigger 
    {
    public:
        FlameShockTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "flame shock") {}
        virtual bool IsActive() override;
    };

    // 触发器：冰霜震击
    class FrostShockSnareTrigger : public SnareTargetTrigger
    {
    public:
        FrostShockSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "frost shock") {}
    };

    // 触发器：英勇
    class HeroismTrigger : public BoostTrigger
    {
    public:
        HeroismTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "heroism") {}
    };

    // 触发器：嗜血
    class BloodlustTrigger : public BoostTrigger
    {
    public:
        BloodlustTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "bloodlust") {}
    };

    // 触发器：漩涡武器
    class MaelstromWeaponTrigger : public HasAuraTrigger
    {
    public:
        MaelstromWeaponTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "maelstrom weapon") {}
    };

    // 触发器：风剪
    class WindShearInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        WindShearInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "wind shear") {}
    };

    // 触发器：消毒术
    class CurePoisonTrigger : public NeedCureTrigger
    {
    public:
        CurePoisonTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cure poison", DISPEL_POISON) {}
    };

    // 触发器：消毒术
    class PartyMemberCurePoisonTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCurePoisonTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cure poison", DISPEL_POISON) {}
    };

    // 触发器：祛病术
    class CureDiseaseTrigger : public NeedCureTrigger
    {
    public:
        CureDiseaseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };

    // 触发器：祛病术
    class PartyMemberCureDiseaseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCureDiseaseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };

    // 触发器：大地之盾
    class PartyTankEarthShieldTrigger : public BuffOnTankTrigger
    {
    public:
        PartyTankEarthShieldTrigger(PlayerbotAI* ai) : BuffOnTankTrigger(ai, "earth shield") {}

        virtual bool IsActive() override
        {
            Group* group = bot->GetGroup();
            if (group)
            {
                for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
                {
                    if (ai->HasAura("earth shield", ref->getSource(), false, true))
                        return false;
                }
            }

            return BuffOnTankTrigger::IsActive();
        }
    };

    // 可施法检查触发器：闪电链 (ChainLightningTrigger)
    CAN_CAST_TRIGGER(ChainLightningTrigger, "chain lightning");

    // 可施法检查触发器：风暴打击 (StormstrikeTrigger)
    CAN_CAST_TRIGGER(StormstrikeTrigger, "stormstrike");
}
