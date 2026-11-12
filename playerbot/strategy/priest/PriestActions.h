// 牧师 - 动作头文件 (PriestActions.h)：定义牧师专用技能施放与战斗动作
#pragma once
#include "playerbot/strategy/actions/GenericActions.h"

namespace ai
{
    // disc
    // 自我增益动作：真言术：韧 (CastPowerWordFortitudeAction)
    BUFF_ACTION(CastPowerWordFortitudeAction, "power word: fortitude");
    // 队友增益动作：真言术：韧 (CastPowerWordFortitudeOnPartyAction)
    BUFF_PARTY_ACTION(CastPowerWordFortitudeOnPartyAction, "power word: fortitude");
    // 团队强效祝福动作：坚韧祷言 (CastPrayerOfFortitudeOnPartyAction)
    GREATER_BUFF_PARTY_ACTION(CastPrayerOfFortitudeOnPartyAction, "prayer of fortitude", "power word: fortitude");
    // 自我增益动作：真言术：盾 (CastPowerWordShieldAction)
    BUFF_ACTION(CastPowerWordShieldAction, "power word: shield");
    // 队友治疗动作：真言术：盾 (CastPowerWordShieldOnPartyAction)
    HEAL_PARTY_ACTION(CastPowerWordShieldOnPartyAction, "power word: shield");
    // 自我增益动作：心灵之火 (CastInnerFireAction)
    BUFF_ACTION(CastInnerFireAction, "inner fire");
    // 自我驱散净化动作：驱散魔法 (CastDispelMagicAction)
    CURE_ACTION(CastDispelMagicAction, "dispel magic");
    // 队友驱散净化动作：驱散魔法 (CastDispelMagicOnPartyAction)
    CURE_PARTY_ACTION(CastDispelMagicOnPartyAction, "dispel magic", DISPEL_MAGIC);
    // 法术施放动作：驱散魔法 (CastDispelMagicOnTargetAction)
    SPELL_ACTION(CastDispelMagicOnTargetAction, "dispel magic");
    // 控制技能(CC)动作：束缚亡灵 (CastShackleUndeadAction)
    CC_ACTION(CastShackleUndeadAction, "shackle undead");
    // 条件法术施放动作：法力燃烧 (CastManaBurnAction)
    SPELL_ACTION_U(CastManaBurnAction, "mana burn", AI_VALUE2(uint8, "mana", "self target") < 50 && AI_VALUE2(uint8, "mana", "current target") >= 20);
    // 自我增益动作：漂浮术 (CastLevitateAction)
    BUFF_ACTION(CastLevitateAction, "levitate");
    // 自我增益动作：神圣之灵 (CastDivineSpiritAction)
    BUFF_ACTION(CastDivineSpiritAction, "divine spirit");
    // 队友增益动作：神圣之灵 (CastDivineSpiritOnPartyAction)
    BUFF_PARTY_ACTION(CastDivineSpiritOnPartyAction, "divine spirit");
    // 团队强效祝福动作：精神祷言 (CastPrayerOfSpiritOnPartyAction)
    GREATER_BUFF_PARTY_ACTION(CastPrayerOfSpiritOnPartyAction, "prayer of spirit", "divine spirit");
    //disc 2.4.3
    // 法术施放动作：群体驱散 (CastMassDispelAction)
    SPELL_ACTION(CastMassDispelAction, "mass dispel");

    // disc talents
    // 自我增益动作：心灵专注 (CastInnerFocusAction)
    BUFF_ACTION(CastInnerFocusAction, "inner focus");
    // disc 2.4.3 talents
    // 自我增益动作：痛苦压制 (CastPainSuppressionAction)
    BUFF_ACTION(CastPainSuppressionAction, "pain suppression");
    // 保护技能动作：痛苦压制 (CastPainSuppressionProtectAction)
    PROTECT_ACTION(CastPainSuppressionProtectAction, "pain suppression");

    // holy
    // 单体治疗动作：次级治疗术 (CastLesserHealAction)
    HEAL_ACTION(CastLesserHealAction, "lesser heal");
    // 队友治疗动作：次级治疗术 (CastLesserHealOnPartyAction)
    HEAL_PARTY_ACTION(CastLesserHealOnPartyAction, "lesser heal");
    // 单体治疗动作：治疗术 (CastHealAction)
    HEAL_ACTION(CastHealAction, "heal");
    // 队友治疗动作：治疗术 (CastHealOnPartyAction)
    HEAL_PARTY_ACTION(CastHealOnPartyAction, "heal");
    // 单体治疗动作：强效治疗术 (CastGreaterHealAction)
    HEAL_ACTION(CastGreaterHealAction, "greater heal");
    // 队友治疗动作：强效治疗术 (CastGreaterHealOnPartyAction)
    HEAL_PARTY_ACTION(CastGreaterHealOnPartyAction, "greater heal");
    // 单体治疗动作：快速治疗 (CastFlashHealAction)
    HEAL_ACTION(CastFlashHealAction, "flash heal");
    // 队友治疗动作：快速治疗 (CastFlashHealOnPartyAction)
    HEAL_PARTY_ACTION(CastFlashHealOnPartyAction, "flash heal");
    // 单体治疗动作：恢复 (CastRenewAction)
    HEAL_ACTION(CastRenewAction, "renew");
    // 队友持续治疗(HoT)动作：恢复 (CastRenewOnPartyAction)
    HEAL_HOT_PARTY_ACTION(CastRenewOnPartyAction, "renew");
    // holy 2.4.3
    // 队友治疗动作：愈合祷言 (CastPrayerOfMendingAction)
    HEAL_PARTY_ACTION(CastPrayerOfMendingAction, "prayer of mending");
    // 队友治疗动作：联结治疗 (CastBindingHealAction)
    HEAL_PARTY_ACTION(CastBindingHealAction, "binding heal");
    
    // 自我增益动作：治疗祷言 (CastPrayerOfHealingAction)
    BUFF_ACTION(CastPrayerOfHealingAction, "prayer of healing");
    // 群体治疗动作：光明之泉 (CastLightwellAction)
    AOE_HEAL_ACTION(CastLightwellAction, "lightwell");
    // 群体治疗动作：治疗之环 (CastCircleOfHealingAction)
    AOE_HEAL_ACTION(CastCircleOfHealingAction, "circle of healing");

    // 法术施放动作：惩击 (CastSmiteAction)
    SPELL_ACTION(CastSmiteAction, "smite");
    // 法术施放动作：神圣新星 (CastHolyNovaAction)
    SPELL_ACTION(CastHolyNovaAction, "holy nova");

    // 复活目标动作：复活术 (CastResurrectionAction)
    RESS_ACTION(CastResurrectionAction, "resurrection");

    // 自我驱散净化动作：祛病术 (CastCureDiseaseAction)
    CURE_ACTION(CastCureDiseaseAction, "cure disease");
    // 队友驱散净化动作：祛病术 (CastCureDiseaseOnPartyAction)
    CURE_PARTY_ACTION(CastCureDiseaseOnPartyAction, "cure disease", DISPEL_DISEASE);
    // 自我驱散净化动作：驱除疾病 (CastAbolishDiseaseAction)
    CURE_ACTION(CastAbolishDiseaseAction, "abolish disease");
    // 队友驱散净化动作：驱除疾病 (CastAbolishDiseaseOnPartyAction)
    CURE_PARTY_ACTION(CastAbolishDiseaseOnPartyAction, "abolish disease", DISPEL_DISEASE);

    // 远程减益技能动作：神圣之火 (CastHolyFireAction)
    RANGED_DEBUFF_ACTION(CastHolyFireAction, "holy fire");

    // shadow
    // 远程减益技能动作：暗言术：痛 (CastPowerWordPainAction)
    RANGED_DEBUFF_ACTION(CastPowerWordPainAction, "shadow word: pain");
    // 对敌方目标远程减益动作：暗言术：痛 (CastPowerWordPainOnAttackerAction)
    RANGED_DEBUFF_ENEMY_ACTION(CastPowerWordPainOnAttackerAction, "shadow word: pain");
    // 法术施放动作：心灵震爆 (CastMindBlastAction)
    SPELL_ACTION(CastMindBlastAction, "mind blast");
    // 法术施放动作：心灵尖啸 (CastPsychicScreamAction)
    SPELL_ACTION(CastPsychicScreamAction, "psychic scream");
    // 远程减益技能动作：安抚心灵 (CastMindSootheAction)
    RANGED_DEBUFF_ACTION(CastMindSootheAction, "mind soothe");
    // 条件自我增益动作：渐隐术 (CastFadeAction)
    BUFF_ACTION_U(CastFadeAction, "fade", bot->GetGroup());
    // 自我增益动作：暗影防护 (CastShadowProtectionAction)
    BUFF_ACTION(CastShadowProtectionAction, "shadow protection");
    // 队友增益动作：暗影防护 (CastShadowProtectionOnPartyAction)
    BUFF_PARTY_ACTION(CastShadowProtectionOnPartyAction, "shadow protection");
    // 团队强效祝福动作：暗影防护祷言 (CastPrayerOfShadowProtectionAction)
    GREATER_BUFF_PARTY_ACTION(CastPrayerOfShadowProtectionAction, "prayer of shadow protection", "shadow protection");
    // shadow 2.4.3
    // 自我增益动作：暗影恶魔 (CastShadowfiendAction)
    BUFF_ACTION(CastShadowfiendAction, "shadowfiend");
    // 法术施放动作：暗言术：灭 (CastShadowWordDeathAction)
    SPELL_ACTION(CastShadowWordDeathAction, "shadow word: death");

    // shadow talents
    // 法术施放动作：精神鞭笞 (CastMindFlayAction)
    SPELL_ACTION(CastMindFlayAction, "mind flay");
    // 远程减益技能动作：吸血鬼的拥抱 (CastVampiricEmbraceAction)
    RANGED_DEBUFF_ACTION(CastVampiricEmbraceAction, "vampiric embrace");
    // 自我增益动作：暗影形态 (CastShadowformAction)
    BUFF_ACTION(CastShadowformAction, "shadowform");
    // 法术施放动作：沉默 (CastSilenceAction)
    SPELL_ACTION(CastSilenceAction, "silence");
    // 针对敌方治疗动作：沉默 (CastSilenceOnEnemyHealerAction)
    ENEMY_HEALER_ACTION(CastSilenceOnEnemyHealerAction, "silence");
    // shadow talents 2.4.3
    // 远程减益技能动作：吸血鬼之触 (CastVampiricTouchAction)
    RANGED_DEBUFF_ACTION(CastVampiricTouchAction, "vampiric touch");
    // 对敌方目标远程减益动作：对攻击者施放吸血鬼之触 (CastVampiricTouchActionOnAttacker)
    RANGED_DEBUFF_ENEMY_ACTION(CastVampiricTouchActionOnAttacker, "vampiric touch on attacker");

    // racials
    // 远程减益技能动作：噬灵疫病 (CastDevouringPlagueAction)
    RANGED_DEBUFF_ACTION(CastDevouringPlagueAction, "devouring plague");
    // 自我增益动作：虚弱之触 (CastTouchOfWeaknessAction)
    BUFF_ACTION(CastTouchOfWeaknessAction, "touch of weakness");
    // 远程减益技能动作：虚弱妖术 (CastHexOfWeaknessAction)
    RANGED_DEBUFF_ACTION(CastHexOfWeaknessAction, "hex of weakness");
    // 自我增益动作：暗影守卫 (CastShadowguardAction)
    BUFF_ACTION(CastShadowguardAction, "shadowguard");
    // 单体治疗动作：绝望祷言 (CastDesperatePrayerAction)
    HEAL_ACTION(CastDesperatePrayerAction, "desperate prayer");
    // 条件法术施放动作：星辰碎片 (CastStarshardsAction)
    SPELL_ACTION_U(CastStarshardsAction, "starshards", (AI_VALUE2(uint8, "mana", "self target") > 50 && ai->GetUnit(AI_VALUE(ObjectGuid, "current target")) && AI_VALUE2(float, "distance", "current target") > 15.0f));
    // 自我增益动作：艾露恩的赐福 (CastElunesGraceAction)
    BUFF_ACTION(CastElunesGraceAction, "elune's grace");
    // 自我增益动作：回馈 (CastFeedbackAction)
    BUFF_ACTION(CastFeedbackAction, "feedback");
    // 自我增益动作：希望符记 (CastSymbolOfHopeAction)
    BUFF_ACTION(CastSymbolOfHopeAction, "symbol of hope");
    // 法术施放动作：吞噬魔法 (CastConsumeMagicAction)
    SPELL_ACTION(CastConsumeMagicAction, "consume magic");
    // 减速技能动作：责罚 (CastChastiseAction)
    SNARE_ACTION(CastChastiseAction, "chastise");

    // 施放取消暗影形态动作
    class CastRemoveShadowformAction : public Action 
    {
    public:
        CastRemoveShadowformAction(PlayerbotAI* ai) : Action(ai, "remove shadowform") {}
        virtual bool isUseful() override { return ai->HasAura("shadowform", ai->GetUnit(AI_VALUE(ObjectGuid, "self target"))); }
        virtual bool isPossible() { return true; }

        virtual bool Execute(Event& event) override
        {
            ai->RemoveAura("shadowform");
            return true;
        }
    };

    // 施放能量灌注动作
    class CastPowerInfusionAction : public CastSpellTargetAction
    {
    public:
        CastPowerInfusionAction(PlayerbotAI* ai) : CastSpellTargetAction(ai, "power infusion", "boost targets", true, true) {}
        std::string GetTargetName() override { return "self target"; }
    };

    // 施放防护恐惧结界动作
    class CastFearWardAction : public CastSpellTargetAction
    {
    public:
        CastFearWardAction(PlayerbotAI* ai) : CastSpellTargetAction(ai, "fear ward", "buff targets", true, true) {}
        std::string GetTargetName() override { return "self target"; }
    };
}

// 施放更新PVE策略动作
class UpdatePriestPveStrategiesAction : public UpdateStrategyDependenciesAction
{
public:
    UpdatePriestPveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
    {
        std::vector<std::string> strategiesRequired = { "holy/heal" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "holy pve", strategiesRequired);

        strategiesRequired = { "holy/heal", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe holy pve", strategiesRequired);

        strategiesRequired = { "holy/heal", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure holy pve", strategiesRequired);

        strategiesRequired = { "holy/heal", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff holy pve", strategiesRequired);

        strategiesRequired = { "holy/heal", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost holy pve", strategiesRequired);

        strategiesRequired = { "holy/heal", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc holy pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc holy pve", strategiesRequired);

        strategiesRequired = { "shadow/dps" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "shadow pve", strategiesRequired);

        strategiesRequired = { "shadow/dps", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe shadow pve", strategiesRequired);

        strategiesRequired = { "shadow/dps", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure shadow pve", strategiesRequired);

        strategiesRequired = { "shadow/dps", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff shadow pve", strategiesRequired);

        strategiesRequired = { "shadow/dps", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost shadow pve", strategiesRequired);

        strategiesRequired = { "shadow/dps", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc shadow pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc shadow pve", strategiesRequired);

        strategiesRequired = { "discipline" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "discipline pve", strategiesRequired);

        strategiesRequired = { "discipline", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe discipline pve", strategiesRequired);

        strategiesRequired = { "discipline", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure discipline pve", strategiesRequired);

        strategiesRequired = { "discipline", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff discipline pve", strategiesRequired);

        strategiesRequired = { "discipline", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost discipline pve", strategiesRequired);

        strategiesRequired = { "discipline", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc discipline pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc discipline pve", strategiesRequired);

        strategiesRequired = { "offheal" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pve", strategiesRequired);

        strategiesRequired = { "offdps" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offdps pve", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offdps pve", strategiesRequired);
    }
};

// 施放更新PVP策略动作
class UpdatePriestPvpStrategiesAction : public UpdateStrategyDependenciesAction
{
public:
    UpdatePriestPvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
    {
        std::vector<std::string> strategiesRequired = { "holy/heal" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "holy pvp", strategiesRequired);

        strategiesRequired = { "holy/heal", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe holy pvp", strategiesRequired);

        strategiesRequired = { "holy/heal", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure holy pvp", strategiesRequired);

        strategiesRequired = { "holy/heal", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff holy pvp", strategiesRequired);

        strategiesRequired = { "holy/heal", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost holy pvp", strategiesRequired);

        strategiesRequired = { "holy/heal", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc holy pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc holy pvp", strategiesRequired);

        strategiesRequired = { "shadow/dps" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "shadow pvp", strategiesRequired);

        strategiesRequired = { "shadow/dps", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe shadow pvp", strategiesRequired);

        strategiesRequired = { "shadow/dps", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure shadow pvp", strategiesRequired);

        strategiesRequired = { "shadow/dps", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff shadow pvp", strategiesRequired);

        strategiesRequired = { "shadow/dps", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost shadow pvp", strategiesRequired);

        strategiesRequired = { "shadow/dps", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc shadow pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc shadow pvp", strategiesRequired);

        strategiesRequired = { "discipline" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "discipline pvp", strategiesRequired);

        strategiesRequired = { "discipline", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe discipline pvp", strategiesRequired);

        strategiesRequired = { "discipline", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure discipline pvp", strategiesRequired);

        strategiesRequired = { "discipline", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff discipline pvp", strategiesRequired);

        strategiesRequired = { "discipline", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost discipline pvp", strategiesRequired);

        strategiesRequired = { "discipline", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc discipline pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc discipline pvp", strategiesRequired);

        strategiesRequired = { "offheal" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pvp", strategiesRequired);

        strategiesRequired = { "offdps" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offdps pvp", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offdps pvp", strategiesRequired);
    }
};

// 施放更新团队副本策略动作
class UpdatePriestRaidStrategiesAction : public UpdateStrategyDependenciesAction
{
public:
    UpdatePriestRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
    {
        std::vector<std::string> strategiesRequired = { "holy/heal" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "holy raid", strategiesRequired);

        strategiesRequired = { "holy/heal", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe holy raid", strategiesRequired);

        strategiesRequired = { "holy/heal", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure holy raid", strategiesRequired);

        strategiesRequired = { "holy/heal", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff holy raid", strategiesRequired);

        strategiesRequired = { "holy/heal", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost holy raid", strategiesRequired);

        strategiesRequired = { "holy/heal", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc holy raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc holy raid", strategiesRequired);

        strategiesRequired = { "shadow/dps" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "shadow raid", strategiesRequired);

        strategiesRequired = { "shadow/dps", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe shadow raid", strategiesRequired);

        strategiesRequired = { "shadow/dps", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure shadow raid", strategiesRequired);

        strategiesRequired = { "shadow/dps", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff shadow raid", strategiesRequired);

        strategiesRequired = { "shadow/dps", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost shadow raid", strategiesRequired);

        strategiesRequired = { "shadow/dps", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc shadow raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc shadow raid", strategiesRequired);

        strategiesRequired = { "discipline" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "discipline raid", strategiesRequired);

        strategiesRequired = { "discipline", "aoe" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe discipline raid", strategiesRequired);

        strategiesRequired = { "discipline", "cure" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure discipline raid", strategiesRequired);

        strategiesRequired = { "discipline", "buff" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff discipline raid", strategiesRequired);

        strategiesRequired = { "discipline", "boost" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost discipline raid", strategiesRequired);

        strategiesRequired = { "discipline", "cc" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc discipline raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc discipline raid", strategiesRequired);

        strategiesRequired = { "offheal" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal raid", strategiesRequired);

        strategiesRequired = { "offdps" };
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offdps raid", strategiesRequired);
        strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offdps raid", strategiesRequired);
    }
};
