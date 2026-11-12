
#include "playerbot/playerbot.h"
#include "CustomStrategy.h"

using namespace ai;

// 解析 "动作名!权重" 格式字符串为 NextAction 对象
NextAction* toNextAction(std::string action)
{
    std::vector<std::string> tokens = split(action, '!');
    if (tokens.size() == 2 && !tokens[0].empty())
        return new NextAction(tokens[0], atof(tokens[1].c_str()));
    else if (tokens.size() == 1 && !tokens[0].empty())
        return new NextAction(tokens[0], ACTION_NORMAL);

    sLog.outError("Invalid action '%s'", action.c_str());
    return NULL;
}

// 拆分逗号分隔的动作列表（忽略花括号嵌套内的逗号）为 NextAction 数组
NextAction** toNextActionArray(std::string actions)
{
    std::vector<std::string> tokens;
    tokens.push_back("");
    int stack = 0;
    for (char a : actions)
    {
       if (a == '{') ++stack;
       if (a == '}') --stack;
       if (a == ',' && stack == 0) tokens.push_back("");
       tokens.back() += a;
    }

    NextAction** res = new NextAction*[tokens.size() + 1];
    int index = 0;
    for (std::vector<std::string>::iterator i = tokens.begin(); i != tokens.end(); ++i)
    {
        NextAction* na = toNextAction(*i);
        if (na)
            res[index++] = na;
    }
    res[index++] = NULL;
    return res;
}

// 解析 "触发器>动作列表" 规则行为 TriggerNode
TriggerNode* toTriggerNode(std::string actionLine)
{
    std::vector<std::string> tokens = split(actionLine, '>');
    if (tokens.size() == 2)
        return new TriggerNode(tokens[0], toNextActionArray(tokens[1]));

    sLog.outError("Invalid action line '%s'", actionLine.c_str());
    return NULL;
}

// 初始化非战斗触发器：优先加载角色专属自定义规则，否则回退加载公共规则(owner=0)
void CustomStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    if (actionLines.empty())
    {
        LoadActionLines((uint32)ai->GetBot()->GetGUIDLow());
        if (this->actionLines.empty())
            LoadActionLines(0);
    }

    for (std::list<std::string>::iterator i = actionLines.begin(); i != actionLines.end(); ++i)
    {
        TriggerNode* tn = toTriggerNode(*i);
        if (tn)
            triggers.push_back(tn);
    }
}

// 战斗状态下复用同一套自定义规则触发器
void CustomStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    InitNonCombatTriggers(triggers);
}

/// 从 ai_playerbot_custom_strategy 数据表按顺序读取规则行
void CustomStrategy::LoadActionLines(uint32 owner)
{
    // The qualifier comes from chat ("co +custom::<name>") | 限定名来自聊天指令
    std::string name = qualifier;
    CharacterDatabase.escape_string(name);
    auto results = CharacterDatabase.PQuery("SELECT action_line FROM ai_playerbot_custom_strategy WHERE name = '%s' and owner = '%u' order by idx",
            name.c_str(), owner);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            std::string action = fields[0].GetString();
            this->actionLines.push_back(action);
        } while (results->NextRow());
    }
}

// 清空已缓存的自定义规则行，以便下次重新加载
void CustomStrategy::Reset()
{
    actionLines.clear();
}
