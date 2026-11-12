#pragma once

#include "playerbot/strategy/Action.h"
#include "Quests/QuestDef.h"

namespace ai
{
    /// 任务交互基类动作：封装与 NPC 或游戏对象进行任务接取与交付的通用逻辑
    class QuestAction : public Action 
    {
    public:
        /// 构造函数：初始化任务交互基类动作
        QuestAction(PlayerbotAI* ai, std::string name = "quest") : Action(ai, name) {}

    public:
        /// 执行动作主逻辑（任务交互基类动作）
        virtual bool Execute(Event& event) override;

    protected:
        /// 处理单个任务发布对象的任务接取或交付逻辑（任务交互基类动作）
        virtual bool ProcessQuest(Player* requester, Quest const* quest, WorldObject* questGiver) = 0;
        /// 向服务端发送完成并交付任务封包
        bool CompleteQuest(Player* player, uint32 entry);
        /// 向服务端发送接受任务封包并触发接取处理
        bool AcceptQuest(Player* requester, Quest const* quest, uint64 questGiver);
        /// 遍历附近或指定对象的可交互任务并逐个处理
        bool ProcessQuests(ObjectGuid questGiver);
        /// 遍历附近或指定对象的可交互任务并逐个处理
        bool ProcessQuests(WorldObject* questGiver);
    };
    
    /// 任务击杀进度更新动作：处理任务击杀计数增加事件并播报进度
    class QuestUpdateAddKillAction : public Action
    {
    public:
        /// 构造函数：初始化任务击杀进度更新动作
        QuestUpdateAddKillAction(PlayerbotAI* ai) : Action(ai, "quest update add kill") {}

    public:
        /// 执行动作主逻辑（任务击杀进度更新动作）
        virtual bool Execute(Event& event) override;
    };

    /// 任务物品进度更新动作：处理任务物品收集计数变化事件
    class QuestUpdateAddItemAction : public Action
    {
    public:
        /// 构造函数：初始化任务物品进度更新动作
        QuestUpdateAddItemAction(PlayerbotAI* ai) : Action(ai, "quest update add item") {}

    public:
        /// 执行动作主逻辑（任务物品进度更新动作）
        virtual bool Execute(Event& event) override;
    };

    /// 任务失败处理动作：响应任务失败事件并更新机器人任务状态
    class QuestUpdateFailedAction : public Action
    {
    public:
        /// 构造函数：初始化任务失败处理动作
        QuestUpdateFailedAction(PlayerbotAI* ai) : Action(ai, "quest update failed") {}

    public:
        /// 执行动作主逻辑（任务失败处理动作）
        virtual bool Execute(Event& event) override;
    };

    /// 任务计时失败处理动作：响应限时任务超时失败事件
    class QuestUpdateFailedTimerAction : public Action
    {
    public:
        /// 构造函数：初始化任务计时失败处理动作
        QuestUpdateFailedTimerAction(PlayerbotAI* ai) : Action(ai, "quest update failed timer") {}

    public:
        /// 执行动作主逻辑（任务计时失败处理动作）
        virtual bool Execute(Event& event) override;
    };

    /// 任务完成处理动作：响应任务目标全部达成事件并播报
    class QuestUpdateCompleteAction : public Action
    {
    public:
        /// 构造函数：初始化任务完成处理动作
        QuestUpdateCompleteAction(PlayerbotAI* ai) : Action(ai, "quest update complete") {}

    public:
        /// 执行动作主逻辑（任务完成处理动作）
        virtual bool Execute(Event& event) override;
    };
}
