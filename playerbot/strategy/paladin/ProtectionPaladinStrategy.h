// 圣骑士 - 防护圣骑士策略头文件 (ProtectionPaladinStrategy.h)
#pragma once
#include "PaladinStrategy.h"

namespace ai
{
    // 防护圣骑士专精占位策略：用于专精识别与占位的策略类
    class ProtectionPaladinPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ProtectionPaladinPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_TANK | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "protection"; }
    };

    // 防护圣骑士策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinStrategy : public PaladinStrategy
    {
    public:
        ProtectionPaladinStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 防护圣骑士PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinPveStrategy : public ProtectionPaladinStrategy
    {
    public:
        ProtectionPaladinPveStrategy(PlayerbotAI* ai) : ProtectionPaladinStrategy(ai) {}
        std::string getName() override { return "protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinPvpStrategy : public ProtectionPaladinStrategy
    {
    public:
        ProtectionPaladinPvpStrategy(PlayerbotAI* ai) : ProtectionPaladinStrategy(ai) {}
        std::string getName() override { return "protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinRaidStrategy : public ProtectionPaladinStrategy
    {
    public:
        ProtectionPaladinRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinStrategy(ai) {}
        std::string getName() override { return "protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAoeStrategy : public PaladinAoeStrategy
    {
    public:
        ProtectionPaladinAoeStrategy(PlayerbotAI* ai) : PaladinAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAoePveStrategy : public ProtectionPaladinAoeStrategy
    {
    public:
        ProtectionPaladinAoePveStrategy(PlayerbotAI* ai) : ProtectionPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAoePvpStrategy : public ProtectionPaladinAoeStrategy
    {
    public:
        ProtectionPaladinAoePvpStrategy(PlayerbotAI* ai) : ProtectionPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAoeRaidStrategy : public ProtectionPaladinAoeStrategy
    {
    public:
        ProtectionPaladinAoeRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBuffStrategy : public PaladinBuffStrategy
    {
    public:
        ProtectionPaladinBuffStrategy(PlayerbotAI* ai) : PaladinBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBuffPveStrategy : public ProtectionPaladinBuffStrategy
    {
    public:
        ProtectionPaladinBuffPveStrategy(PlayerbotAI* ai) : ProtectionPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBuffPvpStrategy : public ProtectionPaladinBuffStrategy
    {
    public:
        ProtectionPaladinBuffPvpStrategy(PlayerbotAI* ai) : ProtectionPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBuffRaidStrategy : public ProtectionPaladinBuffStrategy
    {
    public:
        ProtectionPaladinBuffRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBoostStrategy : public PaladinBoostStrategy
    {
    public:
        ProtectionPaladinBoostStrategy(PlayerbotAI* ai) : PaladinBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBoostPveStrategy : public ProtectionPaladinBoostStrategy
    {
    public:
        ProtectionPaladinBoostPveStrategy(PlayerbotAI* ai) : ProtectionPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBoostPvpStrategy : public ProtectionPaladinBoostStrategy
    {
    public:
        ProtectionPaladinBoostPvpStrategy(PlayerbotAI* ai) : ProtectionPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBoostRaidStrategy : public ProtectionPaladinBoostStrategy
    {
    public:
        ProtectionPaladinBoostRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCcStrategy : public PaladinCcStrategy
    {
    public:
        ProtectionPaladinCcStrategy(PlayerbotAI* ai) : PaladinCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCcPveStrategy : public ProtectionPaladinCcStrategy
    {
    public:
        ProtectionPaladinCcPveStrategy(PlayerbotAI* ai) : ProtectionPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCcPvpStrategy : public ProtectionPaladinCcStrategy
    {
    public:
        ProtectionPaladinCcPvpStrategy(PlayerbotAI* ai) : ProtectionPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCcRaidStrategy : public ProtectionPaladinCcStrategy
    {
    public:
        ProtectionPaladinCcRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士驱散净化策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCureStrategy : public PaladinCureStrategy
    {
    public:
        ProtectionPaladinCureStrategy(PlayerbotAI* ai) : PaladinCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCurePveStrategy : public ProtectionPaladinCureStrategy
    {
    public:
        ProtectionPaladinCurePveStrategy(PlayerbotAI* ai) : ProtectionPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCurePvpStrategy : public ProtectionPaladinCureStrategy
    {
    public:
        ProtectionPaladinCurePvpStrategy(PlayerbotAI* ai) : ProtectionPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinCureRaidStrategy : public ProtectionPaladinCureStrategy
    {
    public:
        ProtectionPaladinCureRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士光环策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAuraStrategy : public PaladinAuraStrategy
    {
    public:
        ProtectionPaladinAuraStrategy(PlayerbotAI* ai) : PaladinAuraStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士光环PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAuraPveStrategy : public ProtectionPaladinAuraStrategy
    {
    public:
        ProtectionPaladinAuraPveStrategy(PlayerbotAI* ai) : ProtectionPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士光环PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAuraPvpStrategy : public ProtectionPaladinAuraStrategy
    {
    public:
        ProtectionPaladinAuraPvpStrategy(PlayerbotAI* ai) : ProtectionPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士光环团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinAuraRaidStrategy : public ProtectionPaladinAuraStrategy
    {
    public:
        ProtectionPaladinAuraRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士祝福策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBlessingStrategy : public PaladinBlessingStrategy
    {
    public:
        ProtectionPaladinBlessingStrategy(PlayerbotAI* ai) : PaladinBlessingStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士祝福PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBlessingPveStrategy : public ProtectionPaladinBlessingStrategy
    {
    public:
        ProtectionPaladinBlessingPveStrategy(PlayerbotAI* ai) : ProtectionPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士祝福PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBlessingPvpStrategy : public ProtectionPaladinBlessingStrategy
    {
    public:
        ProtectionPaladinBlessingPvpStrategy(PlayerbotAI* ai) : ProtectionPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护圣骑士祝福团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionPaladinBlessingRaidStrategy : public ProtectionPaladinBlessingStrategy
    {
    public:
        ProtectionPaladinBlessingRaidStrategy(PlayerbotAI* ai) : ProtectionPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
