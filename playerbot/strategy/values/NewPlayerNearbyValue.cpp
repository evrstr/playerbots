// 策略值实现：NewPlayerNearbyValue（查找首次遇到的友方玩家）

#include "playerbot/playerbot.h"
#include "NewPlayerNearbyValue.h"

using namespace ai;

// 遍历附近友方玩家列表，返回首个不在 already seen players 集合中的玩家 GUID
ObjectGuid NewPlayerNearbyValue::Calculate()
{
    std::list<ObjectGuid> players = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid> >("nearest friendly players")->Get();
    std::set<ObjectGuid>& alreadySeenPlayers = ai->GetAiObjectContext()->GetValue<std::set<ObjectGuid>& >("already seen players")->Get();
    for (std::list<ObjectGuid>::iterator i = players.begin(); i != players.end(); ++i)
    {
        ObjectGuid guid = *i;
        if (alreadySeenPlayers.find(guid) == alreadySeenPlayers.end())
            return guid;
    }

    return ObjectGuid();
}
