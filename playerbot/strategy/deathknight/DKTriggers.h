// 死亡骑士 - 触发器头文件 (DKTriggers.h)：定义死亡骑士增益、减益、冷却及状态检查触发条件
#pragma once
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    
    // 增益触发器：寒冬号角 (HornOfWinterTrigger)
    BUFF_TRIGGER(HornOfWinterTrigger, "horn of winter");
    // 增益触发器：白骨之盾 (BoneShieldTrigger)
    BUFF_TRIGGER(BoneShieldTrigger, "bone shield");
    // 增益触发器：强化冰冷之爪 (ImprovedIcyTalonsTrigger)
    BUFF_TRIGGER(ImprovedIcyTalonsTrigger, "improved icy talons");
    // 减益触发器：瘟疫打击 (PlagueStrikeDebuffTrigger)
    DEBUFF_TRIGGER(PlagueStrikeDebuffTrigger, "plague strike");
    // 减益触发器：冰冷触摸 (IcyTouchDebuffTrigger)
    DEBUFF_TRIGGER(IcyTouchDebuffTrigger, "icy touch");

        // 触发器：瘟疫打击
        class PlagueStrikeDebuffOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        PlagueStrikeDebuffOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "plague strike") {}
    };
        // 触发器：冰冷触摸
        class IcyTouchDebuffOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        IcyTouchDebuffOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "icy touch") {}
    };

    // 触发器：鲜血灵气
    class DKPresenceTrigger : public BuffTrigger {
    public:
        DKPresenceTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blood presence") {}
        virtual bool IsActive() override;
    };

    // 触发器：活力分流
    class BloodTapTrigger : public BuffTrigger {
    public:
        BloodTapTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "blood tap") {}
    };

    // 触发器：亡者复生
    class RaiseDeadTrigger : public BuffTrigger {
    public:
        RaiseDeadTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "raise dead") {}
    };


    // 触发器：符文打击
    class RuneStrikeTrigger : public SpellCanBeCastedTrigger {
    public:
        RuneStrikeTrigger(PlayerbotAI* ai) : SpellCanBeCastedTrigger(ai, "rune strike") {}
    };

    // 触发器：凋零缠绕/死亡缠绕
    class DeathCoilTrigger : public SpellCanBeCastedTrigger {
    public:
        DeathCoilTrigger(PlayerbotAI* ai) : SpellCanBeCastedTrigger(ai, "death coil") {}
    };

    // 触发器：传染
    class PestilenceTrigger : public DebuffTrigger {
    public:
        PestilenceTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "pestilence") {}
    };

    // 触发器：鲜血打击
    class BloodStrikeTrigger : public DebuffTrigger {
    public:
        BloodStrikeTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "blood strike") {}
    };


    // 触发器：凛风冲击
    class HowlingBlastTrigger : public DebuffTrigger {
    public:
        HowlingBlastTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "howling blast") {}
    };

    // 触发器：心灵冰冻
    class MindFreezeInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        MindFreezeInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "mind freeze") {}
    };

    // 触发器：绞袭
    class StrangulateInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        StrangulateInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "strangulate") {}
    };

    // 触发器：杀戮机器
    class KillingMachineTrigger : public BoostTrigger
    {
    public:
        KillingMachineTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "killing machine") {}
    };

    // 触发器：心灵冰冻
    class MindFreezeOnEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        MindFreezeOnEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "mind freeze") {}
    };

    // 触发器：寒冰锁链
    class ChainsOfIceSnareTrigger : public SnareTargetTrigger
    {
    public:
        ChainsOfIceSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "chains of ice") {}
    };

    // 触发器：绞袭
    class StrangulateOnEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        StrangulateOnEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "strangulate") {}
    };

    // 触发器：自动符文熔铸
    class AutoRuneForgeTrigger : public Trigger {
    public:
        AutoRuneForgeTrigger(PlayerbotAI* ai) : Trigger(ai, "auto runeforge") {}
        virtual bool IsActive() override {
            if (AI_VALUE2(time_t, "manual time", "next runeforge check") > time(0))
                return false;

            return AI_VALUE(bool, "should runeforge");
        }
    };
}
