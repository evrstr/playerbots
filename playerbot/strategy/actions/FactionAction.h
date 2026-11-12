#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 阵营声望查询/设置动作：查询或调整机器人在特定阵营中的交互状态
    class FactionAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化阵营声望查询/设置动作
        FactionAction(PlayerbotAI* ai) : ChatCommandAction(ai, "faction") {}
        /// 执行动作主逻辑（阵营声望查询/设置动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（阵营声望查询/设置动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "faction"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This chat command gives information about a bot\'s reputation with factions.\n"
                "Examples:\n"
                "faction : List all factions and their reputation level and at war flag.\n"
                "faction [name] : List the factions matching a certain name or faction link.\n"
                "faction +atwar <name> : Flags the selected factions (name optional) as at war.\n";
                "faction -atwar <name> : Flags the selected factions (name optional) as not at war.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
