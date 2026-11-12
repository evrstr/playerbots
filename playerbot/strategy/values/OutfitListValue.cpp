// 策略值实现：OutfitListValue（配装方案列表存取序列化）

#include "playerbot/playerbot.h"
#include "OutfitListValue.h"

using namespace ai;

// 将配装方案列表以 ^ 符号拼接为字符串
std::string OutfitListValue::Save()
{
    std::ostringstream out;
    bool first = true;
    for (Outfit::iterator i = value.begin(); i != value.end(); ++i)
    {
        if (!first) out << "^";
        else first = false;
        out << *i;
    }
    return out.str();
}

// 按 ^ 符号拆分字符串并恢复配装方案列表
bool OutfitListValue::Load(std::string text)
{
    value.clear();

    std::vector<std::string> ss = split(text, '^');
    for (std::vector<std::string>::iterator i = ss.begin(); i != ss.end(); ++i)
    {
        value.push_back(*i);
    }
    return true;
}
