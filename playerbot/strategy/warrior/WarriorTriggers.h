// 战士 - 触发器头文件 (WarriorTriggers.h)：定义战士增益、减益、冷却及状态检查触发条件
#pragma once
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    // 增益触发器：战斗姿态 (BattleStanceTrigger)
    BUFF_TRIGGER(BattleStanceTrigger, "battle stance");
    // 增益触发器：防御姿态 (DefensiveStanceTrigger)
    BUFF_TRIGGER(DefensiveStanceTrigger, "defensive stance");
    // 增益触发器：狂暴姿态 (BerserkerStanceTrigger)
    BUFF_TRIGGER(BerserkerStanceTrigger, "berserker stance");
    // 增益触发器：盾牌格挡 (ShieldBlockTrigger)
    BUFF_TRIGGER(ShieldBlockTrigger, "shield block");
    // 增益触发器(带条件)：命令怒吼 (CommandingShoutTrigger)
    BUFF_TRIGGER_A(CommandingShoutTrigger, "commanding shout");
    // 减益触发器：撕裂 (RendDebuffTrigger)
    DEBUFF_TRIGGER(RendDebuffTrigger, "rend");
    // 减益触发器：缴械 (DisarmDebuffTrigger)
    DEBUFF_TRIGGER(DisarmDebuffTrigger, "disarm");
    // 减益触发器(带条件)：破甲攻击 (SunderArmorDebuffTrigger)
    DEBUFF_TRIGGER_A(SunderArmorDebuffTrigger, "sunder armor");
    // 减益触发器：挫志怒吼 (DemoralizingShoutDebuffTrigger)
    DEBUFF_TRIGGER(DemoralizingShoutDebuffTrigger, "demoralizing shout");
    // 减益触发器：致死打击 (MortalStrikeDebuffTrigger)
    DEBUFF_TRIGGER(MortalStrikeDebuffTrigger, "mortal strike");
    // 敌方减益触发器：撕裂 (RendDebuffOnAttackerTrigger)
    DEBUFF_ENEMY_TRIGGER(RendDebuffOnAttackerTrigger, "rend");
    // 可施法检查触发器：毁灭打击 (DevastateAvailableTrigger)
    CAN_CAST_TRIGGER(DevastateAvailableTrigger, "devastate");
    // 可施法检查触发器：复仇 (RevengeAvailableTrigger)
    CAN_CAST_TRIGGER(RevengeAvailableTrigger, "revenge");
    // 可施法检查触发器：压制 (OverpowerAvailableTrigger)
    CAN_CAST_TRIGGER(OverpowerAvailableTrigger, "overpower");
    // 增益触发器：暴怒 (RampageAvailableTrigger)
    BUFF_TRIGGER(RampageAvailableTrigger, "rampage");
    // 增益触发器(带条件)：血性狂暴 (BloodrageBuffTrigger)
    BUFF_TRIGGER_A(BloodrageBuffTrigger, "bloodrage");
    // 可施法检查触发器：乘胜追击 (VictoryRushTrigger)
    CAN_CAST_TRIGGER(VictoryRushTrigger, "victory rush");
    // 光环存在触发器：剑盾猛攻 (SwordAndBoardTrigger)
    HAS_AURA_TRIGGER(SwordAndBoardTrigger, "sword and board");
    // 减速触发器：震荡猛击 (ConcussionBlowTrigger)
    SNARE_TRIGGER(ConcussionBlowTrigger, "concussion blow");
    // 减速触发器：断筋 (HamstringTrigger)
    SNARE_TRIGGER(HamstringTrigger, "hamstring");
    // 减速触发器：惩戒痛击 (MockingBlowTrigger)
    SNARE_TRIGGER(MockingBlowTrigger, "mocking blow");
    // 减速触发器：雷霆一击 (ThunderClapSnareTrigger)
    SNARE_TRIGGER(ThunderClapSnareTrigger, "thunder clap");
    // 减益触发器：雷霆一击 (ThunderClapTrigger)
    DEBUFF_TRIGGER(ThunderClapTrigger, "thunder clap");
    // 减速触发器：嘲讽 (TauntSnareTrigger)
    SNARE_TRIGGER(TauntSnareTrigger, "taunt");
    // 减速触发器：拦截 (InterceptSnareTrigger)
    SNARE_TRIGGER(InterceptSnareTrigger, "intercept");
    // 冷却触发器：拦截 (InterceptCanCastTrigger)
    CD_TRIGGER(InterceptCanCastTrigger, "intercept");
    // 减速触发器：震荡波 (ShockwaveSnareTrigger)
    SNARE_TRIGGER(ShockwaveSnareTrigger, "shockwave");
    // 减益触发器：震荡波 (ShockwaveTrigger)
    DEBUFF_TRIGGER(ShockwaveTrigger, "shockwave");
    // 爆发增益触发器：死亡之愿 (DeathWishTrigger)
    BOOST_TRIGGER(DeathWishTrigger, "death wish");
    // 爆发增益触发器：鲁莽 (RecklessnessTrigger)
    BOOST_TRIGGER(RecklessnessTrigger, "recklessness");
    // 打断敌方治疗触发器：盾击 (ShieldBashInterruptEnemyHealerSpellTrigger)
    INTERRUPT_HEALER_TRIGGER(ShieldBashInterruptEnemyHealerSpellTrigger, "shield bash");
    // 打断触发器：盾击 (ShieldBashInterruptSpellTrigger)
    INTERRUPT_TRIGGER(ShieldBashInterruptSpellTrigger, "shield bash");
    // 打断敌方治疗触发器：拳击 (PummelInterruptEnemyHealerSpellTrigger)
    INTERRUPT_HEALER_TRIGGER(PummelInterruptEnemyHealerSpellTrigger, "pummel");
    // 打断触发器：拳击 (PummelInterruptSpellTrigger)
    INTERRUPT_TRIGGER(PummelInterruptSpellTrigger, "pummel");
    // 打断敌方治疗触发器：拦截 (InterceptInterruptEnemyHealerSpellTrigger)
    INTERRUPT_HEALER_TRIGGER(InterceptInterruptEnemyHealerSpellTrigger, "intercept");
    // 打断触发器：拦截 (InterceptInterruptSpellTrigger)
    INTERRUPT_TRIGGER(InterceptInterruptSpellTrigger, "intercept");
    // 法术反射/反制触发器：法术反射 (SpellReflectionTrigger)
    DEFLECT_TRIGGER(SpellReflectionTrigger, "spell reflection");
    // 光环存在触发器：猝死 (SuddenDeathTrigger)
    HAS_AURA_TRIGGER(SuddenDeathTrigger, "sudden death");
    // 光环存在触发器：瞬发猛击(血涌) (SlamInstantTrigger)
    HAS_AURA_TRIGGER(SlamInstantTrigger, "slam!");
    // 光环存在触发器：血之气息 (TasteForBloodTrigger)
    HAS_AURA_TRIGGER(TasteForBloodTrigger, "taste for blood");

    // 触发器：战斗怒吼
    class BattleShoutTrigger : public Trigger
    {
    public:
        BattleShoutTrigger(PlayerbotAI* ai) : Trigger(ai, "battle shout") {}

        bool IsActive() override
        {
            uint32 comShout = AI_VALUE2(uint32, "spell id", "commanding shout");
            uint32 batShout = AI_VALUE2(uint32, "spell id", "battle shout");
            if (!batShout)
                return false;

            if (comShout && bot->HasSpell(comShout))
                return !ai->HasAura("battle shout", bot) && !ai->HasMyAura("commanding shout", bot);

            if (bot->HasSpell(batShout))
                return !ai->HasAura("battle shout", bot);

            return false;
        }
    };

    // 触发器：狂暴之怒增益状态
    class BerserkerRageBuffTrigger : public TargetOfFearCastTrigger
    {
    public:
        BerserkerRageBuffTrigger(PlayerbotAI* ai) : TargetOfFearCastTrigger(ai) {}
        bool IsActive() override
        {
            // Check for spell cooldown
            uint32 spellid = AI_VALUE2(uint32, "spell id", "berserker rage");
            if (spellid && bot->IsSpellReady(spellid))
            {
                return TargetOfFearCastTrigger::IsActive();
            }

            return false;
        }
    };

    // 触发器：横扫攻击
    class SweepingStrikesTrigger : public SpellCanBeCastedTrigger
    {
    public:
        SweepingStrikesTrigger(PlayerbotAI* ai) : SpellCanBeCastedTrigger(ai, "sweeping strikes") {}
        bool IsActive() override
        {
            return SpellCanBeCastedTrigger::IsActive();
        }
    };

    // 触发器：嗜血
    class BloodthirstTrigger : public SpellCanBeCastedTrigger
    {
    public:
        BloodthirstTrigger(PlayerbotAI* ai) : SpellCanBeCastedTrigger(ai, "bloodthirst") {}
        bool IsActive() override
        {
// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
            return SpellCanBeCastedTrigger::IsActive() && (AI_VALUE2(uint8, "health", "current target") > 20 || ai->IsTank(bot));
#elif MANGOSBOT_ONE
            return SpellCanBeCastedTrigger::IsActive()
                && (AI_VALUE2(uint8, "health", "current target") > 20 || AI_VALUE2(uint8, "rage", "self target") >= 40);
#else
            return SpellCanBeCastedTrigger::IsActive();
#endif

        }
    };

    // 触发器：旋风斩
    class WhirlwindTrigger : public SpellCanBeCastedTrigger
    {
    public:
        WhirlwindTrigger(PlayerbotAI* ai) : SpellCanBeCastedTrigger(ai, "whirlwind") {}
        bool IsActive() override
        {
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
            return SpellCanBeCastedTrigger::IsActive();
#else
            return SpellCanBeCastedTrigger::IsActive() && AI_VALUE2(uint8, "health", "current target") > 20;
#endif
        }
    };

    // 触发器：英勇打击
    class HeroicStrikeTrigger : public SpellCanBeCastedTrigger
    {
    public:
        HeroicStrikeTrigger(PlayerbotAI* ai) : SpellCanBeCastedTrigger(ai, "heroic strike") {}
        bool IsActive() override
        {
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
            return SpellCanBeCastedTrigger::IsActive();
#else
            bool hasTalents = bot->HasSpell(12294) || bot->HasSpell(21551) || bot->HasSpell(21552) || bot->HasSpell(21553) || bot->HasSpell(25248) || bot->HasSpell(30330) || bot->HasSpell(23881) || bot->HasSpell(23892) || bot->HasSpell(23893) || bot->HasSpell(23894) || bot->HasSpell(25251) || bot->HasSpell(30335);
            if ((hasTalents && AI_VALUE2(uint8, "rage", "self target") > 60) || (!hasTalents && AI_VALUE2(uint8, "rage", "self target") >= 15))
            {
                return SpellCanBeCastedTrigger::IsActive()
                    && (AI_VALUE2(uint8, "health", "current target") > 20 || ai->IsTank(bot));
            }
            return false;
#endif
        }
    };

    // 触发器：猛击
    class SlamTrigger : public SpellCanBeCastedTrigger
    {
    public:
        SlamTrigger(PlayerbotAI* ai) : SpellCanBeCastedTrigger(ai, "slam") {}
    };
}
