// 圣骑士 - 动作头文件 (PaladinActions.h)：定义圣骑士专用技能施放与战斗动作
#pragma once
#include "playerbot/strategy/actions/GenericActions.h"

namespace ai
{
    // seals
    // 自我增益动作：正义圣印 (CastSealOfRighteousnessAction)
    BUFF_ACTION(CastSealOfRighteousnessAction, "seal of righteousness");
    // 自我增益动作：公正圣印 (CastSealOfJusticeAction)
    BUFF_ACTION(CastSealOfJusticeAction, "seal of justice");
    // 自我增益动作：光明圣印 (CastSealOfLightAction)
    BUFF_ACTION(CastSealOfLightAction, "seal of light");
    // 自我增益动作：智慧圣印 (CastSealOfWisdomAction)
    BUFF_ACTION(CastSealOfWisdomAction, "seal of wisdom");
    // 自我增益动作：命令圣印 (CastSealOfCommandAction)
    BUFF_ACTION(CastSealOfCommandAction, "seal of command");
    // 自我增益动作：复仇圣印 (CastSealOfVengeanceAction)
    BUFF_ACTION(CastSealOfVengeanceAction, "seal of vengeance");
    // 自我增益动作：十字军圣印 (CastSealOfTheCrusaderAction)
    BUFF_ACTION(CastSealOfTheCrusaderAction, "seal of the crusader");
    // 自我增益动作：鲜血圣印 (CastSealOfBloodAction)
    BUFF_ACTION(CastSealOfBloodAction, "seal of blood");

    // 施放审判动作
    class CastJudgementAction : public CastMeleeDebuffSpellAction
    {
    public:
        CastJudgementAction(PlayerbotAI* ai) : CastMeleeDebuffSpellAction(ai, "judgement") { range = 10.0f; }
        virtual bool isUseful() 
        {
            Unit* target = bot->GetTarget();
            if (target && target->IsAlive())
            {
                if (ai->HasAnyAuraOf(bot, "seal of vengeance", NULL))
                    return target->GetAuraCount(31803) > 2; // pointless to judge with no stacks!
                else if (ai->HasAnyAuraOf(bot, "seal of wisdom", NULL))
                {
                    return !target->HasAura(20186) && !target->HasAura(20354) &&
                        !target->HasAura(20355) && !target->HasAura(27164); 
                }
                else if (ai->HasAnyAuraOf(bot, "seal of light", NULL))
                {
                    return !target->HasAura(20185) && !target->HasAura(20344) &&
                        !target->HasAura(20345) && !target->HasAura(20346) &&
                        !target->HasAura(27162); 
                }
                else if (ai->HasAnyAuraOf(bot, "seal of the crusader", NULL))
                {
                    return !target->HasAura(21183) && !target->HasAura(20188) && 
                        !target->HasAura(20300) && !target->HasAura(20301) &&
                        !target->HasAura(20302) && !target->HasAura(20303) &&
                        !target->HasAura(27159);
                }
                else
                    return ai->HasAnyAuraOf(bot, "seal of justice", "seal of command", "seal of blood", "seal of righteousness", NULL);
            }
            else
                return false;
        }
    };

    // judgements
    // 范围近战减益动作：圣光审判 (CastJudgementOfLightAction)
    MELEE_DEBUFF_ACTION_R(CastJudgementOfLightAction, "judgement of light", 10.0f);
    // 范围近战减益动作：智慧审判 (CastJudgementOfWisdomAction)
    MELEE_DEBUFF_ACTION_R(CastJudgementOfWisdomAction, "judgement of wisdom", 10.0f);
    // 范围近战减益动作：公正审判 (CastJudgementOfJusticeAction)
    MELEE_DEBUFF_ACTION_R(CastJudgementOfJusticeAction, "judgement of justice", 10.0f);

    // 法术施放动作：神圣震击 (CastHolyShockAction)
    SPELL_ACTION(CastHolyShockAction, "holy shock");
    // 队友治疗动作：神圣震击 (CastHolyShockOnPartyAction)
    HEAL_PARTY_ACTION(CastHolyShockOnPartyAction, "holy shock");

    // consecration
    // 法术施放动作：奉献 (CastConsecrationAction)
    SPELL_ACTION(CastConsecrationAction, "consecration");

    // repentance
    // 减速技能动作：忏悔 (CastRepentanceSnareAction)
    SNARE_ACTION(CastRepentanceSnareAction, "repentance");
    // 远程减益技能动作：忏悔 (CastRepentanceAction)
    RANGED_DEBUFF_ACTION(CastRepentanceAction, "repentance");
    // 针对敌方治疗动作：忏悔 (CastRepentanceOnHealerAction)
    ENEMY_HEALER_ACTION(CastRepentanceOnHealerAction, "repentance");

    //hammer of wrath
    // 法术施放动作：愤怒之锤 (CastHammerOfWrathAction)
    SPELL_ACTION(CastHammerOfWrathAction, "hammer of wrath");

    // buffs
    // 自我增益动作：神恩术 (CastDivineFavorAction)
    BUFF_ACTION(CastDivineFavorAction, "divine favor");

    // blessings
    // 自我增益动作：自由祝福 (CastBlessingOfFreedomAction)
    BUFF_ACTION(CastBlessingOfFreedomAction, "blessing of freedom");
    // fury
    // 自我增益动作：正义之怒 (CastRighteousFuryAction)
    BUFF_ACTION(CastRighteousFuryAction, "righteous fury");
    // 自我增益动作：复仇之怒 (CastAvengingWrathAction)
    BUFF_ACTION(CastAvengingWrathAction, "avenging wrath");

    // 自我增益动作：神圣启示 (CastDivineIlluminationAction)
    BUFF_ACTION(CastDivineIlluminationAction, "divine illumination");

    // 施放神圣风暴动作
    class CastDivineStormAction : public CastBuffSpellAction
    {
    public:
        CastDivineStormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "divine storm") {}
    };

    // 施放十字军打击动作
    class CastCrusaderStrikeAction : public CastMeleeSpellAction
    {
    public:
        CastCrusaderStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "crusader strike") {}
    };

    // 施放圣骑士圣印动作
    class CastSealSpellAction : public CastBuffSpellAction
    {
    public:
        CastSealSpellAction(PlayerbotAI* ai, std::string name) : CastBuffSpellAction(ai, name) {}
        virtual bool isUseful() override { return AI_VALUE2(bool, "combat", "self target"); }
    };

    // 施放防骑圣印动作
    class ProtSealAction : public CastBuffSpellAction
    {
    public:
        ProtSealAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "prot seal") {}
        virtual bool isPossible() { return true; }
        virtual bool isUseful() override { return AI_VALUE2(bool, "combat", "self target"); }
        virtual bool Execute(Event& event);
    };

    // Pick the aura that is not being used by another paladin
    // 施放圣骑士光环动作
    class CastPaladinAuraAction : public CastBuffSpellAction
    {
    public:
        CastPaladinAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "paladin aura") {}
        virtual bool isPossible() { return true; }
        virtual bool isUseful() override { return true; }
        virtual bool Execute(Event& event);
    };

    // 施放虔诚光环动作
    class CastDevotionAuraAction : public CastBuffSpellAction
    {
    public:
        CastDevotionAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "devotion aura") {}
    };

    // 施放惩罚光环动作
    class CastRetributionAuraAction : public CastBuffSpellAction
    {
    public:
        CastRetributionAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "retribution aura") {}
    };

    // 施放专注光环动作
    class CastConcentrationAuraAction : public CastBuffSpellAction
    {
    public:
        CastConcentrationAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "concentration aura") {}
    };

    // 施放暗影抗性光环动作
    class CastShadowResistanceAuraAction : public CastBuffSpellAction
    {
    public:
        CastShadowResistanceAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "shadow resistance aura") {}
    };

    // 施放冰霜抗性光环动作
    class CastFrostResistanceAuraAction : public CastBuffSpellAction
    {
    public:
        CastFrostResistanceAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "frost resistance aura") {}
    };

    // 施放火焰抗性光环动作
    class CastFireResistanceAuraAction : public CastBuffSpellAction
    {
    public:
        CastFireResistanceAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fire resistance aura") {}
    };

    // 施放十字军光环动作
    class CastCrusaderAuraAction : public CastBuffSpellAction
    {
    public:
        CastCrusaderAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "crusader aura") {}
    };

    // 施放圣洁光环动作
    class CastSanctityAuraAction : public CastBuffSpellAction
    {
    public:
        CastSanctityAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "sanctity aura") {}
    };

    // Pick the best blessing based on spec
    // 施放祝福动作
    class CastBlessingAction : public CastSpellAction
    {
    public:
        CastBlessingAction(PlayerbotAI* ai, std::string name, bool greater) : CastSpellAction(ai, name), greater(greater) {}

    private:
        Unit* GetTarget() override;
        bool isPossible() override;
        bool isUseful() override { return true; }
        virtual std::string GetBlessingForTarget(Unit* target);

    protected:
        virtual std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const = 0;

    private:
        bool greater;
    };

    // 施放PVE祝福动作
    class CastPveBlessingAction : public CastBlessingAction
    {
    public:
        CastPveBlessingAction(PlayerbotAI* ai, std::string name = "pve blessing", bool greater = false) : CastBlessingAction(ai, name, greater) {}

    private:
        std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const override;
    };

    // 施放PVP祝福动作
    class CastPvpBlessingAction : public CastBlessingAction
    {
    public:
        CastPvpBlessingAction(PlayerbotAI* ai, std::string name = "pvp blessing", bool greater = false) : CastBlessingAction(ai, name, greater) {}

    private:
        std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const override;
    };

    // 施放团队副本祝福动作
    class CastRaidBlessingAction : public CastBlessingAction
    {
    public:
        CastRaidBlessingAction(PlayerbotAI* ai, std::string name = "raid blessing", bool greater = false) : CastBlessingAction(ai, name, greater) {}

    private:
        std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const override;
    };

    // 施放PVE强效祝福动作
    class CastPveGreaterBlessingAction : public CastPveBlessingAction
    {
    public:
        CastPveGreaterBlessingAction(PlayerbotAI* ai) : CastPveBlessingAction(ai, "pve greater blessing", true) {}
    };

    // 施放PVP强效祝福动作
    class CastPvpGreaterBlessingAction : public CastPvpBlessingAction
    {
    public:
        CastPvpGreaterBlessingAction(PlayerbotAI* ai) : CastPvpBlessingAction(ai, "pvp greater blessing", true) {}
    };

    // 施放团队副本强效祝福动作
    class CastRaidGreaterBlessingAction : public CastRaidBlessingAction
    {
    public:
        CastRaidGreaterBlessingAction(PlayerbotAI* ai) : CastRaidBlessingAction(ai, "raid greater blessing", true) {}
    };

    // Pick the best blessing based on target
    // 施放祝福 (对队友)动作
    class CastBlessingOnPartyAction : public CastSpellAction
    {
    public:
        CastBlessingOnPartyAction(PlayerbotAI* ai, std::string name, bool greater) : CastSpellAction(ai, name), greater(greater) {}

    private:
        Unit* GetTarget() override;
        bool isPossible() override;
        virtual std::string GetBlessingForTarget(Unit* target);

    protected:
        virtual std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const = 0;

    private:
        bool greater;
    };

    // 对队友施放PVE祝福动作
    class CastPveBlessingOnPartyAction : public CastBlessingOnPartyAction
    {
    public:
        CastPveBlessingOnPartyAction(PlayerbotAI* ai, std::string name = "pve blessing on party", bool greater = false) : CastBlessingOnPartyAction(ai, name, greater) {}

    private:
        std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const override;
    };

    // 对队友施放PVP祝福动作
    class CastPvpBlessingOnPartyAction : public CastBlessingOnPartyAction
    {
    public:
        CastPvpBlessingOnPartyAction(PlayerbotAI* ai, std::string name = "pvp blessing on party", bool greater = false) : CastBlessingOnPartyAction(ai, name, greater) {}

    private:
        std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const override;
    };

    // 对队友施放团队副本祝福动作
    class CastRaidBlessingOnPartyAction : public CastBlessingOnPartyAction
    {
    public:
        CastRaidBlessingOnPartyAction(PlayerbotAI* ai, std::string name = "raid blessing on party", bool greater = false) : CastBlessingOnPartyAction(ai, name, greater) {}

    private:
        std::vector<std::string> GetPossibleBlessingsForTarget(Unit* target) const override;
    };

    // 施放对队友施放PVE强效祝福动作
    class CastPveGreaterBlessingOnPartyAction : public CastPveBlessingOnPartyAction
    {
    public:
        CastPveGreaterBlessingOnPartyAction(PlayerbotAI* ai) : CastPveBlessingOnPartyAction(ai, "pve greater blessing on party", true) {}
    };

    // 施放对队友施放PVP强效祝福动作
    class CastPvpGreaterBlessingOnPartyAction : public CastPvpBlessingOnPartyAction
    {
    public:
        CastPvpGreaterBlessingOnPartyAction(PlayerbotAI* ai) : CastPvpBlessingOnPartyAction(ai, "pvp greater blessing on party", true) {}
    };

    // 施放对队友施放团队强效祝福动作
    class CastRaidGreaterBlessingOnPartyAction : public CastRaidBlessingOnPartyAction
    {
    public:
        CastRaidGreaterBlessingOnPartyAction(PlayerbotAI* ai) : CastRaidBlessingOnPartyAction(ai, "raid greater blessing on party", true) {}
    };

    // 施放力量祝福动作
    class CastBlessingOfMightAction : public CastBuffSpellAction
    {
    public:
        CastBlessingOfMightAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of might") {}
        bool isUseful() override { return CastBuffSpellAction::isUseful() && !ai->HasAura("greater " + GetSpellName(), GetTarget()); }
    };

    // 施放强效力量祝福动作
    class CastGreaterBlessingOfMightAction : public CastBuffSpellAction
    {
    public:
        CastGreaterBlessingOfMightAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "greater blessing of might") {}
    };

    // 施放力量祝福动作
    class CastBlessingOfMightOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastBlessingOfMightOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of might") {}
        std::string GetTargetQualifier() override { return GetSpellName() + ",greater " + GetSpellName() + "-" + (ignoreTanks ? "1" : "0"); }
    };

    // 施放强效力量祝福动作
    class CastGreaterBlessingOfMightOnPartyAction : public GreaterBuffOnPartyAction
    {
    public:
        CastGreaterBlessingOfMightOnPartyAction(PlayerbotAI* ai) : GreaterBuffOnPartyAction(ai, "greater blessing of might", "blessing of might") {}
    };

    // 施放智慧祝福动作
    class CastBlessingOfWisdomAction : public CastBuffSpellAction
    {
    public:
        CastBlessingOfWisdomAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of wisdom") {}
        bool isUseful() override { return CastBuffSpellAction::isUseful() && !ai->HasAura("greater " + GetSpellName(), GetTarget()); }
    };

    // 施放强效智慧祝福动作
    class CastGreaterBlessingOfWisdomAction : public CastBuffSpellAction
    {
    public:
        CastGreaterBlessingOfWisdomAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "greater blessing of wisdom") {}
    };

    // 施放智慧祝福动作
    class CastBlessingOfWisdomOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastBlessingOfWisdomOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of wisdom") {}
        std::string GetTargetQualifier() override { return GetSpellName() + ",greater " + GetSpellName() + "-" + (ignoreTanks ? "1" : "0"); }
    };

    // 施放强效智慧祝福动作
    class CastGreaterBlessingOfWisdomOnPartyAction : public GreaterBuffOnPartyAction
    {
    public:
        CastGreaterBlessingOfWisdomOnPartyAction(PlayerbotAI* ai) : GreaterBuffOnPartyAction(ai, "greater blessing of wisdom", "blessing of wisdom") {}
    };

    // 施放王者祝福动作
    class CastBlessingOfKingsAction : public CastBuffSpellAction
    {
    public:
        CastBlessingOfKingsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of kings") {}
        bool isUseful() override { return CastBuffSpellAction::isUseful() && !ai->HasAura("greater " + GetSpellName(), GetTarget()); }
    };

    // 施放强效王者祝福动作
    class CastGreaterBlessingOfKingsAction : public CastBuffSpellAction
    {
    public:
        CastGreaterBlessingOfKingsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "greater blessing of kings") {}
    };

    // 施放王者祝福动作
    class CastBlessingOfKingsOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastBlessingOfKingsOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of kings") {}
        std::string GetTargetQualifier() override { return GetSpellName() + ",greater " + GetSpellName() + "-" + (ignoreTanks ? "1" : "0"); }
    };

    // 施放强效王者祝福动作
    class CastGreaterBlessingOfKingsOnPartyAction : public GreaterBuffOnPartyAction
    {
    public:
        CastGreaterBlessingOfKingsOnPartyAction(PlayerbotAI* ai) : GreaterBuffOnPartyAction(ai, "greater blessing of kings", "blessing of kings") {}
    };

    // 施放庇护祝福动作
    class CastBlessingOfSanctuaryAction : public CastBuffSpellAction
    {
    public:
        CastBlessingOfSanctuaryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of sanctuary") {}
        bool isUseful() override { return CastBuffSpellAction::isUseful() && !ai->HasAura("greater " + GetSpellName(), GetTarget()); }
    };

    // 施放强效庇护祝福动作
    class CastGreaterBlessingOfSanctuaryAction : public CastBuffSpellAction
    {
    public:
        CastGreaterBlessingOfSanctuaryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "greater blessing of sanctuary") {}
    };

    // 施放庇护祝福动作
    class CastBlessingOfSanctuaryOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastBlessingOfSanctuaryOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of sanctuary") {}
        std::string GetTargetQualifier() override { return GetSpellName() + ",greater " + GetSpellName() + "-" + (ignoreTanks ? "1" : "0"); }
    };

    // 施放强效庇护祝福动作
    class CastGreaterBlessingOfSanctuaryOnPartyAction : public GreaterBuffOnPartyAction
    {
    public:
        CastGreaterBlessingOfSanctuaryOnPartyAction(PlayerbotAI* ai) : GreaterBuffOnPartyAction(ai, "greater blessing of sanctuary", "blessing of sanctuary") {}
    };

    // 施放光明祝福动作
    class CastBlessingOfLightAction : public CastBuffSpellAction
    {
    public:
        CastBlessingOfLightAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of light") {}
        bool isUseful() override { return CastBuffSpellAction::isUseful() && !ai->HasAura("greater " + GetSpellName(), GetTarget()); }
    };

    // 施放强效光明祝福动作
    class CastGreaterBlessingOfLightAction : public CastBuffSpellAction
    {
    public:
        CastGreaterBlessingOfLightAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "greater blessing of light") {}
    };

    // 施放光明祝福动作
    class CastBlessingOfLightOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastBlessingOfLightOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of light") {}
        std::string GetTargetQualifier() override { return GetSpellName() + ",greater " + GetSpellName() + "-" + (ignoreTanks ? "1" : "0"); }
    };

    // 施放强效光明祝福动作
    class CastGreaterBlessingOfLightOnPartyAction : public GreaterBuffOnPartyAction
    {
    public:
        CastGreaterBlessingOfLightOnPartyAction(PlayerbotAI* ai) : GreaterBuffOnPartyAction(ai, "greater blessing of light", "blessing of light") {}
    };

    // 施放拯救祝福动作
    class CastBlessingOfSalvationAction : public CastBuffSpellAction
    {
    public:
        CastBlessingOfSalvationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of salvation") {}
        bool isUseful() override { return CastBuffSpellAction::isUseful() && !ai->HasAura("greater " + GetSpellName(), GetTarget()); }
    };

    // 施放强效拯救祝福动作
    class CastGreaterBlessingOfSalvationAction : public CastBuffSpellAction
    {
    public:
        CastGreaterBlessingOfSalvationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "greater blessing of salvation") {}
    };

    // 施放拯救祝福动作
    class CastBlessingOfSalvationOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastBlessingOfSalvationOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of salvation", true) {}
        std::string GetTargetQualifier() override { return GetSpellName() + ",greater " + GetSpellName() + "-" + (ignoreTanks ? "1" : "0"); }
    };

    // 施放强效拯救祝福动作
    class CastGreaterBlessingOfSalvationOnPartyAction : public GreaterBuffOnPartyAction
    {
    public:
        CastGreaterBlessingOfSalvationOnPartyAction(PlayerbotAI* ai) : GreaterBuffOnPartyAction(ai, "greater blessing of salvation", "blessing of salvation", true) {}

        bool isUseful() override
        {
            if (GreaterBuffOnPartyAction::isUseful())
            {
                // Don't cast greater salvation on possible tank classes
                Unit* target = GetTarget();
                if (target->IsPlayer())
                {
                    const uint8 playerClass = ((Player*)target)->getClass();
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
                    if (playerClass == CLASS_PALADIN || playerClass == CLASS_WARRIOR || playerClass == CLASS_DRUID || playerClass == CLASS_DEATH_KNIGHT)
#else
                    if (playerClass == CLASS_PALADIN || playerClass == CLASS_WARRIOR || playerClass == CLASS_DRUID)
#endif
                    {
                        return false;
                    }
                }

                return true;
            }

            return false;
        }
    };

    // 施放圣光术动作
    class CastHolyLightAction : public CastHealingSpellAction
    {
    public:
        CastHolyLightAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "holy light") {}
    };

    // 施放圣光术动作
    class CastHolyLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHolyLightOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "holy light") {}
    };

    // 施放圣光闪现动作
    class CastFlashOfLightAction : public CastHealingSpellAction
    {
    public:
        CastFlashOfLightAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "flash of light") {}
    };

    // 施放圣光闪现动作
    class CastFlashOfLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashOfLightOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "flash of light") {}
    };

    // 施放圣疗术动作
    class CastLayOnHandsAction : public CastHealingSpellAction
    {
    public:
        CastLayOnHandsAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lay on hands") {}
    };

    // 施放圣疗术动作
    class CastLayOnHandsOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLayOnHandsOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "lay on hands") {}
    };

    // 施放圣佑术动作
    class CastDivineProtectionAction : public CastBuffSpellAction
    {
    public:
        CastDivineProtectionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "divine protection") {}
    };

    // 施放圣佑术动作
    class CastDivineProtectionOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastDivineProtectionOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "divine protection") {}
        virtual std::string getName() override { return "divine protection on party"; }
    };

    // 施放圣盾术动作
    class CastDivineShieldAction: public CastBuffSpellAction
    {
    public:
        CastDivineShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "divine shield") {}
    };

    // 施放神圣愤怒动作
    class CastHolyWrathAction : public CastMeleeSpellAction
    {
    public:
        CastHolyWrathAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "holy wrath") {}
    };

    // 施放制裁之锤动作
    class CastHammerOfJusticeAction : public CastMeleeSpellAction
    {
    public:
        CastHammerOfJusticeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "hammer of justice") {}
    };

    // 施放正义之锤动作
    class CastHammerOfTheRighteousAction : public CastMeleeSpellAction
    {
    public:
        CastHammerOfTheRighteousAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "hammer of the righteous") {}
    };

    // 施放纯净术动作
    class CastPurifyPoisonAction : public CastCureSpellAction
    {
    public:
        CastPurifyPoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "purify") {}
    };

    // 施放纯净术动作
    class CastPurifyDiseaseAction : public CastCureSpellAction
    {
    public:
        CastPurifyDiseaseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "purify") {}
    };

    // 施放纯净术动作
    class CastPurifyPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastPurifyPoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "purify", DISPEL_POISON) {}
        virtual std::string getName() override { return "purify poison on party"; }
    };

    // 施放纯净术动作
    class CastPurifyDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastPurifyDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "purify", DISPEL_DISEASE) {}
        virtual std::string getName() override { return "purify disease on party"; }
    };

    // 施放清算之手动作
    class CastHandOfReckoningAction : public CastSpellAction
    {
    public:
        CastHandOfReckoningAction(PlayerbotAI* ai) : CastSpellAction(ai, "hand of reckoning") {}
    };

    // 施放正义防御动作
    class CastRighteousDefenseAction : public CastSpellAction
    {
    public:
        CastRighteousDefenseAction(PlayerbotAI* ai) : CastSpellAction(ai, "righteous defense") {}
    };

    // 施放清洁术动作
    class CastCleansePoisonAction : public CastCureSpellAction
    {
    public:
        CastCleansePoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cleanse") {}
    };

    // 施放清洁术动作
    class CastCleanseDiseaseAction : public CastCureSpellAction
    {
    public:
        CastCleanseDiseaseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cleanse") {}
    };

    // 施放清洁术动作
    class CastCleanseMagicAction : public CastCureSpellAction
    {
    public:
        CastCleanseMagicAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cleanse") {}
    };

    // 施放清洁术动作
    class CastCleansePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleansePoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_POISON) {}
        virtual std::string getName() override { return "cleanse poison on party"; }
    };

    // 施放清洁术动作
    class CastCleanseDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_DISEASE) {}
        virtual std::string getName() override { return "cleanse disease on party"; }
    };

    // 施放清洁术动作
    class CastCleanseMagicOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseMagicOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_MAGIC) {}
        virtual std::string getName() override { return "cleanse magic on party"; }
    };

    // 法术施放动作：驱邪术 (CastExorcismAction)
    SPELL_ACTION(CastExorcismAction, "exorcism");

    // 法术动作定义：复仇者之盾 (CastAvengersShieldAction)
    BEGIN_SPELL_ACTION(CastAvengersShieldAction, "avenger's shield")
    END_SPELL_ACTION()

    // 施放神圣之盾动作
    class CastHolyShieldAction : public CastBuffSpellAction
    {
    public:
        CastHolyShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "holy shield") {}
    };

    // 施放救赎动作
    class CastRedemptionAction : public ResurrectPartyMemberAction
    {
    public:
        CastRedemptionAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "redemption") {}
    };

    // 施放制裁之锤动作
    class CastHammerOfJusticeOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastHammerOfJusticeOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "hammer of justice") {}
    };

    // 施放制裁之锤动作
    class CastHammerOfJusticeSnareAction : public CastSnareSpellAction
    {
    public:
        CastHammerOfJusticeSnareAction(PlayerbotAI* ai) : CastSnareSpellAction(ai, "hammer of justice") {}
    };

    // 施放超度邪恶动作
    class CastTurnUndeadAction : public CastBuffSpellAction
    {
    public:
        CastTurnUndeadAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "turn undead") {}
        virtual Value<ObjectGuid>* GetTargetValue() { return context->GetValue<ObjectGuid>("cc target", getName()); }
    };

    // 施放牺牲之手动作
    class CastHandOfSacrificeAction : public BuffOnPartyAction
    {
    public:
        CastHandOfSacrificeAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "hand of sacrifice") {}
    };

    // 施放牺牲祝福动作
    class CastBlessingOfSacrificeAction : public BuffOnPartyAction
    {
    public:
        CastBlessingOfSacrificeAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of sacrifice") {}
    };

    // 施放自由祝福动作
    class CastBlessingOfFreedomOnPartyAction : public CastSpellAction
    {
    public:
        CastBlessingOfFreedomOnPartyAction(PlayerbotAI* ai) : CastSpellAction(ai, "blessing of freedom") {}
        bool isUseful() override { return CastSpellAction::isUseful() && !ai->HasAura(GetSpellName(), GetTarget()); }
        std::string GetReachActionName() override { return "reach spell"; }
        std::string GetTargetName() override { return "party member to remove roots"; }
    };

    // 施放保护祝福动作
    class CastBlessingOfProtectionOnPartyAction : public CastProtectSpellAction
    {
    public:
        CastBlessingOfProtectionOnPartyAction(PlayerbotAI* ai) : CastProtectSpellAction(ai, "blessing of protection") {}
        bool isUseful() override 
        { 
            Unit* target = GetTarget();
            if(target && target->IsPlayer() && !ai->IsTank((Player*)target))
            {
                return CastProtectSpellAction::isUseful();
            }

            return false;
        }
    };

    // 施放更新PVE策略动作
    class UpdatePaladinPveStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdatePaladinPveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
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

            strategiesRequired = { "holy/heal", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura holy pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura holy pve", strategiesRequired);

            strategiesRequired = { "holy/heal", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing holy pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing holy pve", strategiesRequired);

            strategiesRequired = { "retribution" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "retribution pve", strategiesRequired);

            strategiesRequired = { "retribution", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe retribution pve", strategiesRequired);

            strategiesRequired = { "retribution", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure retribution pve", strategiesRequired);

            strategiesRequired = { "retribution", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff retribution pve", strategiesRequired);

            strategiesRequired = { "retribution", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost retribution pve", strategiesRequired);

            strategiesRequired = { "retribution", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc retribution pve", strategiesRequired);

            strategiesRequired = { "retribution", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura retribution pve", strategiesRequired);

            strategiesRequired = { "retribution", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing retribution pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing retribution pve", strategiesRequired);

            strategiesRequired = { "protection/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing protection pve", strategiesRequired);
        
            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pve", strategiesRequired);
        }
    };

    // 施放更新PVP策略动作
    class UpdatePaladinPvpStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdatePaladinPvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
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

            strategiesRequired = { "holy/heal", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura holy pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura holy pvp", strategiesRequired);

            strategiesRequired = { "holy/heal", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing holy pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing holy pvp", strategiesRequired);

            strategiesRequired = { "retribution" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "retribution pvp", strategiesRequired);

            strategiesRequired = { "retribution", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe retribution pvp", strategiesRequired);

            strategiesRequired = { "retribution", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure retribution pvp", strategiesRequired);

            strategiesRequired = { "retribution", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff retribution pvp", strategiesRequired);

            strategiesRequired = { "retribution", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost retribution pvp", strategiesRequired);

            strategiesRequired = { "retribution", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc retribution pvp", strategiesRequired);

            strategiesRequired = { "retribution", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura retribution pvp", strategiesRequired);

            strategiesRequired = { "retribution", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing retribution pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing retribution pvp", strategiesRequired);

            strategiesRequired = { "protection/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing protection pvp", strategiesRequired);
        
            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal pvp", strategiesRequired);
        }
    };

    // 施放更新团队副本策略动作
    class UpdatePaladinRaidStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdatePaladinRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
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

            strategiesRequired = { "holy/heal", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura holy raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura holy raid", strategiesRequired);

            strategiesRequired = { "holy/heal", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing holy raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing holy raid", strategiesRequired);

            strategiesRequired = { "retribution" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "retribution raid", strategiesRequired);

            strategiesRequired = { "retribution", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe retribution raid", strategiesRequired);

            strategiesRequired = { "retribution", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure retribution raid", strategiesRequired);

            strategiesRequired = { "retribution", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff retribution raid", strategiesRequired);

            strategiesRequired = { "retribution", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost retribution raid", strategiesRequired);

            strategiesRequired = { "retribution", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc retribution raid", strategiesRequired);

            strategiesRequired = { "retribution", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura retribution raid", strategiesRequired);

            strategiesRequired = { "retribution", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing retribution raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing retribution raid", strategiesRequired);

            strategiesRequired = { "protection/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "aura" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aura protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aura protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "blessing" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "blessing protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "blessing protection raid", strategiesRequired);
        
            strategiesRequired = { "offheal" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "offheal raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "offheal raid", strategiesRequired);
        }
    };
}
