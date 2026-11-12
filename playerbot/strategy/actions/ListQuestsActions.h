#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 任务列表过滤模式枚举：定义列出任务时的筛选条件（全部/已完成/未完成/进行中）
    enum QuestListFilter {
        QUEST_LIST_FILTER_SUMMARY = 0,
        QUEST_LIST_FILTER_COMPLETED = 1,
        QUEST_LIST_FILTER_INCOMPLETED = 2,
        QUEST_LIST_FILTER_ALL = QUEST_LIST_FILTER_COMPLETED | QUEST_LIST_FILTER_INCOMPLETED
    };

    /// 任务旅行详情模式枚举：定义任务列表输出中是否包含导航目标详情
    enum QuestTravelDetail {
        QUEST_TRAVEL_DETAIL_NONE = 0,
        QUEST_TRAVEL_DETAIL_SUMMARY = 1,
        QUEST_TRAVEL_DETAIL_FULL = 2
    };

    /// 列出任务指令动作：按过滤条件输出机器人当前任务日志中的任务清单与进度
    class ListQuestsAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化列出任务指令动作
        ListQuestsAction(PlayerbotAI* ai) : ChatCommandAction(ai, "quests") {}
        /// 执行动作主逻辑（列出任务指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（列出任务指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 按过滤条件格式化并输出任务日志清单
        void ListQuests(Player* requester, QuestListFilter filter, QuestTravelDetail travelDetail = QUEST_TRAVEL_DETAIL_NONE, std::set<uint32> onlyQuestIds = {});
        /// 按过滤条件格式化并输出任务日志清单
        int ListQuests(Player* requester, bool completed, bool silent, QuestTravelDetail travelDetail, std::set<uint32> onlyQuestIds = {});
    };
}
