#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 共享任务指令动作：向队伍成员共享指定任务或任务日志中的任务
    class ShareQuestAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化共享任务指令动作
        ShareQuestAction(PlayerbotAI* ai, std::string name = "share quest") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（共享任务指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（共享任务指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 自动共享任务动作：接取新任务后自动向附近队友共享
    class AutoShareQuestAction : public ShareQuestAction
    {
    public:
        /// 构造函数：初始化自动共享任务动作
        AutoShareQuestAction(PlayerbotAI* ai) : ShareQuestAction(ai, "auto share quest") {}
        /// 执行动作主逻辑（自动共享任务动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自动共享任务动作）
        virtual bool isUsefulWhenStunned() override { return true; }

        /// 判断当前状态下该动作是否可用/有效（自动共享任务动作）
        virtual bool isUseful() override { return bot->GetGroup() && !ai->HasActivePlayerMaster(); }
    };
}
