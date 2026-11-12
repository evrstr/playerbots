// 策略值头文件：ManaSaveLevelValue（省蓝保守系数配置）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：保存法力保留系数（默认 1.0，支持字符串保存和加载）
    class ManaSaveLevelValue : public ManualSetValue<double>
    {
    public:
        ManaSaveLevelValue(PlayerbotAI* ai) : ManualSetValue<double>(ai, 1.0, "mana save level") {}

        virtual std::string Save() override { std::ostringstream out; out << value; return out.str(); }
        virtual bool Load(std::string text) override { value = atof(text.c_str()); return true; }
    };
}
