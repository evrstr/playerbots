// 策略值实现：RangeValue（距离配置值构造函数与字符串读写）

#include "playerbot/playerbot.h"
#include "RangeValues.h"

using namespace ai;

// 构造函数：初始化默认距离值为 0 并启用限定符
RangeValue::RangeValue(PlayerbotAI* ai)
    : ManualSetValue<float>(ai, 0, "range"), Qualified()
{
}

// 将浮点距离值格式化为字符串
std::string RangeValue::Save()
{
    std::ostringstream out; out << value; return out.str();
}

// 从字符串解析并恢复浮点距离值
bool RangeValue::Load(std::string text)
{
    value = atof(text.c_str());
    return true;
}
