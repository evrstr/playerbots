// 猎人 - 射击猎人策略头文件 (MarksmanshipHunterStrategy.h)
#pragma once
#include "HunterStrategy.h"

namespace ai
{
    // 射击猎人专精占位策略：用于专精识别与占位的策略类
    class MarksmanshipHunterPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        MarksmanshipHunterPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "marksmanship"; }
    };

    // 射击猎人策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterStrategy : public HunterStrategy
    {
    public:
        MarksmanshipHunterStrategy(PlayerbotAI* ai) : HunterStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人PVE策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterPveStrategy : public MarksmanshipHunterStrategy
    {
    public:
        MarksmanshipHunterPveStrategy(PlayerbotAI* ai) : MarksmanshipHunterStrategy(ai) {}
        std::string getName() override { return "marksmanship pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人PVP策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterPvpStrategy : public MarksmanshipHunterStrategy
    {
    public:
        MarksmanshipHunterPvpStrategy(PlayerbotAI* ai) : MarksmanshipHunterStrategy(ai) {}
        std::string getName() override { return "marksmanship pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人团队副本策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterRaidStrategy : public MarksmanshipHunterStrategy
    {
    public:
        MarksmanshipHunterRaidStrategy(PlayerbotAI* ai) : MarksmanshipHunterStrategy(ai) {}
        std::string getName() override { return "marksmanship raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人AOE群体策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAoeStrategy : public HunterAoeStrategy
    {
    public:
        MarksmanshipHunterAoeStrategy(PlayerbotAI* ai) : HunterAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAoePveStrategy : public MarksmanshipHunterAoeStrategy
    {
    public:
        MarksmanshipHunterAoePveStrategy(PlayerbotAI* ai) : MarksmanshipHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe marksmanship pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAoePvpStrategy : public MarksmanshipHunterAoeStrategy
    {
    public:
        MarksmanshipHunterAoePvpStrategy(PlayerbotAI* ai) : MarksmanshipHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe marksmanship pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAoeRaidStrategy : public MarksmanshipHunterAoeStrategy
    {
    public:
        MarksmanshipHunterAoeRaidStrategy(PlayerbotAI* ai) : MarksmanshipHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe marksmanship raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人增益Buff策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBuffStrategy : public HunterBuffStrategy
    {
    public:
        MarksmanshipHunterBuffStrategy(PlayerbotAI* ai) : HunterBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBuffPveStrategy : public MarksmanshipHunterBuffStrategy
    {
    public:
        MarksmanshipHunterBuffPveStrategy(PlayerbotAI* ai) : MarksmanshipHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff marksmanship pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBuffPvpStrategy : public MarksmanshipHunterBuffStrategy
    {
    public:
        MarksmanshipHunterBuffPvpStrategy(PlayerbotAI* ai) : MarksmanshipHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff marksmanship pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBuffRaidStrategy : public MarksmanshipHunterBuffStrategy
    {
    public:
        MarksmanshipHunterBuffRaidStrategy(PlayerbotAI* ai) : MarksmanshipHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff marksmanship raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人爆发增益策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBoostStrategy : public HunterBoostStrategy
    {
    public:
        MarksmanshipHunterBoostStrategy(PlayerbotAI* ai) : HunterBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBoostPveStrategy : public MarksmanshipHunterBoostStrategy
    {
    public:
        MarksmanshipHunterBoostPveStrategy(PlayerbotAI* ai) : MarksmanshipHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost marksmanship pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBoostPvpStrategy : public MarksmanshipHunterBoostStrategy
    {
    public:
        MarksmanshipHunterBoostPvpStrategy(PlayerbotAI* ai) : MarksmanshipHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost marksmanship pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterBoostRaidStrategy : public MarksmanshipHunterBoostStrategy
    {
    public:
        MarksmanshipHunterBoostRaidStrategy(PlayerbotAI* ai) : MarksmanshipHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost marksmanship raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterCcStrategy : public HunterCcStrategy
    {
    public:
        MarksmanshipHunterCcStrategy(PlayerbotAI* ai) : HunterCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterCcPveStrategy : public MarksmanshipHunterCcStrategy
    {
    public:
        MarksmanshipHunterCcPveStrategy(PlayerbotAI* ai) : MarksmanshipHunterCcStrategy(ai) {}
        std::string getName() override { return "cc marksmanship pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterCcPvpStrategy : public MarksmanshipHunterCcStrategy
    {
    public:
        MarksmanshipHunterCcPvpStrategy(PlayerbotAI* ai) : MarksmanshipHunterCcStrategy(ai) {}
        std::string getName() override { return "cc marksmanship pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterCcRaidStrategy : public MarksmanshipHunterCcStrategy
    {
    public:
        MarksmanshipHunterCcRaidStrategy(PlayerbotAI* ai) : MarksmanshipHunterCcStrategy(ai) {}
        std::string getName() override { return "cc marksmanship raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人钉刺策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterStingStrategy : public HunterStingStrategy
    {
    public:
        MarksmanshipHunterStingStrategy(PlayerbotAI* ai) : HunterStingStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人钉刺PVE策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterStingPveStrategy : public MarksmanshipHunterStingStrategy
    {
    public:
        MarksmanshipHunterStingPveStrategy(PlayerbotAI* ai) : MarksmanshipHunterStingStrategy(ai) {}
        std::string getName() override { return "sting marksmanship pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人钉刺PVP策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterStingPvpStrategy : public MarksmanshipHunterStingStrategy
    {
    public:
        MarksmanshipHunterStingPvpStrategy(PlayerbotAI* ai) : MarksmanshipHunterStingStrategy(ai) {}
        std::string getName() override { return "sting marksmanship pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人钉刺团队副本策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterStingRaidStrategy : public MarksmanshipHunterStingStrategy
    {
    public:
        MarksmanshipHunterStingRaidStrategy(PlayerbotAI* ai) : MarksmanshipHunterStingStrategy(ai) {}
        std::string getName() override { return "sting marksmanship raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人守护策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAspectStrategy : public HunterAspectStrategy
    {
    public:
        MarksmanshipHunterAspectStrategy(PlayerbotAI* ai) : HunterAspectStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人守护PVE策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAspectPveStrategy : public MarksmanshipHunterAspectStrategy
    {
    public:
        MarksmanshipHunterAspectPveStrategy(PlayerbotAI* ai) : MarksmanshipHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect marksmanship pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人守护PVP策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAspectPvpStrategy : public MarksmanshipHunterAspectStrategy
    {
    public:
        MarksmanshipHunterAspectPvpStrategy(PlayerbotAI* ai) : MarksmanshipHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect marksmanship pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 射击猎人守护团队副本策略：定义该专精/场景下的触发器与默认行为
    class MarksmanshipHunterAspectRaidStrategy : public MarksmanshipHunterAspectStrategy
    {
    public:
        MarksmanshipHunterAspectRaidStrategy(PlayerbotAI* ai) : MarksmanshipHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect marksmanship raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
