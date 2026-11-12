// 术士 - 触发器头文件 (WarlockTriggers.h)：定义术士增益、减益、冷却及状态检查触发条件
#pragma once
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    // 法术反射/反制触发器：防护暗影结界 (ShadowWardTrigger)
    DEFLECT_TRIGGER(ShadowWardTrigger, "shadow ward");

    // 触发器：魔甲术
    class DemonArmorTrigger : public BuffTrigger
    {
    public:
        DemonArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "demon armor") {}
        virtual bool IsActive() override;
    };

    // 触发器：法术石
    class SpellstoneTrigger : public BuffTrigger
    {
    public:
        SpellstoneTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "spellstone") {}
        virtual bool IsActive() override;
    };

    // 触发器：目标无诅咒减益
    class NoCurseTrigger : public Trigger
    {
    public:
        NoCurseTrigger(PlayerbotAI* ai) : Trigger(ai, "no curse") {}
        bool IsActive() override;

    private:
        std::string GetTargetName() override { return "current target"; }
    };

    // 触发器：攻击者无诅咒减益
    class NoCurseOnAttackerTrigger : public Trigger
    {
    public:
        NoCurseOnAttackerTrigger(PlayerbotAI* ai) : Trigger(ai, "no curse on attacker") {}
        bool IsActive() override;
    };

    // 减益触发器(带条件)：腐蚀术 (CorruptionTrigger)
    DEBUFF_TRIGGER_A(CorruptionTrigger, "corruption");
    // 减益触发器：生命虹吸 (SiphonLifeTrigger)
    DEBUFF_TRIGGER(SiphonLifeTrigger, "siphon life");
    // 减益触发器：痛苦无常 (UnstableAfflictionTrigger)
    DEBUFF_TRIGGER(UnstableAfflictionTrigger, "unstable affliction");

    // 打断触发器：凋零缠绕/死亡缠绕 (DeathCoilInterruptTrigger)
    INTERRUPT_TRIGGER(DeathCoilInterruptTrigger, "death coil");
    // 打断敌方治疗触发器：凋零缠绕/死亡缠绕 (DeathCoilInterruptTHealerTrigger)
    INTERRUPT_HEALER_TRIGGER(DeathCoilInterruptTHealerTrigger, "death coil");
    // 减速触发器：凋零缠绕/死亡缠绕 (DeathCoilSnareTrigger)
    SNARE_TRIGGER(DeathCoilSnareTrigger, "death coil");
    // 减速触发器：暗影之怒 (ShadowfurySnareTrigger)
    SNARE_TRIGGER(ShadowfurySnareTrigger, "shadowfury");
    // 打断触发器：暗影之怒 (ShadowfuryInterruptTrigger)
    INTERRUPT_TRIGGER(ShadowfuryInterruptTrigger, "shadowfury");

    // 触发器：腐蚀术
    class CorruptionOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CorruptionOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "corruption") {}
        bool IsActive() override;
    };

    // 触发器：腐蚀之种
    class SeedOfCorruptionOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        SeedOfCorruptionOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "seed of corruption") {}
        bool IsActive() override;
    };

    // 减益触发器：痛苦诅咒 (CurseOfAgonyTrigger)
    DEBUFF_TRIGGER(CurseOfAgonyTrigger, "curse of agony");

    // 触发器：痛苦诅咒
    class CurseOfAgonyOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CurseOfAgonyOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "curse of agony") {}
    };

    // 减益触发器：厄运诅咒 (CurseOfDoomTrigger)
    DEBUFF_TRIGGER(CurseOfDoomTrigger, "curse of doom");

    // 触发器：厄运诅咒
    class CurseOfDoomOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CurseOfDoomOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "curse of doom") {}
    };

    // 减益触发器：元素诅咒 (CurseOfTheElementsTrigger)
    DEBUFF_TRIGGER(CurseOfTheElementsTrigger, "curse of the elements");

    // 触发器：元素诅咒
    class CurseOfTheElementsOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CurseOfTheElementsOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "curse of the elements") {}
    };

    // 减益触发器：鲁莽诅咒 (CurseOfRecklessnessTrigger)
    DEBUFF_TRIGGER(CurseOfRecklessnessTrigger, "curse of recklessness");

    // 触发器：鲁莽诅咒
    class CurseOfRecklessnessOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CurseOfRecklessnessOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "curse of recklessness") {}
    };

    // 减益触发器：虚弱诅咒 (CurseOfWeaknessTrigger)
    DEBUFF_TRIGGER(CurseOfWeaknessTrigger, "curse of weakness");

    // 触发器：虚弱诅咒
    class CurseOfWeaknessOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CurseOfWeaknessOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "curse of weakness") {}
    };

    // 减益触发器：语言诅咒 (CurseOfTonguesTrigger)
    DEBUFF_TRIGGER(CurseOfTonguesTrigger, "curse of tongues");

    // 触发器：语言诅咒
    class CurseOfTonguesOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CurseOfTonguesOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "curse of tongues") {}
    };

    // 减益触发器：暗影诅咒 (CurseOfShadowTrigger)
    DEBUFF_TRIGGER(CurseOfShadowTrigger, "curse of shadow");

    // 触发器：暗影诅咒
    class CurseOfShadowOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CurseOfShadowOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "curse of shadow") {}
    };

    // 触发器：生命虹吸
    class SiphonLifeOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        SiphonLifeOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "siphon life") {}
    };

    // 触发器：痛苦无常
    class UnstableAfflictionOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        UnstableAfflictionOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "unstable affliction") {}
    };

    // 减益触发器：献祭 (ImmolateTrigger)
    DEBUFF_TRIGGER(ImmolateTrigger, "immolate");

    // 触发器：暗影冥思
    class ShadowTranceTrigger : public HasAuraTrigger
    {
    public:
        ShadowTranceTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "shadow trance") {}
    };

    // 触发器：反冲
    class BacklashTrigger : public HasAuraTrigger
    {
    public:
        BacklashTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "backlash", 1, SPELL_AURA_ADD_PCT_MODIFIER) {}
    };

    // 触发器：放逐术
    class BanishTrigger : public HasCcTargetTrigger
    {
    public:
        BanishTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "banish") {}
    };

    // 触发器：术士制造召唤物(治疗石/灵魂石等)检查
    class WarlockConjuredItemTrigger : public ItemCountTrigger
    {
    public:
        WarlockConjuredItemTrigger(PlayerbotAI* ai, std::string item) : ItemCountTrigger(ai, item, 1) {}

        virtual bool IsActive() override { return ItemCountTrigger::IsActive() && (ai->HasCheat(BotCheatMask::item) || AI_VALUE2(uint32, "item count", "soul shard") > 0); }
    };

    // 触发器：法术石
    class HasSpellstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasSpellstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "spellstone") {}
    };

    // 触发器：火焰石
    class HasFirestoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasFirestoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "firestone") {}
    };

    // 触发器：治疗石
    class HasHealthstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasHealthstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "healthstone") {}
    };

    // 触发器：灵魂石
    class HasSoulstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasSoulstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "soulstone") {}
    };

    // 触发器：恐惧术
    class FearTrigger : public HasCcTargetTrigger
    {
    public:
        FearTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "fear") {}
    };

    // 触发器：诅咒增幅
    class AmplifyCurseTrigger : public BuffTrigger
    {
    public:
        AmplifyCurseTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "amplify curse") {}
    };

    // 触发器：地狱火
    class InfernoTrigger : public BuffTrigger
    {
    public:
        InfernoTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "inferno", 10) {}
        virtual bool IsActive() override;
    };

    // 触发器：生命分流
    class LifeTapTrigger : public Trigger
    {
    public:
        LifeTapTrigger(PlayerbotAI* ai) : Trigger(ai, "life tap", 2) {}
        bool IsActive() override;
    };

    // 触发器：吸取灵魂
    class DrainSoulTrigger : public Trigger
    {
    public:
        DrainSoulTrigger(PlayerbotAI* ai) : Trigger(ai, "drain soul") {}
        bool IsActive() override;
    };

    // 触发器：PVP恐惧控制
    class FearPvpTrigger : public Trigger
    {
    public:
        FearPvpTrigger(PlayerbotAI* ai) : Trigger(ai, "fear pvp") {}
        bool IsActive() override;
    };

    // 触发器：点燃
    class ConflagrateTrigger : public Trigger
    {
    public:
        ConflagrateTrigger(PlayerbotAI* ai) : Trigger(ai, "conflagrate") {}
        bool IsActive() override;
    };

    // 触发器：恶魔牺牲
    class DemonicSacrificeTrigger : public Trigger
    {
    public:
        DemonicSacrificeTrigger(PlayerbotAI* ai) : Trigger(ai, "demonic sacrifice") {}
        bool IsActive() override;
    };

    // 触发器：灵魂链接
    class SoulLinkTrigger : public BuffTrigger
    {
    public:
        SoulLinkTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "soul link", 5) {}
        virtual bool IsActive() override;
    };

    // 触发器：缺少特定类型的术士宠物
    class NoSpecificPetTrigger : public Trigger
    {
    public:
        NoSpecificPetTrigger(PlayerbotAI* ai, std::string name, uint32 petEntry) : Trigger(ai, name, 5), entry(petEntry) {}
        bool IsActive() override;

    private:
        uint32 entry;
    };

    // 触发器：缺少小鬼宠物
    class NoImpTrigger : public NoSpecificPetTrigger
    {
    public:
        NoImpTrigger(PlayerbotAI* ai) : NoSpecificPetTrigger(ai, "no imp", 416) {}
    };

    // 触发器：缺少虚空行者宠物
    class NoVoidwalkerTrigger : public NoSpecificPetTrigger
    {
    public:
        NoVoidwalkerTrigger(PlayerbotAI* ai) : NoSpecificPetTrigger(ai, "no voidwalker", 1860) {}
    };

    // 触发器：缺少魅魔宠物
    class NoSuccubusTrigger : public NoSpecificPetTrigger
    {
    public:
        NoSuccubusTrigger(PlayerbotAI* ai) : NoSpecificPetTrigger(ai, "no succubus", 1863) {}
    };

    // 触发器：缺少地狱猎犬宠物
    class NoFelhunterTrigger : public NoSpecificPetTrigger
    {
    public:
        NoFelhunterTrigger(PlayerbotAI* ai) : NoSpecificPetTrigger(ai, "no felhunter", 417) {}
    };

    // 触发器：缺少恶魔卫士宠物
    class NoFelguardTrigger : public NoSpecificPetTrigger
    {
    public:
        NoFelguardTrigger(PlayerbotAI* ai) : NoSpecificPetTrigger(ai, "no felguard", 17252) {}
    };

    // 触发器：法术封锁
    class SpellLockTrigger : public InterruptSpellTrigger
    {
    public:
        SpellLockTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "spell lock") {}

        bool IsActive() override
        {
            return InterruptSpellTrigger::IsActive();
        }
    };

    // 触发器：法术封锁
    class SpellLockEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        SpellLockEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "spell lock") {}
    };

    // 触发器：复活目标
    class SoulstoneTrigger : public ItemTargetTrigger
    {
    public:
        SoulstoneTrigger(PlayerbotAI* ai) : ItemTargetTrigger(ai, "revive targets", true, true) {}
        std::string GetTargetName() override { return "party member to soulstone"; }
        uint32 GetItemId() override;
    };
}
