// 策略值头文件：InvalidTargetValue（目标无效性判定）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 布尔值计算器：判断指定限定符目标是否已不在世界、切换地图、取消选中或不再合法
    class InvalidTargetValue : public BoolCalculatedValue, public Qualified
    {
    public:
        InvalidTargetValue(PlayerbotAI* ai, std::string name = "invalid target") : BoolCalculatedValue(ai, name), Qualified() {}
        virtual bool Calculate() override;
    };
}
