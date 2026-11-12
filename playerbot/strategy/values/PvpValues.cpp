// 策略值实现：PvpValues（战场军官搜索、战场排队筛选与扛旗手识别）

#include "playerbot/playerbot.h"
#include "PvpValues.h"
#include "BattleGround/BattleGroundWS.h"
#include "playerbot/ServerFacade.h"
#ifndef MANGOSBOT_ZERO
#include "BattleGround/BattleGroundEY.h"
#endif
#include "playerbot/TravelMgr.h"
#include "SharedValueContext.h"

using namespace ai;

// 从全局缓存中提取当前阵营与指定战场类型的全部战场军官实例数据
std::list<CreatureDataPair const*> BgMastersValue::Calculate()
{
    BattleGroundTypeId bgTypeId = (BattleGroundTypeId)stoi(qualifier);

    std::vector<uint32> entries;
    std::map<Team, std::map<BattleGroundTypeId, std::list<uint32>>> battleMastersCache = sRandomPlayerbotMgr.getBattleMastersCache();
    entries.insert(entries.end(), battleMastersCache[TEAM_BOTH_ALLOWED][bgTypeId].begin(), battleMastersCache[TEAM_BOTH_ALLOWED][bgTypeId].end());
    entries.insert(entries.end(), battleMastersCache[ALLIANCE][bgTypeId].begin(), battleMastersCache[ALLIANCE][bgTypeId].end());
    entries.insert(entries.end(), battleMastersCache[HORDE][bgTypeId].begin(), battleMastersCache[HORDE][bgTypeId].end());

    std::list<CreatureDataPair const*> bmGuids;

    for (auto entry : entries)
    {
        for(auto creaturePair : WorldPosition().getCreaturesNear(0, entry))
        {
            bmGuids.push_back(creaturePair);
        }        
    }

    return bmGuids;
}

// 优先查找存活且最近的战场军官，若无则放宽允许已死亡记录
CreatureDataPair const* BgMasterValue::Calculate()
{
    CreatureDataPair const* bmPair = NearestBm(false);

    if (!bmPair)
        bmPair = NearestBm(true);
   
    return bmPair;
}

// 遍历同地图非敌对区域的战场军官，返回直线距离最近的目标
CreatureDataPair const* BgMasterValue::NearestBm(bool allowDead)
{
    WorldPosition botPos(bot);

    std::list<CreatureDataPair const*> bmPairs = GAI_VALUE2(std::list<CreatureDataPair const*>, "bg masters", qualifier);

    float rDist;
    CreatureDataPair const* rbmPair = nullptr;

    for (auto& bmPair : bmPairs)
    {
        ObjectGuid bmGuid(HIGHGUID_UNIT, bmPair->second.id, bmPair->first);

        if (!bmPair)
            continue;

        WorldPosition bmPos(bmPair);

        float dist = botPos.distance(bmPos); //This is the aproximate travel distance. | 此处为近似估算的直线行进距离

        // Skip battlemasters that are not on the same map | 跳过不在同一地图上的战场军官
        if (bot->GetMapId() != bmPos.getMapId())
            continue;

        //Did we already find a closer unit that is not dead? | 已有更近的存活军官时跳过较远目标
        if (rbmPair && rDist <= dist)
            continue;

        CreatureInfo const* bmTemplate = ObjectMgr::GetCreatureTemplate(bmPair->second.id);

        if (!bmTemplate)
            continue;

        FactionTemplateEntry const* bmFactionEntry = sFactionTemplateStore.LookupEntry(bmTemplate->Faction);

        //Is the unit hostile? | 忽略对当前机器人敌对的军官
        if (ai->getReaction(bmFactionEntry) < REP_NEUTRAL)
            continue;

        AreaTableEntry const* area = bmPos.GetArea();

        if (!area)
            continue;

        //Is the area hostile? | 忽略位于敌对阵营领地内的军官
        if (area->team == 4 && bot->GetTeam() == ALLIANCE)
            continue;
        if (area->team == 2 && bot->GetTeam() == HORDE)
            continue;

        if (!allowDead)
        {
            Unit* unit = ai->GetUnit(bmPair);

            if (!unit)
                continue;

            //Is the unit dead? | 不允许死亡时跳过当前已死亡的军官
            if (unit->GetDeathState() == DEAD)
                continue;
        }

        rbmPair = bmPair;
        rDist = dist;
    }

    return rbmPair;
}


// 检查逃兵减益与排队槽位，随机返回本等级段尚未排队的战场类型
BattleGroundTypeId RpgBgTypeValue::Calculate()
{
    GuidPosition guidPosition = AI_VALUE(GuidPosition, "rpg target");

    // check Deserter debuff | 检查是否带有逃亡者减益（26013）
    if (!bot->CanJoinToBattleground())
        return BATTLEGROUND_TYPE_NONE;

    // check if has free queue slots | 检查是否还有空闲的战场排队栏位
    if (!bot->HasFreeBattleGroundQueueId())
        return BATTLEGROUND_TYPE_NONE;

    if(guidPosition)
        for (uint32 i = 1; i < MAX_BATTLEGROUND_QUEUE_TYPES; i++)
        {
            BattleGroundQueueTypeId queueTypeId = (BattleGroundQueueTypeId)i;

            BattleGroundTypeId bgTypeId = sServerFacade.BgTemplateId(queueTypeId);

            BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
            if (!bg)
                continue;

            if (bot->GetLevel() < bg->GetMinLevel())
                continue;

            // check if already in queue | 检查是否已在该战场的队列中
            if (bot->InBattleGroundQueueForBattleGroundQueueType(queueTypeId))
                continue;

            std::map<Team, std::map<BattleGroundTypeId, std::list<uint32>>> battleMastersCache = sRandomPlayerbotMgr.getBattleMastersCache();

            for (auto& entry : battleMastersCache[TEAM_BOTH_ALLOWED][bgTypeId])
                if (entry == guidPosition.GetEntry())
                    return bgTypeId;

            for (auto& entry : battleMastersCache[bot->GetTeam()][bgTypeId])
                if (entry == guidPosition.GetEntry())
                    return bgTypeId;
        }

    return BATTLEGROUND_TYPE_NONE;
}

// 查询战歌峡谷己方旗帜或风暴之眼中央旗帜的当前携带者 GUID
ObjectGuid FlagCarrierValue::Calculate()
{
    Unit* carrier = nullptr;

    if (ai->GetBot()->InBattleGround())
    {
        if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
        {
            BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();

            if (!bg)
                return ObjectGuid();

            if ((!sameTeam && bot->GetTeam() == HORDE || (sameTeam && bot->GetTeam() == ALLIANCE)) && !bg->GetFlagCarrierGuid(TEAM_INDEX_HORDE).IsEmpty())
                carrier = bg->GetBgMap()->GetPlayer(bg->GetFlagCarrierGuid(TEAM_INDEX_HORDE));

            if ((!sameTeam && bot->GetTeam() == ALLIANCE || (sameTeam && bot->GetTeam() == HORDE)) && !bg->GetFlagCarrierGuid(TEAM_INDEX_ALLIANCE).IsEmpty())
                carrier = bg->GetBgMap()->GetPlayer(bg->GetFlagCarrierGuid(TEAM_INDEX_ALLIANCE));

            if (carrier)
            {
                if (ignoreRange || bot->IsWithinDistInMap(carrier, sPlayerbotAIConfig.sightDistance))
                {
                    return carrier ? carrier->GetObjectGuid() : ObjectGuid();
                }
                else
                    return ObjectGuid();
            }
        }
#ifndef MANGOSBOT_ZERO
        if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_EY)
        {
            BattleGroundEY* bg = (BattleGroundEY*)ai->GetBot()->GetBattleGround();

            if (!bg)
                return ObjectGuid();

            if (bg->GetFlagCarrierGuid().IsEmpty())
                return ObjectGuid();

            Player* fc = bg->GetBgMap()->GetPlayer(bg->GetFlagCarrierGuid());
            if (!fc)
                return ObjectGuid();

            if (!sameTeam && (fc->GetTeam() != bot->GetTeam()))
                carrier = fc;

            if (sameTeam && (fc->GetTeam() == bot->GetTeam()))
                carrier = fc;

            if (carrier)
            {
                if (ignoreRange || bot->IsWithinDistInMap(carrier, sPlayerbotAIConfig.sightDistance))
                {
                    return carrier ? carrier->GetObjectGuid() : ObjectGuid();
                }
                else
                    return ObjectGuid();
            }
        }
#endif
    }
    return carrier ? carrier->GetObjectGuid() : ObjectGuid();
}
