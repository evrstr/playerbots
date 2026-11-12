
#include "playerbot/playerbot.h"
#include "HelpAction.h"
#include "ChatActionContext.h"
#include "playerbot/PlayerbotHelpMgr.h"

using namespace ai;

/// 构造函数：初始化帮助指令动作
HelpAction::HelpAction(PlayerbotAI* ai) : ChatCommandAction(ai, "help")
{
    chatContext = new ChatActionContext();
}

/// 析构函数：释放帮助指令动作资源
HelpAction::~HelpAction()
{
    delete chatContext;
}

/// 执行动作主逻辑（帮助指令动作）
bool HelpAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    std::string param = event.getParam();
    std::string helpTopic;

    if(param.find("Hvalue:help") != std::string::npos)
    {
        helpTopic = ChatHelper::parseValue("help",param);
    }
    else if (param.find("[h:") != std::string::npos)
    {
        helpTopic = param.substr(3,param.size()-4);
    }

    if (param.empty())
    {
        helpTopic = "help:main";
    }

    std::ostringstream out;
    std::string helpTekst = sPlayerbotHelpMgr.GetBotText(helpTopic);

    if (helpTopic.empty() && !param.empty())
    {
        std::vector<std::string> list = sPlayerbotHelpMgr.FindBotText(param);

        if(list.size() == 1)
            helpTekst = sPlayerbotHelpMgr.GetBotText(list.front());
        else if (!list.empty())
        {
            std::sort(list.begin(), list.end());
            helpTekst = sPlayerbotHelpMgr.GetBotText("help:search");

            std::string topics = sPlayerbotHelpMgr.makeList(list, "[h:<part>|<part>]");

            if (!helpTekst.empty())
                sPlayerbotHelpMgr.replace(helpTekst, "<found>", topics);
            else
                helpTekst = topics; // Fallback for old help table. (旧版帮助表的兼容回退路径。)

            sPlayerbotHelpMgr.FormatHelpTopic(helpTekst);
        }
    }

    if (!helpTekst.empty())
    {
        std::vector<std::string> lines = Qualified::getMultiQualifiers(helpTekst, "\n");

        for (auto& line : lines)
        {
            ai->TellPlayerNoFacing(requester, line, PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, true, false);
        }

        return true;
    }
    
    TellChatCommands(requester);
    TellStrategies(requester);

    return true;
}

/// 向主人发送支持的聊天指令列表
void HelpAction::TellChatCommands(Player* requester)
{
    std::set<std::string> keys;
    chatContext->GetSupportedKeys(keys);

    std::ostringstream out;
    out << "Whisper any of: ";
    out << CombineSupported(keys);
    out << ", [item], [quest] or [object] link";
    ai->TellPlayer(requester, out.str());
}

/// 汇报机器人当前各 AI 状态启用的策略详情
void HelpAction::TellStrategies(Player* requester)
{
    std::set<std::string> strategies;
    ai->GetAiObjectContext()->GetSupportedStrategies(strategies);

    std::ostringstream out;
    out << "Possible strategies (co/nc/dead commands): ";
    out << CombineSupported(strategies);
    ai->TellPlayer(requester, out.str());
}

/// 判断两个状态或条件是否可以合并支持
std::string HelpAction::CombineSupported(const std::set<std::string>& commands) const
{
    std::ostringstream out;

    for (std::set<std::string>::iterator i = commands.begin(); i != commands.end(); )
    {
        out << *i;
        if (++i != commands.end())
            out << ", ";
    }

    return out.str();
}
