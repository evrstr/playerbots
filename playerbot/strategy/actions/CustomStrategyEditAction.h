#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 自定义策略编辑动作：通过聊天命令动态创建、修改或删除自定义策略规则
    class CustomStrategyEditAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化自定义策略编辑动作
        CustomStrategyEditAction(PlayerbotAI* ai) : ChatCommandAction(ai, "cs") {}
        /// 执行动作主逻辑（自定义策略编辑动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自定义策略编辑动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 输出指令帮助文档信息
        bool PrintHelp(Player* requester);
        /// 打印单条动作帮助说明行
        bool PrintActionLine(uint32 idx, std::string command, Player* requester);
        /// 格式化并输出策略或帮助信息文本
        bool Print(std::string name, Player* requester);
        /// 编辑自定义策略规则中的触发器或动作节点
        bool Edit(std::string name, uint32 idx, std::string command, Player* requester);
    };
}
