#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 全部修理指令动作：寻找附近修理商人并修理身上及背包中所有受损装备
    class RepairAllAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化全部修理指令动作
        RepairAllAction(PlayerbotAI* ai) : ChatCommandAction(ai, "repair") {}
        /// 执行动作主逻辑（全部修理指令动作）
        virtual bool Execute(Event& event) override;
    };
}
