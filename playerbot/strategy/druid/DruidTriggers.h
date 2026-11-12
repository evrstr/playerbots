// 德鲁伊 - 触发器头文件 (DruidTriggers.h)：定义德鲁伊增益、减益、冷却及状态检查触发条件
#pragma once
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai 
{
    // 触发器：野性印记
    class MarkOfTheWildOnPartyTrigger : public BuffOnPartyTrigger 
    {
    public:
        MarkOfTheWildOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "mark of the wild", 4) {}
        virtual bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("gift of the wild", GetTarget()); }
    };

    // 触发器：野性印记
    class MarkOfTheWildTrigger : public BuffTrigger 
    {
    public:
        MarkOfTheWildTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "mark of the wild", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("gift of the wild", GetTarget()); }
    };

    // 触发器：野性赐福
    class GiftOfTheWildOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        GiftOfTheWildOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "gift of the wild", "mark of the wild", 4) {}
    };

    // 触发器：荆棘术
    class ThornsOnPartyTrigger : public BuffOnTankTrigger
    {
    public:
        ThornsOnPartyTrigger(PlayerbotAI* ai) : BuffOnTankTrigger(ai, "thorns", 4) {}

        virtual bool IsActive() override
        {
            Unit* target = GetTarget();
            if (target && BuffOnTankTrigger::IsActive() && (!target->IsPlayer() || !ai->IsRanged((Player*)target)))
            {
                // Don't apply thorns if fire shield (conflict) is on the target
                return !ai->HasAura("fire shield", target);
            }

            return false;
        }
    };

    // 触发器：荆棘术
    class ThornsTrigger : public BuffTrigger
    {
    public:
        ThornsTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "thorns", 4) {}

        bool IsActive() override
        {
            if (BuffTrigger::IsActive())
            {
                // Don't apply thorns if fire shield (conflict) is on the target
                return !ai->HasAura("fire shield", GetTarget());
            }

            return false;
        }
    };

    // 触发器：清晰预兆
    class OmenOfClarityTrigger : public BuffTrigger
    {
    public:
        OmenOfClarityTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "omen of clarity") {}
    };

    // 触发器：扫击
    class RakeTrigger : public DebuffTrigger
    {
    public:
        RakeTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "rake") {}
    };

    // 触发器：割裂
    class RipTrigger : public NoDebuffAndComboPointsAvailableTrigger
    {
    public:
        RipTrigger(PlayerbotAI* ai, uint8 comboPoints = 3) : NoDebuffAndComboPointsAvailableTrigger(ai, "rip", comboPoints) {}
    };

    // 触发器：虫群
    class InsectSwarmTrigger : public DebuffTrigger
    {
    public:
        InsectSwarmTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "insect swarm") {}
    };

    // 触发器：月火术
    class MoonfireTrigger : public DebuffTrigger
    {
    public:
        MoonfireTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "moonfire") {}
        virtual bool IsActive() override { return DebuffTrigger::IsActive() && !GetTarget()->IsRooted(); }
    };

    // 触发器：精灵之火
    class FaerieFireTrigger : public DebuffTrigger
    {
    public:
        FaerieFireTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "faerie fire") {}
    };

    // 触发器：精灵之火(野性)
    class FaerieFireFeralTrigger : public DebuffTrigger
    {
    public:
        FaerieFireFeralTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "faerie fire (feral)") {}
    };

    // 触发器：挫志咆哮
    class DemoralizingRoarTrigger : public DebuffTrigger
    {
    public:
        DemoralizingRoarTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "demoralizing roar") {}
        virtual bool IsActive() override { return DebuffTrigger::IsActive() && !ai->HasAura("demoralizing shout", GetTarget()); }
    };

    // 触发器：重击
    class BashInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        BashInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "bash") {}
    };

    // 触发器：猛虎之怒
    class TigersFuryTrigger : public BoostTrigger
    {
    public:
        TigersFuryTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "tiger's fury") {}
    };

    // 触发器：自然之握
    class NaturesGraspTrigger : public BoostTrigger
    {
    public:
        NaturesGraspTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "nature's grasp") {}
    };

    // 触发器：纠缠根须
    class EntanglingRootsTrigger : public HasCcTargetTrigger
    {
    public:
        EntanglingRootsTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "entangling roots") {}
    };

    // 触发器：纠缠根须
    class EntanglingRootsKiteTrigger : public DebuffTrigger
    {
    public:
        EntanglingRootsKiteTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "entangling roots") {}
        virtual bool IsActive() override;
    };

    // 触发器：纠缠根须
    class EntanglingRootsSnareTrigger : public SnareTargetTrigger
    {
    public:
        EntanglingRootsSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "entangling roots", 5) {}
    };

    // 触发器：休眠
    class HibernateTrigger : public HasCcTargetTrigger
    {
    public:
        HibernateTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "hibernate") {}
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

    // 驱散触发器：解除诅咒 (RemoveCurseTrigger)
    CURE_TRIGGER(RemoveCurseTrigger, "remove curse", DISPEL_CURSE);
    // 队友驱散触发器：解除诅咒 (RemoveCurseOnPartyTrigger)
    CURE_PARTY_TRIGGER(RemoveCurseOnPartyTrigger, "remove curse", DISPEL_CURSE);

    // 触发器：熊形态
    class BearFormTrigger : public BuffTrigger
    {
    public:
        BearFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "bear form") {}
        virtual bool IsActive() override { return !ai->HasAnyAuraOf(bot, "bear form", "dire bear form", NULL); }
    };

    // 触发器：生命之树
    class TreeFormTrigger : public BuffTrigger
    {
    public:
        TreeFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "tree of life") {}
        virtual bool IsActive() override { return !ai->HasAura("tree of life", bot); }
    };

    // 触发器：枭兽形态
    class MoonkinFormTrigger : public BuffTrigger
    {
    public:
        MoonkinFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "moonkin form") {}
        virtual bool IsActive() override { return !ai->HasAura("moonkin form", bot); }
    };

    // 触发器：猎豹形态
    class CatFormTrigger : public BuffTrigger
    {
    public:
        CatFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "cat form") {}
        virtual bool IsActive() override { return !ai->HasAura("cat form", bot); }
    };

    // 触发器：日蚀
    class EclipseSolarTrigger : public HasAuraTrigger
    {
    public:
        EclipseSolarTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "eclipse (solar)") {}
    };

    // 触发器：月蚀
    class EclipseLunarTrigger : public HasAuraTrigger
    {
    public:
        EclipseLunarTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "eclipse (lunar)") {}
    };

    // 触发器：重击
    class BashInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        BashInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "bash") {}
    };

    // 触发器：自然迅捷
    class NaturesSwiftnessTrigger : public BuffTrigger
    {
    public:
        NaturesSwiftnessTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "nature's swiftness") {}
    };

    // 触发器：狂怒
    class EnrageTrigger : public BuffTrigger
    {
    public:
        EnrageTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "enrage") {}

    private:
        bool IsActive() override
        {
            return AI_VALUE2(uint8, "health", "self target") >= sPlayerbotAIConfig.mediumHealth &&
                   AI_VALUE2(uint8, "rage", "self target") < 20;
        }
    };

    // 触发器：割伤
    class LacerateTrigger : public DebuffTrigger
    {
    public:
        LacerateTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "lacerate") {}

    private:
        bool IsActive() override
        {
            Unit* target = GetTarget();
            return target && !ai->HasAura("lacerate", target, true) && !HasMaxDebuffs();
        }
    };

    // 触发器：潜行
    class InStealthTrigger : public HasAuraTrigger
    {
    public:
        InStealthTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "prowl") {}
    };

    // 触发器：潜行
    class NoStealthTrigger : public HasNoAuraTrigger
    {
    public:
        NoStealthTrigger(PlayerbotAI* ai) : HasNoAuraTrigger(ai, "prowl")
        {
            checkInterval = 2;
        }
    };

    // 触发器：潜行
    class DruidUnstealthTrigger : public BuffTrigger
    {
    public:
        DruidUnstealthTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "prowl", 2) {}

        bool IsActive() override
        {
            if (ai->HasAura("prowl", bot) && !bot->InBattleGround())
            {
                if (!AI_VALUE(bool, "has attackers") && !AI_VALUE(bool, "has enemy player targets"))
                {
                    if (AI_VALUE2(bool, "moving", "self target"))
                    {
                        if (ai->GetMaster())
                        {
                            return sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), 10.0f);
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }
    };

    // 触发器：潜行
    class StealthTrigger : public Trigger
    {
    public:
        StealthTrigger(PlayerbotAI* ai) : Trigger(ai, "prowl") {}

        bool IsActive() override
        {
            if (ai->HasAura("prowl", bot) || sServerFacade.IsInCombat(bot) || !sServerFacade.IsSpellReady(bot, 5215))
            {
                return false;
            }

            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "enemy player target"));
            if (!target)
            {
                target = ai->GetUnit(AI_VALUE(ObjectGuid, "grind target"));
            }
            if (!target)
            {
                target = ai->GetUnit(AI_VALUE(ObjectGuid, "dps target"));
            }
            if (!target)
            {
                return false;
            }

            float distance = 30.0f;
            if (target && target->GetVictim())
            {
                distance -= 10;
            }

            if (sServerFacade.isMoving(target) && target->GetVictim())
            {
                distance -= 10;
            }

            if (bot->InBattleGround())
            {
                distance += 20;
            }

#ifndef MANGOSBOT_ZERO
            if (bot->InArena())
            {
                distance += 20;
            }
#endif

            return (target && sServerFacade.GetDistance2d(bot, target) < distance);
        }
    };

    // 触发器：变身解控/回能
    class PowershiftTrigger : public Trigger
    {
    public:
        PowershiftTrigger(PlayerbotAI* ai) : Trigger(ai, "powershift") {}

        bool IsActive() override
        {
            if (ai->HasAura("cat form", bot) &&
                AI_VALUE2(uint8, "energy", "self target") < 20 &&
                AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana)
            {
                return true;
            }

            return false;
        }
    };

    // 触发器：凶猛撕咬
    class FerociousBiteTrigger : public ComboPointsAvailableTrigger
    {
    public:
        FerociousBiteTrigger(PlayerbotAI* ai) : ComboPointsAvailableTrigger(ai, 5) {}
    };

    // 触发器：复生
    class RebirthTrigger : public SpellTargetTrigger
    {
    public:
        RebirthTrigger(PlayerbotAI* ai) : SpellTargetTrigger(ai, "rebirth", "revive targets") {}
        std::string GetTargetName() override { return "party member to resurrect"; }

        bool IsTargetValid(Unit* target) override 
        { 
            return SpellTargetTrigger::IsTargetValid(target) && target->IsDead(); 
        }
    };

    // 触发器：激活
    class InnervateTrigger : public SpellTargetTrigger
    {
    public:
        InnervateTrigger(PlayerbotAI* ai) : SpellTargetTrigger(ai, "innervate", "boost targets", true, true) {}
        std::string GetTargetName() override { return "self target"; }

        bool IsTargetValid(Unit* target) override
        {
            if (SpellTargetTrigger::IsTargetValid(target))
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

    // 触发器：生命绽放
    class LifebloomTankTrigger : public Trigger
    {
    public:
        explicit LifebloomTankTrigger(PlayerbotAI* ai) : Trigger(ai, "lifebloom", 1) {}

        Value<ObjectGuid>* GetTargetValue() override;
        bool IsActive() override
        {
            Unit* target = GetTarget();
            return target
                && ai->IsTank((Player*)target)                                          //target is tank 
                && target->IsAlive()                                                    //target is alive
                && !ai->HasAura("lifebloom", target, true, true, -1, false, 2000, 8)    //target dont have max stacked aura or aura will expire soon
                && ai->CanCastSpell("lifebloom", target, 0)                             //bot can cast spell
                && !target->getAttackers().empty();                                     //target have attackers
        }
    };

    // 触发器：节能施法
    class ClearcastingTrigger : public HasAuraTrigger
    {
    public:
        ClearcastingTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "clearcasting") {}
    };
}
