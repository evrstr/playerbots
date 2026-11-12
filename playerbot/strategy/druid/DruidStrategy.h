// 德鲁伊 - 德鲁伊策略头文件 (DruidStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ClassStrategy.h"

namespace ai
{
    // 德鲁伊策略：定义该专精/场景下的触发器与默认行为
    class DruidStrategy : public ClassStrategy
    {
    public:
        DruidStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊PVP策略：定义该专精/场景下的触发器与默认行为
    class DruidPvpStrategy : public ClassPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊PVE策略：定义该专精/场景下的触发器与默认行为
    class DruidPveStrategy : public ClassPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidRaidStrategy : public ClassRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊AOE群体策略：定义该专精/场景下的触发器与默认行为
    class DruidAoeStrategy : public AoeStrategy
    {
    public:
        DruidAoeStrategy(PlayerbotAI* ai) : AoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class DruidAoePvpStrategy : public AoePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class DruidAoePveStrategy : public AoePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidAoeRaidStrategy : public AoeRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class DruidCcStrategy : public CcStrategy
    {
    public:
        DruidCcStrategy(PlayerbotAI* ai) : CcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class DruidCcPvpStrategy : public CcPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class DruidCcPveStrategy : public CcPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidCcRaidStrategy : public CcRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊增益Buff策略：定义该专精/场景下的触发器与默认行为
    class DruidBuffStrategy : public BuffStrategy
    {
    public:
        DruidBuffStrategy(PlayerbotAI* ai) : BuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class DruidBuffPvpStrategy : public BuffPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class DruidBuffPveStrategy : public BuffPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidBuffRaidStrategy : public BuffRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊爆发增益策略：定义该专精/场景下的触发器与默认行为
    class DruidBoostStrategy : public BoostStrategy
    {
    public:
        DruidBoostStrategy(PlayerbotAI* ai) : BoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class DruidBoostPvpStrategy : public BoostPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class DruidBoostPveStrategy : public BoostPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidBoostRaidStrategy : public BoostRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊驱散净化策略：定义该专精/场景下的触发器与默认行为
    class DruidCureStrategy : public CureStrategy
    {
    public:
        DruidCureStrategy(PlayerbotAI* ai) : CureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class DruidCurePvpStrategy : public CurePvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class DruidCurePveStrategy : public CurePveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidCureRaidStrategy : public CureRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // 德鲁伊辅助治疗策略：定义该专精/场景下的触发器与默认行为
    class DruidOffhealStrategy : public OffhealStrategy
    {
    public:
        DruidOffhealStrategy(PlayerbotAI* ai) : OffhealStrategy(ai) {}

    protected:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊辅助治疗PVP策略：定义该专精/场景下的触发器与默认行为
    class DruidOffhealPvpStrategy : public DruidOffhealStrategy
    {
    public:
        DruidOffhealPvpStrategy(PlayerbotAI* ai) : DruidOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊辅助治疗PVE策略：定义该专精/场景下的触发器与默认行为
    class DruidOffhealPveStrategy : public DruidOffhealStrategy
    {
    public:
        DruidOffhealPveStrategy(PlayerbotAI* ai) : DruidOffhealStrategy(ai) {}
        std::string getName() override { return "offheal pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊辅助治疗团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidOffhealRaidStrategy : public DruidOffhealStrategy
    {
    public:
        DruidOffhealRaidStrategy(PlayerbotAI* ai) : DruidOffhealStrategy(ai) {}
        std::string getName() override { return "offheal raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊辅助输出策略：定义该专精/场景下的触发器与默认行为
    class DruidOffdpsStrategy : public OffdpsStrategy
    {
    public:
        DruidOffdpsStrategy(PlayerbotAI* ai) : OffdpsStrategy(ai) {}

    protected:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊辅助输出PVP策略：定义该专精/场景下的触发器与默认行为
    class DruidOffdpsPvpStrategy : public DruidOffdpsStrategy
    {
    public:
        DruidOffdpsPvpStrategy(PlayerbotAI* ai) : DruidOffdpsStrategy(ai) {}
        std::string getName() override { return "offdps pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊辅助输出PVE策略：定义该专精/场景下的触发器与默认行为
    class DruidOffdpsPveStrategy : public DruidOffdpsStrategy
    {
    public:
        DruidOffdpsPveStrategy(PlayerbotAI* ai) : DruidOffdpsStrategy(ai) {}
        std::string getName() override { return "offdps pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 德鲁伊辅助输出团队副本策略：定义该专精/场景下的触发器与默认行为
    class DruidOffdpsRaidStrategy : public DruidOffdpsStrategy
    {
    public:
        DruidOffdpsRaidStrategy(PlayerbotAI* ai) : DruidOffdpsStrategy(ai) {}
        std::string getName() override { return "offdps raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
