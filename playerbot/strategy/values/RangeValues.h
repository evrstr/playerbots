// 策略值头文件：RangeValue（可配置的自定义距离阈值）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：按限定符保存和加载各类行为距离配置值（支持存档序列化）
    class RangeValue : public ManualSetValue<float>, public Qualified
    {
    public:
        RangeValue(PlayerbotAI* ai);
        virtual std::string Save() override;
        virtual bool Load(std::string value) override;
    };
}
