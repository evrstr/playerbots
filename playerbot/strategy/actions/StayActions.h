#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"

namespace ai
{
    /// 停留动作基类：封装让机器人停止移动或坐下休息的通用逻辑
    class StayActionBase : public MovementAction 
    {
    public:
        /// 构造函数：初始化停留动作基类
        StayActionBase(PlayerbotAI* ai, std::string name) : MovementAction(ai, name) {}

    protected:
        /// 停止机器人当前所有移动并保持原地待命
        bool Stay(Player* requester);
    };

    /// 原地待命动作：停止机器人当前所有移动并保持原地站立
    class StayAction : public StayActionBase 
    {
    public:
        /// 构造函数：初始化原地待命动作
        StayAction(PlayerbotAI* ai) : StayActionBase(ai, "stay") {}
        /// 执行动作主逻辑（原地待命动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（原地待命动作）
        virtual bool isUseful() override;
    };

    /// 坐下休息动作：在非战斗空闲状态下让机器人坐下恢复或等待
    class SitAction : public StayActionBase 
    {
    public:
        /// 构造函数：初始化坐下休息动作
        SitAction(PlayerbotAI* ai) : StayActionBase(ai, "sit") {}
        /// 执行动作主逻辑（坐下休息动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（坐下休息动作）
        virtual bool isUseful() override;
    };
}
