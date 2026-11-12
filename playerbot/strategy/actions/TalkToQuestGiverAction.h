#pragma once

#include "playerbot/strategy/Action.h"
#include "QuestAction.h"

namespace ai
{
    /// 与任务发布者对话动作：与附近任务 NPC 交互以接取或交付任务
    class TalkToQuestGiverAction : public QuestAction 
    {
    public:
        /// 构造函数：初始化与任务发布者对话动作
        TalkToQuestGiverAction(PlayerbotAI* ai) : QuestAction(ai, "talk to quest giver") {}

    protected:
        /// 处理单个任务发布对象的任务接取或交付逻辑（与任务发布者对话动作）
        virtual bool ProcessQuest(Player* requester, Quest const* quest, WorldObject* questGiver) override;

    private:
        /// 前往或与 NPC 交互完成指定任务的交付
        bool TurnInQuest(Player* requester, Quest const* quest, WorldObject* questGiver, std::string& out);
        /// 处理无物品奖励的纯经验/声望/金币任务交付
        void RewardNoItem(Quest const* quest, WorldObject* questGiver, std::string& out);
        /// 处理只有一个奖励或直接领取单一物品奖励的逻辑
        void RewardSingleItem(Quest const* quest, WorldObject* questGiver, std::string& out);
        /// 评估任务可选奖励物品并筛选评分最高的选项
        std::set<uint32> BestRewards(Quest const* quest);
        /// 处理包含多个可选奖励的任务交付逻辑
        void RewardMultipleItem(Player* requester, Quest const* quest, WorldObject* questGiver, std::string& out);
        /// 当存在多个可选奖励时向主人发送奖励选择询问
        void AskToSelectReward(Player* requester, Quest const* quest, std::string& out, bool forEquip);
    };
}
