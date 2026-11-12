/// 任务自动接取与交付策略实现

#include "playerbot/playerbot.h"
#include "QuestStrategies.h"

using namespace ai;

/// 构造基础任务策略并注册 accept quest 透传支持
QuestStrategy::QuestStrategy(PlayerbotAI* ai) : PassTroughStrategy(ai)
{
    supported.push_back("accept quest");
}

/// 初始化基础任务非战斗触发器：自动接受队友共享任务
void QuestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PassTroughStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode("quest share", NextAction::array(0, new NextAction("accept quest share", relevance), NULL)));
};

/// 初始化默认任务策略：触发对话接取/交付当前可选任务
void DefaultQuestStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    QuestStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "use game object",
        NextAction::array(0,
            new NextAction("talk to quest giver", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "gossip hello",
        NextAction::array(0,
            new NextAction("talk to quest giver", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "complete quest",
        NextAction::array(0, new NextAction("talk to quest giver", relevance), NULL)));
}

/// 初始化全接任务策略：与任务 NPC 或物体交互时自动接取全部可用任务
void AcceptAllQuestsStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    QuestStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "use game object",
        NextAction::array(0,
            new NextAction("talk to quest giver", relevance), new NextAction("accept all quests", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "gossip hello",
        NextAction::array(0,
            new NextAction("talk to quest giver", relevance), new NextAction("accept all quests", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "complete quest",
        NextAction::array(0, 
            new NextAction("talk to quest giver", relevance), new NextAction("accept all quests", relevance), NULL)));
}
