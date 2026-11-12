// 圣骑士 - 圣骑士策略头文件 (PaladinStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 圣骑士光环专精占位策略：用于专精识别与占位的策略类
    class PaladinAuraPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        PaladinAuraPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "aura"; }
    };

    // 圣骑士祝福专精占位策略：用于专精识别与占位的策略类
    class PaladinBlessingPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        PaladinBlessingPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "blessing"; }
    };

    // 圣骑士策略：定义该专精/场景下的触发器与默认行为
    class PaladinStrategy : public ClassStrategy
    {
    public:
        PaladinStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinPvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinPveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class PaladinAoeStrategy : public AoeStrategy
    {
    public:
        PaladinAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class PaladinCcStrategy : public CcStrategy
    {
    public:
        PaladinCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class PaladinBuffStrategy : public BuffStrategy
    {
    public:
        PaladinBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class PaladinBoostStrategy : public BoostStrategy
    {
    public:
        PaladinBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士驱散净化策略：定义该专精/场景下的触发器与默认行为
    class PaladinCureStrategy : public CureStrategy
    {
    public:
        PaladinCureStrategy(PlayerbotAI* ai) : CureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinCurePvpStrategy : public CurePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinCurePveStrategy : public CurePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinCureRaidStrategy : public CureRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士辅助治疗策略：定义该专精/场景下的触发器与默认行为
    class PaladinOffhealStrategy : public OffhealStrategy
    {
    public:
        PaladinOffhealStrategy(PlayerbotAI* ai) : OffhealStrategy(ai) {}

    protected:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士辅助治疗PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinOffhealPvpStrategy : public PaladinOffhealStrategy
    {
    public:
        PaladinOffhealPvpStrategy(PlayerbotAI* ai) : PaladinOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士辅助治疗PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinOffhealPveStrategy : public PaladinOffhealStrategy
    {
    public:
        PaladinOffhealPveStrategy(PlayerbotAI* ai) : PaladinOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士辅助治疗团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinOffhealRaidStrategy : public PaladinOffhealStrategy
    {
    public:
        PaladinOffhealRaidStrategy(PlayerbotAI* ai) : PaladinOffhealStrategy(ai) {}
        std::string getName() override { return "offheal raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士光环策略：定义该专精/场景下的触发器与默认行为
    class PaladinAuraStrategy : public Strategy
    {
    public:
        PaladinAuraStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士光环PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinAuraPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士光环PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinAuraPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士光环团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinAuraRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士祝福策略：定义该专精/场景下的触发器与默认行为
    class PaladinBlessingStrategy : public Strategy
    {
    public:
        PaladinBlessingStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 圣骑士祝福PVP策略：定义该专精/场景下的触发器与默认行为
    class PaladinBlessingPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士祝福PVE策略：定义该专精/场景下的触发器与默认行为
    class PaladinBlessingPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士祝福团队副本策略：定义该专精/场景下的触发器与默认行为
    class PaladinBlessingRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 圣骑士手动光环策略：定义该专精/场景下的触发器与默认行为
    class PaladinManualAuraStrategy : public Strategy
    {
    public:
        PaladinManualAuraStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName)
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

    // 圣骑士手动祝福策略：定义该专精/场景下的触发器与默认行为
    class PaladinManualBlessingStrategy : public Strategy
    {
    public:
        PaladinManualBlessingStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName)
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
}
