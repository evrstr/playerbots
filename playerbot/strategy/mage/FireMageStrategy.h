// 法师 - 火焰法师策略头文件 (FireMageStrategy.h)
#pragma once
#include "MageStrategy.h"

namespace ai
{
    // 火焰法师专精占位策略：用于专精识别与占位的策略类
    class FireMagePlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        FireMagePlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "fire"; }
    };

    // 火焰法师策略：定义该专精/场景下的触发器与默认行为
    class FireMageStrategy : public MageStrategy
    {
    public:
        FireMageStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 火焰法师PVE策略：定义该专精/场景下的触发器与默认行为
    class FireMagePveStrategy : public FireMageStrategy
    {
    public:
        FireMagePveStrategy(PlayerbotAI* ai) : FireMageStrategy(ai) {}
        std::string getName() override { return "fire pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师PVP策略：定义该专精/场景下的触发器与默认行为
    class FireMagePvpStrategy : public FireMageStrategy
    {
    public:
        FireMagePvpStrategy(PlayerbotAI* ai) : FireMageStrategy(ai) {}
        std::string getName() override { return "fire pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师团队副本策略：定义该专精/场景下的触发器与默认行为
    class FireMageRaidStrategy : public FireMageStrategy
    {
    public:
        FireMageRaidStrategy(PlayerbotAI* ai) : FireMageStrategy(ai) {}
        std::string getName() override { return "fire raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class FireMageAoeStrategy : public MageAoeStrategy
    {
    public:
        FireMageAoeStrategy(PlayerbotAI* ai) : MageAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class FireMageAoePveStrategy : public FireMageAoeStrategy
    {
    public:
        FireMageAoePveStrategy(PlayerbotAI* ai) : FireMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe fire pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class FireMageAoePvpStrategy : public FireMageAoeStrategy
    {
    public:
        FireMageAoePvpStrategy(PlayerbotAI* ai) : FireMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe fire pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class FireMageAoeRaidStrategy : public FireMageAoeStrategy
    {
    public:
        FireMageAoeRaidStrategy(PlayerbotAI* ai) : FireMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe fire raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class FireMageBuffStrategy : public MageBuffStrategy
    {
    public:
        FireMageBuffStrategy(PlayerbotAI* ai) : MageBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class FireMageBuffPveStrategy : public FireMageBuffStrategy
    {
    public:
        FireMageBuffPveStrategy(PlayerbotAI* ai) : FireMageBuffStrategy(ai) {}
        std::string getName() override { return "buff fire pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class FireMageBuffPvpStrategy : public FireMageBuffStrategy
    {
    public:
        FireMageBuffPvpStrategy(PlayerbotAI* ai) : FireMageBuffStrategy(ai) {}
        std::string getName() override { return "buff fire pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class FireMageBuffRaidStrategy : public FireMageBuffStrategy
    {
    public:
        FireMageBuffRaidStrategy(PlayerbotAI* ai) : FireMageBuffStrategy(ai) {}
        std::string getName() override { return "buff fire raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class FireMageBoostStrategy : public MageBoostStrategy
    {
    public:
        FireMageBoostStrategy(PlayerbotAI* ai) : MageBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class FireMageBoostPveStrategy : public FireMageBoostStrategy
    {
    public:
        FireMageBoostPveStrategy(PlayerbotAI* ai) : FireMageBoostStrategy(ai) {}
        std::string getName() override { return "boost fire pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class FireMageBoostPvpStrategy : public FireMageBoostStrategy
    {
    public:
        FireMageBoostPvpStrategy(PlayerbotAI* ai) : FireMageBoostStrategy(ai) {}
        std::string getName() override { return "boost fire pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class FireMageBoostRaidStrategy : public FireMageBoostStrategy
    {
    public:
        FireMageBoostRaidStrategy(PlayerbotAI* ai) : FireMageBoostStrategy(ai) {}
        std::string getName() override { return "boost fire raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class FireMageCcStrategy : public MageCcStrategy
    {
    public:
        FireMageCcStrategy(PlayerbotAI* ai) : MageCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class FireMageCcPveStrategy : public FireMageCcStrategy
    {
    public:
        FireMageCcPveStrategy(PlayerbotAI* ai) : FireMageCcStrategy(ai) {}
        std::string getName() override { return "cc fire pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class FireMageCcPvpStrategy : public FireMageCcStrategy
    {
    public:
        FireMageCcPvpStrategy(PlayerbotAI* ai) : FireMageCcStrategy(ai) {}
        std::string getName() override { return "cc fire pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class FireMageCcRaidStrategy : public FireMageCcStrategy
    {
    public:
        FireMageCcRaidStrategy(PlayerbotAI* ai) : FireMageCcStrategy(ai) {}
        std::string getName() override { return "cc fire raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class FireMageCureStrategy : public MageCureStrategy
    {
    public:
        FireMageCureStrategy(PlayerbotAI* ai) : MageCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class FireMageCurePveStrategy : public FireMageCureStrategy
    {
    public:
        FireMageCurePveStrategy(PlayerbotAI* ai) : FireMageCureStrategy(ai) {}
        std::string getName() override { return "cure fire pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class FireMageCurePvpStrategy : public FireMageCureStrategy
    {
    public:
        FireMageCurePvpStrategy(PlayerbotAI* ai) : FireMageCureStrategy(ai) {}
        std::string getName() override { return "cure fire pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 火焰法师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class FireMageCureRaidStrategy : public FireMageCureStrategy
    {
    public:
        FireMageCureRaidStrategy(PlayerbotAI* ai) : FireMageCureStrategy(ai) {}
        std::string getName() override { return "cure fire raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
