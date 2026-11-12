// 圣骑士 - 触发器头文件 (PaladinTriggers.h)：定义圣骑士增益、减益、冷却及状态检查触发条件
#pragma once
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    // 触发器：缺少圣骑士光环
    class NoPaladinAuraTrigger : public BuffTrigger
    {
    public:
        NoPaladinAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "no paladin aura") {}
        bool IsActive() override;
    };

    // 增益触发器：暗影抗性光环 (ShadowResistanceAuraTrigger)
    BUFF_TRIGGER(ShadowResistanceAuraTrigger, "shadow resistance aura");
    // 增益触发器：冰霜抗性光环 (FrostResistanceAuraTrigger)
    BUFF_TRIGGER(FrostResistanceAuraTrigger, "frost resistance aura");
    // 增益触发器：火焰抗性光环 (FireResistanceAuraTrigger)
    BUFF_TRIGGER(FireResistanceAuraTrigger, "fire resistance aura");
    // 增益触发器：虔诚光环 (DevotionAuraTrigger)
    BUFF_TRIGGER(DevotionAuraTrigger, "devotion aura");
    // 增益触发器：惩罚光环 (RetributionAuraTrigger)
    BUFF_TRIGGER(RetributionAuraTrigger, "retribution aura");
    // 增益触发器：十字军光环 (CrusaderAuraTrigger)
    BUFF_TRIGGER(CrusaderAuraTrigger, "crusader aura");
    // 增益触发器：圣洁光环 (SanctityAuraTrigger)
    BUFF_TRIGGER(SanctityAuraTrigger, "sanctity aura");
    // 增益触发器：专注光环 (ConcentrationAuraTrigger)
    BUFF_TRIGGER(ConcentrationAuraTrigger, "concentration aura");

    // 增益触发器：神圣之盾 (HolyShieldTrigger)
    BUFF_TRIGGER(HolyShieldTrigger, "holy shield");
    // 增益触发器：正义之怒 (RighteousFuryTrigger)
    BUFF_TRIGGER(RighteousFuryTrigger, "righteous fury");

    // 触发器：圣印
    class SealTrigger : public BuffTrigger
    {
    public:
        SealTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "seal") {}
        bool IsActive() override;
    };

    // judgements
    // 减益触发器：审判 (JudgementTrigger)
    DEBUFF_TRIGGER(JudgementTrigger, "judgement");
    // 减益触发器：圣光审判 (JudgementOfLightTrigger)
    DEBUFF_TRIGGER(JudgementOfLightTrigger, "judgement of light");
    // 减益触发器：智慧审判 (JudgementOfWisdomTrigger)
    DEBUFF_TRIGGER(JudgementOfWisdomTrigger, "judgement of wisdom");

    // 触发器：奉献
    class ConsecrationTrigger : public SpellNoCooldownTrigger
    {
    public:
        ConsecrationTrigger(PlayerbotAI* ai) : SpellNoCooldownTrigger(ai, "consecration") {}
        bool IsActive() override;
    };

    // 触发器：驱邪术
    class ExorcismTrigger : public SpellNoCooldownTrigger
    {
    public:
        ExorcismTrigger(PlayerbotAI* ai) : SpellNoCooldownTrigger(ai, "exorcism") {}
        bool IsActive() override;
    };

    // 冷却触发器：十字军打击 (CrusaderStrikeTrigger)
    CD_TRIGGER(CrusaderStrikeTrigger, "crusader strike");

    // repentance triggers
    // 打断敌方治疗触发器：对敌方治疗者施放忏悔 (RepentanceOnHealerTrigger)
    INTERRUPT_HEALER_TRIGGER(RepentanceOnHealerTrigger, "repentance on enemy healer");
    // 减速触发器：对被减速目标施放忏悔 (RepentanceSnareTrigger)
    SNARE_TRIGGER(RepentanceSnareTrigger, "repentance on snare target");
    // 打断触发器：忏悔 (RepentanceInterruptTrigger)
    INTERRUPT_TRIGGER(RepentanceInterruptTrigger, "repentance");

    // 触发器：祝福
    class BlessingOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        BlessingOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "blessing", 4) {}
        bool IsActive() override;
    };

    // 触发器：强效祝福
    class GreaterBlessingOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        GreaterBlessingOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "greater blessing", 4) {}
        bool IsActive() override;
    };

    // 触发器：力量祝福
    class BlessingOfMightOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        BlessingOfMightOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "blessing of might", 4) {}
        bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }

        Value<ObjectGuid>* GetTargetValue() override
        {
            const std::string qualifier = spell + ",greater " + spell + "-" + (ignoreTanks ? "1" : "0");
            return context->GetValue<ObjectGuid>("friendly unit without aura", qualifier);
        }
    };

    // 触发器：强效力量祝福
    class GreaterBlessingOfMightOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        GreaterBlessingOfMightOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "greater blessing of might", "blessing of might", 4) {}
        bool IsActive() override { return (bot->GetMap()->IsDungeon() || bot->GetMap()->IsBattleGround()) && GreaterBuffOnPartyTrigger::IsActive(); }
    };

    // 触发器：智慧祝福
    class BlessingOfWisdomOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        BlessingOfWisdomOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "blessing of wisdom", 4) {}
        bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }

        Value<ObjectGuid>* GetTargetValue() override
        {
            const std::string qualifier = spell + ",greater " + spell + "-" + (ignoreTanks ? "1" : "0");
            return context->GetValue<ObjectGuid>("friendly unit without aura", qualifier);
        }
    };

    // 触发器：强效智慧祝福
    class GreaterBlessingOfWisdomOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        GreaterBlessingOfWisdomOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "greater blessing of wisdom", "blessing of wisdom", 4) {}
        bool IsActive() override { return (bot->GetMap()->IsDungeon() || bot->GetMap()->IsBattleGround()) && GreaterBuffOnPartyTrigger::IsActive(); }
    };

    // 触发器：王者祝福
    class BlessingOfKingsOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        BlessingOfKingsOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "blessing of kings", 4) {}
        bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }

        Value<ObjectGuid>* GetTargetValue() override
        {
            const std::string qualifier = spell + ",greater " + spell + "-" + (ignoreTanks ? "1" : "0");
            return context->GetValue<ObjectGuid>("friendly unit without aura", qualifier);
        }
    };

    // 触发器：强效王者祝福
    class GreaterBlessingOfKingsOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        GreaterBlessingOfKingsOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "greater blessing of kings", "blessing of kings", 4) {}
        bool IsActive() override { return (bot->GetMap()->IsDungeon() || bot->GetMap()->IsBattleGround()) && GreaterBuffOnPartyTrigger::IsActive(); }
    };

    // 触发器：光明祝福
    class BlessingOfLightOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        BlessingOfLightOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "blessing of light", 4) {}
        bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }

        Value<ObjectGuid>* GetTargetValue() override
        {
            const std::string qualifier = spell + ",greater " + spell + "-" + (ignoreTanks ? "1" : "0");
            return context->GetValue<ObjectGuid>("friendly unit without aura", qualifier);
        }
    };

    // 触发器：强效光明祝福
    class GreaterBlessingOfLightOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        GreaterBlessingOfLightOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "greater blessing of light", "blessing of light", 4) {}
        bool IsActive() override { return (bot->GetMap()->IsDungeon() || bot->GetMap()->IsBattleGround()) && GreaterBuffOnPartyTrigger::IsActive(); }
    };

    // 触发器：拯救祝福
    class BlessingOfSalvationOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        BlessingOfSalvationOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "blessing of salvation", 4, true) {}
        bool IsActive() override { return BuffOnPartyTrigger::IsActive(); }

        Value<ObjectGuid>* GetTargetValue() override
        {
            const std::string qualifier = spell + ",greater " + spell + "-" + (ignoreTanks ? "1" : "0");
            return context->GetValue<ObjectGuid>("friendly unit without aura", qualifier);
        }
    };

    // 触发器：强效拯救祝福
    class GreaterBlessingOfSalvationOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        GreaterBlessingOfSalvationOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "greater blessing of salvation", "blessing of salvation", 4, true) {}
        bool IsActive() override { return (bot->GetMap()->IsDungeon() || bot->GetMap()->IsBattleGround()) && GreaterBuffOnPartyTrigger::IsActive(); }
    };

    // 触发器：庇护祝福
    class BlessingOfSanctuaryOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        BlessingOfSanctuaryOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "blessing of sanctuary", 4) {}
        bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }

        Value<ObjectGuid>* GetTargetValue() override
        {
            const std::string qualifier = spell + ",greater " + spell + "-" + (ignoreTanks ? "1" : "0");
            return context->GetValue<ObjectGuid>("friendly unit without aura", qualifier);
        }
    };

    // 触发器：强效庇护祝福
    class GreaterBlessingOfSanctuaryOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        GreaterBlessingOfSanctuaryOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "greater blessing of sanctuary", "blessing of sanctuary", 4) {}
        bool IsActive() override { return (bot->GetMap()->IsDungeon() || bot->GetMap()->IsBattleGround()) && GreaterBuffOnPartyTrigger::IsActive(); }
    };

    // 触发器：十字军审判
    class TargetNoJudgementTrigger : public DebuffOnAttackerTrigger
    {
    public:
        TargetNoJudgementTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "judgement of the crusader") {}
        bool IsActive() override 
        {
            Unit* target = bot->GetTarget();
            if (target)
            {
                return !target->HasAura(21183) && !target->HasAura(20188) &&
                    !target->HasAura(20300) && !target->HasAura(20301) &&
                    !target->HasAura(20302) && !target->HasAura(20303) &&
                    !target->HasAura(27159);
            }

            return false;

        }
    };

    // 触发器：祝福
    class BlessingTrigger : public BuffTrigger
    {
    public:
        BlessingTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blessing", 2) {}
        bool IsActive() override;
    };

    // 触发器：强效祝福
    class GreaterBlessingTrigger : public BuffTrigger
    {
    public:
        GreaterBlessingTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "greater blessing", 2) {}
        bool IsActive() override;
    };

    // 触发器：力量祝福
    class BlessingOfMightTrigger : public BuffTrigger
    {
    public:
        BlessingOfMightTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blessing of might", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }
    };

    // 触发器：强效力量祝福
    class GreaterBlessingOfMightTrigger : public BuffTrigger
    {
    public:
        GreaterBlessingOfMightTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "greater blessing of might", 4) {}

        bool IsActive() override
        {
            if (!bot->GetMap()->IsDungeon() && !bot->GetMap()->IsBattleGround())
                return false;

            Unit* target = GetTarget();
            if (target && target->IsPlayer())
            {
                Player* player = (Player*)target;
                if (bot->IsInGroup(player) && ai->GetBuffedCount((Player*)GetTarget(), spell) < 4)
                {
                    return BuffTrigger::IsActive();
                }
            }

            return false;
        }
    };

    // 触发器：智慧祝福
    class BlessingOfWisdomTrigger : public BuffTrigger
    {
    public:
        BlessingOfWisdomTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blessing of wisdom", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }
    };

    // 触发器：强效智慧祝福
    class GreaterBlessingOfWisdomTrigger : public BuffTrigger
    {
    public:
        GreaterBlessingOfWisdomTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "greater blessing of wisdom", 4) {}

        bool IsActive() override
        {
            if (!bot->GetMap()->IsDungeon() && !bot->GetMap()->IsBattleGround())
                return false;

            Unit* target = GetTarget();
            if (target && target->IsPlayer())
            {
                Player* player = (Player*)target;
                if (bot->IsInGroup(player) && ai->GetBuffedCount((Player*)GetTarget(), spell) < 4)
                {
                    return BuffTrigger::IsActive();
                }
            }

            return false;
        }
    };

    // 触发器：王者祝福
    class BlessingOfKingsTrigger : public BuffTrigger
    {
    public:
        BlessingOfKingsTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blessing of kings", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }
    };

    // 触发器：强效王者祝福
    class GreaterBlessingOfKingsTrigger : public BuffTrigger
    {
    public:
        GreaterBlessingOfKingsTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "greater blessing of kings", 4) {}

        bool IsActive() override
        {
            if (!bot->GetMap()->IsDungeon() && !bot->GetMap()->IsBattleGround())
                return false;

            Unit* target = GetTarget();
            if (target && target->IsPlayer())
            {
                Player* player = (Player*)target;
                if (bot->IsInGroup(player) && ai->GetBuffedCount((Player*)GetTarget(), spell) < 4)
                {
                    return BuffTrigger::IsActive();
                }
            }

            return false;
        }
    };

    // 触发器：光明祝福
    class BlessingOfLightTrigger : public BuffTrigger
    {
    public:
        BlessingOfLightTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blessing of light", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }
    };

    // 触发器：强效光明祝福
    class GreaterBlessingOfLightTrigger : public BuffTrigger
    {
    public:
        GreaterBlessingOfLightTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "greater blessing of light", 4) {}

        bool IsActive() override
        {
            if (!bot->GetMap()->IsDungeon() && !bot->GetMap()->IsBattleGround())
                return false;

            Unit* target = GetTarget();
            if (target && target->IsPlayer())
            {
                Player* player = (Player*)target;
                if (bot->IsInGroup(player) && ai->GetBuffedCount((Player*)GetTarget(), spell) < 4)
                {
                    return BuffTrigger::IsActive();
                }
            }

            return false;
        }
    };

    // 触发器：拯救祝福
    class BlessingOfSalvationTrigger : public BuffTrigger
    {
    public:
        BlessingOfSalvationTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blessing of salvation", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }
    };

    // 触发器：强效拯救祝福
    class GreaterBlessingOfSalvationTrigger : public BuffTrigger
    {
    public:
        GreaterBlessingOfSalvationTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "greater blessing of salvation", 4) {}

        bool IsActive() override
        {
            if (!bot->GetMap()->IsDungeon() && !bot->GetMap()->IsBattleGround())
                return false;

            Unit* target = GetTarget();
            if (target && target->IsPlayer())
            {
                Player* player = (Player*)target;
                if (bot->IsInGroup(player) && ai->GetBuffedCount((Player*)GetTarget(), spell) < 4)
                {
                    return BuffTrigger::IsActive();
                }
            }

            return false;
        }
    };

    // 触发器：庇护祝福
    class BlessingOfSanctuaryTrigger : public BuffTrigger
    {
    public:
        BlessingOfSanctuaryTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blessing of sanctuary", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("greater " + spell, GetTarget()); }
    };

    // 触发器：强效庇护祝福
    class GreaterBlessingOfSanctuaryTrigger : public BuffTrigger
    {
    public:
        GreaterBlessingOfSanctuaryTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "greater blessing of sanctuary", 4) {}

        bool IsActive() override
        {
            if (!bot->GetMap()->IsDungeon() && !bot->GetMap()->IsBattleGround())
                return false;

            Unit* target = GetTarget();
            if (target && target->IsPlayer())
            {
                Player* player = (Player*)target;
                if (bot->IsInGroup(player) && ai->GetBuffedCount((Player*)GetTarget(), spell) < 4)
                {
                    return BuffTrigger::IsActive();
                }
            }

            return false;
        }
    };

    // 触发器：制裁之锤
    class HammerOfJusticeInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        HammerOfJusticeInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "hammer of justice") {}
    };

    // 触发器：制裁之锤
    class HammerOfJusticeSnareTrigger : public SnareTargetTrigger
    {
    public:
        HammerOfJusticeSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "hammer of justice") {}
    };

    // 触发器：对敌方目标施放制裁之锤
    class HammerOfJusticeOnEnemyTrigger : public Trigger
    {
    public:
        HammerOfJusticeOnEnemyTrigger(PlayerbotAI* ai) : Trigger(ai, "hammer of justice on enemy") {}
        virtual bool IsActive() override;
    };

    // 触发器：战争艺术
    class ArtOfWarTrigger : public HasAuraTrigger
    {
    public:
        ArtOfWarTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "the art of war") {}
    };

    // 触发器：清洁术
    class CleanseCureDiseaseTrigger : public NeedCureTrigger
    {
    public:
        CleanseCureDiseaseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse", DISPEL_DISEASE) {}
    };

    // 触发器：清洁术
    class CleanseCurePartyMemberDiseaseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        CleanseCurePartyMemberDiseaseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse", DISPEL_DISEASE) {}
    };

    // 触发器：清洁术
    class CleanseCurePoisonTrigger : public NeedCureTrigger
    {
    public:
        CleanseCurePoisonTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse", DISPEL_POISON) {}
    };

    // 触发器：清洁术
    class CleanseCurePartyMemberPoisonTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        CleanseCurePartyMemberPoisonTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse", DISPEL_POISON) {}
    };

    // 触发器：清洁术
    class CleanseCureMagicTrigger : public NeedCureTrigger
    {
    public:
        CleanseCureMagicTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse", DISPEL_MAGIC) {}
    };

    // 触发器：清洁术
    class CleanseCurePartyMemberMagicTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        CleanseCurePartyMemberMagicTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse", DISPEL_MAGIC) {}
    };

    // 触发器：制裁之锤
    class HammerOfJusticeEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        HammerOfJusticeEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "hammer of justice") {}
    };

    // 触发器：神恩术
    class DivineFavorTrigger : public BuffTrigger
    {
    public:
        DivineFavorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "divine favor") {}
    };

    // 触发器：超度邪恶
    class TurnUndeadTrigger : public HasCcTargetTrigger
    {
    public:
        TurnUndeadTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "turn undead") {}
    };

    // 触发器：牺牲之手
    class HandOfSacrificeTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        HandOfSacrificeTrigger(PlayerbotAI* ai) : PartyMemberLowHealthTrigger(ai, "hand of sacrifice", sPlayerbotAIConfig.criticalHealth, 0, true) {}
    };

    // 触发器：牺牲祝福
    class BlessingOfSacrificeTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        BlessingOfSacrificeTrigger(PlayerbotAI* ai) : PartyMemberLowHealthTrigger(ai, "blessing of sacrifice", sPlayerbotAIConfig.criticalHealth, 0, true) {}
    };

    // 减益触发器：复仇者之盾 (AvengerShieldTrigger)
    DEBUFF_TRIGGER(AvengerShieldTrigger, "avenger's shield");
    // 爆发增益触发器：神圣启示 (DivineIlluminationBoostTrigger)
    BOOST_TRIGGER(DivineIlluminationBoostTrigger, "divine illumination");
}
