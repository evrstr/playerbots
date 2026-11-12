// 策略值头文件：SpellCastUsefulValue（法术施放有效性及冷却就绪检测）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
    // 布尔值计算器：判断指定法术当前是否处于可用状态且未被列入跳过名单
    class SpellCastUsefulValue : public BoolCalculatedValue, public Qualified
    {
    public:
        SpellCastUsefulValue(PlayerbotAI* ai, std::string name = "spell cast useful") : BoolCalculatedValue(ai, name), Qualified() {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断指定法术当前是否已完成冷却准备就绪
    class SpellReadyValue : public BoolCalculatedValue, public Qualified
    {
    public:
        SpellReadyValue(PlayerbotAI* ai, std::string name = "spell ready") : BoolCalculatedValue(ai, name), Qualified() {}
        virtual bool Calculate() override;
    };
}
