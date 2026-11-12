#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 帮助指令动作：输出机器人支持的所有聊天指令与策略帮助说明
    class HelpAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化帮助指令动作
        HelpAction(PlayerbotAI* ai);
        virtual ~HelpAction();
        /// 执行动作主逻辑（帮助指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（帮助指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 向主人发送支持的聊天指令列表
        void TellChatCommands(Player* requester);
        /// 汇报机器人当前各 AI 状态启用的策略详情
        void TellStrategies(Player* requester);
        /// 判断两个状态或条件是否可以合并支持
        std::string CombineSupported(const std::set<std::string>& commands) const;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "help"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This chat command will make the bot give you help on various topics.\n"
                "Each help topic will provide various chat-links which can be linked in chat.\n"
                "Links can be copied to chat with shift-click and when sent to a bot will provide feedback.\n"
                "It is possible to search for help topics by adding part of the topic name after the command.\n"
                "Example commands: 'help' and 'help rpg'.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    private:
        NamedObjectContext<Action>* chatContext;
    };

}
