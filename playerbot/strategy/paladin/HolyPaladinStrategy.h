// 圣骑士 - 神圣圣骑士策略头文件 (HolyPaladinStrategy.h)
#pragma once
#include "PaladinStrategy.h"

namespace ai
{
    // 神圣圣骑士专精占位策略：用于专精识别与占位的策略类
    class HolyPaladinPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        HolyPaladinPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_HEAL | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "holy"; }
    };

    // 神圣圣骑士策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinStrategy : public PaladinStrategy
    {
    public:
        HolyPaladinStrategy(PlayerbotAI* ai) : PaladinStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinPveStrategy : public HolyPaladinStrategy
    {
    public:
        HolyPaladinPveStrategy(PlayerbotAI* ai) : HolyPaladinStrategy(ai) {}
        std::string getName() override { return "holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinPvpStrategy : public HolyPaladinStrategy
    {
    public:
        HolyPaladinPvpStrategy(PlayerbotAI* ai) : HolyPaladinStrategy(ai) {}
        std::string getName() override { return "holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinRaidStrategy : public HolyPaladinStrategy
    {
    public:
        HolyPaladinRaidStrategy(PlayerbotAI* ai) : HolyPaladinStrategy(ai) {}
        std::string getName() override { return "holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAoeStrategy : public PaladinAoeStrategy
    {
    public:
        HolyPaladinAoeStrategy(PlayerbotAI* ai) : PaladinAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAoePveStrategy : public HolyPaladinAoeStrategy
    {
    public:
        HolyPaladinAoePveStrategy(PlayerbotAI* ai) : HolyPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAoePvpStrategy : public HolyPaladinAoeStrategy
    {
    public:
        HolyPaladinAoePvpStrategy(PlayerbotAI* ai) : HolyPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAoeRaidStrategy : public HolyPaladinAoeStrategy
    {
    public:
        HolyPaladinAoeRaidStrategy(PlayerbotAI* ai) : HolyPaladinAoeStrategy(ai) {}
        std::string getName() override { return "aoe holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBuffStrategy : public PaladinBuffStrategy
    {
    public:
        HolyPaladinBuffStrategy(PlayerbotAI* ai) : PaladinBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBuffPveStrategy : public HolyPaladinBuffStrategy
    {
    public:
        HolyPaladinBuffPveStrategy(PlayerbotAI* ai) : HolyPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBuffPvpStrategy : public HolyPaladinBuffStrategy
    {
    public:
        HolyPaladinBuffPvpStrategy(PlayerbotAI* ai) : HolyPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBuffRaidStrategy : public HolyPaladinBuffStrategy
    {
    public:
        HolyPaladinBuffRaidStrategy(PlayerbotAI* ai) : HolyPaladinBuffStrategy(ai) {}
        std::string getName() override { return "buff holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBoostStrategy : public PaladinBoostStrategy
    {
    public:
        HolyPaladinBoostStrategy(PlayerbotAI* ai) : PaladinBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBoostPveStrategy : public HolyPaladinBoostStrategy
    {
    public:
        HolyPaladinBoostPveStrategy(PlayerbotAI* ai) : HolyPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBoostPvpStrategy : public HolyPaladinBoostStrategy
    {
    public:
        HolyPaladinBoostPvpStrategy(PlayerbotAI* ai) : HolyPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBoostRaidStrategy : public HolyPaladinBoostStrategy
    {
    public:
        HolyPaladinBoostRaidStrategy(PlayerbotAI* ai) : HolyPaladinBoostStrategy(ai) {}
        std::string getName() override { return "boost holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCcStrategy : public PaladinCcStrategy
    {
    public:
        HolyPaladinCcStrategy(PlayerbotAI* ai) : PaladinCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCcPveStrategy : public HolyPaladinCcStrategy
    {
    public:
        HolyPaladinCcPveStrategy(PlayerbotAI* ai) : HolyPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCcPvpStrategy : public HolyPaladinCcStrategy
    {
    public:
        HolyPaladinCcPvpStrategy(PlayerbotAI* ai) : HolyPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCcRaidStrategy : public HolyPaladinCcStrategy
    {
    public:
        HolyPaladinCcRaidStrategy(PlayerbotAI* ai) : HolyPaladinCcStrategy(ai) {}
        std::string getName() override { return "cc holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士驱散净化策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCureStrategy : public PaladinCureStrategy
    {
    public:
        HolyPaladinCureStrategy(PlayerbotAI* ai) : PaladinCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCurePveStrategy : public HolyPaladinCureStrategy
    {
    public:
        HolyPaladinCurePveStrategy(PlayerbotAI* ai) : HolyPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCurePvpStrategy : public HolyPaladinCureStrategy
    {
    public:
        HolyPaladinCurePvpStrategy(PlayerbotAI* ai) : HolyPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinCureRaidStrategy : public HolyPaladinCureStrategy
    {
    public:
        HolyPaladinCureRaidStrategy(PlayerbotAI* ai) : HolyPaladinCureStrategy(ai) {}
        std::string getName() override { return "cure holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士光环策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAuraStrategy : public PaladinAuraStrategy
    {
    public:
        HolyPaladinAuraStrategy(PlayerbotAI* ai) : PaladinAuraStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士光环PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAuraPveStrategy : public HolyPaladinAuraStrategy
    {
    public:
        HolyPaladinAuraPveStrategy(PlayerbotAI* ai) : HolyPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士光环PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAuraPvpStrategy : public HolyPaladinAuraStrategy
    {
    public:
        HolyPaladinAuraPvpStrategy(PlayerbotAI* ai) : HolyPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士光环团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinAuraRaidStrategy : public HolyPaladinAuraStrategy
    {
    public:
        HolyPaladinAuraRaidStrategy(PlayerbotAI* ai) : HolyPaladinAuraStrategy(ai) {}
        std::string getName() override { return "aura holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士祝福策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBlessingStrategy : public PaladinBlessingStrategy
    {
    public:
        HolyPaladinBlessingStrategy(PlayerbotAI* ai) : PaladinBlessingStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士祝福PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBlessingPveStrategy : public HolyPaladinBlessingStrategy
    {
    public:
        HolyPaladinBlessingPveStrategy(PlayerbotAI* ai) : HolyPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士祝福PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBlessingPvpStrategy : public HolyPaladinBlessingStrategy
    {
    public:
        HolyPaladinBlessingPvpStrategy(PlayerbotAI* ai) : HolyPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣圣骑士祝福团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPaladinBlessingRaidStrategy : public HolyPaladinBlessingStrategy
    {
    public:
        HolyPaladinBlessingRaidStrategy(PlayerbotAI* ai) : HolyPaladinBlessingStrategy(ai) {}
        std::string getName() override { return "blessing holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
