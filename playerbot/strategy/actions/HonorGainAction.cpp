
#include "playerbot/playerbot.h"
#include "HonorGainAction.h"



using namespace ai;

/// 执行动作主逻辑（荣誉击杀处理动作）
bool HonorGainAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    // 解析事件携带的网络封包数据
    WorldPacket p(event.getPacket()); // (4+8+4)
    uint32 honorPointsGain;
    ObjectGuid guid;
    uint32 victimRank;

    p.rpos(0);
    p >> honorPointsGain;      // gained honor (can be gain or decrease...) (获得的荣誉值（可正可负）)
    p >> guid;    // ObjectGuid of victim (victim can be yourself, in which case it is 0)
    p >> victimRank;      // 0-19 (will be 0 if you are the victim or if you killed an NPC that is not leader of the race, race leader is 19) (0-19（若自身为受害者或击杀非种族领袖 NPC 则为 0，种族领袖为 19）)

    // no idea how to make this any better (暂保持当前实现)
    // actual signed value (实际有符号数值)
    int honorPointsActual = honorPointsGain < std::numeric_limits<uint32>::max() / 2 ? honorPointsGain : (std::numeric_limits<uint32>::max() - honorPointsGain) * -1;

    ai->TellDebug(requester, "Gained " + std::to_string(honorPointsActual) + " honor points", "debug xp");

    //if the bot killed somebody
    if (guid)
    {
        // honorable kill basically (either player or NPC) (荣誉击杀（玩家或荣誉 NPC）)
        if (honorPointsActual > 0)
        {
            // decrease death count by 1 to keep on rocking if the bot can (若机器人可继续作战则将死亡计数减 1)
            if (uint32 currentDeathCount = AI_VALUE(uint32, "death count"))
            {
                SET_AI_VALUE(uint32, "death count", currentDeathCount - 1);
            }
        }

        Creature* creature = ai->GetCreature(guid);
        Player* player = sObjectMgr.GetPlayer(guid);

        if (player)
        {
            if (!bot->InBattleGround()
#ifndef MANGOSBOT_ZERO
                && !bot->InArena()
#endif
                )
            {
                BroadcastHelper::BroadcastPlayerKill(ai, bot, player);
            }
        }
        else if (creature)
        {
            // TODO broadcast honorable NPC kills (待办：播报击杀荣誉 NPC 事件)
        }

        return false;
    }

    //if the bot is the victim


    return false;
}
