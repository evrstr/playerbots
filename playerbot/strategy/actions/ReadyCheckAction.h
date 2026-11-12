#pragma once
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 响应就位确认动作：收到团队就位确认时检查各项状态并回复准备结果
    class ReadyCheckAction : public Action
    {
    public:
        /// 构造函数：初始化响应就位确认动作
        ReadyCheckAction(PlayerbotAI* ai, std::string name = "ready check") : Action(ai, name) {}
        /// 执行动作主逻辑（响应就位确认动作）
        virtual bool Execute(Event& event) override;

    protected:
        /// 遍历并执行当前就位确认检查项的检测逻辑
        bool ReadyCheck(Player* requester);
    };

    /// 完成就位确认动作：处理就位检查收尾并汇总报告未就位原因
    class FinishReadyCheckAction : public ReadyCheckAction
    {
    public:
        /// 构造函数：初始化完成就位确认动作
        FinishReadyCheckAction(PlayerbotAI* ai) : ReadyCheckAction(ai, "finish ready check") {}
        /// 执行动作主逻辑（完成就位确认动作）
        virtual bool Execute(Event& event) override;
    };
}
