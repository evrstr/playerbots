/// 机器人状态切换触发器实现（进战/脱战/死亡/复活）

#include "playerbot/playerbot.h"
#include "playerbot/ServerFacade.h"
#include "BotStateTriggers.h"

using namespace ai;

/// 检测是否应进入战斗状态（非战斗/非死亡且附近队友或自身受袭）
bool CombatStartTrigger::IsActive()
{
    if (!ai->IsStateActive(BotState::BOT_STATE_COMBAT) && !ai->IsStateActive(BotState::BOT_STATE_DEAD))
    {
        // Check if any member of the group (near this bot) is getting attacked | 检查附近是否有任何队伍成员正在遭受攻击
        return AI_VALUE(bool, "has attackers");
    }

    return false;
}

/// 检测是否应脱离战斗状态（当前处于战斗状态且无附近攻击者）
bool CombatEndTrigger::IsActive()
{
    // Check if the bot is currently in combat | 检查机器人当前是否处于战斗状态
    if (ai->IsStateActive(BotState::BOT_STATE_COMBAT))
    {
        // Check if any member of the group (near this bot) is getting attacked | 检查附近是否有任何队伍成员正在遭受攻击
        return !AI_VALUE(bool, "has attackers");
    }

    return false;
}

/// 检测是否触发死亡状态（当前未标记死亡且角色实际已死亡）
bool DeathTrigger::IsActive()
{
    return !ai->IsStateActive(BotState::BOT_STATE_DEAD) && !sServerFacade.IsAlive(bot);
}

/// 检测是否触发复活状态（当前标记死亡且角色已存活）
bool ResurrectTrigger::IsActive()
{
    return ai->IsStateActive(BotState::BOT_STATE_DEAD) && sServerFacade.IsAlive(bot);
}