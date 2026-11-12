/// 拉怪（Pull）、防 Add 与拉怪归位策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"
#include "playerbot/strategy/Multiplier.h"

namespace ai
{
    /// 策略：由坦克或指定拉怪手使用远程技能安全引怪
    class PullStrategy : public Strategy
    {
    public:
        PullStrategy(PlayerbotAI* ai, std::string pullAction, std::string prePullAction = "");

    public:
        std::string getName() override { return "pull"; }

        static PullStrategy* Get(PlayerbotAI* ai);
        static uint8 GetMaxPullTime() { return 15; }
        const time_t& GetPullStartTime() const { return pullStartTime; }
        
        bool CanDoPullAction(Unit* target);

        Unit* GetTarget() const;
        bool HasTarget() const { return GetTarget() != nullptr; }

        std::string GetPullActionName() const;
        std::string GetSpellName() const;
        float GetRange() const;

        std::string GetPreActionName() const;

        void RequestPull(Unit* target, bool resetTime = true);
        bool IsPullPendingToStart() const { return pendingToStart; }
        bool HasPullStarted() const { return pullStartTime > 0; }
        void OnPullStarted();
        void OnPullEnded();
        ReactStates GetPetReactState() const { return petReactState; }
        void SetPetReactState(ReactStates reactState) { petReactState = reactState; }

    private:
        void SetTarget(Unit* target);

        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitNonCombatMultipliers(std::list<Multiplier*>& multipliers) override;

    private:
        std::string pullActionName; //shoot | 默认拉怪动作（如 shoot）
        std::string preActionName;
        bool pendingToStart;
        time_t pullStartTime;
        ReactStates petReactState;
    };

    /// 乘数：在拉怪执行阶段屏蔽非拉怪相关动作
    class PullMultiplier : public Multiplier
    {
    public:
        PullMultiplier(PlayerbotAI* ai) : Multiplier(ai, "pull") {}

    public:
        float GetValue(Action* action) override;
    };

    /// 策略：警戒周围潜在巡逻怪物并适时躲避（ads）
    class PossibleAddsStrategy : public Strategy
    {
    public:
        PossibleAddsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "ads"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：引怪后自动跑回预设拉怪锚点位置（pull back）
    class PullBackStrategy : public Strategy
    {
    public:
        PullBackStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "pull back"; }

        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
