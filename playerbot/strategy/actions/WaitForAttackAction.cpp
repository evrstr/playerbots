
#include "playerbot/playerbot.h"
#include "WaitForAttackAction.h"
#include "playerbot/strategy/generic/CombatStrategy.h"
#include "playerbot/strategy/values/PositionValue.h"

using namespace ai;

/// 执行动作主逻辑（等待开怪保持安全距离动作）
bool WaitForAttackKeepSafeDistanceAction::Execute(Event& event)
{  
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (target)
    {
        WorldPosition basePos = WorldPosition(target);
        if (target->GetTarget())
        {
            target = target->GetTarget();
            basePos = WorldPosition(target);
            if (target->IsPlayer())
            {
                // If target's target is a bot, see if we can get the pull back pos (若目标的目标是机器人，尝试获取拉回位置)
                // else we should just base it off of the player pos
                Player* player = (Player*)target;

                if (PlayerbotAI* pullerAI = player->GetPlayerbotAI())
                {
                    if (pullerAI->HasStrategy("pull back", BotState::BOT_STATE_COMBAT))
                    {
                        PositionMap& posMap = PAI_VALUE(PositionMap&, "position");
                        PositionEntry pullPosition = posMap["pull"];
                        if (pullPosition.valueSet)
                            basePos = pullPosition.Get();
                    }
                }
            }
        }

        if (target->IsAlive())
        {
            const float safeDistance = WaitForAttackStrategy::GetSafeDistance();
            const float safeDistanceThreshold = WaitForAttackStrategy::GetSafeDistanceThreshold();

            // only reposition if it makes sense, ie. we are actually too close to danger (仅在确实过于接近危险时才调整站位)
            if (WorldPosition(bot).fDist(basePos) <= safeDistance)
            {
                // Find the best point around the target. (查找目标周围的最佳站位点。)
                const WorldPosition bestPoint = GetBestPoint(basePos, (safeDistance - safeDistanceThreshold), safeDistance);
                if (bestPoint)
                {
                    // Move to the best point (移动到最佳站位点)
                    bool success = MoveTo(bestPoint.getMapId(), bestPoint.getX(), bestPoint.getY(), bestPoint.getZ(), false, false, false, true);
                    if (success)
                        WaitForReach(WorldPosition(bot).fDist(bestPoint));
                    return success;
                }
            }

        }
    }

    return false;
}

/// 从候选坐标集合中评估并挑选最安全的站位点
const ai::WorldPosition WaitForAttackKeepSafeDistanceAction::GetBestPoint(const WorldPosition& pos, float minDistance, float maxDistance) const
{
    const WorldPosition botPosition(bot);
    const WorldPosition targetPosition = pos;
    const int8 startDir = urand(0, 1) * 2 - 1;
    const float radiansIncrement = (5.0f / 180.0f) * (M_PI_F);
    const float startAngle = targetPosition.getAngleTo(botPosition) + urand(0.f,radiansIncrement) * startDir;
    const float distance = frand(minDistance, maxDistance);
    const std::list<ObjectGuid> enemies = AI_VALUE(std::list<ObjectGuid>, "possible targets no los");

    if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
    {
        for (uint32 dist = 0; dist < distance; dist++)
        {
            WorldPosition point = targetPosition + WorldPosition(0, dist * cos(startAngle), dist * sin(startAngle), 1.0f);
            Creature* wpCreature = bot->SummonCreature(1, point.getX(), point.getY(), point.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 1000.0f + dist * 100.0f);
        }
    }

    std::list<WorldPosition> points;

    for (float tryAngle = 0.0f; tryAngle < M_PI_F; tryAngle += radiansIncrement)
    {
        for (int8 tryDir = -1; tryAngle && tryDir < 1; tryDir += 2)
        {
            float pointAngle = startAngle;
            pointAngle += tryAngle * startDir * tryDir;

            WorldPosition point = targetPosition + WorldPosition(0, distance * cos(pointAngle), distance * sin(pointAngle), 1.0f);

            point.setZ(point.getHeight());

            if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
            {
                Creature* wpCreature = bot->SummonCreature(1, point.getX(), point.getY(), point.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f + tryAngle * 1000.0f);
            }

            // Check if the target is visible from the point (检查从该坐标点是否能直接看见目标)
            if (!pos.IsInLineOfSight(WorldPosition(point.getMapId(), point.getX(), point.getY(), point.getZ() + bot->GetCollisionHeight())))
                continue;

            // Check if the point is not surrounded by other enemies (检查坐标点周围是否没有其他敌人包围)
            if (IsEnemyClose(point, enemies))
                continue;

            // Check if the bot can move to this point. (检查机器人能否移动到该坐标点。)
            if (!botPosition.canPathTo(point,bot))
                continue;

            if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
            {
                Creature* wpCreature = bot->SummonCreature(15631, point.getX(), point.getY(), point.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f + tryAngle * 1000.0f);
            }

            points.push_back(point);
        }
    }

    // Use a minimal move from where we are to a safe spot. If no points were found just use original pos. (从当前位置微调至安全点；若未找到安全点则保留原坐标。)
    WorldPosition minimumMove = botPosition;
    if (!points.empty())
    {
        auto it = std::min_element(points.begin(), points.end(),
            [botPosition](const WorldPosition& i, const WorldPosition& j) {
                return botPosition.fDist(i) < botPosition.fDist(j);
            });

        if (it != points.end())
            return *it;
    }
    return minimumMove;
}

/// 判断附近指定半径内是否存在敌对单位
bool WaitForAttackKeepSafeDistanceAction::IsEnemyClose(const WorldPosition& point, const std::list<ObjectGuid>& enemies) const
{
    for (const ObjectGuid& enemyGUID : enemies)
    {
        Unit* enemy = ai->GetUnit(enemyGUID);
        if (enemy)
        {
            // If the enemy is not neutral (若敌对单位并非中立状态)
            if (enemy->CanAttackOnSight(bot))
            {
                const float enemyAttackRange = enemy->GetAttackDistance(bot) + ATTACK_DISTANCE;
                const float distanceToPoint = WorldPosition(enemy).sqDistance(point);
                if (distanceToPoint <= (enemyAttackRange * enemyAttackRange))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（等待开怪保持安全距离动作）
bool WaitForAttackKeepSafeDistanceAction::isUseful()
{
    // Not useful to keep safe distance if we need to cc. (需要执行控场时无需刻意保持安全距离。)
    bool notCCBusy = (!ai->GetUnit(AI_VALUE2(ObjectGuid, "cc target", getName())) || (ai->GetUnit(AI_VALUE2(ObjectGuid, "cc target", getName())) && ai->GetUnit(AI_VALUE2(ObjectGuid, "current cc target", getName()))));

    return !ai->HasStrategy("stay", ai->GetState()) && notCCBusy && (!ai->HasStrategy("guard", ai->GetState()) ||  WaitForAttackStrategy::GetSafeDistance() <= ai->GetRange("guard")) && ai->GetRange("flee") > 5.0f;
}
