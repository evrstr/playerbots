// 猎人 - 野兽控制猎人策略头文件 (BeastMasteryHunterStrategy.h)
#pragma once
#include "HunterStrategy.h"

namespace ai
{
    // 野兽控制猎人专精占位策略：用于专精识别与占位的策略类
    class BeastMasteryHunterPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        BeastMasteryHunterPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "beast mastery"; }
    };

    // 野兽控制猎人策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterStrategy : public HunterStrategy
    {
    public:
        BeastMasteryHunterStrategy(PlayerbotAI* ai) : HunterStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人PVE策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterPveStrategy : public BeastMasteryHunterStrategy
    {
    public:
        BeastMasteryHunterPveStrategy(PlayerbotAI* ai) : BeastMasteryHunterStrategy(ai) {}
        std::string getName() override { return "beast mastery pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人PVP策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterPvpStrategy : public BeastMasteryHunterStrategy
    {
    public:
        BeastMasteryHunterPvpStrategy(PlayerbotAI* ai) : BeastMasteryHunterStrategy(ai) {}
        std::string getName() override { return "beast mastery pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人团队副本策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterRaidStrategy : public BeastMasteryHunterStrategy
    {
    public:
        BeastMasteryHunterRaidStrategy(PlayerbotAI* ai) : BeastMasteryHunterStrategy(ai) {}
        std::string getName() override { return "beast mastery raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人AOE群体策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAoeStrategy : public HunterAoeStrategy
    {
    public:
        BeastMasteryHunterAoeStrategy(PlayerbotAI* ai) : HunterAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAoePveStrategy : public BeastMasteryHunterAoeStrategy
    {
    public:
        BeastMasteryHunterAoePveStrategy(PlayerbotAI* ai) : BeastMasteryHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe beast mastery pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAoePvpStrategy : public BeastMasteryHunterAoeStrategy
    {
    public:
        BeastMasteryHunterAoePvpStrategy(PlayerbotAI* ai) : BeastMasteryHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe beast mastery pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAoeRaidStrategy : public BeastMasteryHunterAoeStrategy
    {
    public:
        BeastMasteryHunterAoeRaidStrategy(PlayerbotAI* ai) : BeastMasteryHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe beast mastery raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人增益Buff策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBuffStrategy : public HunterBuffStrategy
    {
    public:
        BeastMasteryHunterBuffStrategy(PlayerbotAI* ai) : HunterBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBuffPveStrategy : public BeastMasteryHunterBuffStrategy
    {
    public:
        BeastMasteryHunterBuffPveStrategy(PlayerbotAI* ai) : BeastMasteryHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff beast mastery pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBuffPvpStrategy : public BeastMasteryHunterBuffStrategy
    {
    public:
        BeastMasteryHunterBuffPvpStrategy(PlayerbotAI* ai) : BeastMasteryHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff beast mastery pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBuffRaidStrategy : public BeastMasteryHunterBuffStrategy
    {
    public:
        BeastMasteryHunterBuffRaidStrategy(PlayerbotAI* ai) : BeastMasteryHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff beast mastery raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人爆发增益策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBoostStrategy : public HunterBoostStrategy
    {
    public:
        BeastMasteryHunterBoostStrategy(PlayerbotAI* ai) : HunterBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBoostPveStrategy : public BeastMasteryHunterBoostStrategy
    {
    public:
        BeastMasteryHunterBoostPveStrategy(PlayerbotAI* ai) : BeastMasteryHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost beast mastery pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBoostPvpStrategy : public BeastMasteryHunterBoostStrategy
    {
    public:
        BeastMasteryHunterBoostPvpStrategy(PlayerbotAI* ai) : BeastMasteryHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost beast mastery pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterBoostRaidStrategy : public BeastMasteryHunterBoostStrategy
    {
    public:
        BeastMasteryHunterBoostRaidStrategy(PlayerbotAI* ai) : BeastMasteryHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost beast mastery raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterCcStrategy : public HunterCcStrategy
    {
    public:
        BeastMasteryHunterCcStrategy(PlayerbotAI* ai) : HunterCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterCcPveStrategy : public BeastMasteryHunterCcStrategy
    {
    public:
        BeastMasteryHunterCcPveStrategy(PlayerbotAI* ai) : BeastMasteryHunterCcStrategy(ai) {}
        std::string getName() override { return "cc beast mastery pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterCcPvpStrategy : public BeastMasteryHunterCcStrategy
    {
    public:
        BeastMasteryHunterCcPvpStrategy(PlayerbotAI* ai) : BeastMasteryHunterCcStrategy(ai) {}
        std::string getName() override { return "cc beast mastery pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterCcRaidStrategy : public BeastMasteryHunterCcStrategy
    {
    public:
        BeastMasteryHunterCcRaidStrategy(PlayerbotAI* ai) : BeastMasteryHunterCcStrategy(ai) {}
        std::string getName() override { return "cc beast mastery raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人钉刺策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterStingStrategy : public HunterStingStrategy
    {
    public:
        BeastMasteryHunterStingStrategy(PlayerbotAI* ai) : HunterStingStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人钉刺PVE策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterStingPveStrategy : public BeastMasteryHunterStingStrategy
    {
    public:
        BeastMasteryHunterStingPveStrategy(PlayerbotAI* ai) : BeastMasteryHunterStingStrategy(ai) {}
        std::string getName() override { return "sting beast mastery pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人钉刺PVP策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterStingPvpStrategy : public BeastMasteryHunterStingStrategy
    {
    public:
        BeastMasteryHunterStingPvpStrategy(PlayerbotAI* ai) : BeastMasteryHunterStingStrategy(ai) {}
        std::string getName() override { return "sting beast mastery pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人钉刺团队副本策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterStingRaidStrategy : public BeastMasteryHunterStingStrategy
    {
    public:
        BeastMasteryHunterStingRaidStrategy(PlayerbotAI* ai) : BeastMasteryHunterStingStrategy(ai) {}
        std::string getName() override { return "sting beast mastery raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人守护策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAspectStrategy : public HunterAspectStrategy
    {
    public:
        BeastMasteryHunterAspectStrategy(PlayerbotAI* ai) : HunterAspectStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人守护PVE策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAspectPveStrategy : public BeastMasteryHunterAspectStrategy
    {
    public:
        BeastMasteryHunterAspectPveStrategy(PlayerbotAI* ai) : BeastMasteryHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect beast mastery pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人守护PVP策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAspectPvpStrategy : public BeastMasteryHunterAspectStrategy
    {
    public:
        BeastMasteryHunterAspectPvpStrategy(PlayerbotAI* ai) : BeastMasteryHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect beast mastery pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 野兽控制猎人守护团队副本策略：定义该专精/场景下的触发器与默认行为
    class BeastMasteryHunterAspectRaidStrategy : public BeastMasteryHunterAspectStrategy
    {
    public:
        BeastMasteryHunterAspectRaidStrategy(PlayerbotAI* ai) : BeastMasteryHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect beast mastery raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
