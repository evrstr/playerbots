// 死亡骑士 - 鲜血死亡骑士策略头文件 (BloodDKStrategy.h)
#pragma once
#include "GenericDKStrategy.h"

namespace ai
{
    // 鲜血死亡骑士策略：定义该专精/场景下的触发器与默认行为
    class BloodDKStrategy : public GenericDKStrategy
    {
    public:
        BloodDKStrategy(PlayerbotAI* ai);
        std::string getName() override { return "blood"; }
        int GetType() override { return STRATEGY_TYPE_TANK | STRATEGY_TYPE_MELEE; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        NextAction** GetDefaultCombatActions() override;
    };
}
