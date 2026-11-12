// 策略值实现：OperatorValues（布尔组合逻辑与数值比较求值）
#include "playerbot/playerbot.h"
#include "playerbot/strategy/Value.h"
#include "OperatorValues.h"

namespace ai
{
    // 逐项求值限定符列表，全部为 true 时返回 true
    bool BoolAndValue::Calculate()
    {
        std::vector<std::string> values = getMultiQualifiers(getQualifier(), ",");

        for (auto value : values)
        {
            if (!AI_VALUE(bool, value))
                return false;
        }

        return true;
    }

    // 逐项求值限定符列表，任一为 true 时返回 false
    bool NotValue::Calculate()
    {
        std::vector<std::string> values = getMultiQualifiers(getQualifier(), ",");

        for (auto value : values)
        {
            if (AI_VALUE(bool, value))
                return false;
        }

        return true;
    }

    // 逐项求值限定符列表，任一为 true 时返回 true
    bool BoolOrValue::Calculate()
    {
        std::vector<std::string> values = getMultiQualifiers(getQualifier(), ",");

        for (auto value : values)
        {
            if (AI_VALUE(bool, value))
                return true;
        }

        return false;
    }

    // 解析左右两个操作数（字面量或 AI 值名），返回 lhs > rhs
    bool GT32Value::Calculate()
    {
        std::vector<std::string> values = getMultiQualifiers(getQualifier(), ",");

        if (values.size() < 2)
            return false;

        uint32 value1, value2;

        if (isValidNumberString(values[0]))
            value1 = stoi(values[0]);
        else
            value1 = AI_VALUE(uint32, values[0]);

        if (isValidNumberString(values[1]))
            value2 = stoi(values[1]);
        else
            value2 = AI_VALUE(uint32, values[1]);

        return value1 > value2;
    }
}
