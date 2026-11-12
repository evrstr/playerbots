// 潜行者 - 战斗潜行者策略头文件 (CombatRogueStrategy.h)
#pragma once
#include "RogueStrategy.h"

namespace ai
{
    // 战斗潜行者专精占位策略：用于专精识别与占位的策略类
    class CombatRoguePlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        CombatRoguePlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "combat"; }
    };

    // 战斗潜行者策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueStrategy : public RogueStrategy
    {
    public:
        CombatRogueStrategy(PlayerbotAI* ai) : RogueStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者PVE策略：定义该专精/场景下的触发器与默认行为
    class CombatRoguePveStrategy : public CombatRogueStrategy
    {
    public:
        CombatRoguePveStrategy(PlayerbotAI* ai) : CombatRogueStrategy(ai) {}
        std::string getName() override { return "combat pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者PVP策略：定义该专精/场景下的触发器与默认行为
    class CombatRoguePvpStrategy : public CombatRogueStrategy
    {
    public:
        CombatRoguePvpStrategy(PlayerbotAI* ai) : CombatRogueStrategy(ai) {}
        std::string getName() override { return "combat pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者团队副本策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueRaidStrategy : public CombatRogueStrategy
    {
    public:
        CombatRogueRaidStrategy(PlayerbotAI* ai) : CombatRogueStrategy(ai) {}
        std::string getName() override { return "combat raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者AOE群体策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueAoeStrategy : public RogueAoeStrategy
    {
    public:
        CombatRogueAoeStrategy(PlayerbotAI* ai) : RogueAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueAoePveStrategy : public CombatRogueAoeStrategy
    {
    public:
        CombatRogueAoePveStrategy(PlayerbotAI* ai) : CombatRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe combat pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueAoePvpStrategy : public CombatRogueAoeStrategy
    {
    public:
        CombatRogueAoePvpStrategy(PlayerbotAI* ai) : CombatRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe combat pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueAoeRaidStrategy : public CombatRogueAoeStrategy
    {
    public:
        CombatRogueAoeRaidStrategy(PlayerbotAI* ai) : CombatRogueAoeStrategy(ai) {}
        std::string getName() override { return "aoe combat raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者增益Buff策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBuffStrategy : public RogueBuffStrategy
    {
    public:
        CombatRogueBuffStrategy(PlayerbotAI* ai) : RogueBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBuffPveStrategy : public CombatRogueBuffStrategy
    {
    public:
        CombatRogueBuffPveStrategy(PlayerbotAI* ai) : CombatRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff combat pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBuffPvpStrategy : public CombatRogueBuffStrategy
    {
    public:
        CombatRogueBuffPvpStrategy(PlayerbotAI* ai) : CombatRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff combat pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBuffRaidStrategy : public CombatRogueBuffStrategy
    {
    public:
        CombatRogueBuffRaidStrategy(PlayerbotAI* ai) : CombatRogueBuffStrategy(ai) {}
        std::string getName() override { return "buff combat raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者爆发增益策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBoostStrategy : public RogueBoostStrategy
    {
    public:
        CombatRogueBoostStrategy(PlayerbotAI* ai) : RogueBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBoostPveStrategy : public CombatRogueBoostStrategy
    {
    public:
        CombatRogueBoostPveStrategy(PlayerbotAI* ai) : CombatRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost combat pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBoostPvpStrategy : public CombatRogueBoostStrategy
    {
    public:
        CombatRogueBoostPvpStrategy(PlayerbotAI* ai) : CombatRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost combat pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueBoostRaidStrategy : public CombatRogueBoostStrategy
    {
    public:
        CombatRogueBoostRaidStrategy(PlayerbotAI* ai) : CombatRogueBoostStrategy(ai) {}
        std::string getName() override { return "boost combat raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueCcStrategy : public RogueCcStrategy
    {
    public:
        CombatRogueCcStrategy(PlayerbotAI* ai) : RogueCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueCcPveStrategy : public CombatRogueCcStrategy
    {
    public:
        CombatRogueCcPveStrategy(PlayerbotAI* ai) : CombatRogueCcStrategy(ai) {}
        std::string getName() override { return "cc combat pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueCcPvpStrategy : public CombatRogueCcStrategy
    {
    public:
        CombatRogueCcPvpStrategy(PlayerbotAI* ai) : CombatRogueCcStrategy(ai) {}
        std::string getName() override { return "cc combat pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueCcRaidStrategy : public CombatRogueCcStrategy
    {
    public:
        CombatRogueCcRaidStrategy(PlayerbotAI* ai) : CombatRogueCcStrategy(ai) {}
        std::string getName() override { return "cc combat raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者潜行策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueStealthStrategy : public RogueStealthStrategy
    {
    public:
        CombatRogueStealthStrategy(PlayerbotAI* ai) : RogueStealthStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者潜行PVE策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueStealthPveStrategy : public CombatRogueStealthStrategy
    {
    public:
        CombatRogueStealthPveStrategy(PlayerbotAI* ai) : CombatRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth combat pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者潜行PVP策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueStealthPvpStrategy : public CombatRogueStealthStrategy
    {
    public:
        CombatRogueStealthPvpStrategy(PlayerbotAI* ai) : CombatRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth combat pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者潜行团队副本策略：定义该专精/场景下的触发器与默认行为
    class CombatRogueStealthRaidStrategy : public CombatRogueStealthStrategy
    {
    public:
        CombatRogueStealthRaidStrategy(PlayerbotAI* ai) : CombatRogueStealthStrategy(ai) {}
        std::string getName() override { return "stealth combat raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者毒药策略：定义该专精/场景下的触发器与默认行为
    class CombatRoguePoisonsStrategy : public RoguePoisonsStrategy
    {
    public:
        CombatRoguePoisonsStrategy(PlayerbotAI* ai) : RoguePoisonsStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者毒药PVE策略：定义该专精/场景下的触发器与默认行为
    class CombatRoguePoisonsPveStrategy : public CombatRoguePoisonsStrategy
    {
    public:
        CombatRoguePoisonsPveStrategy(PlayerbotAI* ai) : CombatRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons combat pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者毒药PVP策略：定义该专精/场景下的触发器与默认行为
    class CombatRoguePoisonsPvpStrategy : public CombatRoguePoisonsStrategy
    {
    public:
        CombatRoguePoisonsPvpStrategy(PlayerbotAI* ai) : CombatRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons combat pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 战斗潜行者毒药团队副本策略：定义该专精/场景下的触发器与默认行为
    class CombatRoguePoisonsRaidStrategy : public CombatRoguePoisonsStrategy
    {
    public:
        CombatRoguePoisonsRaidStrategy(PlayerbotAI* ai) : CombatRoguePoisonsStrategy(ai) {}
        std::string getName() override { return "poisons combat raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
