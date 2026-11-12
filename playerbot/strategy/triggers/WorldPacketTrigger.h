/// 网络数据包触发器基类
#pragma once

#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：由服务端/客户端 WorldPacket 外部事件驱动的触发器
    class WorldPacketTrigger : public Trigger {
    public:
        WorldPacketTrigger(PlayerbotAI* ai, std::string command) : Trigger(ai, command), triggered(false) {}

        /// 标记该触发器为外部事件驱动
        virtual bool IsExternalEvent() const override { return true; }

        /// 接收外部 WorldPacket 并标记已触发
        virtual void ExternalEvent(WorldPacket &packet, Player* owner = NULL) override
        {
            this->packet = packet;
            this->owner = owner;
            triggered = true;
        }

        /// 检查触发标志并生成携带数据包的事件
        virtual Event Check() override
        {
            if (!triggered)
                return Event();

            return Event(getName(), packet, owner);
        }

        /// 重置触发状态
        virtual void Reset() override
        {
            triggered = false;
        }
    private:
        WorldPacket packet;
        bool triggered;
        Player* owner;
    };
}
