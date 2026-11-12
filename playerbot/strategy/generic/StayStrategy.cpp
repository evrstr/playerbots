/// 原地停留（Stay）与坐下休息（Sit）策略实现

#include "playerbot/playerbot.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "StayStrategy.h"

using namespace ai;

/// 获取非战斗默认动作：原地站定停留
NextAction** StayStrategy::GetDefaultNonCombatActions()
{
    return NextAction::array(0, new NextAction("stay", 1.0f), NULL);
}

/// 获取战斗默认动作：复用原地停留动作
ai::NextAction** StayStrategy::GetDefaultCombatActions()
{
    return GetDefaultNonCombatActions();
}

/// 启用停留策略时立即打断当前非静止移动
void StayStrategy::OnStrategyAdded(BotState state)
{
    if (state == ai->GetState() && ai->GetBot()->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE)
    {
        ai->StopMoving();
    }
}

/// 初始化非战斗触发器：偏离停留坐标时返回指定停留点
void StayStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "return to stay position",
        NextAction::array(0, new NextAction("return to stay position", 1.5f), NULL)));
}

/// 初始化战斗触发器：战斗中同样维持停留归位检测
void StayStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    InitNonCombatTriggers(triggers);
}

/// 初始化坐下策略非战斗触发器：静止一段时间后坐下休息
void SitStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "sit",
        NextAction::array(0, new NextAction("sit", 1.5f), NULL)));
}
