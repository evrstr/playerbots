#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/AiFactory.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    /// 进入载具动作：靠近可用载具或攻城器械并交互上车
    class EnterVehicleAction : public MovementAction
    {
    public:
        /// 构造函数：初始化进入载具动作
        EnterVehicleAction(PlayerbotAI* ai, std::string name = "enter vehicle") : MovementAction(ai, name) {}
        /// 执行动作主逻辑（进入载具动作）
        virtual bool Execute(Event& event) override;
        //virtual bool isUseful() override;
    };

    /// 离开载具动作：退出当前驾驶或乘坐的载具座位
    class LeaveVehicleAction : public MovementAction
    {
    public:
        /// 构造函数：初始化离开载具动作
        LeaveVehicleAction(PlayerbotAI* ai, std::string name = "leave vehicle") : MovementAction(ai, name) {}
        /// 执行动作主逻辑（离开载具动作）
        virtual bool Execute(Event& event) override;
        //virtual bool isUseful() override;
    };
}
