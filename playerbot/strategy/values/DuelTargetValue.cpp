// 策略值实现：DuelTargetValue（获取决斗对手）

#include "playerbot/playerbot.h"
#include "DuelTargetValue.h"

using namespace ai;

// 若处于决斗状态，返回决斗对手玩家的 GUID
ObjectGuid DuelTargetValue::Calculate()
{
    if (bot->duel)
    {
        Player* player = bot->duel->opponent;
        if (player) return player->GetObjectGuid();
    }
    
    return ObjectGuid();
}
