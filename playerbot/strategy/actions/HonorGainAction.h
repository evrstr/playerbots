#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 荣誉击杀处理动作：监听并播报机器人获得荣誉击杀或荣誉点数事件
    class HonorGainAction : public Action
    {
    public:
        /// 构造函数：初始化荣誉击杀处理动作
        HonorGainAction(PlayerbotAI* ai) : Action(ai, "honor gain") {}
        /// 执行动作主逻辑（荣誉击杀处理动作）
        virtual bool Execute(Event& event) override;
    };
}
