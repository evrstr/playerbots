// 术士 - 动作头文件 (WarlockActions.h)：定义术士专用技能施放与战斗动作
#pragma once

#include "playerbot/strategy/actions/GenericActions.h"
#include "playerbot/strategy/actions/UseItemAction.h"

namespace ai
{
    // 减速技能动作：凋零缠绕/死亡缠绕 (CastDeathCoilSnareAction)
    SNARE_ACTION(CastDeathCoilSnareAction, "death coil");
    // 针对敌方治疗动作：凋零缠绕/死亡缠绕 (CastDeathCoilOnHealerAction)
    ENEMY_HEALER_ACTION(CastDeathCoilOnHealerAction, "death coil");
    // 法术施放动作：凋零缠绕/死亡缠绕 (CastDeathCoilAction)
    SPELL_ACTION(CastDeathCoilAction, "death coil");
    // 自我增益动作：防护暗影结界 (CastShadowWardAction)
    BUFF_ACTION(CastShadowWardAction, "shadow ward");
    
    // 施放恶魔皮肤动作
    class CastDemonSkinAction : public CastBuffSpellAction 
    {
    public:
        CastDemonSkinAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demon skin") {}
    };

    // 施放魔甲术动作
    class CastDemonArmorAction : public CastBuffSpellAction
    {
    public:
        CastDemonArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demon armor") {}
    };

    // 施放邪甲术动作
    class CastFelArmorAction : public CastBuffSpellAction
    {
    public:
        CastFelArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fel armor") {}
    };

    // 远程法术动作定义：暗影箭 (CastShadowBoltAction)
    BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
    END_SPELL_ACTION()

    // 施放吸取灵魂动作
    class CastDrainSoulAction : public CastSpellAction
    {
    public:
        CastDrainSoulAction(PlayerbotAI* ai) : CastSpellAction(ai, "drain soul") {}
    };

    // 施放暗影灼烧动作
    class CastShadowburnAction : public CastSpellAction
    {
    public:
        CastShadowburnAction(PlayerbotAI* ai) : CastSpellAction(ai, "shadowburn") {}

        bool Execute(Event& event) override
        {
            if (CastSpellAction::Execute(event))
            {
                // Remove potential extra soul shard
                if (ai->HasCheat(BotCheatMask::item))
                {
                    Unit* target = GetTarget();
                    if (target && AI_VALUE2(uint8, "health", GetTargetName()) <= 20)
                    {
                        Item* soulShard = bot->GetItemByEntry(6265);
                        if (soulShard)
                        {
                            bot->DestroyItem(soulShard->GetBagSlot(), soulShard->GetSlot(), true);
                        }
                    }
                }
                
                return true;
            }

            return false;
        }
    };

    // 施放复活目标动作
    class CastSoulstoneAction : public CastItemTargetAction
    {
    public:
        CastSoulstoneAction(PlayerbotAI* ai) : CastItemTargetAction(ai, "revive targets", true, true) {}
        std::string GetTargetName() override { return "party member to soulstone"; }

    private:
        uint32 GetItemId() override 
        { 
            uint32 itemId = 0;
            const uint32 level = bot->GetLevel();
            if (level >= 18 && level < 30)
            {
                itemId = 5232;
            }
            else if (level >= 30 && level < 40)
            {
                itemId = 16892;
            }
            else if (level >= 40 && level < 50)
            {
                itemId = 16893;
            }
            else if (level >= 50 && level < 60)
            {
                itemId = 16895;
            }
            else if (level >= 60 && level < 70)
            {
                itemId = 16896;
            }
            else if (level >= 70 && level < 76)
            {
                itemId = 22116;
            }
            else if (level >= 76)
            {
                itemId = 36895;
            }

            return itemId;
        }
    };

    // 施放灵魂碎裂动作
    class CastSoulShatterAction : public CastSpellAction
    {
    public:
        CastSoulShatterAction(PlayerbotAI* ai) : CastSpellAction(ai, "soulshatter") {}
        std::string GetTargetName() override { return "self target"; }
    };

    // 施放灵魂之火动作
    class CastSoulFireAction : public CastSpellAction
    {
    public:
        CastSoulFireAction(PlayerbotAI* ai) : CastSpellAction(ai, "soul fire") {}
    };

    // 自我增益动作：黑暗契约 (CastDarkPactAction)
    BUFF_ACTION(CastDarkPactAction, "dark pact");

    // 施放吸取法力动作
    class CastDrainManaAction : public CastSpellAction
    {
    public:
        CastDrainManaAction(PlayerbotAI* ai) : CastSpellAction(ai, "drain mana") {}
    };

    // 施放吸取生命动作
    class CastDrainLifeAction : public CastSpellAction
    {
    public:
        CastDrainLifeAction(PlayerbotAI* ai) : CastSpellAction(ai, "drain life") {}
    };

    // 施放疲劳诅咒动作
    class CastCurseOfExhaustionAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfExhaustionAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of exhaustion") {}
    };

    // 施放腐蚀术动作
    class CastCorruptionAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCorruptionAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "corruption") {}
    };

    // 施放腐蚀术动作
    class CastCorruptionOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCorruptionOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "corruption") {}
    };

    // 施放腐蚀之种动作
    class CastSeedOfCorruptionOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastSeedOfCorruptionOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "seed of corruption") {}
    };

    // 施放痛苦无常动作
    class CastUnstableAfflictionOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastUnstableAfflictionOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "unstable affliction") {}
    };

    // 施放痛苦诅咒动作
    class CastCurseOfAgonyAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfAgonyAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of agony") {}
    };

    // 施放痛苦诅咒动作
    class CastCurseOfAgonyOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfAgonyOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "curse of agony") {}
    };

    // 施放厄运诅咒动作
    class CastCurseOfDoomAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfDoomAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of doom") {}
    };

    // 施放厄运诅咒动作
    class CastCurseOfDoomOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfDoomOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "curse of doom") {}
    };

    // 施放元素诅咒动作
    class CastCurseOfTheElementsAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfTheElementsAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of the elements") {}
    };

    // 施放元素诅咒动作
    class CastCurseOfTheElementsOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfTheElementsOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "curse of the elements") {}
    };

    // 施放鲁莽诅咒动作
    class CastCurseOfRecklessnessAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfRecklessnessAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of recklessness") {}
    };

    // 施放鲁莽诅咒动作
    class CastCurseOfRecklessnessOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfRecklessnessOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "curse of recklessness") {}
    };

    // 施放虚弱诅咒动作
    class CastCurseOfWeaknessAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfWeaknessAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of weakness") {}
    };

    // 施放虚弱诅咒动作
    class CastCurseOfWeaknessOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfWeaknessOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "curse of weakness") {}
    };

    // 施放语言诅咒动作
    class CastCurseOfTonguesAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfTonguesAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of tongues") {}
    };

    // 施放语言诅咒动作
    class CastCurseOfTonguesOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfTonguesOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "curse of tongues") {}
    };

    // 施放暗影诅咒动作
    class CastCurseOfShadowAction : public CastRangedDebuffSpellAction
    {
    public:
        CastCurseOfShadowAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "curse of shadow") {}
    };

    // 施放暗影诅咒动作
    class CastCurseOfShadowOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfShadowOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "curse of shadow") {}
    };

    // 施放恶魔牺牲动作
    class CastDemonicSacrificeAction : public CastBuffSpellAction
    {
    public:
        CastDemonicSacrificeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demonic sacrifice") {}
    };

    // 施放灵魂链接动作
    class CastSoulLinkAction : public CastBuffSpellAction
    {
    public:
        CastSoulLinkAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "soul link") {}
    };

    // 施放牺牲动作
    class CastSacrificeAction : public CastPetSpellAction
    {
    public:
        CastSacrificeAction(PlayerbotAI* ai) : CastPetSpellAction(ai, "sacrifice") {}
        std::string GetTargetName() override { return "self target"; }
    };

    // 施放法术封锁动作
    class CastSpellLockAction : public CastPetSpellAction
    {
    public:
        CastSpellLockAction(PlayerbotAI* ai) : CastPetSpellAction(ai, "spell lock") {}
    };

    // 施放法术封锁动作
    class CastSpellLockOnEnemyHealerAction : public CastPetSpellAction
    {
    public:
        CastSpellLockOnEnemyHealerAction(PlayerbotAI* ai) : CastPetSpellAction(ai, "spell lock") {}
        virtual std::string GetTargetName() override { return "enemy healer target"; }
        virtual std::string GetTargetQualifier() override { return GetSpellName(); }
        virtual std::string getName() override { return GetSpellName() + " on enemy healer"; }
    };

    // 施放召唤小鬼动作
    class CastSummonImpAction : public CastBuffSpellAction
    {
    public:
        CastSummonImpAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon imp") {}
        std::string GetTargetName() override { return "self target"; }

        bool isUseful() override
        {
            Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
            if (pet)
            {
                return pet->GetEntry() != 416;
            }

            return true;
        }
    };

    // 施放召唤魅魔动作
    class CastSummonSuccubusAction : public CastSpellAction
    {
    public:
        CastSummonSuccubusAction(PlayerbotAI* ai) : CastSpellAction(ai, "summon succubus") {}
        std::string GetTargetName() override { return "self target"; }

        bool isUseful() override
        {
            Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
            if (pet)
            {
                return pet->GetEntry() != 1863;
            }

            return true;
        }
    };

    // 施放召唤地狱猎犬动作
    class CastSummonFelhunterAction : public CastSpellAction
    {
    public:
        CastSummonFelhunterAction(PlayerbotAI* ai) : CastSpellAction(ai, "summon felhunter") {}
        std::string GetTargetName() override { return "self target"; }

        bool isUseful() override
        {
            Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
            if (pet)
            {
                return pet->GetEntry() != 417;
            }

            return true;
        }
    };

    // 施放召唤虚空行者动作
    class CastSummonVoidwalkerAction : public CastSpellAction
    {
    public:
        CastSummonVoidwalkerAction(PlayerbotAI* ai) : CastSpellAction(ai, "summon voidwalker") {}
        std::string GetTargetName() override { return "self target"; }

        bool isUseful() override
        {
            Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
            if (pet)
            {
                return pet->GetEntry() != 1860;
            }

            return true;
        }
    };

    // 施放召唤恶魔卫士动作
    class CastSummonFelguardAction : public CastSpellAction
    {
    public:
        CastSummonFelguardAction(PlayerbotAI* ai) : CastSpellAction(ai, "summon felguard") {}
        std::string GetTargetName() override { return "self target"; }

        bool isUseful() override
        {
            Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
            if (pet)
            {
                return pet->GetEntry() != 17252;
            }

            return true;
        }
    };

    // 施放地狱火动作
    class CastSummonInfernoAction : public CastSpellAction
    {
    public:
        CastSummonInfernoAction(PlayerbotAI* ai) : CastSpellAction(ai, "inferno") {}
        virtual bool isPossible() { return true; }
    };

    // 施放制造治疗石动作
    class CastCreateHealthstoneAction : public CastSpellAction
    {
    public:
        CastCreateHealthstoneAction(PlayerbotAI* ai) : CastSpellAction(ai, "create healthstone") {}
        std::string GetTargetName() override { return "self target"; }
    };

        // 施放制造灵魂石动作
        class CastCreateSoulstoneAction : public CastSpellAction
        {
        public:
                CastCreateSoulstoneAction(PlayerbotAI* ai) : CastSpellAction(ai, "create soulstone") {}
        std::string GetTargetName() override { return "self target"; }
        };

    // 施放制造火焰石动作
    class CastCreateFirestoneAction : public CastSpellAction
    {
    public:
        CastCreateFirestoneAction(PlayerbotAI* ai) : CastSpellAction(ai, "create firestone") {}
        std::string GetTargetName() override { return "self target"; }
    };

    // 施放制造法术石动作
    class CastCreateSpellstoneAction : public CastSpellAction
    {
    public:
        CastCreateSpellstoneAction(PlayerbotAI* ai) : CastSpellAction(ai, "create spellstone") {}
        std::string GetTargetName() override { return "self target"; }
    };

    // 施放放逐术动作
    class CastBanishAction : public CastSpellAction
    {
    public:
        CastBanishAction(PlayerbotAI* ai) : CastSpellAction(ai, "banish") {}
        virtual std::string GetTargetName() override { return "snare target"; }
        virtual std::string GetTargetQualifier() override { return GetSpellName(); }
        virtual ActionThreatType getThreatType() { return ActionThreatType::ACTION_THREAT_NONE; }
    };

    // 施放放逐术动作
    class CastBanishOnCcAction : public CastCrowdControlSpellAction
    {
    public:
        CastBanishOnCcAction(PlayerbotAI* ai) : CastCrowdControlSpellAction(ai, "banish") {}
    };

    // 施放腐蚀之种动作
    class CastSeedOfCorruptionAction : public CastRangedDebuffSpellAction
    {
    public:
        CastSeedOfCorruptionAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "seed of corruption") {}
    };

    // 施放火焰之雨动作
    class CastRainOfFireAction : public CastSpellAction
    {
    public:
        CastRainOfFireAction(PlayerbotAI* ai) : CastSpellAction(ai, "rain of fire") {}
    };

    // 施放暗影之怒动作
    class CastShadowfuryAction : public CastSpellAction
    {
    public:
        CastShadowfuryAction(PlayerbotAI* ai) : CastSpellAction(ai, "shadowfury") {}
    };

    // 减速技能动作：暗影之怒 (CastShadowfurySnareAction)
    SNARE_ACTION(CastShadowfurySnareAction, "shadowfury");
    // 远程减益技能动作：痛苦无常 (CastUnstableAfflictionAction)
    RANGED_DEBUFF_ACTION(CastUnstableAfflictionAction, "unstable affliction");

    // 施放献祭动作
    class CastImmolateAction : public CastRangedDebuffSpellAction
    {
    public:
        CastImmolateAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "immolate") {}
    };

    // 施放点燃动作
    class CastConflagrateAction : public CastSpellAction
    {
    public:
        CastConflagrateAction(PlayerbotAI* ai) : CastSpellAction(ai, "conflagrate") {}
    };

    // 施放烧尽动作
    class CastIncinerateAction : public CastSpellAction
    {
    public:
        CastIncinerateAction(PlayerbotAI* ai) : CastSpellAction(ai, "incinerate") {}
    };

    // 施放恐惧术动作
    class CastFearAction : public CastRangedDebuffSpellAction
    {
    public:
        CastFearAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "fear") {}
    };

    // 施放恐惧术动作
    class CastFearOnCcAction : public CastCrowdControlSpellAction
    {
    public:
        CastFearOnCcAction(PlayerbotAI* ai) : CastCrowdControlSpellAction(ai, "fear") {}
    };

    // 施放生命分流动作
    class CastLifeTapAction: public CastSpellAction
    {
    public:
        CastLifeTapAction(PlayerbotAI* ai) : CastSpellAction(ai, "life tap") {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool isUseful() override { return AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig.lowHealth; }
    };

    // 施放诅咒增幅动作
    class CastAmplifyCurseAction : public CastBuffSpellAction
    {
    public:
        CastAmplifyCurseAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "amplify curse") {}
    };

    // 施放生命虹吸动作
    class CastSiphonLifeAction : public CastRangedDebuffSpellAction
    {
    public:
        CastSiphonLifeAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "siphon life") {}
    };

    // 施放生命虹吸动作
    class CastSiphonLifeOnAttackerAction : public CastRangedDebuffSpellOnAttackerAction
    {
    public:
        CastSiphonLifeOnAttackerAction(PlayerbotAI* ai) : CastRangedDebuffSpellOnAttackerAction(ai, "siphon life") {}
    };

    // 施放恐惧嚎叫动作
    class CastHowlOfTerrorAction : public CastMeleeAoeSpellAction
    {
    public:
        CastHowlOfTerrorAction(PlayerbotAI* ai) : CastMeleeAoeSpellAction(ai, "howl of terror", 10.0f) {}
    };

    // 法术施放动作：灼热之痛 (CastSearingPainAction)
    SPELL_ACTION(CastSearingPainAction, "searing pain");

    // 施放更新PVE策略动作
    class UpdateWarlockPveStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateWarlockPveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
        {
            std::vector<std::string> strategiesRequired = { "demonology" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "demonology pve", strategiesRequired);

            strategiesRequired = { "demonology", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe demonology pve", strategiesRequired);

            strategiesRequired = { "demonology", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc demonology pve", strategiesRequired);

            strategiesRequired = { "demonology", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet demonology pve", strategiesRequired);

            strategiesRequired = { "demonology", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff demonology pve", strategiesRequired);

            strategiesRequired = { "demonology", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost demonology pve", strategiesRequired);

            strategiesRequired = { "demonology", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse demonology pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse demonology pve", strategiesRequired);

            strategiesRequired = { "destruction" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "destruction pve", strategiesRequired);

            strategiesRequired = { "destruction", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe destruction pve", strategiesRequired);

            strategiesRequired = { "destruction", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc destruction pve", strategiesRequired);

            strategiesRequired = { "destruction", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet destruction pve", strategiesRequired);

            strategiesRequired = { "destruction", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff destruction pve", strategiesRequired);

            strategiesRequired = { "destruction", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost destruction pve", strategiesRequired);

            strategiesRequired = { "destruction", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse destruction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse destruction pve", strategiesRequired);

            strategiesRequired = { "affliction" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "affliction pve", strategiesRequired);

            strategiesRequired = { "affliction", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe affliction pve", strategiesRequired);

            strategiesRequired = { "affliction", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc affliction pve", strategiesRequired);

            strategiesRequired = { "affliction", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet affliction pve", strategiesRequired);

            strategiesRequired = { "affliction", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff affliction pve", strategiesRequired);

            strategiesRequired = { "affliction", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost affliction pve", strategiesRequired);

            strategiesRequired = { "affliction", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse affliction pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse affliction pve", strategiesRequired);
        }
    };

    // 施放更新PVP策略动作
    class UpdateWarlockPvpStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateWarlockPvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
        {
            std::vector<std::string> strategiesRequired = { "demonology" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "demonology pvp", strategiesRequired);

            strategiesRequired = { "demonology", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe demonology pvp", strategiesRequired);

            strategiesRequired = { "demonology", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc demonology pvp", strategiesRequired);

            strategiesRequired = { "demonology", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet demonology pvp", strategiesRequired);

            strategiesRequired = { "demonology", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff demonology pvp", strategiesRequired);

            strategiesRequired = { "demonology", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost demonology pvp", strategiesRequired);

            strategiesRequired = { "demonology", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse demonology pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse demonology pvp", strategiesRequired);

            strategiesRequired = { "destruction" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "destruction pvp", strategiesRequired);

            strategiesRequired = { "destruction", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe destruction pvp", strategiesRequired);

            strategiesRequired = { "destruction", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc destruction pvp", strategiesRequired);

            strategiesRequired = { "destruction", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet destruction pvp", strategiesRequired);

            strategiesRequired = { "destruction", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff destruction pvp", strategiesRequired);

            strategiesRequired = { "destruction", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost destruction pvp", strategiesRequired);

            strategiesRequired = { "destruction", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse destruction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse destruction pvp", strategiesRequired);

            strategiesRequired = { "affliction" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "affliction pvp", strategiesRequired);

            strategiesRequired = { "affliction", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe affliction pvp", strategiesRequired);

            strategiesRequired = { "affliction", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc affliction pvp", strategiesRequired);

            strategiesRequired = { "affliction", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet affliction pvp", strategiesRequired);

            strategiesRequired = { "affliction", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff affliction pvp", strategiesRequired);

            strategiesRequired = { "affliction", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost affliction pvp", strategiesRequired);

            strategiesRequired = { "affliction", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse affliction pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse affliction pvp", strategiesRequired);
        }
    };

    // 施放更新团队副本策略动作
    class UpdateWarlockRaidStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateWarlockRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
        {
            std::vector<std::string> strategiesRequired = { "demonology" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "demonology raid", strategiesRequired);

            strategiesRequired = { "demonology", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe demonology raid", strategiesRequired);

            strategiesRequired = { "demonology", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc demonology raid", strategiesRequired);

            strategiesRequired = { "demonology", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet demonology raid", strategiesRequired);

            strategiesRequired = { "demonology", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff demonology raid", strategiesRequired);

            strategiesRequired = { "demonology", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost demonology raid", strategiesRequired);

            strategiesRequired = { "demonology", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse demonology raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse demonology raid", strategiesRequired);

            strategiesRequired = { "destruction" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "destruction raid", strategiesRequired);

            strategiesRequired = { "destruction", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe destruction raid", strategiesRequired);

            strategiesRequired = { "destruction", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc destruction raid", strategiesRequired);

            strategiesRequired = { "destruction", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet destruction raid", strategiesRequired);

            strategiesRequired = { "destruction", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff destruction raid", strategiesRequired);

            strategiesRequired = { "destruction", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost destruction raid", strategiesRequired);

            strategiesRequired = { "destruction", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse destruction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse destruction raid", strategiesRequired);

            strategiesRequired = { "affliction" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "affliction raid", strategiesRequired);

            strategiesRequired = { "affliction", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe affliction raid", strategiesRequired);

            strategiesRequired = { "affliction", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc affliction raid", strategiesRequired);

            strategiesRequired = { "affliction", "pet" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "pet affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "pet affliction raid", strategiesRequired);

            strategiesRequired = { "affliction", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff affliction raid", strategiesRequired);

            strategiesRequired = { "affliction", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost affliction raid", strategiesRequired);

            strategiesRequired = { "affliction", "curse" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "curse affliction raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "curse affliction raid", strategiesRequired);
        }
    };
}
