/// 驱散与世界增益触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    class SpellTrigger;

    /// 触发器：自身需要特定类型驱散（中毒/疾病/诅咒/魔法等）
    class NeedCureTrigger : public SpellTrigger 
    {
    public:
        NeedCureTrigger(PlayerbotAI* ai, std::string spell, uint32 dispelType, int checkInterval = 3) : SpellTrigger(ai, spell, checkInterval), dispelType(dispelType) {}
        virtual std::string GetTargetName() override { return "self target"; }
        virtual bool IsActive() override;

    protected:
        uint32 dispelType;
    };

    /// 触发器：当前目标需要净化/驱散敌方增益
    class TargetAuraDispelTrigger : public NeedCureTrigger 
    {
    public:
        TargetAuraDispelTrigger(PlayerbotAI* ai, std::string spell, uint32 dispelType, int checkInterval = 3) : NeedCureTrigger(ai, spell, dispelType, checkInterval) {}
        virtual std::string GetTargetName() override { return "current target"; }
    };

    /// 触发器：小队成员需要驱散负面效果
    class PartyMemberNeedCureTrigger : public NeedCureTrigger 
    {
    public:
        PartyMemberNeedCureTrigger(PlayerbotAI* ai, std::string spell, uint32 dispelType) : NeedCureTrigger(ai, spell, dispelType) {}
        virtual Value<ObjectGuid>* GetTargetValue() override;
    };

    /// 触发器：缺少世界增益（World Buff）
    class NeedWorldBuffTrigger : public Trigger 
    {
    public:
        NeedWorldBuffTrigger(PlayerbotAI* ai) : Trigger(ai, "need world buff", 5) {}
        virtual bool IsActive() override;
    };
}