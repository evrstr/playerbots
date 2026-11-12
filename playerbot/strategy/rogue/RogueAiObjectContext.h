// 潜行者 - AI对象上下文头文件 (RogueAiObjectContext.h)：定义并注册该职业的策略、动作、触发器与乘数
#pragma once

#include "playerbot/strategy/AiObjectContext.h"

namespace ai
{
    // 潜行者 AI 对象上下文：管理并注册职业策略、动作、触发器与乘数
    class RogueAiObjectContext : public AiObjectContext
    {
    public:
        RogueAiObjectContext(PlayerbotAI* ai);
    };
}
