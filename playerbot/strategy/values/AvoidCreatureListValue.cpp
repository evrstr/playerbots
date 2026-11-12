// 策略值实现：AvoidCreatureListValue（规避生物列表序列化）

#include "playerbot/playerbot.h"
#include "AvoidCreatureListValue.h"

using namespace ai;

// 将生物 Entry 集合输出为逗号分隔的字符串
std::string AvoidCreatureListValue::Save()
{
    std::ostringstream out;
    bool first = true;
    for (std::set<uint32>::iterator i = value.begin(); i != value.end(); ++i)
    {
        if (!first) out << ",";
        else first = false;
        out << *i;
    }
    return out.str();
}

// 解析逗号分隔字符串并重建生物 Entry 集合
bool AvoidCreatureListValue::Load(std::string text)
{
    value.clear();

    std::vector<std::string> ss = split(text, ',');
    for (std::vector<std::string>::iterator i = ss.begin(); i != ss.end(); ++i)
    {
        value.insert(atoi(i->c_str()));
    }
    return true;
}