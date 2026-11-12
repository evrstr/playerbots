#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 法术信息查询指令动作：查询并汇报指定法术或物品的详情
    class TellSpellAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化法术信息查询指令动作
        TellSpellAction(PlayerbotAI* ai) : ChatCommandAction(ai, "spell") {}
        /// 执行动作主逻辑（法术信息查询指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（法术信息查询指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 施法失败通知动作：将法术施放失败的原因汇报给主人
    class TellCastFailedAction : public Action 
    {
    public:
        /// 构造函数：初始化施法失败通知动作
        TellCastFailedAction(PlayerbotAI* ai) : Action(ai, "tell cast failed") {}

        /// 执行动作主逻辑（施法失败通知动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（施法失败通知动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
