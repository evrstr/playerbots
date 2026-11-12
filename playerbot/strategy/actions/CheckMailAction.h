#pragma once

#include "playerbot/strategy/Action.h"
#include "QuestAction.h"

namespace ai
{
    /// 检查邮件动作：检测新邮件并在需要时提醒或触发收信逻辑
    class CheckMailAction : public Action
    {
    public:
        /// 构造函数：初始化检查邮件动作
        CheckMailAction(PlayerbotAI* ai) : Action(ai, "check mail") {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "check mail"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot automatically check its mailbox when not in combat or battlegrounds.\n"
                   "Any items received will be returned to sender unless they were specifically requested.\n"
                   "The bot only checks mail when it has no active master controlling it.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
        /// 执行动作主逻辑（检查邮件动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（检查邮件动作）
        virtual bool isUseful() override;

    private:
        /// 遍历邮箱列表并执行相应的邮件处理器操作
        void ProcessMail(Mail* mail, Player* owner);
    };
}
