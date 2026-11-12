// 策略值头文件：WaitForAttackTimeValue（开怪前等待队友就位时间配置）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：保存开怪拉怪后等待攻击的秒数阈值（默认 10 秒，支持存取序列化）
    class WaitForAttackTimeValue : public ManualSetValue<uint8>, public Qualified
    {
    public:
        WaitForAttackTimeValue(PlayerbotAI* ai) : ManualSetValue<uint8>(ai, 10), Qualified() {}
        virtual std::string Save() override { return std::to_string(value); }
        virtual bool Load(std::string inValue) override { value = stoi(inValue); return true; }
    };
}
