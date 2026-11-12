#pragma once

namespace ai
{
    /// 记录飞行点动作：与飞行管理员交互或路过时解锁并记录新发现的飞行点
    class RememberTaxiAction : public Action {
    public:
        /// 构造函数：初始化记录飞行点动作
        RememberTaxiAction(PlayerbotAI* ai) : Action(ai, "remember taxi") {}

    public:
        /// 执行动作主逻辑（记录飞行点动作）
        virtual bool Execute(Event& event) override;
    };

}
