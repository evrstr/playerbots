#pragma once
#include "playerbot/LootObjectStack.h"
#include "MovementActions.h"

namespace ai
{
    /// 拾取动作：向战利品目标移动并触发拾取或采集流程
    class LootAction : public MovementAction
    {
    public:
        /// 构造函数：初始化拾取动作
        LootAction(PlayerbotAI* ai) : MovementAction(ai, "loot") {}
        /// 执行动作主逻辑（拾取动作）
        virtual bool Execute(Event& event) override;
    };

    /// 打开拾取动作：靠近目标并打开尸体、宝箱或可交互采集物
    class OpenLootAction : public MovementAction
    {
    public:
        /// 构造函数：初始化打开拾取动作
        OpenLootAction(PlayerbotAI* ai) : MovementAction(ai, "open loot") {}
        /// 执行动作主逻辑（打开拾取动作）
        virtual bool Execute(Event& event) override;

    private:
        /// 执行打开尸体、拾取全部物品或触发采集的具体操作
        bool DoLoot(LootObject& lootObject);
        /// 获取开启指定带锁宝箱或门所需使用的开锁或专业技能 ID
        uint32 GetOpeningSpell(LootObject& lootObject);
        /// 获取开启指定带锁宝箱或门所需使用的开锁或专业技能 ID
        uint32 GetOpeningSpell(LootObject& lootObject, GameObject* go);
        /// 判断机器人能否打开指定的带锁游戏对象或物品
        bool CanOpenLock(LootObject& lootObject, const SpellEntry* pSpellInfo, GameObject* go);
        /// 判断机器人能否打开指定的带锁游戏对象或物品
        bool CanOpenLock(uint32 skillId, uint32 reqSkillValue);
    };

    /// 获取对象动作：定位并尝试拾取或收集指定任务或战利品对象
    class FetchObjectAction : public MovementAction
    {
    public:
        /// 构造函数：初始化获取对象动作
        FetchObjectAction(PlayerbotAI* ai) : MovementAction(ai, "fetch object") {}
        /// 执行动作主逻辑（获取对象动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（获取对象动作）
        virtual bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（获取对象动作）
        virtual bool isPossible() override { return true; }

    private:
        /// 更新基于时间推移的对话或状态同步时钟
        void UpdateClock();
        /// 判断当前动作或等待状态是否已经超时
        bool IsTimedOut();
        /// 判断当前目标点是否为支持多次重复交互的任务或世界增益节点
        bool IsMultiUseNode(GameObject* go);
        /// 获取触发当前动作的玩家请求者指针
        Player* GetRequester();
        /// 完成当前操作流程并清理临时状态
        void Finish(bool restoreMode);
    };

    /// 存储战利品动作：处理拾取窗口并将战利品物品存入背包
    class StoreLootAction : public Action
    {
    public:
        /// 构造函数：初始化存储战利品动作
        StoreLootAction(PlayerbotAI* ai) : Action(ai, "store loot") {}
        /// 执行动作主逻辑（存储战利品动作）
        virtual bool Execute(Event& event) override;
        /// 校验指定物品或目标是否允许机器人拾取
        static bool IsLootAllowed(ItemQualifier& itemQualifier, PlayerbotAI *ai);
    };

    /// 释放拾取动作：关闭当前拾取窗口并清理拾取状态
    class ReleaseLootAction : public MovementAction
    {
    public:
        /// 构造函数：初始化释放拾取动作
        ReleaseLootAction(PlayerbotAI* ai) : MovementAction(ai, "release loot") {}
        /// 执行动作主逻辑（释放拾取动作）
        virtual bool Execute(Event& event) override;
    };
}
