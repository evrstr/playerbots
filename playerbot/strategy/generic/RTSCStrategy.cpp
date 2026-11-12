/// RTSC（即时战略群体控制）跳跃策略实现

#include "playerbot/playerbot.h"
#include "RTSCStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：存在 RTSC 保存跳跃点时执行定向跳跃
void RTSCSJumptrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rtsc jump active",
        NextAction::array(0, new NextAction("jump::rtsc", ACTION_MOVE), NULL)));
}
