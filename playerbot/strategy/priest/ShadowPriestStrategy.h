// 牧师 - 暗影牧师策略头文件 (ShadowPriestStrategy.h)
#pragma once
#include "PriestStrategy.h"

namespace ai
{
    // 暗影牧师专精占位策略：用于专精识别与占位的策略类
    class ShadowPriestPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ShadowPriestPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "shadow"; }
    };

    // 暗影牧师策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestStrategy : public PriestStrategy
    {
    public:
        ShadowPriestStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 暗影牧师PVE策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestPveStrategy : public ShadowPriestStrategy
    {
    public:
        ShadowPriestPveStrategy(PlayerbotAI* ai) : ShadowPriestStrategy(ai) {}
        std::string getName() override { return "shadow pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师PVP策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestPvpStrategy : public ShadowPriestStrategy
    {
    public:
        ShadowPriestPvpStrategy(PlayerbotAI* ai) : ShadowPriestStrategy(ai) {}
        std::string getName() override { return "shadow pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestRaidStrategy : public ShadowPriestStrategy
    {
    public:
        ShadowPriestRaidStrategy(PlayerbotAI* ai) : ShadowPriestStrategy(ai) {}
        std::string getName() override { return "shadow raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestAoeStrategy : public PriestAoeStrategy
    {
    public:
        ShadowPriestAoeStrategy(PlayerbotAI* ai) : PriestAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestAoePveStrategy : public ShadowPriestAoeStrategy
    {
    public:
        ShadowPriestAoePveStrategy(PlayerbotAI* ai) : ShadowPriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe shadow pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestAoePvpStrategy : public ShadowPriestAoeStrategy
    {
    public:
        ShadowPriestAoePvpStrategy(PlayerbotAI* ai) : ShadowPriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe shadow pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestAoeRaidStrategy : public ShadowPriestAoeStrategy
    {
    public:
        ShadowPriestAoeRaidStrategy(PlayerbotAI* ai) : ShadowPriestAoeStrategy(ai) {}
        std::string getName() override { return "aoe shadow raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBuffStrategy : public PriestBuffStrategy
    {
    public:
        ShadowPriestBuffStrategy(PlayerbotAI* ai) : PriestBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBuffPveStrategy : public ShadowPriestBuffStrategy
    {
    public:
        ShadowPriestBuffPveStrategy(PlayerbotAI* ai) : ShadowPriestBuffStrategy(ai) {}
        std::string getName() override { return "buff shadow pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBuffPvpStrategy : public ShadowPriestBuffStrategy
    {
    public:
        ShadowPriestBuffPvpStrategy(PlayerbotAI* ai) : ShadowPriestBuffStrategy(ai) {}
        std::string getName() override { return "buff shadow pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBuffRaidStrategy : public ShadowPriestBuffStrategy
    {
    public:
        ShadowPriestBuffRaidStrategy(PlayerbotAI* ai) : ShadowPriestBuffStrategy(ai) {}
        std::string getName() override { return "buff shadow raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBoostStrategy : public PriestBoostStrategy
    {
    public:
        ShadowPriestBoostStrategy(PlayerbotAI* ai) : PriestBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBoostPveStrategy : public ShadowPriestBoostStrategy
    {
    public:
        ShadowPriestBoostPveStrategy(PlayerbotAI* ai) : ShadowPriestBoostStrategy(ai) {}
        std::string getName() override { return "boost shadow pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBoostPvpStrategy : public ShadowPriestBoostStrategy
    {
    public:
        ShadowPriestBoostPvpStrategy(PlayerbotAI* ai) : ShadowPriestBoostStrategy(ai) {}
        std::string getName() override { return "boost shadow pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestBoostRaidStrategy : public ShadowPriestBoostStrategy
    {
    public:
        ShadowPriestBoostRaidStrategy(PlayerbotAI* ai) : ShadowPriestBoostStrategy(ai) {}
        std::string getName() override { return "boost shadow raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCcStrategy : public PriestCcStrategy
    {
    public:
        ShadowPriestCcStrategy(PlayerbotAI* ai) : PriestCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCcPveStrategy : public ShadowPriestCcStrategy
    {
    public:
        ShadowPriestCcPveStrategy(PlayerbotAI* ai) : ShadowPriestCcStrategy(ai) {}
        std::string getName() override { return "cc shadow pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCcPvpStrategy : public ShadowPriestCcStrategy
    {
    public:
        ShadowPriestCcPvpStrategy(PlayerbotAI* ai) : ShadowPriestCcStrategy(ai) {}
        std::string getName() override { return "cc shadow pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCcRaidStrategy : public ShadowPriestCcStrategy
    {
    public:
        ShadowPriestCcRaidStrategy(PlayerbotAI* ai) : ShadowPriestCcStrategy(ai) {}
        std::string getName() override { return "cc shadow raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCureStrategy : public PriestCureStrategy
    {
    public:
        ShadowPriestCureStrategy(PlayerbotAI* ai) : PriestCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCurePveStrategy : public ShadowPriestCureStrategy
    {
    public:
        ShadowPriestCurePveStrategy(PlayerbotAI* ai) : ShadowPriestCureStrategy(ai) {}
        std::string getName() override { return "cure shadow pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCurePvpStrategy : public ShadowPriestCureStrategy
    {
    public:
        ShadowPriestCurePvpStrategy(PlayerbotAI* ai) : ShadowPriestCureStrategy(ai) {}
        std::string getName() override { return "cure shadow pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 暗影牧师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShadowPriestCureRaidStrategy : public ShadowPriestCureStrategy
    {
    public:
        ShadowPriestCureRaidStrategy(PlayerbotAI* ai) : ShadowPriestCureStrategy(ai) {}
        std::string getName() override { return "cure shadow raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
