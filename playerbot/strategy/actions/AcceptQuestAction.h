#pragma once

#include "playerbot/strategy/Action.h"
#include "QuestAction.h"

namespace ai
{
    /// 接受全部任务动作：从选定或附近的任务发布者处接受所有可用任务
    class AcceptAllQuestsAction : public QuestAction 
    {
    public:
        /// 构造函数：初始化接受全部任务动作
        AcceptAllQuestsAction(PlayerbotAI* ai, std::string name = "accept all quests") : QuestAction(ai, name) {}
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（接受全部任务动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    protected:
        /// 处理单个任务发布对象的任务接取或交付逻辑（接受全部任务动作）
        virtual bool ProcessQuest(Player* requester, Quest const* quest, WorldObject* questGiver) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "accept all quests"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action wil accept all quests from the npc selected by the master\n"
                "It will use all nearby quest givers if none is selected.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs" ,  "nearest game objects no los" }; }
#endif 
    };

    /// 接受指定任务动作：根据任务链接或通配符从附近发布者处接受任务
    class AcceptQuestAction : public AcceptAllQuestsAction 
    {
    public:
        /// 构造函数：初始化接受指定任务动作
        AcceptQuestAction(PlayerbotAI* ai) : AcceptAllQuestsAction(ai, "accept quest") {}
        /// 执行动作主逻辑（接受指定任务动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（接受指定任务动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "accept quests"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action wil accept a specified quest (link or *) from any nearby quest giver.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { }; }
        virtual std::vector<std::string> GetUsedValues() { return { "nearest npcs" ,  "nearest game objects no los" }; }
#endif 
    };

    /// 接受共享任务动作：自动接受队友共享的任务
    class AcceptQuestShareAction : public Action 
    {
    public:
        /// 构造函数：初始化接受共享任务动作
        AcceptQuestShareAction(PlayerbotAI* ai) : Action(ai, "accept quest share") {}
        /// 执行动作主逻辑（接受共享任务动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "accept quest share"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action will make a bot click accept when shared a quest.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { }; }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    /// 确认任务动作：在任务确认界面点击接受以开启任务
    class ConfirmQuestAction : public Action {
    public:
        /// 构造函数：初始化确认任务动作
        ConfirmQuestAction(PlayerbotAI* ai) : Action(ai, "confirm quest") {}
        /// 执行动作主逻辑（确认任务动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "confirm quest"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action will make a bot click accept asked to start a quest.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { }; }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    /// 任务详情确认动作：在任务详情页面点击接受任务
    class QuestDetailsAction : public Action {
    public:
        /// 构造函数：初始化任务详情确认动作
        QuestDetailsAction(PlayerbotAI* ai) : Action(ai, "quest details") {}
        /// 执行动作主逻辑（任务详情确认动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "quest details"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action will make a bot click accept in the quest details page.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { }; }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };
}
