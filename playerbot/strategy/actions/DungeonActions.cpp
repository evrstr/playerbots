#include "DungeonActions.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "playerbot/strategy/AiObjectContext.h"
#include "playerbot/PlayerbotAI.h"
#include "playerbot/ServerFacade.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;

/// 执行动作主逻辑（远离地面危险区域动作）
bool MoveAwayFromHazard::Execute(Event& event)
{
    const std::list<HazardPosition>& hazards = AI_VALUE(std::list<HazardPosition>, "hazards");

    // Get the closest hazard to move away from (获取需要躲避的最近危险区域)
    const HazardPosition* closestHazard = nullptr;
    float closestHazardDistance = 9999.0f;
    for (const HazardPosition& hazard : hazards)
    {
        const WorldPosition& hazardPosition = hazard.first;
        const float distance = bot->GetDistance(hazardPosition.getX(), hazardPosition.getY(), hazardPosition.getZ());
        if (distance < closestHazardDistance)
        {
            closestHazardDistance = distance;
            closestHazard = &hazard;
        }
    }

    if (closestHazard)
    {
        // Check if the bot is inside the closest hazard (检查机器人是否正处于最近的危险区域内部)
        const float hazardRadius = closestHazard->second;
        if (closestHazardDistance <= hazardRadius)
        {
            float angle = 0.0f;
            const WorldPosition initialPosition(closestHazard->first);
            const float distance = frand(hazardRadius, hazardRadius * 1.5f);

            Unit* currentTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if (currentTarget)
            {
                const int8 startDir = urand(0, 1) * 2 - 1;
                const WorldPosition targetPosition(currentTarget);
                angle = targetPosition.getAngleTo(initialPosition) + (0.5 * M_PI_F * startDir);
            }
            else
            {
                angle = frand(0, M_PI_F * 2.0f);
            }

            const uint8 attempts = 10;
            float angleIncrement = (float)((2 * M_PI) / attempts);

            for (uint8 i = 0; i < attempts; i++)
            {
                WorldPosition point = initialPosition + WorldPosition(0, distance * cos(angle), distance * sin(angle), 1.0f);
                point.setZ(point.getHeight());

                // Check if the point is not near other hazards (检查坐标点是否远离其他危险区域)
                if (!IsHazardNearby(point, hazards))
                {
                    if (bot->IsWithinLOS(point.getX(), point.getY(), point.getZ() + bot->GetCollisionHeight()) && initialPosition.canPathTo(point, bot))
                    {
                        if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
                        {
                            bot->SummonCreature(15631, point.getX(), point.getY(), point.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f);
                        }

                        if (MoveTo(bot->GetMapId(), point.getX(), point.getY(), point.getZ(), false, IsReaction(), false, true))
                        {
                            if (!IsReaction())
                            {
                                WaitForReach(point.distance(initialPosition));
                            }

                            return true;
                        }
                    }
                }

                if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
                {
                    bot->SummonCreature(1, point.getX(), point.getY(), point.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f);
                }

                angle += angleIncrement;
            }
        }
    }

    return false;
}

/// 判断执行该动作的前置条件是否满足（远离地面危险区域动作）
bool MoveAwayFromHazard::isPossible()
{
    if (MovementAction::isPossible())
    {
        return ai->CanMove();
    }

    return false;
}

/// 检查机器人当前周围是否存在需要规避的危险区域
bool MoveAwayFromHazard::IsHazardNearby(const WorldPosition& point, const std::list<HazardPosition>& hazards) const
{
    for (const HazardPosition& hazard : hazards)
    {
        const float hazardRange = hazard.second;
        const WorldPosition& hazardPosition = hazard.first;
        const float distance = point.distance(hazardPosition);
        if (distance < hazardRange)
        {
            return true;
        }
    }

    return false;
}

/// 遍历并筛选符合条件的附近生物辅助函数
bool MoveAwayFromCreature::CreatureSearchHelperFunction(Event& event, uint32 creatureId)
{
    // Get the active attacking creatures (获取当前正在交战的敌对生物列表)
    std::list<Creature*> creatures;
    size_t closestCreatureIdx = 0;
    float closestCreatureDistance = 9999.0f;

    // Iterate through the near creatures (遍历附近的生物单位)
    std::list<Unit*> units;
    MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(bot, creatureID, range);
    MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(units, u_check);
    Cell::VisitAllObjects(bot, searcher, range);

    for (Unit* unit : units)
    {
        Creature* creature = (Creature*)unit;
        if (creature)
        {
            creatures.push_back(creature);

            // Get the closest creature to the bot (获取距离机器人最近的生物)
            const float distance = bot->GetDistance(creature);
            if (distance < closestCreatureDistance)
            {
                closestCreatureDistance = distance;
                closestCreatureIdx = creatures.size() - 1;
            }
        }
    }

    if (creatures.empty() || closestCreatureDistance >= range)
    {
        return false;
    }

    const std::list<HazardPosition>& hazards = AI_VALUE(std::list<HazardPosition>, "hazards");

    // Get the closest creature reference (获取距离最近的生物参考坐标)
    auto it = creatures.begin();
    advance(it, closestCreatureIdx);
    Creature* closestCreature = *it;
    // Remove the closest creature from the list to prevent checking it twice (从列表中移除最近的生物以免重复检测)
    creatures.erase(it);

    // Generate the initial angle directly behind the bot looking at the closest creature (生成机器人背对最近生物正后方的初始撤退角度)
    WorldPosition botPosition(bot);
    WorldPosition targetPosition(closestCreature);
    float angleLeft = targetPosition.getAngleTo(botPosition);
    float angleRight = angleLeft;

    Group* group = bot->GetGroup();
    bool shouldRunToHeal = group && healersSafe && !ai->IsHeal(bot, true);
    if (shouldRunToHeal)
    {
        std::list<WorldPosition> points;
        for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
        {
            Player* member = ref->getSource();
            if (!member || !sServerFacade.IsAlive(member))
                continue;

            if (ai->IsHeal(member, true))
            {
                WorldPosition healPosition(member);
                points.push_back(healPosition);
            }
        }
        // Use a minimal move from where we are to a safe spot. (从当前位置执行最小位移移动至安全地点。)
        if (!points.empty())
        {
            points.sort([botPosition](WorldPosition i, WorldPosition j) { return botPosition.fDist(i) < botPosition.fDist(j); });
            WorldPosition* validPoint = &points.front();
            if (IsValidPoint(points.front(), creatures, hazards))
            {
                if (MoveTo(bot->GetMapId(), validPoint->getX(), validPoint->getY(), validPoint->getZ(), false, IsReaction(), false, false))
                {
                    if (!IsReaction())
                        WaitForReach(validPoint->distance(botPosition));
                    return true;
                }
            }

        }
    }

    const uint8 attempts = 20;
    const uint8 halfAtempts = (uint8)(attempts * 0.5f);
    float angleIncrement = (float)((M_PI) / halfAtempts);

    const float sizeFactor = bot->GetCombatReach() + closestCreature->GetCombatReach();
    const float distance = (range + sizeFactor);

    for (uint8 i = 0; i < halfAtempts; i++)
    {
        WorldPosition* validPoint = nullptr;

        // Calculate a point to the left and right (计算左右两侧的偏移点)
        WorldPosition pointLeft = targetPosition + WorldPosition(0, distance * cos(angleLeft), distance * sin(angleLeft), 1.0f);
        pointLeft.setZ(pointLeft.getHeight());
        WorldPosition pointRight = targetPosition + WorldPosition(0, distance * cos(angleRight), distance * sin(angleRight), 1.0f);
        pointRight.setZ(pointRight.getHeight());

        if (IsValidPoint(pointLeft, creatures, hazards))
        {
            validPoint = &pointLeft;
        }
        else if (IsValidPoint(pointRight, creatures, hazards))
        {
            validPoint = &pointRight;
        }

        if (validPoint)
        {
            if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
            {
                bot->SummonCreature(15631, validPoint->getX(), validPoint->getY(), validPoint->getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f);
            }

            if (MoveTo(bot->GetMapId(), validPoint->getX(), validPoint->getY(), validPoint->getZ(), false, IsReaction(), false, true))
            {
                if (!IsReaction())
                {
                    WaitForReach(validPoint->distance(botPosition));
                }

                return true;
            }
        }

        if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
        {
            bot->SummonCreature(1, pointLeft.getX(), pointLeft.getY(), pointLeft.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f);
            bot->SummonCreature(1, pointRight.getX(), pointRight.getY(), pointRight.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f);
        }

        angleLeft += angleIncrement;
        angleRight -= angleIncrement;
    }

    return false;
}

/// 执行动作主逻辑（远离特定生物动作）
bool MoveAwayFromCreature::Execute(Event& event)
{
    return CreatureSearchHelperFunction(event, creatureID);
}

/// 判断执行该动作的前置条件是否满足（远离特定生物动作）
bool MoveAwayFromCreature::isPossible()
{
    if (MovementAction::isPossible())
    {
        return ai->CanMove();
    }

    return false;
}

/// 验证三维坐标点是否处于合法地图边界与有效地形内
bool MoveAwayFromCreature::IsValidPoint(const WorldPosition& point, const std::list<Creature*>& creatures, const std::list<HazardPosition>& hazards)
{
    // Check if the point is not near other game objects (检查坐标点是否远离其他游戏对象)
    if (!HasCreaturesNearby(point, creatures) && !IsHazardNearby(point, hazards))
    {
        if (bot->IsWithinLOS(point.getX(), point.getY(), point.getZ() + bot->GetCollisionHeight()))
        {
            const WorldPosition botPosition(bot);
            return botPosition.canPathTo(point, bot);
        }
    }

    return false;
}

/// 检查周围指定范围内是否存在生物单位
bool MoveAwayFromCreature::HasCreaturesNearby(const WorldPosition& point, const std::list<Creature*>& creatures) const
{
    for (const Creature* creature : creatures)
    {
        const float distance = creature->GetDistance(point.getX(), point.getY(), point.getZ());
        if (distance <= range)
        {
            return true;
        }
    }

    return false;
}

/// 检查机器人当前周围是否存在需要规避的危险区域
bool MoveAwayFromCreature::IsHazardNearby(const WorldPosition& point, const std::list<HazardPosition>& hazards) const
{
    for (const HazardPosition& hazard : hazards)
    {
        const float hazardRange = hazard.second;
        const WorldPosition& hazardPosition = hazard.first;
        const float distance = point.distance(hazardPosition);
        if (distance < hazardRange)
        {
            return true;
        }
    }

    return false;
}

/// 执行动作主逻辑（远离指定生物列表动作）
bool MoveAwayFromSpecificCreatures::Execute(Event& event)
{
    std::set<uint32>&creatureIDList = AI_VALUE(std::set<uint32>&, "avoid creature list");
    for (const uint32 creatureToCheck : creatureIDList)
    {
        bool result = CreatureSearchHelperFunction(event, creatureToCheck);
        if (result)
            return result;
    }
    return false;
}
