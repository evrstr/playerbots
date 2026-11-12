// 德鲁伊 - 输出野性德鲁伊策略头文件 (DpsFeralDruidStrategy.h)
#pragma once
#include "DruidStrategy.h"

namespace ai
{
    // 输出野性德鲁伊专精占位策略：用于专精识别与占位的策略类
    class DpsFeralDruidPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        DpsFeralDruidPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "dps feral"; }
    };

    // 输出野性德鲁伊策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidStrategy : public DruidStrategy
    {
    public:
        DpsFeralDruidStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    
        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 输出野性德鲁伊PVE策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidPveStrategy : public DpsFeralDruidStrategy
    {
    public:
        DpsFeralDruidPveStrategy(PlayerbotAI* ai) : DpsFeralDruidStrategy(ai) {}
        std::string getName() override { return "dps feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊PVP策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidPvpStrategy : public DpsFeralDruidStrategy
    {
    public:
        DpsFeralDruidPvpStrategy(PlayerbotAI* ai) : DpsFeralDruidStrategy(ai) {}
        std::string getName() override { return "dps feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊团队副本策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidRaidStrategy : public DpsFeralDruidStrategy
    {
    public:
        DpsFeralDruidRaidStrategy(PlayerbotAI* ai) : DpsFeralDruidStrategy(ai) {}
        std::string getName() override { return "dps feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊AOE群体策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidAoeStrategy : public DruidAoeStrategy
    {
    public:
        DpsFeralDruidAoeStrategy(PlayerbotAI* ai) : DruidAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidAoePveStrategy : public DpsFeralDruidAoeStrategy
    {
    public:
        DpsFeralDruidAoePveStrategy(PlayerbotAI* ai) : DpsFeralDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe dps feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidAoePvpStrategy : public DpsFeralDruidAoeStrategy
    {
    public:
        DpsFeralDruidAoePvpStrategy(PlayerbotAI* ai) : DpsFeralDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe dps feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidAoeRaidStrategy : public DpsFeralDruidAoeStrategy
    {
    public:
        DpsFeralDruidAoeRaidStrategy(PlayerbotAI* ai) : DpsFeralDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe dps feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊增益Buff策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBuffStrategy : public DruidBuffStrategy
    {
    public:
        DpsFeralDruidBuffStrategy(PlayerbotAI* ai) : DruidBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBuffPveStrategy : public DpsFeralDruidBuffStrategy
    {
    public:
        DpsFeralDruidBuffPveStrategy(PlayerbotAI* ai) : DpsFeralDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff dps feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBuffPvpStrategy : public DpsFeralDruidBuffStrategy
    {
    public:
        DpsFeralDruidBuffPvpStrategy(PlayerbotAI* ai) : DpsFeralDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff dps feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBuffRaidStrategy : public DpsFeralDruidBuffStrategy
    {
    public:
        DpsFeralDruidBuffRaidStrategy(PlayerbotAI* ai) : DpsFeralDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff dps feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊爆发增益策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBoostStrategy : public DruidBoostStrategy
    {
    public:
        DpsFeralDruidBoostStrategy(PlayerbotAI* ai) : DruidBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBoostPveStrategy : public DpsFeralDruidBoostStrategy
    {
    public:
        DpsFeralDruidBoostPveStrategy(PlayerbotAI* ai) : DpsFeralDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost dps feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBoostPvpStrategy : public DpsFeralDruidBoostStrategy
    {
    public:
        DpsFeralDruidBoostPvpStrategy(PlayerbotAI* ai) : DpsFeralDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost dps feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidBoostRaidStrategy : public DpsFeralDruidBoostStrategy
    {
    public:
        DpsFeralDruidBoostRaidStrategy(PlayerbotAI* ai) : DpsFeralDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost dps feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCcStrategy : public DruidCcStrategy
    {
    public:
        DpsFeralDruidCcStrategy(PlayerbotAI* ai) : DruidCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCcPveStrategy : public DpsFeralDruidCcStrategy
    {
    public:
        DpsFeralDruidCcPveStrategy(PlayerbotAI* ai) : DpsFeralDruidCcStrategy(ai) {}
        std::string getName() override { return "cc dps feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCcPvpStrategy : public DpsFeralDruidCcStrategy
    {
    public:
        DpsFeralDruidCcPvpStrategy(PlayerbotAI* ai) : DpsFeralDruidCcStrategy(ai) {}
        std::string getName() override { return "cc dps feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCcRaidStrategy : public DpsFeralDruidCcStrategy
    {
    public:
        DpsFeralDruidCcRaidStrategy(PlayerbotAI* ai) : DpsFeralDruidCcStrategy(ai) {}
        std::string getName() override { return "cc dps feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊驱散净化策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCureStrategy : public DruidCureStrategy
    {
    public:
        DpsFeralDruidCureStrategy(PlayerbotAI* ai) : DruidCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCurePveStrategy : public DpsFeralDruidCureStrategy
    {
    public:
        DpsFeralDruidCurePveStrategy(PlayerbotAI* ai) : DpsFeralDruidCureStrategy(ai) {}
        std::string getName() override { return "cure dps feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCurePvpStrategy : public DpsFeralDruidCureStrategy
    {
    public:
        DpsFeralDruidCurePvpStrategy(PlayerbotAI* ai) : DpsFeralDruidCureStrategy(ai) {}
        std::string getName() override { return "cure dps feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidCureRaidStrategy : public DpsFeralDruidCureStrategy
    {
    public:
        DpsFeralDruidCureRaidStrategy(PlayerbotAI* ai) : DpsFeralDruidCureStrategy(ai) {}
        std::string getName() override { return "cure dps feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊潜行策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidStealthStrategy : public StealthStrategy
    {
    public:
        DpsFeralDruidStealthStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊潜行PVP策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidStealthPvpStrategy : public DpsFeralDruidStealthStrategy
    {
    public:
        DpsFeralDruidStealthPvpStrategy(PlayerbotAI* ai) : DpsFeralDruidStealthStrategy(ai) {}
        std::string getName() override { return "stealth dps feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊潜行PVE策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidStealthPveStrategy : public DpsFeralDruidStealthStrategy
    {
    public:
        DpsFeralDruidStealthPveStrategy(PlayerbotAI* ai) : DpsFeralDruidStealthStrategy(ai) {}
        std::string getName() override { return "stealth dps feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊潜行团队副本策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidStealthRaidStrategy : public DpsFeralDruidStealthStrategy
    {
    public:
        DpsFeralDruidStealthRaidStrategy(PlayerbotAI* ai) : DpsFeralDruidStealthStrategy(ai) {}
        std::string getName() override { return "stealth dps feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 输出野性德鲁伊潜行状态策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidStealthedStrategy : public StealthedStrategy
    {
    public:
        DpsFeralDruidStealthedStrategy(PlayerbotAI* ai) : StealthedStrategy(ai) {}

    private:
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitNonCombatMultipliers(std::list<Multiplier*>& multipliers) override;
    };

    // 输出野性德鲁伊变身解控策略：定义该专精/场景下的触发器与默认行为
    class DpsFeralDruidPowershiftStrategy : public Strategy
    {
    public:
        DpsFeralDruidPowershiftStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "powershift"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
