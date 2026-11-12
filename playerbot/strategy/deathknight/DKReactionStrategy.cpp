// 死亡骑士 - 死亡骑士战斗反应策略实现文件 (DKReactionStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DKReactionStrategy.h"

using namespace ai;

// 初始化反应阶段触发器列表 (死亡骑士战斗反应策略)
void DKReactionStrategy::InitReactionTriggers(std::list<TriggerNode*> &triggers)
{
    ReactionStrategy::InitReactionTriggers(triggers);

    // Add class specific reactions here
    // ...
}
