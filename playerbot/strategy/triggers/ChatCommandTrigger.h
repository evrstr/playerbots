/// 聊天指令触发器基类
#pragma once

#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：由外部聊天指令触发的通用触发器
    class ChatCommandTrigger : public Trigger {
    public:
        ChatCommandTrigger(PlayerbotAI* ai, std::string command) : Trigger(ai, command) {}

        /// 接收外部聊天事件并保存参数与发送者
        virtual void ExternalEvent(std::string param, Player* owner = NULL) override
        {
            this->param = param;
            this->owner = owner;
            triggered = true;
        }

        /// 检查触发状态并返回对应事件
        virtual Event Check() override
        {
            if (!triggered)
                return Event();

            return Event(getName(), param, owner);
        }

        /// 重置触发标记
        virtual void Reset() override
        {
            triggered = false;
        }
    };
}
