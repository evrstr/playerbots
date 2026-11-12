/// 任务自动接取与交付策略头文件
#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    /// 策略基类：响应任务共享与任务命令的基础任务策略
    class QuestStrategy : public PassTroughStrategy
    {
    public:
        QuestStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override {};
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override {}
    };

    /// 策略：常规任务交互策略（在对话/交任务时辅助交互）
    class DefaultQuestStrategy : public QuestStrategy
    {
    public:
        DefaultQuestStrategy(PlayerbotAI* ai) : QuestStrategy(ai) {}
        std::string getName() override { return "quest"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：全接任务策略（与任务发布者交互时自动接受全部可接任务）
    class AcceptAllQuestsStrategy : public QuestStrategy
    {
    public:
        AcceptAllQuestsStrategy(PlayerbotAI* ai) : QuestStrategy(ai) {}
        std::string getName() override { return "accept all quests"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
