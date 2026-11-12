#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 放弃任务指令动作：根据指令或任务日志容量自动放弃指定或低级任务
    class DropQuestAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化放弃任务指令动作
        DropQuestAction(PlayerbotAI* ai) : ChatCommandAction(ai, "drop quest") {}
        /// 执行动作主逻辑（放弃任务指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（放弃任务指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "drop quest"; }
        virtual std::string GetHelpDescription()
        {
            return "This command makes the bot drop a specific quest.\n"
                   "Usage: drop [quest_name or link]\n"
                   "Example: drop [The Missing Diplomat] (drops the specified quest)";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

    /// 清理任务日志动作：自动清理灰色、失败或低收益任务以腾出日志空间
    class CleanQuestLogAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化清理任务日志动作
        CleanQuestLogAction(PlayerbotAI* ai) : ChatCommandAction(ai, "clean quest log") {}
        /// 执行动作主逻辑（清理任务日志动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（清理任务日志动作）
        virtual bool isUsefulWhenStunned() override { return true; }

        /// 判断当前状态下该动作是否可用/有效（清理任务日志动作）
        virtual bool isUseful() override { return ai->HasStrategy("rpg quest", BotState::BOT_STATE_NON_COMBAT); }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "clean quest log"; }
        virtual std::string GetHelpDescription()
        {
            return "This command makes the bot automatically drop certain quests to make room for new ones.\n"
                   "It selects quests to drop based on priority (ie. gray without progress ones first)\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"can fight equal"}; }
#endif 

        /// 按指定条件批量放弃符合类型的任务
        void DropQuestType(Player* requester, uint8& numQuest, uint8 wantNum = 100, bool isGreen = false, bool hasProgress = false, bool isComplete = false);

        /// 检查指定任务是否已有击杀或物品收集进度
        static bool HasProgress(Player* bot, Quest const* quest);
    };
}
