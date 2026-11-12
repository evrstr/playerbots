// 牧师 - AI对象上下文头文件 (PriestAiObjectContext.h)：定义并注册该职业的策略、动作、触发器与乘数
#pragma once

#include "playerbot/strategy/AiObjectContext.h"

namespace ai
{
    // 牧师 AI 对象上下文：管理并注册职业策略、动作、触发器与乘数
    class PriestAiObjectContext : public AiObjectContext
    {
    public:
        PriestAiObjectContext(PlayerbotAI* ai);
    };
}
