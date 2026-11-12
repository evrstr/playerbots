// 策略值头文件：CurrentTargetValue（机器人当前选中的目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：存储和读取机器人当前的选定目标 GUID，超出视距则失效
    class CurrentTargetValue : public UnitManualSetValue
    {
    public:
        CurrentTargetValue(PlayerbotAI* ai, std::string name = "current target") : UnitManualSetValue(ai, ObjectGuid(), name) {}
        virtual ObjectGuid Get() override;
        virtual void Set(ObjectGuid unitGuid) override;

    private:
        ObjectGuid selection;
    };
}
