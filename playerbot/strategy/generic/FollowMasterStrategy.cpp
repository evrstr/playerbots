/// 跟随主人与自由移动策略实现

#include "playerbot/playerbot.h"
#include "FollowMasterStrategy.h"

using namespace ai;

/// 初始化非战斗跟随触发器：超出自由范围或需要调整队形时执行跟随
void FollowMasterStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "out of free move range",
        NextAction::array(0, new NextAction("check mount state", ACTION_HIGH), new NextAction("follow", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "update follow",
        NextAction::array(0, new NextAction("follow", ACTION_IDLE), NULL)));
}

/// 初始化战斗跟随触发器
void FollowMasterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    InitNonCombatTriggers(triggers);
}

/// 初始化死亡跟随触发器
void FollowMasterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    InitNonCombatTriggers(triggers);
}

/// 初始化反应跟随触发器：条件变化时停止跟随
void FollowMasterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "stop follow",
        NextAction::array(0, new NextAction("stop follow", ACTION_PASSTROUGH), NULL)));
}

/// 策略添加回调：同步在反应状态中启用跟随策略
void FollowMasterStrategy::OnStrategyAdded(BotState state)
{
    if (state != BotState::BOT_STATE_REACTION)
    {
        ai->ChangeStrategy("+" + getName(), BotState::BOT_STATE_REACTION);
    }
}

/// 策略移除回调：停止当前跟随移动并在所有状态均无跟随时移除反应状态跟随
void FollowMasterStrategy::OnStrategyRemoved(BotState state)
{
    if (state == ai->GetState() && ai->GetBot()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FOLLOW_MOTION_TYPE)
    {
        ai->StopMoving();
    }

    if (state == BotState::BOT_STATE_REACTION)
        return;

    bool hasFollow = false;

    for (uint8 checkState = (uint8)BotState::BOT_STATE_COMBAT; checkState < (uint8)BotState::BOT_STATE_REACTION; checkState++)
    {
        if (ai->HasStrategy(getName(), BotState(checkState)))
        {
            hasFollow = true;
            break;
        }
    }

    if (!hasFollow)
    {
        ai->ChangeStrategy("-" + getName(), BotState::BOT_STATE_REACTION);
    }
}
