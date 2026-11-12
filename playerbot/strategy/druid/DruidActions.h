// 德鲁伊 - 动作头文件 (DruidActions.h)：定义德鲁伊专用技能施放与战斗动作
#pragma once
#include "playerbot/strategy/actions/GenericActions.h"

namespace ai
{
    // 施放精灵之火动作
    class CastFaerieFireAction : public CastRangedDebuffSpellAction
    {
    public:
        CastFaerieFireAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "faerie fire") {}
    };

    // 施放精灵之火(野性)动作
    class CastFaerieFireFeralAction : public CastRangedDebuffSpellAction
    {
    public:
        CastFaerieFireFeralAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "faerie fire (feral)") {}
    };

    // 施放回春术动作
    class CastRejuvenationAction : public CastHealingSpellAction 
    {
    public:
        CastRejuvenationAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "rejuvenation") {}
    };

    // 施放愈合动作
    class CastRegrowthAction : public CastHealingSpellAction 
    {
    public:
        CastRegrowthAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "regrowth") {}
    };

    // 施放迅捷治愈动作
    class CastSwiftmendAction : public CastHealingSpellAction 
    {
    public:
        CastSwiftmendAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "swiftmend") {}
        virtual bool isPossible() override
        {
            return CastHealingSpellAction::isPossible() && (ai->HasAura("regrowth", GetTarget()) || ai->HasAura("rejuvenation", GetTarget()));
        }
    };

    // 施放治疗之触动作
    class CastHealingTouchAction : public CastHealingSpellAction 
    {
    public:
        CastHealingTouchAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "healing touch") {}
    };

    // 施放回春术动作
    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "rejuvenation") {}
    };

    // 施放愈合动作
    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "regrowth") {}
    };

    // 施放迅捷治愈动作
    class CastSwiftmendOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastSwiftmendOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "swiftmend") {}
        virtual bool isPossible() override
        {
            return HealPartyMemberAction::isPossible() && (ai->HasAura("regrowth", GetTarget()) || ai->HasAura("rejuvenation", GetTarget()));
        }
    };

    // 施放治疗之触动作
    class CastHealingTouchOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingTouchOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "healing touch") {}
    };

    // 施放起死回生动作
    class CastReviveAction : public ResurrectPartyMemberAction
    {
    public:
        CastReviveAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "revive") {}

        virtual NextAction** getPrerequisites() 
        {
            return NextAction::merge( NextAction::array(0, new NextAction("restoration caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
        }
    };

    // 施放复生动作
    class CastRebirthAction : public CastSpellTargetAction
    {
    public:
        CastRebirthAction(PlayerbotAI* ai) : CastSpellTargetAction(ai, "rebirth", "revive targets") {}
        std::string GetReachActionName() override { return "reach party member to heal"; }
        std::string GetTargetName() override { return "party member to resurrect"; }
    };

    // 自我增益动作：野性印记 (CastMarkOfTheWildAction)
    BUFF_ACTION(CastMarkOfTheWildAction, "mark of the wild");
    // 队友增益动作：野性印记 (CastMarkOfTheWildOnPartyAction)
    BUFF_PARTY_ACTION(CastMarkOfTheWildOnPartyAction, "mark of the wild");
    // 团队强效祝福动作：野性赐福 (CastGiftOfTheWildOnPartyAction)
    GREATER_BUFF_PARTY_ACTION(CastGiftOfTheWildOnPartyAction, "gift of the wild", "mark of the wild");

    // 施放生存本能动作
    class CastSurvivalInstinctsAction : public CastBuffSpellAction 
    {
    public:
        CastSurvivalInstinctsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "survival instincts") {}
    };

    // 施放荆棘术动作
    class CastThornsAction : public CastBuffSpellAction 
    {
    public:
        CastThornsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "thorns") {}
    };

    // 施放荆棘术动作
    class CastThornsOnPartyAction : public BuffOnPartyAction 
    {
    public:
        CastThornsOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "thorns") {}
    };

    // 施放清晰预兆动作
    class CastOmenOfClarityAction : public CastBuffSpellAction 
    {
    public:
        CastOmenOfClarityAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "omen of clarity") {}
        virtual bool isUseful() override { return CastBuffSpellAction::isUseful() && ai->HasSpell("omen of clarity"); }
    };

    // 施放愤怒动作
    class CastWrathAction : public CastSpellAction
    {
    public:
        CastWrathAction(PlayerbotAI* ai) : CastSpellAction(ai, "wrath") {}
    };

    // 施放星辰坠落动作
    class CastStarfallAction : public CastSpellAction
    {
    public:
        CastStarfallAction(PlayerbotAI* ai) : CastSpellAction(ai, "starfall") {}
    };

    // 施放飓风动作
    class CastHurricaneAction : public CastSpellAction
    {
    public:
        CastHurricaneAction(PlayerbotAI* ai) : CastSpellAction(ai, "hurricane") {}
    };

    // 施放月火术动作
    class CastMoonfireAction : public CastRangedDebuffSpellAction
    {
    public:
        CastMoonfireAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "moonfire") {}
    };

    // 施放虫群动作
    class CastInsectSwarmAction : public CastRangedDebuffSpellAction
    {
    public:
        CastInsectSwarmAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "insect swarm") {}
    };

    // 施放星火术动作
    class CastStarfireAction : public CastSpellAction
    {
    public:
        CastStarfireAction(PlayerbotAI* ai) : CastSpellAction(ai, "starfire") {}
    };

    // 施放纠缠根须动作
    class CastEntanglingRootsAction : public CastSpellAction
    {
    public:
        CastEntanglingRootsAction(PlayerbotAI* ai) : CastSpellAction(ai, "entangling roots") {}
    };

    // 施放纠缠根须动作
    class CastEntanglingRootsCcAction : public CastCrowdControlSpellAction
    {
    public:
        CastEntanglingRootsCcAction(PlayerbotAI* ai) : CastCrowdControlSpellAction(ai, "entangling roots") {}
    };

    // 减速技能动作：纠缠根须 (CastEntanglingRootsSnareAction)
    SNARE_ACTION(CastEntanglingRootsSnareAction, "entangling roots");

    // 施放休眠动作
    class CastHibernateAction : public CastSpellAction
    {
    public:
        CastHibernateAction(PlayerbotAI* ai) : CastSpellAction(ai, "hibernate") {}
    };

    // 施放休眠动作
    class CastHibernateCcAction : public CastCrowdControlSpellAction
    {
    public:
        CastHibernateCcAction(PlayerbotAI* ai) : CastCrowdControlSpellAction(ai, "hibernate") {}
    };

    // 施放自然之握动作
    class CastNaturesGraspAction : public CastBuffSpellAction
    {
    public:
        CastNaturesGraspAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "nature's grasp") {}
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

    // 施放驱毒术动作
    class CastAbolishPoisonAction : public CastCureSpellAction
    {
    public:
        CastAbolishPoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "abolish poison") {}
    };

    // 施放驱毒术动作
    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "abolish poison", DISPEL_POISON) {}
    };

    // 自我驱散净化动作：解除诅咒 (CastRemoveCurseAction)
    CURE_ACTION(CastRemoveCurseAction, "remove curse");
    // 队友驱散净化动作：解除诅咒 (CastRemoveCurseOnPartyAction)
    CURE_PARTY_ACTION(CastRemoveCurseOnPartyAction, "remove curse", DISPEL_CURSE);

    // 施放树皮术动作
    class CastBarskinAction : public CastBuffSpellAction
    {
    public:
        CastBarskinAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "barskin") {}
    };

    // 施放激活动作
    class CastInnervateAction : public CastSpellTargetAction
    {
    public:
        CastInnervateAction(PlayerbotAI* ai) : CastSpellTargetAction(ai, "innervate", "boost targets", true, true) {}
        std::string GetTargetName() override { return "self target"; }

        bool IsTargetValid(Unit* target) override
        {
            if (CastSpellTargetAction::IsTargetValid(target))
            {
                const uint32 currentMana = target->GetPower(POWER_MANA);
                if (currentMana > 0)
                {
                    const uint32 maxMana = target->GetMaxPower(POWER_MANA);
                    const uint32 currentManaPct = (uint32)(currentMana / maxMana) * 100;
                    return currentManaPct < sPlayerbotAIConfig.lowMana;
                }
            }

            return false;
        }
    };

    // 施放宁静动作
    class CastTranquilityAction : public CastAoeHealSpellAction
    {
    public:
        CastTranquilityAction(PlayerbotAI* ai) : CastAoeHealSpellAction(ai, "tranquility") {}
    };

    // 施放自然迅捷动作
    class CastNaturesSwiftnessAction : public CastBuffSpellAction
    {
    public:
        CastNaturesSwiftnessAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "nature's swiftness") {}
    };

    // 施放熊形态动作
    class CastBearFormAction : public CastBuffSpellAction
    {
    public:
        CastBearFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bear form") {}

        virtual bool isPossible()
        {
            return CastBuffSpellAction::isPossible() && !ai->HasAura("dire bear form", GetTarget());
        }

        virtual bool isUseful()
        {
            return CastBuffSpellAction::isUseful() && !ai->HasAura("dire bear form", GetTarget());
        }
    };

    // 施放巨熊形态动作
    class CastDireBearFormAction : public CastBuffSpellAction
    {
    public:
        CastDireBearFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "dire bear form") {}

        virtual NextAction** getAlternatives() 
        {
            return NextAction::merge(NextAction::array(0, new NextAction("bear form"), NULL), CastSpellAction::getAlternatives());
        }
    };

    // 施放猎豹形态动作
    class CastCatFormAction : public CastBuffSpellAction
    {
    public:
        CastCatFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cat form") {}
    };

    // 施放生命之树动作
    class CastTreeFormAction : public CastBuffSpellAction
    {
    public:
        CastTreeFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "tree of life") {}
    };

    // 施放枭兽形态动作
    class CastMoonkinFormAction : public CastBuffSpellAction
    {
    public:
        CastMoonkinFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "moonkin form") {}
    };

    // 施放水栖形态动作
    class CastAquaticFormAction : public CastBuffSpellAction
    {
    public:
        CastAquaticFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aquatic form") {}
    };

    // 施放旅行形态动作
    class CastTravelFormAction : public CastBuffSpellAction
    {
    public:
        CastTravelFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "travel form") {}
        
        virtual bool isUseful()
        {
            bool firstmount = bot->GetLevel() >=
// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
                40
#else
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE
                30
#else
                20
#endif
#endif
                ;

            // useful if no mount or with wsg flag
            return !bot->IsMounted() || !firstmount;
        }
    };

    // 施放人形态(施法者形态)动作
    class CastCasterFormAction : public CastBuffSpellAction
    {
    public:
        CastCasterFormAction(PlayerbotAI* ai, std::string spell = "caster form") : CastBuffSpellAction(ai, spell) {}

        virtual bool isUseful() override
        {
            return ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form", "flight form", "swift flight form", "moonkin form", "tree of life", NULL);
        }

        virtual bool isPossible() { return true; }

        virtual bool Execute(Event& event);
    };

    // 施放平衡施法者形态动作
    class CastBalanceCasterFormAction : public CastCasterFormAction
    {
    public:
        CastBalanceCasterFormAction(PlayerbotAI* ai) : CastCasterFormAction(ai, "balance caster form") {}

        bool isUseful() override
        {
            return ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form", "flight form", "swift flight form", "tree of life", NULL);
        }
    };

    // 施放恢复施法者形态动作
    class CastRestorationCasterFormAction : public CastCasterFormAction
    {
    public:
        CastRestorationCasterFormAction(PlayerbotAI* ai) : CastCasterFormAction(ai, "restoration caster form") {}

        bool isUseful() override
        {
            return ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form", "flight form", "swift flight form", "moonkin form", NULL);
        }
    };

    // 施放平衡或恢复施法者形态动作
    class CastBalanceOrRestorationCasterFormAction : public CastCasterFormAction
    {
    public:
        CastBalanceOrRestorationCasterFormAction(PlayerbotAI* ai) : CastCasterFormAction(ai, "balance or restoration caster form") {}

        bool isUseful() override
        {
            return ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form", "flight form", "swift flight form", NULL);
        }
    };

    // 施放野性冲锋(豹)动作
    class CastFeralChargeCatAction : public CastReachTargetSpellAction
    {
    public:
        CastFeralChargeCatAction(PlayerbotAI* ai) : CastReachTargetSpellAction(ai, "feral charge - cat", 1.5f) {}
    };

    // 施放畏缩动作
    class CastCowerAction : public CastBuffSpellAction
    {
    public:
        CastCowerAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cower") {}
    };

    // 施放狂暴动作
    class CastBerserkAction : public CastBuffSpellAction
    {
    public:
        CastBerserkAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "berserk") {}
    };

    // 施放猛虎之怒动作
    class CastTigersFuryAction : public CastBuffSpellAction
    {
    public:
        CastTigersFuryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "tiger's fury") {}
    };

    // 施放扫击动作
    class CastRakeAction : public CastMeleeDebuffSpellAction
    {
    public:
        CastRakeAction(PlayerbotAI* ai) : CastMeleeDebuffSpellAction(ai, "rake") {}
    };

    // 施放爪击动作
    class CastClawAction : public CastMeleeSpellAction
    {
    public:
        CastClawAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "claw") {}
    };

    // 施放裂伤(豹)动作
    class CastMangleCatAction : public CastMeleeSpellAction
    {
    public:
        CastMangleCatAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mangle (cat)") {}
    };

    // 施放横扫(豹)动作
    class CastSwipeCatAction : public CastMeleeSpellAction
    {
    public:
        CastSwipeCatAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe (cat)") {}
    };

    // 施放凶猛撕咬动作
    class CastFerociousBiteAction : public CastMeleeSpellAction
    {
    public:
        CastFerociousBiteAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "ferocious bite") {}
    };

    // 施放割裂动作
    class CastRipAction : public CastMeleeSpellAction
    {
    public:
        CastRipAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "rip") {}
    };

    // 施放撕碎动作
    class CastShredAction : public CastMeleeSpellAction
    {
    public:
        CastShredAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "shred") {}
    };

    // 施放潜行动作
    class CastProwlAction : public CastBuffSpellAction
    {
    public:
        CastProwlAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "prowl") {}

        virtual std::string GetTargetName() override { return "self target"; }

        virtual bool isUseful()
        {
            if (ai->HasAura("prowl", bot))
            {
                return false;
            }

            // do not use with WSG flag
            return !ai->HasAura(23333, bot) && !ai->HasAura(23335, bot) && !ai->HasAura(34976, bot);
        }

        virtual bool Execute(Event& event)
        {
            if (ai->CastSpell("prowl", bot))
            {
                ai->ChangeStrategy("+stealthed", BotState::BOT_STATE_COMBAT);
                ai->ChangeStrategy("+stealthed", BotState::BOT_STATE_NON_COMBAT);
                bot->InterruptSpell(CURRENT_MELEE_SPELL);
            }

            return true;
        }
    };

    // 施放解除潜行动作
    class DruidUnstealthAction : public Action
    {
    public:
        DruidUnstealthAction(PlayerbotAI* ai) : Action(ai, "unstealth") {}

        bool Execute(Event& event) override
        {
            if (ai->HasAura("prowl", bot))
            {
                ai->RemoveAura("prowl");
                ai->ChangeStrategy("-stealthed", BotState::BOT_STATE_COMBAT);
                ai->ChangeStrategy("-stealthed", BotState::BOT_STATE_NON_COMBAT);
                return true;
            }

            return false;
        }
    };

    // 施放检查潜行动作
    class CheckStealthAction : public Action
    {
    public:
        CheckStealthAction(PlayerbotAI* ai) : Action(ai, "check stealth") {}

        bool Execute(Event& event) override
        {
            const bool isStealthed = ai->HasAura("prowl", bot);
            const bool hasStealthStrategy = ai->HasStrategy("stealthed", BotState::BOT_STATE_COMBAT);

            if (isStealthed && !hasStealthStrategy)
            {
                ai->ChangeStrategy("+stealthed", BotState::BOT_STATE_COMBAT);
                ai->ChangeStrategy("+stealthed", BotState::BOT_STATE_NON_COMBAT);
                return true;
            }
            else if (!isStealthed && hasStealthStrategy)
            {
                ai->ChangeStrategy("-stealthed", BotState::BOT_STATE_COMBAT);
                ai->ChangeStrategy("-stealthed", BotState::BOT_STATE_NON_COMBAT);
                return true;
            }

            return false;
        }

        bool isUseful() override
        {
            const bool isStealthed = ai->HasAura("prowl", bot);
            const bool hasStealthStrategy = ai->HasStrategy("stealthed", BotState::BOT_STATE_COMBAT);
            return (isStealthed && !hasStealthStrategy) || (!isStealthed && hasStealthStrategy);
        }
    };

    // 施放急奔动作
    class CastDashAction : public CastBuffSpellAction
    {
    public:
        CastDashAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "dash") {}
    };

    // 施放毁灭动作
    class CastRavageAction : public CastMeleeSpellAction
    {
    public:
        CastRavageAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "ravage") {}
    };

    // 施放突袭动作
    class CastPounceAction : public CastMeleeSpellAction
    {
    public:
        CastPounceAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "pounce") {}
    };

    // 施放野性冲锋(熊形态)动作
    class CastFeralChargeBearAction : public CastReachTargetSpellAction
    {
    public:
        CastFeralChargeBearAction(PlayerbotAI* ai) 
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
        : CastReachTargetSpellAction(ai, "feral charge - bear", 1.5f) {}
#else
        : CastReachTargetSpellAction(ai, "feral charge", 1.5f) {}
#endif
    };

    // 施放低吼动作
    class CastGrowlAction : public CastSpellAction
    {
    public:
        CastGrowlAction(PlayerbotAI* ai) : CastSpellAction(ai, "growl") {}
    };

    // 施放重殴动作
    class CastMaulAction : public CastMeleeSpellAction
    {
    public:
        CastMaulAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "maul") {}
        virtual bool isUseful() override { return CastMeleeSpellAction::isUseful() && AI_VALUE2(uint8, "rage", "self target") >= 45; }
    };

    // 施放重击动作
    class CastBashAction : public CastMeleeSpellAction
    {
    public:
        CastBashAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "bash") {}
    };

    // 施放横扫动作
    class CastSwipeAction : public CastMeleeSpellAction
    {
    public:
        CastSwipeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe") {}
    };

    // 施放挫志咆哮动作
    class CastDemoralizingRoarAction : public CastMeleeDebuffSpellAction
    {
    public:
        CastDemoralizingRoarAction(PlayerbotAI* ai) : CastMeleeDebuffSpellAction(ai, "demoralizing roar") {}
    };

    // 施放裂伤(熊)动作
    class CastMangleBearAction : public CastMeleeSpellAction
    {
    public:
        CastMangleBearAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mangle (bear)") {}
    };

    // 施放横扫(熊)动作
    class CastSwipeBearAction : public CastMeleeSpellAction
    {
    public:
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
        CastSwipeBearAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe (bear)") {}
#else
        CastSwipeBearAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe") {}
#endif
    };

    // 施放割伤动作
    class CastLacerateAction : public CastMeleeSpellAction
    {
    public:
        CastLacerateAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "lacerate") {}
    };

    // 施放重击动作
    class CastBashOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastBashOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "bash") {}
    };

    // 施放狂暴回复动作
    class CastFrenziedRegenerationAction : public CastBuffSpellAction
    {
    public:
        CastFrenziedRegenerationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "frenzied regeneration") {}
    };

    // 施放挑战咆哮动作
    class CastChallengingRoarAction : public CastMeleeSpellAction
    {
    public:
        CastChallengingRoarAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "challenging roar") {}
    };

    // 施放狂怒动作
    class CastEnrageAction : public CastBuffSpellAction
    {
    public:
        CastEnrageAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "enrage") {}
    };

    // 施放生命绽放动作
    class CastLifebloomAction : public CastSpellAction
    {
    public:
        explicit CastLifebloomAction(PlayerbotAI* ai) : CastSpellAction(ai, "lifebloom") {}

        std::string GetTargetName() override { return "party tank without lifebloom"; }
    };

    // 施放更新PVE策略动作
    class UpdateDruidPveStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateDruidPveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
        {
            std::vector<std::string> strategiesRequired = { "tank feral/bear/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "tank feral pve", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe tank feral pve", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc tank feral pve", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth tank feral pve", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure tank feral pve", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff tank feral pve", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost tank feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost tank feral pve", strategiesRequired);

            strategiesRequired = { "dps feral/cat" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "dps feral pve", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe dps feral pve", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc dps feral pve", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth dps feral pve", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure dps feral pve", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff dps feral pve", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost dps feral pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost dps feral pve", strategiesRequired);

            strategiesRequired = { "restoration/heal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "restoration pve", strategiesRequired);

            strategiesRequired = { "restoration/heal", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe restoration pve", strategiesRequired);

            strategiesRequired = { "restoration/heal", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc restoration pve", strategiesRequired);

            strategiesRequired = { "restoration/heal", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth restoration pve", strategiesRequired);

            strategiesRequired = { "restoration/heal", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure restoration pve", strategiesRequired);

            strategiesRequired = { "restoration/heal", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff restoration pve", strategiesRequired);

            strategiesRequired = { "restoration/heal", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost restoration pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost restoration pve", strategiesRequired);

            strategiesRequired = { "balance" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "balance pve", strategiesRequired);

            strategiesRequired = { "balance", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe balance pve", strategiesRequired);

            strategiesRequired = { "balance", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc balance pve", strategiesRequired);

            strategiesRequired = { "balance", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth balance pve", strategiesRequired);

            strategiesRequired = { "balance", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure balance pve", strategiesRequired);

            strategiesRequired = { "balance", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff balance pve", strategiesRequired);
            
            strategiesRequired = { "balance", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost balance pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost balance pve", strategiesRequired);

            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pve", strategiesRequired);
        }
    };

    // 施放更新PVP策略动作
    class UpdateDruidPvpStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateDruidPvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
        {
            std::vector<std::string> strategiesRequired = { "tank feral/bear/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "tank feral pvp", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe tank feral pvp", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc tank feral pvp", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth tank feral pvp", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure tank feral pvp", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff tank feral pvp", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost tank feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost tank feral pvp", strategiesRequired);

            strategiesRequired = { "dps feral/cat" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "dps feral pvp", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe dps feral pvp", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc dps feral pvp", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth dps feral pvp", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure dps feral pvp", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff dps feral pvp", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost dps feral pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost dps feral pvp", strategiesRequired);

            strategiesRequired = { "restoration/heal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration/heal", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration/heal", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration/heal", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration/heal", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration/heal", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff restoration pvp", strategiesRequired);

            strategiesRequired = { "restoration/heal", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost restoration pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost restoration pvp", strategiesRequired);

            strategiesRequired = { "balance" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "balance pvp", strategiesRequired);

            strategiesRequired = { "balance", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe balance pvp", strategiesRequired);

            strategiesRequired = { "balance", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc balance pvp", strategiesRequired);

            strategiesRequired = { "balance", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth balance pvp", strategiesRequired);

            strategiesRequired = { "balance", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure balance pvp", strategiesRequired);

            strategiesRequired = { "balance", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff balance pvp", strategiesRequired);

            strategiesRequired = { "balance", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost balance pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost balance pvp", strategiesRequired);

            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pvp", strategiesRequired);
        }
    };

    // 施放更新团队副本策略动作
    class UpdateDruidRaidStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateDruidRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
        {
            std::vector<std::string> strategiesRequired = { "tank feral/bear/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "tank feral raid", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe tank feral raid", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc tank feral raid", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth tank feral raid", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure tank feral raid", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff tank feral raid", strategiesRequired);

            strategiesRequired = { "tank feral/bear/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost tank feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost tank feral raid", strategiesRequired);

            strategiesRequired = { "dps feral/cat" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "dps feral raid", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe dps feral raid", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc dps feral raid", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth dps feral raid", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure dps feral raid", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff dps feral raid", strategiesRequired);

            strategiesRequired = { "dps feral/cat", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost dps feral raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost dps feral raid", strategiesRequired);

            strategiesRequired = { "restoration/heal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "restoration raid", strategiesRequired);

            strategiesRequired = { "restoration/heal", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe restoration raid", strategiesRequired);

            strategiesRequired = { "restoration/heal", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc restoration raid", strategiesRequired);

            strategiesRequired = { "restoration/heal", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth restoration raid", strategiesRequired);

            strategiesRequired = { "restoration/heal", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure restoration raid", strategiesRequired);

            strategiesRequired = { "restoration/heal", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff restoration raid", strategiesRequired);

            strategiesRequired = { "restoration/heal", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost restoration raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost restoration raid", strategiesRequired);

            strategiesRequired = { "balance" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "balance raid", strategiesRequired);

            strategiesRequired = { "balance", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe balance raid", strategiesRequired);

            strategiesRequired = { "balance", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc balance raid", strategiesRequired);

            strategiesRequired = { "balance", "stealth" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "stealth balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "stealth balance raid", strategiesRequired);

            strategiesRequired = { "balance", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure balance raid", strategiesRequired);

            strategiesRequired = { "balance", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff balance raid", strategiesRequired);

            strategiesRequired = { "balance", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost balance raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost balance raid", strategiesRequired);

            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal raid", strategiesRequired);
        }
    };
}
