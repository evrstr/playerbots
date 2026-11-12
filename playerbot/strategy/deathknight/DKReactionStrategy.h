// 死亡骑士 - 死亡骑士战斗反应策略头文件 (DKReactionStrategy.h)
#pragma once
#include "playerbot/strategy/generic/ReactionStrategy.h"

namespace ai
{
    // 死亡骑士战斗反应策略：定义该专精/场景下的触发器与默认行为
    class DKReactionStrategy : public ReactionStrategy
    {
    public:
        DKReactionStrategy(PlayerbotAI* ai) : ReactionStrategy(ai) {}
        std::string getName() override { return "react"; }

    private:
        void InitReactionTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
