// 法师 - 法师策略头文件 (MageStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 法师策略：定义该专精/场景下的触发器与默认行为
    class MageStrategy : public ClassStrategy
    {
    public:
        MageStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 法师PVP策略：定义该专精/场景下的触发器与默认行为
    class MagePvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师PVE策略：定义该专精/场景下的触发器与默认行为
    class MagePveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师团队副本策略：定义该专精/场景下的触发器与默认行为
    class MageRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师AOE群体策略：定义该专精/场景下的触发器与默认行为
    class MageAoeStrategy : public AoeStrategy
    {
    public:
        MageAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 法师AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class MageAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class MageAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class MageAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师增益Buff策略：定义该专精/场景下的触发器与默认行为
    class MageBuffStrategy : public BuffStrategy
    {
    public:
        MageBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 法师增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class MageBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class MageBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class MageBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师爆发增益策略：定义该专精/场景下的触发器与默认行为
    class MageBoostStrategy : public BoostStrategy
    {
    public:
        MageBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 法师爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class MageBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class MageBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class MageBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class MageCcStrategy : public CcStrategy
    {
    public:
        MageCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 法师控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class MageCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class MageCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class MageCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师驱散净化策略：定义该专精/场景下的触发器与默认行为
    class MageCureStrategy : public CureStrategy
    {
    public:
        MageCureStrategy(PlayerbotAI* ai) : CureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 法师驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class MageCurePvpStrategy : public CurePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class MageCurePveStrategy : public CurePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 法师驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class MageCureRaidStrategy : public CureRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };
}
