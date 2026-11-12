
#include "playerbot/playerbot.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/values/LastMovementValue.h"
#include "CombatActions.h"

using namespace ai;

/// 判断当前状态下该动作是否可用/有效（切换近战策略动作）
bool SwitchToMeleeAction::isUseful()
{
    return ai->HasStrategy("ranged", BotState::BOT_STATE_COMBAT);
}

/// 执行动作主逻辑（切换近战策略动作）
bool SwitchToMeleeAction::Execute(Event &event)
{
    if (Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target")))
    {
        bot->MeleeAttackStart(target);
        return ChangeCombatStrategyAction::Execute(event);
    }
    return false;
}

/// 判断当前状态下该动作是否可用/有效（切换远程策略动作）
bool SwitchToRangedAction::isUseful()
{

    return ai->HasStrategy("close", BotState::BOT_STATE_COMBAT);
}

/// 执行动作主逻辑（切换远程策略动作）
bool SwitchToRangedAction::Execute(Event &event)
{
    if (Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target")))
    {
        bot->MeleeAttackStop(target);
        return ChangeCombatStrategyAction::Execute(event);
    }
    return false;
}
