// 策略值实现：FreeMoveValues（自由活动中心与范围校验）

#include "playerbot/playerbot.h"
#include "FreeMoveValues.h"
#include "PositionValue.h"
#include "Formations.h"


using namespace ai;

// 根据跟随策略、传送状态及阵型坐标确定自由移动中心点
GuidPosition FreeMoveCenterValue::Calculate()
{       
    if (ai->HasStrategy("follow", ai->GetState()) ||
        ai->HasStrategy("wander", ai->GetState()))
    {
        Unit* followTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "follow target"));

        if (!followTarget)
            return bot;

        //Use bot as center when follow target is on a different map. | 跟随目标位于不同地图时以机器人自身为中心
        if (followTarget->GetMapId() != bot->GetMapId()) 
            return followTarget;

        Player* player = dynamic_cast<Player*>(followTarget);

        //Use bot as cetner when follow target is being teleported. | 跟随目标正在传送时以机器人自身为中心
        if (player && player->IsBeingTeleported())
            return bot;

        //Use formation location as reference point. | 以阵型计算出的站位作为参考点
        Formation* formation = AI_VALUE(Formation*, "formation");
        GuidPosition loc(followTarget->GetObjectGuid(),formation->GetLocation());

        if (Formation::IsNullLocation(loc) || loc.mapid == -1)
            return followTarget;

        //Move the location to a location around follow targets destination. | 将参考位置微调至跟随目标目的地的周边
        if (player && player->GetPlayerbotAI() && ai->IsSafe(player) && PAI_VALUE(WorldPosition, "last long move"))
            loc += (PAI_VALUE(WorldPosition, "last long move") - player);

        return loc;
    }

    PositionEntry pos;

    if (ai->HasStrategy("stay", ai->GetState()) && (pos = AI_VALUE2(PositionEntry, "pos", "stay")).isSet())
        return GuidPosition(bot->GetObjectGuid(), pos.Get());

    if (ai->HasStrategy("guard", ai->GetState()) && (pos = AI_VALUE2(PositionEntry, "pos", "guard")).isSet())
        return GuidPosition(bot->GetObjectGuid(), pos.Get());

    return bot;
}

// 根据跟随/停留/漫游等策略与阵型最大距离计算允许活动半径
float FreeMoveRangeValue::Calculate()
{
    if (ai->HasStrategy("stay", ai->GetState()))
        return INTERACTION_DISTANCE;

    if (ai->GetUnit(AI_VALUE(ObjectGuid, "rti cc target")))
        return ai->GetRange("spell");

    Unit* followTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "follow target"));

    if (!followTarget || followTarget == bot)
        return 0;

   if (ai->HasStrategy("wander", ai->GetState()))
   {
       return ai->GetRange("wandermax");
   }
   if (ai->HasStrategy("follow", ai->GetState()))
   {
       return ai->GetRange("follow");
   }
   if (ai->HasStrategy("guard", ai->GetState()))
   {
       return ai->GetRange("guard");
   }
    
   return 0;
}

// 检查目标位置与自由移动中心的平面距离是否在允许范围内
bool CanFreeMoveValue::CanFreeMove(PlayerbotAI* ai, WorldPosition dest, float range)
{
    if (!dest)
        return true;

    if (!range)
        return true;

    AiObjectContext* context = ai->GetAiObjectContext();

    GuidPosition center = AI_VALUE(GuidPosition, "free move center");
    return center.distance(dest) < range;
}

// 判定是否允许自由移动至目标点
bool CanFreeMoveValue::CanFreeMoveTo(PlayerbotAI* ai, WorldPosition dest)
{
    AiObjectContext* context = ai->GetAiObjectContext();
    return CanFreeMove(ai, dest, AI_VALUE(float, "free move range"));
}

// 判定攻击或交互目标是否在允许移动范围加施法射程内
bool CanFreeMoveValue::CanFreeTarget(PlayerbotAI* ai, WorldPosition dest)
{
    AiObjectContext* context = ai->GetAiObjectContext();
    float range = ai->HasStrategy("stay", BotState::BOT_STATE_NON_COMBAT) ? std::min(ai->GetRange("spell"), AI_VALUE(float, "free move range")) : AI_VALUE(float, "free move range");

    return CanFreeMove(ai, dest, range);
}

// 判定目标是否在自由移动范围内可进行攻击
bool CanFreeMoveValue::CanFreeAttack(PlayerbotAI* ai, WorldPosition dest)
{
    return CanFreeMove(ai, dest, ai->GetRange("attack"));
}

// 解析限定符中的位置点并校验是否允许自由移动至该处
bool CanFreeMoveValue::Calculate()
{
    float range = 0.0;

    if (qualifier.empty())
        range = AI_VALUE(float, "free move range");
    else
        range = ai->GetRange(qualifier);

    return CanFreeMove(ai, bot, range);
}
