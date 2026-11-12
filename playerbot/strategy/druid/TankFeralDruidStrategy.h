// 德鲁伊 - 坦克野性德鲁伊策略头文件 (TankFeralDruidStrategy.h)
#pragma once
#include "DruidStrategy.h"

namespace ai
{
    // 坦克野性德鲁伊专精占位策略：用于专精识别与占位的策略类
    class TankFeralDruidPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        TankFeralDruidPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_TANK | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "tank feral"; }
    };

    // 坦克野性德鲁伊策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidStrategy : public DruidStrategy
    {
    public:
        TankFeralDruidStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    
        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 坦克野性德鲁伊PVE策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidPveStrategy : public TankFeralDruidStrategy
    {
    public:
        TankFeralDruidPveStrategy(PlayerbotAI* ai) : TankFeralDruidStrategy(ai) {}
        std::string getName() override { return "tank feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊PVP策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidPvpStrategy : public TankFeralDruidStrategy
    {
    public:
        TankFeralDruidPvpStrategy(PlayerbotAI* ai) : TankFeralDruidStrategy(ai) {}
        std::string getName() override { return "tank feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊团队副本策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidRaidStrategy : public TankFeralDruidStrategy
    {
    public:
        TankFeralDruidRaidStrategy(PlayerbotAI* ai) : TankFeralDruidStrategy(ai) {}
        std::string getName() override { return "tank feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊AOE群体策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidAoeStrategy : public DruidAoeStrategy
    {
    public:
        TankFeralDruidAoeStrategy(PlayerbotAI* ai) : DruidAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidAoePveStrategy : public TankFeralDruidAoeStrategy
    {
    public:
        TankFeralDruidAoePveStrategy(PlayerbotAI* ai) : TankFeralDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe tank feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidAoePvpStrategy : public TankFeralDruidAoeStrategy
    {
    public:
        TankFeralDruidAoePvpStrategy(PlayerbotAI* ai) : TankFeralDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe tank feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidAoeRaidStrategy : public TankFeralDruidAoeStrategy
    {
    public:
        TankFeralDruidAoeRaidStrategy(PlayerbotAI* ai) : TankFeralDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe tank feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊增益Buff策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBuffStrategy : public DruidBuffStrategy
    {
    public:
        TankFeralDruidBuffStrategy(PlayerbotAI* ai) : DruidBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBuffPveStrategy : public TankFeralDruidBuffStrategy
    {
    public:
        TankFeralDruidBuffPveStrategy(PlayerbotAI* ai) : TankFeralDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff tank feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBuffPvpStrategy : public TankFeralDruidBuffStrategy
    {
    public:
        TankFeralDruidBuffPvpStrategy(PlayerbotAI* ai) : TankFeralDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff tank feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBuffRaidStrategy : public TankFeralDruidBuffStrategy
    {
    public:
        TankFeralDruidBuffRaidStrategy(PlayerbotAI* ai) : TankFeralDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff tank feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊爆发增益策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBoostStrategy : public DruidBoostStrategy
    {
    public:
        TankFeralDruidBoostStrategy(PlayerbotAI* ai) : DruidBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBoostPveStrategy : public TankFeralDruidBoostStrategy
    {
    public:
        TankFeralDruidBoostPveStrategy(PlayerbotAI* ai) : TankFeralDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost tank feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBoostPvpStrategy : public TankFeralDruidBoostStrategy
    {
    public:
        TankFeralDruidBoostPvpStrategy(PlayerbotAI* ai) : TankFeralDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost tank feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidBoostRaidStrategy : public TankFeralDruidBoostStrategy
    {
    public:
        TankFeralDruidBoostRaidStrategy(PlayerbotAI* ai) : TankFeralDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost tank feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCcStrategy : public DruidCcStrategy
    {
    public:
        TankFeralDruidCcStrategy(PlayerbotAI* ai) : DruidCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCcPveStrategy : public TankFeralDruidCcStrategy
    {
    public:
        TankFeralDruidCcPveStrategy(PlayerbotAI* ai) : TankFeralDruidCcStrategy(ai) {}
        std::string getName() override { return "cc tank feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCcPvpStrategy : public TankFeralDruidCcStrategy
    {
    public:
        TankFeralDruidCcPvpStrategy(PlayerbotAI* ai) : TankFeralDruidCcStrategy(ai) {}
        std::string getName() override { return "cc tank feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCcRaidStrategy : public TankFeralDruidCcStrategy
    {
    public:
        TankFeralDruidCcRaidStrategy(PlayerbotAI* ai) : TankFeralDruidCcStrategy(ai) {}
        std::string getName() override { return "cc tank feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊驱散净化策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCureStrategy : public DruidCureStrategy
    {
    public:
        TankFeralDruidCureStrategy(PlayerbotAI* ai) : DruidCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCurePveStrategy : public TankFeralDruidCureStrategy
    {
    public:
        TankFeralDruidCurePveStrategy(PlayerbotAI* ai) : TankFeralDruidCureStrategy(ai) {}
        std::string getName() override { return "cure tank feral pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCurePvpStrategy : public TankFeralDruidCureStrategy
    {
    public:
        TankFeralDruidCurePvpStrategy(PlayerbotAI* ai) : TankFeralDruidCureStrategy(ai) {}
        std::string getName() override { return "cure tank feral pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 坦克野性德鲁伊驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class TankFeralDruidCureRaidStrategy : public TankFeralDruidCureStrategy
    {
    public:
        TankFeralDruidCureRaidStrategy(PlayerbotAI* ai) : TankFeralDruidCureStrategy(ai) {}
        std::string getName() override { return "cure tank feral raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
