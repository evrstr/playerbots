#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 省蓝策略指令动作：查询或设置机器人在战斗中启用节能省蓝模式的法力阈值
    class SaveManaAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化省蓝策略指令动作
        SaveManaAction(PlayerbotAI* ai) : ChatCommandAction(ai, "save mana") {}
        /// 执行动作主逻辑（省蓝策略指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（省蓝策略指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 按格式模板拼接输出字符串
        std::string format(double value);
    };
}
