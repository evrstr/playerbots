#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 距离设置指令动作：查询或设置机器人战斗、跟随、法术等各类距离参数
    class RangeAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化距离设置指令动作
        RangeAction(PlayerbotAI* ai) : ChatCommandAction(ai, "range") {}
        /// 执行动作主逻辑（距离设置指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（距离设置指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 输出当前配置的各类距离参数值
        void PrintRange(std::string type, Player* requester);
    };
}
