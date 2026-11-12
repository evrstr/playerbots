// 战士 - 武器战士策略头文件 (ArmsWarriorStrategy.h)
#pragma once
#include "WarriorStrategy.h"

namespace ai
{
    // 武器战士专精占位策略：用于专精识别与占位的策略类
    class ArmsWarriorPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ArmsWarriorPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "arms"; }
    };

    // 武器战士策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorStrategy : public WarriorStrategy
    {
    public:
        ArmsWarriorStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 武器战士PVE策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorPveStrategy : public ArmsWarriorStrategy
    {
    public:
        ArmsWarriorPveStrategy(PlayerbotAI* ai) : ArmsWarriorStrategy(ai) {}
        std::string getName() override { return "arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士PVP策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorPvpStrategy : public ArmsWarriorStrategy
    {
    public:
        ArmsWarriorPvpStrategy(PlayerbotAI* ai) : ArmsWarriorStrategy(ai) {}
        std::string getName() override { return "arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorRaidStrategy : public ArmsWarriorStrategy
    {
    public:
        ArmsWarriorRaidStrategy(PlayerbotAI* ai) : ArmsWarriorStrategy(ai) {}
        std::string getName() override { return "arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorAoeStrategy : public WarriorAoeStrategy
    {
    public:
        ArmsWarriorAoeStrategy(PlayerbotAI* ai) : WarriorAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorAoePveStrategy : public ArmsWarriorAoeStrategy
    {
    public:
        ArmsWarriorAoePveStrategy(PlayerbotAI* ai) : ArmsWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorAoePvpStrategy : public ArmsWarriorAoeStrategy
    {
    public:
        ArmsWarriorAoePvpStrategy(PlayerbotAI* ai) : ArmsWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorAoeRaidStrategy : public ArmsWarriorAoeStrategy
    {
    public:
        ArmsWarriorAoeRaidStrategy(PlayerbotAI* ai) : ArmsWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBuffStrategy : public WarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffStrategy(PlayerbotAI* ai) : WarriorBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBuffPveStrategy : public ArmsWarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffPveStrategy(PlayerbotAI* ai) : ArmsWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBuffPvpStrategy : public ArmsWarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffPvpStrategy(PlayerbotAI* ai) : ArmsWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBuffRaidStrategy : public ArmsWarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffRaidStrategy(PlayerbotAI* ai) : ArmsWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBoostStrategy : public WarriorBoostStrategy
    {
    public:
        ArmsWarriorBoostStrategy(PlayerbotAI* ai) : WarriorBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBoostPveStrategy : public ArmsWarriorBoostStrategy
    {
    public:
        ArmsWarriorBoostPveStrategy(PlayerbotAI* ai) : ArmsWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBoostPvpStrategy : public ArmsWarriorBoostStrategy
    {
    public:
        ArmsWarriorBoostPvpStrategy(PlayerbotAI* ai) : ArmsWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorBoostRaidStrategy : public ArmsWarriorBoostStrategy
    {
    public:
        ArmsWarriorBoostRaidStrategy(PlayerbotAI* ai) : ArmsWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorCcStrategy : public WarriorCcStrategy
    {
    public:
        ArmsWarriorCcStrategy(PlayerbotAI* ai) : WarriorCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorCcPveStrategy : public ArmsWarriorCcStrategy
    {
    public:
        ArmsWarriorCcPveStrategy(PlayerbotAI* ai) : ArmsWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorCcPvpStrategy : public ArmsWarriorCcStrategy
    {
    public:
        ArmsWarriorCcPvpStrategy(PlayerbotAI* ai) : ArmsWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 武器战士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArmsWarriorCcRaidStrategy : public ArmsWarriorCcStrategy
    {
    public:
        ArmsWarriorCcRaidStrategy(PlayerbotAI* ai) : ArmsWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
