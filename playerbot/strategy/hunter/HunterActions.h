// 猎人 - 动作头文件 (HunterActions.h)：定义猎人专用技能施放与战斗动作
#pragma once

#include "playerbot/strategy/actions/GenericActions.h"

namespace ai
{
    // 远程减益动作定义：猎人印记 (CastHuntersMarkAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastHuntersMarkAction, "hunter's mark")
    END_SPELL_ACTION()

    // 施放自动射击动作
    class CastAutoShotAction : public CastSpellAction
    {
    public:
        CastAutoShotAction(PlayerbotAI* ai) : CastSpellAction(ai, "auto shot") {}
        bool Execute(Event& event) override;
        bool isUseful() override;
    };

    // 施放装备弹药动作
    class HunterEquipAmmoAction : public Action
{
public:
    HunterEquipAmmoAction(PlayerbotAI* ai) : Action(ai, "equip ammo") {}
    virtual bool Execute(Event& event) override;
};

    // 远程法术动作定义：宁神射击 (CastTranquilizingShotAction)
    BEGIN_RANGED_SPELL_ACTION(CastTranquilizingShotAction, "tranquilizing shot")
    END_SPELL_ACTION()

    // 远程法术动作定义：奥术射击 (CastArcaneShotAction)
    BEGIN_RANGED_SPELL_ACTION(CastArcaneShotAction, "arcane shot")
    END_SPELL_ACTION()

    // 远程法术动作定义：爆炸射击 (CastExplosiveShotAction)
    BEGIN_RANGED_SPELL_ACTION(CastExplosiveShotAction, "explosive shot")
    END_SPELL_ACTION()

    // 远程法术动作定义：瞄准射击 (CastAimedShotAction)
    BEGIN_RANGED_SPELL_ACTION(CastAimedShotAction, "aimed shot")
    END_SPELL_ACTION()

    // 远程法术动作定义：奇美拉射击 (CastChimeraShotAction)
    BEGIN_RANGED_SPELL_ACTION(CastChimeraShotAction, "chimera shot")
    END_SPELL_ACTION()

    // 远程减益动作定义：震荡射击 (CastConcussiveShotAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastConcussiveShotAction, "concussive shot")
    END_SPELL_ACTION()

    // 远程减益动作定义：驱散射击 (CastScatterShotAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastScatterShotAction, "scatter shot")
    END_SPELL_ACTION()

    // 施放驱散射击动作
    class CastScatterShotOnClosestAttackerTargetingMeAction : public CastRangedDebuffSpellAction
    {
    public:
        CastScatterShotOnClosestAttackerTargetingMeAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "scatter shot") {}
        std::string GetTargetName() override { return "closest attacker targeting me"; }
    };

    // 远程法术动作定义：扰乱射击 (CastDistractingShotAction)
    BEGIN_RANGED_SPELL_ACTION(CastDistractingShotAction, "distracting shot")
    END_SPELL_ACTION()

    // 远程法术动作定义：多重射击 (CastMultiShotAction)
    BEGIN_RANGED_SPELL_ACTION(CastMultiShotAction, "multi-shot")
    END_SPELL_ACTION()

    // 远程法术动作定义：乱射 (CastVolleyAction)
    BEGIN_RANGED_SPELL_ACTION(CastVolleyAction, "volley")
    END_SPELL_ACTION()

    // 远程减益动作定义：毒蛇钉刺 (CastSerpentStingAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastSerpentStingAction, "serpent sting")
        virtual bool isUseful();
    END_SPELL_ACTION()

    // 远程减益动作定义：蝮蛇钉刺 (CastViperStingAction)
    BEGIN_RANGED_DEBUFF_ACTION(CastViperStingAction, "viper sting")
        virtual bool isUseful();
    END_SPELL_ACTION()

    // 远程法术动作定义：毒蝎钉刺 (CastScorpidStingAction)
    BEGIN_RANGED_SPELL_ACTION(CastScorpidStingAction, "scorpid sting")
    END_SPELL_ACTION()

    // 施放误导动作
    class MisdirectionOnPartyTankAction : public BuffOnTankAction
    {
    public:
        MisdirectionOnPartyTankAction(PlayerbotAI* ai) : BuffOnTankAction(ai, "misdirection") {}
    };

    // 施放灵猴守护动作
    class CastAspectOfTheMonkeyAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfTheMonkeyAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the monkey") {}
    };

    // 施放雄鹰守护动作
    class CastAspectOfTheHawkAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfTheHawkAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the hawk") {}
    };

    // 施放野性守护动作
    class CastAspectOfTheWildAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfTheWildAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the wild") {}
    };

    // 施放猎豹守护动作
    class CastAspectOfTheCheetahAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfTheCheetahAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the cheetah") {}
        
        bool isUseful() override
        {
            return CastBuffSpellAction::isUseful() && !AI_VALUE(bool, "has attackers");
        }
    };

    // 施放豹群守护动作
    class CastAspectOfThePackAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfThePackAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the pack") {}
    
        bool isUseful() override
        {
            return CastBuffSpellAction::isUseful() && !AI_VALUE(bool, "has attackers");
        }
    };

    // 施放蝮蛇守护动作
    class CastAspectOfTheViperAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfTheViperAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the viper") {}
    };

    // 施放野兽守护动作
    class CastAspectOfTheBeastAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfTheBeastAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the beast") {}
    };

    // 施放龙鹰守护动作
    class CastAspectOfTheDragonhawkAction : public CastBuffSpellAction
    {
    public:
        CastAspectOfTheDragonhawkAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the dragonhawk") {}
    };

    // 施放召唤宠物动作
    class CastCallPetAction : public CastBuffSpellAction
    {
    public:
        CastCallPetAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call pet") {}
    };

    // 施放治疗宠物动作
    class CastMendPetAction : public CastAuraSpellAction
    {
    public:
        CastMendPetAction(PlayerbotAI* ai) : CastAuraSpellAction(ai, "mend pet") {}
        virtual std::string GetTargetName() override { return "pet target"; }
    };

    // 施放复活宠物动作
    class CastRevivePetAction : public CastBuffSpellAction
    {
    public:
        CastRevivePetAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "revive pet") {}
    };

    // 施放强击光环动作
    class CastTrueshotAuraAction : public CastBuffSpellAction
    {
    public:
        CastTrueshotAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "trueshot aura") {}
    };

    // 施放假死动作
    class CastFeignDeathAction : public CastBuffSpellAction
    {
    public:
        CastFeignDeathAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "feign death") {}
    };

    // 取消增益状态动作：假死 (RemoveFeignDeathAction)
    REMOVE_BUFF_ACTION(RemoveFeignDeathAction, "feign death");

    // 施放急速射击动作
    class CastRapidFireAction : public CastBuffSpellAction
    {
    public:
        CastRapidFireAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "rapid fire") {}
    };

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
    // 施放杀戮命令动作
    class CastKillCommandAction : public CastBuffSpellAction
    {
    public:
        CastKillCommandAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "kill command") {}
    };
#else
    // 法术施放动作：杀戮命令 (CastKillCommandAction)
    SPELL_ACTION(CastKillCommandAction, "kill command");
#endif

    // 施放黑箭动作
    class CastBlackArrow : public CastRangedDebuffSpellAction
    {
    public:
        CastBlackArrow(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "black arrow") {}
    };

    // 减速技能动作：黑箭 (CastBlackArrowSnareAction)
    SNARE_ACTION(CastBlackArrowSnareAction, "black arrow");
    // 法术施放动作：沉默射击 (CastSilencingShotAction)
    SPELL_ACTION(CastSilencingShotAction, "silencing shot");
    // 针对敌方治疗动作：沉默射击 (CastSilencingShotOnHealerAction)
    ENEMY_HEALER_ACTION(CastSilencingShotOnHealerAction, "silencing shot");
    // 自我增益动作：准备就绪 (CastReadinessAction)
    BUFF_ACTION(CastReadinessAction, "readiness");
    ;
    // 施放摔绊动作
    class CastWingClipAction : public CastMeleeSpellAction
    {
    public:
        CastWingClipAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "wing clip") {}

        virtual bool isUseful()
        {
            return CastMeleeSpellAction::isUseful() && !ai->HasAura(GetSpellName(), GetTarget());
        }
    };

    // 施放猛禽一击动作
    class CastRaptorStrikeAction : public CastMeleeSpellAction
    {
    public:
        CastRaptorStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "raptor strike") {}

        virtual bool isUseful()
        {
            Unit* target = GetTarget();
            return CastMeleeSpellAction::isUseful() && (ai->HasStrategy("close", BotState::BOT_STATE_COMBAT) || bot->hasUnitState(UNIT_STAT_MELEE_ATTACKING));
        }
    };

    // 施放毒蛇钉刺动作
    class CastSerpentStingOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastSerpentStingOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "serpent sting") {}
    };

    // 施放蝮蛇钉刺动作
    class CastViperStingOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastViperStingOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "viper sting") {}
    };

    // 施放喂养宠物动作
    class FeedPetAction : public Action
    {
    public:
        FeedPetAction(PlayerbotAI* ai) : Action(ai, "feed pet") {}
        virtual bool Execute(Event& event);
    };

    // 施放狂野怒火动作
    class CastBestialWrathAction : public CastBuffSpellAction
    {
    public:
        CastBestialWrathAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bestial wrath") {}
    };

    // 施放恐吓野兽动作
    class CastScareBeastAction : public CastSpellAction
    {
    public:
        CastScareBeastAction(PlayerbotAI* ai) : CastSpellAction(ai, "scare beast") {}
    };

    // 施放恐吓野兽动作
    class CastScareBeastCcAction : public CastCrowdControlSpellAction
    {
    public:
        CastScareBeastCcAction(PlayerbotAI* ai) : CastCrowdControlSpellAction(ai, "scare beast") {}
    };

    // 自我增益动作：胁迫 (IntimidationAction)
    BUFF_ACTION(IntimidationAction, "intimidation");
    // 自我增益动作：威慑 (DeterrenceAction)
    BUFF_ACTION(DeterrenceAction, "deterrence");
    // 近战技能动作：反击 (CastCounterattackAction)
    MELEE_ACTION(CastCounterattackAction, "counterattack");
    // 减速技能动作：翼龙钉刺 (WyvernStingSnareAction)
    SNARE_ACTION(WyvernStingSnareAction, "wyvern sting");
    // 近战技能动作：猫鼬撕咬 (MongooseBiteAction)
    MELEE_ACTION(MongooseBiteAction, "mongoose bite");

    // 施放驯服野兽动作
    class TameBeastAction : public CastSpellAction
    {
    public:
        TameBeastAction(PlayerbotAI* ai) : CastSpellAction(ai, "tame beast") {}
    };

    // 施放照明弹动作
    class CastFlareAction : public CastSpellAction
    {
    public:
        CastFlareAction(PlayerbotAI* ai) : CastSpellAction(ai, "flare") {}
        virtual std::string GetTargetName() override { return "nearest stealthed unit"; }
    };

    // 施放稳固射击动作
    class CastSteadyShotAction : public CastSpellAction
    {
    public:
        CastSteadyShotAction(PlayerbotAI* ai) : CastSpellAction(ai, "steady shot") {}
        virtual bool Execute(Event& event);

    private:
        uint32 weaponDelay;
    };

    // 在目标脚下放置陷阱动作
    class TrapOnTargetAction : public CastSpellAction
    {
    public:
// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
        // For vanilla, bots need to feign death before dropping the trap
        TrapOnTargetAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, "feign death"), trapSpell(spell)
        {
            trapSpellID = AI_VALUE2(uint32, "spell id", trapSpell);
        }
#else
        TrapOnTargetAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell), trapSpell(spell) {}
#endif

    protected:
        // Traps don't really have target for the spell
        std::string GetTargetName() override { return "self target"; }

        // The move to target
        virtual std::string GetTrapTargetName() { return "current target"; }

        // The trap spell that will be used
        std::string GetTrapSpellName() { return trapSpell; }

        std::string GetReachActionName() override { return "reach melee"; }
        std::string GetTargetQualifier() override { return GetTrapSpellName(); }
        ActionThreatType getThreatType() override { return ActionThreatType::ACTION_THREAT_NONE; }

        NextAction** getPrerequisites() override
        {
            const std::string reachAction = GetReachActionName();
            const std::string spellName = GetSpellName();
            const std::string targetName = GetTrapTargetName();

            // Generate the reach action with qualifiers
            std::vector<std::string> qualifiers = { spellName, targetName, trapSpell };
            const std::string qualifiersStr = Qualified::MultiQualify(qualifiers, "::");
            return NextAction::merge(NextAction::array(0, new NextAction(reachAction + "::" + qualifiersStr), NULL), Action::getPrerequisites());
        }

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
        bool isPossible() override
        {
            // If the trap spell and feign death are not on cooldown
            return sServerFacade.IsSpellReady(bot, trapSpellID) && sServerFacade.IsSpellReady(bot, 5384);
        }

        NextAction** getContinuers() override
        {
            return NextAction::merge(NextAction::array(0, new NextAction(trapSpell, ACTION_PASSTROUGH), NULL), CastSpellAction::getContinuers());
        }
#endif

private:
        std::string trapSpell;
        uint32 trapSpellID;
    };

    // 在控制目标脚下放置陷阱动作
    class TrapOnCcTargetAction : public TrapOnTargetAction
    {
    public:
        TrapOnCcTargetAction(PlayerbotAI* ai, std::string spell) : TrapOnTargetAction(ai, spell) {}
        std::string GetTrapTargetName() override { return "cc target"; }
    };

    // TrapInPlace
    class TrapInPlace : public TrapOnTargetAction
    {
    public:
        TrapInPlace(PlayerbotAI* ai, std::string spell) : TrapOnTargetAction(ai, spell) {}
        std::string GetTrapTargetName() override { return "self target"; }
    };

    // 放置猎人陷阱动作
    class CastTrapAction : public CastSpellAction
    {
    public:
        CastTrapAction(PlayerbotAI* ai, std::string spell) : CastSpellAction(ai, spell) {}

        // Traps don't really have target for the spell
        std::string GetTargetName() override { return "self target"; }

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
        bool Execute(Event& event) override
        {
            // The trap could come just after feign death, so better remove it
            ai->RemoveAura("feign death");
            return CastSpellAction::Execute(event);
        }
#endif
    };

    // 施放献祭陷阱动作
    class CastImmolationTrapAction : public CastTrapAction
    {
    public:
        CastImmolationTrapAction(PlayerbotAI* ai) : CastTrapAction(ai, "immolation trap") {}
    };

    // 施放献祭陷阱动作
    class CastImmolationTrapOnTargetAction : public TrapOnTargetAction
    {
    public:
        CastImmolationTrapOnTargetAction(PlayerbotAI* ai) : TrapOnTargetAction(ai, "immolation trap") {}
    };

    // 放置猎人陷阱动作
    class CastImmolationTrapInPlaceAction : public TrapInPlace
    {
    public:
        CastImmolationTrapInPlaceAction(PlayerbotAI* ai) : TrapInPlace(ai, "immolation trap") {}
    };

    // 施放冰冻陷阱动作
    class CastFreezingTrapAction : public CastTrapAction
    {
    public:
        CastFreezingTrapAction(PlayerbotAI* ai) : CastTrapAction(ai, "freezing trap") {}
    };

    // 施放冰冻陷阱动作
    class CastFreezingTrapOnTargetAction : public TrapOnTargetAction
    {
    public:
        CastFreezingTrapOnTargetAction(PlayerbotAI* ai) : TrapOnTargetAction(ai, "freezing trap") {}
    };

    // 放置猎人陷阱动作
    class CastFreezingTrapInPlaceAction : public TrapInPlace
    {
    public:
        CastFreezingTrapInPlaceAction(PlayerbotAI* ai) : TrapInPlace(ai, "freezing trap") {}
    };

    // 施放冰冻陷阱动作
    class CastFreezingTrapOnCcAction : public TrapOnCcTargetAction
    {
    public:
        CastFreezingTrapOnCcAction(PlayerbotAI* ai) : TrapOnCcTargetAction(ai, "freezing trap") {}
    };

    // 施放冰霜陷阱动作
    class CastFrostTrapAction : public CastTrapAction
    {
    public:
        CastFrostTrapAction(PlayerbotAI* ai) : CastTrapAction(ai, "frost trap") {}
    };

    // 施放冰霜陷阱动作
    class CastFrostTrapOnTargetAction : public TrapOnTargetAction
    {
    public:
        CastFrostTrapOnTargetAction(PlayerbotAI* ai) : TrapOnTargetAction(ai, "frost trap") {}
    };

    // 放置猎人陷阱动作
    class CastFrostTrapInPlaceAction : public TrapInPlace
    {
    public:
        CastFrostTrapInPlaceAction(PlayerbotAI* ai) : TrapInPlace(ai, "frost trap") {}
    };

    // 施放爆炸陷阱动作
    class CastExplosiveTrapAction : public CastTrapAction
    {
    public:
        CastExplosiveTrapAction(PlayerbotAI* ai) : CastTrapAction(ai, "explosive trap") {}
    };

    // 施放爆炸陷阱动作
    class CastExplosiveTrapOnTargetAction : public TrapOnTargetAction
    {
    public:
        CastExplosiveTrapOnTargetAction(PlayerbotAI* ai) : TrapOnTargetAction(ai, "explosive trap") {}
    };

    // 放置猎人陷阱动作
    class CastExplosiveTrapInPlaceAction : public TrapInPlace
    {
    public:
        CastExplosiveTrapInPlaceAction(PlayerbotAI* ai) : TrapInPlace(ai, "explosive trap") {}
    };

    // 施放解散宠物动作
    class CastDismissPetAction : public CastSpellAction
    {
    public:
        CastDismissPetAction(PlayerbotAI* ai) : CastSpellAction(ai, "dismiss pet") {}

        std::string GetTargetName() override { return "self target"; }

        bool isUseful() override
        {
            return ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
        }
    };

    // 施放更新PVE策略动作
    class UpdateHunterPveStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateHunterPveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
        {
            std::vector<std::string> strategiesRequired = { "beast mastery" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "beast mastery pve", strategiesRequired);

            strategiesRequired = { "beast mastery", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe beast mastery pve", strategiesRequired);

            strategiesRequired = { "beast mastery", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff beast mastery pve", strategiesRequired);

            strategiesRequired = { "beast mastery", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost beast mastery pve", strategiesRequired);

            strategiesRequired = { "beast mastery", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc beast mastery pve", strategiesRequired);

            strategiesRequired = { "beast mastery", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting beast mastery pve", strategiesRequired);

            strategiesRequired = { "beast mastery", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect beast mastery pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect beast mastery pve", strategiesRequired);

            strategiesRequired = { "marksmanship" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "marksmanship pve", strategiesRequired);

            strategiesRequired = { "marksmanship", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe marksmanship pve", strategiesRequired);

            strategiesRequired = { "marksmanship", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff marksmanship pve", strategiesRequired);

            strategiesRequired = { "marksmanship", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost marksmanship pve", strategiesRequired);

            strategiesRequired = { "marksmanship", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc marksmanship pve", strategiesRequired);

            strategiesRequired = { "marksmanship", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting marksmanship pve", strategiesRequired);

            strategiesRequired = { "marksmanship", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect marksmanship pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect marksmanship pve", strategiesRequired);

            strategiesRequired = { "survival" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "survival pve", strategiesRequired);

            strategiesRequired = { "survival", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe survival pve", strategiesRequired);

            strategiesRequired = { "survival", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff survival pve", strategiesRequired);

            strategiesRequired = { "survival", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost survival pve", strategiesRequired);

            strategiesRequired = { "survival", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc survival pve", strategiesRequired);

            strategiesRequired = { "survival", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting survival pve", strategiesRequired);

            strategiesRequired = { "survival", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect survival pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect survival pve", strategiesRequired);
        }
    };

    // 施放更新PVP策略动作
    class UpdateHunterPvpStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateHunterPvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
        {
            std::vector<std::string> strategiesRequired = { "beast mastery" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "beast mastery pvp", strategiesRequired);

            strategiesRequired = { "beast mastery", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe beast mastery pvp", strategiesRequired);

            strategiesRequired = { "beast mastery", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff beast mastery pvp", strategiesRequired);

            strategiesRequired = { "beast mastery", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost beast mastery pvp", strategiesRequired);

            strategiesRequired = { "beast mastery", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc beast mastery pvp", strategiesRequired);

            strategiesRequired = { "beast mastery", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting beast mastery pvp", strategiesRequired);

            strategiesRequired = { "beast mastery", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect beast mastery pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect beast mastery pvp", strategiesRequired);

            strategiesRequired = { "marksmanship" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "marksmanship pvp", strategiesRequired);

            strategiesRequired = { "marksmanship", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe marksmanship pvp", strategiesRequired);

            strategiesRequired = { "marksmanship", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff marksmanship pvp", strategiesRequired);

            strategiesRequired = { "marksmanship", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost marksmanship pvp", strategiesRequired);

            strategiesRequired = { "marksmanship", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc marksmanship pvp", strategiesRequired);

            strategiesRequired = { "marksmanship", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting marksmanship pvp", strategiesRequired);

            strategiesRequired = { "marksmanship", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect marksmanship pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect marksmanship pvp", strategiesRequired);

            strategiesRequired = { "survival" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "survival pvp", strategiesRequired);

            strategiesRequired = { "survival", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe survival pvp", strategiesRequired);

            strategiesRequired = { "survival", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff survival pvp", strategiesRequired);

            strategiesRequired = { "survival", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost survival pvp", strategiesRequired);

            strategiesRequired = { "survival", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc survival pvp", strategiesRequired);

            strategiesRequired = { "survival", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting survival pvp", strategiesRequired);

            strategiesRequired = { "survival", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect survival pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect survival pvp", strategiesRequired);
        }
    };

    // 施放更新团队副本策略动作
    class UpdateHunterRaidStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateHunterRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
        {
            std::vector<std::string> strategiesRequired = { "beast mastery" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "beast mastery raid", strategiesRequired);

            strategiesRequired = { "beast mastery", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe beast mastery raid", strategiesRequired);

            strategiesRequired = { "beast mastery", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff beast mastery raid", strategiesRequired);

            strategiesRequired = { "beast mastery", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost beast mastery raid", strategiesRequired);

            strategiesRequired = { "beast mastery", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc beast mastery raid", strategiesRequired);

            strategiesRequired = { "beast mastery", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting beast mastery raid", strategiesRequired);

            strategiesRequired = { "beast mastery", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect beast mastery raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect beast mastery raid", strategiesRequired);

            strategiesRequired = { "marksmanship" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "marksmanship raid", strategiesRequired);

            strategiesRequired = { "marksmanship", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe marksmanship raid", strategiesRequired);

            strategiesRequired = { "marksmanship", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff marksmanship raid", strategiesRequired);

            strategiesRequired = { "marksmanship", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost marksmanship raid", strategiesRequired);

            strategiesRequired = { "marksmanship", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc marksmanship raid", strategiesRequired);

            strategiesRequired = { "marksmanship", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting marksmanship raid", strategiesRequired);

            strategiesRequired = { "marksmanship", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect marksmanship raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect marksmanship raid", strategiesRequired);

            strategiesRequired = { "survival" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "survival raid", strategiesRequired);

            strategiesRequired = { "survival", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe survival raid", strategiesRequired);

            strategiesRequired = { "survival", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff survival raid", strategiesRequired);

            strategiesRequired = { "survival", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost survival raid", strategiesRequired);

            strategiesRequired = { "survival", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc survival raid", strategiesRequired);

            strategiesRequired = { "survival", "sting" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "sting survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "sting survival raid", strategiesRequired);

            strategiesRequired = { "survival", "aspect" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aspect survival raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aspect survival raid", strategiesRequired);
        }
    };
}
