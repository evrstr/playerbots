#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 飞行路线指令动作：与飞行管理员交互、查询已解锁航线或乘骑飞行坐骑前往目的地
    class TaxiAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化飞行路线指令动作
        TaxiAction(PlayerbotAI* ai) : ChatCommandAction(ai, "taxi") {}
        /// 执行动作主逻辑（飞行路线指令动作）
        virtual bool Execute(Event& event) override;
    };
}
