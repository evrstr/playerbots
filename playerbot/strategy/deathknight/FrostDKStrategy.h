// 死亡骑士 - 冰霜死亡骑士策略头文件 (FrostDKStrategy.h)
#pragma once
#include "GenericDKStrategy.h"

namespace ai
{
    // 冰霜死亡骑士策略：定义该专精/场景下的触发器与默认行为
    class FrostDKStrategy : public GenericDKStrategy
    {
    public:
        FrostDKStrategy(PlayerbotAI* ai);
        std::string getName() override { return "frost"; }
        int GetType() override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        NextAction** GetDefaultCombatActions() override;
    };

    // 冰霜死亡骑士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class FrostDKAoeStrategy : public CombatStrategy
    {
    public:
        FrostDKAoeStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        std::string getName() override { return "frost aoe"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
