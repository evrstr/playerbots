// 牧师 - 触发器头文件 (PriestTriggers.h)：定义牧师增益、减益、冷却及状态检查触发条件
#pragma once

#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    // 减益触发器：神圣之火 (HolyFireTrigger)
    DEBUFF_TRIGGER(HolyFireTrigger, "holy fire");
    // 减益触发器：暗言术：痛 (PowerWordPainTrigger)
    DEBUFF_TRIGGER(PowerWordPainTrigger, "shadow word: pain");
    // 敌方减益触发器：暗言术：痛 (PowerWordPainOnAttackerTrigger)
    DEBUFF_ENEMY_TRIGGER(PowerWordPainOnAttackerTrigger, "shadow word: pain");
    // 减益触发器：吸血鬼之触 (VampiricTouchTrigger)
    DEBUFF_TRIGGER(VampiricTouchTrigger, "vampiric touch");
    // 敌方减益触发器：吸血鬼之触 (VampiricTouchOnAttackerTrigger)
    DEBUFF_ENEMY_TRIGGER(VampiricTouchOnAttackerTrigger, "vampiric touch");
    // 减益触发器：吸血鬼的拥抱 (VampiricEmbraceTrigger)
    DEBUFF_TRIGGER(VampiricEmbraceTrigger, "vampiric embrace");
    // 驱散触发器：驱散魔法 (DispelMagicTrigger)
    CURE_TRIGGER(DispelMagicTrigger, "dispel magic", DISPEL_MAGIC);
    // 队友驱散触发器：驱散魔法 (DispelMagicPartyMemberTrigger)
    CURE_PARTY_TRIGGER(DispelMagicPartyMemberTrigger, "dispel magic", DISPEL_MAGIC);
    // 驱散触发器：祛病术 (CureDiseaseTrigger)
    CURE_TRIGGER(CureDiseaseTrigger, "cure disease", DISPEL_DISEASE);
    // 队友驱散触发器：祛病术 (PartyMemberCureDiseaseTrigger)
    CURE_PARTY_TRIGGER(PartyMemberCureDiseaseTrigger, "cure disease", DISPEL_DISEASE);
    // 增益触发器(带条件)：心灵之火 (InnerFireTrigger)
    BUFF_TRIGGER_A(InnerFireTrigger, "inner fire");
    // 增益触发器(带条件)：暗影形态 (ShadowformTrigger)
    BUFF_TRIGGER_A(ShadowformTrigger, "shadowform");
    // 爆发增益触发器(带条件)：心灵专注 (InnerFocusTrigger)
    BOOST_TRIGGER_A(InnerFocusTrigger, "inner focus");
    // 控制技能触发器：束缚亡灵 (ShackleUndeadTrigger)
    CC_TRIGGER(ShackleUndeadTrigger, "shackle undead");
    // 打断触发器：沉默 (SilenceTrigger)
    INTERRUPT_TRIGGER(SilenceTrigger, "silence");
    // 打断敌方治疗触发器：沉默 (SilenceEnemyHealerTrigger)
    INTERRUPT_HEALER_TRIGGER(SilenceEnemyHealerTrigger, "silence");

    // racials
    // 减益触发器：噬灵疫病 (DevouringPlagueTrigger)
    DEBUFF_TRIGGER(DevouringPlagueTrigger, "devouring plague");
    // 增益触发器：虚弱之触 (TouchOfWeaknessTrigger)
    BUFF_TRIGGER(TouchOfWeaknessTrigger, "touch of weakness");
    // 减益触发器：虚弱妖术 (HexOfWeaknessTrigger)
    DEBUFF_TRIGGER(HexOfWeaknessTrigger, "hex of weakness");
    // 法术反射/反制触发器：回馈 (FeedbackTrigger)
    DEFLECT_TRIGGER(FeedbackTrigger, "feedback");
    // 减速触发器：责罚 (ChastiseTrigger)
    SNARE_TRIGGER(ChastiseTrigger, "chastise");
    // 减益触发器：星辰碎片 (StarshardsTrigger)
    DEBUFF_TRIGGER(StarshardsTrigger, "starshards");

    // 爆发增益触发器(带条件)：暗影恶魔 (ShadowfiendTrigger)
    BOOST_TRIGGER_A(ShadowfiendTrigger, "shadowfiend");
    // 可施法检查触发器：心灵震爆 (MindBlastTrigger)
    CAN_CAST_TRIGGER(MindBlastTrigger, "mind blast");
    // 可施法检查触发器：惩击 (SmiteTrigger)
    CAN_CAST_TRIGGER(SmiteTrigger, "smite");

    // 触发器：暗影守卫
    class ShadowguardTrigger : public BuffTrigger
    {
    public:
        ShadowguardTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "shadowguard", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && bot->getRace() == RACE_TROLL; }
    };

    // 触发器：真言术：韧
    class PowerWordFortitudeOnPartyTrigger : public BuffOnPartyTrigger 
    {
    public:
        PowerWordFortitudeOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "power word: fortitude", 4) {}
        virtual bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("prayer of fortitude", GetTarget()); }
    };

    // 触发器：真言术：韧
    class PowerWordFortitudeTrigger : public BuffTrigger 
    {
    public:
        PowerWordFortitudeTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "power word: fortitude", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("prayer of fortitude", GetTarget()); }
    };

    // 触发器：神圣之灵
    class DivineSpiritOnPartyTrigger : public BuffOnPartyTrigger 
    {
    public:
        DivineSpiritOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "divine spirit", 4) {}
        virtual bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("prayer of spirit", GetTarget()); }
    };

    // 触发器：神圣之灵
    class DivineSpiritTrigger : public BuffTrigger 
    {
    public:
        DivineSpiritTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "divine spirit", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("prayer of spirit", GetTarget()); }
    };

    // 触发器：暗影防护
    class ShadowProtectionOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        ShadowProtectionOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "shadow protection", 4) {}
        virtual bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("prayer of shadow protection", GetTarget()); }
    };

    // 触发器：暗影防护
    class ShadowProtectionTrigger : public BuffTrigger 
    {
    public:
        ShadowProtectionTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "shadow protection", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("prayer of shadow protection", GetTarget()); }
    };

    // 触发器：坚韧祷言
    class PrayerOfFortitudeOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        PrayerOfFortitudeOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "prayer of fortitude", "power word: fortitude", 4) {}
    };

    // 触发器：精神祷言
    class PrayerOfSpiritOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        PrayerOfSpiritOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "prayer of spirit", "divine spirit", 4) {}
    };

    // 触发器：暗影防护祷言
    class PrayerOfShadowProtectionOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        PrayerOfShadowProtectionOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "prayer of shadow protection", "shadow protection", 4) {}
    };

    // 触发器：联结治疗
    class BindingHealTrigger : public PartyMemberLowHealthTrigger 
    {
    public:
        BindingHealTrigger(PlayerbotAI* ai) : PartyMemberLowHealthTrigger(ai, "binding heal", sPlayerbotAIConfig.lowHealth, 0) {}

        virtual bool IsActive() override
        {
            return PartyMemberLowHealthTrigger::IsActive() && AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.mediumHealth;
        }
    };

    // 触发器：能量灌注
    class PowerInfusionTrigger : public SpellTargetTrigger
    {
    public:
        PowerInfusionTrigger(PlayerbotAI* ai) : SpellTargetTrigger(ai, "power infusion", "boost targets", true, true) {}
        std::string GetTargetName() override { return "self target"; }
    };

    // 触发器：防护恐惧结界
    class FearWardTrigger : public SpellTargetTrigger
    {
    public:
        FearWardTrigger(PlayerbotAI* ai) : SpellTargetTrigger(ai, "fear ward", "buff targets", true, true) {}
        std::string GetTargetName() override { return "self target"; }
    };
}
