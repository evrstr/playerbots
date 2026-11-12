// 战士 - 狂怒战士策略头文件 (FuryWarriorStrategy.h)
#pragma once
#include "WarriorStrategy.h"

namespace ai
{
    // 狂怒战士专精占位策略：用于专精识别与占位的策略类
    class FuryWarriorPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        FuryWarriorPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "fury"; }
    };

    // 狂怒战士策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorStrategy : public WarriorStrategy
    {
    public:
        FuryWarriorStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 狂怒战士PVE策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorPveStrategy : public FuryWarriorStrategy
    {
    public:
        FuryWarriorPveStrategy(PlayerbotAI* ai) : FuryWarriorStrategy(ai) {}
        std::string getName() override { return "fury pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士PVP策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorPvpStrategy : public FuryWarriorStrategy
    {
    public:
        FuryWarriorPvpStrategy(PlayerbotAI* ai) : FuryWarriorStrategy(ai) {}
        std::string getName() override { return "fury pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士团队副本策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorRaidStrategy : public FuryWarriorStrategy
    {
    public:
        FuryWarriorRaidStrategy(PlayerbotAI* ai) : FuryWarriorStrategy(ai) {}
        std::string getName() override { return "fury raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorAoeStrategy : public WarriorAoeStrategy
    {
    public:
        FuryWarriorAoeStrategy(PlayerbotAI* ai) : WarriorAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorAoePveStrategy : public FuryWarriorAoeStrategy
    {
    public:
        FuryWarriorAoePveStrategy(PlayerbotAI* ai) : FuryWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe fury pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorAoePvpStrategy : public FuryWarriorAoeStrategy
    {
    public:
        FuryWarriorAoePvpStrategy(PlayerbotAI* ai) : FuryWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe fury pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorAoeRaidStrategy : public FuryWarriorAoeStrategy
    {
    public:
        FuryWarriorAoeRaidStrategy(PlayerbotAI* ai) : FuryWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe fury raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBuffStrategy : public WarriorBuffStrategy
    {
    public:
        FuryWarriorBuffStrategy(PlayerbotAI* ai) : WarriorBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBuffPveStrategy : public FuryWarriorBuffStrategy
    {
    public:
        FuryWarriorBuffPveStrategy(PlayerbotAI* ai) : FuryWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff fury pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBuffPvpStrategy : public FuryWarriorBuffStrategy
    {
    public:
        FuryWarriorBuffPvpStrategy(PlayerbotAI* ai) : FuryWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff fury pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBuffRaidStrategy : public FuryWarriorBuffStrategy
    {
    public:
        FuryWarriorBuffRaidStrategy(PlayerbotAI* ai) : FuryWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff fury raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBoostStrategy : public WarriorBoostStrategy
    {
    public:
        FuryWarriorBoostStrategy(PlayerbotAI* ai) : WarriorBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBoostPveStrategy : public FuryWarriorBoostStrategy
    {
    public:
        FuryWarriorBoostPveStrategy(PlayerbotAI* ai) : FuryWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost fury pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBoostPvpStrategy : public FuryWarriorBoostStrategy
    {
    public:
        FuryWarriorBoostPvpStrategy(PlayerbotAI* ai) : FuryWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost fury pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorBoostRaidStrategy : public FuryWarriorBoostStrategy
    {
    public:
        FuryWarriorBoostRaidStrategy(PlayerbotAI* ai) : FuryWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost fury raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorCcStrategy : public WarriorCcStrategy
    {
    public:
        FuryWarriorCcStrategy(PlayerbotAI* ai) : WarriorCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorCcPveStrategy : public FuryWarriorCcStrategy
    {
    public:
        FuryWarriorCcPveStrategy(PlayerbotAI* ai) : FuryWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc fury pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorCcPvpStrategy : public FuryWarriorCcStrategy
    {
    public:
        FuryWarriorCcPvpStrategy(PlayerbotAI* ai) : FuryWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc fury pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 狂怒战士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class FuryWarriorCcRaidStrategy : public FuryWarriorCcStrategy
    {
    public:
        FuryWarriorCcRaidStrategy(PlayerbotAI* ai) : FuryWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc fury raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
