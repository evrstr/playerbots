// 战士 - 动作头文件 (WarriorActions.h)：定义战士专用技能施放与战斗动作
#pragma once
#include "playerbot/strategy/actions/GenericActions.h"

namespace ai
{
    // stances
    // 自我增益动作：战斗姿态 (CastBattleStanceAction)
    BUFF_ACTION(CastBattleStanceAction, "battle stance");
    // 自我增益动作：防御姿态 (CastDefensiveStanceAction)
    BUFF_ACTION(CastDefensiveStanceAction, "defensive stance");
    // 自我增益动作：狂暴姿态 (CastBerserkerStanceAction)
    BUFF_ACTION(CastBerserkerStanceAction, "berserker stance");

    // shouts
    // 条件近战技能动作：战斗怒吼 (CastBattleShoutTauntAction)
    MELEE_ACTION_U(CastBattleShoutTauntAction, "battle shout", CastSpellAction::isUseful()); // useful to rebuff
    // 范围近战减益动作：挫志怒吼 (CastDemoralizingShoutAction)
    MELEE_DEBUFF_ACTION_R(CastDemoralizingShoutAction, "demoralizing shout", 8.0f); // low range debuff
    // 近战技能动作：挑战怒吼 (CastChallengingShoutAction)
    MELEE_ACTION(CastChallengingShoutAction, "challenging shout");
    // 范围近战减益动作：破胆怒吼 (CastIntimidatingShoutAction)
    MELEE_DEBUFF_ACTION_R(CastIntimidatingShoutAction, "intimidating shout", 8.0f);
    // shouts 2.4.3
    // 自我增益动作：命令怒吼 (CastCommandingShoutAction)
    BUFF_ACTION(CastCommandingShoutAction, "commanding shout");

    // arms
    // 近战技能动作：英勇打击 (CastHeroicStrikeAction)
    MELEE_ACTION(CastHeroicStrikeAction, "heroic strike");
    // 突进/接近目标动作：冲锋 (CastChargeAction)
    REACH_ACTION(CastChargeAction, "charge", 8.0f);
    // 近战减益技能动作：撕裂 (CastRendAction)
    MELEE_DEBUFF_ACTION(CastRendAction, "rend");
    // 对敌方目标近战减益动作：撕裂 (CastRendOnAttackerAction)
    MELEE_DEBUFF_ENEMY_ACTION(CastRendOnAttackerAction, "rend");
    // 范围近战减益动作：雷霆一击 (CastThunderClapAction)
    MELEE_DEBUFF_ACTION_R(CastThunderClapAction, "thunder clap", 8.0f);
    // 法术施放动作：雷霆一击 (CastThunderClapThreatAction)
    SPELL_ACTION(CastThunderClapThreatAction, "thunder clap");
    // 减速技能动作：雷霆一击 (CastThunderClapSnareAction)
    SNARE_ACTION(CastThunderClapSnareAction, "thunder clap");
    // 减速技能动作：断筋 (CastHamstringAction)
    SNARE_ACTION(CastHamstringAction, "hamstring");
    // 近战技能动作：压制 (CastOverpowerAction)
    MELEE_ACTION(CastOverpowerAction, "overpower");
    // 近战技能动作：惩戒痛击 (CastMockingBlowAction)
    MELEE_ACTION(CastMockingBlowAction, "mocking blow");
    // 自我增益动作：反击风暴 (CastRetaliationAction)
    BUFF_ACTION(CastRetaliationAction, "retaliation");
    // arms 3.3.5
    // 法术施放动作：英勇投掷 (CastHeroicThrowAction)
    SPELL_ACTION(CastHeroicThrowAction, "heroic throw");
    // 减速技能动作：英勇投掷 (CastHeroicThrowSnareAction)
    SNARE_ACTION(CastHeroicThrowSnareAction, "heroic throw");
    // 远程减益技能动作：碎裂投掷 (CastShatteringThrowAction)
    RANGED_DEBUFF_ACTION(CastShatteringThrowAction, "shattering throw");
    
    // arms talents
    // 近战技能动作：致死打击 (CastMortalStrikeAction)
    MELEE_ACTION(CastMortalStrikeAction, "mortal strike");
    // 自我增益动作：横扫攻击 (CastSweepingStrikesAction)
    BUFF_ACTION(CastSweepingStrikesAction, "sweeping strikes");
    // arms talents 3.3.5
    // 自我增益动作：剑刃风暴 (CastBladestormAction)
    BUFF_ACTION(CastBladestormAction, "bladestorm");

    // fury
    // 近战技能动作：顺劈斩 (CastCleaveAction)
    MELEE_ACTION(CastCleaveAction, "cleave");
    // 近战技能动作：斩杀 (CastExecuteAction)
    MELEE_ACTION(CastExecuteAction, "execute");
    // 突进/接近目标动作：拦截 (CastInterceptAction)
    REACH_ACTION(CastInterceptAction, "intercept", 8.0f);
    // 针对敌方治疗动作：拦截 (CastInterceptOnEnemyHealerAction)
    ENEMY_HEALER_ACTION(CastInterceptOnEnemyHealerAction, "intercept");
    // 减速技能动作：拦截 (CastInterceptOnSnareTargetAction)
    SNARE_ACTION(CastInterceptOnSnareTargetAction, "intercept");
    // 近战技能动作：猛击 (CastSlamAction)
    MELEE_ACTION(CastSlamAction, "slam");
    // 自我增益动作：狂暴之怒 (CastBerserkerRageAction)
    BUFF_ACTION(CastBerserkerRageAction, "berserker rage");
    // 近战技能动作：旋风斩 (CastWhirlwindAction)
    MELEE_ACTION(CastWhirlwindAction, "whirlwind");
    // 近战技能动作：拳击 (CastPummelAction)
    MELEE_ACTION(CastPummelAction, "pummel");
    // 针对敌方治疗动作：拳击 (CastPummelOnEnemyHealerAction)
    ENEMY_HEALER_ACTION(CastPummelOnEnemyHealerAction, "pummel");
    // 自我增益动作：鲁莽 (CastRecklessnessAction)
    BUFF_ACTION(CastRecklessnessAction, "recklessness");
    // fury 2.4.3
    // 近战技能动作：乘胜追击 (CastVictoryRushAction)
    MELEE_ACTION(CastVictoryRushAction, "victory rush");
    // fury 3.3.5
    // 自我增益动作：狂怒回复 (CastEnragedRegenerationAction)
    BUFF_ACTION(CastEnragedRegenerationAction, "enraged regeneration");
    // 自我增益动作：英勇之怒 (CastHeroicFuryAction)
    BUFF_ACTION(CastHeroicFuryAction, "heroic fury");

    // fury talents
    // 自我增益动作：死亡之愿 (CastDeathWishAction)
    BUFF_ACTION(CastDeathWishAction, "death wish");
    // 近战技能动作：嗜血 (CastBloodthirstAction)
    MELEE_ACTION(CastBloodthirstAction, "bloodthirst");
    // 范围近战减益动作：刺耳怒吼 (CastPiercingHowlAction)
    MELEE_DEBUFF_ACTION_R(CastPiercingHowlAction, "piercing howl", 8.0f);
    // fury talents 2.4.3
    // 自我增益动作：暴怒 (CastRampageAction)
    BUFF_ACTION(CastRampageAction, "rampage");

    // protection
    // 条件法术施放动作：嘲讽 (CastTauntAction)
    SPELL_ACTION_U(CastTauntAction, "taunt", GetTarget() && GetTarget()->GetVictim() && GetTarget()->GetVictim() != bot);
    // 减速技能动作：嘲讽 (CastTauntOnSnareTargetAction)
    SNARE_ACTION(CastTauntOnSnareTargetAction, "taunt");
    // 自我增益动作：血性狂暴 (CastBloodrageAction)
    BUFF_ACTION(CastBloodrageAction, "bloodrage");
    // 近战技能动作：盾击 (CastShieldBashAction)
    MELEE_ACTION(CastShieldBashAction, "shield bash");
    // 针对敌方治疗动作：盾击 (CastShieldBashOnEnemyHealerAction)
    ENEMY_HEALER_ACTION(CastShieldBashOnEnemyHealerAction, "shield bash");
    // 近战技能动作：复仇 (CastRevengeAction)
    MELEE_ACTION(CastRevengeAction, "revenge");
    // 自我增益动作：盾牌格挡 (CastShieldBlockAction)
    BUFF_ACTION(CastShieldBlockAction, "shield block");
    // 条件近战减益动作：缴械 (CastDisarmAction)
    MELEE_DEBUFF_ACTION_U(CastDisarmAction, "disarm", GetTarget() && GetTarget()->IsPlayer() ? !ai->IsRanged((Player*)GetTarget()) : CastMeleeDebuffSpellAction::isUseful());
    // 对敌方目标近战减益动作：缴械 (CastDisarmOnAttackerAction)
    MELEE_DEBUFF_ENEMY_ACTION(CastDisarmOnAttackerAction, "disarm");
    // 自我增益动作：盾墙 (CastShieldWallAction)
    BUFF_ACTION(CastShieldWallAction, "shield wall");
    // protection 2.4.3
    // 保护技能动作：援护 (CastInterveneAction)
    PROTECT_ACTION(CastInterveneAction, "intervene");
    // 自我增益动作：法术反射 (CastSpellReflectionAction)
    BUFF_ACTION(CastSpellReflectionAction, "spell reflection");

    // protection talents
    // 自我增益动作：破釜沉舟 (CastLastStandAction)
    BUFF_ACTION(CastLastStandAction, "last stand");
    // 近战技能动作：盾牌猛击 (CastShieldSlamAction)
    MELEE_ACTION(CastShieldSlamAction, "shield slam");
    // 近战技能动作：震荡猛击 (CastConcussionBlowAction)
    MELEE_ACTION(CastConcussionBlowAction, "concussion blow");
    // protection talents 2.4.3
    // MELEE_ACTION(CastDevastateAction, "devastate");
    // protection talents 3.3.5
    // 范围近战减益动作：震荡波 (CastShockwaveAction)
    MELEE_DEBUFF_ACTION_R(CastShockwaveAction, "shockwave", 8.0f);
    // 减速技能动作：震荡波 (CastShockwaveSnareAction)
    SNARE_ACTION(CastShockwaveSnareAction, "shockwave");

    // 施放战斗怒吼动作
    class CastBattleShoutAction : public CastBuffSpellAction
    {
    public:
        CastBattleShoutAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "battle shout") {}

        bool isUseful() override
        {
            static const std::vector<uint32> battleShoutIds = {6673, 5242, 6192, 11549, 11550, 11551, 25289, 2048, 47436};

            for (uint32 id : battleShoutIds)
            {
                if (bot->HasAura(id))
                    return false;
            }

            return CastSpellAction::isUseful();
        }
    };

    // 施放破甲攻击动作
    class CastSunderArmorAction : public CastMeleeDebuffSpellAction
    {
    public:
        CastSunderArmorAction(PlayerbotAI* ai) : CastMeleeDebuffSpellAction(ai, "sunder armor")
        {
            range = ATTACK_DISTANCE;
        }

        virtual bool isUseful() override
        {
            Unit* target = GetTarget();
            if (!target)
                return false;

            const bool isTank = ai->IsTank(bot);

            if (isTank)
            {
                uint32 bloodThirst = AI_VALUE2(uint32, "spell id", "bloodthirst");
                uint32 mortalStrike = AI_VALUE2(uint32, "spell id", "mortal strike");
                uint32 shieldSlam = AI_VALUE2(uint32, "spell id", "shield slam");

                if ((bloodThirst && bot->IsSpellReady(bloodThirst)) ||
                    (mortalStrike && bot->IsSpellReady(mortalStrike)) ||
                    (shieldSlam && bot->IsSpellReady(shieldSlam)))
                {
                    return false;
                }
            }

            if (isTank && !target->IsPlayer())
                return true;

            return !ai->HasAura("sunder armor", target, true) && !ai->HasAura("expose armor", target);
        }
    };

    // 施放毁灭打击动作
    class CastDevastateAction : public CastMeleeSpellAction
    {
    public:
        CastDevastateAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "devastate") {}

        virtual bool isUseful() override
        {
            Unit* target = GetTarget();
            if (!target)
                return false;

            const bool isTank = ai->IsTank(bot);

            uint32 shieldSlam = AI_VALUE2(uint32, "spell id", "shield slam");

            if (shieldSlam)
            {
                return !bot->IsSpellReady(shieldSlam);
            }

            return true;
        }
    };

    // 施放更新PVE策略动作
    class UpdateWarriorPveStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateWarriorPveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
        {
            std::vector<std::string> strategiesRequired = { "arms" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "arms pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "arms pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "arms pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "arms pve", strategiesRequired);

            strategiesRequired = { "arms", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe arms pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe arms pve", strategiesRequired);

            strategiesRequired = { "arms", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff arms pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff arms pve", strategiesRequired);

            strategiesRequired = { "arms", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost arms pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost arms pve", strategiesRequired);

            strategiesRequired = { "arms", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc arms pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc arms pve", strategiesRequired);

            strategiesRequired = { "fury" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "fury pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "fury pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "fury pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "fury pve", strategiesRequired);

            strategiesRequired = { "fury", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe fury pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe fury pve", strategiesRequired);

            strategiesRequired = { "fury", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff fury pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff fury pve", strategiesRequired);

            strategiesRequired = { "fury", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost fury pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost fury pve", strategiesRequired);

            strategiesRequired = { "fury", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc fury pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc fury pve", strategiesRequired);

            strategiesRequired = { "protection/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost protection pve", strategiesRequired);

            strategiesRequired = { "protection/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc protection pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc protection pve", strategiesRequired);
        }
    };

    // 施放更新PVP策略动作
    class UpdateWarriorPvpStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateWarriorPvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
        {
            std::vector<std::string> strategiesRequired = { "arms" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "arms pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "arms pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "arms pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "arms pvp", strategiesRequired);

            strategiesRequired = { "arms", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe arms pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe arms pvp", strategiesRequired);

            strategiesRequired = { "arms", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff arms pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff arms pvp", strategiesRequired);

            strategiesRequired = { "arms", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost arms pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost arms pvp", strategiesRequired);

            strategiesRequired = { "arms", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc arms pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc arms pvp", strategiesRequired);

            strategiesRequired = { "fury" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "fury pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "fury pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "fury pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "fury pvp", strategiesRequired);

            strategiesRequired = { "fury", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe fury pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe fury pvp", strategiesRequired);

            strategiesRequired = { "fury", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff fury pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff fury pvp", strategiesRequired);

            strategiesRequired = { "fury", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost fury pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost fury pvp", strategiesRequired);

            strategiesRequired = { "fury", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc fury pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc fury pvp", strategiesRequired);

            strategiesRequired = { "protection/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost protection pvp", strategiesRequired);

            strategiesRequired = { "protection/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc protection pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc protection pvp", strategiesRequired);
        }
    };

    // 施放更新团队副本策略动作
    class UpdateWarriorRaidStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateWarriorRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
        {
            std::vector<std::string> strategiesRequired = { "arms" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "arms raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "arms raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "arms raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "arms raid", strategiesRequired);

            strategiesRequired = { "arms", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe arms raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe arms raid", strategiesRequired);

            strategiesRequired = { "arms", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff arms raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff arms raid", strategiesRequired);

            strategiesRequired = { "arms", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost arms raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost arms raid", strategiesRequired);

            strategiesRequired = { "arms", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc arms raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc arms raid", strategiesRequired);

            strategiesRequired = { "fury" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "fury raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "fury raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "fury raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "fury raid", strategiesRequired);

            strategiesRequired = { "fury", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe fury raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe fury raid", strategiesRequired);

            strategiesRequired = { "fury", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff fury raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff fury raid", strategiesRequired);

            strategiesRequired = { "fury", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost fury raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost fury raid", strategiesRequired);

            strategiesRequired = { "fury", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc fury raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc fury raid", strategiesRequired);

            strategiesRequired = { "protection/tank" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost protection raid", strategiesRequired);

            strategiesRequired = { "protection/tank", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc protection raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc protection raid", strategiesRequired);
        }
    };
}
