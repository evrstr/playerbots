// 策略值头文件：EngineValues（动作可行性、有用性、触发器状态与策略查询）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 布尔值计算器：查询指定名称的动作当前是否可执行（isPossible）
    class ActionPossibleValue : public BoolCalculatedValue, public Qualified
    {
    public:
        ActionPossibleValue(PlayerbotAI* ai, std::string name = "action possible") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override;
    };

    // 布尔值计算器：查询指定名称的动作当前是否有用（isUseful）
    class ActionUsefulValue : public BoolCalculatedValue, public Qualified
    {
    public:
        ActionUsefulValue(PlayerbotAI* ai, std::string name = "action useful") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override;
    };

    // 布尔值计算器：查询指定触发器是否处于激活且满足检查条件的状态
    class TriggerActiveValue : public BoolCalculatedValue, public Qualified
    {
    public:
        TriggerActiveValue(PlayerbotAI* ai, std::string name = "trigger active") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override;
    };

    // 布尔值计算器：查询指定状态（战斗/非战斗/死亡/反应）下是否启用了某策略
    class HasStrategyValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasStrategyValue(PlayerbotAI* ai, std::string name = "has strategy") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override;
    };
}
