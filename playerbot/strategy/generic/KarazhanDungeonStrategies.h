/// 卡拉赞（Karazhan）团队副本及首领策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

    /// 埃兰之影战斗阶段枚举
enum class AranPhase : uint8
{
    PHASE_NONE = 1,
    PHASE_ARCANE = 2,
    PHASE_FIRE = 3,
    PHASE_FROST = 4
};

namespace ai
{
    /// 策略：卡拉赞副本总控策略，负责监测并启用各首领专项策略
    class KarazhanDungeonStrategy : public Strategy
    {
    public:
        KarazhanDungeonStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "karazhan"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：虚空幽龙（Netherspite）战斗策略（虚空地带规避与三色射线管理）
    class NetherspiteFightStrategy : public Strategy
    {
    public:
        NetherspiteFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        static NetherspiteFightStrategy* Get(PlayerbotAI* ai);
        void SetBossGuid(ObjectGuid guid) { netherspiteGuid = guid; }
        ObjectGuid GetBossGuid() { return netherspiteGuid; }
        std::string getName() override { return "netherspite"; }
    private:
        ObjectGuid netherspiteGuid;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
        void OnStrategyAdded(BotState state) override;
    };

    /// 策略：埃兰之影（Shade of Aran）战斗策略（奥/火/冰阶段走位与水元素处理）
    class ShadeOfAranFightStrategy : public Strategy
    {
    public:
        ShadeOfAranFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        static ShadeOfAranFightStrategy* Get(PlayerbotAI* ai);
        void SetPhase(AranPhase phase) { currentPhase = phase; }
        AranPhase GetPhase() { return currentPhase; }
        void SetBossGuid(ObjectGuid guid) { aranGuid = guid; }
        ObjectGuid GetBossGuid() { return aranGuid; }
        void SetRangedBot(bool isRanged) { rangedBot = isRanged; }
        bool GetRangedBot() { return rangedBot; }
        void SetElementals(bool isOut) { elementalsOut = isOut; }
        bool GetElementals() { return elementalsOut; }
        std::string getName() override { return "shade of aran"; }
    private:
        ObjectGuid aranGuid;
        AranPhase currentPhase;
        bool rangedBot;
        bool elementalsOut;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*> &triggers) override;
        void OnStrategyAdded(BotState state) override;
    };
  
    /// 策略：歌剧院大灰狼战斗策略（小红帽风筝走位）
    class BigBadWolfFightStrategy : public Strategy
    {
    public:
        BigBadWolfFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "big bad wolf"; }
    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：玛克扎尔王子战斗策略（地狱火规避、虚弱散开与暗影新星躲避）
    class PrinceMalchezaarFightStrategy : public Strategy
    {
    public:
        PrinceMalchezaarFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "prince malchezaar"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };
}