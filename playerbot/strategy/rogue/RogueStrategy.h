// 潜行者 - 潜行者策略头文件 (RogueStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 潜行者毒药专精占位策略：用于专精识别与占位的策略类
    class RoguePoisonsPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        RoguePoisonsPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "poisons"; }
    };

    // 潜行者策略：定义该专精/场景下的触发器与默认行为
    class RogueStrategy : public ClassStrategy
    {
    public:
        RogueStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
        
        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 潜行者PVP策略：定义该专精/场景下的触发器与默认行为
    class RoguePvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者PVE策略：定义该专精/场景下的触发器与默认行为
    class RoguePveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者团队副本策略：定义该专精/场景下的触发器与默认行为
    class RogueRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者AOE群体策略：定义该专精/场景下的触发器与默认行为
    class RogueAoeStrategy : public AoeStrategy
    {
    public:
        RogueAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 潜行者AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class RogueAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class RogueAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class RogueAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者增益Buff策略：定义该专精/场景下的触发器与默认行为
    class RogueBuffStrategy : public BuffStrategy
    {
    public:
        RogueBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 潜行者增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class RogueBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class RogueBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class RogueBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者爆发增益策略：定义该专精/场景下的触发器与默认行为
    class RogueBoostStrategy : public BoostStrategy
    {
    public:
        RogueBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 潜行者爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class RogueBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class RogueBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class RogueBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class RogueCcStrategy : public CcStrategy
    {
    public:
        RogueCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 潜行者控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class RogueCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class RogueCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class RogueCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者潜行策略：定义该专精/场景下的触发器与默认行为
    class RogueStealthStrategy : public StealthStrategy
    {
    public:
        RogueStealthStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 潜行者潜行PVP策略：定义该专精/场景下的触发器与默认行为
    class RogueStealthPvpStrategy : public StealthPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者潜行PVE策略：定义该专精/场景下的触发器与默认行为
    class RogueStealthPveStrategy : public StealthPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者潜行团队副本策略：定义该专精/场景下的触发器与默认行为
    class RogueStealthRaidStrategy : public StealthRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者毒药策略：定义该专精/场景下的触发器与默认行为
    class RoguePoisonsStrategy : public AoeStrategy
    {
    public:
        RoguePoisonsStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 潜行者毒药PVP策略：定义该专精/场景下的触发器与默认行为
    class RoguePoisonsPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者毒药PVE策略：定义该专精/场景下的触发器与默认行为
    class RoguePoisonsPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者毒药团队副本策略：定义该专精/场景下的触发器与默认行为
    class RoguePoisonsRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 潜行者手动毒药策略：定义该专精/场景下的触发器与默认行为
    class RogueManualPoisonStrategy : public Strategy
    {
    public:
        RogueManualPoisonStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName)
        : Strategy(ai)
        , name(inName)
        , triggerName(inTriggerName)
        , actionName(inActionName) {}

        std::string getName() override { return name; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;

    private:
        std::string name;
        std::string triggerName;
        std::string actionName;
    };

    // 潜行者潜行状态策略：定义该专精/场景下的触发器与默认行为
    class RogueStealthedStrategy : public StealthedStrategy
    {
    public:
        RogueStealthedStrategy(PlayerbotAI* ai) : StealthedStrategy(ai) {}

    private:
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitNonCombatMultipliers(std::list<Multiplier*>& multipliers) override;
    };
}
