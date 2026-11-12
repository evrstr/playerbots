// 德鲁伊 - AI对象上下文头文件 (DruidAiObjectContext.h)：定义并注册该职业的策略、动作、触发器与乘数
#pragma once

#include "playerbot/strategy/AiObjectContext.h"

namespace ai
{
    // 德鲁伊 AI 对象上下文：管理并注册职业策略、动作、触发器与乘数
    class DruidAiObjectContext : public AiObjectContext
    {
    public:
        DruidAiObjectContext(PlayerbotAI* ai);
    };
}
