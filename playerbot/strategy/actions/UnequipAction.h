#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 卸下装备指令动作：卸下指定装备栏或指定名称的已穿戴装备
    class UnequipAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化卸下装备指令动作
        UnequipAction(PlayerbotAI* ai) : ChatCommandAction(ai, "unequip") {}
        /// 执行动作主逻辑（卸下装备指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（卸下装备指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

         /// 卸下指定装备栏位或名称的已穿戴装备
         static void UnequipItem(PlayerbotAI* ai, Player* requester, Item* item, bool silent = false);
    private:
        /// 卸下指定装备栏位或名称的已穿戴装备
        void UnequipItem(Player* requester, FindItemVisitor* visitor);
    };
}
