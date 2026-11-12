#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{

    /// 设置避让区域动作：添加、清除或查看机器人寻路时需避开的危险坐标区域
    class SetAvoidAreaAction : public Action
    {
    public:
        /// 构造函数：初始化设置避让区域动作
        SetAvoidAreaAction(PlayerbotAI* ai) : Action(ai, "set avoid area") {};
        /// 执行动作主逻辑（设置避让区域动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（设置避让区域动作）
        virtual bool isUseful() override;
    };
}
