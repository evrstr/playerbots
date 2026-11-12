#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 背包操作失败通知动作：处理装备或背包变更失败的错误码并反馈给主人
    class InventoryChangeFailureAction : public Action {
    public:
        /// 构造函数：初始化背包操作失败通知动作
        InventoryChangeFailureAction(PlayerbotAI* ai) : Action(ai, "inventory change failure") {}
        /// 执行动作主逻辑（背包操作失败通知动作）
        virtual bool Execute(Event& event) override;

    private:
        static std::map<InventoryResult, std::string> messages;
    };
}
