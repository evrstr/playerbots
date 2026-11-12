#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 汇报物品数量动作：查询并告知主人机器人背包内指定物品的数量
    class TellItemCountAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化汇报物品数量动作
        TellItemCountAction(PlayerbotAI* ai) : ChatCommandAction(ai, "c") {}
        /// 执行动作主逻辑（汇报物品数量动作）
        virtual bool Execute(Event& event) override;

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（汇报物品数量动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
