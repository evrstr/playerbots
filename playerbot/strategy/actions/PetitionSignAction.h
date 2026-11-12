#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 签署公会登记表动作：响应公会签名请求并在符合条件时签署登记表
    class PetitionSignAction : public Action {
    public:
        /// 构造函数：初始化签署公会登记表动作
        PetitionSignAction(PlayerbotAI* ai) : Action(ai, "petition sign") {}
        /// 执行动作主逻辑（签署公会登记表动作）
        virtual bool Execute(Event& event) override;
    };    
}
