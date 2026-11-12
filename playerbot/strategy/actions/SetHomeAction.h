#pragma once
#include "MovementActions.h"

namespace ai
{
    /// 绑定炉石点动作：寻找附近旅店老板并将炉石绑定到当前旅店
    class SetHomeAction : public MovementAction 
    {
    public:
        /// 构造函数：初始化绑定炉石点动作
        SetHomeAction(PlayerbotAI* ai) : MovementAction(ai, "home") {}
        /// 执行动作主逻辑（绑定炉石点动作）
        virtual bool Execute(Event& event) override;
    };
}
