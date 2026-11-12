// 战士 - 防护战士策略头文件 (ProtectionWarriorStrategy.h)
#pragma once
#include "WarriorStrategy.h"

namespace ai
{
    // 防护战士专精占位策略：用于专精识别与占位的策略类
    class ProtectionWarriorPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ProtectionWarriorPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_TANK | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "protection"; }
    };

    // 防护战士策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorStrategy : public WarriorStrategy
    {
    public:
        ProtectionWarriorStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 防护战士PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorPveStrategy : public ProtectionWarriorStrategy
    {
    public:
        ProtectionWarriorPveStrategy(PlayerbotAI* ai) : ProtectionWarriorStrategy(ai) {}
        std::string getName() override { return "protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorPvpStrategy : public ProtectionWarriorStrategy
    {
    public:
        ProtectionWarriorPvpStrategy(PlayerbotAI* ai) : ProtectionWarriorStrategy(ai) {}
        std::string getName() override { return "protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorRaidStrategy : public ProtectionWarriorStrategy
    {
    public:
        ProtectionWarriorRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorStrategy(ai) {}
        std::string getName() override { return "protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorAoeStrategy : public WarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoeStrategy(PlayerbotAI* ai) : WarriorAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorAoePveStrategy : public ProtectionWarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoePveStrategy(PlayerbotAI* ai) : ProtectionWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorAoePvpStrategy : public ProtectionWarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoePvpStrategy(PlayerbotAI* ai) : ProtectionWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorAoeRaidStrategy : public ProtectionWarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoeRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorAoeStrategy(ai) {}
        std::string getName() override { return "aoe protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBuffStrategy : public WarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffStrategy(PlayerbotAI* ai) : WarriorBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBuffPveStrategy : public ProtectionWarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffPveStrategy(PlayerbotAI* ai) : ProtectionWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBuffPvpStrategy : public ProtectionWarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffPvpStrategy(PlayerbotAI* ai) : ProtectionWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBuffRaidStrategy : public ProtectionWarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorBuffStrategy(ai) {}
        std::string getName() override { return "buff protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBoostStrategy : public WarriorBoostStrategy
    {
    public:
        ProtectionWarriorBoostStrategy(PlayerbotAI* ai) : WarriorBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBoostPveStrategy : public ProtectionWarriorBoostStrategy
    {
    public:
        ProtectionWarriorBoostPveStrategy(PlayerbotAI* ai) : ProtectionWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBoostPvpStrategy : public ProtectionWarriorBoostStrategy
    {
    public:
        ProtectionWarriorBoostPvpStrategy(PlayerbotAI* ai) : ProtectionWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorBoostRaidStrategy : public ProtectionWarriorBoostStrategy
    {
    public:
        ProtectionWarriorBoostRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorBoostStrategy(ai) {}
        std::string getName() override { return "boost protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorCcStrategy : public WarriorCcStrategy
    {
    public:
        ProtectionWarriorCcStrategy(PlayerbotAI* ai) : WarriorCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorCcPveStrategy : public ProtectionWarriorCcStrategy
    {
    public:
        ProtectionWarriorCcPveStrategy(PlayerbotAI* ai) : ProtectionWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorCcPvpStrategy : public ProtectionWarriorCcStrategy
    {
    public:
        ProtectionWarriorCcPvpStrategy(PlayerbotAI* ai) : ProtectionWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 防护战士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class ProtectionWarriorCcRaidStrategy : public ProtectionWarriorCcStrategy
    {
    public:
        ProtectionWarriorCcRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorCcStrategy(ai) {}
        std::string getName() override { return "cc protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
