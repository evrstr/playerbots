
#include "playerbot/playerbot.h"
#include "BotStateActions.h"
#include "playerbot/strategy/values/PositionValue.h"

using namespace ai;

/// 执行动作主逻辑（设置战斗状态动作）
bool SetCombatStateAction::Execute(Event& event)
{
    SetDuration(sPlayerbotAIConfig.reactDelay);
    ai->OnCombatStarted();
    return true;
}

/// 执行动作主逻辑（设置非战斗状态动作）
bool SetNonCombatStateAction::Execute(Event& event)
{
    SetDuration(sPlayerbotAIConfig.reactDelay);
    if (ai->IsStateActive(BotState::BOT_STATE_DEAD))
    {
        ai->OnResurrected();
    }
    else
    {
        ai->OnCombatEnded();
    }

    return true;
}

/// 执行动作主逻辑（设置死亡状态动作）
bool SetDeadStateAction::Execute(Event& event)
{
    SetDuration(sPlayerbotAIConfig.reactDelay);
    ai->OnDeath();
    return true;
}
