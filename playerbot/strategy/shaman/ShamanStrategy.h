// 萨满祭司 - 萨满祭司策略头文件 (ShamanStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 萨满祭司图腾专精占位策略：用于专精识别与占位的策略类
    class ShamanTotemsPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        ShamanTotemsPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "totems"; }
    };

    // 萨满祭司策略：定义该专精/场景下的触发器与默认行为
    class ShamanStrategy : public ClassStrategy
    {
    public:
        ShamanStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司PVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanPvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司PVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanPveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司AOE群体策略：定义该专精/场景下的触发器与默认行为
    class ShamanAoeStrategy : public AoeStrategy
    {
    public:
        ShamanAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class ShamanCcStrategy : public CcStrategy
    {
    public:
        ShamanCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司增益Buff策略：定义该专精/场景下的触发器与默认行为
    class ShamanBuffStrategy : public BuffStrategy
    {
    public:
        ShamanBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司爆发增益策略：定义该专精/场景下的触发器与默认行为
    class ShamanBoostStrategy : public BoostStrategy
    {
    public:
        ShamanBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司驱散净化策略：定义该专精/场景下的触发器与默认行为
    class ShamanCureStrategy : public CureStrategy
    {
    public:
        ShamanCureStrategy(PlayerbotAI* ai) : CureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanCurePvpStrategy : public CurePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanCurePveStrategy : public CurePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanCureRaidStrategy : public CureRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司辅助治疗策略：定义该专精/场景下的触发器与默认行为
    class ShamanOffhealStrategy : public OffhealStrategy
    {
    public:
        ShamanOffhealStrategy(PlayerbotAI* ai) : OffhealStrategy(ai) {}

    protected:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司辅助治疗PVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanOffhealPvpStrategy : public ShamanOffhealStrategy
    {
    public:
        ShamanOffhealPvpStrategy(PlayerbotAI* ai) : ShamanOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司辅助治疗PVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanOffhealPveStrategy : public ShamanOffhealStrategy
    {
    public:
        ShamanOffhealPveStrategy(PlayerbotAI* ai) : ShamanOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司辅助治疗团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanOffhealRaidStrategy : public ShamanOffhealStrategy
    {
    public:
        ShamanOffhealRaidStrategy(PlayerbotAI* ai) : ShamanOffhealStrategy(ai) {}
        std::string getName() override { return "offheal raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司图腾策略：定义该专精/场景下的触发器与默认行为
    class ShamanTotemsStrategy : public Strategy
    {
    public:
        ShamanTotemsStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司图腾PVP策略：定义该专精/场景下的触发器与默认行为
    class ShamanTotemsPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司图腾PVE策略：定义该专精/场景下的触发器与默认行为
    class ShamanTotemsPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司图腾团队副本策略：定义该专精/场景下的触发器与默认行为
    class ShamanTotemsRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 萨满祭司图腾动作条元素策略：定义该专精/场景下的触发器与默认行为
    class ShamanTotemBarElementsStrategy : public Strategy
    {
    public:
        ShamanTotemBarElementsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "totembar elements"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司图腾动作条先祖策略：定义该专精/场景下的触发器与默认行为
    class ShamanTotemBarAncestorsStrategy : public Strategy
    {
    public:
        ShamanTotemBarAncestorsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "totembar ancestors"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司图腾动作条灵魂策略：定义该专精/场景下的触发器与默认行为
    class ShamanTotemBarSpiritsStrategy : public Strategy
    {
    public:
        ShamanTotemBarSpiritsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "totembar spirits"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 萨满祭司手动图腾策略：定义该专精/场景下的触发器与默认行为
    class ShamanManualTotemStrategy : public Strategy
    {
    public:
        ShamanManualTotemStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName) 
        : Strategy(ai) 
        , name(inName)
        , triggerName(inTriggerName)
        , actionName(inActionName) {}

        std::string getName() override { return name; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;

    private:
        std::string name;
        std::string triggerName;
        std::string actionName;
    };
}
