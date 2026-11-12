// 死亡骑士 - 动作头文件 (DKActions.h)：定义死亡骑士专用技能施放与战斗动作
#pragma once

#include "playerbot/strategy/actions/GenericActions.h"
#include "playerbot/strategy/actions/MovementActions.h"

namespace ai
{
    // 施放鲜血灵气动作
    class CastBloodPresenceAction : public CastBuffSpellAction {
    public:
        CastBloodPresenceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blood presence") {}
    };

    // 施放冰霜灵气动作
    class CastFrostPresenceAction : public CastBuffSpellAction {
    public:
        CastFrostPresenceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "frost presence") {}
    };

    // 施放邪恶灵气动作
    class CastUnholyPresenceAction : public CastBuffSpellAction {
    public:
        CastUnholyPresenceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "unholy presence") {}
    };

    // 施放死亡之寒动作
    class CastDeathchillAction : public CastBuffSpellAction {
    public:
        CastDeathchillAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "deathchill") {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge(NextAction::array(0, new NextAction("frost presence"), NULL), CastSpellAction::getPrerequisites());
        }
    };

    // 施放黑暗命令动作
    class CastDarkCommandAction : public CastBuffSpellAction {
    public:
        CastDarkCommandAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "dark command") {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge(NextAction::array(0, new NextAction("blood presence"), NULL), CastSpellAction::getPrerequisites());
        }
    };

    // 远程法术动作定义：死亡之握 (CastDeathGripAction)
    BEGIN_RANGED_SPELL_ACTION(CastDeathGripAction, "death grip")
        END_SPELL_ACTION()

    // Unholy presence
    // 施放邪恶系近战符文技能动作
    class CastUnholyMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastUnholyMeleeSpellAction(PlayerbotAI* ai, std::string spell) : CastMeleeSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge(NextAction::array(0, new NextAction("unholy presence"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };


    // Frost presence
    // 施放冰霜系近战符文技能动作
    class CastFrostMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastFrostMeleeSpellAction(PlayerbotAI* ai, std::string spell) : CastMeleeSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge(NextAction::array(0, new NextAction("frost presence"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    // Blood presence
    // 施放鲜血系近战符文技能动作
    class CastBloodMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastBloodMeleeSpellAction(PlayerbotAI* ai, std::string spell) : CastMeleeSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge(NextAction::array(0, new NextAction("blood presence"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };
        // a
    // 施放符文打击动作
    class CastRuneStrikeAction : public CastMeleeSpellAction {
    public:
    CastRuneStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "rune strike") {}
    };
    //debuff
    // 近战减益动作定义：传染 (CastPestilenceAction)
    BEGIN_MELEE_DEBUFF_ACTION(CastPestilenceAction, "pestilence")
    END_SPELL_ACTION()

    //debuff
    // 远程减益动作定义：凛风冲击 (CastHowlingBlastAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastHowlingBlastAction, "howling blast")
    END_SPELL_ACTION()

    //debuff it
    // 远程减益动作定义：冰冷触摸 (CastIcyTouchAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastIcyTouchAction, "icy touch")
    END_SPELL_ACTION()


    // 施放冰冷触摸动作
    class CastIcyTouchOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastIcyTouchOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "icy touch") {}
    };

    //debuff ps
    // 近战减益动作定义：瘟疫打击 (CastPlagueStrikeAction)
    BEGIN_MELEE_DEBUFF_ACTION(CastPlagueStrikeAction, "plague strike")
    END_SPELL_ACTION()


    // 施放瘟疫打击动作
    class CastPlagueStrikeOnAttackerAction : public CastMeleeDebuffSpellOnAttackerAction
    {
    public:
        CastPlagueStrikeOnAttackerAction(PlayerbotAI* ai) : CastMeleeDebuffSpellOnAttackerAction(ai, "plague strike") {}
    };

    //debuff
    // 远程减益动作定义：鲜血印记 (CastMarkOfBloodAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastMarkOfBloodAction, "mark of blood")
    END_SPELL_ACTION()

    // 施放鲜血印记动作
    class CastMarkOfBloodOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastMarkOfBloodOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "mark of blood") {}
    };

    // 施放邪恶虫群动作
    class CastUnholyBlightAction : public CastBuffSpellAction
    {
    public:
        CastUnholyBlightAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "unholy blight") {}
    };

    // 施放召唤石像鬼动作
    class CastSummonGargoyleAction : public CastBuffSpellAction
    {
    public:
        CastSummonGargoyleAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon gargoyle") {}
    };

    // 施放食尸鬼狂热动作
    class CastGhoulFrenzyAction : public CastBuffSpellAction
    {
    public:
        CastGhoulFrenzyAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "ghoul frenzy") {}
    };

    // 近战法术动作定义：尸体爆炸 (CastCorpseExplosionAction)
    BEGIN_MELEE_SPELL_ACTION(CastCorpseExplosionAction, "corpse explosion")
    END_SPELL_ACTION()

    // 近战法术动作定义：反魔法护罩 (CastAntiMagicShellAction)
    BEGIN_MELEE_SPELL_ACTION(CastAntiMagicShellAction, "anti magic shell")
    END_SPELL_ACTION()


    // 近战法术动作定义：反魔法领域 (CastAntiMagicZoneAction)
    BEGIN_MELEE_SPELL_ACTION(CastAntiMagicZoneAction, "anti magic zone")
    END_SPELL_ACTION()


    // 施放寒冰锁链动作
    class CastChainsOfIceAction : public CastSpellAction {
    public:
        CastChainsOfIceAction(PlayerbotAI* ai) : CastSpellAction(ai, "chains of ice") {}
    };

    // 施放饥饿之寒动作
    class CastHungeringColdAction : public CastMeleeSpellAction {
    public:
        CastHungeringColdAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "hungering cold") {}
    };

    // 施放心脏打击动作
    class CastHeartStrikeAction : public CastMeleeSpellAction {
    public:
        CastHeartStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "heart strike") {}
    };

    // 施放鲜血打击动作
    class CastBloodStrikeAction : public CastMeleeSpellAction {
    public:
        CastBloodStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "blood strike") {}
    };
    
    // 施放冰霜打击动作
    class CastFrostStrikeAction : public CastMeleeSpellAction {
    public:
        CastFrostStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "frost strike") {}
    };

    // 施放湮灭动作
    class CastObliterateAction : public CastMeleeSpellAction {
    public:
        CastObliterateAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "obliterate") {}
    };

    // 施放灵界打击动作
    class CastDeathStrikeAction : public CastMeleeSpellAction {
    public:
        CastDeathStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "death strike") {}
    };

    // 施放天灾打击动作
    class CastScourgeStrikeAction : public CastMeleeSpellAction {
    public:
        CastScourgeStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "scorgue strike") {}
    };

    // 施放凋零缠绕/死亡缠绕动作
    class CastDeathCoilAction : public CastSpellAction {
    public:
        CastDeathCoilAction(PlayerbotAI* ai) : CastSpellAction(ai, "death coill") {}
    };

    // 施放血液沸腾动作
    class CastBloodBoilAction : public CastBuffSpellAction {
    public:
        CastBloodBoilAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blood boil") {}
    };

    // 施放枯萎凋零动作
    class CastDeathAndDecayAction : public CastSpellAction {
    public:
        CastDeathAndDecayAction(PlayerbotAI* ai) : CastSpellAction(ai, "death and decay") {}
    };

    // 施放寒冬号角动作
    class CastHornOfWinterAction : public CastBuffSpellAction
    {
    public:
        CastHornOfWinterAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "horn of winter") {}
    };

    // 施放强化冰冷之爪动作
    class CastImprovedIcyTalonsAction : public CastBuffSpellAction
    {
    public:
        CastImprovedIcyTalonsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "improved icy talons") {}
    };

    // 施放白骨之盾动作
    class CastBoneShieldAction : public CastBuffSpellAction
    {
    public:
        CastBoneShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bone shield") {}
    };

    // 施放天灾契约动作
    class CastDeathPactAction : public CastBuffSpellAction
    {
    public:
        CastDeathPactAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "death pact") {}
    };

    // 施放死亡符文掌握动作
    class CastDeathRuneMasteryAction : public CastBuffSpellAction
    {
    public:
        CastDeathRuneMasteryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "death rune mastery") {}
    };

    // 施放符文刃舞动作
    class CastDancingWeaponAction : public CastBuffSpellAction
    {
    public:
        CastDancingWeaponAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "dancing weapon") {}
    };

    // 施放符文武器增效动作
    class CastEmpowerRuneWeaponAction : public CastBuffSpellAction
    {
    public:
        CastEmpowerRuneWeaponAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "empower rune weapon") {}
    };

    // 施放亡者大军动作
    class CastArmyOfTheDeadAction : public CastBuffSpellAction
    {
    public:
        CastArmyOfTheDeadAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "army of the dead") {}
    };


    // 施放亡者复生动作
    class CastRaiseDeadAction : public CastBuffSpellAction
    {
    public:
        CastRaiseDeadAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "raise dead") {}
        virtual bool isPossible() override;
    };

    // 施放杀戮机器动作
    class CastKillingMachineAction : public CastBuffSpellAction
    {
    public:
        CastKillingMachineAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "killing machine") {}
    };

    // 施放冰封之韧动作
    class CastIceboundFortitudeAction : public CastBuffSpellAction
    {
    public:
        CastIceboundFortitudeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "icebound fortitude") {}
    };

    // 施放铜墙铁壁动作
    class CastUnbreakableArmorAction : public CastBuffSpellAction
    {
    public:
        CastUnbreakableArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "unbreakable armor") {}
    };

    // 施放吸血鬼之血动作
    class CastVampiricBloodAction : public CastBuffSpellAction
    {
    public:
        CastVampiricBloodAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "vampiric blood") {}
    };
    
    // 施放心灵冰冻动作
    class CastMindFreezeAction : public CastMeleeSpellAction {
    public:
        CastMindFreezeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mind freeze") {}
    };

    // 施放绞袭动作
    class CastStrangulateAction : public CastMeleeSpellAction {
    public:
        CastStrangulateAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "strangulate") {}
    };

    // 施放心灵冰冻动作
    class CastMindFreezeOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastMindFreezeOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "mind freeze") {}
    };

    // 施放符文分流动作
    class CastRuneTapAction : public CastMeleeSpellAction {
    public:
        CastRuneTapAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "rune tap") {}

    };
    // 施放活力分流动作
    class CastBloodTapAction : public CastMeleeSpellAction {
    public:
        CastBloodTapAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "blood tap") {}
    };

    const std::vector<uint32> RUNEFORGES = { 190557, 191746, 191747, 191748, 191757, 191758 };

    // 施放符文熔铸动作
    class RuneforgeAction : public MovementAction
    {
    public:
        RuneforgeAction(PlayerbotAI* ai) : MovementAction(ai, "runeforge") {}

        virtual bool Execute(Event& event);
        virtual bool isUseful();
    };
}
