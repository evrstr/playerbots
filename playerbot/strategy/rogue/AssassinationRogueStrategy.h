// 潜行者 - 刺杀潜行者策略头文件 (AssassinationRogueStrategy.h)
#pragma once
#include "RogueStrategy.h"

namespace ai
{
    // 刺杀潜行者专精占位策略：用于专精识别与占位的策略类
    class AssassinationRoguePlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        AssassinationRoguePlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "assassination"; }
    };

    // 刺杀潜行者策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueStrategy : public RogueStrategy
    {
    public:
        AssassinationRogueStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者PVE策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRoguePveStrategy : public AssassinationRogueStrategy
    {
    public:
        AssassinationRoguePveStrategy(PlayerbotAI* ai) : AssassinationRogueStrategy(ai) {}
        std::string getName() override { return "assassination pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者PVP策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRoguePvpStrategy : public AssassinationRogueStrategy
    {
    public:
        AssassinationRoguePvpStrategy(PlayerbotAI* ai) : AssassinationRogueStrategy(ai) {}
        std::string getName() override { return "assassination pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者团队副本策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueRaidStrategy : public AssassinationRogueStrategy
    {
    public:
        AssassinationRogueRaidStrategy(PlayerbotAI* ai) : AssassinationRogueStrategy(ai) {}
        std::string getName() override { return "assassination raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者AOE群体策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueAoeStrategy : public RogueAoeStrategy
    {
    public:
        AssassinationRogueAoeStrategy(PlayerbotAI* ai) : RogueAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueAoePveStrategy : public AssassinationRogueAoeStrategy
    {
    public:
        AssassinationRogueAoePveStrategy(PlayerbotAI* ai) : AssassinationRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe assassination pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueAoePvpStrategy : public AssassinationRogueAoeStrategy
    {
    public:
        AssassinationRogueAoePvpStrategy(PlayerbotAI* ai) : AssassinationRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe assassination pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueAoeRaidStrategy : public AssassinationRogueAoeStrategy
    {
    public:
        AssassinationRogueAoeRaidStrategy(PlayerbotAI* ai) : AssassinationRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe assassination raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者增益Buff策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBuffStrategy : public RogueBuffStrategy
    {
    public:
        AssassinationRogueBuffStrategy(PlayerbotAI* ai) : RogueBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBuffPveStrategy : public AssassinationRogueBuffStrategy
    {
    public:
        AssassinationRogueBuffPveStrategy(PlayerbotAI* ai) : AssassinationRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff assassination pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBuffPvpStrategy : public AssassinationRogueBuffStrategy
    {
    public:
        AssassinationRogueBuffPvpStrategy(PlayerbotAI* ai) : AssassinationRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff assassination pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBuffRaidStrategy : public AssassinationRogueBuffStrategy
    {
    public:
        AssassinationRogueBuffRaidStrategy(PlayerbotAI* ai) : AssassinationRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff assassination raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者爆发增益策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBoostStrategy : public RogueBoostStrategy
    {
    public:
        AssassinationRogueBoostStrategy(PlayerbotAI* ai) : RogueBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBoostPveStrategy : public AssassinationRogueBoostStrategy
    {
    public:
        AssassinationRogueBoostPveStrategy(PlayerbotAI* ai) : AssassinationRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost assassination pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBoostPvpStrategy : public AssassinationRogueBoostStrategy
    {
    public:
        AssassinationRogueBoostPvpStrategy(PlayerbotAI* ai) : AssassinationRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost assassination pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueBoostRaidStrategy : public AssassinationRogueBoostStrategy
    {
    public:
        AssassinationRogueBoostRaidStrategy(PlayerbotAI* ai) : AssassinationRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost assassination raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueCcStrategy : public RogueCcStrategy
    {
    public:
        AssassinationRogueCcStrategy(PlayerbotAI* ai) : RogueCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueCcPveStrategy : public AssassinationRogueCcStrategy
    {
    public:
        AssassinationRogueCcPveStrategy(PlayerbotAI* ai) : AssassinationRogueCcStrategy(ai) {}
        std::string getName() override { return "cc assassination pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueCcPvpStrategy : public AssassinationRogueCcStrategy
    {
    public:
        AssassinationRogueCcPvpStrategy(PlayerbotAI* ai) : AssassinationRogueCcStrategy(ai) {}
        std::string getName() override { return "cc assassination pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueCcRaidStrategy : public AssassinationRogueCcStrategy
    {
    public:
        AssassinationRogueCcRaidStrategy(PlayerbotAI* ai) : AssassinationRogueCcStrategy(ai) {}
        std::string getName() override { return "cc assassination raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者潜行策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueStealthStrategy : public RogueStealthStrategy
    {
    public:
        AssassinationRogueStealthStrategy(PlayerbotAI* ai) : RogueStealthStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者潜行PVE策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueStealthPveStrategy : public AssassinationRogueStealthStrategy
    {
    public:
        AssassinationRogueStealthPveStrategy(PlayerbotAI* ai) : AssassinationRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth assassination pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者潜行PVP策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueStealthPvpStrategy : public AssassinationRogueStealthStrategy
    {
    public:
        AssassinationRogueStealthPvpStrategy(PlayerbotAI* ai) : AssassinationRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth assassination pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者潜行团队副本策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRogueStealthRaidStrategy : public AssassinationRogueStealthStrategy
    {
    public:
        AssassinationRogueStealthRaidStrategy(PlayerbotAI* ai) : AssassinationRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth assassination raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者毒药策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRoguePoisonsStrategy : public RoguePoisonsStrategy
    {
    public:
        AssassinationRoguePoisonsStrategy(PlayerbotAI* ai) : RoguePoisonsStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者毒药PVE策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRoguePoisonsPveStrategy : public AssassinationRoguePoisonsStrategy
    {
    public:
        AssassinationRoguePoisonsPveStrategy(PlayerbotAI* ai) : AssassinationRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons assassination pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者毒药PVP策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRoguePoisonsPvpStrategy : public AssassinationRoguePoisonsStrategy
    {
    public:
        AssassinationRoguePoisonsPvpStrategy(PlayerbotAI* ai) : AssassinationRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons assassination pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 刺杀潜行者毒药团队副本策略：定义该专精/场景下的触发器与默认行为
    class AssassinationRoguePoisonsRaidStrategy : public AssassinationRoguePoisonsStrategy
    {
    public:
        AssassinationRoguePoisonsRaidStrategy(PlayerbotAI* ai) : AssassinationRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons assassination raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
