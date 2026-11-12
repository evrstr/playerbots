
#include "playerbot/playerbot.h"
#include "MoveToRpgTargetAction.h"
#include "ChooseRpgTargetAction.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/LootObjectStack.h"
#include "playerbot/strategy/values/PossibleRpgTargetsValue.h"
#include "playerbot/strategy/values/FreeMoveValues.h"
#include "playerbot/TravelMgr.h"

using namespace ai;

/// 执行动作主逻辑（前往 RPG 目标动作）
bool MoveToRpgTargetAction::Execute(Event& event)
{
    GuidPosition guidP = AI_VALUE(GuidPosition, "rpg target");
    Unit* unit = ai->GetUnit(guidP);
    GameObject* go = ai->GetGameObject(guidP);
    Player* player = guidP.GetPlayer();

    WorldObject* wo;
    if (unit)
    {
        wo = unit;
    }
    else if(go)
        wo = go;
    else
        return false;

    if (guidP.IsPlayer())
    {
        Player* player = guidP.GetPlayer();

        if (player && ai->IsSafe(player) && player->GetPlayerbotAI())
        {
            GuidPosition guidPP = PAI_VALUE(GuidPosition, "rpg target");

            if (guidPP.IsPlayer())
            {
                AI_VALUE(std::set<ObjectGuid>&,"ignore rpg target").insert(AI_VALUE(GuidPosition, "rpg target"));

                RESET_AI_VALUE(GuidPosition, "rpg target");

                if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
                {
                    ai->TellPlayerNoFacing(GetMaster(), "Rpg player target is targeting me. Drop target");
                }
                return false;
            }
        }
    }

    if (unit && unit->IsMoving() && !urand(0, 20) && guidP.sqDistance2d(bot) < INTERACTION_DISTANCE * INTERACTION_DISTANCE * 2)
    {
        AI_VALUE(std::set<ObjectGuid>&,"ignore rpg target").insert(AI_VALUE(GuidPosition, "rpg target"));

        RESET_AI_VALUE(GuidPosition,"rpg target");

        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            ai->TellPlayerNoFacing(GetMaster(), "Rpg target is moving. Random drop target.");
        }
        return false;
    }

    if (!CanFreeMoveValue::CanFreeMoveTo(ai, wo))
    {
        AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target").insert(AI_VALUE(GuidPosition, "rpg target"));

        RESET_AI_VALUE(GuidPosition, "rpg target");

        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            ai->TellPlayerNoFacing(GetMaster(), "Rpg target is far from mater. Random drop target.");
        }
        return false;
    }

    if (guidP.distance(bot) > sPlayerbotAIConfig.reactDistance * 2)
    {
        AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target").insert(AI_VALUE(GuidPosition, "rpg target"));

        RESET_AI_VALUE(GuidPosition, "rpg target");

        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            ai->TellPlayerNoFacing(GetMaster(), "Rpg target is beyond react distance. Drop target");
        }
        return false;
    }

    if (guidP.IsGameObject() && guidP.sqDistance2d(bot) < INTERACTION_DISTANCE * INTERACTION_DISTANCE && guidP.distance(bot) > INTERACTION_DISTANCE * 1.5 && !urand(0, 5))
    {
        AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target").insert(AI_VALUE(GuidPosition, "rpg target"));

        RESET_AI_VALUE(GuidPosition, "rpg target");

        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            ai->TellPlayerNoFacing(GetMaster(), "Under/above object drop rpg target");
        }
        return false;
    }

    if (!urand(0, 50))
    {
        AI_VALUE(std::set<ObjectGuid>&, "ignore rpg target").insert(AI_VALUE(GuidPosition, "rpg target"));

        RESET_AI_VALUE(GuidPosition, "rpg target");

        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            ai->TellPlayerNoFacing(GetMaster(), "Random drop rpg target");
        }
        return false;
    }

    float x = wo->GetPositionX();
    float y = wo->GetPositionY();
    float z = wo->GetPositionZ();
    float mapId = wo->GetMapId();

    if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
    {
        std::string name = chat->formatWorldobject(wo);

        ai->Poi(x, y, name);
    }
    
    if (sPlayerbotAIConfig.RandombotsWalkingRPG)
        if (!bot->GetTerrain()->IsOutdoors(bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ()))
            bot->m_movementInfo.AddMovementFlag(MOVEFLAG_WALK_MODE);

    float angle;
    float distance = 1.0f;
    
    if (bot->IsWithinLOS(x, y, z, true))
    {
        if (!unit || !unit->IsMoving())
            angle = wo->GetAngle(bot) + (M_PI * irand(-25, 25) / 100.0); // Closest 45 degrees towards the target (朝向目标方向最近的 45 度角位置)
        else if (!unit->HasInArc(bot))
            angle = wo->GetOrientation() + (M_PI * irand(-10, 10) / 100.0); // 20 degrees infront of target (leading it's movement) (目标前方 20 度位置（预判其移动方向）)
        else
            angle = wo->GetAngle(bot); // Current approuch angle. (当前接近角度。)

        if (guidP.sqDistance2d(bot) < INTERACTION_DISTANCE * INTERACTION_DISTANCE)
            distance = sqrt(guidP.sqDistance2d(bot)); // Stay at this distance. (保持在此间距。)
        else if(unit || !urand(0, 5)) // Stay futher away from npc's and sometimes gameobjects (for large hitbox objects). (与大型 NPC 或游戏对象保持稍远距离（适配大型碰撞体积）。)
            distance = frand(0.5, 1);
        else
            distance = frand(0, 0.5);
    }
    else
        angle = 2 * M_PI * urand(0, 100) / 100.0; // A circle around the target. (围绕目标的圆形范围。)

    x += cos(angle) * INTERACTION_DISTANCE * distance;
    y += sin(angle) * INTERACTION_DISTANCE * distance;

    WorldPosition movePos(mapId, x, y, z);
    
    if (movePos.distance(bot) < sPlayerbotAIConfig.sightDistance)
    {
        if (!movePos.ClosestCorrectPoint(5.0f, 5.0f, bot->GetInstanceId()) || abs(movePos.getZ()- z) > 10.0f)
        {
            ai->TellDebug(GetMaster(), "Can not path to desired location around " + chat->formatWorldobject(guidP.GetWorldObject(bot->GetInstanceId())) + " trying again later.", "debug move");

            return false;
        }
    }

    bool couldMove;

    if (unit && unit->IsMoving() && bot->GetDistance(unit) < INTERACTION_DISTANCE * 2 && unit->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE)
    {

        Creature* creature = static_cast<Creature*>(unit);


        if (creature)
            if (uint32 pauseTimer = creature->GetInteractionPauseTimer())
                creature->GetMotionMaster()->PauseWaypoints(pauseTimer);
    }
        couldMove = MoveTo(mapId, x, y, z, false, false);

    if (!couldMove && movePos.distance(bot) > INTERACTION_DISTANCE)
    {
        AI_VALUE(std::set<ObjectGuid>&,"ignore rpg target").insert(AI_VALUE(GuidPosition, "rpg target"));

        RESET_AI_VALUE(GuidPosition, "rpg target");

        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            ai->TellPlayerNoFacing(GetMaster(), "Could not move to rpg target. Drop rpg target");
        }

        return false;
    }

    if ((ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT) || ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT)) && guidP.GetWorldObject(bot->GetInstanceId()))
    {
        if (couldMove)
        {
            std::ostringstream out;
            out << "Heading to: ";
            out << chat->formatWorldobject(guidP.GetWorldObject(bot->GetInstanceId()));
            ai->TellPlayerNoFacing(GetMaster(), out);
        }
        else
        {
            std::ostringstream out;
            out << "Near: ";
            out << chat->formatWorldobject(guidP.GetWorldObject(bot->GetInstanceId()));
            ai->TellPlayerNoFacing(GetMaster(), out);
        }
    }

    return couldMove;
}

/// 判断当前状态下该动作是否可用/有效（前往 RPG 目标动作）
bool MoveToRpgTargetAction::isUseful()
{
    GuidPosition guidP = AI_VALUE(GuidPosition, "rpg target");
    WorldPosition oldPosition = guidP;

    if (!guidP)
        return false;

    WorldObject* wo = guidP.GetWorldObject(bot->GetInstanceId());

    if (!wo)
    {
        RESET_AI_VALUE(GuidPosition, "rpg target");

        if (ai->HasStrategy("debug rpg", BotState::BOT_STATE_NON_COMBAT))
        {
            ai->TellPlayerNoFacing(GetMaster(), "Target could not be found. Drop rpg target");
        }
    }

    if(MEM_AI_VALUE(WorldPosition, "current position")->LastChangeDelay() < 60)
        if (bot->IsMoving() && bot->GetMotionMaster() && bot->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE)
            return false;

    if (AI_VALUE(bool, "travel target traveling"))
        return false;

    if (AI_VALUE2(float, "distance", "rpg target") < INTERACTION_DISTANCE)
        return false;

    if (!AI_VALUE(bool, "can move around"))
        return false;

    // Should the bot still loot something? (检查机器人是否仍有尚未拾取的战利品)
    if (AI_VALUE(bool, "has available loot"))
    {
        LootObject lootObject = AI_VALUE(LootObjectStack*, "available loot")->GetLoot(ai->GetRange("loot"));
        if (lootObject.IsLootPossible(bot))
            return false;
    }

    // Is the bot still going to loot something? (检查机器人是否仍有待拾取的目标)
    LootObject loot = AI_VALUE(LootObject, "loot target");

    if (loot.IsLootPossible(bot))
        return false;

    return true;
}


