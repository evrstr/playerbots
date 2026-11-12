// 死亡骑士 - 邪恶死亡骑士策略头文件 (UnholyDKStrategy.h)
#pragma once
#include "GenericDKStrategy.h"

namespace ai
{
    // 邪恶死亡骑士策略：定义该专精/场景下的触发器与默认行为
    class UnholyDKStrategy : public GenericDKStrategy
    {
    public:
        UnholyDKStrategy(PlayerbotAI* ai) : GenericDKStrategy(ai) {}
        std::string getName() override { return "unholy"; }
        int GetType() override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        NextAction** GetDefaultCombatActions() override;
        
    };

    // 邪恶死亡骑士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class UnholyDKAoeStrategy : public CombatStrategy
    {
    public:
        UnholyDKAoeStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        std::string getName() override { return "unholy aoe"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
