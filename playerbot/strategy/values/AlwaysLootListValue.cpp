// 策略值实现：AlwaysLootListValue（强制拾取物品列表的序列化与反序列化）

#include "AlwaysLootListValue.h"
#include "playerbot/playerbot.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

// 将强制拾取列表中的所有物品 ID 拼接为逗号分隔字符串
std::string AlwaysLootListValue::Save()
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

// 解析逗号分隔的字符串并重新填充强制拾取物品集合
bool AlwaysLootListValue::Load(std::string text)
{
    value.clear();

    std::vector<std::string> ss = split(text, ',');
    for (std::vector<std::string>::iterator i = ss.begin(); i != ss.end(); ++i)
    {
        value.insert(atoi(i->c_str()));
    }
    return true;
}
