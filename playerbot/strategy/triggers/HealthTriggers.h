/// 生命值区间与治疗状态触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    /// 触发器基类：判断目标数值是否落在 [minValue, maxValue) 区间内
    class ValueInRangeTrigger : public Trigger
    {
    public:
        ValueInRangeTrigger(PlayerbotAI* ai, std::string name, float maxValue, float minValue) : Trigger(ai, name) 
        {
            this->maxValue = maxValue;
            this->minValue = minValue;
        }

    public:
        virtual float GetValue() = 0;

        virtual bool IsActive() override
        {
            float value = GetValue();
            return value < maxValue && value >= minValue;
        }

    protected:
        float maxValue, minValue;
    };

    /// 触发器基类：检测指定目标的生命值百分比区间（支持预治疗伤害预测）
    class HealthInRangeTrigger : public ValueInRangeTrigger
    {
    public:
        HealthInRangeTrigger(PlayerbotAI* ai, std::string name, float maxValue, float minValue = 0, bool isTankRequired = false) : ValueInRangeTrigger(ai, name, maxValue, minValue) 
        {
            this->isTankRequired = isTankRequired;
        }

        bool IsActive() override;
        float GetValue() override;

    protected:
        bool isTankRequired;
    };

    /// 触发器：自身低生命值
    class LowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        LowHealthTrigger(PlayerbotAI* ai, std::string name = "low health",
            float value = sPlayerbotAIConfig.lowHealth, float minValue = sPlayerbotAIConfig.criticalHealth) :
            HealthInRangeTrigger(ai, name, value, minValue) {}

        virtual std::string GetTargetName() override { return "self target"; }
    };

    /// 触发器：自身危急生命值
    class CriticalHealthTrigger : public LowHealthTrigger
    {
    public:
        CriticalHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "critical health", sPlayerbotAIConfig.criticalHealth, 0) {}
    };

    /// 触发器：自身中等生命值
    class MediumHealthTrigger : public LowHealthTrigger
    {
    public:
        MediumHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "medium health", sPlayerbotAIConfig.mediumHealth, sPlayerbotAIConfig.lowHealth) {}
    };

    /// 触发器：自身接近满血
    class AlmostFullHealthTrigger : public LowHealthTrigger
    {
    public:
        AlmostFullHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "almost full health", sPlayerbotAIConfig.almostFullHealth, sPlayerbotAIConfig.mediumHealth) {}
    };

    /// 触发器：小队成员低生命值
    class PartyMemberLowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        PartyMemberLowHealthTrigger(PlayerbotAI* ai, std::string name = "party member low health", float value = sPlayerbotAIConfig.lowHealth, float minValue = sPlayerbotAIConfig.criticalHealth, bool isTankRequired = false) :
            HealthInRangeTrigger(ai, name, value, minValue, isTankRequired) {}

        virtual std::string GetTargetName() override { return "party member to heal"; }
    };

    /// 触发器：小队成员危急生命值
    class PartyMemberCriticalHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberCriticalHealthTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member critical health", sPlayerbotAIConfig.criticalHealth, 0) {}
    };

    /// 触发器：小队成员中等生命值
    class PartyMemberMediumHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberMediumHealthTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member medium health", sPlayerbotAIConfig.mediumHealth,sPlayerbotAIConfig.lowHealth) {}
    };

    /// 触发器：小队成员接近满血
    class PartyMemberAlmostFullHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberAlmostFullHealthTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member almost full health", sPlayerbotAIConfig.almostFullHealth,sPlayerbotAIConfig.mediumHealth) {}
    };

    /// 触发器：当前目标低生命值
    class TargetLowHealthTrigger : public HealthInRangeTrigger 
    {
    public:
        TargetLowHealthTrigger(PlayerbotAI* ai, float value, float minValue = 0) : HealthInRangeTrigger(ai, "target low health", value, minValue) {}
        virtual std::string GetTargetName() override { return "current target"; }
    };

    /// 触发器：当前目标危急生命值（< 20%）
    class TargetCriticalHealthTrigger : public TargetLowHealthTrigger
    {
    public:
        TargetCriticalHealthTrigger(PlayerbotAI* ai) : TargetLowHealthTrigger(ai, 20) {}
    };

    /// 触发器：存在需要复活的死亡队友
    class PartyMemberDeadTrigger : public Trigger 
    {
    public:
        PartyMemberDeadTrigger(PlayerbotAI* ai) : Trigger(ai, "resurrect", 3) {}
        virtual std::string GetTargetName() override { return "party member to resurrect"; }
        virtual bool IsActive() override;
    };

    /// 触发器：机器人自身已死亡
    class DeadTrigger : public Trigger 
    {
    public:
        DeadTrigger(PlayerbotAI* ai) : Trigger(ai, "dead") {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool IsActive() override;
    };

    /// 触发器：满足群体治疗（AoE Heal）人数阈值
    class AoeHealTrigger : public Trigger 
    {
    public:
        AoeHealTrigger(PlayerbotAI* ai, std::string name, std::string type, int count) :
            Trigger(ai, name), type(type), count(count) {}
    public:
        virtual bool IsActive() override;

    protected:
        int count;
        std::string type;
    };

    /// 触发器：当前治疗法术的目标已满血或过量治疗过高，应中断施法
    class HealTargetFullHealthTrigger : public Trigger
    {
    public:
        HealTargetFullHealthTrigger(PlayerbotAI* ai, std::string name = "heal target full health") : Trigger(ai, name) {}
        bool IsActive() override;
    };
}
