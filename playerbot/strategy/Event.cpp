
#include "playerbot/playerbot.h"
#include "Entities/Player.h"
#include "Event.h"


using namespace ai;

// 从事件携带的网络数据包中读取首个 ObjectGuid
ObjectGuid Event::getObject()
{
    if (packet.empty())
        return ObjectGuid();

    WorldPacket p(packet);
    p.rpos(0);
    
    ObjectGuid guid;
    p >> guid;

    return guid;
}
