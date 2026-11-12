// 策略值实现：SkipSpellsListValue（屏蔽法术列表存取序列化）

#include "playerbot/playerbot.h"
#include "SkipSpellsListValue.h"

using namespace ai;

// 将屏蔽法术 ID 集合序列化为逗号分隔字符串
std::string SkipSpellsListValue::Save()
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

// 解析逗号分隔字符串并重建屏蔽法术 ID 集合
bool SkipSpellsListValue::Load(std::string text)
{
    value.clear();

    std::vector<std::string> ss = split(text, ',');
    for (std::vector<std::string>::iterator i = ss.begin(); i != ss.end(); ++i)
    {
        value.insert(atoi(i->c_str()));
    }
    return true;
}
