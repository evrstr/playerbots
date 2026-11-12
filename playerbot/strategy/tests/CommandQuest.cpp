/// 测试命令：任务状态配置与通用聊天命令执行实现
#include "playerbot/playerbot.h"
#include "CommandQuest.h"
#include "Quests/QuestDef.h"
#include "Globals/ObjectMgr.h"
#include <sstream>

using namespace ai;

// =====================================================
// CommandSetupAcceptQuest | 强制接取任务命令
// Format: "accept quest <questId>" | 格式："accept quest <questId>"
// =====================================================
/// 执行 accept quest 命令：校验并强制为机器人接取指定任务，同时发放起始任务物品
TestResult CommandSetupAcceptQuest::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string questStr = params;
    // Strip "quest " prefix if present from params | 若参数带有 "quest " 前缀则先剥离
    if (questStr.find("quest ") == 0)
        questStr = questStr.substr(6);

    uint32 questId = static_cast<uint32>(std::strtoul(questStr.c_str(), nullptr, 10));
    if (!questId)
    {
        message = "Invalid quest ID: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
    if (!quest)
    {
        message = "Quest template not found: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    // Check if already has this quest | 检查机器人是否已持有或已完成该任务
    QuestStatus status = bot->GetQuestStatus(questId);
    if (status == QUEST_STATUS_INCOMPLETE || status == QUEST_STATUS_COMPLETE)
        return TestResult::PASS; // Already have it

    if (!bot->CanAddQuest(quest, false))
    {
        message = "Bot cannot accept quest " + questStr + " (log full or requirements not met)";
        return TestResult::IMPOSSIBLE;
    }

    bot->AddQuest(quest, nullptr);
    bot->GiveQuestSourceItemIfNeed(quest);

    if (uint32 sourceItemId = quest->GetSrcItemId())
    {
        uint32 sourceItemCount = std::max<uint32>(1, quest->GetSrcItemCount());
        if (bot->GetItemCount(sourceItemId, true) < sourceItemCount)
        {
            message = "Quest " + questStr + " accepted but missing required source item " + std::to_string(sourceItemId);
            return TestResult::IMPOSSIBLE;
        }
    }

    return TestResult::PASS;
}

// =====================================================
// CommandSetupForceCompleteQuest | 强制完成任务全部目标命令
// Format: "complete quest <questId>" | 格式："complete quest <questId>"
// Force-completes all objectives (items + creature/GO counts) | 强制满足物品收集与怪物/对象交互计数
// =====================================================
/// 执行 complete quest 命令：自动补齐任务物品并触发所有击杀/交互计数
TestResult CommandSetupForceCompleteQuest::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string questStr = params;
    if (questStr.find("quest ") == 0)
        questStr = questStr.substr(6);

    uint32 questId = static_cast<uint32>(std::strtoul(questStr.c_str(), nullptr, 10));
    if (!questId)
    {
        message = "Invalid quest ID: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
    if (!quest)
    {
        message = "Quest template not found: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    QuestStatus status = bot->GetQuestStatus(questId);
    if (status == QUEST_STATUS_NONE)
    {
        message = "Bot does not have quest " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    if (status == QUEST_STATUS_COMPLETE)
        return TestResult::PASS;

    // Satisfy item objectives | 满足所有任务物品需求
    for (uint8 i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
    {
        uint32 itemId = quest->ReqItemId[i];
        uint32 count = quest->ReqItemCount[i];
        if (!itemId || !count)
            continue;

        uint32 curCount = bot->GetItemCount(itemId, true);
        if (curCount >= count)
            continue;

        ItemPosCountVec dest;
        uint8 msg = bot->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count - curCount);
        if (msg != EQUIP_ERR_OK)
        {
            message = "Cannot store quest item " + std::to_string(itemId) + " (bag full?)";
            return TestResult::IMPOSSIBLE;
        }
        Item* item = bot->StoreNewItem(dest, itemId, true);
        bot->SendNewItem(item, count - curCount, true, false);
    }

    // Satisfy creature/GO kill objectives | 满足所有生物击杀或游戏对象交互计数
    for (uint8 i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
    {
        int32 creature = quest->ReqCreatureOrGOId[i];
        uint32 creatureCount = quest->ReqCreatureOrGOCount[i];
        if (!creature || !creatureCount)
            continue;

        if (uint32 spellId = quest->ReqSpell[i])
        {
            for (uint32 z = 0; z < creatureCount; ++z)
                bot->CastedCreatureOrGO(creature, ObjectGuid((creature > 0 ? HIGHGUID_UNIT : HIGHGUID_GAMEOBJECT), uint32(std::abs(creature)), 1u), spellId);
        }
        else if (creature > 0)
        {
            CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(creature);
            if (cInfo)
            {
                for (uint32 z = 0; z < creatureCount; ++z)
                    bot->KilledMonster(cInfo, nullptr);
            }
        }
        else if (creature < 0)
        {
            for (uint32 z = 0; z < creatureCount; ++z)
                bot->CastedCreatureOrGO(creature, ObjectGuid(HIGHGUID_GAMEOBJECT, uint32(std::abs(creature)), 1u), 0);
        }
    }

    bot->CompleteQuest(questId);

    return bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE ? TestResult::PASS : TestResult::IMPOSSIBLE;
}

// =====================================================
// CommandSetupRewardQuest | 强制直接结算任务奖励命令
// Format: "reward quest <questId>" | 格式："reward quest <questId>"
// Completes objectives and rewards the quest immediately | 补齐任务目标并立即发放奖励
// =====================================================
/// 执行 reward quest 命令：若未领奖则直接完成目标并结算任务奖励
TestResult CommandSetupRewardQuest::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string questStr = params;
    if (questStr.find("quest ") == 0)
        questStr = questStr.substr(6);

    uint32 questId = static_cast<uint32>(std::strtoul(questStr.c_str(), nullptr, 10));
    if (!questId)
    {
        message = "Invalid quest ID: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
    if (!quest)
    {
        message = "Quest template not found: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    // Check if already rewarded | 检查任务是否已经领过奖励
    auto it = bot->getQuestStatusMap().find(questId);
    if (it != bot->getQuestStatusMap().end() && it->second.m_rewarded)
        return TestResult::PASS;

    // Accept if not already | 若尚未接取则先接取任务
    QuestStatus status = bot->GetQuestStatus(questId);
    if (status == QUEST_STATUS_NONE)
    {
        if (!bot->CanAddQuest(quest, false))
        {
            message = "Bot cannot accept quest " + questStr;
            return TestResult::IMPOSSIBLE;
        }
        bot->AddQuest(quest, nullptr);
    }

    // Satisfy all objectives | 满足全部任务目标
    for (uint8 i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
    {
        uint32 itemId = quest->ReqItemId[i];
        uint32 count = quest->ReqItemCount[i];
        if (!itemId || !count)
            continue;

        uint32 curCount = bot->GetItemCount(itemId, true);
        if (curCount >= count)
            continue;

        ItemPosCountVec dest;
        uint8 msg = bot->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count - curCount);
        if (msg != EQUIP_ERR_OK)
        {
            message = "Cannot store quest item " + std::to_string(itemId) + " (bag full?)";
            return TestResult::IMPOSSIBLE;
        }
        Item* item = bot->StoreNewItem(dest, itemId, true);
        bot->SendNewItem(item, count - curCount, true, false);
    }

    for (uint8 i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
    {
        int32 creature = quest->ReqCreatureOrGOId[i];
        uint32 creatureCount = quest->ReqCreatureOrGOCount[i];
        if (!creature || !creatureCount)
            continue;

        if (uint32 spellId = quest->ReqSpell[i])
        {
            for (uint32 z = 0; z < creatureCount; ++z)
                bot->CastedCreatureOrGO(creature, ObjectGuid((creature > 0 ? HIGHGUID_UNIT : HIGHGUID_GAMEOBJECT), uint32(std::abs(creature)), 1u), spellId);
        }
        else if (creature > 0)
        {
            CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(creature);
            if (cInfo)
                for (uint32 z = 0; z < creatureCount; ++z)
                    bot->KilledMonster(cInfo, nullptr);
        }
        else if (creature < 0)
        {
            for (uint32 z = 0; z < creatureCount; ++z)
                bot->CastedCreatureOrGO(creature, ObjectGuid(HIGHGUID_GAMEOBJECT, uint32(std::abs(creature)), 1u), 0);
        }
    }

    // Reward the quest | 结算任务奖励
    bot->RewardQuest(quest, 0, bot, false);

    return TestResult::PASS;
}

// =====================================================
// CommandSetupForceObjectives | 强制满足部分任务目标命令
// Format: "force objectives <questId> except <objIndex>" | 格式："force objectives <questId> except <objIndex>"
// Satisfies every objective of an ACTIVE quest except the given creature/GO objective index | 满足除指定索引外的全部激活任务目标（注入物品或计入击杀数），
// (items get injected, creature counts credited). Used by the quest-clear test flavor. | 专用于孤立测试单一任务目标（objIndex 为空表示满足所有目标）。
// =====================================================
/// 执行 force objectives 命令：强行满足除指定目标索引外的所有任务条件
TestResult CommandSetupForceObjectives::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    // params: "<questId> except <objIndex>" | 参数格式："<questId> except <objIndex>"
    std::istringstream in(params);
    std::string questStr;
    std::string exceptKeyword;
    std::string objStr;
    in >> questStr >> exceptKeyword >> objStr;

    uint32 questId = static_cast<uint32>(std::strtoul(questStr.c_str(), nullptr, 10));
    if (!questId)
    {
        message = "Invalid quest ID: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
    if (!quest)
    {
        message = "Quest template not found: " + questStr;
        return TestResult::IMPOSSIBLE;
    }

    if (exceptKeyword != "except")
    {
        message = "Usage: force objectives <questId> except <objIndex>";
        return TestResult::IMPOSSIBLE;
    }

    if (objStr.empty() || objStr.find_first_not_of("0123456789") != std::string::npos)
    {
        message = "Invalid objective index: " + objStr;
        return TestResult::IMPOSSIBLE;
    }

    int32 exceptIndex = static_cast<int32>(std::strtol(objStr.c_str(), nullptr, 10));
    if (exceptIndex >= QUEST_ITEM_OBJECTIVES_COUNT)
    {
        message = "Objective index out of range: " + objStr;
        return TestResult::IMPOSSIBLE;
    }

    QuestStatus status = bot->GetQuestStatus(questId);
    if (status != QUEST_STATUS_INCOMPLETE && status != QUEST_STATUS_COMPLETE)
    {
        message = "Bot does not have quest " + questStr + " active";
        return TestResult::IMPOSSIBLE;
    }

    // Satisfy item objectives | 满足全部物品需求
    for (uint8 i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
    {
        if (static_cast<int32>(i) == exceptIndex)
            continue;

        uint32 itemId = quest->ReqItemId[i];
        uint32 count = quest->ReqItemCount[i];
        if (!itemId || !count)
            continue;

        uint32 curCount = bot->GetItemCount(itemId, true);
        if (curCount >= count)
            continue;

        ItemPosCountVec dest;
        uint8 msg = bot->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count - curCount);
        if (msg != EQUIP_ERR_OK)
        {
            message = "Cannot store quest item " + std::to_string(itemId) + " (bag full?)";
            return TestResult::IMPOSSIBLE;
        }
        Item* item = bot->StoreNewItem(dest, itemId, true);
        bot->SendNewItem(item, count - curCount, true, false);
    }

    // Satisfy creature/GO objectives | 满足非排除索引的生物/游戏对象目标
    for (uint8 i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
    {
        if (static_cast<int32>(i) == exceptIndex)
            continue;

        int32 creature = quest->ReqCreatureOrGOId[i];
        uint32 creatureCount = quest->ReqCreatureOrGOCount[i];
        if (!creature || !creatureCount)
            continue;

        if (uint32 spellId = quest->ReqSpell[i])
        {
            for (uint32 z = 0; z < creatureCount; ++z)
                bot->CastedCreatureOrGO(creature, ObjectGuid((creature > 0 ? HIGHGUID_UNIT : HIGHGUID_GAMEOBJECT), uint32(std::abs(creature)), 1u), spellId);
        }
        else if (creature > 0)
        {
            CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(creature);
            if (cInfo)
                for (uint32 z = 0; z < creatureCount; ++z)
                    bot->KilledMonster(cInfo, nullptr);
        }
        else if (creature < 0)
        {
            for (uint32 z = 0; z < creatureCount; ++z)
                bot->CastedCreatureOrGO(creature, ObjectGuid(HIGHGUID_GAMEOBJECT, uint32(std::abs(creature)), 1u), 0);
        }
    }

    return TestResult::PASS;
}

// =====================================================
// CommandSetupDo// Format: "do <chat command>" | 执行机器人聊天指令命令 | 格式："do <chat command>"
// Executes a bot chat command (like equip upgrades, accept quest, etc.) | 转发执行任意机器人聊天命令（如装备升级、接任务等）
// =====================================================
/// 执行 do 命令：通过耳语消息向机器人 AI 分发任意聊天控制指令
TestResult CommandSetupDo::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    if (params.empty())
    {
        message = "No command specified for 'do'";
        return TestResult::IMPOSSIBLE;
    }

    ai->HandleCommand(ChatMsg::CHAT_MSG_WHISPER, params, *bot);
    return TestResult::PASS;
}
