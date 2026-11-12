#pragma once

/// 机器人行为状态枚举（战斗、非战斗、死亡、反应、全状态）
enum class BotState : uint8
{
    BOT_STATE_COMBAT = 0,
    BOT_STATE_NON_COMBAT = 1,
    BOT_STATE_DEAD = 2,
    BOT_STATE_REACTION = 3,
    BOT_STATE_ALL
};
