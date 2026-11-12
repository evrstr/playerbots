// 猎人 - 触发器头文件 (HunterTriggers.h)：定义猎人增益、减益、冷却及状态检查触发条件
#pragma once

#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    // 光环剩余时间触发器：假死 (FeignDeathTrigger)
    HAS_AURA_TRIGGER_TIME(FeignDeathTrigger, "feign death", 2);

    // 自定义触发器定义：HunterNoStingsActiveTrigger
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    // 触发器：雄鹰守护
    class AspectOfTheHawkTrigger : public BuffTrigger
    {
    public:
        AspectOfTheHawkTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the hawk") {}
    };

    // 触发器：野性守护
    class AspectOfTheWildTrigger : public BuffTrigger
    {
    public:
        AspectOfTheWildTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the wild") {}
    };

    // 触发器：蝮蛇守护
    class AspectOfTheViperTrigger : public BuffTrigger
    {
    public:
        AspectOfTheViperTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the viper") {}
    };

    // 触发器：豹群守护
    class AspectOfThePackTrigger : public BuffTrigger
    {
    public:
        AspectOfThePackTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the pack") {}
    };

    // 触发器：灵猴守护
    class AspectOfTheMonkeyTrigger : public BuffTrigger
    {
    public:
        AspectOfTheMonkeyTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the monkey") {}
    };

    // 触发器：野兽守护
    class AspectOfTheBeastTrigger : public BuffTrigger
    {
    public:
        AspectOfTheBeastTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the beast") {}
    };

    // 触发器：猎豹守护
    class AspectOfTheCheetahTrigger : public BuffTrigger
    {
    public:
        AspectOfTheCheetahTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the cheetah") {}
    };

    // 触发器：龙鹰守护
    class AspectOfTheDragonhawkTrigger : public BuffTrigger
    {
    public:
        AspectOfTheDragonhawkTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the dragonhawk") {}
    
        bool IsActive() override
        {
            return BuffTrigger::IsActive() && !ai->HasAura("aspect of the hawk", bot);
        }
    };

    // 自定义触发器定义：HuntersPetDeadTrigger
    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    // 自定义触发器定义：HuntersPetLowHealthTrigger
    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

    // 触发器：黑箭
    class BlackArrowTrigger : public DebuffTrigger
    {
    public:
        BlackArrowTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "black arrow") {}
    };

    // 减速触发器：黑箭 (BlackArrowSnareTrigger)
    SNARE_TRIGGER(BlackArrowSnareTrigger, "black arrow");

    // 触发器：猎人印记
    class HuntersMarkTrigger : public DebuffTrigger
    {
    public:
        HuntersMarkTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "hunter's mark") {}
    };

    // 触发器：冰冻陷阱
    class FreezingTrapTrigger : public HasCcTargetTrigger
    {
    public:
        FreezingTrapTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "freezing trap") {}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
        bool IsActive() override
        {
            // Check if feign death not on cooldown
            if (sServerFacade.IsSpellReady(bot, 5384))
            {
                return HasCcTargetTrigger::IsActive();
            }

            return false;
        }
#endif
    };

    // 触发器：冰霜陷阱
    class FrostTrapTrigger : public MeleeLightAoeTrigger
    {
    public:
        FrostTrapTrigger(PlayerbotAI* ai, std::string spell = "frost trap") : MeleeLightAoeTrigger(ai)
        {
            spellId = AI_VALUE2(uint32, "spell id", spell);
        }

        bool IsActive() override
        {
// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
            // Check if feign death not on cooldown
            if (!sServerFacade.IsSpellReady(bot, 5384))
            {
                return false;
            }
#endif

            return sServerFacade.IsSpellReady(bot, spellId) && MeleeLightAoeTrigger::IsActive();
        }

    private:
        uint32 spellId;
    };

    // 触发器：爆炸陷阱
    class ExplosiveTrapTrigger : public RangedMediumAoeTrigger
    {
    public:
        ExplosiveTrapTrigger(PlayerbotAI* ai, std::string spell = "explosive trap") : RangedMediumAoeTrigger(ai)
        {
            spellId = AI_VALUE2(uint32, "spell id", spell);
        }

        bool IsActive() override
        {
// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
            // Check if feign death not on cooldown
            if (!sServerFacade.IsSpellReady(bot, 5384))
            {
                return false;
            }
#endif

            return sServerFacade.IsSpellReady(bot, spellId) && RangedMediumAoeTrigger::IsActive();
        }

    private:
        uint32 spellId;
    };

    // 触发器：急速射击
    class RapidFireTrigger : public BuffTrigger
    {
    public:
        RapidFireTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "rapid fire") {}
    };

    // 触发器：强击光环
    class TrueshotAuraTrigger : public BuffTrigger
    {
    public:
        TrueshotAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "trueshot aura") {}
    };

    // 触发器：毒蛇钉刺
    class SerpentStingOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        SerpentStingOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "serpent sting") {}
        virtual bool IsActive() override;
    };

    // 触发器：蝮蛇钉刺
    class ViperStingOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        ViperStingOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "viper sting") {}
        virtual bool IsActive() override;
    };

    // 自定义触发器定义：HunterPetNotHappy
    BEGIN_TRIGGER(HunterPetNotHappy, Trigger)
    END_TRIGGER()

    // 触发器：震荡射击
    class ConsussiveShotSnareTrigger : public SnareTargetTrigger
    {
    public:
        ConsussiveShotSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "concussive shot") {}
    };

    // 减速触发器：驱散射击 (ScatterShotSnareTrigger)
    SNARE_TRIGGER(ScatterShotSnareTrigger, "scatter shot");

    // 触发器：恐吓野兽
    class ScareBeastTrigger : public HasCcTargetTrigger
    {
    public:
        ScareBeastTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "scare beast") {}
    };

    // 触发器：弹药
    class HunterLowAmmoTrigger : public AmmoCountTrigger
    {
    public:
        HunterLowAmmoTrigger(PlayerbotAI* ai) : AmmoCountTrigger(ai, "ammo", 1, 30) {}
        virtual bool IsActive() override { return bot->GetGroup() && (AI_VALUE2(uint32, "item count", "ammo") < 100) && (AI_VALUE2(uint32, "item count", "ammo") > 0); }
    };

    // 触发器：弹药
    class HunterNoAmmoTrigger : public AmmoCountTrigger
{
public:
    HunterNoAmmoTrigger(PlayerbotAI* ai)
        : AmmoCountTrigger(ai, "ammo", 1, 10), lastCheckTime(0)
    {
    }

    virtual bool IsActive() override
    {
        uint32 now = time(nullptr);

        // Only check every 3 seconds to avoid spamming
        if (now - lastCheckTime < 3)
            return false;

        lastCheckTime = now;

        uint32 ammoId = bot->GetUInt32Value(PLAYER_AMMO_ID);

        // No ammo equipped at all
        if (ammoId == 0)
            return AI_VALUE2(uint32, "item count", "ammo") > 0;

        // Check if we still have THIS ammo in inventory
        uint32 count = AI_VALUE2(uint32, "item count", std::to_string(ammoId));

        // If equipped ammo is gone, but we have other ammo → trigger
        return count == 0 && AI_VALUE2(uint32, "item count", "ammo") > 0;
    }

private:
    time_t lastCheckTime;
};
    // 触发器：弹药
    class HunterHasAmmoTrigger : public AmmoCountTrigger
    {
    public:
        HunterHasAmmoTrigger(PlayerbotAI* ai) : AmmoCountTrigger(ai, "ammo", 1, 10) {}
        virtual bool IsActive() override { return !AmmoCountTrigger::IsActive(); }
    };

    // 触发器：切换至远程
    class SwitchToRangedTrigger : public Trigger
    {
    public:
        SwitchToRangedTrigger(PlayerbotAI* ai) : Trigger(ai, "switch to ranged", 1) {}

        bool IsActive() override
        {
// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
            bool hasAmmo = ai->HasCheat(BotCheatMask::item) || AI_VALUE2(uint32, "item count", "ammo");
#else
            bool hasAmmo = ai->HasCheat(BotCheatMask::item) || bot->HasAura(46699) || AI_VALUE2(uint32, "item count", "ammo");
#endif
            if (!hasAmmo)
                return false;

            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            float distance = AI_VALUE2(float, "distance", "current target");
            return target && ai->HasStrategy("close", BotState::BOT_STATE_COMBAT) &&
                (target->GetVictim() != bot ||
                target->IsImmobilizedState() ||
                (target->GetSpeed(MOVE_RUN) <= (bot->GetSpeed(MOVE_RUN) / 2) && !((!bot->GetPet() || bot->GetPet()->IsDead()) && target->IsCreature() && target->GetHealthPercent() < 50.f && target->GetHealth() < bot->GetHealth())) ||
                distance > 8.0f);
        }
    };

    // 触发器：切换至近战
    class SwitchToMeleeTrigger : public Trigger
    {
    public:
        SwitchToMeleeTrigger(PlayerbotAI* ai) : Trigger(ai, "switch to melee", 1) {}

        bool IsActive() override
        {
// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO
            bool hasAmmo = ai->HasCheat(BotCheatMask::item) || AI_VALUE2(uint32, "item count", "ammo");
#else
            bool hasAmmo = ai->HasCheat(BotCheatMask::item) || bot->HasAura(46699) || AI_VALUE2(uint32, "item count", "ammo");
#endif
            if (!hasAmmo)
                return true;

            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            return target && ((target->GetSpeed(MOVE_RUN) > (bot->GetSpeed(MOVE_RUN) / 2)) || ((!bot->GetPet() || bot->GetPet()->IsDead()) && target->GetHealthPercent() < 50.f && target->IsCreature() && target->GetHealth() < bot->GetHealth())) &&
                !target->IsImmobilizedState() &&
                ai->HasStrategy("ranged", BotState::BOT_STATE_COMBAT) &&
                target->GetVictim() == bot &&
                sServerFacade.IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "current target"), 8.0f);
        }
    };

    // 可施法检查触发器：奇美拉射击 (ChimeraShotCanCastTrigger)
    CAN_CAST_TRIGGER(ChimeraShotCanCastTrigger, "chimera shot");
    // 可施法检查触发器：爆炸射击 (ExplosiveShotCanCastTrigger)
    CAN_CAST_TRIGGER(ExplosiveShotCanCastTrigger, "explosive shot");
    // 可施法检查触发器：多重射击 (MultishotCanCastTrigger)
    CAN_CAST_TRIGGER(MultishotCanCastTrigger, "multi-shot");
    // 可施法检查触发器：稳固射击 (SteadyShotCanCastTrigger)
    CAN_CAST_TRIGGER(SteadyShotCanCastTrigger, "steady shot");
    // 可施法检查触发器：奥术射击 (ArcaneShotTrigger)
    CAN_CAST_TRIGGER(ArcaneShotTrigger, "arcane shot");
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
    // 爆发增益触发器：杀戮命令 (KillCommandBoostTrigger)
    BOOST_TRIGGER(KillCommandBoostTrigger, "kill command");
#else
    // 可施法检查触发器：杀戮命令 (KillCommandBoostTrigger)
    CAN_CAST_TRIGGER(KillCommandBoostTrigger, "kill command");
#endif
    // 减速触发器：胁迫 (IntimidationSnareTrigger)
    SNARE_TRIGGER(IntimidationSnareTrigger, "intimidation");
    // 可施法检查触发器：反击 (CounterattackCanCastTrigger)
    CAN_CAST_TRIGGER(CounterattackCanCastTrigger, "counterattack");
    // 减速触发器：翼龙钉刺 (WybernStingSnareTrigger)
    SNARE_TRIGGER(WybernStingSnareTrigger, "wyvern sting");
    // 可施法检查触发器：猫鼬撕咬 (MongooseBiteCastTrigger)
    CAN_CAST_TRIGGER(MongooseBiteCastTrigger, "mongoose bite");
    // 爆发增益触发器：狂野怒火 (BestialWrathBoostTrigger)
    BOOST_TRIGGER(BestialWrathBoostTrigger, "bestial wrath");

    // 打断触发器：沉默射击 (SilencingShotInterruptTrigger)
    INTERRUPT_TRIGGER(SilencingShotInterruptTrigger, "silencing shot");
    // 打断敌方治疗触发器：沉默射击 (SilencingShotInterruptHealerTrigger)
    INTERRUPT_HEALER_TRIGGER(SilencingShotInterruptHealerTrigger, "silencing shot");

    // 触发器：蝮蛇钉刺
    class ViperStingTrigger : public DebuffTrigger
    {
    public:
        ViperStingTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "viper sting") {}

        virtual bool IsActive() override
        {
            return DebuffTrigger::IsActive() && AI_VALUE2(uint8, "mana", "current target") >= 10;
        }
    };

    // 触发器：瞄准射击
    class AimedShotTrigger : public Trigger
    {
    public:
        AimedShotTrigger(PlayerbotAI* ai) : Trigger(ai, "aimed shot", 2) {}
        virtual std::string GetTargetName() override { return "current target"; }

        virtual bool IsActive() override
        {
            if (!bot->HasSpell(19434) || !bot->IsSpellReady(19434))
                return false;

            Unit* target = GetTarget();
            if (!target)
                return false;

            float distanceTo = AI_VALUE2(float, "distance", GetTargetName());
            if (target->GetSelectionGuid() != bot->GetObjectGuid() && sServerFacade.IsDistanceGreaterOrEqualThan(distanceTo, 8.0f))
                return true;

            // victim
            if (target->GetSelectionGuid() == bot->GetObjectGuid())
            {
                if (sServerFacade.IsDistanceGreaterOrEqualThan(distanceTo, 15.0f))
                    return true;
            }
            return false;
        }
    };

    // HunterNoPet
    class HunterNoPet : public Trigger 
    {
    public:
        HunterNoPet(PlayerbotAI* ai) : Trigger(ai, "no pet", 1) {}
        virtual bool IsActive() override
        {
            if (AI_VALUE2(bool, "mounted", "self target"))
            return false;

            if (bot->GetPetGuid())
            return false;

            if (ai->CanCastSpell("call pet", bot, 0))
            return false;

            return ai->CanCastSpell("tame beast", bot, 0);
        }
    };

    // 触发器：附近有潜行单位
    class StealthedNearbyTrigger : public Trigger 
    {
    public:
        StealthedNearbyTrigger(PlayerbotAI* ai) : Trigger(ai, "stealthed nearby", 5) {}
        virtual bool IsActive() override
        {
            if (!bot->HasSpell(1543))
                return false;

            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "nearest stealthed unit"));
            return target;
        }
    };
}

