// 策略值实现：SubStrategyValue（子策略增删改语法解析与加载）

#include "SubStrategyValue.h"

using namespace ai;

// 使用新配置字符串更新当前子策略集合
void SubStrategyValue::Set(std::string newValue)
{
    SetValues(value, newValue, allowedValues);
}


// 解析 +/-/~/all/clear 操作符，对逗号分隔的子策略列表进行增删或翻转
void SubStrategyValue::SetValues(std::string& currentValue, const std::string newValue, const std::string allowedValues)
{
    std::vector<std::string> currentValues = StrSplit(currentValue, ",");
    std::vector<std::string> newValues = StrSplit(newValue, ",");
    std::vector<std::string> allowedVals = StrSplit(allowedValues, ",");

    for (std::string& newVal : newValues)
    {
        char operation = newVal[0];

        if (operation == '-' || operation == '+' || operation == '~')
            newVal = newVal.substr(1);
        else
            operation = '+';

        if (allowedValues.size() && std::find(allowedVals.begin(), allowedVals.end(), newVal) == allowedVals.end())
            continue;

        auto found = std::find(currentValues.begin(), currentValues.end(), newVal);

        if (found == currentValues.end())
        {
            if (operation != '-')
                currentValues.push_back(newVal);
        }
        else
        {
            if (operation != '+')
                currentValues.erase(found);
        }
    }

    currentValue = "";

    for (std::string value : currentValues)
        currentValue += value + ",";

    if(!currentValues.empty())
        currentValue.pop_back();
}

// 清空旧配置并重新加载保存的子策略字符串
bool SubStrategyValue::Load(std::string value)
{
    this->value = "";
    Set(value);
    return true;
}