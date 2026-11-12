// 法师 - 奥术法师策略头文件 (ArcaneMageStrategy.h)
#pragma once
#include "MageStrategy.h"

namespace ai
{
    // 奥术法师专精占位策略：用于专精识别与占位的策略类
    class ArcaneMagePlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ArcaneMagePlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "arcane"; }
    };

    // 奥术法师策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageStrategy : public MageStrategy
    {
    public:
        ArcaneMageStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 奥术法师PVE策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMagePveStrategy : public ArcaneMageStrategy
    {
    public:
        ArcaneMagePveStrategy(PlayerbotAI* ai) : ArcaneMageStrategy(ai) {}
        std::string getName() override { return "arcane pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师PVP策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMagePvpStrategy : public ArcaneMageStrategy
    {
    public:
        ArcaneMagePvpStrategy(PlayerbotAI* ai) : ArcaneMageStrategy(ai) {}
        std::string getName() override { return "arcane pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageRaidStrategy : public ArcaneMageStrategy
    {
    public:
        ArcaneMageRaidStrategy(PlayerbotAI* ai) : ArcaneMageStrategy(ai) {}
        std::string getName() override { return "arcane raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageAoeStrategy : public MageAoeStrategy
    {
    public:
        ArcaneMageAoeStrategy(PlayerbotAI* ai) : MageAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageAoePveStrategy : public ArcaneMageAoeStrategy
    {
    public:
        ArcaneMageAoePveStrategy(PlayerbotAI* ai) : ArcaneMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe arcane pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageAoePvpStrategy : public ArcaneMageAoeStrategy
    {
    public:
        ArcaneMageAoePvpStrategy(PlayerbotAI* ai) : ArcaneMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe arcane pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageAoeRaidStrategy : public ArcaneMageAoeStrategy
    {
    public:
        ArcaneMageAoeRaidStrategy(PlayerbotAI* ai) : ArcaneMageAoeStrategy(ai) {}
        std::string getName() override { return "aoe arcane raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBuffStrategy : public MageBuffStrategy
    {
    public:
        ArcaneMageBuffStrategy(PlayerbotAI* ai) : MageBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBuffPveStrategy : public ArcaneMageBuffStrategy
    {
    public:
        ArcaneMageBuffPveStrategy(PlayerbotAI* ai) : ArcaneMageBuffStrategy(ai) {}
        std::string getName() override { return "buff arcane pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBuffPvpStrategy : public ArcaneMageBuffStrategy
    {
    public:
        ArcaneMageBuffPvpStrategy(PlayerbotAI* ai) : ArcaneMageBuffStrategy(ai) {}
        std::string getName() override { return "buff arcane pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBuffRaidStrategy : public ArcaneMageBuffStrategy
    {
    public:
        ArcaneMageBuffRaidStrategy(PlayerbotAI* ai) : ArcaneMageBuffStrategy(ai) {}
        std::string getName() override { return "buff arcane raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBoostStrategy : public MageBoostStrategy
    {
    public:
        ArcaneMageBoostStrategy(PlayerbotAI* ai) : MageBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBoostPveStrategy : public ArcaneMageBoostStrategy
    {
    public:
        ArcaneMageBoostPveStrategy(PlayerbotAI* ai) : ArcaneMageBoostStrategy(ai) {}
        std::string getName() override { return "boost arcane pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBoostPvpStrategy : public ArcaneMageBoostStrategy
    {
    public:
        ArcaneMageBoostPvpStrategy(PlayerbotAI* ai) : ArcaneMageBoostStrategy(ai) {}
        std::string getName() override { return "boost arcane pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageBoostRaidStrategy : public ArcaneMageBoostStrategy
    {
    public:
        ArcaneMageBoostRaidStrategy(PlayerbotAI* ai) : ArcaneMageBoostStrategy(ai) {}
        std::string getName() override { return "boost arcane raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCcStrategy : public MageCcStrategy
    {
    public:
        ArcaneMageCcStrategy(PlayerbotAI* ai) : MageCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCcPveStrategy : public ArcaneMageCcStrategy
    {
    public:
        ArcaneMageCcPveStrategy(PlayerbotAI* ai) : ArcaneMageCcStrategy(ai) {}
        std::string getName() override { return "cc arcane pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCcPvpStrategy : public ArcaneMageCcStrategy
    {
    public:
        ArcaneMageCcPvpStrategy(PlayerbotAI* ai) : ArcaneMageCcStrategy(ai) {}
        std::string getName() override { return "cc arcane pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCcRaidStrategy : public ArcaneMageCcStrategy
    {
    public:
        ArcaneMageCcRaidStrategy(PlayerbotAI* ai) : ArcaneMageCcStrategy(ai) {}
        std::string getName() override { return "cc arcane raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCureStrategy : public MageCureStrategy
    {
    public:
        ArcaneMageCureStrategy(PlayerbotAI* ai) : MageCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCurePveStrategy : public ArcaneMageCureStrategy
    {
    public:
        ArcaneMageCurePveStrategy(PlayerbotAI* ai) : ArcaneMageCureStrategy(ai) {}
        std::string getName() override { return "cure arcane pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCurePvpStrategy : public ArcaneMageCureStrategy
    {
    public:
        ArcaneMageCurePvpStrategy(PlayerbotAI* ai) : ArcaneMageCureStrategy(ai) {}
        std::string getName() override { return "cure arcane pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 奥术法师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class ArcaneMageCureRaidStrategy : public ArcaneMageCureStrategy
    {
    public:
        ArcaneMageCureRaidStrategy(PlayerbotAI* ai) : ArcaneMageCureStrategy(ai) {}
        std::string getName() override { return "cure arcane raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
