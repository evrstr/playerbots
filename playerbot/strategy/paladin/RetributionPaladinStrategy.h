// 圣骑士 - 惩戒圣骑士策略头文件 (RetributionPaladinStrategy.h)
#pragma once
#include "PaladinStrategy.h"

namespace ai
{
    // 惩戒圣骑士专精占位策略：用于专精识别与占位的策略类
    class RetributionPaladinPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        RetributionPaladinPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "retribution"; }
    };

    // 惩戒圣骑士策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinStrategy : public PaladinStrategy
    {
    public:
        RetributionPaladinStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 惩戒圣骑士PVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinPveStrategy : public RetributionPaladinStrategy
    {
    public:
        RetributionPaladinPveStrategy(PlayerbotAI* ai) : RetributionPaladinStrategy(ai) {}
        std::string getName() override { return "retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士PVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinPvpStrategy : public RetributionPaladinStrategy
    {
    public:
        RetributionPaladinPvpStrategy(PlayerbotAI* ai) : RetributionPaladinStrategy(ai) {}
        std::string getName() override { return "retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinRaidStrategy : public RetributionPaladinStrategy
    {
    public:
        RetributionPaladinRaidStrategy(PlayerbotAI* ai) : RetributionPaladinStrategy(ai) {}
        std::string getName() override { return "retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAoeStrategy : public PaladinAoeStrategy
    {
    public:
        RetributionPaladinAoeStrategy(PlayerbotAI* ai) : PaladinAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAoePveStrategy : public RetributionPaladinAoeStrategy
    {
    public:
        RetributionPaladinAoePveStrategy(PlayerbotAI* ai) : RetributionPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAoePvpStrategy : public RetributionPaladinAoeStrategy
    {
    public:
        RetributionPaladinAoePvpStrategy(PlayerbotAI* ai) : RetributionPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAoeRaidStrategy : public RetributionPaladinAoeStrategy
    {
    public:
        RetributionPaladinAoeRaidStrategy(PlayerbotAI* ai) : RetributionPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBuffStrategy : public PaladinBuffStrategy
    {
    public:
        RetributionPaladinBuffStrategy(PlayerbotAI* ai) : PaladinBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBuffPveStrategy : public RetributionPaladinBuffStrategy
    {
    public:
        RetributionPaladinBuffPveStrategy(PlayerbotAI* ai) : RetributionPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBuffPvpStrategy : public RetributionPaladinBuffStrategy
    {
    public:
        RetributionPaladinBuffPvpStrategy(PlayerbotAI* ai) : RetributionPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBuffRaidStrategy : public RetributionPaladinBuffStrategy
    {
    public:
        RetributionPaladinBuffRaidStrategy(PlayerbotAI* ai) : RetributionPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBoostStrategy : public PaladinBoostStrategy
    {
    public:
        RetributionPaladinBoostStrategy(PlayerbotAI* ai) : PaladinBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBoostPveStrategy : public RetributionPaladinBoostStrategy
    {
    public:
        RetributionPaladinBoostPveStrategy(PlayerbotAI* ai) : RetributionPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBoostPvpStrategy : public RetributionPaladinBoostStrategy
    {
    public:
        RetributionPaladinBoostPvpStrategy(PlayerbotAI* ai) : RetributionPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBoostRaidStrategy : public RetributionPaladinBoostStrategy
    {
    public:
        RetributionPaladinBoostRaidStrategy(PlayerbotAI* ai) : RetributionPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCcStrategy : public PaladinCcStrategy
    {
    public:
        RetributionPaladinCcStrategy(PlayerbotAI* ai) : PaladinCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCcPveStrategy : public RetributionPaladinCcStrategy
    {
    public:
        RetributionPaladinCcPveStrategy(PlayerbotAI* ai) : RetributionPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCcPvpStrategy : public RetributionPaladinCcStrategy
    {
    public:
        RetributionPaladinCcPvpStrategy(PlayerbotAI* ai) : RetributionPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCcRaidStrategy : public RetributionPaladinCcStrategy
    {
    public:
        RetributionPaladinCcRaidStrategy(PlayerbotAI* ai) : RetributionPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士驱散净化策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCureStrategy : public PaladinCureStrategy
    {
    public:
        RetributionPaladinCureStrategy(PlayerbotAI* ai) : PaladinCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCurePveStrategy : public RetributionPaladinCureStrategy
    {
    public:
        RetributionPaladinCurePveStrategy(PlayerbotAI* ai) : RetributionPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCurePvpStrategy : public RetributionPaladinCureStrategy
    {
    public:
        RetributionPaladinCurePvpStrategy(PlayerbotAI* ai) : RetributionPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinCureRaidStrategy : public RetributionPaladinCureStrategy
    {
    public:
        RetributionPaladinCureRaidStrategy(PlayerbotAI* ai) : RetributionPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士光环策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAuraStrategy : public PaladinAuraStrategy
    {
    public:
        RetributionPaladinAuraStrategy(PlayerbotAI* ai) : PaladinAuraStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士光环PVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAuraPveStrategy : public RetributionPaladinAuraStrategy
    {
    public:
        RetributionPaladinAuraPveStrategy(PlayerbotAI* ai) : RetributionPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士光环PVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAuraPvpStrategy : public RetributionPaladinAuraStrategy
    {
    public:
        RetributionPaladinAuraPvpStrategy(PlayerbotAI* ai) : RetributionPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士光环团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinAuraRaidStrategy : public RetributionPaladinAuraStrategy
    {
    public:
        RetributionPaladinAuraRaidStrategy(PlayerbotAI* ai) : RetributionPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士祝福策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBlessingStrategy : public PaladinBlessingStrategy
    {
    public:
        RetributionPaladinBlessingStrategy(PlayerbotAI* ai) : PaladinBlessingStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士祝福PVE策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBlessingPveStrategy : public RetributionPaladinBlessingStrategy
    {
    public:
        RetributionPaladinBlessingPveStrategy(PlayerbotAI* ai) : RetributionPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing retribution pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士祝福PVP策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBlessingPvpStrategy : public RetributionPaladinBlessingStrategy
    {
    public:
        RetributionPaladinBlessingPvpStrategy(PlayerbotAI* ai) : RetributionPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing retribution pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 惩戒圣骑士祝福团队副本策略：定义该专精/场景下的触发器与默认行为
    class RetributionPaladinBlessingRaidStrategy : public RetributionPaladinBlessingStrategy
    {
    public:
        RetributionPaladinBlessingRaidStrategy(PlayerbotAI* ai) : RetributionPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing retribution raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
