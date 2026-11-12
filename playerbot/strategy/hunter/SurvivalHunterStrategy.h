// 猎人 - 生存猎人策略头文件 (SurvivalHunterStrategy.h)
#pragma once
#include "HunterStrategy.h"

namespace ai
{
    // 生存猎人专精占位策略：用于专精识别与占位的策略类
    class SurvivalHunterPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        SurvivalHunterPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "survival"; }
    };

    // 生存猎人策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterStrategy : public HunterStrategy
    {
    public:
        SurvivalHunterStrategy(PlayerbotAI* ai) : HunterStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人PVE策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterPveStrategy : public SurvivalHunterStrategy
    {
    public:
        SurvivalHunterPveStrategy(PlayerbotAI* ai) : SurvivalHunterStrategy(ai) {}
        std::string getName() override { return "survival pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人PVP策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterPvpStrategy : public SurvivalHunterStrategy
    {
    public:
        SurvivalHunterPvpStrategy(PlayerbotAI* ai) : SurvivalHunterStrategy(ai) {}
        std::string getName() override { return "survival pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人团队副本策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterRaidStrategy : public SurvivalHunterStrategy
    {
    public:
        SurvivalHunterRaidStrategy(PlayerbotAI* ai) : SurvivalHunterStrategy(ai) {}
        std::string getName() override { return "survival raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人AOE群体策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAoeStrategy : public HunterAoeStrategy
    {
    public:
        SurvivalHunterAoeStrategy(PlayerbotAI* ai) : HunterAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAoePveStrategy : public SurvivalHunterAoeStrategy
    {
    public:
        SurvivalHunterAoePveStrategy(PlayerbotAI* ai) : SurvivalHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe survival pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAoePvpStrategy : public SurvivalHunterAoeStrategy
    {
    public:
        SurvivalHunterAoePvpStrategy(PlayerbotAI* ai) : SurvivalHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe survival pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAoeRaidStrategy : public SurvivalHunterAoeStrategy
    {
    public:
        SurvivalHunterAoeRaidStrategy(PlayerbotAI* ai) : SurvivalHunterAoeStrategy(ai) {}
        std::string getName() override { return "aoe survival raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人增益Buff策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBuffStrategy : public HunterBuffStrategy
    {
    public:
        SurvivalHunterBuffStrategy(PlayerbotAI* ai) : HunterBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBuffPveStrategy : public SurvivalHunterBuffStrategy
    {
    public:
        SurvivalHunterBuffPveStrategy(PlayerbotAI* ai) : SurvivalHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff survival pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBuffPvpStrategy : public SurvivalHunterBuffStrategy
    {
    public:
        SurvivalHunterBuffPvpStrategy(PlayerbotAI* ai) : SurvivalHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff survival pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBuffRaidStrategy : public SurvivalHunterBuffStrategy
    {
    public:
        SurvivalHunterBuffRaidStrategy(PlayerbotAI* ai) : SurvivalHunterBuffStrategy(ai) {}
        std::string getName() override { return "buff survival raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人爆发增益策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBoostStrategy : public HunterBoostStrategy
    {
    public:
        SurvivalHunterBoostStrategy(PlayerbotAI* ai) : HunterBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBoostPveStrategy : public SurvivalHunterBoostStrategy
    {
    public:
        SurvivalHunterBoostPveStrategy(PlayerbotAI* ai) : SurvivalHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost survival pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBoostPvpStrategy : public SurvivalHunterBoostStrategy
    {
    public:
        SurvivalHunterBoostPvpStrategy(PlayerbotAI* ai) : SurvivalHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost survival pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterBoostRaidStrategy : public SurvivalHunterBoostStrategy
    {
    public:
        SurvivalHunterBoostRaidStrategy(PlayerbotAI* ai) : SurvivalHunterBoostStrategy(ai) {}
        std::string getName() override { return "boost survival raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterCcStrategy : public HunterCcStrategy
    {
    public:
        SurvivalHunterCcStrategy(PlayerbotAI* ai) : HunterCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterCcPveStrategy : public SurvivalHunterCcStrategy
    {
    public:
        SurvivalHunterCcPveStrategy(PlayerbotAI* ai) : SurvivalHunterCcStrategy(ai) {}
        std::string getName() override { return "cc survival pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterCcPvpStrategy : public SurvivalHunterCcStrategy
    {
    public:
        SurvivalHunterCcPvpStrategy(PlayerbotAI* ai) : SurvivalHunterCcStrategy(ai) {}
        std::string getName() override { return "cc survival pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterCcRaidStrategy : public SurvivalHunterCcStrategy
    {
    public:
        SurvivalHunterCcRaidStrategy(PlayerbotAI* ai) : SurvivalHunterCcStrategy(ai) {}
        std::string getName() override { return "cc survival raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人钉刺策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterStingStrategy : public HunterStingStrategy
    {
    public:
        SurvivalHunterStingStrategy(PlayerbotAI* ai) : HunterStingStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人钉刺PVE策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterStingPveStrategy : public SurvivalHunterStingStrategy
    {
    public:
        SurvivalHunterStingPveStrategy(PlayerbotAI* ai) : SurvivalHunterStingStrategy(ai) {}
        std::string getName() override { return "sting survival pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人钉刺PVP策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterStingPvpStrategy : public SurvivalHunterStingStrategy
    {
    public:
        SurvivalHunterStingPvpStrategy(PlayerbotAI* ai) : SurvivalHunterStingStrategy(ai) {}
        std::string getName() override { return "sting survival pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人钉刺团队副本策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterStingRaidStrategy : public SurvivalHunterStingStrategy
    {
    public:
        SurvivalHunterStingRaidStrategy(PlayerbotAI* ai) : SurvivalHunterStingStrategy(ai) {}
        std::string getName() override { return "sting survival raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人守护策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAspectStrategy : public HunterAspectStrategy
    {
    public:
        SurvivalHunterAspectStrategy(PlayerbotAI* ai) : HunterAspectStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人守护PVE策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAspectPveStrategy : public SurvivalHunterAspectStrategy
    {
    public:
        SurvivalHunterAspectPveStrategy(PlayerbotAI* ai) : SurvivalHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect survival pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人守护PVP策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAspectPvpStrategy : public SurvivalHunterAspectStrategy
    {
    public:
        SurvivalHunterAspectPvpStrategy(PlayerbotAI* ai) : SurvivalHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect survival pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 生存猎人守护团队副本策略：定义该专精/场景下的触发器与默认行为
    class SurvivalHunterAspectRaidStrategy : public SurvivalHunterAspectStrategy
    {
    public:
        SurvivalHunterAspectRaidStrategy(PlayerbotAI* ai) : SurvivalHunterAspectStrategy(ai) {}
        std::string getName() override { return "aspect survival raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
