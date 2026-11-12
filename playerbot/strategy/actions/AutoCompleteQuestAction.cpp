#include "playerbot/playerbot.h"
#include "AutoCompleteQuestAction.h"

using namespace ai;

/// 执行动作主逻辑（自动完成任务动作）
bool AutoCompleteQuestAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    // Static list of quest IDs to auto-complete (支持自动完成的静态任务 ID 列表)
    static const std::vector<uint32> autoCompleteQuests = {
        0,     // Dummy quest : please remove when a classic quest is found that needs to be skipped. (占位示例任务：当发现经典旧世中需要跳过的任务时请替换此处。)
#ifdef MANGOSBOT_TWO  
        25229, // a-few-good-gnomes: Bot uses motivatron but it does nothing in game. (少数好侏儒任务：机器人使用激励器但游戏内无效果。)
        12641, // Death Comes From On High: Requires complex vehicle control. (任务“天降厄运”：需要复杂的石像鬼载具控制。)
#endif
    };

    static const std::vector<std::pair<uint32, uint8>> autoCompleteObjectives = {
        {0,     0}
#ifdef MANGOSBOT_TWO
        ,
        // {12779, 1}  // An End To All Things (second objective needs vehicle riding). ({12779, 1}  // 万物终结（第二个目标需要骑乘载具）)
#endif
    };

    bool completedQuest = false;

    bool isAutoCompleteQuest = false;
    bool isAutoCompleteObjective = false;

    // Check the bot's quest log for any active quests from the list (检查机器人任务日志中是否包含列表里的活跃任务)
    for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        uint32 questId = bot->GetQuestSlotQuestId(slot);
        if (!questId)
            continue;

        if (!ai->HasCheat(BotCheatMask::quest))
        {
            isAutoCompleteQuest = std::find(autoCompleteQuests.begin(), autoCompleteQuests.end(), questId) != autoCompleteQuests.end();
        }
        else
            isAutoCompleteQuest = true;

        Quest const* pQuest = sObjectMgr.GetQuestTemplate(questId);
        if (!pQuest)
            continue;

        if (bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE)
            continue;

        // Add quest items for quests that require items (为需要收集物品的任务添加相关任务道具)
        for (uint8 x = 0; x < QUEST_ITEM_OBJECTIVES_COUNT; ++x)
        {
            isAutoCompleteObjective = std::find(autoCompleteObjectives.begin(), autoCompleteObjectives.end(), std::make_pair(questId, x)) != autoCompleteObjectives.end();

            if (!isAutoCompleteQuest && !isAutoCompleteObjective)
                continue;

            uint32 id = pQuest->ReqItemId[x];
            uint32 count = pQuest->ReqItemCount[x];
            if (!id || !count)
                continue;

            uint32 curItemCount = bot->GetItemCount(id, true);

            ItemPosCountVec dest;
            uint8 msg = bot->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, id, count - curItemCount);
            if (msg == EQUIP_ERR_OK)
            {
                Item* item = bot->StoreNewItem(dest, id, true);
                bot->SendNewItem(item, count - curItemCount, true, false);
            }
        }

        // All creature/GO slain/casted (not required, but otherwise it will display "Creature slain 0/10") (所有生物/物体击杀或交互进度（非必需，否则会显示“击杀 0/10”）)
        for (uint8 i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        {
            isAutoCompleteObjective = std::find(autoCompleteObjectives.begin(), autoCompleteObjectives.end(), std::make_pair(questId, i)) != autoCompleteObjectives.end();

            if (!isAutoCompleteQuest && !isAutoCompleteObjective)
                continue;

            int32 creature = pQuest->ReqCreatureOrGOId[i];
            uint32 creaturecount = pQuest->ReqCreatureOrGOCount[i];

            if (uint32 spell_id = pQuest->ReqSpell[i])
            {
                for (uint16 z = 0; z < creaturecount; ++z)
                    bot->CastedCreatureOrGO(creature, ObjectGuid((creature > 0 ? HIGHGUID_UNIT : HIGHGUID_GAMEOBJECT), uint32(std::abs(creature)), 1u), spell_id);
            }
            else if (creature > 0)
            {
                if (CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(creature))
                    for (uint16 z = 0; z < creaturecount; ++z)
                        bot->KilledMonster(cInfo, nullptr);
            }
            else if (creature < 0)
            {
                for (uint16 z = 0; z < creaturecount; ++z)
                    bot->CastedCreatureOrGO(-creature, ObjectGuid(), 0);
            }
        }

        if (!isAutoCompleteQuest)
            continue;

#ifdef MANGOSBOT_TWO
        // player kills (玩家击杀数)
        if (pQuest->HasSpecialFlag(QUEST_SPECIAL_FLAGS_PLAYER_KILL))
            if (uint32 reqPlayers = pQuest->GetPlayersSlain())
                bot->KilledPlayerCreditForQuest(reqPlayers, pQuest);
#endif

        // If the quest requires reputation to complete (若该任务要求达到特定声望才能完成)
        if (uint32 repFaction = pQuest->GetRepObjectiveFaction())
        {
            uint32 repValue = pQuest->GetRepObjectiveValue();
            uint32 curRep = bot->GetReputationMgr().GetReputation(repFaction);
            if (curRep < repValue)
#ifndef MANGOSBOT_ONE
                if (FactionEntry const* factionEntry = sFactionStore.LookupEntry(repFaction))
#else
                if (FactionEntry const* factionEntry = sFactionStore.LookupEntry<FactionEntry>(repFaction))
#endif
                    bot->GetReputationMgr().SetReputation(factionEntry, repValue);
        }

        // If the quest requires money (若该任务要求缴纳金币)
        int32 ReqOrRewMoney = pQuest->GetRewOrReqMoney();
        if (ReqOrRewMoney < 0)
            bot->ModifyMoney(-ReqOrRewMoney);

        bot->CompleteQuest(questId);
        completedQuest = true;
    }

    if (completedQuest)
    {
        return true;
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（自动完成任务动作）
bool AutoCompleteQuestAction::isUseful()
{
    if (ai->HasActivePlayerMaster() && !ai->HasCheat(BotCheatMask::quest))
        return false;

    return true;
}
