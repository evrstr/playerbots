// 法师 - AI对象上下文头文件 (MageAiObjectContext.h)：定义并注册该职业的策略、动作、触发器与乘数
#pragma once

#include "playerbot/strategy/AiObjectContext.h"

namespace ai
{
    // 法师 AI 对象上下文：管理并注册职业策略、动作、触发器与乘数
    class MageAiObjectContext : public AiObjectContext
    {
    public:
        MageAiObjectContext(PlayerbotAI* ai);
    };
}
