// 法师 - 动作头文件 (MageActions.h)：定义法师专用技能施放与战斗动作
#pragma once

#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/actions/GenericActions.h"
#include "playerbot/strategy/actions/UseItemAction.h"

namespace ai
{
    // 自我增益动作：防护火焰结界 (CastFireWardAction)
    BUFF_ACTION(CastFireWardAction, "fire ward");
    // 自我增益动作：防护冰霜结界 (CastFrostWardAction)
    BUFF_ACTION(CastFrostWardAction, "frost ward");
    // 自我增益动作：闪现术 (CastBlinkAction)
    BUFF_ACTION(CastBlinkAction, "blink");
    // 法术施放动作：冰枪术 (CastIceLanceAction)
    SPELL_ACTION(CastIceLanceAction, "ice lance");

    // 施放火球术动作
    class CastFireballAction : public CastSpellAction
    {
    public:
        CastFireballAction(PlayerbotAI* ai) : CastSpellAction(ai, "fireball") {}
    };

    // 施放灼烧动作
    class CastScorchAction : public CastSpellAction
    {
    public:
        CastScorchAction(PlayerbotAI* ai) : CastSpellAction(ai, "scorch") {}
    };

    // 施放火焰冲击动作
    class CastFireBlastAction : public CastSpellAction
    {
    public:
        CastFireBlastAction(PlayerbotAI* ai) : CastSpellAction(ai, "fire blast") {}
    };

    // 施放奥术冲击动作
    class CastArcaneBlastAction : public CastBuffSpellAction
    {
    public:
        CastArcaneBlastAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane blast") {}
        virtual std::string GetTargetName() override { return "current target"; }
    };

    // 施放奥术冲击动作
    class CastArcaneBlastTBCAction : public CastSpellAction
    {
    public:
        CastArcaneBlastTBCAction(PlayerbotAI* ai) : CastSpellAction(ai, "arcane blast") {}
    };

    // 施放奥术弹幕动作
    class CastArcaneBarrageAction : public CastSpellAction
    {
    public:
        CastArcaneBarrageAction(PlayerbotAI* ai) : CastSpellAction(ai, "arcane barrage") {}
    };

    // 施放奥术飞弹动作
    class CastArcaneMissilesAction : public CastSpellAction
    {
    public:
        CastArcaneMissilesAction(PlayerbotAI* ai) : CastSpellAction(ai, "arcane missiles") {}
    };

    // 施放炎爆术动作
    class CastPyroblastAction : public CastSpellAction
    {
    public:
        CastPyroblastAction(PlayerbotAI* ai) : CastSpellAction(ai, "pyroblast") {}
    };

    // 施放烈焰风暴动作
    class CastFlamestrikeAction : public CastSpellAction
    {
    public:
        CastFlamestrikeAction(PlayerbotAI* ai) : CastSpellAction(ai, "flamestrike") {}
    };

    // 施放冰霜新星动作
    class CastFrostNovaAction : public CastMeleeAoeSpellAction
    {
    public:
        CastFrostNovaAction(PlayerbotAI* ai) : CastMeleeAoeSpellAction(ai, "frost nova", 10.0f) {}
    };

    // 施放寒冰箭动作
    class CastFrostboltAction : public CastSpellAction
    {
    public:
        CastFrostboltAction(PlayerbotAI* ai) : CastSpellAction(ai, "frostbolt") {}
    };

    // 施放暴风雪动作
    class CastBlizzardAction : public CastSpellAction
    {
    public:
        CastBlizzardAction(PlayerbotAI* ai) : CastSpellAction(ai, "blizzard") {}
        virtual ActionThreatType getThreatType() { return ActionThreatType::ACTION_THREAT_AOE; }
        virtual bool isUseful() override { return CastSpellAction::isUseful() && ai->GetCombatStartTime() && (time(0) - ai->GetCombatStartTime()) > 10; }
    };

    // 施放奥术智慧动作
    class CastArcaneIntellectAction : public CastBuffSpellAction
    {
    public:
        CastArcaneIntellectAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane intellect") {}
    };

    // 施放奥术智慧动作
    class CastArcaneIntellectOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastArcaneIntellectOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "arcane intellect") {}
    };

    // 施放奥术光辉动作
    class CastArcaneBrillianceOnPartyAction : public GreaterBuffOnPartyAction
    {
    public:
        CastArcaneBrillianceOnPartyAction(PlayerbotAI* ai) : GreaterBuffOnPartyAction(ai, "arcane brilliance", "arcane intellect") {}
    };

    // 施放解除诅咒动作
    class CastRemoveCurseAction : public CastCureSpellAction
    {
    public:
        CastRemoveCurseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "remove curse") {}
    };

    // 施放解除次级诅咒动作
    class CastRemoveLesserCurseAction : public CastCureSpellAction
    {
    public:
        CastRemoveLesserCurseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "remove lesser curse") {}
    };

    // 施放冰冷血脉动作
    class CastIcyVeinsAction : public CastBuffSpellAction
    {
    public:
        CastIcyVeinsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "icy veins") {}
    };

    // 施放燃烧动作
    class CastCombustionAction : public CastBuffSpellAction
    {
    public:
        CastCombustionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "combustion") {}
    };

    // 法术动作定义：法术反制 (CastCounterspellAction)
    BEGIN_SPELL_ACTION(CastCounterspellAction, "counterspell")
    END_SPELL_ACTION()

    // 施放解除诅咒动作
    class CastRemoveCurseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastRemoveCurseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "remove curse", DISPEL_CURSE) {}
    };

    // 施放解除次级诅咒动作
    class CastRemoveLesserCurseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastRemoveLesserCurseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "remove lesser curse", DISPEL_CURSE) {}
    };

    // 施放造食术动作
    class CastConjureFoodAction : public CastBuffSpellAction
    {
    public:
        CastConjureFoodAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "conjure food") {}
    };

    // 施放造水术动作
    class CastConjureWaterAction : public CastBuffSpellAction
    {
    public:
        CastConjureWaterAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "conjure water") {}
    };

    // 施放制造法力宝石动作
    class CastConjureManaGemAction : public Action
    {
    public:
        CastConjureManaGemAction(PlayerbotAI* ai) : Action(ai, "conjure mana gem") {}

        bool Execute(Event& event) override
        {
            uint32 spellDuration = sPlayerbotAIConfig.globalCoolDown;
            if (ai->CastSpell(spellId, bot, nullptr, false, &spellDuration))
            {
                if (ai->HasCheat(BotCheatMask::attackspeed))
                {
                    spellDuration = 1;
                }

                SetDuration(spellDuration);
                return true;
            }

            return false;
        }

        bool isPossible() override 
        { 
            if (!ai->HasCheat(BotCheatMask::item))
            {
                const uint32 level = bot->GetLevel();
                if (level >= 28 && level < 38)
                {
                    spellId = 759;
                }
                else if (level >= 38 && level < 48)
                {
                    spellId = 3552;
                }
                else if (level >= 48 && level < 58)
                {
                    spellId = 10053;
                }
                else if (level >= 58 && level < 68)
                {
                    spellId = 10054;
                }
                else if (level >= 68 && level < 77)
                {
                    spellId = 27101;
                }
                else if (level >= 77)
                {
                    spellId = 42985;
                }

                return ai->CanCastSpell(spellId, bot, 0);
            }

            return false;
        }

    private:
        uint32 spellId;
    };

    // 施放寒冰屏障动作
    class CastIceBlockAction : public CastBuffSpellAction
    {
    public:
        CastIceBlockAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "ice block") {}
    };

    // 自我增益动作：寒冰护体 (CastIceBarrierAction)
    BUFF_ACTION(CastIceBarrierAction, "ice barrier");
    // 自我增益动作：法力护盾 (CastManaShieldAction)
    BUFF_ACTION(CastManaShieldAction, "mana shield");

    // 施放熔甲术动作
    class CastMoltenArmorAction : public CastBuffSpellAction
    {
    public:
        CastMoltenArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "molten armor") {}
    };

    // 施放魔甲术动作
    class CastMageArmorAction : public CastBuffSpellAction
    {
    public:
        CastMageArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "mage armor") {}
    };

    // 施放冰甲术动作
    class CastIceArmorAction : public CastBuffSpellAction
    {
    public:
        CastIceArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "ice armor") {}
    };

    // 施放霜甲术动作
    class CastFrostArmorAction : public CastBuffSpellAction
    {
    public:
        CastFrostArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "frost armor") {}
    };

    // 施放变形术动作
    class CastPolymorphAction : public CastCrowdControlSpellAction
    {
    public:
        CastPolymorphAction(PlayerbotAI* ai) : CastCrowdControlSpellAction(ai, "polymorph") {}
        virtual bool Execute(Event& event)
        {
            std::vector<std::string> polySpells;
            polySpells.push_back("polymorph");
            if (bot->HasSpell(28271))
                polySpells.push_back("polymorph: turtle");
            if (bot->HasSpell(28272))
                polySpells.push_back("polymorph: pig");

            return ai->CastSpell(polySpells[urand(0, polySpells.size() - 1)], GetTarget());
        }
    };

    // 施放法术吸取动作
    class CastSpellstealAction : public CastSpellAction
    {
    public:
        CastSpellstealAction(PlayerbotAI* ai) : CastSpellAction(ai, "spellsteal") {}
    };

    // 施放隐形术动作
    class CastInvisibilityAction : public CastBuffSpellAction
    {
    public:
        CastInvisibilityAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "invisibility") {}
    };

    // 施放次级隐形术动作
    class CastLesserInvisibilityAction : public CastBuffSpellAction
    {
    public:
        CastLesserInvisibilityAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "lesser invisibility") {}
    };

    // 施放唤醒动作
    class CastEvocationAction : public CastSpellAction
    {
    public:
        CastEvocationAction(PlayerbotAI* ai) : CastSpellAction(ai, "evocation") {}
        virtual std::string GetTargetName() override { return "self target"; }
    };

    // 施放法术反制动作
    class CastCounterspellOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastCounterspellOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "counterspell") {}
    };

    // 施放奥术强化动作
    class CastArcanePowerAction : public CastBuffSpellAction
    {
    public:
        CastArcanePowerAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane power") {}
    };

    // 施放气定神闲动作
    class CastPresenceOfMindAction : public CastBuffSpellAction
    {
    public:
        CastPresenceOfMindAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "presence of mind") {}
    };

    // 施放急速冷却动作
    class CastColdSnapAction : public CastBuffSpellAction
    {
    public:
        CastColdSnapAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cold snap") {}
    };

    // 施放魔爆术动作
    class CastArcaneExplosionAction : public CastMeleeAoeSpellAction
    {
    public:
        CastArcaneExplosionAction(PlayerbotAI* ai) : CastMeleeAoeSpellAction(ai, "arcane explosion", 10.0f) {}
    };

    // 施放冰锥术动作
    class CastConeOfColdAction : public CastMeleeAoeSpellAction
    {
    public:
        CastConeOfColdAction(PlayerbotAI* ai) : CastMeleeAoeSpellAction(ai, "cone of cold", 10.0f) {}
    };
    
    // 自我增益动作：召唤水元素 (CastSummonWaterElementalAction)
    BUFF_ACTION(CastSummonWaterElementalAction, "summon water elemental");

    // 施放龙息术动作
    class CastDragonsBreathAction : public CastMeleeAoeSpellAction
    {
    public:
        CastDragonsBreathAction(PlayerbotAI* ai) : CastMeleeAoeSpellAction(ai, "dragon's breath", 10.0f) {}
    };

    // 施放冲击波动作
    class CastBlastWaveAction : public CastMeleeAoeSpellAction
    {
    public:
        CastBlastWaveAction(PlayerbotAI* ai) : CastMeleeAoeSpellAction(ai, "blast wave", 10.0f) {}
    };

    // 施放活动炸弹动作
    class CastLivingBombAction : public CastRangedDebuffSpellAction
    {
    public:
        CastLivingBombAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "living bomb") {}
    };

    // 施放霜火之箭动作
    class CastFrostfireBoltAction : public CastSpellAction
    {
    public:
        CastFrostfireBoltAction(PlayerbotAI* ai) : CastSpellAction(ai, "frostfire bolt") {}
    };

    // 施放深度冻结动作
    class DeepFreezeAction : public CastSpellAction
    {
    public:
        DeepFreezeAction(PlayerbotAI* ai) : CastSpellAction(ai, "deep freeze") {}
    };

    // 施放镜像动作
    class MirrorImageAction : public CastBuffSpellAction
    {
    public:
        MirrorImageAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "mirror image") {}
    }; 

    // 施放法力宝石动作
    class UseManaGemAction : public UseItemIdAction
    {
    public:
        UseManaGemAction(PlayerbotAI* ai) : UseItemIdAction(ai, "mana gem") {}

        uint32 GetItemId() override
        {
            uint32 itemId = 0;
            if (ai->HasCheat(BotCheatMask::item))
            {
                const uint32 level = bot->GetLevel();
                if (level >= 28 && level < 38)
                {
                    itemId = 5514;
                }
                else if (level >= 38 && level < 48)
                {
                    itemId = 5513;
                }
                else if (level >= 48 && level < 58)
                {
                    itemId = 8007;
                }
                else if (level >= 58 && level < 68)
                {
                    itemId = 8008;
                }
                else if (level >= 68 && level < 77)
                {
                    itemId = 22044;
                }
                else if (level >= 77)
                {
                    itemId = 33312;
                }
            }
            else
            {
                const std::vector<uint32> manaGemIds = { 5514, 5513, 8007, 8008, 22044, 33312 };
                for (const uint32 manaGemId : manaGemIds)
                {
                    if (bot->HasItemCount(manaGemId, 1))
                    {
                        itemId = manaGemId;
                        break;
                    }
                }
            }

            return itemId;
        }
    };

    // 施放更新PVE策略动作
    class UpdateMagePveStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateMagePveStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pve strats")
        {
            std::vector<std::string> strategiesRequired = { "frost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "frost pve", strategiesRequired);

            strategiesRequired = { "frost", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe frost pve", strategiesRequired);

            strategiesRequired = { "frost", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure frost pve", strategiesRequired);

            strategiesRequired = { "frost", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff frost pve", strategiesRequired);

            strategiesRequired = { "frost", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost frost pve", strategiesRequired);

            strategiesRequired = { "frost", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc frost pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc frost pve", strategiesRequired);

            strategiesRequired = { "fire" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "fire pve", strategiesRequired);

            strategiesRequired = { "fire", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe fire pve", strategiesRequired);

            strategiesRequired = { "fire", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure fire pve", strategiesRequired);

            strategiesRequired = { "fire", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff fire pve", strategiesRequired);

            strategiesRequired = { "fire", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost fire pve", strategiesRequired);

            strategiesRequired = { "fire", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc fire pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc fire pve", strategiesRequired);

            strategiesRequired = { "arcane" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "arcane pve", strategiesRequired);

            strategiesRequired = { "arcane", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe arcane pve", strategiesRequired);

            strategiesRequired = { "arcane", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure arcane pve", strategiesRequired);

            strategiesRequired = { "arcane", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff arcane pve", strategiesRequired);

            strategiesRequired = { "arcane", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost arcane pve", strategiesRequired);

            strategiesRequired = { "arcane", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc arcane pve", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc arcane pve", strategiesRequired);
        }
    };

    // 施放更新PVP策略动作
    class UpdateMagePvpStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateMagePvpStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update pvp strats")
        {
            std::vector<std::string> strategiesRequired = { "frost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "frost pvp", strategiesRequired);

            strategiesRequired = { "frost", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe frost pvp", strategiesRequired);

            strategiesRequired = { "frost", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure frost pvp", strategiesRequired);

            strategiesRequired = { "frost", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff frost pvp", strategiesRequired);

            strategiesRequired = { "frost", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost frost pvp", strategiesRequired);

            strategiesRequired = { "frost", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc frost pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc frost pvp", strategiesRequired);

            strategiesRequired = { "fire" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "fire pvp", strategiesRequired);

            strategiesRequired = { "fire", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe fire pvp", strategiesRequired);

            strategiesRequired = { "fire", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure fire pvp", strategiesRequired);

            strategiesRequired = { "fire", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff fire pvp", strategiesRequired);

            strategiesRequired = { "fire", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost fire pvp", strategiesRequired);

            strategiesRequired = { "fire", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc fire pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc fire pvp", strategiesRequired);

            strategiesRequired = { "arcane" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "arcane pvp", strategiesRequired);

            strategiesRequired = { "arcane", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe arcane pvp", strategiesRequired);

            strategiesRequired = { "arcane", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure arcane pvp", strategiesRequired);

            strategiesRequired = { "arcane", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff arcane pvp", strategiesRequired);

            strategiesRequired = { "arcane", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost arcane pvp", strategiesRequired);

            strategiesRequired = { "arcane", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc arcane pvp", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc arcane pvp", strategiesRequired);
        }
    };

    // 施放更新团队副本策略动作
    class UpdateMageRaidStrategiesAction : public UpdateStrategyDependenciesAction
    {
    public:
        UpdateMageRaidStrategiesAction(PlayerbotAI* ai) : UpdateStrategyDependenciesAction(ai, "update raid strats")
        {
            std::vector<std::string> strategiesRequired = { "frost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "frost raid", strategiesRequired);

            strategiesRequired = { "frost", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe frost raid", strategiesRequired);

            strategiesRequired = { "frost", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure frost raid", strategiesRequired);

            strategiesRequired = { "frost", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff frost raid", strategiesRequired);

            strategiesRequired = { "frost", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost frost raid", strategiesRequired);

            strategiesRequired = { "frost", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc frost raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc frost raid", strategiesRequired);

            strategiesRequired = { "fire" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "fire raid", strategiesRequired);

            strategiesRequired = { "fire", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe fire raid", strategiesRequired);

            strategiesRequired = { "fire", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure fire raid", strategiesRequired);

            strategiesRequired = { "fire", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff fire raid", strategiesRequired);

            strategiesRequired = { "fire", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost fire raid", strategiesRequired);

            strategiesRequired = { "fire", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc fire raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc fire raid", strategiesRequired);

            strategiesRequired = { "arcane" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_DEAD, "arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_REACTION, "arcane raid", strategiesRequired);

            strategiesRequired = { "arcane", "aoe" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "aoe arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "aoe arcane raid", strategiesRequired);

            strategiesRequired = { "arcane", "cure" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cure arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cure arcane raid", strategiesRequired);

            strategiesRequired = { "arcane", "buff" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "buff arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "buff arcane raid", strategiesRequired);

            strategiesRequired = { "arcane", "boost" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "boost arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "boost arcane raid", strategiesRequired);

            strategiesRequired = { "arcane", "cc" };
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_COMBAT, "cc arcane raid", strategiesRequired);
            strategiesToUpdate.emplace_back(BotState::BOT_STATE_NON_COMBAT, "cc arcane raid", strategiesRequired);
        }
    };
}
