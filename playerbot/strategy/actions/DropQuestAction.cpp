
#include "playerbot/playerbot.h"
#include "DropQuestAction.h"

using namespace ai;

/// 执行动作主逻辑（放弃任务指令动作）
bool DropQuestAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    std::string link = event.getParam();
    if (!GetMaster())
        return false;

    PlayerbotChatHandler handler(GetMaster());
    uint32 entry = handler.extractQuestId(link);
    bool dropped = false;

    // remove all quest entries for 'entry' from quest log (从任务日志中移除指定任务的所有条目)
    for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        uint32 logQuest = bot->GetQuestSlotQuestId(slot);
        Quest const* quest = sObjectMgr.GetQuestTemplate(logQuest);
        if (!quest)
            continue;

        if (logQuest == entry || link.find(quest->GetTitle()) != std::string::npos || link == "all")
        {
            bot->SetQuestSlot(slot, 0);

            // we ignore unequippable quest items in this case, its' still be equipped (此处忽略不可穿戴的任务道具，其余按常规装备逻辑处理)
            bot->TakeQuestSourceItem(logQuest, false);
            entry = logQuest;

            bot->SetQuestStatus(entry, QUEST_STATUS_NONE);
            bot->getQuestStatusMap()[entry].m_rewarded = false;

            dropped = true;

            if (link != "all")
                break;
        }
    }

    if(dropped)
        ai->TellPlayer(requester, BOT_TEXT("quest_remove"));

    return dropped;
}

/// 执行动作主逻辑（清理任务日志动作）
bool CleanQuestLogAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    std::string link = event.getParam();
    if (ai->HasActivePlayerMaster())
        return false;

    uint8 totalQuests = 0;

    DropQuestType(requester, totalQuests); // Count the total quests (统计当前总任务数量)

    // Drop failed quests. Unconditional: the counting pass used to do this on (放弃已失败任务（无条件执行：旧计数流程仅在特定槽位触发）)
    // every call as a side effect of the bug fixed here, and it ran before this (每次调用的副作用，且在修复之前就会执行)
    // threshold was evaluated, so gating it on the threshold would leave failed (阈值此前已评估过，若再以阈值过滤会导致失败任务残留)
    // quests holding slots whenever the log is between 4 and 6 slots from full. (当任务日志距离上限还剩 4~6 格时，清理占位的低价值任务。)
    DropQuestType(requester, totalQuests, MAX_QUEST_LOG_SIZE, true, true);

    if (MAX_QUEST_LOG_SIZE - totalQuests > 6)
        return true;

    if (AI_VALUE(bool, "can fight equal")) // Only drop gray quests when able to fight proper lvl quests. (仅在能够接取合适等级的任务时才放弃灰色低级任务。)
    {
        DropQuestType(requester, totalQuests, MAX_QUEST_LOG_SIZE - 6); // Drop gray/red quests. (放弃灰色或红色难度任务。)
        DropQuestType(requester, totalQuests, MAX_QUEST_LOG_SIZE - 6, false, true); // Drop gray/red quests with progress. (放弃已有部分进度的灰色或红色任务。)
        DropQuestType(requester, totalQuests, MAX_QUEST_LOG_SIZE - 6, false, true, true); // Drop gray/red completed quests. (放弃灰色或红色等级的已完成任务。)
    }

    if (MAX_QUEST_LOG_SIZE - totalQuests > 4)
        return true;

    DropQuestType(requester, totalQuests, MAX_QUEST_LOG_SIZE - 4, true); // Drop quests without progress. (放弃尚无任何进度的任务。)

    if (MAX_QUEST_LOG_SIZE - totalQuests > 2)
        return true;

    DropQuestType(requester, totalQuests, MAX_QUEST_LOG_SIZE - 2, true, true); // Drop quests with progress. (放弃已有部分进度的任务。)

    if (MAX_QUEST_LOG_SIZE - totalQuests > 0)
        return true;

    DropQuestType(requester, totalQuests, MAX_QUEST_LOG_SIZE - 1, true, true, true); // Drop completed quests. (放弃或清理已完成（待交）任务。)

    if (MAX_QUEST_LOG_SIZE - totalQuests > 0)
        return true;

    return false;
}

/// 按指定条件批量放弃符合类型的任务
void CleanQuestLogAction::DropQuestType(Player* requester, uint8 &numQuest, uint8 wantNum, bool isGreen, bool hasProgress, bool isComplete)
{
    std::vector<uint8> slots;

    for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
        slots.push_back(slot);


    if (wantNum < 100)
    {
        std::shuffle(slots.begin(), slots.end(), *GetRandomGenerator());
    }

    for (uint8 slot : slots)
    {
        uint32 questId = bot->GetQuestSlotQuestId(slot);

        if (!questId)
            continue;

        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
        if (!quest)
            continue;

        // Counting pass: count every countable slot and drop nothing. Failed and (计数阶段：仅统计可计数的任务槽位且不放弃任何任务；失败与)
        // class specific quests hold a slot too, and dropping one here decremented (职业专属任务同样占用一个槽位，此处放弃会导致计数减少)
        // a counter that had not counted it, wrapping the uint8 to 255 - after (未计入该任务的计数器会导致 uint8 下溢为 255 —— 之后)
        // which every later pass saw a full log and pruned until it wrapped back. (导致后续每次遍历都误判任务日志已满并持续清理直到计数回绕。)
        if (wantNum == 100)
        {
            numQuest++;
            continue;
        }

        if (bot->GetQuestStatus(questId) != QUEST_STATUS_FAILED)
        {
            if (quest->GetRequiredClasses()) // Do not drop class specific quests (不要放弃职业专属任务)
                continue;

            int32 lowLevelDiff = sWorld.getConfig(CONFIG_INT32_QUEST_LOW_LEVEL_HIDE_DIFF);
            if (lowLevelDiff < 0 || bot->GetLevel() <= bot->GetQuestLevelForPlayer(quest) + uint32(lowLevelDiff)) // Quest is not gray (任务非灰色)
            {
                if (bot->GetLevel() + 5 > bot->GetQuestLevelForPlayer(quest)) // Quest is not red (任务非红色（非过高难度）)
                    if (!isGreen)
                        continue;
            }
            else // Quest is gray (任务为灰色（低等级）)
            {
                if (isGreen)
                    continue;
            }

            if (HasProgress(bot, quest) && !hasProgress && bot->GetQuestStatus(questId) != QUEST_STATUS_FAILED)
                continue;

            if (bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE && !isComplete)
                continue;

            if (numQuest <= wantNum)
                continue;
        }

        // Drop quest. (放弃该任务。)
        bot->GetPlayerbotAI()->DropQuest(questId);

        if (numQuest)
            numQuest--;

        ai->TellPlayer(requester, BOT_TEXT("quest_remove") + " " + chat->formatQuest(quest), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
    }
}

/// 检查指定任务是否已有击杀或物品收集进度
bool CleanQuestLogAction::HasProgress(Player* bot, Quest const* quest)
{
    uint32 questId = quest->GetQuestId();

    if (bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE)
        return true;

    QuestStatusData questStatus = bot->getQuestStatusMap()[questId];

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
    {
        if (!quest->ObjectiveText[i].empty())
            return true;

        if (quest->ReqItemId[i])
        {
            int required = quest->ReqItemCount[i];
            int available = questStatus.m_itemcount[i];
            if (available > 0 && required > 0)
                return true;
        }

        if (quest->ReqCreatureOrGOId[i])
        {
            int required = quest->ReqCreatureOrGOCount[i];
            int available = questStatus.m_creatureOrGOcount[i];

            if (available > 0 && required > 0)
                return true;
        }
    }

    return false;
}
