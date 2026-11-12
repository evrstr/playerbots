#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 揭示采集物动作：搜索附近矿脉、草药或交互物并向主人汇报位置
    class RevealGatheringItemAction : public Action {
    public:
        /// 构造函数：初始化揭示采集物动作
        RevealGatheringItemAction(PlayerbotAI* ai) : Action(ai, "reveal gathering item") {}

        /// 执行动作主逻辑（揭示采集物动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（揭示采集物动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

}
