// 法师 - 触发器头文件 (MageTriggers.h)：定义法师增益、减益、冷却及状态检查触发条件
#pragma once
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    // 法术反射/反制触发器：防护火焰结界 (FireWardTrigger)
    DEFLECT_TRIGGER(FireWardTrigger, "fire ward");
    // 法术反射/反制触发器：防护冰霜结界 (FrostWardTrigger)
    DEFLECT_TRIGGER(FrostWardTrigger, "frost ward");

    // 触发器：闪现术
    class BlinkTrigger : public Trigger
    {
    public:
        BlinkTrigger(PlayerbotAI* ai) : Trigger(ai, "blink", 2) {}

        virtual bool IsActive() override
        {
            return bot->HasAuraType(SPELL_AURA_MOD_ROOT) ||
                   bot->HasAuraType(SPELL_AURA_MOD_STUN);
        }
    };

    // 触发器：奥术智慧
    class ArcaneIntellectOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        ArcaneIntellectOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "arcane intellect", 4) {}
        virtual bool IsActive() override { return BuffOnPartyTrigger::IsActive() && !ai->HasAura("arcane brilliance", GetTarget()); }
    };

    // 触发器：奥术智慧
    class ArcaneIntellectTrigger : public BuffTrigger 
    {
    public:
        ArcaneIntellectTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "arcane intellect", 4) {}
        virtual bool IsActive() override { return BuffTrigger::IsActive() && !ai->HasAura("arcane brilliance", GetTarget()); }
    };

    // 触发器：奥术光辉
    class ArcaneBrillianceOnPartyTrigger : public GreaterBuffOnPartyTrigger
    {
    public:
        ArcaneBrillianceOnPartyTrigger(PlayerbotAI* ai) : GreaterBuffOnPartyTrigger(ai, "arcane brilliance", "arcane intellect", 4) {}
    };

    // 触发器：任意法师护甲
    class AnyMageArmorTrigger : public BuffTrigger 
    {
    public:
        AnyMageArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "any mage armor", 5) {}
        virtual bool IsActive() override;
    };

    // 触发器：魔甲术
    class MageArmorTrigger : public BuffTrigger
    {
    public:
        MageArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "mage armor", 5) {}
        virtual bool IsActive() override;
    };

    // 触发器：冰甲术
    class IceArmorTrigger : public BuffTrigger
    {
    public:
        IceArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "ice armor", 5) {}
        virtual bool IsActive() override;
    };

    // 触发器：熔甲术
    class MoltenArmorTrigger : public BuffTrigger
    {
    public:
        MoltenArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "molten armor", 5) {}
        virtual bool IsActive() override;
    };

    // 触发器：火球术
    class FireballTrigger : public DebuffTrigger 
    {
    public:
        FireballTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "fireball") {}
    };

    // 触发器：炎爆术
    class PyroblastTrigger : public DebuffTrigger 
    {
    public:
        PyroblastTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "pyroblast", 10) {}
    };

    // 触发器：飞弹速射
    class MissileBarrageTrigger : public HasAuraTrigger 
    {
    public:
        MissileBarrageTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "missile barrage") {}
    };

    // 触发器：奥术冲击
    class ArcaneBlastTrigger : public BuffTrigger 
    {
    public:
        ArcaneBlastTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "arcane blast") {}
        virtual bool IsActive() override;
    };

    // 触发器：奥术冲击
    class ArcaneBlastFullTrigger : public BuffTrigger
    {
    public:
        ArcaneBlastFullTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "arcane blast") {}
        virtual bool IsActive() override;
    };

    // 触发器：法术反制
    class CounterspellInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        CounterspellInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "counterspell") {}
    };

    // 触发器：燃烧
    class CombustionTrigger : public BoostTrigger
    {
    public:
        CombustionTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "combustion") {}
    };

    // 触发器：冰冷血脉
    class IcyVeinsTrigger : public BoostTrigger
    {
    public:
        IcyVeinsTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "icy veins") {}
    };

    // 爆发增益触发器：召唤水元素 (WaterElementalBoostTrigger)
    BOOST_TRIGGER(WaterElementalBoostTrigger, "summon water elemental");

    // 触发器：变形术
    class PolymorphTrigger : public HasCcTargetTrigger
    {
    public:
        PolymorphTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "polymorph") {}
    };

    // 触发器：解除诅咒
    class RemoveCurseTrigger : public NeedCureTrigger
    {
    public:
        RemoveCurseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "remove curse", DISPEL_CURSE) {}
    };

    // 触发器：解除诅咒
    class PartyMemberRemoveCurseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberRemoveCurseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "remove curse", DISPEL_CURSE) {}
    };

    // 触发器：法术吸取
    class SpellstealTrigger : public TargetAuraDispelTrigger
    {
    public:
        SpellstealTrigger(PlayerbotAI* ai) : TargetAuraDispelTrigger(ai, "spellsteal", DISPEL_MAGIC) {}
    };

    // 触发器：法术反制
    class CounterspellEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        CounterspellEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "counterspell") {}
    };

    // 触发器：奥术强化
    class ArcanePowerTrigger : public BuffTrigger
    {
    public:
        ArcanePowerTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "arcane power") {}
    };

    // 触发器：气定神闲
    class PresenceOfMindTrigger : public BuffTrigger
    {
    public:
        PresenceOfMindTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "presence of mind") {}
    };

    // 光环存在触发器：气定神闲 (PresenceOfMindAuraTrigger)
    HAS_AURA_TRIGGER(PresenceOfMindAuraTrigger, "presence of mind");

    // 触发器：法力护盾
    class ManaShieldTrigger : public BuffTrigger
    {
    public:
        ManaShieldTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "mana shield", 5) {}
        virtual bool IsActive() override;
    };

    // 触发器：寒冰护体
    class IceBarrierTrigger : public BuffTrigger
    {
    public:
        IceBarrierTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "ice barrier", 5) {}
    };

    // FireSpellsLocked
    class FireSpellsLocked : public Trigger
    {
    public:
        FireSpellsLocked(PlayerbotAI* ai) : Trigger(ai, "fire spells locked", 2) {}

        virtual bool IsActive() override
        {
            return !bot->IsSpellReady(133)      //fireball
                && !bot->IsSpellReady(2948);    //scorch
        }
    };

    // FrostSpellsLocked
    class FrostSpellsLocked : public Trigger
    {
    public:
        FrostSpellsLocked(PlayerbotAI* ai) : Trigger(ai, "frost spells locked", 2) {}

        virtual bool IsActive() override
        {
            return !bot->IsSpellReady(116);      //frostbolt
        }
    };

    // 触发器：冰枪术
    class IceLanceTrigger : public Trigger
    {
    public:
        IceLanceTrigger(PlayerbotAI* ai) : Trigger(ai, "ice lance") {}
        bool IsActive() override;
        std::string GetTargetName() override { return "current target"; }
    };

    // 增益触发器：镜像 (MirrorImageTrigger)
    BUFF_TRIGGER(MirrorImageTrigger, "mirror image");
    // 增益触发器(带条件)：法术连击 (HotStreakTrigger)
    BUFF_TRIGGER_A(HotStreakTrigger, "hot streak");
    // 增益触发器(带条件)：瞬发火球术(法术连击) (FireballOrFrostfireBoltFreeTrigger)
    BUFF_TRIGGER_A(FireballOrFrostfireBoltFreeTrigger, "fireball!");
    // 减益触发器(带条件)：强化灼烧 (NoImprovedScorchDebuffTrigger)
    DEBUFF_TRIGGER_A(NoImprovedScorchDebuffTrigger, "improved scorch");
    // 光环存在触发器：寒冰指 (FingersOfFrostTrigger)
    HAS_AURA_TRIGGER(FingersOfFrostTrigger, "fingers of frost");

    // 触发器：目标无火焰易伤减益
    class NoFireVulnerabilityTrigger : public Trigger
    {
    public:
        NoFireVulnerabilityTrigger(PlayerbotAI* ai) : Trigger(ai, "no fire vulnerability") {}

        virtual bool IsActive() override
        {
            // Required non-player target
            Unit* target = GetTarget();
            if (target && !target->IsPlayer())
            {
                // Required Improved Scorch talent
                if (bot->HasSpell(11095) || bot->HasSpell(12872) || bot->HasSpell(12873))
                {
                    // Check if have max stacks of fire vulnerability expiring in less than 7 seconds
                    Aura* aura = ai->GetAura(22959, target);
                    if (aura)
                    {
                        // Check if the stack is at the maximum
                        const uint32 maxStackAmount = aura->GetSpellProto()->StackAmount;
                        const uint32 stackAmount = aura->GetHolder()->GetStackAmount();
                        if (stackAmount >= maxStackAmount)
                        {
                            // Check if the aura is about to expire
                            if (aura->GetHolder()->GetAuraDuration() > 7000)
                            {
                                return false;
                            }
                        }
                    }

                    return true;
                }                    
            }

            return false;
        }

        virtual std::string GetTargetName() override { return "current target"; }
    };

    // 触发器：活动炸弹
    class LivingBombTrigger : public DebuffTrigger 
    {
    public:
        LivingBombTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "living bomb") {}
    };

    // 触发器：急速冷却
    class ColdSnapTrigger : public Trigger
    {
    public:
        ColdSnapTrigger(PlayerbotAI* ai) : Trigger(ai, "cold snap", 2) {}

        virtual bool IsActive() override
        {
            return !bot->IsSpellReady(12472)    //icy veins on cooldown
                && bot->IsSpellReady(11958);    //cold snap not on cooldown
        }
    };

    // 触发器：缺少食物触发器
    class NoFoodTrigger : public Trigger
    {
    public:
        NoFoodTrigger(PlayerbotAI* ai) : Trigger(ai, "no food trigger", 5) {}

        virtual bool IsActive() override
        {
            return !ai->HasCheat(BotCheatMask::item) && AI_VALUE2(std::list<Item*>, "inventory items", "conjured food").empty();
        }
    };

    // 触发器：缺少饮料触发器
    class NoDrinkTrigger : public Trigger
    {
    public:
        NoDrinkTrigger(PlayerbotAI* ai) : Trigger(ai, "no drink trigger", 5) {}

        virtual bool IsActive() override
        {
            return !ai->HasCheat(BotCheatMask::item) && AI_VALUE2(std::list<Item*>, "inventory items", "conjured water").empty();
        }
    };

    // 触发器：缺少法力宝石触发器
    class NoManaGemTrigger : public Trigger
    {
    public:
        NoManaGemTrigger(PlayerbotAI* ai) : Trigger(ai, "no mana gem trigger", 5) {}

        virtual bool IsActive() override
        {
            if (!ai->HasCheat(BotCheatMask::item))
            {
                uint32 itemId = 0;
                const uint32 level = bot->GetLevel();
                const std::vector<uint32> manaGemIds = { 5514, 5513, 8007, 8008, 22044, 33312 };
                for (const uint32 manaGemId : manaGemIds)
                {
                    if (bot->HasItemCount(manaGemId, 1))
                    {
                        return false;
                    }
                }

                return true;
            }

            return false;
        }
    };
}
