// 策略值头文件：PetTargetValue（机器人当前召唤宠物目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：获取机器人当前激活的宠物 GUID
    class PetTargetValue : public UnitCalculatedValue
    {
    public:
        PetTargetValue(PlayerbotAI* ai, std::string name = "pet target") : UnitCalculatedValue(ai, name) {}

        virtual ObjectGuid Calculate() override 
        {
            Unit* pet = ai->GetBot()->GetPet();
            return pet ? pet->GetObjectGuid() : ObjectGuid();
        }
    };
}
