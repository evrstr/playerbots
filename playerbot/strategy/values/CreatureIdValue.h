// 策略值头文件：CreatureIdValue（从文本参数解析生物模板 ID）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
    // 值计算器：从限定符字符串或链接中提取并校验有效的生物 Entry ID
    class CreatureIdValue : public CalculatedValue<uint32>, public Qualified
    {
    public:
        CreatureIdValue(PlayerbotAI* ai);
        virtual uint32 Calculate() override;
    };
}
