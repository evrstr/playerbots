#pragma once
#include "GenericActions.h"

namespace ai
{
    /// NPC 对话问候动作：向选定 NPC 发送对话请求并输出可用对话选项
    class GossipHelloAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化NPC 对话问候动作
        GossipHelloAction(PlayerbotAI* ai) : ChatCommandAction(ai, "gossip hello") {}
        /// 执行动作主逻辑（NPC 对话问候动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 输出当前对话 NPC 提供的所有 Gossip 菜单选项
        void TellGossipMenus(Player* requester);
        /// 处理 NPC 对话菜单选项并输出或选择指定条目
        bool ProcessGossip(Player* requester, ObjectGuid creatureGuid, int menuToSelect);
        /// 输出当前对话 NPC 的问候正文文本
        void TellGossipText(Player* requester, uint32 textId);
    };
}
