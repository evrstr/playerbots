
#include "playerbot/playerbot.h"
#include "SetAvoidAreaAction.h"

#include "playerbot/strategy/values/PositionValue.h"
#include "MotionGenerators/PathFinder.h"
using namespace ai;


/// 执行动作主逻辑（设置避让区域动作）
bool SetAvoidAreaAction::Execute(Event& event)
{
    PathFinder pathfinder(bot->GetMapId(), bot->GetInstanceId());

    SET_AI_VALUE2(PositionEntry, "pos", "last avoid", PositionEntry(bot));

    std::list<ObjectGuid> targets = AI_VALUE_LAZY(std::list<ObjectGuid>, "possible targets");

    if (targets.empty())
        return false;

    FactionTemplateEntry const* humanFaction = sFactionTemplateStore.LookupEntry(1);
    FactionTemplateEntry const* orcFaction = sFactionTemplateStore.LookupEntry(2);

    for (auto& target : targets)
    {
        CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(target.GetEntry());

        if (!cInfo)
            continue;

        if (cInfo->NpcFlags > 0) // Ignore npcs. (忽略 NPC。)
            continue;

        if (cInfo->MaxLevel < bot->GetLevel() - 3) // Ignore lower level mobs. (忽略低等级怪物。)
            continue;

        FactionTemplateEntry const* factionEntry = sFactionTemplateStore.LookupEntry(cInfo->Faction);
        ReputationRank reactionHum = PlayerbotAI::GetFactionReaction(humanFaction, factionEntry);
        ReputationRank reactionOrc = PlayerbotAI::GetFactionReaction(orcFaction, factionEntry);

        if (reactionHum >= REP_NEUTRAL || reactionOrc >= REP_NEUTRAL) // ignore mobs friendly to opposing faction (they share avoid maps) (忽略对立阵营友好的怪物（共用避让表）)
            continue;

        Unit* targetUnit = ai->GetUnit(target);

        if (!targetUnit)
            continue;

        WorldPosition point(targetUnit);
        pathfinder.setArea(point.getMapId(), point.getX(), point.getY(), point.getZ(), 12, targetUnit->GetAttackDistance(bot) * 2.5);
        pathfinder.setArea(point.getMapId(), point.getX(), point.getY(), point.getZ(), 13, targetUnit->GetAttackDistance(bot));
    }

    return true;
}

/// 判断当前状态下该动作是否可用/有效（设置避让区域动作）
bool SetAvoidAreaAction::isUseful()
{
    if (bot->GetInstanceId())
        return false;

    PositionEntry p = AI_VALUE2(PositionEntry, "pos", "last avoid");

    if (!p.isSet())
        return true;

    return p.Get().distance(bot) > 20.0f;
}
