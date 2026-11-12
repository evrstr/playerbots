// 策略值实现：LineTargetValue（纵队链式跟随目标查找）

#include "playerbot/playerbot.h"
#include "LineTargetValue.h"

#include "playerbot/ServerFacade.h"
using namespace ai;

// 遍历小队成员，返回队伍名单中位于自身前一位的存活队员 GUID（首位则跟随主控）
ObjectGuid LineTargetValue::Calculate()
{
    Player* master = GetMaster();
    if (!master)
        return ObjectGuid();

    Group* group = master->GetGroup();
    if (!group)
        return ObjectGuid();

    Player *prev = master;
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *player = sObjectMgr.GetPlayer(itr->guid);
        if( !player || !sServerFacade.IsAlive(player) || player == master)
            continue;

        if (player == bot)
            return prev ? prev->GetObjectGuid() : ObjectGuid();

        prev = player;
    }

    return master ? master->GetObjectGuid() : ObjectGuid();
}

