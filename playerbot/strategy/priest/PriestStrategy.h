// 牧师 - 牧师策略头文件 (PriestStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 牧师策略：定义该专精/场景下的触发器与默认行为
    class PriestStrategy : public ClassStrategy
    {
    public:
        PriestStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师PVP策略：定义该专精/场景下的触发器与默认行为
    class PriestPvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师PVE策略：定义该专精/场景下的触发器与默认行为
    class PriestPveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class PriestAoeStrategy : public AoeStrategy
    {
    public:
        PriestAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class PriestAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class PriestAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class PriestCcStrategy : public CcStrategy
    {
    public:
        PriestCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class PriestCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class PriestCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class PriestBuffStrategy : public BuffStrategy
    {
    public:
        PriestBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class PriestBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class PriestBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class PriestBoostStrategy : public BoostStrategy
    {
    public:
        PriestBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class PriestBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class PriestBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class PriestCureStrategy : public CureStrategy
    {
    public:
        PriestCureStrategy(PlayerbotAI* ai) : CureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class PriestCurePvpStrategy : public CurePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class PriestCurePveStrategy : public CurePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestCureRaidStrategy : public CureRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 牧师辅助治疗策略：定义该专精/场景下的触发器与默认行为
    class PriestOffhealStrategy : public OffhealStrategy
    {
    public:
        PriestOffhealStrategy(PlayerbotAI* ai) : OffhealStrategy(ai) {}

    protected:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师辅助治疗PVP策略：定义该专精/场景下的触发器与默认行为
    class PriestOffhealPvpStrategy : public PriestOffhealStrategy
    {
    public:
        PriestOffhealPvpStrategy(PlayerbotAI* ai) : PriestOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师辅助治疗PVE策略：定义该专精/场景下的触发器与默认行为
    class PriestOffhealPveStrategy : public PriestOffhealStrategy
    {
    public:
        PriestOffhealPveStrategy(PlayerbotAI* ai) : PriestOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师辅助治疗团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestOffhealRaidStrategy : public PriestOffhealStrategy
    {
    public:
        PriestOffhealRaidStrategy(PlayerbotAI* ai) : PriestOffhealStrategy(ai) {}
        std::string getName() override { return "offheal raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师辅助输出策略：定义该专精/场景下的触发器与默认行为
    class PriestOffdpsStrategy : public OffdpsStrategy
    {
    public:
        PriestOffdpsStrategy(PlayerbotAI* ai) : OffdpsStrategy(ai) {}

    protected:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师辅助输出PVP策略：定义该专精/场景下的触发器与默认行为
    class PriestOffdpsPvpStrategy : public PriestOffdpsStrategy
    {
    public:
        PriestOffdpsPvpStrategy(PlayerbotAI* ai) : PriestOffdpsStrategy(ai) {}
        std::string getName() override { return "offdps pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师辅助输出PVE策略：定义该专精/场景下的触发器与默认行为
    class PriestOffdpsPveStrategy : public PriestOffdpsStrategy
    {
    public:
        PriestOffdpsPveStrategy(PlayerbotAI* ai) : PriestOffdpsStrategy(ai) {}
        std::string getName() override { return "offdps pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 牧师辅助输出团队副本策略：定义该专精/场景下的触发器与默认行为
    class PriestOffdpsRaidStrategy : public PriestOffdpsStrategy
    {
    public:
        PriestOffdpsRaidStrategy(PlayerbotAI* ai) : PriestOffdpsStrategy(ai) {}
        std::string getName() override { return "offdps raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
