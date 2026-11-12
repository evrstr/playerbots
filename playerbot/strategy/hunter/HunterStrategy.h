// 猎人 - 猎人策略头文件 (HunterStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 猎人钉刺专精占位策略：用于专精识别与占位的策略类
    class HunterStingPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        HunterStingPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "sting"; }
    };

    // 猎人守护专精占位策略：用于专精识别与占位的策略类
    class HunterAspectPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        HunterAspectPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "aspect"; }
    };

    // 猎人策略：定义该专精/场景下的触发器与默认行为
    class HunterStrategy : public ClassStrategy
    {
    public:
        HunterStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 猎人PVP策略：定义该专精/场景下的触发器与默认行为
    class HunterPvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人PVE策略：定义该专精/场景下的触发器与默认行为
    class HunterPveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人团队副本策略：定义该专精/场景下的触发器与默认行为
    class HunterRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人AOE群体策略：定义该专精/场景下的触发器与默认行为
    class HunterAoeStrategy : public AoeStrategy
    {
    public:
        HunterAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 猎人AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class HunterAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class HunterAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class HunterAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人增益Buff策略：定义该专精/场景下的触发器与默认行为
    class HunterBuffStrategy : public BuffStrategy
    {
    public:
        HunterBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 猎人增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class HunterBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class HunterBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class HunterBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人爆发增益策略：定义该专精/场景下的触发器与默认行为
    class HunterBoostStrategy : public BoostStrategy
    {
    public:
        HunterBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 猎人爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class HunterBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class HunterBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class HunterBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class HunterCcStrategy : public CcStrategy
    {
    public:
        HunterCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 猎人控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class HunterCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class HunterCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class HunterCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人钉刺策略：定义该专精/场景下的触发器与默认行为
    class HunterStingStrategy : public Strategy
    {
    public:
        HunterStingStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 猎人钉刺PVP策略：定义该专精/场景下的触发器与默认行为
    class HunterStingPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人钉刺PVE策略：定义该专精/场景下的触发器与默认行为
    class HunterStingPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人钉刺团队副本策略：定义该专精/场景下的触发器与默认行为
    class HunterStingRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人手动钉刺策略：定义该专精/场景下的触发器与默认行为
    class HunterManualStingStrategy : public Strategy
    {
    public:
        HunterManualStingStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName)
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

    // 猎人守护策略：定义该专精/场景下的触发器与默认行为
    class HunterAspectStrategy : public Strategy
    {
    public:
        HunterAspectStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 猎人守护PVP策略：定义该专精/场景下的触发器与默认行为
    class HunterAspectPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人守护PVE策略：定义该专精/场景下的触发器与默认行为
    class HunterAspectPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人守护团队副本策略：定义该专精/场景下的触发器与默认行为
    class HunterAspectRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 猎人手动守护策略：定义该专精/场景下的触发器与默认行为
    class HunterManualAspectStrategy : public Strategy
    {
    public:
        HunterManualAspectStrategy(PlayerbotAI* ai, std::string inName, std::string inTriggerName, std::string inActionName)
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

    // 猎人宠物策略：定义该专精/场景下的触发器与默认行为
    class HunterPetStrategy : public Strategy
    {
    public:
        HunterPetStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "pet"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
