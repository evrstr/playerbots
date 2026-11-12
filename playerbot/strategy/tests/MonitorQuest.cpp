/// 测试监听器：任务进度与交付状态断言实现
#include "playerbot/playerbot.h"
#include "MonitorQuest.h"
#include "Quests/QuestDef.h"
#include "TestRegistry.h"

using namespace ai;

// =====================================================
// Helpers | 辅助函数
// =====================================================
namespace
{
/// 从监控参数字符串开头解析出数字 ID
    uint32 ExtractLeadingId(const std::string& monitorStr)
    {
        size_t idStart = monitorStr.find_first_not_of(' ');
        if (idStart == std::string::npos)
            return 0;

        std::string idStr;
        size_t idEnd = monitorStr.find_first_of(" =><", idStart);
        if (idEnd == std::string::npos)
            idStr = monitorStr.substr(idStart);
        else
            idStr = monitorStr.substr(idStart, idEnd - idStart);

        char* endPtr = nullptr;
        unsigned long val = std::strtoul(idStr.c_str(), &endPtr, 10);
        if (endPtr == idStr.c_str() || val == 0)
            return 0;

        return static_cast<uint32>(val);
    }
}

// =====================================================
// MonitorQuestComplete
// Format: "quest complete <questId> => pass/fail \"message\""
// True when quest status is COMPLETE or has been rewarded
// =====================================================
/// 检测任务是否处于完成状态或已被标记为已领奖
bool MonitorQuestComplete::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    uint32 questId = ExtractLeadingId(monitorStr);
    if (!questId)
        return false;

    QuestStatus status = bot->GetQuestStatus(questId);
    if (status == QUEST_STATUS_COMPLETE)
        return true;

    // Also check rewarded | 同时检查已领奖状态
    auto it = bot->getQuestStatusMap().find(questId);
    if (it != bot->getQuestStatusMap().end() && it->second.m_rewarded)
        return true;

    return false;
}

// =====================================================
// MonitorQuestRewarded
// Format: "quest rewarded <questId> => pass/fail \"message\""
// True only when quest has been turned in and rewarded
// =====================================================
/// 检测任务是否已被交付并领奖
bool MonitorQuestRewarded::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    uint32 questId = ExtractLeadingId(monitorStr);
    if (!questId)
        return false;

    auto it = bot->getQuestStatusMap().find(questId);
    if (it != bot->getQuestStatusMap().end() && it->second.m_rewarded)
        return true;

    return false;
}

/// 检测任务是否已成功交付（不再处于未完成日志中或已领奖）
bool MonitorQuestTurnedIn::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    uint32 questId = ExtractLeadingId(monitorStr);
    if (!questId)
        return false;

    return bot->GetQuestStatus(questId) != QUEST_STATUS_COMPLETE;
}

// =====================================================
// MonitorQuestActive
// Format: "quest active <questId> => pass/fail \"message\""
// True when bot has the quest in their log (incomplete or complete, not rewarded/none)
// =====================================================
/// 检测任务当前是否处于任务日志激活状态
bool MonitorQuestActive::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    uint32 questId = ExtractLeadingId(monitorStr);
    if (!questId)
        return false;

    QuestStatus status = bot->GetQuestStatus(questId);
    return (status == QUEST_STATUS_INCOMPLETE || status == QUEST_STATUS_COMPLETE);
}

// =====================================================
// MonitorQuestObjective
// Format: "quest objective <questId> <objIndex> done => pass/fail \"message\""
// True when a specific objective (0-3) is fully satisfied
// =====================================================
/// 检测任务指定子目标（0-3）是否已完成或达到指定进度计数
bool MonitorQuestObjective::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    size_t idStart = monitorStr.find_first_not_of(' ');
    if (idStart == std::string::npos)
        return false;

    size_t idEnd = monitorStr.find(' ', idStart);
    if (idEnd == std::string::npos)
        return false;

    std::string idStr = monitorStr.substr(idStart, idEnd - idStart);
    uint32 questId = static_cast<uint32>(std::strtoul(idStr.c_str(), nullptr, 10));
    if (!questId)
        return false;

    // Extract objective index | 提取子目标索引
    size_t objStart = monitorStr.find_first_not_of(' ', idEnd);
    if (objStart == std::string::npos)
        return false;

    size_t objEnd = monitorStr.find_first_of(" =><", objStart);
    std::string objStr;
    if (objEnd == std::string::npos)
        objStr = monitorStr.substr(objStart);
    else
        objStr = monitorStr.substr(objStart, objEnd - objStart);

    uint32 objIndex = static_cast<uint32>(std::strtoul(objStr.c_str(), nullptr, 10));
    if (objIndex >= QUEST_OBJECTIVES_COUNT)
        return false;

    Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
    if (!quest)
        return false;

    auto it = bot->getQuestStatusMap().find(questId);
    if (it == bot->getQuestStatusMap().end())
        return false;

    const QuestStatusData& statusData = it->second;

    // Optional "count <op> <N>" form (partial progress), e.g. "quest objective 123 2 count > 0 => pass". | 可选 "count <op> <N>" 形式以检验部分进度；
    // Without it the objective must be fully satisfied ("done"). | 省略时要求该子目标完全达成（"done"）。
    size_t tokStart = monitorStr.find_first_not_of(" \t", objEnd == std::string::npos ? monitorStr.size() : objEnd);
    if (tokStart != std::string::npos && monitorStr.compare(tokStart, 5, "count") == 0)
    {
        size_t cmpStart = monitorStr.find_first_not_of(" \t", tokStart + 5);
        if (cmpStart == std::string::npos)
            return false;

        std::string op;
        std::string valueStr;
        std::string valueName;
        std::string parseMessage;
        if (TryParseComparisonValue(monitorStr.substr(cmpStart), valueName, op, valueStr, parseMessage, GetName()) != TestResult::PASS)
            return false;

        uint32 threshold = 0;
        if (TryParseUInt32Strict(valueStr, threshold, parseMessage, GetName()) != TestResult::PASS)
            return false;

        uint32 progress = 0;
        if (quest->ReqCreatureOrGOId[objIndex])
            progress = statusData.m_creatureOrGOcount[objIndex];
        else if (objIndex < QUEST_ITEM_OBJECTIVES_COUNT && quest->ReqItemId[objIndex])
            progress = bot->GetItemCount(quest->ReqItemId[objIndex], true);
        else
            return false;

        if (op == ">")
            return progress > threshold;
        if (op == "<")
            return progress < threshold;
        if (op == "==")
            return progress == threshold;
        if (op == "!=")
            return progress != threshold;

        return false;
    }

    // Check creature/GO count objective | 检查生物击杀或游戏对象交互计数目标
    if (quest->ReqCreatureOrGOId[objIndex])
    {
        return statusData.m_creatureOrGOcount[objIndex] >= quest->ReqCreatureOrGOCount[objIndex];
    }

    // Check item count objective (if objIndex < QUEST_ITEM_OBJECTIVES_COUNT) | 检查物品收集目标（若索引在物品目标数量范围内）
    if (objIndex < QUEST_ITEM_OBJECTIVES_COUNT && quest->ReqItemId[objIndex])
    {
        uint32 itemCount = bot->GetItemCount(quest->ReqItemId[objIndex], true);
        return itemCount >= quest->ReqItemCount[objIndex];
    }

    return false;
}

// =====================================================
// MonitorHasItem
// Format: "has item <itemId> => pass/fail \"message\""
// True when bot has at least 1 of the item
// =====================================================
/// 检测背包或银行中是否持有指定 ID 的物品
bool MonitorHasItem::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    uint32 itemId = ExtractLeadingId(monitorStr);
    if (!itemId)
        return false;

    return bot->GetItemCount(itemId, true) > 0;
}

// =====================================================
// MonitorOnMap
// Format: "on map <mapId> => pass/fail \"message\""
// True when bot is on the specified map
// =====================================================
/// 检测机器人当前是否位于指定地图 ID
bool MonitorOnMap::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    uint32 mapId = ExtractLeadingId(monitorStr);
    if (!mapId && monitorStr.find(" 0 ") == std::string::npos) // map 0 is valid
        return false;

    return bot->GetMapId() == mapId;
}

// =====================================================
// MonitorHasMount
// Format: "has mount => pass/fail \"message\""
// True when bot knows a mount spell
// =====================================================
/// 检测机器人是否学会任意坐骑法术（含 DK 死亡战马）
bool MonitorHasMount::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    // Check common DK mount spell (Acherus Deathcharger) | 检查常见死亡骑士职业坐骑（阿彻鲁斯死亡战马）
    // SpellID 48778 = Acherus Deathcharger | 法术 ID 48778 = 阿彻鲁斯死亡战马
    if (bot->HasSpell(48778))
        return true;

    // Check generic mount spells - any riding skill mount | 检查通用坐骑法术（任何具有骑乘光环的法术）
    const PlayerSpellMap& spellMap = bot->GetSpellMap();
    for (const auto& pair : spellMap)
    {
        if (pair.second.state == PLAYERSPELL_REMOVED)
            continue;

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(pair.first);
        if (!spellInfo)
            continue;

        // Check if it's a mount spell (has SPELL_AURA_MOUNTED effect) | 判断法术是否包含 SPELL_AURA_MOUNTED 光环效果
        for (int i = 0; i < 3; ++i)
        {
            if (spellInfo->EffectApplyAuraName[i] == SPELL_AURA_MOUNTED)
                return true;
        }
    }

    return false;
}

// =====================================================
// MonitorNpcDead | MonitorNpcDead：任务发布/交付 NPC 死亡中断检测
// Format: "npc dead <location> => abort \"message\""
// True when the named creature location has no live unit on the bot's map
// (giver/taker died or despawned mid-test). GameObject locations are not
// covered, mirroring the setup-time require.
// =====================================================
/// 检测任务关联的生物 NPC 是否已在世界地图上死亡或消失
bool MonitorNpcDead::IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const
{
    std::string locName = monitorStr;
    size_t arrow = locName.find("=>");
    if (arrow != std::string::npos)
        locName = locName.substr(0, arrow);
    size_t nameStart = locName.find_first_not_of(" \t");
    if (nameStart == std::string::npos)
        return false;
    size_t nameEnd = locName.find_last_not_of(" \t");
    locName = locName.substr(nameStart, nameEnd - nameStart + 1);
    if (locName.empty())
        return false;

    GuidPosition loc;
    if (!TestRegistry::ParseLocation(locName, loc))
        return false;

    if (!loc || !loc.IsCreature() || !loc.GetEntry())
        return false;

    if (!bot->IsInWorld() || !bot->GetMap())
        return false;

    uint32 instanceId = bot->GetMapId() == loc.getMapId() ? bot->GetInstanceId() : 0;

    Creature* liveNpc = loc.GetCreature(instanceId);
    if (!liveNpc)
        return false;

    if (!liveNpc->IsAlive())
        return true;

    return false;
}
