#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 购买失败反馈动作：处理购买物品失败的封包并通知主人
    class BuyFailedAction : public Action {
    public:
        /// 构造函数：初始化购买失败反馈动作
        BuyFailedAction(PlayerbotAI* ai) : Action(ai, "buy failed") {}
        /// 执行动作主逻辑（购买失败反馈动作）
        virtual bool Execute(Event& event) override;

    private:
        static std::map<BuyResult, std::string> messages;
    };
}
