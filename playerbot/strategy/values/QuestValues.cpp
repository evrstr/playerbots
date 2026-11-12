// 策略值实现：QuestValues（全服任务索引构建、进度检查、对话状态计算与物品任务交互）

#include "playerbot/playerbot.h"
#include "QuestValues.h"
#include "SharedValueContext.h"
#include "ItemUsageValue.h"
#include "playerbot/TravelMgr.h"
#include "playerbot/strategy/deathknight/DKActions.h"

using namespace ai;


//What kind of a relation does this entry have with this quest. | 统计每个生物/对象 Entry 与各个任务之间的关联类型
// 汇总数据库任务发布者、接收者、击杀、掉落、购买及物品需求目标关系（含死亡骑士新手村等硬编码特例）
EntryQuestRelationMap EntryQuestRelationMapValue::Calculate()
{
    EntryQuestRelationMap rMap;

    //Quest givers takers | 记录任务的接取与交付对象
    QuestObjectMgr* questObjectMgr = (QuestObjectMgr*)&sObjectMgr;

    for (auto [entry, questId] : questObjectMgr->GetCreatureQuestRelationsMap())
        rMap[entry][questId] |= (uint8)TravelDestinationPurpose::QuestGiver;

    for (auto [entry, questId] : questObjectMgr->GetCreatureQuestInvolvedRelationsMap())
        rMap[entry][questId] |= (uint8)TravelDestinationPurpose::QuestTaker;

    for (auto [entry, questId] : questObjectMgr->GetGOQuestRelationsMap())
        rMap[-(int32)entry][questId] |= (uint8)TravelDestinationPurpose::QuestGiver;

    for (auto [entry, questId] : questObjectMgr->GetGOQuestInvolvedRelationsMap())
        rMap[-(int32)entry][questId] |= (uint8)TravelDestinationPurpose::QuestTaker;

    //Quest objectives | 解析任务模板中的各类目标需求
    ObjectMgr::QuestMap const& questMap = sObjectMgr.GetQuestTemplates();

    for (auto& [questId, questPtr] : questMap)
    {
        Quest* quest = questPtr.get();

        for (uint32 objective = 0; objective < QUEST_OBJECTIVES_COUNT; objective++)
        {
            uint32 relationFlag = 1 << (objective+1);

            //Kill objective | 击杀生物或交互游戏对象目标
            if (quest->ReqCreatureOrGOId[objective])
                rMap[quest->ReqCreatureOrGOId[objective]][questId] |= relationFlag;

            //Loot objective | 拾取物品目标：通过掉落表与衍生物品建立关联
            if (quest->ReqItemId[objective])
            {
                uint32 itemId = quest->ReqItemId[objective];
                while (itemId)
                {
                    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);

                    if (proto)
                    {
                        for (auto& entry : GAI_VALUE2(std::list<int32>, "item drop list", itemId))
                        {
                            std::string chanceQualifier = std::to_string(entry) + " " + std::to_string(itemId);
                            if (proto->Class == ITEM_CLASS_QUEST || GAI_VALUE2(float, "loot chance", chanceQualifier) > 5.0f)
                                rMap[entry][questId] |= relationFlag;
                        }
                    }

                    itemId = ItemUsageValue::ItemCreatedFrom(itemId);
                }
            }

            //Buy from vendor objective | 需要从商人购买的物品目标
            if (quest->ReqItemId[objective])
            {
                for (auto& entry : GAI_VALUE2(std::list<int32>, "item vendor list", quest->ReqItemId[objective]))
                    rMap[entry][questId] |= relationFlag;
            }
        }

        //Target entry of source item of quest.  | 绑定了任务起始物品所需交互的目标生物/对象
        if (quest->GetSrcItemId())
        {
            ItemRequiredTargetMapBounds bounds = sObjectMgr.GetItemRequiredTargetMapBounds(quest->GetSrcItemId());

            if (bounds.first != bounds.second) //Add target of source item to second quest objective. | 将起始物品关联的目标登记为 QuestObjective2
                for (ItemRequiredTargetMap::const_iterator itr = bounds.first; itr != bounds.second; ++itr)
                    rMap[itr->second.m_uiTargetEntry][questId] |= (uint8)TravelDestinationPurpose::QuestObjective2;
        }
    }

    //Hard coded: | 硬编码补充特殊脚本任务（如死亡骑士新手村系列）目标关联
#ifdef MANGOSBOT_TWO
    rMap[28406][12733] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Death Knight Initiate][Death's Challenge]
    rMap[28605][12680] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Havenshire Stallion][Grand Theft Palomino]
    rMap[28606][12680] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Havenshire Mare][Grand Theft Palomino]
    rMap[28607][12680] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Havenshire Cotl][Grand Theft Palomino]
    rMap[28653][12680] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Salanar the Horseman][Grand Theft Palomino]    

    rMap[28909][12687] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Dark Rider of Acherus][Into the Realm of Shadows]    
    rMap[28782][12687] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Acherus Deathcharger][Into the Realm of Shadows]    
    rMap[29501][12687] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Scourge Gryphon][Into the Realm of Shadows]    
    
    rMap[28577][12678] |= (uint8)TravelDestinationPurpose::QuestObjective2; //[Citizen of Havenshire][If Chaos Drives, Let Suffering Hold The Reins]
    rMap[28576][12678] |= (uint8)TravelDestinationPurpose::QuestObjective2; //[Citizen of Havenshire][If Chaos Drives, Let Suffering Hold The Reins]

    rMap[28658][12698] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Gothic the Harvester][The Gift That Keeps On Giving]    
    rMap[28819][12698] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Scarlet Miner][The Gift That Keeps On Giving]    

    rMap[-190767][12701] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Inconspicuous mine car][Massacre At Light's Point]    
    rMap[28833][12701] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Scarlet Cannon][Massacre At Light's Point]    

    rMap[28941][12722] |= (uint8)TravelDestinationPurpose::QuestObjective2; //[Citizen of New Avalon][Lambs To The Slaughter]
    rMap[28942][12722] |= (uint8)TravelDestinationPurpose::QuestObjective2; //[Citizen of Havenshire][Lambs To The Slaughter]

    rMap[28912][12727] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Koltira Deathweaver][Bloody Breakout]

    rMap[28936][12754] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Scarlet Commander][Ambush At The Overlook]
    rMap[29076][12754] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Scarlet Courier][Ambush At The Overlook]    


    rMap[29102][12779] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[HearthglenCrusader][An End To All Things]    
    rMap[29103][12779] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Tirisfal Crusader][An End To All Things]    
    rMap[29104][12779] |= (uint8)TravelDestinationPurpose::QuestObjective2; //[Scarlet Ballista][An End To All Things]    

    rMap[29173][12801] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Highlord Darion Mograine][The Light of Dawn]    
    rMap[29175][12801] |= (uint8)TravelDestinationPurpose::QuestObjective1; //[Highlord Tirion Fordring][The Light of Dawn]    
    
#endif
    return rMap;
}


//Get all the objective entries for a specific quest. | 收集各任务所需的全部目标 Entry 索引
// 拆解全局 Entry 任务关系表，建立按生物/物件 Entry 和物品 ID 索引的快速查询表
void FindQuestObjectData::GetObjectiveEntries()
{
    relationMap = GAI_VALUE(EntryQuestRelationMap, "entry quest relation");
}

//Data worker. Checks for a specific creature what quest they are needed for and puts them in the proper place in the quest map. | 生物遍历回调：匹配生物与任务的关联并写入映射
// 生物网格遍历回调：将有任务关联的生物出生点坐标存入 questGuidpMap
bool FindQuestObjectData::operator()(CreatureDataPair const& dataPair)
{
    uint32 entry = dataPair.second.id;

    for (auto& [questId, flag] : relationMap[entry])
    {
        data[questId][flag][entry].push_back(GuidPosition(&dataPair));
    }

    return false;
}

//GameObject data worker. Checks for a specific gameObject what quest they are needed for and puts them in the proper place in the quest map. | 游戏对象遍历回调：匹配游戏对象与任务的关联并写入映射
// 游戏对象网格遍历回调：将有任务关联的游戏对象出生点坐标存入 questGuidpMap
bool FindQuestObjectData::operator()(GameObjectDataPair const& dataPair)
{
    int32 entry = dataPair.second.id * -1;

    for (auto& [questId,flag] : relationMap[entry])
    {
        data[questId][flag][entry].push_back(GuidPosition(&dataPair));
    }

    return false;
}

//Goes past all creatures and gameobjects and creatures the full quest guid map. | 遍历所有生物和游戏对象，生成全局任务坐标映射
// 扫描所有已配置的生物和游戏对象生成点，构建全局任务对象位置缓存
questGuidpMap QuestGuidpMapValue::Calculate()
{
    FindQuestObjectData worker;
    sObjectMgr.DoCreatureData(worker);
    sObjectMgr.DoGOData(worker);
    return worker.GetResult();
}

//Selects all questgivers for a specific level (range). | 筛选指定等级范围内的任务发布者
// 根据限定符指定的等级或等级区间筛选所有有效任务发布者位置
questGiverMap QuestGiversValue::Calculate()
{
    uint32 level = 0;
    std::string q = getQualifier();
    bool hasQualifier = !q.empty();

    if (hasQualifier)
        level = stoi(q);

    questGuidpMap questMap = GAI_VALUE(questGuidpMap, "quest guidp map");

    questGiverMap guidps;

    for (auto& [questId, questRelationGuidps]: questMap)
    {
        for (auto& entry : questRelationGuidps[(uint8)TravelDestinationPurpose::QuestGiver])
        {
            for (auto& guidp : entry.second)
            {
                if (hasQualifier)
                {
                    Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

                    if (quest && (level < quest->GetMinLevel() || (int32)level > quest->GetQuestLevel() + 10))
                        continue;
                }

                guidps[questId].push_back(guidp);
            }
        }
    }

    return guidps;
}

// 筛选机器人当前满足前置条件且有空位接取的活跃任务发布者坐标
std::list<GuidPosition> ActiveQuestGiversValue::Calculate()
{
    questGiverMap qGivers = GAI_VALUE2(questGiverMap, "quest givers", bot->GetLevel());

    std::list<GuidPosition> retQuestGivers;

    for (auto& [questId, guidPs] :qGivers)
    {
        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

        if (!quest || !quest->IsActive())
        {
            continue;
        }

        if (!bot->CanTakeQuest(quest, false))
            continue;

        QuestStatus status = bot->GetQuestStatus(questId);

        if (status != QUEST_STATUS_NONE)
            continue;

        for (auto& guidp : guidPs)
        {
            CreatureInfo const* creatureInfo = guidp.GetCreatureTemplate();

            if (creatureInfo)
            {
                if (!ai->IsFriendlyTo(creatureInfo->Faction))
                    continue;
            }

            if (guidp.isDead(bot->GetInstanceId()))
                continue;

            retQuestGivers.push_back(guidp);
        }
    }

    return retQuestGivers;
}

// 筛选机器人已达成目标并可前往交付任务的所有任务接收者坐标
std::list<GuidPosition> ActiveQuestTakersValue::Calculate()
{
    questGuidpMap questMap = GAI_VALUE(questGuidpMap, "quest guidp map");

    std::list<GuidPosition> retQuestTakers;

    QuestStatusMap& questStatusMap = bot->getQuestStatusMap();

    for (auto& [questId, questStatusData]: questStatusMap)
    {
        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

        if (!quest || !quest->IsActive())
        {
            continue;
        }

        QuestStatus status = questStatusData.m_status;

        if ((status != QUEST_STATUS_COMPLETE || bot->GetQuestRewardStatus(questId)) && (!quest->IsAutoComplete() || !bot->CanTakeQuest(quest, false)))
            continue;

        auto q = questMap.find(questId);

        if (q == questMap.end())
            continue;

        auto qt = q->second.find((uint8)TravelDestinationPurpose::QuestTaker);

        if (qt == q->second.end())
            continue;        

        for (auto& [entry, guidps] : qt->second)
        {
            if (entry > 0)
            {
                CreatureInfo const* info = sObjectMgr.GetCreatureTemplate(entry);

                if (info)
                {
                    if (!ai->IsFriendlyTo(info->Faction))
                        continue;
                }
            }

            for (auto& guidp : guidps)
            {
                if (guidp.isDead(bot->GetInstanceId()))
                    continue;

                retQuestTakers.push_back(guidp);
            }
        }
    }

    return retQuestTakers;
}

// 筛选机器人当前未完成任务各项未达成目标对应的世界对象坐标
std::list<GuidPosition> ActiveQuestObjectivesValue::Calculate()
{
    questGuidpMap questMap = GAI_VALUE(questGuidpMap, "quest guidp map");

    std::list<GuidPosition> retQuestObjectives;

    QuestStatusMap& questStatusMap = bot->getQuestStatusMap();

    for (auto& [questId, questStatusData] : questStatusMap)
    {        
        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

        if (!quest || !quest->IsActive())
        {
            continue;
        }

        if (questStatusData.m_status != QUEST_STATUS_INCOMPLETE)
            continue;

        for (uint32 objective = 0; objective < QUEST_OBJECTIVES_COUNT; objective++)
        {
            if (quest->ReqItemCount[objective])
            {
                uint32  reqCount = quest->ReqItemCount[objective];
                uint32  hasCount = questStatusData.m_itemcount[objective];

                if (!reqCount || hasCount >= reqCount)
                    continue;
            }

            if (quest->ReqCreatureOrGOCount[objective])
            {
                uint32 reqCount = quest->ReqCreatureOrGOCount[objective];
                uint32 hasCount = questStatusData.m_creatureOrGOcount[objective];

                if (!reqCount || hasCount >= reqCount)
                    continue;
            }

            auto q = questMap.find(questId);

            if (q == questMap.end())
                continue;

            auto qt = q->second.find((uint8)TravelDestinationPurpose(1<<(objective+1)));

            if (qt == q->second.end())
                continue;

            for (auto& entry : qt->second)
            {
                for (auto& guidp : entry.second)
                {
                    if (guidp.isDead(bot->GetInstanceId()))
                        continue;

                    retQuestObjectives.push_back(guidp);
                }
            }
        }
    }

    return retQuestObjectives;
}

// 判断指定生物或游戏对象是否用于完成某任务的具体目标槽位
bool NeedQuestObjectiveValue::IsNeeded(PlayerbotAI* ai, uint32 questId, uint32 objective, int32 entry)
{
    if (objective >= QUEST_OBJECTIVES_COUNT)
        return false;

    Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

    if (!quest || !quest->IsActive() || !ai->GetBot()->IsActiveQuest(questId))
        return false;

    QuestStatusData& questStatus = ai->GetBot()->getQuestStatusMap().at(questId);

    if (questStatus.m_status != QUEST_STATUS_INCOMPLETE)
        return false;

    int32 reqEntry = quest->ReqCreatureOrGOId[objective];
    uint32 reqCount = quest->ReqCreatureOrGOCount[objective];

    if (reqEntry != 0 && entry == reqEntry && reqCount != 0 && questStatus.m_creatureOrGOcount[objective] < reqCount)
        return true;

    uint32 itemReq = quest->ReqItemCount[objective];
    uint32 itemHas = questStatus.m_itemcount[objective];

    if (itemReq && itemHas < itemReq)
    {
        std::list<int32> drops = GAI_VALUE2(std::list<int32>, "item drop list", quest->ReqItemId[objective]);
        if (std::find(drops.begin(), drops.end(), entry) != drops.end())
            return true;
    }

    return false;
}

// 判断指定物品是否为某任务针对特定目标 Entry 的交互道具
bool CanUseItemOn::IsQuestItemForEntry(PlayerbotAI* ai, uint32 itemId, int32 entry)
{
    QuestStatusMap& questStatusMap = ai->GetBot()->getQuestStatusMap();

    for (auto& [questId, questStatusData] : questStatusMap)
    {
        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

        if (!quest || !quest->IsActive() || questStatusData.m_status != QUEST_STATUS_INCOMPLETE)
            continue;

        if (quest->GetSrcItemId() != itemId)
            continue;

        for (uint32 objective = 0; objective < QUEST_OBJECTIVES_COUNT; objective++)
            if (NeedQuestObjectiveValue::IsNeeded(ai, questId, objective, entry))
                return true;
    }

    return false;
}

// 检查机器人背包里是否有可对目标 Entry 使用的任务物品
bool CanUseItemOn::HasQuestItemForEntry(PlayerbotAI* ai, int32 entry)
{
    std::list<Item*> questItems = ai->GetAiObjectContext()->GetValue<std::list<Item*>>("inventory items", "quest")->Get();

    for (Item* item : questItems)
    {
        if (!item)
            continue;

        if (IsQuestItemForEntry(ai, item->GetProto()->ItemId, entry))
            return true;
    }

    return false;
}

// 检查机器人当前任务日志中是否存在尚未完成的任务
bool NeedQuestObjectiveValue::HasIncompleteObjective(PlayerbotAI* ai)
{
    QuestStatusMap& questStatusMap = ai->GetBot()->getQuestStatusMap();

    for (auto& [questId, questStatusData] : questStatusMap)
    {
        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

        if (!quest || !quest->IsActive() || questStatusData.m_status != QUEST_STATUS_INCOMPLETE)
            continue;

        for (uint32 objective = 0; objective < QUEST_OBJECTIVES_COUNT; objective++)
        {
            if (quest->ReqCreatureOrGOId[objective] != 0 && quest->ReqCreatureOrGOCount[objective] != 0 &&
                questStatusData.m_creatureOrGOcount[objective] < quest->ReqCreatureOrGOCount[objective])
                return true;

            if (quest->ReqItemCount[objective] != 0 &&
                questStatusData.m_itemcount[objective] < quest->ReqItemCount[objective])
                return true;
        }
    }

    return false;
}

// 遍历当前所有已接任务，检查指定 Entry 是否为仍需击杀或交互的目标
bool NeedForQuestValue::Calculate()
{
    if (!Qualified::isValidNumberString(getQualifier()))
        return false;

    int32 entry = stoi(getQualifier());

    QuestStatusMap& questStatusMap = bot->getQuestStatusMap();

    for (auto& [questId, questStatusData] : questStatusMap)
    {
        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);

        if (!quest || !quest->IsActive() || questStatusData.m_status != QUEST_STATUS_INCOMPLETE)
            continue;

        for (uint32 objective = 0; objective < QUEST_OBJECTIVES_COUNT; objective++)
        {
            if (!NeedQuestObjectiveValue::IsNeeded(ai, questId, objective, entry))
                continue;

            return true;
        }
    }

    return false;
}

// 计算任务日志最大槽位数减去当前已接任务数的剩余空位
uint8 FreeQuestLogSlotValue::Calculate()
{
    uint8 numQuest = 0;
    for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        uint32 questId = bot->GetQuestSlotQuestId(slot);

        if (!questId)
            continue;

        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
        if (!quest)
            continue;

        numQuest++;
    }

    return MAX_QUEST_LOG_SIZE - numQuest;
}

// 计算 NPC 或游戏对象对机器人展示的任务感叹号/问号状态
uint32 DialogStatusValue::getDialogStatus(Player* bot, int32 questgiver, uint32 questId)
{
    uint32 dialogStatus = DIALOG_STATUS_NONE;

    QuestRelationsMapBounds rbounds;                        // QuestRelations (quest-giver)
    QuestRelationsMapBounds irbounds;                       // InvolvedRelations (quest-finisher)

    if (questgiver > 0)
    {
        rbounds = sObjectMgr.GetCreatureQuestRelationsMapBounds(questgiver);
        irbounds = sObjectMgr.GetCreatureQuestInvolvedRelationsMapBounds(questgiver);
    }
    else
    {
        rbounds = sObjectMgr.GetGOQuestRelationsMapBounds(questgiver * -1);
        irbounds = sObjectMgr.GetGOQuestInvolvedRelationsMapBounds(questgiver * -1);
    }

    // Check markings for quest-finisher
    for (QuestRelationsMap::const_iterator itr = irbounds.first; itr != irbounds.second; ++itr)
    {
        if (questId && itr->second != questId)
            continue;

        Quest const* pQuest = sObjectMgr.GetQuestTemplate(itr->second);

        uint32 dialogStatusNew = DIALOG_STATUS_NONE;

        if (!pQuest || !pQuest->IsActive())
        {
            continue;
        }

        QuestStatus status = bot->GetQuestStatus(itr->second);

        if ((status == QUEST_STATUS_COMPLETE && !bot->GetQuestRewardStatus(itr->second)) ||
            (pQuest->IsAutoComplete() && bot->CanTakeQuest(pQuest, false)))
        {
            if (pQuest->IsAutoComplete() && pQuest->IsRepeatable())
            {
                dialogStatusNew = DIALOG_STATUS_REWARD_REP;
            }
            else
            {
                dialogStatusNew = DIALOG_STATUS_REWARD2;
            }
        }
        else if (status == QUEST_STATUS_INCOMPLETE)
        {
            dialogStatusNew = DIALOG_STATUS_INCOMPLETE;
        }

        if (dialogStatusNew > dialogStatus)
        {
            dialogStatus = dialogStatusNew;
        }
    }

    // check markings for quest-giver
    for (QuestRelationsMap::const_iterator itr = rbounds.first; itr != rbounds.second; ++itr)
    {
        if (questId && itr->second != questId)
            continue;

        Quest const* pQuest = sObjectMgr.GetQuestTemplate(itr->second);

        uint32 dialogStatusNew = DIALOG_STATUS_NONE;

        if (!pQuest || !pQuest->IsActive())
        {
            continue;
        }

        QuestStatus status = bot->GetQuestStatus(itr->second);

        if (status == QUEST_STATUS_NONE)                    // For all other cases the mark is handled either at some place else, or with involved-relations already
        {
            if (bot->CanSeeStartQuest(pQuest))
            {
                if (bot->SatisfyQuestLevel(pQuest, false))
                {
                    int32 lowLevelDiff = sWorld.getConfig(CONFIG_INT32_QUEST_LOW_LEVEL_HIDE_DIFF);
                    if (pQuest->IsAutoComplete() || (pQuest->IsRepeatable() && bot->getQuestStatusMap()[itr->second].m_rewarded))
                    {
                        dialogStatusNew = DIALOG_STATUS_REWARD_REP;
                    }
                    else if (lowLevelDiff < 0 || bot->GetLevel() <= bot->GetQuestLevelForPlayer(pQuest) + uint32(lowLevelDiff) || pQuest->GetRequiredClasses())
                    {
                        dialogStatusNew = DIALOG_STATUS_AVAILABLE;
                    }
                    else
                    {
#ifndef MANGOSBOT_TWO
                        dialogStatusNew = DIALOG_STATUS_CHAT;
#else
                        dialogStatusNew = DIALOG_STATUS_LOW_LEVEL_AVAILABLE;
#endif
                    }
                }
                else
                {
                    dialogStatusNew = DIALOG_STATUS_UNAVAILABLE;
                }
            }
        }

        if (dialogStatusNew > dialogStatus)
        {
            dialogStatus = dialogStatusNew;
        }
    }

    return dialogStatus;
}

// 检查指定对象是否提供无需前置步骤可直接自动完成的任务
bool CanAcceptQuestValue::CanAcceptAutoCompleteQuest(Player* bot, int32 questgiver)
{
    QuestRelationsMapBounds rbounds;

    if (questgiver > 0)
        rbounds = sObjectMgr.GetCreatureQuestRelationsMapBounds(questgiver);
    else
        rbounds = sObjectMgr.GetGOQuestRelationsMapBounds(questgiver * -1);

    for (QuestRelationsMap::const_iterator itr = rbounds.first; itr != rbounds.second; ++itr)
    {
        Quest const* pQuest = sObjectMgr.GetQuestTemplate(itr->second);

        if (!pQuest || !pQuest->IsActive() || !pQuest->IsAutoComplete())
            continue;

        if (bot->GetQuestStatus(itr->second) != QUEST_STATUS_NONE)
            continue;

        if (bot->CanRewardQuest(pQuest, false))
            continue;

        if (pQuest->IsRepeatable() && bot->getQuestStatusMap()[itr->second].m_rewarded)
            continue;

        if (bot->CanSeeStartQuest(pQuest) && bot->SatisfyQuestLevel(pQuest, false))
            return true;
    }

    return false;
}


// 检查任务奖励列表是否包含职业限定奖励或可装备升级的装备
bool NeedQuestRewardValue::Calculate()
{
    uint32 questId = stoi(getQualifier());
    Quest const* pQuest = sObjectMgr.GetQuestTemplate(questId);

    if (pQuest->GetRequiredClasses()) //Always try to do class quests. | 职业专属任务总是视为需要获取奖励
        return true;

    for (uint8 i = 0; i < pQuest->GetRewChoiceItemsCount(); ++i)
    {
        ItemUsage usage = AI_VALUE2_LAZY(ItemUsage, "item usage", pQuest->RewChoiceItemId[i]);
        if (usage == ItemUsage::ITEM_USAGE_EQUIP || usage == ItemUsage::ITEM_USAGE_BAD_EQUIP)
            return true;
    }

    return false;
}

// 检查任务所需物品是否可通过怪物掉落或用现有金钱从商人处购得
bool NeedQuestObjectiveValue::CanGetItemSomewhere(const uint32 itemId, const uint32 reqCount, Player* bot)
{
    if (!GAI_VALUE2(std::list<int32>, "item drop list", itemId).empty()) //Can get it from drop. | 可通过击杀掉落获取
        return true;

    if (GAI_VALUE2(std::list<int32>, "item vendor list", itemId).empty()) //Can not get it from vendor. | 商人处无售该物品
        return true;

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);

    if (!proto)
        return true;

    if (bot->GetMoney() > proto->BuyPrice * reqCount) //Bot has money to buy item from vendor. | 机器人持有足够金钱从商人购买
        return true;

    return false;
}

// 综合检查整条任务或特定任务目标（奖励/交任务/生物击杀/物品收集）是否尚未达成
bool NeedQuestObjectiveValue::Calculate()
{
    uint32 questId = getMultiQualifierInt(getQualifier(),0,",");
    if (!bot->IsActiveQuest(questId))
        return false;

    QuestStatusData& questStatus = bot->getQuestStatusMap().at(questId);

    if (getQualifier().find("reward") != std::string::npos)
    {
        return !questStatus.m_rewarded; //Still need the reward | 尚未领取该任务奖励
    }

    if (questStatus.m_status != QUEST_STATUS_INCOMPLETE)
        return false;

    if (getQualifier().find(",") == std::string::npos) //Status of entire quest. | 检查整个任务的总体完成状态
        return true;

#ifdef MANGOSBOT_TWO        
        switch (questId) {
        case 12687: //Into the Realm of Shadows
            return true; //No objectives for this quest. | 该任务无额外前置目标（直接就绪）
        }
#endif

    Quest const* pQuest = sObjectMgr.GetQuestTemplate(questId);

    uint32 objective = getMultiQualifierInt(getQualifier(), 1, ",");

    uint32  reqCount = pQuest->ReqItemCount[objective];
    uint32  hasCount = questStatus.m_itemcount[objective];

    bool needItems = false;
    bool needCreatures = false;

    if (reqCount && hasCount < reqCount)
    {
        uint32 itemId = pQuest->ReqItemId[objective];

        if (CanGetItemSomewhere(itemId, reqCount, bot))
            needItems = true;
    }

    reqCount = pQuest->ReqCreatureOrGOCount[objective];
    hasCount = questStatus.m_creatureOrGOcount[objective];

    if (reqCount && hasCount < reqCount)
        needCreatures = true;

    return needItems || needCreatures;
}

// 判断指定物品与目标对象的组合是否满足特殊任务硬编码条件、法术或任务道具交互条件
bool CanUseItemOn::Calculate()
{
    uint32 itemId = getMultiQualifierInt(getQualifier(), 0, ",");
    std::string guidPString = getMultiQualifierStr(getQualifier(), 1, ",");
    GuidPosition guidP(guidPString);

    Unit* unit = nullptr;
    GameObject* gameObject = nullptr;

    if (!guidP)
        return false;

    switch (itemId)
    {
        case 17117:                                                                                                                 //Rat Catcher's Flute
            return guidP.IsCreature() && guidP.GetEntry() == 13016;                                                                 //Deeprun Rat
        case 52566:                                                                                                                 //Motivate-a-Tron (currently broken?)
            return guidP.IsCreature() && guidP.GetEntry() == 39623;                                                                 //Gnome Citizen
        case 38607:                                                                                                                 //Battle-worn Sword
            return guidP.IsGameObject() && (std::find(RUNEFORGES.begin(), RUNEFORGES.end(), guidP.GetEntry()) != RUNEFORGES.end()); //Runeforge
        case 39253:                                                                                                                 //Gift of the Harester
            return guidP.IsCreature() && guidP.GetEntry() == 28819;                                                                 //Scarlet Miner
        case 39645:                                                                                                                 //Makeshift Cover
            return guidP.IsCreature() && guidP.GetEntry() == 28936;                                                                 //Scarlet Commander
            // 注释：保留的冰霜巨龙号角任务交互判断代码
            /*        case 39700:                                                                                                                 //Horn of the Frostbrood
        
            switch (AI_VALUE(TravelTarget*, "travel target")->GetEntry())
            case 29102: //HearthglenCrusader
            case 29103: //Tirisfal Crusader
            case 29104: //Scarlet Ballista
        
            return !AI_VALUE2(bool, "trigger active", "in vehicle") && AI_VALUE2(bool, "need quest objective", "12779"); //Mount up!
        */
    }

    if (guidP.IsUnit())
        unit = guidP.GetUnit(bot->GetInstanceId());
    else if (guidP.IsGameObject())
        gameObject = guidP.GetGameObject(bot->GetInstanceId());

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);

    if (!proto)
        return false;

    bool tryRandomCast = !urand(0, 20);

    uint32 spellId = proto->Spells[0].SpellId;
    if (spellId)
    {
        SpellEntry const* spellInfo = sServerFacade.LookupSpellInfo(spellId);

        if (unit)
        {
            if (spellInfo->Effect[0] == SPELL_EFFECT_DUMMY && spellInfo->Id == 19938)  // Awaken Lazy Peon (hardcoded in core!) | 唤醒偷懒的苦工（核心硬编码法术 19938）
            {
                // 17743 = Lazy Peon Sleep | 10556 = Lazy Peon | 17743 为沉睡苦工光环，10556 为苦工 NPC Entry
                if (!unit->HasAura(17743) || unit->GetEntry() != 10556)
                    return false;

                return true;
            }

            if (ai->CanCastSpell(spellId, unit, 0, false, nullptr, true))
            {
                if (CanUseItemOn::IsQuestItemForEntry(ai, itemId, (int32)guidP.GetEntry()))
                    return true;

                return tryRandomCast;
            }
        }
        else if (gameObject)
        {
            if (ai->CanCastSpell(spellId, gameObject, 0, false, true))
                return tryRandomCast;
        }
    }

    return false;
};

// 扫描附近可交互 NPC 与游戏对象，判断是否有可接取或可交付的任务
bool HasNearbyQuestTakerValue::Calculate()
{
    std::list<ObjectGuid> possibleTargets = AI_VALUE(std::list<ObjectGuid>, "possible rpg targets");

    int32 travelEntry = AI_VALUE(TravelTarget*, "travel target")->GetEntry();
    
    for (auto& target : possibleTargets)
    {
        if (target.GetEntry() == travelEntry)
            continue;

        if(AI_VALUE2(bool, "can turn in quest npc", target.GetEntry()))
            return true;
    }

    std::list<ObjectGuid> possibleObjects = bot->GetMap()->IsDungeon() ? AI_VALUE(std::list<ObjectGuid>, "nearest game objects") : AI_VALUE(std::list<ObjectGuid>, "nearest game objects no los");

    for (auto& target : possibleObjects)
    {
        if (target.GetEntry() == (travelEntry * -1))
            continue;

        if (AI_VALUE2(bool, "can turn in quest npc", target.GetEntry()))
            return true;
    }

    return false;
};