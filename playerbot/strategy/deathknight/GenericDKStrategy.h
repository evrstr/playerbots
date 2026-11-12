// 死亡骑士 - 通用死亡骑士战斗策略头文件 (GenericDKStrategy.h)
#pragma once
#include "playerbot/strategy/generic/MeleeCombatStrategy.h"

namespace ai
{
    // 通用死亡骑士战斗策略：定义该专精/场景下的触发器与默认行为
    class GenericDKStrategy : public CombatStrategy
    {
    public:
        GenericDKStrategy(PlayerbotAI* ai);
        virtual std::string getName() override { return "DK"; }

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
