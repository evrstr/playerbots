// 牧师 - 戒律牧师策略头文件 (DisciplinePriestStrategy.h)
#pragma once
#include "PriestStrategy.h"

namespace ai
{
    // 戒律牧师专精占位策略：用于专精识别与占位的策略类
    class DisciplinePriestPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        DisciplinePriestPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_HEAL | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "discipline"; }
    };

    // 戒律牧师策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestStrategy : public PriestStrategy
    {
    public:
        DisciplinePriestStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师PVE策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestPveStrategy : public DisciplinePriestStrategy
    {
    public:
        DisciplinePriestPveStrategy(PlayerbotAI* ai) : DisciplinePriestStrategy(ai) {}
        std::string getName() override { return "discipline pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师PVP策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestPvpStrategy : public DisciplinePriestStrategy
    {
    public:
        DisciplinePriestPvpStrategy(PlayerbotAI* ai) : DisciplinePriestStrategy(ai) {}
        std::string getName() override { return "discipline pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师团队副本策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestRaidStrategy : public DisciplinePriestStrategy
    {
    public:
        DisciplinePriestRaidStrategy(PlayerbotAI* ai) : DisciplinePriestStrategy(ai) {}
        std::string getName() override { return "discipline raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestAoeStrategy : public PriestAoeStrategy
    {
    public:
        DisciplinePriestAoeStrategy(PlayerbotAI* ai) : PriestAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestAoePveStrategy : public DisciplinePriestAoeStrategy
    {
    public:
        DisciplinePriestAoePveStrategy(PlayerbotAI* ai) : DisciplinePriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe discipline pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestAoePvpStrategy : public DisciplinePriestAoeStrategy
    {
    public:
        DisciplinePriestAoePvpStrategy(PlayerbotAI* ai) : DisciplinePriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe discipline pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestAoeRaidStrategy : public DisciplinePriestAoeStrategy
    {
    public:
        DisciplinePriestAoeRaidStrategy(PlayerbotAI* ai) : DisciplinePriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe discipline raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBuffStrategy : public PriestBuffStrategy
    {
    public:
        DisciplinePriestBuffStrategy(PlayerbotAI* ai) : PriestBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBuffPveStrategy : public DisciplinePriestBuffStrategy
    {
    public:
        DisciplinePriestBuffPveStrategy(PlayerbotAI* ai) : DisciplinePriestBuffStrategy(ai) {}
        std::string getName() override { return "buff discipline pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBuffPvpStrategy : public DisciplinePriestBuffStrategy
    {
    public:
        DisciplinePriestBuffPvpStrategy(PlayerbotAI* ai) : DisciplinePriestBuffStrategy(ai) {}
        std::string getName() override { return "buff discipline pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBuffRaidStrategy : public DisciplinePriestBuffStrategy
    {
    public:
        DisciplinePriestBuffRaidStrategy(PlayerbotAI* ai) : DisciplinePriestBuffStrategy(ai) {}
        std::string getName() override { return "buff discipline raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBoostStrategy : public PriestBoostStrategy
    {
    public:
        DisciplinePriestBoostStrategy(PlayerbotAI* ai) : PriestBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBoostPveStrategy : public DisciplinePriestBoostStrategy
    {
    public:
        DisciplinePriestBoostPveStrategy(PlayerbotAI* ai) : DisciplinePriestBoostStrategy(ai) {}
        std::string getName() override { return "boost discipline pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBoostPvpStrategy : public DisciplinePriestBoostStrategy
    {
    public:
        DisciplinePriestBoostPvpStrategy(PlayerbotAI* ai) : DisciplinePriestBoostStrategy(ai) {}
        std::string getName() override { return "boost discipline pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestBoostRaidStrategy : public DisciplinePriestBoostStrategy
    {
    public:
        DisciplinePriestBoostRaidStrategy(PlayerbotAI* ai) : DisciplinePriestBoostStrategy(ai) {}
        std::string getName() override { return "boost discipline raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCcStrategy : public PriestCcStrategy
    {
    public:
        DisciplinePriestCcStrategy(PlayerbotAI* ai) : PriestCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCcPveStrategy : public DisciplinePriestCcStrategy
    {
    public:
        DisciplinePriestCcPveStrategy(PlayerbotAI* ai) : DisciplinePriestCcStrategy(ai) {}
        std::string getName() override { return "cc discipline pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCcPvpStrategy : public DisciplinePriestCcStrategy
    {
    public:
        DisciplinePriestCcPvpStrategy(PlayerbotAI* ai) : DisciplinePriestCcStrategy(ai) {}
        std::string getName() override { return "cc discipline pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCcRaidStrategy : public DisciplinePriestCcStrategy
    {
    public:
        DisciplinePriestCcRaidStrategy(PlayerbotAI* ai) : DisciplinePriestCcStrategy(ai) {}
        std::string getName() override { return "cc discipline raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCureStrategy : public PriestCureStrategy
    {
    public:
        DisciplinePriestCureStrategy(PlayerbotAI* ai) : PriestCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCurePveStrategy : public DisciplinePriestCureStrategy
    {
    public:
        DisciplinePriestCurePveStrategy(PlayerbotAI* ai) : DisciplinePriestCureStrategy(ai) {}
        std::string getName() override { return "cure discipline pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCurePvpStrategy : public DisciplinePriestCureStrategy
    {
    public:
        DisciplinePriestCurePvpStrategy(PlayerbotAI* ai) : DisciplinePriestCureStrategy(ai) {}
        std::string getName() override { return "cure discipline pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 戒律牧师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class DisciplinePriestCureRaidStrategy : public DisciplinePriestCureStrategy
    {
    public:
        DisciplinePriestCureRaidStrategy(PlayerbotAI* ai) : DisciplinePriestCureStrategy(ai) {}
        std::string getName() override { return "cure discipline raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
