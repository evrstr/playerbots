// 德鲁伊 - 平衡德鲁伊策略头文件 (BalanceDruidStrategy.h)
#pragma once
#include "DruidStrategy.h"

namespace ai
{
    // 平衡德鲁伊专精占位策略：用于专精识别与占位的策略类
    class BalanceDruidPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        BalanceDruidPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "balance"; }
    };

    // 平衡德鲁伊策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidStrategy : public DruidStrategy
    {
    public:
        BalanceDruidStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    
        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 平衡德鲁伊PVE策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidPveStrategy : public BalanceDruidStrategy
    {
    public:
        BalanceDruidPveStrategy(PlayerbotAI* ai) : BalanceDruidStrategy(ai) {}
        std::string getName() override { return "balance pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊PVP策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidPvpStrategy : public BalanceDruidStrategy
    {
    public:
        BalanceDruidPvpStrategy(PlayerbotAI* ai) : BalanceDruidStrategy(ai) {}
        std::string getName() override { return "balance pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊团队副本策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidRaidStrategy : public BalanceDruidStrategy
    {
    public:
        BalanceDruidRaidStrategy(PlayerbotAI* ai) : BalanceDruidStrategy(ai) {}
        std::string getName() override { return "balance raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        NextAction** GetDefaultCombatActions() override;
    };

    // 平衡德鲁伊AOE群体策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidAoeStrategy : public DruidAoeStrategy
    {
    public:
        BalanceDruidAoeStrategy(PlayerbotAI* ai) : DruidAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidAoePveStrategy : public BalanceDruidAoeStrategy
    {
    public:
        BalanceDruidAoePveStrategy(PlayerbotAI* ai) : BalanceDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe balance pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidAoePvpStrategy : public BalanceDruidAoeStrategy
    {
    public:
        BalanceDruidAoePvpStrategy(PlayerbotAI* ai) : BalanceDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe balance pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidAoeRaidStrategy : public BalanceDruidAoeStrategy
    {
    public:
        BalanceDruidAoeRaidStrategy(PlayerbotAI* ai) : BalanceDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe balance raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊增益Buff策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBuffStrategy : public DruidBuffStrategy
    {
    public:
        BalanceDruidBuffStrategy(PlayerbotAI* ai) : DruidBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBuffPveStrategy : public BalanceDruidBuffStrategy
    {
    public:
        BalanceDruidBuffPveStrategy(PlayerbotAI* ai) : BalanceDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff balance pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBuffPvpStrategy : public BalanceDruidBuffStrategy
    {
    public:
        BalanceDruidBuffPvpStrategy(PlayerbotAI* ai) : BalanceDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff balance pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBuffRaidStrategy : public BalanceDruidBuffStrategy
    {
    public:
        BalanceDruidBuffRaidStrategy(PlayerbotAI* ai) : BalanceDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff balance raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊爆发增益策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBoostStrategy : public DruidBoostStrategy
    {
    public:
        BalanceDruidBoostStrategy(PlayerbotAI* ai) : DruidBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBoostPveStrategy : public BalanceDruidBoostStrategy
    {
    public:
        BalanceDruidBoostPveStrategy(PlayerbotAI* ai) : BalanceDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost balance pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBoostPvpStrategy : public BalanceDruidBoostStrategy
    {
    public:
        BalanceDruidBoostPvpStrategy(PlayerbotAI* ai) : BalanceDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost balance pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidBoostRaidStrategy : public BalanceDruidBoostStrategy
    {
    public:
        BalanceDruidBoostRaidStrategy(PlayerbotAI* ai) : BalanceDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost balance raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCcStrategy : public DruidCcStrategy
    {
    public:
        BalanceDruidCcStrategy(PlayerbotAI* ai) : DruidCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCcPveStrategy : public BalanceDruidCcStrategy
    {
    public:
        BalanceDruidCcPveStrategy(PlayerbotAI* ai) : BalanceDruidCcStrategy(ai) {}
        std::string getName() override { return "cc balance pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCcPvpStrategy : public BalanceDruidCcStrategy
    {
    public:
        BalanceDruidCcPvpStrategy(PlayerbotAI* ai) : BalanceDruidCcStrategy(ai) {}
        std::string getName() override { return "cc balance pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCcRaidStrategy : public BalanceDruidCcStrategy
    {
    public:
        BalanceDruidCcRaidStrategy(PlayerbotAI* ai) : BalanceDruidCcStrategy(ai) {}
        std::string getName() override { return "cc balance raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊驱散净化策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCureStrategy : public DruidCureStrategy
    {
    public:
        BalanceDruidCureStrategy(PlayerbotAI* ai) : DruidCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCurePveStrategy : public BalanceDruidCureStrategy
    {
    public:
        BalanceDruidCurePveStrategy(PlayerbotAI* ai) : BalanceDruidCureStrategy(ai) {}
        std::string getName() override { return "cure balance pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCurePvpStrategy : public BalanceDruidCureStrategy
    {
    public:
        BalanceDruidCurePvpStrategy(PlayerbotAI* ai) : BalanceDruidCureStrategy(ai) {}
        std::string getName() override { return "cure balance pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 平衡德鲁伊驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class BalanceDruidCureRaidStrategy : public BalanceDruidCureStrategy
    {
    public:
        BalanceDruidCureRaidStrategy(PlayerbotAI* ai) : BalanceDruidCureStrategy(ai) {}
        std::string getName() override { return "cure balance raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
