#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 前往旅行目标动作：控制机器人沿长途路径或传送门向旅行目的地行进
    class MoveToTravelTargetAction : public MovementAction {
    public:
        /// 构造函数：初始化前往旅行目标动作
        MoveToTravelTargetAction(PlayerbotAI* ai) : MovementAction(ai, "move to travel target") {}

        /// 执行动作主逻辑（前往旅行目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（前往旅行目标动作）
        virtual bool isUseful() override;
    };

}
