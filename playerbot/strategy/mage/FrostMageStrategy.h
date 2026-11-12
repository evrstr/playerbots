// 法师 - 冰霜法师策略头文件 (FrostMageStrategy.h)
#pragma once
#include "MageStrategy.h"

namespace ai
{
    // 冰霜法师专精占位策略：用于专精识别与占位的策略类
    class FrostMagePlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        FrostMagePlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "frost"; }
    };

    // 冰霜法师策略：定义该专精/场景下的触发器与默认行为
    class FrostMageStrategy : public MageStrategy
    {
    public:
        FrostMageStrategy(PlayerbotAI* ai) : MageStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 冰霜法师PVE策略：定义该专精/场景下的触发器与默认行为
    class FrostMagePveStrategy : public FrostMageStrategy
    {
    public:
        FrostMagePveStrategy(PlayerbotAI* ai) : FrostMageStrategy(ai) {}
        std::string getName() override { return "frost pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师PVP策略：定义该专精/场景下的触发器与默认行为
    class FrostMagePvpStrategy : public FrostMageStrategy
    {
    public:
        FrostMagePvpStrategy(PlayerbotAI* ai) : FrostMageStrategy(ai) {}
        std::string getName() override { return "frost pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师团队副本策略：定义该专精/场景下的触发器与默认行为
    class FrostMageRaidStrategy : public FrostMageStrategy
    {
    public:
        FrostMageRaidStrategy(PlayerbotAI* ai) : FrostMageStrategy(ai) {}
        std::string getName() override { return "frost raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class FrostMageAoeStrategy : public MageAoeStrategy
    {
    public:
        FrostMageAoeStrategy(PlayerbotAI* ai) : MageAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class FrostMageAoePveStrategy : public FrostMageAoeStrategy
    {
    public:
        FrostMageAoePveStrategy(PlayerbotAI* ai) : FrostMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe frost pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class FrostMageAoePvpStrategy : public FrostMageAoeStrategy
    {
    public:
        FrostMageAoePvpStrategy(PlayerbotAI* ai) : FrostMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe frost pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class FrostMageAoeRaidStrategy : public FrostMageAoeStrategy
    {
    public:
        FrostMageAoeRaidStrategy(PlayerbotAI* ai) : FrostMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe frost raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBuffStrategy : public MageBuffStrategy
    {
    public:
        FrostMageBuffStrategy(PlayerbotAI* ai) : MageBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBuffPveStrategy : public FrostMageBuffStrategy
    {
    public:
        FrostMageBuffPveStrategy(PlayerbotAI* ai) : FrostMageBuffStrategy(ai) {}
        std::string getName() override { return "buff frost pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBuffPvpStrategy : public FrostMageBuffStrategy
    {
    public:
        FrostMageBuffPvpStrategy(PlayerbotAI* ai) : FrostMageBuffStrategy(ai) {}
        std::string getName() override { return "buff frost pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBuffRaidStrategy : public FrostMageBuffStrategy
    {
    public:
        FrostMageBuffRaidStrategy(PlayerbotAI* ai) : FrostMageBuffStrategy(ai) {}
        std::string getName() override { return "buff frost raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBoostStrategy : public MageBoostStrategy
    {
    public:
        FrostMageBoostStrategy(PlayerbotAI* ai) : MageBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBoostPveStrategy : public FrostMageBoostStrategy
    {
    public:
        FrostMageBoostPveStrategy(PlayerbotAI* ai) : FrostMageBoostStrategy(ai) {}
        std::string getName() override { return "boost frost pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBoostPvpStrategy : public FrostMageBoostStrategy
    {
    public:
        FrostMageBoostPvpStrategy(PlayerbotAI* ai) : FrostMageBoostStrategy(ai) {}
        std::string getName() override { return "boost frost pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class FrostMageBoostRaidStrategy : public FrostMageBoostStrategy
    {
    public:
        FrostMageBoostRaidStrategy(PlayerbotAI* ai) : FrostMageBoostStrategy(ai) {}
        std::string getName() override { return "boost frost raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCcStrategy : public MageCcStrategy
    {
    public:
        FrostMageCcStrategy(PlayerbotAI* ai) : MageCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCcPveStrategy : public FrostMageCcStrategy
    {
    public:
        FrostMageCcPveStrategy(PlayerbotAI* ai) : FrostMageCcStrategy(ai) {}
        std::string getName() override { return "cc frost pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCcPvpStrategy : public FrostMageCcStrategy
    {
    public:
        FrostMageCcPvpStrategy(PlayerbotAI* ai) : FrostMageCcStrategy(ai) {}
        std::string getName() override { return "cc frost pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCcRaidStrategy : public FrostMageCcStrategy
    {
    public:
        FrostMageCcRaidStrategy(PlayerbotAI* ai) : FrostMageCcStrategy(ai) {}
        std::string getName() override { return "cc frost raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCureStrategy : public MageCureStrategy
    {
    public:
        FrostMageCureStrategy(PlayerbotAI* ai) : MageCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCurePveStrategy : public FrostMageCureStrategy
    {
    public:
        FrostMageCurePveStrategy(PlayerbotAI* ai) : FrostMageCureStrategy(ai) {}
        std::string getName() override { return "cure frost pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCurePvpStrategy : public FrostMageCureStrategy
    {
    public:
        FrostMageCurePvpStrategy(PlayerbotAI* ai) : FrostMageCureStrategy(ai) {}
        std::string getName() override { return "cure frost pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 冰霜法师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class FrostMageCureRaidStrategy : public FrostMageCureStrategy
    {
    public:
        FrostMageCureRaidStrategy(PlayerbotAI* ai) : FrostMageCureStrategy(ai) {}
        std::string getName() override { return "cure frost raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
