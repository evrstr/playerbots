/// 拉怪（Pull）策略触发器实现

#include "playerbot/playerbot.h"
#include "playerbot/strategy/Action.h"
#include "playerbot/strategy/generic/PullStrategy.h"
#include "PullTriggers.h"
#include "playerbot/strategy/values/PositionValue.h"

using namespace ai;

/// 检测拉怪策略是否处于待开始状态
bool PullStartTrigger::IsActive()
{
    const PullStrategy* strategy = PullStrategy::Get(ai);
    return strategy && strategy->IsPullPendingToStart();
}

/// 检测拉怪过程是否结束（超时、目标进入近战/施法距离或到达预设拉怪点）
bool PullEndTrigger::IsActive()
{
    const PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy && strategy->HasPullStarted())
    {
        Unit* target = strategy->GetTarget();
        if (target)
        {
            // Check if the pull is taking too long | 检查拉怪耗时是否过长
            const time_t secondsSincePullStarted = time(0) - strategy->GetPullStartTime();
            if (secondsSincePullStarted >= strategy->GetMaxPullTime())
            {
                return true;
            }
            else
            {
                float distanceToPullTarget = target->GetDistance(ai->GetBot());
                // sometimes creatures can reach slightly more than normal attack distance | 有时生物的攻击判定距离略大于常规近战范围
                float creatureMeleeRange = ATTACK_DISTANCE + BASE_MELEERANGE_OFFSET + 1;

                if (distanceToPullTarget <= creatureMeleeRange || (target->IsNonMeleeSpellCasted(true) && target->IsInCombat()) || (secondsSincePullStarted >= 10 && target->GetTarget() != bot) || (ai->IsRanged(bot) && distanceToPullTarget <= ai->GetRange("spell")))
                {
                    if (ai->HasStrategy("pull back", BotState::BOT_STATE_COMBAT))
                    {
                        PositionMap& posMap = AI_VALUE(PositionMap&, "position");
                        PositionEntry pullPosition = posMap["pull"];
                        if (pullPosition.isSet())
                        {
                            distanceToPullTarget = bot->GetDistance(pullPosition.x, pullPosition.y, pullPosition.z);
                            return distanceToPullTarget <= ai->GetRange("follow");
                        }
                    }

                    // Check if the pulled target has approached the bot | 检查被拉目标是否已接近机器人
                    return true;
                }
            }
        }
    }

    return false;
}
