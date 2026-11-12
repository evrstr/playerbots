// 德鲁伊 - 恢复德鲁伊策略头文件 (RestorationDruidStrategy.h)
#pragma once
#include "DruidStrategy.h"

namespace ai
{
    // 恢复德鲁伊专精占位策略：用于专精识别与占位的策略类
    class RestorationDruidPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        RestorationDruidPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_HEAL | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "restoration"; }
    };

    // 恢复德鲁伊策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidStrategy : public DruidStrategy
    {
    public:
        RestorationDruidStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidPveStrategy : public RestorationDruidStrategy
    {
    public:
        RestorationDruidPveStrategy(PlayerbotAI* ai) : RestorationDruidStrategy(ai) {}
        std::string getName() override { return "restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidPvpStrategy : public RestorationDruidStrategy
    {
    public:
        RestorationDruidPvpStrategy(PlayerbotAI* ai) : RestorationDruidStrategy(ai) {}
        std::string getName() override { return "restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidRaidStrategy : public RestorationDruidStrategy
    {
    public:
        RestorationDruidRaidStrategy(PlayerbotAI* ai) : RestorationDruidStrategy(ai) {}
        std::string getName() override { return "restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊AOE群体策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidAoeStrategy : public DruidAoeStrategy
    {
    public:
        RestorationDruidAoeStrategy(PlayerbotAI* ai) : DruidAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidAoePveStrategy : public RestorationDruidAoeStrategy
    {
    public:
        RestorationDruidAoePveStrategy(PlayerbotAI* ai) : RestorationDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidAoePvpStrategy : public RestorationDruidAoeStrategy
    {
    public:
        RestorationDruidAoePvpStrategy(PlayerbotAI* ai) : RestorationDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidAoeRaidStrategy : public RestorationDruidAoeStrategy
    {
    public:
        RestorationDruidAoeRaidStrategy(PlayerbotAI* ai) : RestorationDruidAoeStrategy(ai) {}
        std::string getName() override { return "aoe restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊增益Buff策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBuffStrategy : public DruidBuffStrategy
    {
    public:
        RestorationDruidBuffStrategy(PlayerbotAI* ai) : DruidBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBuffPveStrategy : public RestorationDruidBuffStrategy
    {
    public:
        RestorationDruidBuffPveStrategy(PlayerbotAI* ai) : RestorationDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBuffPvpStrategy : public RestorationDruidBuffStrategy
    {
    public:
        RestorationDruidBuffPvpStrategy(PlayerbotAI* ai) : RestorationDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBuffRaidStrategy : public RestorationDruidBuffStrategy
    {
    public:
        RestorationDruidBuffRaidStrategy(PlayerbotAI* ai) : RestorationDruidBuffStrategy(ai) {}
        std::string getName() override { return "buff restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊爆发增益策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBoostStrategy : public DruidBoostStrategy
    {
    public:
        RestorationDruidBoostStrategy(PlayerbotAI* ai) : DruidBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBoostPveStrategy : public RestorationDruidBoostStrategy
    {
    public:
        RestorationDruidBoostPveStrategy(PlayerbotAI* ai) : RestorationDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBoostPvpStrategy : public RestorationDruidBoostStrategy
    {
    public:
        RestorationDruidBoostPvpStrategy(PlayerbotAI* ai) : RestorationDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidBoostRaidStrategy : public RestorationDruidBoostStrategy
    {
    public:
        RestorationDruidBoostRaidStrategy(PlayerbotAI* ai) : RestorationDruidBoostStrategy(ai) {}
        std::string getName() override { return "boost restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCcStrategy : public DruidCcStrategy
    {
    public:
        RestorationDruidCcStrategy(PlayerbotAI* ai) : DruidCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCcPveStrategy : public RestorationDruidCcStrategy
    {
    public:
        RestorationDruidCcPveStrategy(PlayerbotAI* ai) : RestorationDruidCcStrategy(ai) {}
        std::string getName() override { return "cc restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCcPvpStrategy : public RestorationDruidCcStrategy
    {
    public:
        RestorationDruidCcPvpStrategy(PlayerbotAI* ai) : RestorationDruidCcStrategy(ai) {}
        std::string getName() override { return "cc restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCcRaidStrategy : public RestorationDruidCcStrategy
    {
    public:
        RestorationDruidCcRaidStrategy(PlayerbotAI* ai) : RestorationDruidCcStrategy(ai) {}
        std::string getName() override { return "cc restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊驱散净化策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCureStrategy : public DruidCureStrategy
    {
    public:
        RestorationDruidCureStrategy(PlayerbotAI* ai) : DruidCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCurePveStrategy : public RestorationDruidCureStrategy
    {
    public:
        RestorationDruidCurePveStrategy(PlayerbotAI* ai) : RestorationDruidCureStrategy(ai) {}
        std::string getName() override { return "cure restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCurePvpStrategy : public RestorationDruidCureStrategy
    {
    public:
        RestorationDruidCurePvpStrategy(PlayerbotAI* ai) : RestorationDruidCureStrategy(ai) {}
        std::string getName() override { return "cure restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复德鲁伊驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationDruidCureRaidStrategy : public RestorationDruidCureStrategy
    {
    public:
        RestorationDruidCureRaidStrategy(PlayerbotAI* ai) : RestorationDruidCureStrategy(ai) {}
        std::string getName() override { return "cure restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
