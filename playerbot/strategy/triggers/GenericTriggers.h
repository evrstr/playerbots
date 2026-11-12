/// 通用核心触发器定义（资源、战斗、增益、减益、种族天赋等）
#pragma once
#include "playerbot/strategy/Trigger.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "Spells/SpellAuraDefines.h"
#include "DungeonTriggers.h"

namespace ai
{
    /// 触发器基类：检测指定数值资源是否达到阈值
    class StatAvailable : public Trigger
    {
    public:
        StatAvailable(PlayerbotAI* ai, int amount, std::string name = "stat available") : Trigger(ai, name)
        {
            this->amount = amount;
        }

    protected:
        int amount;
    };

    /// 触发器：检测当前怒气值是否足够
    class RageAvailable : public StatAvailable
    {
    public:
        RageAvailable(PlayerbotAI* ai, int amount) : StatAvailable(ai, amount, "rage available") {}
        virtual bool IsActive() override;
    };

    /// 触发器：少量怒气可用（>= 20）
    class LightRageAvailableTrigger : public RageAvailable
    {
    public:
        LightRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 20) {}
    };

    /// 触发器：中等怒气可用（>= 40）
    class MediumRageAvailableTrigger : public RageAvailable
    {
    public:
        MediumRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 40) {}
    };

    /// 触发器：高怒气可用（>= 60）
    class HighRageAvailableTrigger : public RageAvailable
    {
    public:
        HighRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 60) {}
    };

    /// 触发器：检测当前能量值是否足够
    class EnergyAvailable : public StatAvailable
    {
    public:
        EnergyAvailable(PlayerbotAI* ai, int amount) : StatAvailable(ai, amount, "energy available") {}
        virtual bool IsActive() override;
    };

    /// 触发器：能量不足（< 20）
    class NoEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        NoEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 20) {}

        bool IsActive() override
        {
            return AI_VALUE2(uint8, "energy", "self target") < amount;
        }
    };

    /// 触发器：少量能量可用（>= 20）
    class LightEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        LightEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 20) {}
    };

    /// 触发器：中等能量可用（>= 40）
    class MediumEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        MediumEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 40) {}
    };

    /// 触发器：高能量可用（>= 60）
    class HighEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        HighEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 60) {}
    };

    /// 触发器：当前目标上的连击点数是否达到指定数量（默认 5 星）
    class ComboPointsAvailableTrigger : public StatAvailable
    {
    public:
        ComboPointsAvailableTrigger(PlayerbotAI* ai, uint8 amount = 5) : StatAvailable(ai, amount, "combo points available") {}
        virtual bool IsActive() override;
    };

    /// 触发器：自身失去当前目标仇恨（坦克仇恨丢失检测）
    class LoseAggroTrigger : public Trigger 
    {
    public:
        LoseAggroTrigger(PlayerbotAI* ai) : Trigger(ai, "lose aggro") {}
        virtual bool IsActive() override;
    };

    /// 触发器：自身对当前目标持有最高仇恨
    class HasAggroTrigger : public Trigger 
    {
    public:
        HasAggroTrigger(PlayerbotAI* ai) : Trigger(ai, "have aggro") {}
        virtual bool IsActive() override;
    };

    /// 触发器基类：与指定法术关联的通用触发器
    class SpellTrigger : public Trigger
    {
    public:
        SpellTrigger(PlayerbotAI* ai, std::string spell, int checkInterval = 1) : Trigger(ai, spell, checkInterval)
        {
            this->spell = spell;
        }

        virtual std::string GetTargetName() override { return "current target"; }
        virtual std::string getName() override { return spell; }
        virtual bool IsActive() override;

    protected:
        std::string spell;
    };

    /// 触发器：指定法术当前满足所有施放条件
    class SpellCanBeCastedTrigger : public SpellTrigger
    {
    public:
        SpellCanBeCastedTrigger(PlayerbotAI* ai, std::string spell) : SpellTrigger(ai, spell) {}
        virtual bool IsActive() override;
    };

    /// 触发器：指定法术已脱离冷却时间
    class SpellNoCooldownTrigger : public SpellTrigger
    {
    public:
        SpellNoCooldownTrigger(PlayerbotAI* ai, std::string spell) : SpellTrigger(ai, spell) {}
        virtual bool IsActive() override;
    };

    // TODO: check other targets | 待办：检查其他潜在目标
    /// 触发器：当前目标正在施放可被打断的法术
    class InterruptSpellTrigger : public SpellTrigger
    {
    public:
        InterruptSpellTrigger(PlayerbotAI* ai, std::string spell) : SpellTrigger(ai, spell) {}
        virtual std::string GetTargetName() override { return "current target"; }
        virtual bool IsActive() override;
    };

    /// 触发器：存在正在攻击机器人自身的敌对目标
    class TargetOfAttacker : public Trigger
    {
    public:
        TargetOfAttacker(PlayerbotAI* ai, std::string name = "target of attacker", int checkInterval = 1) : Trigger(ai, name, checkInterval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：距离最近的攻击者进入指定范围内
    class TargetOfAttackerInRange : public TargetOfAttacker
    {
    public:
        TargetOfAttackerInRange(PlayerbotAI* ai, std::string name, float distance, int checkInterval = 1) : TargetOfAttacker(ai, name, checkInterval), distance(distance) {}
        virtual bool IsActive() override;

    private:
        float distance;
    };

    /// 触发器：攻击者进入近距离危险范围
    class TargetOfAttackerClose : public TargetOfAttackerInRange
    {
    public:
        TargetOfAttackerClose(PlayerbotAI* ai) : TargetOfAttackerInRange(ai, "target of attacker close", sPlayerbotAIConfig.tooCloseDistance) {}
    };

    /// 触发器：攻击者正在对机器人施放指定光环类型（如恐惧）的法术
    class TargetOfCastedAuraTypeTrigger : public Trigger
    {
    public:
        TargetOfCastedAuraTypeTrigger(PlayerbotAI* ai, std::string name, AuraType auraType, int checkInterval = 1) : Trigger(ai, name, checkInterval), auraType(auraType) {}
        virtual bool IsActive() override;

    private:
        AuraType auraType;
    };

    /// 触发器：攻击者正在对机器人施放恐惧类法术
    class TargetOfFearCastTrigger : public TargetOfCastedAuraTypeTrigger
    {
    public:
        TargetOfFearCastTrigger(PlayerbotAI* ai, std::string name = "target of fear cast") : TargetOfCastedAuraTypeTrigger(ai, name, AuraType::SPELL_AURA_MOD_FEAR) {}
    };

    /// 触发器：可使用法术反射或防御法术抵御目标施放的法术
    class DeflectSpellTrigger : public SpellTrigger
    {
    public:
        DeflectSpellTrigger(PlayerbotAI* ai, std::string spell) : SpellTrigger(ai, spell) {}
        virtual bool IsActive() override;
    };

    /// 触发器基类：视野内攻击者数量达到阈值
    class AttackerCountTrigger : public Trigger
    {
    public:
        AttackerCountTrigger(PlayerbotAI* ai, int amount, float distance = sPlayerbotAIConfig.sightDistance) : Trigger(ai, "attackers count", 2)
        {
            this->amount = amount;
            this->distance = distance;
        }

        virtual bool IsActive() override
        {
            return AI_VALUE(uint8, "attackers count") >= amount;
        }

        virtual std::string getName() override { return "attackers count"; }

    protected:
        int amount;
        float distance;
    };

    /// 触发器：至少存在 1 个攻击者
    class HasAttackersTrigger : public AttackerCountTrigger
    {
    public:
        HasAttackersTrigger(PlayerbotAI* ai) : AttackerCountTrigger(ai, 1) {}
    };

    /// 触发器：正在攻击机器人自身的敌人数量达到阈值
    class MyAttackerCountTrigger : public AttackerCountTrigger
    {
    public:
        MyAttackerCountTrigger(PlayerbotAI* ai, int amount) : AttackerCountTrigger(ai, amount) {}
        virtual bool IsActive() override;

        virtual std::string getName() override { return "my attacker count"; }
    };

    /// 触发器：正同时被 2 个或以上敌人攻击
    class MultipleAttackersTrigger : public MyAttackerCountTrigger
    {
    public:
        MultipleAttackersTrigger(PlayerbotAI* ai) : MyAttackerCountTrigger(ai, 2) {}
    };

    /// 触发器：当前目标对自身威胁值过高（>= 80%，即将 OT）
    class HighThreatTrigger : public Trigger
    {
    public:
        HighThreatTrigger(PlayerbotAI* ai, std::string name = "high threat", int checkinterval = 1) : Trigger(ai, name, checkinterval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前目标威胁值处于中等警戒区间（>= 60%）
    class MediumThreatTrigger : public Trigger
    {
    public:
        MediumThreatTrigger(PlayerbotAI* ai, std::string name = "medium threat", int checkinterval = 1) : Trigger(ai, name, checkinterval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前目标具有一定威胁值（>= 25%）
    class SomeThreatTrigger : public Trigger
    {
    public:
        SomeThreatTrigger(PlayerbotAI* ai, std::string name = "some threat", int checkinterval = 1) : Trigger(ai, name, checkinterval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前目标威胁值较低（< 25%）
    class NoThreatTrigger : public SomeThreatTrigger
    {
    public:
        NoThreatTrigger(PlayerbotAI* ai, std::string name = "some threat", int checkinterval = 1) : SomeThreatTrigger(ai, name, checkinterval) {}
        virtual bool IsActive() override;
    };

    /// 触发器基类：指定半径范围内存在足够密集的敌方单位可施放 AoE
    class AoeTrigger : public AttackerCountTrigger
    {
    public:
        AoeTrigger(PlayerbotAI* ai, int amount = 3, float range = 40.0f) : AttackerCountTrigger(ai, amount), range(range) {}
        std::string getName() override { return "aoe"; }
        bool IsActive() override;

    private:
        float range;
    };

    /// 触发器：近战轻度 AoE（5 码内至少 2 个敌人）
    class MeleeLightAoeTrigger : public AoeTrigger
    {
    public:
        MeleeLightAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 2, 5.0f) {}
    };

    /// 触发器：近战中度 AoE（5 码内至少 3 个敌人）
    class MeleeMediumAoeTrigger : public AoeTrigger
    {
    public:
        MeleeMediumAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 3, 5.0f) {}
    };

    /// 触发器：近战高度 AoE（5 码内至少 6 个敌人）
    class MeleeHighAoeTrigger : public AoeTrigger
    {
    public:
        MeleeHighAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 6, 5.0f) {}
    };

    /// 触发器：近战极高密度 AoE（5 码内至少 10 个敌人）
    class MeleeVeryHighAoeTrigger : public AoeTrigger
    {
    public:
        MeleeVeryHighAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 10, 5.0f) {}
    };

    /// 触发器：远程轻度 AoE（40 码内至少 2 个敌人）
    class RangedLightAoeTrigger : public AoeTrigger
    {
    public:
        RangedLightAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 2) {}
    };

    /// 触发器：远程中度 AoE（40 码内至少 3 个敌人）
    class RangedMediumAoeTrigger : public AoeTrigger
    {
    public:
        RangedMediumAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 3) {}
    };

    /// 触发器：远程高度 AoE（40 码内至少 5 个敌人）
    class RangedHighAoeTrigger : public AoeTrigger
    {
    public:
        RangedHighAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 5) {}
    };

    /// 触发器：远程极高密度 AoE（40 码内至少 10 个敌人）
    class RangedVeryHighAoeTrigger : public AoeTrigger
    {
    public:
        RangedVeryHighAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 10) {}
    };

    /// 触发器基类：目标缺少指定增益 Buff 光环
    class BuffTrigger : public SpellTrigger
    {
    public:
        BuffTrigger(PlayerbotAI* ai, std::string spell, int checkInterval = 1, bool checkIsOwner = false) : SpellTrigger(ai, spell, checkInterval) { this->checkIsOwner = checkIsOwner; }

    public:
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool IsActive() override;

    protected:
        bool checkIsOwner;
    };

    /// 触发器：目标缺少由机器人自身施放的指定增益光环
    class MyBuffTrigger : public BuffTrigger
    {
    public:
        MyBuffTrigger(PlayerbotAI* ai, std::string spell, int checkInterval = 1) : BuffTrigger(ai, spell, checkInterval) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：小队中存在缺少指定增益光环的成员
    class BuffOnPartyTrigger : public BuffTrigger
    {
    public:
        BuffOnPartyTrigger(PlayerbotAI* ai, std::string spell, int checkInterval = 2, bool ignoreTanks = false) : BuffTrigger(ai, spell, checkInterval), ignoreTanks(ignoreTanks) {}

    public:
        virtual Value<ObjectGuid>* GetTargetValue() override;
        virtual std::string getName() override { return spell + " on party"; }

    protected:
        bool ignoreTanks;
    };

    /// 触发器：小队成员缺少强效祝福或其低阶对应增益
    class GreaterBuffOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        GreaterBuffOnPartyTrigger(PlayerbotAI* ai, std::string spell, std::string lowerSpell, int checkInterval = 2, bool ignoreTanks = false) : BuffOnPartyTrigger(ai, spell, checkInterval, ignoreTanks), lowerSpell(lowerSpell) {}
        virtual Value<ObjectGuid>* GetTargetValue() override;
        virtual bool IsActive() override;

    private:
        std::string lowerSpell;
    };

    /// 触发器：队伍坦克缺少指定增益光环
    class BuffOnTankTrigger : public BuffTrigger
    {
    public:
        BuffOnTankTrigger(PlayerbotAI* ai, std::string spell, int checkInterval = 2) : BuffTrigger(ai, spell, checkInterval) {}

    public:
        virtual Value<ObjectGuid>* GetTargetValue() override;
        virtual std::string getName() override { return spell + " on tank"; }
    };

    /// 触发器：小队成员缺少由机器人自身施放的指定光环
    class MyBuffOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        MyBuffOnPartyTrigger(PlayerbotAI* ai, std::string spell, int checkInterval = 2, bool ignoreTanks = false) : BuffOnPartyTrigger(ai, spell, checkInterval, ignoreTanks) {}

    public:
        virtual Value<ObjectGuid>* GetTargetValue() override;
        virtual std::string getName() override { return spell + " on party"; }
    };

    /// 触发器：自身缺少指定增益且目标连击点已达要求
    class NoBuffAndComboPointsAvailableTrigger : public BuffTrigger
    {
    public:
        NoBuffAndComboPointsAvailableTrigger(PlayerbotAI* ai, std::string spell, uint8 comboPoints, bool checkIsOwner = true, int checkInterval = 1) : BuffTrigger(ai, spell, checkInterval, checkIsOwner), comboPoints(comboPoints) {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual std::string GetComboPointsTargetName() { return "current target"; }
        virtual bool IsActive() override;

    private:
        uint8 comboPoints;
    };

    /// 触发器：目标缺少指定减益且连击点已达要求
    class NoDebuffAndComboPointsAvailableTrigger : public NoBuffAndComboPointsAvailableTrigger
    {
    public:
        NoDebuffAndComboPointsAvailableTrigger(PlayerbotAI* ai, std::string spell, uint8 comboPoints, bool checkIsOwner = true, int checkInterval = 1) : NoBuffAndComboPointsAvailableTrigger(ai, spell, comboPoints, checkIsOwner, checkIsOwner) {}
        virtual std::string GetTargetName() override { return "current target"; }
    };

    /// 触发器：目标列表中有满足条件需要施放法术的单位
    class SpellTargetTrigger : public SpellTrigger
    {
    public:
        SpellTargetTrigger(PlayerbotAI* ai, std::string spell, std::string targetsValue, bool aliveCheck = false, bool auraCheck = false, int checkInterval = 1) : SpellTrigger(ai, spell, checkInterval), targetsValue(targetsValue), aliveCheck(aliveCheck), auraCheck(auraCheck) {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool IsTargetValid(Unit* target);
        virtual bool IsSpellReady();

    private:
        bool IsActive() override;

    private:
        std::string targetsValue;
        bool aliveCheck;
        bool auraCheck;
    };

    /// 触发器：目标列表中有满足条件需要使用物品的单位
    class ItemTargetTrigger : public SpellTargetTrigger
    {
    public:
        ItemTargetTrigger(PlayerbotAI* ai, std::string targetsValue, bool aliveCheck = false, bool auraCheck = false, int checkInterval = 1) : SpellTargetTrigger(ai, "item target", targetsValue, aliveCheck, false, checkInterval), itemAuraCheck(auraCheck) {}
        virtual bool IsTargetValid(Unit* target) override;
        virtual bool IsSpellReady() override;
        virtual uint32 GetItemId() = 0;

    private:
        bool itemAuraCheck;
    };

    /// 触发器：存在需要保护的友方小队成员
    class ProtectPartyMemberTrigger : public Trigger
    {
    public:
        ProtectPartyMemberTrigger(PlayerbotAI* ai) : Trigger(ai, "protect party member") {}
        virtual std::string GetTargetName() override { return "party member to protect"; }

        virtual bool IsActive() override
        {
            return ai->GetUnit(AI_VALUE(ObjectGuid, "party member to protect"));
        }
    };

    /// 触发器：当前无主目标但有敌人正在攻击自己
    class NoAttackersTrigger : public Trigger
    {
    public:
        NoAttackersTrigger(PlayerbotAI* ai, std::string name = "no attackers") : Trigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前未选中目标或需要切换至有效目标
    class NoTargetTrigger : public Trigger
    {
    public:
        NoTargetTrigger(PlayerbotAI* ai) : Trigger(ai, "no target") {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前目标已失效（死亡、消失或不可攻击）
    class InvalidTargetTrigger : public Trigger
    {
    public:
        InvalidTargetTrigger(PlayerbotAI* ai) : Trigger(ai, "invalid target") {}
        virtual bool IsActive() override;
    };

    /// 触发器：视野内存在可刷怪（Grind）的目标
    class TargetInSightTrigger : public Trigger 
    {
    public:
        TargetInSightTrigger(PlayerbotAI* ai) : Trigger(ai, "target in sight") {}
        virtual bool IsActive() override { return ai->GetUnit(AI_VALUE(ObjectGuid, "grind target")); }
    };

    /// 触发器：当前目标缺少指定减益（Debuff）且未达上限
    class DebuffTrigger : public BuffTrigger
    {
    public:
        DebuffTrigger(PlayerbotAI* ai, std::string spell, int checkInterval = 1, bool checkIsOwner = false) : BuffTrigger(ai, spell, checkInterval, checkIsOwner) {}

    public:
        virtual std::string GetTargetName() override { return "current target"; }
        virtual bool IsActive() override;

    protected:
        bool HasMaxDebuffs();
    };

    /// 触发器：存在缺少指定减益的攻击者单位
    class DebuffOnAttackerTrigger : public DebuffTrigger
    {
    public:
        DebuffOnAttackerTrigger(PlayerbotAI* ai, std::string spell) : DebuffTrigger(ai, spell) {}

    public:
        virtual Value<ObjectGuid>* GetTargetValue() override;
        virtual std::string getName() override { return spell + " on attacker"; }
    };

    /// 触发器：爆发技能触发器（满足平衡度或副本 Boss 条件时开启）
    class BoostTrigger : public BuffTrigger
    {
    public:
        BoostTrigger(PlayerbotAI* ai, std::string spell, float balance = 50) : BuffTrigger(ai, spell, 3), balance(balance) {}
        virtual bool IsActive() override;

    protected:
        float balance;
    };

    /// 触发器：基于随机概率和冷却间隔触发
    class RandomTrigger : public Trigger
    {
    public:
        RandomTrigger(PlayerbotAI* ai, std::string name, int probability = 7) : Trigger(ai, name)
        {
            this->probability = probability;
            lastCheck = time(0);         
        }

        virtual bool IsActive() override;

    protected:
        time_t lastCheck;
        int probability;
    };

    /// 触发器：固定时间间隔周期性触发
    class TimeTrigger : public Trigger
    {
    public:
        TimeTrigger(PlayerbotAI* ai, std::string name, int interval = 2) : Trigger(ai, name, interval) {}
        virtual bool IsActive() override { return true; }
    };

    /// 触发器：逻辑与组合触发器（所有逗号分隔子触发器均激活时触发）
    class AndTrigger : public Trigger, public Qualified
    {
    public:
         AndTrigger(PlayerbotAI* ai, std::string name = "and", int checkInterval = 1) : Trigger(ai, name, checkInterval), Qualified() {}
        virtual bool IsActive() override;
        virtual std::string getName() override;
    };

    /// 触发器：逻辑或组合触发器（任意逗号分隔子触发器激活时触发）
    class OrTrigger : public Trigger, public Qualified
    {
    public:
        OrTrigger(PlayerbotAI* ai, std::string name = "or", int checkInterval = 1) : Trigger(ai, name, checkInterval), Qualified() {}
        virtual bool IsActive() override;
        virtual std::string getName() override;
    };

    /// 触发器：双触发器逻辑与组合
    class TwoTriggers : public Trigger
    {
    public:
        TwoTriggers(PlayerbotAI* ai, std::string name1 = "", std::string name2 = "") : Trigger(ai)
        {
            this->name1 = name1;
            this->name2 = name2;
        }

        virtual bool IsActive() override;
        virtual std::string getName() override;

    protected:
        std::string name1;
        std::string name2;
    };

    /// 触发器：直接评估指定布尔型 AI Value 的通用触发器
    class ValueTrigger : public Trigger, public Qualified
    {
    public:
        ValueTrigger(PlayerbotAI* ai, std::string name = "val", int checkInterval = 1) : Trigger(ai, name, checkInterval), Qualified() {}
        virtual bool IsActive() override { name = getQualifier();  return AI_VALUE(bool, getQualifier()); }
    };

    /// 触发器：存在需要减速控制（风筝/防逃跑）的目标
    class SnareTargetTrigger : public DebuffTrigger
    {
    public:
        SnareTargetTrigger(PlayerbotAI* ai, std::string spell, int interval = 1) : DebuffTrigger(ai, spell, interval) {}
        virtual std::string getName() override { return spell + " on snare target"; }
        virtual Value<ObjectGuid>* GetTargetValue() override;
    };

    /// 触发器：法力值耗尽（< 5%）
    class NoManaTrigger : public Trigger
    {
    public:
        NoManaTrigger(PlayerbotAI* ai) : Trigger(ai, "no mana") {}

        virtual bool IsActive() override;
    };

    /// 触发器：低法力值
    class LowManaTrigger : public Trigger
    {
    public:
        LowManaTrigger(PlayerbotAI* ai) : Trigger(ai, "low mana") {}

        virtual bool IsActive() override;
    };

    /// 触发器：中等法力值
    class MediumManaTrigger : public Trigger
    {
    public:
        MediumManaTrigger(PlayerbotAI* ai) : Trigger(ai, "medium mana") {}

        virtual bool IsActive() override;
    };

    /// 触发器：高法力值（< 65%）
    class HighManaTrigger : public Trigger
    {
    public:
        HighManaTrigger(PlayerbotAI* ai) : Trigger(ai, "high mana") {}

        virtual bool IsActive() override;
    };

    /// 触发器：接近满法力值（> 85%）
    class AlmostFullManaTrigger : public Trigger
    {
    public:
        AlmostFullManaTrigger(PlayerbotAI* ai) : Trigger(ai, "almost full mana") {}

        virtual bool IsActive() override;
    };

    /// 触发器：濒危恐慌状态（非 PvP 环境下生命与法力同时危急）
    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual std::string getName() override { return "panic"; }
    END_TRIGGER()

    /// 触发器：野外战斗处于明显人数/战力劣势
    BEGIN_TRIGGER(OutNumberedTrigger, Trigger)
        virtual std::string getName() override { return "outnumbered"; }
    END_TRIGGER()

    /// 触发器：当前未召唤宠物且未处于骑乘状态
    class NoPetTrigger : public Trigger
    {
    public:
        NoPetTrigger(PlayerbotAI* ai) : Trigger(ai, "no pet", 30) {}

        virtual bool IsActive() override
        {
            return !ai->GetUnit(AI_VALUE(ObjectGuid, "pet target")) && !AI_VALUE2(bool, "mounted", "self target");
        }
    };

    /// 触发器：指定物品库存数量低于设定阈值
    class ItemCountTrigger : public Trigger 
    {
    public:
        ItemCountTrigger(PlayerbotAI* ai, std::string item, int count, int interval = 30) : Trigger(ai, item, interval) 
        {
            this->item = item;
            this->count = count;
        }

        virtual bool IsActive() override;
        virtual std::string getName() override { return "item count"; }

    protected:
        std::string item;
        int count;
    };

    /// 触发器：弹药（箭矢/子弹）库存数量不足
    class AmmoCountTrigger : public ItemCountTrigger
    {
    public:
        AmmoCountTrigger(PlayerbotAI* ai, std::string item, uint32 count = 1, int interval = 30) : ItemCountTrigger(ai, item, count, interval) {}
    };

    /// 触发器：检测目标身上是否带有指定名称/ID/层数的光环
    class HasAuraTrigger : public Trigger, public Qualified
    {
    public:
        HasAuraTrigger(PlayerbotAI* ai, std::string spell = "", int interval = 1, int auraTypeId = TOTAL_AURAS) : Trigger(ai, spell, interval), Qualified(), auraTypeId(auraTypeId) {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool IsActive() override;
      virtual std::string getName() override;

    protected:
        int auraTypeId;
    };

    /// 触发器：检测自身是否不带有指定光环
    class HasNoAuraTrigger : public Trigger 
    {
    public:
        HasNoAuraTrigger(PlayerbotAI* ai, std::string spell) : Trigger(ai, spell) {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool IsActive() override;
    };

    /// 触发器：每秒触发一次的通用计时器触发器
    class TimerTrigger : public Trigger
    {
    public:
        TimerTrigger(PlayerbotAI* ai) : Trigger(ai, "timer"), lastCheck(0) {}

        virtual bool IsActive() override
        {
            if (time(0) != lastCheck)
            {
                lastCheck = time(0);
                return true;
            }
            return false;
        }

    private:
        time_t lastCheck;
    };

    /// 触发器：协助坦克攻击当前坦克目标
    class TankAssistTrigger : public NoAttackersTrigger
    {
    public:
        TankAssistTrigger(PlayerbotAI* ai) : NoAttackersTrigger(ai, "tank assist") {}
        virtual bool IsActive() override;
    };

    /// 触发器：DPS 协助攻击队伍目标（兼顾宠物与开怪等待逻辑）
    class DpsAssistTrigger : public Trigger
    {
    public:
        DpsAssistTrigger(PlayerbotAI* ai) : Trigger(ai, "dps assist", 2) {}
        virtual bool IsActive() override;
    };

    /// 触发器：机器人当前处于目标背后
    class IsBehindTargetTrigger : public Trigger
    {
    public:
        IsBehindTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}
        virtual bool IsActive() override;
    };

    /// 触发器：机器人当前未处于目标背后
    class IsNotBehindTargetTrigger : public Trigger
    {
    public:
        IsNotBehindTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}
        virtual bool IsActive() override;
    };

    /// 触发器：机器人当前未面向目标
    class IsNotFacingTargetTrigger : public Trigger
    {
    public:
        IsNotFacingTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}
        virtual bool IsActive() override;
    };

    /// 触发器：存在可用控制技能处理且就绪的控场（CC）目标
    class HasCcTargetTrigger : public Trigger
    {
    public:
        HasCcTargetTrigger(PlayerbotAI* ai, std::string name) : Trigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：机器人当前未在移动
    class NoMovementTrigger : public Trigger
    {
    public:
        NoMovementTrigger(PlayerbotAI* ai, std::string name) : Trigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：周围无任何可攻击目标
    class NoPossibleTargetsTrigger : public Trigger
    {
    public:
        NoPossibleTargetsTrigger(PlayerbotAI* ai) : Trigger(ai, "no possible targets") {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前攻击的不是最优单体 DPS 目标
    class NotDpsTargetActiveTrigger : public Trigger
    {
    public:
        NotDpsTargetActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "not dps target active", 2) {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前攻击的不是最优 AoE 目标
    class NotDpsAoeTargetActiveTrigger : public Trigger
    {
    public:
        NotDpsAoeTargetActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "not dps aoe target active") {}
        virtual bool IsActive() override;
    };

    /// 触发器：周围存在可能引到的额外巡逻/潜在怪物
    class PossibleAddsTrigger : public Trigger
    {
    public:
        PossibleAddsTrigger(PlayerbotAI* ai) : Trigger(ai, "possible adds") {}
        virtual bool IsActive() override;
    };

    /// 触发器：机器人当前正处于游泳状态
    class IsSwimmingTrigger : public Trigger
    {
    public:
        IsSwimmingTrigger(PlayerbotAI* ai) : Trigger(ai, "swimming") {}
        virtual bool IsActive() override;
    };

    /// 触发器：最近范围内存在新增的 Add 敌人
    class HasNearestAddsTrigger : public Trigger
    {
    public:
        HasNearestAddsTrigger(PlayerbotAI* ai) : Trigger(ai, "has nearest adds") {}
        virtual bool IsActive() override;
    };

    /// 触发器：背包中持有施放指定法术所需的消耗材料物品
    class HasItemForSpellTrigger : public Trigger
    {
    public:
        HasItemForSpellTrigger(PlayerbotAI* ai, std::string spell) : Trigger(ai, spell) {}
        virtual bool IsActive() override;
    };

    /// 触发器：当前选定的目标发生变更
    class TargetChangedTrigger : public Trigger
    {
    public:
        TargetChangedTrigger(PlayerbotAI* ai) : Trigger(ai, "target changed") {}
        virtual bool IsActive() override;
    };

    /// 触发器：存在可被打断施法的敌方治疗者
    class InterruptEnemyHealerTrigger : public SpellTrigger
    {
    public:
        InterruptEnemyHealerTrigger(PlayerbotAI* ai, std::string spell) : SpellTrigger(ai, spell) {}
        virtual Value<ObjectGuid>* GetTargetValue() override;
        virtual std::string getName() override { return spell + " on enemy healer"; }
    };

    /// 触发器：随机机器人周期性自主更新触发器
    class RandomBotUpdateTrigger : public RandomTrigger
    {
    public:
        RandomBotUpdateTrigger(PlayerbotAI* ai) : RandomTrigger(ai, "random bot update", 30) {}

        virtual bool IsActive() override
        {
            return RandomTrigger::IsActive() && AI_VALUE(bool, "random bot update");
        }
    };

    /// 触发器：周围没有任何真人玩家
    class NoNonBotPlayersAroundTrigger : public Trigger
    {
    public:
        NoNonBotPlayersAroundTrigger(PlayerbotAI* ai) : Trigger(ai, "no non bot players around", 10) {}

        virtual bool IsActive() override
        {
            return !ai->HasPlayerNearby();
            /*if (!bot->InBattleGround())
                return AI_VALUE(std::list<ObjectGuid>, "nearest non bot players").empty();
            else
                return false;*/
        }
    };

    /// 触发器：检测到有新玩家进入附近视野
    class NewPlayerNearbyTrigger : public Trigger
    {
    public:
        NewPlayerNearbyTrigger(PlayerbotAI* ai) : Trigger(ai, "new player nearby", 10) {}

        virtual bool IsActive() override
        {
            return AI_VALUE(ObjectGuid, "new player nearby");
        }
    };

    /// 触发器：检测到与其他单位或障碍物发生碰撞重叠
    class CollisionTrigger : public Trigger
    {
    public:
        CollisionTrigger(PlayerbotAI* ai) : Trigger(ai, "collision", 5) {}

        virtual bool IsActive() override
        {
            return AI_VALUE2(bool, "collision", "self target");
        }
    };

    /// 触发器基类：在原地停留达到指定延迟时间后触发
    class StayTimeTrigger : public Trigger
    {
    public:
        StayTimeTrigger(PlayerbotAI* ai, uint32 delay, std::string name) : Trigger(ai, name, 5), delay(delay) {}

        virtual bool IsActive() override;

    private:
        uint32 delay;
    };

    /// 触发器：原地静止超时后坐下休息
    class SitTrigger : public StayTimeTrigger
    {
    public:
        SitTrigger(PlayerbotAI* ai) : StayTimeTrigger(ai, sPlayerbotAIConfig.sitDelay, "sit") {}
    };

    /// 触发器：原地静止超时后返回初始位置
    class ReturnTrigger : public StayTimeTrigger
    {
    public:
        ReturnTrigger(PlayerbotAI* ai) : StayTimeTrigger(ai, sPlayerbotAIConfig.returnDelay, "return") {}
    };

    /// 触发器：偏离预设停留（Stay）位置过远需返回
    class ReturnToStayPositionTrigger : public Trigger
    {
    public:
        ReturnToStayPositionTrigger(PlayerbotAI* ai) : Trigger(ai, "return to stay position", 2) {}

        virtual bool IsActive() override;
    };

    /// 触发器：偏离预设拉怪（Pull）位置过远需返回
    class ReturnToPullPositionTrigger : public Trigger
    {
    public:
        ReturnToPullPositionTrigger(PlayerbotAI* ai) : Trigger(ai, "return to pull position", 2) {}

        virtual bool IsActive() override;
    };

    /// 触发器基类：队友缺少指定物品且自身有库存可交易/分发
    class GiveItemTrigger : public Trigger
    {
    public:
        GiveItemTrigger(PlayerbotAI* ai, std::string name, std::string item) : Trigger(ai, name, 2), item(item) {}

        virtual bool IsActive() override
        {
            return ai->GetUnit(AI_VALUE2(ObjectGuid, "party member without item", item)) && AI_VALUE2(uint32, "item count", item);
        }

    protected:
        std::string item;
    };

    /// 触发器：需要向缺少食物的队友分发魔法食物
    class GiveFoodTrigger : public GiveItemTrigger
    {
    public:
        GiveFoodTrigger(PlayerbotAI* ai) : GiveItemTrigger(ai, "give food", "conjured food") {}

        virtual bool IsActive() override
        {
            return ai->GetUnit(AI_VALUE(ObjectGuid, "party member without food")) && AI_VALUE2(uint32, "item count", item);
        }
    };

    /// 触发器：需要向缺少饮水的队友分发魔法饮水
    class GiveWaterTrigger : public GiveItemTrigger
    {
    public:
        GiveWaterTrigger(PlayerbotAI* ai) : GiveItemTrigger(ai, "give water", "conjured water") {}

        virtual bool IsActive() override
        {
            return ai->GetUnit(AI_VALUE(ObjectGuid, "party member without water")) && AI_VALUE2(uint32, "item count", item);
        }
    };

    /// 触发器：机器人当前正处于骑乘状态
    class IsMountedTrigger : public Trigger
    {
    public:
        IsMountedTrigger(PlayerbotAI* ai) : Trigger(ai, "mounted", 1) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：距离自身尸体足够近，可就地复活
    class CorpseNearTrigger : public Trigger
    {
    public:
        CorpseNearTrigger(PlayerbotAI* ai) : Trigger(ai, "corpse near", 10) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：角色正处于坠落/跳跃状态
    class IsFallingTrigger : public Trigger
    {
    public:
        IsFallingTrigger(PlayerbotAI* ai) : Trigger(ai, "falling", 10) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：角色正处于高空长距离坠落状态
    class IsFallingFarTrigger : public Trigger
    {
    public:
        IsFallingFarTrigger(PlayerbotAI* ai) : Trigger(ai, "falling far", 10) {}

    public:
        virtual bool IsActive() override;
    };

    /// 触发器：存在冷却就绪的主动使用饰品
    class UseTrinketTrigger : public Trigger
    {
    public:
        UseTrinketTrigger(PlayerbotAI* ai) : Trigger(ai, "use trinket", 3) {}
        virtual bool IsActive() override { return !AI_VALUE(std::list<Item*>, "trinkets on use").empty(); }
    };

    /// 触发器：自身正承受区域性环境减益效果
    class HasAreaDebuffTrigger : public Trigger 
    {
    public:
        HasAreaDebuffTrigger(PlayerbotAI* ai) : Trigger(ai, "has area debuff", 3) {}
        virtual bool IsActive() override;
    };

    // racials | 种族天赋触发器

    /// 触发器：巨魔种族天赋“狂暴”爆发
    class BerserkingTrigger : public BoostTrigger
    {
    public:
        BerserkingTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "berserking") {}
    };

    /// 触发器：兽人种族天赋“血性狂怒”爆发
    class BloodFuryTrigger : public BoostTrigger
    {
    public:
        BloodFuryTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "blood fury") {}
    };

    /// 触发器：亡灵种族天赋“食尸”（血量未满且5码内有人形/亡灵尸体）
    class CannibalizeTrigger : public Trigger
    {
    public:
        CannibalizeTrigger(PlayerbotAI* ai) : Trigger(ai, "cannibalize") {}

        virtual bool IsActive() override
        {
            if (AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig.almostFullHealth)
                return false;

            std::list<ObjectGuid> corpses = context->GetValue<std::list<ObjectGuid> >("nearest corpses")->Get();
            for (std::list<ObjectGuid>::iterator i = corpses.begin(); i != corpses.end(); i++)
            {
                if (!i->IsUnit())
                    continue;

                Unit* corpse = ai->GetUnit(*i);
                if (!corpse)
                    continue;

                if (!(corpse->GetCreatureType() == CREATURE_TYPE_HUMANOID || corpse->GetCreatureType() == CREATURE_TYPE_UNDEAD))
                    continue;

                if (sServerFacade.GetDistance2d(bot, corpse) <= 5.0f)
                    return true;
            }
            return false;
        }

    };

    /// 触发器：亡灵种族天赋“亡灵意志”（处于恐惧/昏迷/魅惑/混乱状态）
    class WOtFTrigger : public Trigger
    {
    public:
        WOtFTrigger(PlayerbotAI* ai) : Trigger(ai, "will of the forsaken") {}

        virtual bool IsActive() override
        {
            return bot->HasAuraType(SPELL_AURA_MOD_FEAR);
            return bot->HasAuraType(SPELL_AURA_MOD_STUN);
            return bot->HasAuraType(SPELL_AURA_MOD_CHARM);
            return bot->HasAuraType(SPELL_AURA_MOD_CONFUSE);
        }
    };

    /// 触发器：自身处于定身或减速状态（非生命之树形态）
    class RootedTrigger : public Trigger
    {
    public:
        RootedTrigger(PlayerbotAI* ai) : Trigger(ai, "rooted") {}

        bool IsActive() override
        {
            return bot->HasAuraType(SPELL_AURA_MOD_ROOT) ||
                   (bot->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED) && !ai->HasAnyAuraOf(bot, "tree of life", NULL));
        }
    };

    /// 触发器：队友处于定身状态需要协助解除
    class PartyMemberRootedTrigger : public Trigger
    {
    public:
        PartyMemberRootedTrigger(PlayerbotAI* ai) : Trigger(ai, "party member rooted") {}

        bool IsActive() override
        {
            return ai->GetUnit(AI_VALUE(ObjectGuid, "party member to remove roots"));
        }
    };

    /// 触发器：自身处于恐惧状态
    class FearedTrigger : public Trigger
    {
    public:
        FearedTrigger(PlayerbotAI* ai) : Trigger(ai, "feared") {}

        bool IsActive() override
        {
            return bot->HasAuraType(SPELL_AURA_MOD_FEAR);
        }
    };

    /// 触发器：自身处于昏迷状态
    class StunnedTrigger : public Trigger
    {
    public:
        StunnedTrigger(PlayerbotAI* ai) : Trigger(ai, "stunned") {}

        bool IsActive() override
        {
            return bot->HasAuraType(SPELL_AURA_MOD_STUN);
        }
    };

    /// 触发器：自身处于魅惑状态
    class CharmedTrigger : public Trigger
    {
    public:
        CharmedTrigger(PlayerbotAI* ai) : Trigger(ai, "charmed") {}

        bool IsActive() override
        {
            return bot->HasAuraType(SPELL_AURA_MOD_CHARM);
        }
    };

    /// 触发器：矮人种族天赋“石像形态”（中了流血/中毒/疾病）
    class StoneformTrigger : public Trigger
    {
    public:
        StoneformTrigger(PlayerbotAI* ai) : Trigger(ai, "stoneform") {}

        virtual bool IsActive() override
        {
            uint32 disMask = GetDispellMask(DISPEL_DISEASE);
            uint32 poisMask = GetDispellMask(DISPEL_POISON);
            uint32 bleedType = 1 << (MECHANIC_BLEED - 1);
            for (auto itr : bot->GetSpellAuraHolderMap())
            {
                SpellEntry const* spell = itr.second->GetSpellProto();
                if (IsPositiveSpell(spell->Id))
                    continue;

                if (((1 << spell->Dispel) & disMask) || ((1 << spell->Dispel) & poisMask))
                    return true;

                if (!spell->HasAttribute(SPELL_ATTR_NO_IMMUNITIES) && itr.second->HasMechanicMask(bleedType))
                    return true;
            }
            return false;
        }
    };

    /// 触发器：暗夜精灵种族天赋“影遁”
    class ShadowmeldTrigger : public Trigger
    {
    public:
        ShadowmeldTrigger(PlayerbotAI* ai) : Trigger(ai, "shadowmeld") {}

        virtual bool IsActive() override
        {
            Unit* master = ai->GetMaster();
            if (ai->HasAura("shadowmeld", bot))
                return false;
            return ((!master || (master && master->HasStealthAura() && !master->IsMoving())) && !bot->IsMoving());
        }
    };

    /// 触发器：血精灵种族天赋“法力分流”（目标拥有法力值）
    class ManaTapTrigger : public Trigger
    {
    public:
        ManaTapTrigger(PlayerbotAI* ai) : Trigger(ai, "mana tap") {}

        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            return target && AI_VALUE2(bool, "has mana", "current target");
        }
    };

    /// 触发器：血精灵种族天赋“奥术洪流”（8码内目标正在施放可打断法术）
    class ArcanetorrentTrigger : public InterruptSpellTrigger
    {
    public:
        ArcanetorrentTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "arcane torrent") {}

        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            return InterruptSpellTrigger::IsActive() && target && AI_VALUE2(float, "distance", "current target") <= 8.0f;
        }
    };

    /// 触发器：牛头人种族天赋“战争践踏”（8码内需要自保或打断）
    class WarStompTrigger : public Trigger
    {
    public:
        WarStompTrigger(PlayerbotAI* ai) : Trigger(ai, "war stomp") {}

        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            return target && AI_VALUE2(bool, "combat", "self target") && AI_VALUE2(float, "distance", "current target") <= 8.0f &&
                (AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.mediumHealth ||
                    AI_VALUE(uint8, "my attacker count") >= 3 ||
                    ai->IsInterruptableSpellCasting(target, "war stomp"));
        }
    };

    /// 触发器：人类种族天赋“感知”（探测周围潜行职业）
    class PerceptionTrigger : public BuffTrigger
    {
    public:
        PerceptionTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "perception") {}

        virtual bool IsActive() override
        {
            for (auto& attacker : ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get())
            {
                Unit* enemy = ai->GetUnit(attacker);
                if (!enemy)
                    continue;

                if (enemy->getClass() == CLASS_ROGUE || enemy->getClass() == CLASS_DRUID)
                    return true;
            }
            return false;
        }
    };

    /// 触发器：当前处于 PvP 战斗/区域环境
    class InPvpTrigger : public Trigger
    {
    public:
        InPvpTrigger(PlayerbotAI* ai, std::string name = "in pvp") : Trigger(ai, name, 5) {}
        bool IsActive() override;
    };

    /// 触发器：当前处于 PvE 战斗/区域环境
    class InPveTrigger : public Trigger
    {
    public:
        InPveTrigger(PlayerbotAI* ai, std::string name = "in pve") : Trigger(ai, name, 5) {}
        bool IsActive() override;
    };

    /// 触发器：当前处于团队副本战斗中
    class InRaidFightTrigger : public Trigger
    {
    public:
        InRaidFightTrigger(PlayerbotAI* ai, std::string name = "in raid fight") : Trigger(ai, name, 5) {}
        bool IsActive() override;
    };

    /// 触发器：身上存在拯救祝福光环
    class HasBlessingOfSalvationTrigger : public HasAuraTrigger
    {
    public:
        HasBlessingOfSalvationTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "blessing of salvation") {}
    };

    /// 触发器：身上存在强效拯救祝福光环
    class HasGreaterBlessingOfSalvationTrigger : public HasAuraTrigger
    {
    public:
        HasGreaterBlessingOfSalvationTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "greater blessing of salvation") {}
    };

    /// 触发器：当前目标身上拥有指定的增益光环 ID
    class BuffOnTargetTrigger : public Trigger
    {
    public:
        BuffOnTargetTrigger(PlayerbotAI* ai, std::string name, uint32 buffID)
        : Trigger(ai, name, 1)
        , buffID(buffID) {}

        virtual bool IsActive() override;

    protected:
        virtual std::string GetTargetName() override { return "current target"; }

    protected:
        uint32 buffID;
    };

    /// 触发器：当前目标身上存在可被指定驱散类型清除的光环
    class DispelOnTargetTrigger : public Trigger
    {
    public:
        DispelOnTargetTrigger(PlayerbotAI* ai, std::string name, DispelType dispelType, int checkInterval = 1)
        : Trigger(ai, name, checkInterval)
        , dispelType(dispelType) {}

        virtual bool IsActive() override;

    protected:
        virtual std::string GetTargetName() override { return "current target"; }

    private:
        DispelType dispelType;
    };

    /// 触发器：当前目标身上存在可驱散的激怒效果
    class DispelEnrageOnTargetTrigger : public DispelOnTargetTrigger
    {
    public:
        DispelEnrageOnTargetTrigger(PlayerbotAI* ai, std::string name = "dispel enrage") : DispelOnTargetTrigger(ai, name, DISPEL_ENRAGE) {}
    };

    /// 触发器：自身身上存在可驱散的中毒减益
    class HasPoisonDebuffTrigger : public Trigger
    {
    public:
        HasPoisonDebuffTrigger(PlayerbotAI* ai) : Trigger(ai, "has poison debuff", 3) {}

        bool IsActive() override
        {
            return ai->HasAuraToDispel(bot, DISPEL_POISON);
        }
    };

    /// 触发器：RTSC 即时战略控制模式下存在已保存的跳跃目标点
    class RtscJumpTrigger : public Trigger
    {
    public:
        RtscJumpTrigger(PlayerbotAI* ai) : Trigger(ai, "rtsc jump active") {}

        bool IsActive() override;
    };

    /// 触发器：检查声望面板是否存在标记为“交战状态”但尚未敌对的阵营
    class AtWarTrigger : public Trigger
    {
    public:
        AtWarTrigger(PlayerbotAI* ai) : Trigger(ai, "at war", 60) {}

        bool IsActive() override;
    };
}

    /// 触发器：药水冷却计时或指定增益药水就绪触发器
class PotionCooldownTrigger : public ai::ItemBuffReadyTrigger
{
public:
    PotionCooldownTrigger(PlayerbotAI* ai, uint32 itemID = 0, uint32 buffID = 0)
        : ai::ItemBuffReadyTrigger(ai, "potion cooldown", itemID, buffID), lastPotionTime(0), localItemID(itemID), localBuffID(buffID) {}

    virtual bool IsActive() override
    {
        if (localItemID == 0 && localBuffID == 0)
        {
            time_t now = time(0);
            if (now - lastPotionTime >= 120)
            {
                lastPotionTime = now;
                return true;
            }
            return false;
        }

        return ai::ItemBuffReadyTrigger::IsActive();
    }

private:
    time_t lastPotionTime;
    uint32 localItemID;
    uint32 localBuffID;
};

#include "RangeTriggers.h"
#include "HealthTriggers.h"
#include "CureTriggers.h"
