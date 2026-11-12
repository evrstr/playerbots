// 死亡骑士 - 通用死亡骑士非战斗策略头文件 (GenericDKNonCombatStrategy.h)
#pragma once
#include "playerbot/strategy/generic/NonCombatStrategy.h"

namespace ai
{
    // 通用死亡骑士非战斗策略：定义该专精/场景下的触发器与默认行为
    class GenericDKNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericDKNonCombatStrategy(PlayerbotAI* ai);
        std::string getName() override { return "nc"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    // 死亡骑士增益Buff输出策略：定义该专精/场景下的触发器与默认行为
    class DKBuffDpsStrategy : public Strategy
    {
    public:
        DKBuffDpsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "bdps"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

// 死亡骑士新手起始任务策略：定义该专精/场景下的触发器与默认行为
class DKStartQuestStrategy : public Strategy
    {
    public:
        DKStartQuestStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "dksquest"; }
    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override {}
    };
}
