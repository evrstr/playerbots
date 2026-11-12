// 牧师 - 神圣牧师策略头文件 (HolyPriestStrategy.h)
#pragma once
#include "PriestStrategy.h"

namespace ai
{
    // 神圣牧师专精占位策略：用于专精识别与占位的策略类
    class HolyPriestPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        HolyPriestPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_HEAL | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "holy"; }
    };

    // 神圣牧师策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestStrategy : public PriestStrategy
    {
    public:
        HolyPriestStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestPveStrategy : public HolyPriestStrategy
    {
    public:
        HolyPriestPveStrategy(PlayerbotAI* ai) : HolyPriestStrategy(ai) {}
        std::string getName() override { return "holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestPvpStrategy : public HolyPriestStrategy
    {
    public:
        HolyPriestPvpStrategy(PlayerbotAI* ai) : HolyPriestStrategy(ai) {}
        std::string getName() override { return "holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestRaidStrategy : public HolyPriestStrategy
    {
    public:
        HolyPriestRaidStrategy(PlayerbotAI* ai) : HolyPriestStrategy(ai) {}
        std::string getName() override { return "holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestAoeStrategy : public PriestAoeStrategy
    {
    public:
        HolyPriestAoeStrategy(PlayerbotAI* ai) : PriestAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestAoePveStrategy : public HolyPriestAoeStrategy
    {
    public:
        HolyPriestAoePveStrategy(PlayerbotAI* ai) : HolyPriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestAoePvpStrategy : public HolyPriestAoeStrategy
    {
    public:
        HolyPriestAoePvpStrategy(PlayerbotAI* ai) : HolyPriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestAoeRaidStrategy : public HolyPriestAoeStrategy
    {
    public:
        HolyPriestAoeRaidStrategy(PlayerbotAI* ai) : HolyPriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBuffStrategy : public PriestBuffStrategy
    {
    public:
        HolyPriestBuffStrategy(PlayerbotAI* ai) : PriestBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBuffPveStrategy : public HolyPriestBuffStrategy
    {
    public:
        HolyPriestBuffPveStrategy(PlayerbotAI* ai) : HolyPriestBuffStrategy(ai) {}
        std::string getName() override { return "buff holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBuffPvpStrategy : public HolyPriestBuffStrategy
    {
    public:
        HolyPriestBuffPvpStrategy(PlayerbotAI* ai) : HolyPriestBuffStrategy(ai) {}
        std::string getName() override { return "buff holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBuffRaidStrategy : public HolyPriestBuffStrategy
    {
    public:
        HolyPriestBuffRaidStrategy(PlayerbotAI* ai) : HolyPriestBuffStrategy(ai) {}
        std::string getName() override { return "buff holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBoostStrategy : public PriestBoostStrategy
    {
    public:
        HolyPriestBoostStrategy(PlayerbotAI* ai) : PriestBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBoostPveStrategy : public HolyPriestBoostStrategy
    {
    public:
        HolyPriestBoostPveStrategy(PlayerbotAI* ai) : HolyPriestBoostStrategy(ai) {}
        std::string getName() override { return "boost holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBoostPvpStrategy : public HolyPriestBoostStrategy
    {
    public:
        HolyPriestBoostPvpStrategy(PlayerbotAI* ai) : HolyPriestBoostStrategy(ai) {}
        std::string getName() override { return "boost holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestBoostRaidStrategy : public HolyPriestBoostStrategy
    {
    public:
        HolyPriestBoostRaidStrategy(PlayerbotAI* ai) : HolyPriestBoostStrategy(ai) {}
        std::string getName() override { return "boost holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCcStrategy : public PriestCcStrategy
    {
    public:
        HolyPriestCcStrategy(PlayerbotAI* ai) : PriestCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCcPveStrategy : public HolyPriestCcStrategy
    {
    public:
        HolyPriestCcPveStrategy(PlayerbotAI* ai) : HolyPriestCcStrategy(ai) {}
        std::string getName() override { return "cc holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCcPvpStrategy : public HolyPriestCcStrategy
    {
    public:
        HolyPriestCcPvpStrategy(PlayerbotAI* ai) : HolyPriestCcStrategy(ai) {}
        std::string getName() override { return "cc holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCcRaidStrategy : public HolyPriestCcStrategy
    {
    public:
        HolyPriestCcRaidStrategy(PlayerbotAI* ai) : HolyPriestCcStrategy(ai) {}
        std::string getName() override { return "cc holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCureStrategy : public PriestCureStrategy
    {
    public:
        HolyPriestCureStrategy(PlayerbotAI* ai) : PriestCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCurePveStrategy : public HolyPriestCureStrategy
    {
    public:
        HolyPriestCurePveStrategy(PlayerbotAI* ai) : HolyPriestCureStrategy(ai) {}
        std::string getName() override { return "cure holy pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCurePvpStrategy : public HolyPriestCureStrategy
    {
    public:
        HolyPriestCurePvpStrategy(PlayerbotAI* ai) : HolyPriestCureStrategy(ai) {}
        std::string getName() override { return "cure holy pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 神圣牧师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class HolyPriestCureRaidStrategy : public HolyPriestCureStrategy
    {
    public:
        HolyPriestCureRaidStrategy(PlayerbotAI* ai) : HolyPriestCureStrategy(ai) {}
        std::string getName() override { return "cure holy raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
