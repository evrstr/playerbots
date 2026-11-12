// 德鲁伊 - 数值计算头文件 (DruidValues.h)：定义德鲁伊专用状态评估值
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/values/PartyMemberValue.h"

namespace ai
{
    // 状态评估值 (PartyTankWithoutLifebloomValue)：计算并返回职业特定目标或状态值
    class PartyTankWithoutLifebloomValue : public PartyMemberValue, public Qualified
    {
    public:
        PartyTankWithoutLifebloomValue(PlayerbotAI* ai, std::string name = "party tank without lifebloom", float range = 40.0f) :
            PartyMemberValue(ai, name), Qualified() {}

    protected:
        ObjectGuid Calculate() override;
    };
}
