#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 发送邮件指令动作：向指定玩家发送包含金币或物品的邮件
    class SendMailAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化发送邮件指令动作
        SendMailAction(PlayerbotAI* ai) : ChatCommandAction(ai, "sendmail") {}
        /// 执行动作主逻辑（发送邮件指令动作）
        virtual bool Execute(Event& event) override;
    };
}
