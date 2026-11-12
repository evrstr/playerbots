/// 大世界智能旅行与探索策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 乘数：协调旅行目标请求与执行之间的互斥屏蔽
    class TravelActionMultiplier : public Multiplier
    {
    public:
        TravelActionMultiplier(PlayerbotAI* ai) : Multiplier(ai, "travel action") {}

    public:
        virtual float GetValue(Action* action) override;
    };

    /// 策略：驱动自主机器人在世界范围选择练级、任务、商人、银行等旅行目的地并前往
    class TravelStrategy : public Strategy
    {
    public:
        TravelStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "travel"; }

    public:
        void InitNonCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
        NextAction** GetDefaultNonCombatActions() override;
    };

    /// 策略：执行单次预设旅行目标的移动策略（不自动续接新目标）
    class TravelOnceStrategy : public Strategy
    {
    public:
        TravelOnceStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        std::string getName() override { return "travel once"; }
    };

    /// 策略：允许机器人在旅行中顺路探索未知区域与地图
    class ExploreStrategy : public Strategy
    {
    public:
        ExploreStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "explore"; }
    };

    /// 策略：记录已探索地图区域标记
    class MapStrategy : public Strategy
    {
    public:
        MapStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "map"; }
    };

    /// 策略：全图探索模式标记
    class MapFullStrategy : public Strategy
    {
    public:
        MapFullStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "map full"; }
    };
}
