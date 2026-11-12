/// 网络数据包事件响应与就绪确认策略头文件
#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    /// 策略：默认核心策略（default），负责响应服务端下发的各类游戏网络事件数据包
    class WorldPacketHandlerStrategy : public PassTroughStrategy
    {
    public:
        WorldPacketHandlerStrategy(PlayerbotAI* ai);
        std::string getName() override { return "default"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：团队就绪确认（ready check）响应策略
    class ReadyCheckStrategy : public PassTroughStrategy
    {
    public:
        ReadyCheckStrategy(PlayerbotAI* ai) : PassTroughStrategy(ai) {}
        std::string getName() override { return "ready check"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
