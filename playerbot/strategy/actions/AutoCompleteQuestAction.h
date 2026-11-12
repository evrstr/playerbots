#pragma once

#include "GenericActions.h"

namespace ai
{
    /// 自动完成任务动作：自动交付并完成预定义的特定任务（如难以正常交互的任务）
    class AutoCompleteQuestAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化自动完成任务动作
        AutoCompleteQuestAction(PlayerbotAI* ai) : ChatCommandAction(ai, "auto complete quest") {}
        /// 执行动作主逻辑（自动完成任务动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（自动完成任务动作）
        virtual bool isUseful() override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自动完成任务动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "auto complete quest"; }
        virtual std::string GetHelpDescription()
        {
            return "This action allows the bot to automatically complete certain predefined quests.\n"
                   "These quests are currently impossible for bots to complete on their own. However they are still important for the bot's progression.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
};
