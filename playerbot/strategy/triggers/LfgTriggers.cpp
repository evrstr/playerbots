/// 地下城查找器（LFG）触发器实现

#include "playerbot/playerbot.h"
#include "LfgTriggers.h"

using namespace ai;

/// 检测是否存在待确认的 LFG 组队邀请
bool LfgProposalActiveTrigger::IsActive()
{
    return AI_VALUE(uint32, "lfg proposal");
}

/// 检测机器人是否与主人位于同一未知地下城地图中
bool UnknownDungeonTrigger::IsActive()
{
    return ai->HasActivePlayerMaster() &&
        ai->GetMaster() &&
        ai->GetMaster()->IsInWorld() &&
        ai->GetMaster()->GetMap()->IsDungeon() &&
        bot->GetMapId() == ai->GetMaster()->GetMapId();
}
