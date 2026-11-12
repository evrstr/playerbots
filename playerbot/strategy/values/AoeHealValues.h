// 策略值头文件：AoeHealValues（群体治疗需求统计）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 值计算器：根据限定符（low/medium/critical）统计范围内需要群体治疗的队友数量
    class AoeHealValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        AoeHealValue(PlayerbotAI* ai, std::string name = "aoe heal") : Uint8CalculatedValue(ai, name, 3), Qualified() {}

    public:
        // 计算符合对应血量阈值的范围内队友人数
        virtual uint8 Calculate() override;
    };
}
