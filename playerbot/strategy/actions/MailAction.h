#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 邮件处理器基类：定义遍历与处理机器人邮箱邮件的抽象接口
    class MailProcessor
    {
    public:
        /// 在执行动作之前触发前置辅助逻辑
        virtual bool Before(Player* requester, PlayerbotAI* ai) { return true; }
        /// 处理当前邮件或队列条目
        virtual bool Process(Player* requester, int index, Mail* mail, PlayerbotAI* ai, Event& event) = 0;
        /// 在执行动作之后触发后续辅助逻辑
        virtual bool After(Player* requester, PlayerbotAI* ai) { return true; }

    public:
        /// 在附近搜索可用的邮箱游戏对象
        static ObjectGuid FindMailbox(PlayerbotAI* ai);

    protected:
        /// 删除已读或空附件的邮件记录
        void RemoveMail(Player* bot, uint32 id, ObjectGuid mailbox);
    };


    /// 邮件管理指令动作：支持查看、收取、删除邮件的聊天指令入口
    class MailAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化邮件管理指令动作
        MailAction(PlayerbotAI* ai) : ChatCommandAction(ai, "mail") {}
        /// 执行动作主逻辑（邮件管理指令动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 检查附近邮箱并在可用时读取邮件
        bool CheckMailbox();

    private:
        static std::map<std::string, MailProcessor*> processors;
    };

}
