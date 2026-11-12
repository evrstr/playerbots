// 策略值头文件：IsFacingValue（判断机器人是否正面向目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 布尔值计算器：检查目标是否在机器人视距和前方施法扇形角度范围内
    class IsFacingValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsFacingValue(PlayerbotAI* ai, std::string name = "is facing") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));
            if (!target)
                return false;

            return sServerFacade.IsInFront(bot, target, sPlayerbotAIConfig.sightDistance, CAST_ANGLE_IN_FRONT);
        }
    };
}
