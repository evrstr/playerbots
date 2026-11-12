// 术士 - 术士策略头文件 (WarlockStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 术士宠物专精占位策略：用于专精识别与占位的策略类
    class WarlockPetPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        WarlockPetPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "pet"; }
    };

    // 术士诅咒专精占位策略：用于专精识别与占位的策略类
    class WarlockCursePlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        WarlockCursePlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "curse"; }
    };

    // 术士策略：定义该专精/场景下的触发器与默认行为
    class WarlockStrategy : public ClassStrategy
    {
    public:
        WarlockStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 术士PVP策略：定义该专精/场景下的触发器与默认行为
    class WarlockPvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士PVE策略：定义该专精/场景下的触发器与默认行为
    class WarlockPveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士团队副本策略：定义该专精/场景下的触发器与默认行为
    class WarlockRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class WarlockAoeStrategy : public AoeStrategy
    {
    public:
        WarlockAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 术士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class WarlockAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class WarlockAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class WarlockAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class WarlockBuffStrategy : public BuffStrategy
    {
    public:
        WarlockBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 术士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class WarlockBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class WarlockBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class WarlockBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class WarlockBoostStrategy : public BoostStrategy
    {
    public:
        WarlockBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 术士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class WarlockBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class WarlockBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class WarlockBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class WarlockCcStrategy : public CcStrategy
    {
    public:
        WarlockCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 术士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class WarlockCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class WarlockCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class WarlockCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士宠物策略：定义该专精/场景下的触发器与默认行为
    class WarlockPetStrategy : public Strategy
    {
    public:
        WarlockPetStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 术士宠物PVP策略：定义该专精/场景下的触发器与默认行为
    class WarlockPetPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士宠物PVE策略：定义该专精/场景下的触发器与默认行为
    class WarlockPetPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士宠物团队副本策略：定义该专精/场景下的触发器与默认行为
    class WarlockPetRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士诅咒策略：定义该专精/场景下的触发器与默认行为
    class WarlockCursesStrategy : public Strategy
    {
    public:
        WarlockCursesStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 术士诅咒PVP策略：定义该专精/场景下的触发器与默认行为
    class WarlockCursesPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士诅咒PVE策略：定义该专精/场景下的触发器与默认行为
    class WarlockCursesPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士诅咒团队副本策略：定义该专精/场景下的触发器与默认行为
    class WarlockCursesRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 术士手动宠物策略：定义该专精/场景下的触发器与默认行为
    class WarlockManualPetStrategy : public Strategy
    {
    public:
        WarlockManualPetStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName)
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

    // 术士手动诅咒策略：定义该专精/场景下的触发器与默认行为
    class WarlockManualCurseStrategy : public Strategy
    {
    public:
        WarlockManualCurseStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName)
        : Strategy(ai) 
        , name(inName)
        , triggerName(inTriggerName)
        , actionName(inActionName) {}

        std::string getName() override { return name; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;

    private:
        std::string name;
        std::string triggerName;
        std::string actionName;
    };
}
