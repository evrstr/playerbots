// 策略值头文件：MasterTargetValue（小队主控玩家目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：获取当前机器人在队伍中的主控玩家（GroupMaster）GUID
    class MasterTargetValue : public UnitCalculatedValue
    {
    public:
        MasterTargetValue(PlayerbotAI* ai, std::string name = "master target") : UnitCalculatedValue(ai, name) {}

        virtual ObjectGuid Calculate() override;
    };
}
