#pragma once
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 移除指定光环动作：主动取消机器人身上指定的增益或状态光环
    class RemoveAuraAction : public Action
    {
    public:
        /// 构造函数：初始化移除指定光环动作
        RemoveAuraAction(PlayerbotAI* ai, std::string aura = "") : Action(ai, aura.empty() ? "ra" : "remove" + aura), aura(aura) {}
        /// 执行动作主逻辑（移除指定光环动作）
        virtual bool Execute(Event& event) override;

    private:
        std::string aura;
    };
}
