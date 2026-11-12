// 萨满祭司 - 动作头文件 (ShamanActions.h)：定义萨满祭司专用技能施放与战斗动作
#pragma once

#include "playerbot/strategy/actions/GenericActions.h"
#include "playerbot/strategy/actions/ChangeStrategyAction.h"

namespace ai
{
    // 自我增益动作：幽魂之狼 (CastGhostWolfAction)
    BUFF_ACTION(CastGhostWolfAction, "ghost wolf");
    // 施放次级治疗波动作
    class CastLesserHealingWaveAction : public CastHealingSpellAction 
    {
    public:
        CastLesserHealingWaveAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lesser healing wave") {}
    };

    // 施放次级治疗波动作
    class CastLesserHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealingWaveOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "lesser healing wave") {}
    };

    // 施放治疗波动作
    class CastHealingWaveAction : public CastHealingSpellAction 
    {
    public:
        CastHealingWaveAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "healing wave") {}
    };

    // 施放治疗波动作
    class CastHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingWaveOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "healing wave") {}
    };

    // 施放治疗链动作
    class CastChainHealAction : public CastAoeHealSpellAction 
    {
    public:
        CastChainHealAction(PlayerbotAI* ai) : CastAoeHealSpellAction(ai, "chain heal") {}
    };

    // 施放激流动作
    class CastRiptideAction : public CastHealingSpellAction 
    {
    public:
        CastRiptideAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "riptide") {}
    };

    // 施放激流动作
    class CastRiptideOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRiptideOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "riptide") {}
    };

    // 施放大地之盾动作
    class CastEarthShieldAction : public CastBuffSpellAction 
    {
    public:
        CastEarthShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "earth shield") {}
    };

    // 施放大地之盾动作
    class CastEarthShieldOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastEarthShieldOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "earth shield") {}
    };

    // 施放水之盾动作
    class CastWaterShieldAction : public CastBuffSpellAction 
    {
    public:
        CastWaterShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "water shield") {}
    };

    // 施放闪电之盾动作
    class CastLightningShieldAction : public CastBuffSpellAction 
    {
    public:
        CastLightningShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "lightning shield") {}
    };

    // 施放大地生命武器动作
    class CastEarthlivingWeaponAction : public CastEnchantItemAction 
    {
    public:
        CastEarthlivingWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "earthliving weapon") {}
    };

    // 施放石化武器动作
    class CastRockbiterWeaponAction : public CastEnchantItemAction 
    {
    public:
        CastRockbiterWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "rockbiter weapon") {}
    };

    // 施放火舌武器动作
    class CastFlametongueWeaponAction : public CastEnchantItemAction 
    {
    public:
        CastFlametongueWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "flametongue weapon") {}
    };

    // 施放冰封武器动作
    class CastFrostbrandWeaponAction : public CastEnchantItemAction 
    {
    public:
        CastFrostbrandWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "frostbrand weapon") {}
    };

    // 施放风怒武器动作
    class CastWindfuryWeaponAction : public CastEnchantItemAction 
    {
    public:
        CastWindfuryWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "windfury weapon") {}
    };

    // 施放萨满图腾动作
    class CastTotemAction : public CastBuffSpellAction
    {
    public:
        CastTotemAction(PlayerbotAI* ai, std::string spell) : CastBuffSpellAction(ai, spell) {}

        bool isUseful() override
        {
            if (!CastBuffSpellAction::isUseful())
                return false;

            Group* group = bot->GetGroup();
            if (!group)
                return !AI_VALUE2(bool, "has totem", name);

            for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
            {
                Player* member = ref->getSource();
                if (!member || !sServerFacade.IsAlive(member))
                    continue;

                if (member == bot)
                    continue;

                if (!member->IsInWorld() || member->GetMapId() != bot->GetMapId())
                    continue;

                if (!bot->IsWithinDistInMap(member, sPlayerbotAIConfig.spellDistance, false))
                    continue;

                // TODO: Implement a better check if member is affected
                // The aura we want to check is not the same as the spell to summon the totem
                // While all totems give an aura, aura behavior and naming is not consistent.
                // The consistent option between all totems is to check if the member is in range to the totem
                
                // This is somewhat inaccurate but a much simpler check: if the totem is down already,
                // then casting the totem is useless. This also checks proximity to owner. 
                // And if we are not within spell distance of other members, then dropping the totem won't help them. 
                return !AI_VALUE2(bool, "has totem", name);
            }

            return false;
        }

    protected:
        std::string GetTargetName() override { return "self target"; }
        std::string GetReachActionName() override { return "reach party member for totem"; }

        NextAction** getPrerequisites() override
        {
            if (!bot->GetGroup())
                return CastBuffSpellAction::getPrerequisites();

            const std::string qualifiersStr = Qualified::MultiQualify({ GetSpellName(), "party member for totem" }, "::");
            return NextAction::merge(
                NextAction::array(0, new NextAction("reach party member for totem::" + qualifiersStr), nullptr),
                CastBuffSpellAction::getPrerequisites());
        }
    };

    // 施放石肤图腾动作
    class CastStoneskinTotemAction : public CastTotemAction
    {
    public:
        CastStoneskinTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "stoneskin totem") {}
    };

    // 施放石爪图腾动作
    class CastStoneclawTotemAction : public CastTotemAction
    {
    public:
        CastStoneclawTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "stoneclaw totem") {}
    };

    // 施放根基图腾动作
    class CastGroundingTotemAction : public CastTotemAction
    {
    public:
        CastGroundingTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "grounding totem") {}
    };

    // 施放地缚图腾动作
    class CastEarthbindTotemAction : public CastTotemAction
    {
    public:
        CastEarthbindTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "earthbind totem") {}
    };

    // 施放战栗图腾动作
    class CastTremorTotemAction : public CastTotemAction
    {
    public:
        CastTremorTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "tremor totem") {}
    };

    // 施放宁静之风图腾动作
    class CastTranquilAirTotemAction : public CastTotemAction
    {
    public:
        CastTranquilAirTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "tranquil air totem") {}
    };

    // 施放大地之力图腾动作
    class CastStrengthOfEarthTotemAction : public CastTotemAction
    {
    public:
        CastStrengthOfEarthTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "strength of earth totem") {}
    };

    // 施放法力之泉图腾动作
    class CastManaSpringTotemAction : public CastTotemAction
    {
    public:
        CastManaSpringTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "mana spring totem") {}
        virtual bool isUseful() override { return CastTotemAction::isUseful() && !AI_VALUE2(bool, "has totem", "healing stream totem"); }
    };

    // 施放法力之潮图腾动作
    class CastManaTideTotemAction : public CastTotemAction
    {
    public:
        CastManaTideTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "mana tide totem") {}
        virtual std::string GetTargetName() override { return "self target"; }
    };

    // 施放治疗之泉图腾动作
    class CastHealingStreamTotemAction : public CastTotemAction
    {
    public:
        CastHealingStreamTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "healing stream totem") {}
    };

    // 施放空气之怒图腾动作
    class CastWrathOfAirTotemAction : public CastTotemAction
    {
    public:
        CastWrathOfAirTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "wrath of air totem") {}

        virtual bool isUseful() override
        {
            return (!bot->GetGroup() || ai->HasStrategy("totem air wrath", BotState::BOT_STATE_COMBAT)) && CastTotemAction::isUseful();
        }
    };

    // 施放抗寒图腾动作
    class CastFrostResistanceTotemAction : public CastTotemAction
    {
    public:
        CastFrostResistanceTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "frost resistance totem") {}
    };

    // 施放抗火图腾动作
    class CastFireResistanceTotemAction : public CastTotemAction
    {
    public:
        CastFireResistanceTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "fire resistance totem") {}
    };

    // 施放自然抗性图腾动作
    class CastNatureResistanceTotemAction : public CastTotemAction
    {
    public:
        CastNatureResistanceTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "nature resistance totem") {}
    };

    // 施放祛病图腾动作
    class CastDiseaseCleansingTotemAction : public CastTotemAction
    {
    public:
        CastDiseaseCleansingTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "disease cleansing totem") {}
    };

    // 施放清毒图腾动作
    class CastPoisonCleansingTotemAction : public CastTotemAction
    {
    public:
        CastPoisonCleansingTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "poison cleansing totem") {}
    };

    // 施放天罚图腾动作
    class CastTotemOfWrathAction : public CastTotemAction
    {
    public:
        CastTotemOfWrathAction(PlayerbotAI* ai) : CastTotemAction(ai, "totem of wrath") {}
    };

    // 施放清毒图腾动作
    class CastCleansingTotemAction : public CastTotemAction
    {
    public:
        CastCleansingTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "cleansing totem") {}
    };

    // 施放火舌图腾动作
    class CastFlametongueTotemAction : public CastTotemAction
    {
    public:
        CastFlametongueTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "flametongue totem") {}
        virtual bool isUseful() override { return CastTotemAction::isUseful() && !AI_VALUE2(bool, "has totem", "magma totem"); }
    };

    // 施放风怒图腾动作
    class CastWindfuryTotemAction : public CastTotemAction
    {
    public:
        CastWindfuryTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "windfury totem") {}

        virtual bool isUseful() override
        {
            return (bot->GetGroup() || ai->HasStrategy("totem air windfury", BotState::BOT_STATE_COMBAT)) && CastTotemAction::isUseful();
        }
    };

    // 施放风墙图腾动作
    class CastWindwallTotemAction : public CastTotemAction
    {
    public:
        CastWindwallTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "windwall totem") {}
    };

    // 施放风之优雅图腾动作
    class CastGraceOfAirTotemAction : public CastTotemAction
    {
    public:
        CastGraceOfAirTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "grace of air totem") {}

        virtual bool isUseful() override
        {
            return (!bot->GetGroup() || ai->HasStrategy("totem air grace", BotState::BOT_STATE_COMBAT)) && CastTotemAction::isUseful();
        }
    };

    // 施放灼热图腾动作
    class CastSearingTotemAction : public CastTotemAction
    {
    public:
        CastSearingTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "searing totem") {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool isUseful() override { return CastTotemAction::isUseful() && !AI_VALUE2(bool, "has totem", "flametongue totem"); }
    };

    // 施放熔岩图腾动作
    class CastMagmaTotemAction : public CastMeleeSpellAction
    {
    public:
        CastMagmaTotemAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "magma totem") {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool isUseful() override { return CastMeleeSpellAction::isUseful() && !AI_VALUE2(bool, "has totem", name); }
    };

    // 施放火焰新星动作
    class CastFireNovaAction : public CastSpellAction 
    {
    public:
        CastFireNovaAction(PlayerbotAI* ai) : CastSpellAction(ai, "fire nova") {}
    };

    // 施放风剪动作
    class CastWindShearAction : public CastSpellAction 
    {
    public:
        CastWindShearAction(PlayerbotAI* ai) : CastSpellAction(ai, "wind shear") {}
    };

    // 施放先祖之魂动作
    class CastAncestralSpiritAction : public ResurrectPartyMemberAction
    {
    public:
        CastAncestralSpiritAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "ancestral spirit") {}
    };

    // 施放净化术动作
    class CastPurgeAction : public CastSpellAction
    {
    public:
        CastPurgeAction(PlayerbotAI* ai) : CastSpellAction(ai, "purge") {}
    };

    // 施放风暴打击动作
    class CastStormstrikeAction : public CastMeleeSpellAction 
    {
    public:
        CastStormstrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "stormstrike") {}
    };

    // 施放熔岩猛击动作
    class CastLavaLashAction : public CastMeleeSpellAction 
    {
    public:
        CastLavaLashAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "lava lash") {}
    };

    // 施放水下呼吸动作
    class CastWaterBreathingAction : public CastBuffSpellAction 
    {
    public:
        CastWaterBreathingAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "water breathing") {}
    };

    // 施放水上行走动作
    class CastWaterWalkingAction : public CastBuffSpellAction 
    {
    public:
        CastWaterWalkingAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "water walking") {}
    };

    // 施放水下呼吸动作
    class CastWaterBreathingOnPartyAction : public BuffOnPartyAction 
    {
    public:
        CastWaterBreathingOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "water breathing") {}
    };

    // 施放水上行走动作
    class CastWaterWalkingOnPartyAction : public BuffOnPartyAction 
    {
    public:
        CastWaterWalkingOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "water walking") {}
    };

    // 施放净化灵魂动作
    class CastCleanseSpiritAction : public CastCureSpellAction 
    {
    public:
        CastCleanseSpiritAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cleanse spirit") {}
    };

    // 施放净化灵魂动作
    class CastCleanseSpiritPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseSpiritPoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse spirit", DISPEL_POISON) {}

        virtual std::string getName() override { return "cleanse spirit poison on party"; }
    };
    // 施放净化灵魂动作
    class CastCleanseSpiritCurseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseSpiritCurseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse spirit", DISPEL_CURSE) {}

        virtual std::string getName() override { return "cleanse spirit curse on party"; }
    };
    // 施放净化灵魂动作
    class CastCleanseSpiritDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseSpiritDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse spirit", DISPEL_DISEASE) {}

        virtual std::string getName() override { return "cleanse spirit disease on party"; }
    };

    // 施放烈焰震击动作
    class CastFlameShockAction : public CastRangedDebuffSpellAction
    {
    public:
        CastFlameShockAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "flame shock") {}
    };

    // 施放大地震击动作
    class CastEarthShockAction : public CastRangedDebuffSpellAction
    {
    public:
        CastEarthShockAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "earth shock") {}
    };

    // 施放冰霜震击动作
    class CastFrostShockAction : public CastSnareSpellAction
    {
    public:
        CastFrostShockAction(PlayerbotAI* ai) : CastSnareSpellAction(ai, "frost shock") {}
    };

    // 施放闪电链动作
    class CastChainLightningAction : public CastSpellAction
    {
    public:
        CastChainLightningAction(PlayerbotAI* ai) : CastSpellAction(ai, "chain lightning") {}
    };

    // 施放闪电箭动作
    class CastLightningBoltAction : public CastSpellAction
    {
    public:
        CastLightningBoltAction(PlayerbotAI* ai) : CastSpellAction(ai, "lightning bolt") {}
    };

    // 施放雷霆风暴动作
    class CastThunderstormAction : public CastMeleeSpellAction
    {
    public:
        CastThunderstormAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "thunderstorm") {}
    };

    // 施放英勇动作
    class CastHeroismAction : public CastBuffSpellAction
    {
    public:
        CastHeroismAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "heroism") {}
    };

    // 施放嗜血动作
    class CastBloodlustAction : public CastBuffSpellAction
    {
    public:
        CastBloodlustAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bloodlust") {}
    };

    // 施放风剪动作
    class CastWindShearOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastWindShearOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "wind shear") {}
    };

    // 施放消毒术动作
    class CastCurePoisonAction : public CastCureSpellAction
    {
    public:
        CastCurePoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cure poison") {}
    };

    // 施放消毒术动作
    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}
    };

    // 施放祛病术动作
    class CastCureDiseaseAction : public CastCureSpellAction 
    {
    public:
        CastCureDiseaseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cure disease") {}
    };

    // 施放祛病术动作
    class CastCureDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCureDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cure disease", DISPEL_DISEASE) {}
        virtual std::string getName() override { return "cure disease on party"; }
    };

    // 施放元素的召唤动作
    class CastCallOfTheElements : public CastBuffSpellAction
    {
    public:
        CastCallOfTheElements(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call of the elements") {}
    };

    // 施放先祖的召唤动作
    class CastCallOfTheAncestors : public CastBuffSpellAction
    {
    public:
        CastCallOfTheAncestors(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call of the ancestors") {}
    };

    // 施放灵魂的召唤动作
    class CastCallOfTheSpirits : public CastBuffSpellAction
    {
    public:
        CastCallOfTheSpirits(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call of the spirits") {}
    };    

    // 施放图腾收回动作
    class CastTotemicRecall : public CastBuffSpellAction
    {
    public:
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE
        CastTotemicRecall(PlayerbotAI* ai) : CastBuffSpellAction(ai, "totemic call") {}
#else
        CastTotemicRecall(PlayerbotAI* ai) : CastBuffSpellAction(ai, "totemic recall") {}
#endif
    };

    // 施放大地之盾动作
    class CastEarthShieldOnPartyTankAction : public BuffOnTankAction
    {
    public:
        CastEarthShieldOnPartyTankAction(PlayerbotAI* ai) : BuffOnTankAction(ai, "earth shield") {}
    };

    // SetTotemBars
    class SetTotemBars : public Action
    {
    public:
        SetTotemBars(PlayerbotAI* ai) : Action(ai, "setup shaman totembar")
        {
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
            //This sets the totems in the proper actions bars (the totem bars)
            //Fire totems
            uint32 totem_of_wrath_id = AI_VALUE2(uint32, "spell id", "totem of wrath");
            uint32 searing_totem_id = AI_VALUE2(uint32, "spell id", "searing totem");
            uint32 magma_totem_id = AI_VALUE2(uint32, "spell id", "magma totem");

            //Earth totems
            uint32 strength_of_earth_totem_id = AI_VALUE2(uint32, "spell id", "strength of earth totem");
            uint32 stoneskin_totem_id = AI_VALUE2(uint32, "spell id", "stoneskin totem");

            //Air totems
            uint32 windfury_totem_id = AI_VALUE2(uint32, "spell id", "windfury totem");
            uint32 wrath_of_air_totem_id = AI_VALUE2(uint32, "spell id", "wrath of air totem");

            //Water totems
            uint32 healing_stream_totem_id = AI_VALUE2(uint32, "spell id", "healing stream totem");
            uint32 mana_spring_totem_id = AI_VALUE2(uint32, "spell id", "mana spring totem");

            Player* bot = ai->GetBot();
            // Call of the elements - Melee focus
            if (magma_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR, magma_totem_id, ACTION_BUTTON_SPELL);
            if (strength_of_earth_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 1, strength_of_earth_totem_id, ACTION_BUTTON_SPELL);
            if (windfury_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 2, windfury_totem_id, ACTION_BUTTON_SPELL);
            if (healing_stream_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 3, healing_stream_totem_id, ACTION_BUTTON_SPELL);

            // Call of the Ancestors - Caster focus
            if (totem_of_wrath_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 4, totem_of_wrath_id, ACTION_BUTTON_SPELL);
            else if (searing_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 4, searing_totem_id, ACTION_BUTTON_SPELL);

            if (stoneskin_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 5, stoneskin_totem_id, ACTION_BUTTON_SPELL);
            if (wrath_of_air_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 6, wrath_of_air_totem_id, ACTION_BUTTON_SPELL);
            if (mana_spring_totem_id)
                bot->addActionButton(bot->GetActiveSpec(), ACTION_BUTTON_SHAMAN_TOTEMS_BAR + 7, mana_spring_totem_id, ACTION_BUTTON_SPELL);
#endif
        }
    };

    // 施放更新PVE策略动作
    class UpdateShamanPveStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateShamanPveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
        {
            std::vector<std::string> strategiesRequired = {"elemental"};
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "elemental pve", strategiesRequired);
            
            strategiesRequired = {"elemental", "aoe"};
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe elemental pve", strategiesRequired);

            strategiesRequired = { "elemental", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc elemental pve", strategiesRequired);

            strategiesRequired = { "elemental", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure elemental pve", strategiesRequired);

            strategiesRequired = { "elemental", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems elemental pve", strategiesRequired);

            strategiesRequired = { "elemental", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff elemental pve", strategiesRequired);

            strategiesRequired = { "elemental", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost elemental pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost elemental pve", strategiesRequired);

            strategiesRequired = { "enhancement" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "enhancement pve", strategiesRequired);

            strategiesRequired = { "enhancement", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe enhancement pve", strategiesRequired);

            strategiesRequired = { "enhancement", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc enhancement pve", strategiesRequired);

            strategiesRequired = { "enhancement", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure enhancement pve", strategiesRequired);

            strategiesRequired = { "enhancement", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems enhancement pve", strategiesRequired);

            strategiesRequired = { "enhancement", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff enhancement pve", strategiesRequired);

            strategiesRequired = { "enhancement", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost enhancement pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost enhancement pve", strategiesRequired);

            strategiesRequired = { "restoration" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "restoration pve", strategiesRequired);

            strategiesRequired = { "restoration", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe restoration pve", strategiesRequired);
            
            strategiesRequired = { "restoration", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc restoration pve", strategiesRequired);

            strategiesRequired = { "restoration", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure restoration pve", strategiesRequired);

            strategiesRequired = { "restoration", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems restoration pve", strategiesRequired);

            strategiesRequired = { "restoration", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff restoration pve", strategiesRequired);

            strategiesRequired = { "restoration", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost restoration pve", strategiesRequired);
        
            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pve", strategiesRequired);
        }
    };

    // 施放更新PVP策略动作
    class UpdateShamanPvpStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateShamanPvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
        {
            std::vector<std::string> strategiesRequired = { "elemental" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "elemental pvp", strategiesRequired);

            strategiesRequired = { "elemental", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe elemental pvp", strategiesRequired);

            strategiesRequired = { "elemental", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc elemental pvp", strategiesRequired);

            strategiesRequired = { "elemental", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure elemental pvp", strategiesRequired);

            strategiesRequired = { "elemental", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems elemental pvp", strategiesRequired);

            strategiesRequired = { "elemental", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff elemental pvp", strategiesRequired);

            strategiesRequired = { "elemental", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost elemental pvp", strategiesRequired);

            strategiesRequired = { "enhancement" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "enhancement pvp", strategiesRequired);

            strategiesRequired = { "enhancement", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe enhancement pvp", strategiesRequired);

            strategiesRequired = { "enhancement", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc enhancement pvp", strategiesRequired);

            strategiesRequired = { "enhancement", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure enhancement pvp", strategiesRequired);

            strategiesRequired = { "enhancement", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems enhancement pvp", strategiesRequired);

            strategiesRequired = { "enhancement", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff enhancement pvp", strategiesRequired);

            strategiesRequired = { "enhancement", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost enhancement pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost enhancement pvp", strategiesRequired);

            strategiesRequired = { "restoration" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc elemental pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc elemental pvp", strategiesRequired);

            strategiesRequired = { "restoration", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost restoration pvp", strategiesRequired);
        
            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pvp", strategiesRequired);
        }
    };

    // 施放更新团队副本策略动作
    class UpdateShamanRaidStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateShamanRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
        {
            std::vector<std::string> strategiesRequired = { "elemental" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "elemental raid", strategiesRequired);

            strategiesRequired = { "elemental", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe elemental raid", strategiesRequired);

            strategiesRequired = { "elemental", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc elemental raid", strategiesRequired);

            strategiesRequired = { "elemental", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure elemental raid", strategiesRequired);

            strategiesRequired = { "elemental", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems elemental raid", strategiesRequired);

            strategiesRequired = { "elemental", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff elemental raid", strategiesRequired);

            strategiesRequired = { "elemental", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost elemental raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost elemental raid", strategiesRequired);

            strategiesRequired = { "enhancement" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "enhancement raid", strategiesRequired);

            strategiesRequired = { "enhancement", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe enhancement raid", strategiesRequired);

            strategiesRequired = { "enhancement", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc enhancement raid", strategiesRequired);

            strategiesRequired = { "enhancement", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure enhancement raid", strategiesRequired);

            strategiesRequired = { "enhancement", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems enhancement raid", strategiesRequired);

            strategiesRequired = { "enhancement", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff enhancement raid", strategiesRequired);

            strategiesRequired = { "enhancement", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost enhancement raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost enhancement raid", strategiesRequired);

            strategiesRequired = { "restoration" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "restoration raid", strategiesRequired);

            strategiesRequired = { "restoration", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe restoration raid", strategiesRequired);

            strategiesRequired = { "restoration", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc restoration raid", strategiesRequired);

            strategiesRequired = { "restoration", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure restoration raid", strategiesRequired);

            strategiesRequired = { "restoration", "totems" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "totems restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "totems restoration raid", strategiesRequired);

            strategiesRequired = { "restoration", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff restoration raid", strategiesRequired);

            strategiesRequired = { "restoration", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost restoration raid", strategiesRequired);
        
            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal raid", strategiesRequired);
        }
    };
}
