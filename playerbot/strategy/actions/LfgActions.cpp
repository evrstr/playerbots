
#include "playerbot/playerbot.h"
#include "LfgActions.h"
#include "playerbot/strategy/ItemVisitors.h"
#include "playerbot/TravelMgr.h"

using namespace ai;

/// 执行动作主逻辑（加入地下城查找器排队动作）
bool LfgJoinAction::Execute(Event& event)
{
    return JoinLFG();
}

#ifdef MANGOSBOT_TWO
/// 获取机器人当前的地下城查找器职责标识
LfgRoles LfgJoinAction::GetRoles()
{
    if (!sRandomPlayerbotMgr.IsRandomBot(bot))
    {
        if (ai->IsTank(bot))
            return PLAYER_ROLE_TANK;
        if (ai->IsHeal(bot))
            return PLAYER_ROLE_HEALER;
        else
            return PLAYER_ROLE_DAMAGE;
    }

    int spec = AiFactory::GetPlayerSpecTab(bot);
    switch (bot->getClass())
    {
    case CLASS_DRUID:
        if (spec == 2)
            return PLAYER_ROLE_HEALER;
        else if (spec == 1 && bot->GetLevel() >= 20)
            return LfgRoles(PLAYER_ROLE_TANK | PLAYER_ROLE_DAMAGE);
        else
            return PLAYER_ROLE_DAMAGE;
        break;
    case CLASS_PALADIN:
        if (spec == 1)
            return PLAYER_ROLE_TANK;
        else if (spec == 0)
            return PLAYER_ROLE_HEALER;
        else
            return PLAYER_ROLE_DAMAGE;
        break;
    case CLASS_PRIEST:
        if (spec != 2)
            return PLAYER_ROLE_HEALER;
        else
            return PLAYER_ROLE_DAMAGE;
        break;
    case CLASS_SHAMAN:
        if (spec == 2)
            return PLAYER_ROLE_HEALER;
        else
            return PLAYER_ROLE_DAMAGE;
        break;
    case CLASS_WARRIOR:
        if (spec == 2)
            return PLAYER_ROLE_TANK;
        else
            return PLAYER_ROLE_DAMAGE;
        break;
#ifdef MANGOSBOT_TWO
    case CLASS_DEATH_KNIGHT:
        if (spec == 0)
            return PLAYER_ROLE_TANK;
        else
            return PLAYER_ROLE_DAMAGE;
        break;
#endif
    default:
        return PLAYER_ROLE_DAMAGE;
        break;
    }

    return PLAYER_ROLE_DAMAGE;
}
#endif

/// 根据职业与天赋设置机器人在 LFG 中的职责标识
bool LfgJoinAction::SetRoles()
{
#ifdef MANGOSBOT_TWO_UNUSED
    LFGData pState = bot->GetLfgData();
    pState.SetPlayerRoles(GetRoles());
#endif
    return true;
}

/// 向地下城查找器提交排队请求
bool LfgJoinAction::JoinLFG()
{
#ifdef MANGOSBOT_ZERO
    //ItemCountByQuality visitor;
    //IterateItems(&visitor, ITERATE_ITEMS_IN_EQUIP);
    //bool raid = (urand(0, 100) < 50 && visitor.count[ITEM_QUALITY_EPIC] >= 5 && (bot->GetLevel() == 60 || bot->GetLevel() == 70 || bot->GetLevel() == 80));

    MeetingStoneSet stones = sWorld.GetLFGQueue().GetDungeonsForPlayer(bot);
    if (!stones.size())
        return false;

    std::vector<uint32> dungeons = sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()];
    if (!dungeons.size())
        return false;

    std::vector<MeetingStoneInfo> selected;
    for (std::vector<uint32>::iterator i = dungeons.begin(); i != dungeons.end(); ++i)
    {
        uint32 zoneId = 0;
        uint32 dungeonId = (*i & 0xFFFF);
        zoneId = ((*i >> 16) & 0xFFFF);

        // join only if close to closest graveyard (仅当靠近最近墓地时加入)
        if (zoneId)
        {
            WorldSafeLocsEntry const* ClosestGrave = nullptr;
            ClosestGrave = sWorldSafeLocsStore.LookupEntry<WorldSafeLocsEntry>(zoneId);

            bool inCity = false;
            AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(bot->GetAreaId());
            if (areaEntry)
            {
                if (areaEntry->zone)
                    areaEntry = GetAreaEntryByAreaID(areaEntry->zone);

                if (areaEntry && areaEntry->flags & AREA_FLAG_CAPITAL)
                    inCity = true;
            }

            if (ClosestGrave)
            {
                if (!(inCity || bot->GetMapId() == ClosestGrave->map_id))
                    continue;
            }
            else
                continue;
        }

        for (MeetingStoneSet::iterator i = stones.begin(); i != stones.end(); ++i)
        {
            if (i->area == dungeonId)
                selected.push_back(*i);
        }
    }

    if (!selected.size())
        return false;

    uint32 dungeon = urand(0, selected.size() - 1);
    MeetingStoneInfo stoneInfo = selected[dungeon];
    BotRoles botRoles = AiFactory::GetPlayerRoles(bot);
    std::string _botRoles;
    switch (botRoles)
    {
    case BOT_ROLE_TANK:
        _botRoles = "Tank";
        break;
    case BOT_ROLE_HEALER:
        _botRoles = "Healer";
        break;
    case BOT_ROLE_DPS:
    default:
        _botRoles = "Dps";
        break;
    }

    if (botRoles & BOT_ROLE_TANK && botRoles & BOT_ROLE_DPS)
        _botRoles = "Tank/Dps";
    /*for (MeetingStoneSet::const_iterator itr = stones.begin(); itr != stones.end(); ++itr)
    {
        auto data = *itr;

        idx.push_back(data.area);
    }

    if (idx.empty())
        return false;*/

    sLog.outDetail("Bot #%d %s:%d <%s>: uses LFG, Dungeon - %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), stoneInfo.name, _botRoles.c_str());

    sLFGMgr.AddToQueue(bot, stoneInfo.area);
#endif
#ifdef MANGOSBOT_ONE
    uint32 zoneLFG = 0;
    uint32 questLFG = 0;
    uint32 questZoneLFG = 0;
    std::string questName;
    std::string zoneName;
    std::string lfgName;
    uint32 needMembers = 0;
    LfgType lfgType = LFG_TYPE_NONE;
    TravelState state = TravelState::TRAVEL_STATE_IDLE;
    TravelStatus status = TravelStatus::TRAVEL_STATUS_NONE;

    GrouperType grouperType = ai->GetGrouperType();

    if (grouperType == GrouperType::SOLO)
        return false;

    bool isLFG = false; // member (成员)
    bool isLFM = false; // leader (队长)

    if (grouperType == GrouperType::MEMBER)
        isLFG = true;

    if (grouperType >= GrouperType::LEADER_2)
        isLFM = true;

    Group* group = bot->GetGroup();

    // don't use lfg if already has group (已有队伍时不使用自动寻队)
    if (isLFG && group)
        return false;

    needMembers = uint8(grouperType) - 1;

    // don't use lfg if not leader or group has enough members (非队长或队伍人数已足够时不使用寻队)
    if (isLFM && group)
    {
        if (group->IsFull())
            return false;

        if (ai->GetGroupMaster() != bot)
            return false;

        uint32 memberCount = group->GetMembersCount();

        if (memberCount >= uint8(grouperType))
            return false;

        needMembers = uint8(grouperType) - memberCount;
    }

    bool groupQ = false;
    TravelTarget* target = bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<TravelTarget*>("travel target")->Get();
    if (target)
    {
        state = target->GetTravelState();
        status = target->GetStatus();
        // queue only if quest not completed (仅在任务尚未完成时加入队列)
        if (state < TravelState::TRAVEL_STATE_TRAVEL_HAND_IN_QUEST)
        {
            if (typeid(*target) == typeid(QuestTravelDestination))
            {
                Quest const* qinfo = sObjectMgr.GetQuestTemplate(((QuestTravelDestination*)target->GetDestination())->GetQuestId());
                if (qinfo)
                {
                    // only group quests are allowed for quest lfg (任务寻队仅限组队/精英任务)
                    if (qinfo->GetType() == QUEST_TYPE_ELITE)
                        groupQ = true;

                    questLFG = qinfo->GetQuestId();
                    questZoneLFG = qinfo->GetZoneOrSort();
                    questName = qinfo->GetTitle();
                }
            }
        }
    }

    /*AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(bot->GetZoneId());
    // check if area has no parent zone
    if (areaEntry && !areaEntry->zone)
    {
        zoneLFG = areaEntry->ID;
        zoneName = areaEntry->area_name[0];
    }*/

    // only use lfg zone if current quest leads there (仅当当前任务指向该区域时使用区域 LFG)
    if (questZoneLFG)
    {
        AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(questZoneLFG);
        // check if area has no parent zone (检查区域是否没有父级区域)
        if (areaEntry && !areaEntry->zone)
        {
            zoneLFG = areaEntry->ID;
            zoneName = areaEntry->area_name[0];
        }
    }
    else if (!bot->IsTaxiFlying())
    {
        AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(bot->GetZoneId());
        // check if area has no parent zone (检查区域是否没有父级区域)
        if (areaEntry && !areaEntry->zone)
        {
            zoneLFG = areaEntry->ID;
            zoneName = areaEntry->area_name[0];
        }
    }

    bool joinedLFG = false;
    bool realLFG = false;
    // if bot wants to lead
    if (isLFM)
    {
        // lfm for current elite quest (LFM 招人：针对当前精英任务)
        if (questLFG && groupQ)
        {
            lfgType = LFG_TYPE_QUEST;
            lfgName = questName;
            WorldPacket p;
            uint32 temp = questLFG | (lfgType << 24);
            p << temp;
            bot->GetSession()->HandleSetLfmOpcode(p);
            bot->GetSession()->HandleLfmClearAutoFillOpcode(p);
            joinedLFG = true;
        }
        // lfm for current quest zone or just current zone (LFM 招人：针对当前任务区域或所在区域)
        else if (zoneLFG && (questZoneLFG || (status >= TravelStatus::TRAVEL_STATUS_COOLDOWN || state >= TravelState::TRAVEL_STATE_TRAVEL_HAND_IN_QUEST || (state == TravelState::TRAVEL_STATE_IDLE && !urand(0, 4)))))
        {
            for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
            {
                if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i))
                {
                    if (dungeon->maxlevel < bot->GetLevel())
                        continue;
                    if (dungeon->minlevel > bot->GetLevel())
                        continue;
                    // skip enemy faction (跳过敌对阵营)
                    if (dungeon->faction == 0 && bot->GetTeam() == ALLIANCE)
                        continue;
                    if (dungeon->faction == 1 && bot->GetTeam() == HORDE)
                        continue;

                    // check by zone name... (按区域名称检查...)
                    if (dungeon->name[0] == zoneName)
                    {
                        lfgType = LFG_TYPE_ZONE;
                        lfgName = zoneName;
                        WorldPacket p;
                        uint32 temp = dungeon->ID | (lfgType << 24);
                        p << temp;
                        bot->GetSession()->HandleSetLfmOpcode(p);
                        bot->GetSession()->HandleLfmClearAutoFillOpcode(p);
                        joinedLFG = true;
                        break;
                    }
                }
            }
        }
        // lfm for random dungeon if nothing else to do (LFM 招人：无其他事务时招人打随机副本)
        else if (status >= TravelStatus::TRAVEL_STATUS_COOLDOWN || state >= TravelState::TRAVEL_STATE_TRAVEL_HAND_IN_QUEST || (state == TravelState::TRAVEL_STATE_IDLE && !urand(0, 4)))
        {
            std::vector<uint32> dungeons;
            for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
            {
                if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i))
                {
                    if (dungeon->maxlevel < bot->GetLevel())
                        continue;
                    if (dungeon->minlevel > bot->GetLevel())
                        continue;

                    // only normal dungeons (仅限普通难度地下城)
                    if (dungeon->type != 1)
                        continue;

                    // skip enemy faction (跳过敌对阵营)
                    if (dungeon->faction == 0 && bot->GetTeam() == ALLIANCE)
                        continue;
                    if (dungeon->faction == 1 && bot->GetTeam() == HORDE)
                        continue;

                    dungeons.push_back(dungeon->ID);
                }
            }
            if (!dungeons.empty())
            {
                uint32 dungeonId = dungeons[urand(0, dungeons.size() - 1)];
                if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(dungeonId))
                {
                    lfgType = LFG_TYPE_DUNGEON;
                    lfgName = dungeon->name[0];
                    WorldPacket p;
                    uint32 temp = dungeon->ID | (lfgType << 24);
                    p << temp;
                    bot->GetSession()->HandleSetLfmOpcode(p);
                    bot->GetSession()->HandleLfmClearAutoFillOpcode(p);
                    joinedLFG = true;
                }
            }
        }
        // try to LFM for current dungeon (尝试为当前地下城招人（LFM）)
        if (target && group && !group->IsFull())
        {
            // if moving to boss
            if (target->GetDestination() && typeid(*target->GetDestination()) == typeid(BossTravelDestination))
            {
                WorldPosition* location = target->GetPosition();
                uint32 targetAreaFlag = GetAreaFlagByMapId(location->mapid);
                if (targetAreaFlag)
                {
                    AreaTableEntry const* areaEntry = GetAreaEntryByAreaFlagAndMap(targetAreaFlag, location->mapid);
                    if (areaEntry)
                    {
                        if (areaEntry->zone)
                            areaEntry = GetAreaEntryByAreaID(areaEntry->zone);

                        if (areaEntry && !areaEntry->zone)
                        {
                            for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
                            {
                                if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i))
                                {
                                    if (dungeon->maxlevel < bot->GetLevel())
                                        continue;
                                    if (dungeon->minlevel > bot->GetLevel())
                                        continue;

                                    // only normal dungeons (仅限普通难度地下城)
                                    if (dungeon->type != 1)
                                        continue;

                                    // skip enemy faction (跳过敌对阵营)
                                    if (dungeon->faction == 0 && bot->GetTeam() == ALLIANCE)
                                        continue;
                                    if (dungeon->faction == 1 && bot->GetTeam() == HORDE)
                                        continue;

                                    // check by zone name, doesn't work for some dungeons (按区域名称检查（部分副本不适用）)
                                    if (dungeon->name[0] == areaEntry->area_name[0])
                                    {
                                        lfgType = LFG_TYPE_DUNGEON;
                                        lfgName = dungeon->name[0];
                                        WorldPacket p;
                                        uint32 temp = dungeon->ID | (lfgType << 24);
                                        p << temp;
                                        bot->GetSession()->HandleSetLfmOpcode(p);
                                        bot->GetSession()->HandleLfmSetAutoFillOpcode(p);

                                        // set auto invite if real player in queue (队列中有真实玩家时开启自动邀请)
                                        std::vector<uint32> player_dungeons = sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()];
                                        if (!player_dungeons.empty())
                                        {
                                            for (std::vector<uint32>::iterator i = player_dungeons.begin(); i != player_dungeons.end(); ++i)
                                            {
                                                uint32 zoneId = 0;
                                                uint32 entry = (*i & 0xFFFF);
                                                uint32 type = ((*i >> 8) & 0xFFFF);
                                                zoneId = ((*i >> 16) & 0xFFFF);

                                                // only lfg (仅使用 LFG 队列)
                                                if (type != 0)
                                                    continue;

                                                // join only if close to closest graveyard (仅当靠近最近墓地时加入)
                                                if (zoneId)
                                                {
                                                    WorldSafeLocsEntry const* ClosestGrave = nullptr;
                                                    ClosestGrave = sWorldSafeLocsStore.LookupEntry<WorldSafeLocsEntry>(zoneId);

                                                    bool inCity = false;
                                                    AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(bot->GetAreaId());
                                                    if (areaEntry)
                                                    {
                                                        if (areaEntry->zone)
                                                            areaEntry = GetAreaEntryByAreaID(areaEntry->zone);

                                                        if (areaEntry && areaEntry->flags & AREA_FLAG_CAPITAL)
                                                            inCity = true;
                                                    }

                                                    if (ClosestGrave)
                                                    {
                                                        if (!(inCity || bot->GetMapId() == ClosestGrave->map_id))
                                                            continue;
                                                    }
                                                    else
                                                        continue;
                                                }

                                                if (LFGDungeonEntry const* player_dungeon = sLFGDungeonStore.LookupEntry(entry))
                                                {
                                                    if (player_dungeon->ID == dungeon->ID)
                                                        bot->GetSession()->HandleLfmSetAutoFillOpcode(p);

                                                    realLFG = true;
                                                }
                                            }
                                        }
                                        joinedLFG = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // set auto invite if real player in queue (队列中有真实玩家时开启自动邀请)
        std::vector<uint32> player_dungeons = sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()];
        if (!player_dungeons.empty() && !group)
        {
            for (std::vector<uint32>::iterator i = player_dungeons.begin(); i != player_dungeons.end(); ++i)
            {
                uint32 zoneId = 0;
                uint32 entry = (*i & 0xFFFF) & 0xFF;
                uint32 type = ((*i & 0xFFFF) >> 8);
                zoneId = (*i >> 16) & 0xFFFF;

                // leader only queue if player is lfg, not lfm (仅当玩家处于求组（LFG）而非招人（LFM）状态时由队长排队)
                if (type != 0)
                    continue;

                // join only if close to closest graveyard (仅当靠近最近墓地时加入)
                if (zoneId)
                {
                    WorldSafeLocsEntry const* ClosestGrave = nullptr;
                    ClosestGrave = sWorldSafeLocsStore.LookupEntry<WorldSafeLocsEntry>(zoneId);

                    bool inCity = false;
                    AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(bot->GetAreaId());
                    if (areaEntry)
                    {
                        if (areaEntry->zone)
                            areaEntry = GetAreaEntryByAreaID(areaEntry->zone);

                        if (areaEntry && areaEntry->flags & AREA_FLAG_CAPITAL)
                            inCity = true;
                    }

                    if (ClosestGrave)
                    {
                        if (!(inCity || bot->GetMapId() == ClosestGrave->map_id))
                            continue;
                    }
                    else
                        continue;
                }

                if (LFGDungeonEntry const* player_dungeon = sLFGDungeonStore.LookupEntry(entry))
                {
                    if (player_dungeon->maxlevel < bot->GetLevel())
                        continue;
                    if (player_dungeon->minlevel > bot->GetLevel())
                        continue;

                    // only normal dungeons (仅限普通难度地下城)
                    if (player_dungeon->type != 1)
                        continue;

                    // skip enemy faction (跳过敌对阵营)
                    if (player_dungeon->faction == 0 && bot->GetTeam() == ALLIANCE)
                        continue;
                    if (player_dungeon->faction == 1 && bot->GetTeam() == HORDE)
                        continue;

                    lfgType = LFG_TYPE_DUNGEON;
                    lfgName = player_dungeon->name[0];
                    WorldPacket p;
                    uint32 temp = player_dungeon->ID | (lfgType << 24);
                    p << temp;
                    bot->GetSession()->HandleSetLfmOpcode(p);
                    bot->GetSession()->HandleLfmSetAutoFillOpcode(p);
                    joinedLFG = true;
                    realLFG = true;
                    break;
                }
            }
        }
    }
    else if (isLFG) // bot is alone and looks for group (机器人当前独处，正在寻找队伍)
    {
        // lfg slot 1 for current elite quest (LFG 槽位 1：用于当前精英任务)
        if (questLFG && groupQ)
        {
            lfgType = LFG_TYPE_QUEST;
            lfgName = questName;
            WorldPacket p;
            p << uint32(0); // lfg slot (LFG 队列槽位)
            uint32 temp = questLFG | (lfgType << 24);
            p << temp;
            bot->GetSession()->HandleSetLfgOpcode(p);
            bot->GetSession()->HandleLfgClearAutoJoinOpcode(p);
            joinedLFG = true;
        }
        // lfg slot 2 for current quest zone or just current zone (LFG 槽位 2：用于当前任务区域或所在区域)
        if (zoneLFG && (questZoneLFG || (status >= TravelStatus::TRAVEL_STATUS_COOLDOWN || state >= TravelState::TRAVEL_STATE_TRAVEL_HAND_IN_QUEST || (state == TravelState::TRAVEL_STATE_IDLE && !urand(0, 4))))) // use second lfg slot for zone lfg (使用第二个 LFG 槽位进行区域寻队)
        {
            for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
            {
                if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i))
                {
                    if (dungeon->maxlevel < bot->GetLevel())
                        continue;
                    if (dungeon->minlevel > bot->GetLevel())
                        continue;

                    // skip enemy faction (跳过敌对阵营)
                    if (dungeon->faction == 0 && bot->GetTeam() == ALLIANCE)
                        continue;
                    if (dungeon->faction == 1 && bot->GetTeam() == HORDE)
                        continue;

                    // check by zone name... (按区域名称检查...)
                    if (dungeon->name[0] == zoneName)
                    {
                        lfgType = LFG_TYPE_ZONE;
                        lfgName = zoneName;
                        WorldPacket p;
                        p << uint32(1); // lfg slot (LFG 队列槽位)
                        uint32 temp = dungeon->ID | (lfgType << 24);
                        p << temp;
                        bot->GetSession()->HandleSetLfgOpcode(p);
                        bot->GetSession()->HandleLfgClearAutoJoinOpcode(p);
                        joinedLFG = true;
                        break;
                    }
                }
            }
        }
        // lfg for dungeon if real player used LFM with auto invite (若真实玩家开启自动邀请招人（LFM），则自动排队匹配该副本)
        std::vector<uint32> player_dungeons = sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()];
        if (!player_dungeons.empty())
        {
            for (std::vector<uint32>::iterator i = player_dungeons.begin(); i != player_dungeons.end(); ++i)
            {
                uint32 zoneId = 0;
                uint32 entry = (*i & 0xFFFF) & 0xFF;
                uint32 type = ((*i & 0xFFFF) >> 8);
                zoneId = (*i >> 16) & 0xFFFF;

                // members queue only if player is lfm, not lfg (仅当玩家处于 LFM 状态时队员才排队)
                if (type != 1)
                    continue;

                // join only if close to closest graveyard (仅当靠近最近墓地时加入)
                if (zoneId)
                {
                    WorldSafeLocsEntry const* ClosestGrave = nullptr;
                    ClosestGrave = sWorldSafeLocsStore.LookupEntry<WorldSafeLocsEntry>(zoneId);

                    bool inCity = false;
                    AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(bot->GetAreaId());
                    if (areaEntry)
                    {
                        if (areaEntry->zone)
                            areaEntry = GetAreaEntryByAreaID(areaEntry->zone);

                        if (areaEntry && areaEntry->flags & AREA_FLAG_CAPITAL)
                            inCity = true;
                    }

                    if (ClosestGrave)
                    {
                        if (!(inCity || bot->GetMapId() == ClosestGrave->map_id))
                            continue;
                    }
                    else
                        continue;
                }

                if (LFGDungeonEntry const* player_dungeon = sLFGDungeonStore.LookupEntry(entry))
                {
                    if (player_dungeon->maxlevel < bot->GetLevel())
                        continue;
                    if (player_dungeon->minlevel > bot->GetLevel())
                        continue;

                    // only normal dungeons (仅限普通难度地下城)
                    //if (player_dungeon->type != 1)
                    //    continue;

                    // skip enemy faction (跳过敌对阵营)
                    if (player_dungeon->faction == 0 && bot->GetTeam() == ALLIANCE)
                        continue;
                    if (player_dungeon->faction == 1 && bot->GetTeam() == HORDE)
                        continue;

                    lfgType = LFG_TYPE_DUNGEON;
                    lfgName = player_dungeon->name[0];
                    WorldPacket p;
                    p << uint32(2); // lfg slot (LFG 队列槽位)
                    uint32 temp = player_dungeon->ID | (lfgType << 24);
                    p << temp;
                    bot->GetSession()->HandleSetLfgOpcode(p);
                    bot->GetSession()->HandleLfgSetAutoJoinOpcode(p);
                    joinedLFG = true;
                    realLFG = true;
                    break;
                }
            }
        }
        // lfg slot 3 for random dungeon if not very busy (LFG 槽位 3：空闲时用于随机地下城)
        else if (status >= TravelStatus::TRAVEL_STATUS_COOLDOWN || state >= TravelState::TRAVEL_STATE_TRAVEL_HAND_IN_QUEST || (state == TravelState::TRAVEL_STATE_IDLE && !urand(0, 4)))
        {
            std::vector<uint32> dungeons;
            for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
            {
                if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i))
                {
                    if (dungeon->maxlevel < bot->GetLevel())
                        continue;
                    if (dungeon->minlevel > bot->GetLevel())
                        continue;

                    // only normal dungeons (仅限普通难度地下城)
                    if (dungeon->type != 1)
                        continue;

                    // skip enemy faction (跳过敌对阵营)
                    if (dungeon->faction == 0 && bot->GetTeam() == ALLIANCE)
                        continue;
                    if (dungeon->faction == 1 && bot->GetTeam() == HORDE)
                        continue;

                    dungeons.push_back(dungeon->ID);
                }
            }
            if (!dungeons.empty())
            {
                uint32 dungeonId = dungeons[urand(0, dungeons.size() - 1)];
                if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(dungeonId))
                {
                    lfgType = LFG_TYPE_DUNGEON;
                    lfgName = dungeon->name[0];
                    WorldPacket p;
                    p << uint32(2); // lfg slot (LFG 队列槽位)
                    uint32 temp = dungeon->ID | (lfgType << 24);
                    p << temp;
                    bot->GetSession()->HandleSetLfgOpcode(p);
                    bot->GetSession()->HandleLfgClearAutoJoinOpcode(p);

                    // set auto invite if real players in queue (队列中有真实玩家时开启自动邀请)
                    /*vector<uint32> player_dungeons = sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()];
                    if (!player_dungeons.empty())
                    {
                        for (std::vector<uint32>::iterator i = player_dungeons.begin(); i != player_dungeons.end(); ++i)
                        {
                            uint32 zoneId = 0;
                            uint32 entry = (*i & 0xFFFF) & 0xFF;
                            uint32 type = ((*i & 0xFFFF) >> 8);
                            zoneId = (*i >> 16) & 0xFFFF;

                            // join only if in current zone
                            if (bot->GetZoneId() != zoneId)
                                continue;

                            // members queue only if player is lfm, not lfg
                            if (type != 1)
                                continue;

                            if (LFGDungeonEntry const* player_dungeon = sLFGDungeonStore.LookupEntry(entry))
                            {
                                if (player_dungeon->ID == dungeon->ID)
                                    bot->GetSession()->HandleLfgSetAutoJoinOpcode(p);
                            }
                        }
                    }*/
                    joinedLFG = true;
                }
            }
        }
    }
    
    if (!joinedLFG)
        return false;

    // set comment (设置备注信息)
    BotRoles botRoles = AiFactory::GetPlayerRoles(bot);
    std::string _botRoles;
    switch (botRoles)
    {
    case BOT_ROLE_TANK:
        _botRoles = "Tank";
        break;
    case BOT_ROLE_HEALER:
        _botRoles = "Healer";
        break;
    case BOT_ROLE_DPS:
    default:
        _botRoles = "Dps";
        break;
    }

    if (botRoles & BOT_ROLE_TANK && botRoles & BOT_ROLE_DPS)
        _botRoles = "Tank or Dps";

    WorldPacket p;
    std::string lfgComment;
    if (isLFM)
    {
        if (!group)
            lfgComment += _botRoles + ", ";

        lfgComment = "LF " + std::to_string(needMembers) + " more";
        if (questLFG)
            lfgComment += ", doing " + questName;
    }
    if (isLFG)
    {
        lfgComment = _botRoles;
        if (groupQ)
            lfgComment += ", lfg for " + questName;
        else if (questLFG)
            lfgComment += ", doing " + questName;
    }
    if (lfgType == LFG_TYPE_DUNGEON)
    {
        std::string _gs = std::to_string(bot->GetPlayerbotAI()->GetEquipGearScore(bot, false, false));
        lfgComment += ", GS " + _gs;
    }

    p << lfgComment;// +", GS - " + _gs;
    bot->GetSession()->HandleSetLfgCommentOpcode(p);
    std::string lfgGroup = isLFG ? "LFG" : "LFM";
    std::string lfgOption = lfgType == LFG_TYPE_QUEST ? "Quest" : (lfgType == LFG_TYPE_ZONE ? "Zone" : "Dungeon");

    if (realLFG)
        sLog.outDetail("Bot #%d %s:%d <%s>: uses %s, %s - %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), lfgGroup.c_str(), lfgOption.c_str(), lfgName.c_str(), _botRoles.c_str());
    else
        sLog.outDetail("Bot #%d %s:%d <%s>: uses %s, %s - %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), lfgGroup.c_str(), lfgOption.c_str(), lfgName.c_str(), _botRoles.c_str());
#endif
#ifdef MANGOSBOT_TWO
    LFGData pState = bot->GetLfgData();

    // check if already in lfg (检查是否已在地下城查找器队列中)
    if (!pState.GetListedDungeonSet().empty())
        return false;

    /*ItemCountByQuality visitor;
    IterateItems(&visitor, ITERATE_ITEMS_IN_EQUIP);
    bool random = urand(0, 100) < 20;
    bool heroic = urand(0, 100) < 50 && (visitor.count[ITEM_QUALITY_EPIC] >= 3 || visitor.count[ITEM_QUALITY_RARE] >= 10) && bot->GetLevel() >= 70;
    bool raid = !heroic && (urand(0, 100) < 50 && visitor.count[ITEM_QUALITY_EPIC] >= 5 && (bot->GetLevel() == 60 || bot->GetLevel() == 70 || bot->GetLevel() == 80));*/

    LfgDungeonSet list;
    std::vector<uint32> selected;

    std::vector<uint32> dungeons = sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()];
    if (!dungeons.size())
        return false;

    for (std::vector<uint32>::iterator i = dungeons.begin(); i != dungeons.end(); ++i)
    {
        LFGDungeonData const* dungeon = sLFGMgr.GetLFGDungeon(*i);
        if (!dungeon || (dungeon->type != LFG_TYPE_RANDOM_DUNGEON && dungeon->type != LFG_TYPE_DUNGEON && dungeon->type != LFG_TYPE_HEROIC_DUNGEON &&
            dungeon->type != LFG_TYPE_RAID))
            continue;

        uint32 botLevel = bot->GetLevel();
        if (!dungeon->CheckMinLevel(2, botLevel))
            continue;
        if (!dungeon->CheckMaxLevel(2, botLevel))
            continue;

        selected.push_back(dungeon->id);
        list.insert(dungeon->id);
    }

    if (selected.empty())
        return false;

    if (list.empty())
        return false;

    bool many = list.size() > 1;
    //LFGDungeonEntry const* dungeon = *list.begin();
    LFGDungeonData const* dungeon = sLFGMgr.GetLFGDungeon(*list.begin());

    /*for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
    {
        LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i);
        if (!dungeon || (dungeon->type != LFG_TYPE_RANDOM_DUNGEON && dungeon->type != LFG_TYPE_DUNGEON && dungeon->type != LFG_TYPE_HEROIC_DUNGEON &&
            dungeon->type != LFG_TYPE_RAID))
            continue;

        uint32 botLevel = bot->GetLevel();
        if (dungeon->minlevel && botLevel < dungeon->minlevel)
            continue;

        if (dungeon->minlevel && botLevel > dungeon->minlevel + 10)
            continue;

        if (dungeon->maxlevel && botLevel > dungeon->maxlevel)
            continue;

        if (heroic && !dungeon->difficulty)
            continue;

        if (raid && dungeon->type != LFG_TYPE_RAID)
            continue;

        if (!random && !raid && !heroic && dungeon->type != LFG_TYPE_DUNGEON)
            continue;

        list.insert(dungeon);
    }

    if (std::list.empty() && !random)
        return false;*/

    // check role for console msg (检查用于控制台日志显示的职责)
    std::string _roles = "multiple roles";

    if ((pState.GetPlayerRoles() & PLAYER_ROLE_TANK) != 0)
        _roles = "TANK";
    if ((pState.GetPlayerRoles() & PLAYER_ROLE_HEALER) != 0)
        _roles = "HEAL";
    if ((pState.GetPlayerRoles() & PLAYER_ROLE_DAMAGE) != 0)
        _roles = "DPS";

    //pState->SetType(LFG_TYPE_DUNGEON);
    sLog.outDetail("Bot #%d %s:%d <%s>: queues LFG, Dungeon as %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), _roles.c_str(), many ? "several dungeons" : dungeon->name.c_str());

    /*if (lfgState->IsSingleRole())
    {
        if (lfgState->HasRole(ROLE_TANK))
            _roles = "TANK";
        if (lfgState->HasRole(ROLE_HEALER))
            _roles = "HEAL";
        if (lfgState->HasRole(ROLE_DAMAGE))
            _roles = "DPS";
    }*/

    /*LFGDungeonEntry const* dungeon;

    if(!random)
        dungeon = *list.begin();

    bool many = list.size() > 1;

    if (random)
    {
        LFGDungeonSet randList = sLFGMgr.GetRandomDungeonsForPlayer(bot);
        for (LFGDungeonSet::const_iterator itr = randList.begin(); itr != randList.end(); ++itr)
        {
            LFGDungeonEntry const* dungeon = *itr;

            if (!dungeon)
                continue;

            idx.push_back(dungeon->ID);
        }
        if (idx.empty())
            return false;

        // choose random dungeon
        dungeon = sLFGDungeonStore.LookupEntry(idx[urand(0, idx.size() - 1)]);
        list.insert(dungeon);

        pState->SetType(LFG_TYPE_RANDOM_DUNGEON);
        sLog.outDetail("Bot #%d %s:%d <%s>: queues LFG, Random Dungeon as %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), _roles, dungeon->name[0]);
        return true;
    }
    else if (heroic)
    {
        pState->SetType(LFG_TYPE_HEROIC_DUNGEON);
        sLog.outDetail("Bot #%d %s:%d <%s>: queues LFG, Heroic Dungeon as %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), _roles, many ? "several dungeons" : dungeon->name[0]);
    }
    else if (raid)
    {
        pState->SetType(LFG_TYPE_RAID);
        sLog.outDetail("Bot #%d  %s:%d <%s>: queues LFG, Raid as %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), _roles, many ? "several dungeons" : dungeon->name[0]);
    }
    else
    {
        pState->SetType(LFG_TYPE_DUNGEON);
        sLog.outDetail("Bot #%d %s:%d <%s>: queues LFG, Dungeon as %s (%s)", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), _roles, many ? "several dungeons" : dungeon->name[0]);
    }*/

    // Set Raid Browser comment (设置团队查找器备注说明)
    std::string _gs = std::to_string(bot->GetEquipGearScore());
    std::string comment = "Bot " + _roles + " GS:" + _gs + " for LFG";
    sLFGMgr.JoinLfg(bot, GetRoles(), list, comment);
#endif
    return true;
}

/// 执行动作主逻辑（LFG 职责确认动作）
bool LfgRoleCheckAction::Execute(Event& event)
{
#ifdef MANGOSBOT_TWO
    Group* group = bot->GetGroup();
    if (group)
    {
        LFGQueuePlayer pData = sWorld.GetLFGQueue().GetQueueData(group->GetObjectGuid()).m_playerInfoPerGuid[bot->GetObjectGuid()];
        uint8 currentRoles = pData.m_roles;
        LfgRoles newRoles = GetRoles();
        if (currentRoles == (uint8)newRoles) return false;
        
        sWorld.GetLFGQueue().GetMessager().AddMessage([group = group->GetObjectGuid(), playerGuid = bot->GetObjectGuid(), newRoles](LFGQueue* queue)
        {
            queue->SetPlayerRoles(group, playerGuid, newRoles);
        });
        sLog.outDetail("Bot #%d %s:%d <%s>: LFG roles checked", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName());
        return true;
    }
#endif
    return false;
}

/// 执行动作主逻辑（接受地下城查找器邀请动作）
bool LfgAcceptAction::Execute(Event& event)
{
#ifdef MANGOSBOT_TWO
    //LFGData pState = bot->GetLfgData();
    //if (pState.GetState() != LFG_STATE_PROPOSAL)
    //    return false;

    //if (sWorld.GetLFGQueue().GetQueueData(bot->GetGroup() ? bot->GetGroup()->GetObjectGuid() : bot->GetObjectGuid()))

    uint32 id = AI_VALUE(uint32, "lfg proposal");
    if (id)
    {
        //if (urand(0, 1 + 10 / sPlayerbotAIConfig.randomChangeMultiplier))
        //    return false;

        if (bot->IsInCombat() || bot->IsDead())
        {
            sLog.outDetail("Bot #%d %s:%d <%s> is in combat and refuses LFG proposal %d", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), id);
            /*WorldPacket p(CMSG_LFG_PROPOSAL_RESULT);
            p << id;
            p << false;
            bot->GetSession()->HandleLfgProposalResultOpcode(p);*/
            bool accept = false;
            sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = bot->GetObjectGuid(), id, accept](LFGQueue* queue)
            {
                queue->UpdateProposal(playerGuid, id, accept);
            });
            return true;
        }

        sLog.outDetail("Bot #%d %s:%d <%s> accepts LFG proposal %d", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), id);
        ai->GetAiObjectContext()->GetValue<uint32>("lfg proposal")->Set(0);
        bot->clearUnitState(UNIT_STAT_ALL_STATE);
        /*WorldPacket p(CMSG_LFG_PROPOSAL_RESULT);
        p << id;
        p << uint8(1);
        bot->GetSession()->HandleLfgProposalResultOpcode(p);*/

        bool accept = true;
        sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = bot->GetObjectGuid(), id, accept](LFGQueue* queue)
        {
            queue->UpdateProposal(playerGuid, id, accept);
        });

        if (sRandomPlayerbotMgr.IsRandomBot(bot) && !bot->GetGroup())
        {
            sRandomPlayerbotMgr.Refresh(bot);
            ai->ResetStrategies();
            //bot->TeleportToHomebind();
        }
        ai->Reset();
        return true;
    }

    // 解析事件携带的网络封包数据
    WorldPacket p(event.getPacket());

    uint32 dungeon;
    uint8 state;
    p >> dungeon >> state >> id;

    ai->GetAiObjectContext()->GetValue<uint32>("lfg proposal")->Set(id);
#endif
    return true;
}

/// 执行动作主逻辑（离开 LFG 队列动作）
bool LfgLeaveAction::Execute(Event& event)
{
    // Don't leave if lfg strategy enabled (若启用了 LFG 策略则不要离开队列)
    //if (ai->HasStrategy("lfg", BotState::BOT_STATE_NON_COMBAT))
    //    return false;
#ifdef MANGOSBOT_ZERO
    LFGPlayerQueueInfo qInfo;
    sWorld.GetLFGQueue().GetPlayerQueueInfo(&qInfo, bot->GetObjectGuid());
    AreaTableEntry const* area = GetAreaEntryByAreaID(qInfo.areaId);
    if (area)
    {
        sLog.outDetail("Bot #%d %s:%d <%s>: leaves LFG queue to %s after %u minutes", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), area->area_name[0], (qInfo.timeInLFG / 60000));
        sWorld.GetLFGQueue().RemovePlayerFromQueue(bot->GetObjectGuid(), PLAYER_CLIENT_LEAVE);
    }
#endif
#ifdef MANGOSBOT_ONE
    /* todo: Fix with new system
    bool isLFG = false;
    bool isLFM = false;
    for (int i = 0; i < MAX_LOOKING_FOR_GROUP_SLOT; ++i)
        if (!bot->m_lookingForGroup.group[i].empty())
            isLFG = true;

    if (!bot->m_lookingForGroup.more.empty())
        isLFM = true;

    if (isLFG || isLFM)
    {
        sLog.outDetail("Bot #%d %s:%d <%s>: leaves %s", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->GetLevel(), bot->GetName(), isLFG ? "LFG" : "LFM");
        WorldPacket p;
        if (isLFG) // clear lfg
            bot->GetSession()->HandleLfgClearOpcode(p);
        if (isLFM) // clear lfm
            bot->GetSession()->HandleLfmClearOpcode(p);

        // clear comment
        std::string empty;
        p << empty;
        bot->GetSession()->HandleSetLfgCommentOpcode(p);
    }
    */
#endif
#ifdef MANGOSBOT_TWO
    // Don't leave if already invited / in dungeon (若已收到副本邀请或已身处副本内，则不离开队列)
    if (bot->GetLfgData().GetState() > LFG_STATE_QUEUED)
        return false;

    sLFGMgr.LeaveLfg(bot);
#endif
    return true;
}

/// 判断当前状态下该动作是否可用/有效（离开 LFG 队列动作）
bool LfgLeaveAction::isUseful()
{
#ifdef MANGOSBOT_ZERO
    if (!sWorld.GetLFGQueue().IsPlayerInQueue(bot->GetObjectGuid()))
        return false;
    else
    {
        LFGPlayerQueueInfo qInfo;
        sWorld.GetLFGQueue().GetPlayerQueueInfo(&qInfo, bot->GetObjectGuid());
        if (qInfo.timeInLFG < (5 * MINUTE * IN_MILLISECONDS))
            return false;
    }

    if (bot->GetGroup() && !ai->IsGroupLeader())
    {
        if (sWorld.GetLFGQueue().IsPlayerInQueue(bot->GetGroup()->GetLeaderGuid()))
            return false;
    }

    if ((ai->GetMaster() && !ai->GetMaster()->GetPlayerbotAI()))
    {
        return false;
    }
#endif
    return true;
}

/// 执行动作主逻辑（LFG 副本传送动作）
bool LfgTeleportAction::Execute(Event& event)
{
#ifdef MANGOSBOT_TWO
    bool out = false;

    // 解析事件携带的网络封包数据
    WorldPacket p(event.getPacket());
    if (!p.empty())
    {
        p.rpos(0);
        p >> out;
    }

    bot->clearUnitState(UNIT_STAT_ALL_STATE);
    sLFGMgr.TeleportPlayer(bot, out, false);
#endif
    return true;
}

/// 判断当前状态下该动作是否可用/有效（加入地下城查找器排队动作）
bool LfgJoinAction::isUseful()
{
    if (!sPlayerbotAIConfig.randomBotJoinLfg)
    {
        //ai->ChangeStrategy("-lfg", BotState::BOT_STATE_NON_COMBAT);
        return false;
    }

#ifdef MANGOSBOT_TWO
    if (bot->GetLevel() < 15)
        return false;
#endif

    // don't use if active player master (存在活跃真实玩家主人时不使用)
    if (ai->HasRealPlayerMaster())
        return false;

#ifdef MANGOSBOT_ZERO
    if (bot->GetGroup())
#else
    if (bot->GetGroup() && !ai->IsGroupLeader())
#endif
    {
        //ai->ChangeStrategy("-lfg", BotState::BOT_STATE_NON_COMBAT);
        return false;
    }

    if (bot->IsBeingTeleported())
        return false;

    if (bot->InBattleGround())
        return false;

    if (bot->InBattleGroundQueue())
        return false;

    if (bot->IsDead())
        return false;

    if (!sRandomPlayerbotMgr.IsFreeBot(bot))
        return false;

    Map* map = bot->GetMap();
    if (map && map->Instanceable())
        return false;
    
#ifdef MANGOSBOT_ZERO
    if (sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()].empty())
        return false;

    if (sWorld.GetLFGQueue().IsPlayerInQueue(bot->GetObjectGuid()))
        return false;

    LfgRoles botRoles = sLFGMgr.CalculateTalentRoles(bot);

    LfgRolePriority prio = sLFGMgr.GetPriority((Classes)bot->getClass(), (LfgRoles)botRoles);
    if (prio < LFG_PRIORITY_NORMAL)
        return false;

    if (bot->GetGroup() && bot->GetGroup()->IsFull())
        return false;
#endif
#ifdef MANGOSBOT_ONE
    /* todo: Fix with new system
    bool isLFG = false;
    bool isLFM = false;
    for (int i = 0; i < MAX_LOOKING_FOR_GROUP_SLOT; ++i)
        if (!bot->m_lookingForGroup.group[i].empty())
            isLFG = true;

    if (!bot->m_lookingForGroup.more.empty())
        isLFM = true;

    if ((isLFG || isLFM) && sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()].empty())
        return false;
        */
#endif
#ifdef MANGOSBOT_TWO
    if (sRandomPlayerbotMgr.LfgDungeons[bot->GetTeam()].empty())
        return false;

    LFGData pState = bot->GetLfgData();
    if (pState.GetState() != LFG_STATE_NONE)
        return false;
#endif
    return true;
}
