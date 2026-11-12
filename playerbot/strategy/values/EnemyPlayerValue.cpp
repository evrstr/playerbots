// 策略值实现：EnemyPlayerValue（敌对玩家合法性、可达性校验与目标优选）

#include "playerbot/playerbot.h"
#include "EnemyPlayerValue.h"
#include "TargetValue.h"

using namespace ai;

// 计算附近符合攻击条件的敌对玩家列表
std::list<ObjectGuid> EnemyPlayersValue::Calculate()
{
    std::list<ObjectGuid> result;
    if (ai->AllowActivity(ALL_ACTIVITY))
    {
        if (bot->IsInWorld() && !bot->IsBeingTeleported())
        {
            // Check if we only need one attacker | 检查是否只需获取一名敌对玩家
            bool getOne = false;
            if (!qualifier.empty())
            {
                getOne = std::stoi(qualifier);
            }

            if (getOne)
            {
                // Try to get one enemy target | 尝试先获取单个潜在敌对目标
                result = AI_VALUE2(std::list<ObjectGuid>, "possible attack targets", 1);
                ApplyFilter(result, getOne);
            }

            // If the one enemy player failed, retry with multiple possible attack targets | 若单个目标筛选失败，则回退遍历完整目标列表
            if (result.empty())
            {
                result = AI_VALUE(std::list<ObjectGuid>, "possible attack targets");
                ApplyFilter(result, getOne);
            }
        }
    }

    return result;
}

// 校验目标是否为非友方、非心控友军且可攻击的敌对玩家
bool EnemyPlayersValue::IsValid(Unit* target, Player* player)
{
    if (target)
    {
        // If the target is a player | 确认目标为玩家单位
        Player* enemyPlayer = dynamic_cast<Player*>(target);
        if (enemyPlayer)
        {
            // If the target is friendly to the player | 若目标对己方友好则排除
            if (sServerFacade.IsFriendlyTo(target, player))
            {
                return false;
            }

            // Check that the target is not a mind controlled ally | 排除被心灵控制的友方玩家
            if (target->HasAuraType(SPELL_AURA_MOD_CHARM) || target->HasAuraType(SPELL_AURA_MOD_POSSESS))
            {
                if (player && player->IsInGroup(target))
                {
                    return false;
                }
            }

            if (!IsReachable(target, player))
            {
                return false;
            }

            // 注释：已停用的旧距离校验代码
            /*
            // Check if too far away (Do we need this?)
            const float maxPvPDistance = GetMaxAttackDistance(player);
            const bool inCannon = player->GetPlayerbotAI() && player->GetPlayerbotAI()->IsInVehicle(false, true);
            uint32 const pvpDistance = (inCannon || player->GetHealth() > enemyPlayer->GetHealth()) ? maxPvPDistance : 20.0f;
            if (!player->IsWithinDist(enemyPlayer, pvpDistance, false))
            {
                return false;
            }
            */

            return true;
        }
    }

    return false;
}

// 结合高度差阈值和寻路系统判定敌对玩家是否实际可达
bool EnemyPlayersValue::IsReachable(Unit* target, Player* player)
{
    // A player standing under the map (or on a ledge with no way up) is close in 2D but can | 处于地图下方或无法到达高台的玩家 2D 距离虽近但实际不可达，防止机器人无限卡死战斗
    // never be reached, and would otherwise keep the bot in combat with it indefinitely. | 否则会导致机器人永久停留在对其战斗状态中
    if (!player || !PlayerbotAI::IsSafe(player, target))
    {
        return true;
    }

    // The path check below decides reachability. This height gate only decides when it is | 下方路径检测决定可达性；高度差阈值用于过滤普通台阶斜坡，避免高频寻路开销
    // worth running: normal fights (slopes, stairs, small ledges) stay within a few yards | 常见高低差较小无需调用完整寻路
    // of height, so skipping them keeps the pathfinder out of the common case. The cases | 仅针对落差过大（如掉入地下约 30 码）的异常情况触发寻路校验
    // this targets are far outside it (e.g. a player that fell ~30 yd under the map). | 该类异常目标通常远离正常战斗高度范围
    // A lower value only costs more path checks, a higher one only misses shallower cases. | 阈值越小寻路调用越频繁，越大则可能漏检浅层卡位
    const float maxHeightWithoutPathCheck = 10.0f;
    if (std::abs(target->GetPositionZ() - player->GetPositionZ()) <= maxHeightWithoutPathCheck)
    {
        return true;
    }

    return WorldPosition(player).canPathTo(WorldPosition(target), player);
}

// 校验并筛选有效可达的敌对玩家目标列表
void EnemyPlayersValue::ApplyFilter(std::list<ObjectGuid>& targets, bool getOne)
{
    std::list<ObjectGuid> filteredTargets;
    for (const ObjectGuid& targetGuid : targets)
    {
        Unit* target = ai->GetUnit(targetGuid);
        if (IsValid(target, bot))
        {
            filteredTargets.push_back(target->GetObjectGuid());

            if (getOne)
            {
                break;
            }
        }
    }

    targets = filteredTargets;
}

// 检查 enemy player targets 是否非空
bool HasEnemyPlayersValue::Calculate()
{
    return !context->GetValue<std::list<ObjectGuid>>("enemy player targets", 1)->Get().empty();
}

// 优先选择决斗对手或战场扛旗者，其次按距离或最低生命值优选敌对玩家
ObjectGuid EnemyPlayerValue::Calculate()
{
    // Prioritize the duel opponent | 优先锁定决斗对手
    if(bot->duel && bot->duel->opponent && !sServerFacade.IsFriendlyTo(bot->duel->opponent, bot))
    {
        return bot->duel->opponent->GetObjectGuid();
    }

    Unit* bestEnemyPlayer = nullptr;
    std::list<ObjectGuid> enemyPlayers = AI_VALUE(std::list<ObjectGuid>, "enemy player targets");
    if (!enemyPlayers.empty())
    {
        const bool isMelee = !ai->IsRanged(bot);
        uint32 bestEnemyPlayerHealth = std::numeric_limits<uint32>::max();
        float bestEnemyPlayerDistance = std::numeric_limits<float>::max();
      
        // Use the first enemy player as a base | 以首个敌对玩家作为初始比较基准
        Unit* firstTarget = ai->GetUnit(enemyPlayers.front());
        if (firstTarget)
        {
            bestEnemyPlayerDistance = firstTarget->GetDistance(bot, true);
            bestEnemyPlayerHealth = firstTarget->GetHealth();
            bestEnemyPlayer = firstTarget;
        }

        for (const ObjectGuid& targetGuid : enemyPlayers)
        {
            Unit* target = ai->GetUnit(targetGuid);
            if (target)
            {
                // Prioritize an enemy player if it has a battleground flag | 若敌对玩家携带战场旗帜则最高优先集火
                if ((bot->GetTeam() == HORDE && target->HasAura(23333)) ||
                    (bot->GetTeam() == ALLIANCE && target->HasAura(23335)))
                {
                    bestEnemyPlayer = target;
                    break;
                }

                if (isMelee)
                {
                    // Score best enemy player based on lowest distance | 根据最近距离筛选最优敌对玩家
                    const float distanceToEnemyPlayer = target->GetDistance(bot, true);
                    if (distanceToEnemyPlayer < bestEnemyPlayerDistance)
                    {
                        bestEnemyPlayerDistance = distanceToEnemyPlayer;
                        bestEnemyPlayer = target;
                    }
                }
                else
                {
                    // Score best enemy player based on lowest health | 根据最低生命值筛选最优敌对玩家
                    const uint32 enemyPlayerHealth = target->GetHealth();
                    if (enemyPlayerHealth < bestEnemyPlayerHealth)
                    {
                        bestEnemyPlayerHealth = enemyPlayerHealth;
                        bestEnemyPlayer = target;
                    }
                }
            }
        }
    }

    return bestEnemyPlayer ? bestEnemyPlayer->GetObjectGuid() : ObjectGuid();
}


// 根据地图类型及战斗/非战斗状态返回追击敌对玩家的最大距离
float EnemyPlayerValue::GetMaxAttackDistance(Player* bot)
{
    if (!bot->GetBattleGround())
        return 60.0f;

    if (bot->InBattleGround())
    {
        BattleGround* bg = bot->GetBattleGround();
        if (!bg)
            return 40.0f;

        BattleGroundTypeId bgType = bg->GetTypeId();

#ifdef MANGOSBOT_TWO
        if (bgType == BATTLEGROUND_RB)
            bgType = bg->GetTypeId(true);

        if (bgType == BATTLEGROUND_IC)
        {
            if (bot->GetPlayerbotAI()->IsInVehicle(false, true))
                return 120.0f;
        }
#endif
        if (bgType == BATTLEGROUND_AV)
        {
            bool strifeTime = bg->GetStartTime() < (uint32)(20 * MINUTE * IN_MILLISECONDS);
            return strifeTime ? 40.0f : 10.0f;
        }
    }

    return 40.0f;
}
