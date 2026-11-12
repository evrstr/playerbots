#pragma once
#include "Strategy.h"

namespace ai
{
    /// 数据库驱动的自定义策略类，支持按玩家或全局配置动态加载触发器-动作规则
    class CustomStrategy : public Strategy, public Qualified
    {
    public:
        CustomStrategy(PlayerbotAI* ai) : Strategy(ai), Qualified() {}
        std::string getName() override { return "custom::" + qualifier; }
        void Reset();

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;

        void LoadActionLines(uint32 owner);

    private:
        std::list<std::string> actionLines;
    };
}
