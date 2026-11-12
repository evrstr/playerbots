// 潜行者 - 敏锐潜行者策略头文件 (SubtletyRogueStrategy.h)
#pragma once
#include "RogueStrategy.h"

namespace ai
{
    // 敏锐潜行者专精占位策略：用于专精识别与占位的策略类
    class SubtletyRoguePlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        SubtletyRoguePlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "subtlety"; }
    };

    // 敏锐潜行者策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueStrategy : public RogueStrategy
    {
    public:
        SubtletyRogueStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者PVE策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRoguePveStrategy : public SubtletyRogueStrategy
    {
    public:
        SubtletyRoguePveStrategy(PlayerbotAI* ai) : SubtletyRogueStrategy(ai) {}
        std::string getName() override { return "subtlety pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者PVP策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRoguePvpStrategy : public SubtletyRogueStrategy
    {
    public:
        SubtletyRoguePvpStrategy(PlayerbotAI* ai) : SubtletyRogueStrategy(ai) {}
        std::string getName() override { return "subtlety pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者团队副本策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueRaidStrategy : public SubtletyRogueStrategy
    {
    public:
        SubtletyRogueRaidStrategy(PlayerbotAI* ai) : SubtletyRogueStrategy(ai) {}
        std::string getName() override { return "subtlety raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者AOE群体策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueAoeStrategy : public RogueAoeStrategy
    {
    public:
        SubtletyRogueAoeStrategy(PlayerbotAI* ai) : RogueAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueAoePveStrategy : public SubtletyRogueAoeStrategy
    {
    public:
        SubtletyRogueAoePveStrategy(PlayerbotAI* ai) : SubtletyRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe subtlety pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueAoePvpStrategy : public SubtletyRogueAoeStrategy
    {
    public:
        SubtletyRogueAoePvpStrategy(PlayerbotAI* ai) : SubtletyRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe subtlety pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueAoeRaidStrategy : public SubtletyRogueAoeStrategy
    {
    public:
        SubtletyRogueAoeRaidStrategy(PlayerbotAI* ai) : SubtletyRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe subtlety raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者增益Buff策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBuffStrategy : public RogueBuffStrategy
    {
    public:
        SubtletyRogueBuffStrategy(PlayerbotAI* ai) : RogueBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBuffPveStrategy : public SubtletyRogueBuffStrategy
    {
    public:
        SubtletyRogueBuffPveStrategy(PlayerbotAI* ai) : SubtletyRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff subtlety pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBuffPvpStrategy : public SubtletyRogueBuffStrategy
    {
    public:
        SubtletyRogueBuffPvpStrategy(PlayerbotAI* ai) : SubtletyRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff subtlety pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBuffRaidStrategy : public SubtletyRogueBuffStrategy
    {
    public:
        SubtletyRogueBuffRaidStrategy(PlayerbotAI* ai) : SubtletyRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff subtlety raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者爆发增益策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBoostStrategy : public RogueBoostStrategy
    {
    public:
        SubtletyRogueBoostStrategy(PlayerbotAI* ai) : RogueBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBoostPveStrategy : public SubtletyRogueBoostStrategy
    {
    public:
        SubtletyRogueBoostPveStrategy(PlayerbotAI* ai) : SubtletyRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost subtlety pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBoostPvpStrategy : public SubtletyRogueBoostStrategy
    {
    public:
        SubtletyRogueBoostPvpStrategy(PlayerbotAI* ai) : SubtletyRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost subtlety pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueBoostRaidStrategy : public SubtletyRogueBoostStrategy
    {
    public:
        SubtletyRogueBoostRaidStrategy(PlayerbotAI* ai) : SubtletyRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost subtlety raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueCcStrategy : public RogueCcStrategy
    {
    public:
        SubtletyRogueCcStrategy(PlayerbotAI* ai) : RogueCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueCcPveStrategy : public SubtletyRogueCcStrategy
    {
    public:
        SubtletyRogueCcPveStrategy(PlayerbotAI* ai) : SubtletyRogueCcStrategy(ai) {}
        std::string getName() override { return "cc subtlety pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueCcPvpStrategy : public SubtletyRogueCcStrategy
    {
    public:
        SubtletyRogueCcPvpStrategy(PlayerbotAI* ai) : SubtletyRogueCcStrategy(ai) {}
        std::string getName() override { return "cc subtlety pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueCcRaidStrategy : public SubtletyRogueCcStrategy
    {
    public:
        SubtletyRogueCcRaidStrategy(PlayerbotAI* ai) : SubtletyRogueCcStrategy(ai) {}
        std::string getName() override { return "cc subtlety raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者潜行策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueStealthStrategy : public RogueStealthStrategy
    {
    public:
        SubtletyRogueStealthStrategy(PlayerbotAI* ai) : RogueStealthStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者潜行PVE策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueStealthPveStrategy : public SubtletyRogueStealthStrategy
    {
    public:
        SubtletyRogueStealthPveStrategy(PlayerbotAI* ai) : SubtletyRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth subtlety pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者潜行PVP策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueStealthPvpStrategy : public SubtletyRogueStealthStrategy
    {
    public:
        SubtletyRogueStealthPvpStrategy(PlayerbotAI* ai) : SubtletyRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth subtlety pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者潜行团队副本策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRogueStealthRaidStrategy : public SubtletyRogueStealthStrategy
    {
    public:
        SubtletyRogueStealthRaidStrategy(PlayerbotAI* ai) : SubtletyRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth subtlety raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者毒药策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRoguePoisonsStrategy : public RoguePoisonsStrategy
    {
    public:
        SubtletyRoguePoisonsStrategy(PlayerbotAI* ai) : RoguePoisonsStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者毒药PVE策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRoguePoisonsPveStrategy : public SubtletyRoguePoisonsStrategy
    {
    public:
        SubtletyRoguePoisonsPveStrategy(PlayerbotAI* ai) : SubtletyRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons subtlety pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者毒药PVP策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRoguePoisonsPvpStrategy : public SubtletyRoguePoisonsStrategy
    {
    public:
        SubtletyRoguePoisonsPvpStrategy(PlayerbotAI* ai) : SubtletyRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons subtlety pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 敏锐潜行者毒药团队副本策略：定义该专精/场景下的触发器与默认行为
    class SubtletyRoguePoisonsRaidStrategy : public SubtletyRoguePoisonsStrategy
    {
    public:
        SubtletyRoguePoisonsRaidStrategy(PlayerbotAI* ai) : SubtletyRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons subtlety raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
