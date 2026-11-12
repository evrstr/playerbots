
#include "playerbot/playerbot.h"
#include "ChatShortcutActions.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "playerbot/strategy/values/Formations.h"

using namespace ai;

/// 重置指定的策略坐标锚点
void ReturnPositionResetAction::ResetPosition(std::string posName)
{
    ai::PositionMap& posMap = context->GetValue<ai::PositionMap&>("position")->Get();
    ai::PositionEntry pos = posMap[posName];
    pos.Reset();
    posMap[posName] = pos;
}

/// 保存当前或指定坐标到命名位置记录
void ReturnPositionResetAction::SetPosition(WorldPosition wPos, std::string posName)
{
    ai::PositionMap& posMap = context->GetValue<ai::PositionMap&>("position")->Get();
    ai::PositionEntry pos = posMap[posName];
    pos.Set(wPos);
    posMap[posName] = pos;
}

/// 输出指定状态下的已启用策略列表
void ReturnPositionResetAction::PrintStrategies(PlayerbotAI* ai, Event& event)
{
    if (event.getParam() == "?")
    {
        Player* requester = event.getOwner() ? event.getOwner() : ai->GetMaster();
        ai->PrintStrategies(requester, BotState::BOT_STATE_ALL);
    }
}

/// 执行动作主逻辑（跟随指令快捷动作）
bool FollowChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+follow,-passive,-stay,-wander,", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-stay,-guard,-wander", BotState::BOT_STATE_COMBAT);

    if(ai->HasStrategy("passive", BotState::BOT_STATE_COMBAT)) // Remove flee (移除逃跑/撤退状态)
        ai->ChangeStrategy("-passive,-follow", BotState::BOT_STATE_COMBAT);

    ai::PositionMap& posMap = context->GetValue<ai::PositionMap&>("position")->Get();
    ai::PositionEntry pos = posMap["return"];
    pos.Reset();
    posMap["return"] = pos;

    /// 输出指定状态下的已启用策略列表
    ReturnPositionResetAction::PrintStrategies(ai, event);

    Formation* formation = AI_VALUE(Formation*, "formation");
    MEM_AI_VALUE(WorldPosition, "master position")->Reset();

    if (formation->getName() == "custom") // If in custom formation set relative position to current position. (若处于自定义阵型模式，则将相对位置设为当前位置。)
    {
        ai::PositionEntry pos = posMap["follow"];

        WorldPosition relPos(bot);

        if (!ai->IsSafe(requester) || sServerFacade.GetDistance2d(bot, requester) > sPlayerbotAIConfig.reactDistance) // Use default formation location. (使用默认队伍阵型站位。)
        {
            relPos = WorldPosition(bot->GetMapId(), cos(GetFollowAngle()) * ai->GetRange("follow"), sin(GetFollowAngle()) * ai->GetRange("follow"), 0);
        }
        else // Use relative location. (使用相对偏移坐标。)
        {
            relPos -= WorldPosition(ai->GetMaster());
            relPos.rotateXY(-1 * ai->GetMaster()->GetOrientation());
        }

        pos.Set(relPos.getX(), relPos.getY(), relPos.getZ(), relPos.getMapId());
        posMap["follow"] = pos;
    }

    if (sServerFacade.IsInCombat(bot))
    {     
        WorldLocation loc = formation->GetLocation();
        if (Formation::IsNullLocation(loc) || loc.mapid == -1)
            return false;

        if (MoveTo(loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, false, false))
        {
            ai->TellPlayerNoFacing(requester, BOT_TEXT("following"));
            return true;
        }
    }

    ai->TellPlayerNoFacing(requester, BOT_TEXT("following"));
    return true;
}

/// 执行动作主逻辑（原地待命指令快捷动作）
bool StayChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+stay,-follow,-wander,-passive", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+stay,-follow,-wander,-passive", BotState::BOT_STATE_COMBAT);

    SetPosition(bot);
    SetPosition(bot, "stay");
    MEM_AI_VALUE(WorldPosition, "master position")->Reset();

    PrintStrategies(ai, event);

    ai->TellPlayerNoFacing(requester, BOT_TEXT("staying"));
    return true;
}

/// 执行动作主逻辑（警戒守卫指令快捷动作）
bool GuardChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+guard,-follow,-wander,-passive", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+guard,-follow,-wander,-passive", BotState::BOT_STATE_COMBAT);

    SetPosition(bot);
    SetPosition(bot, "guard");
    MEM_AI_VALUE(WorldPosition, "master position")->Reset();  

    PrintStrategies(ai, event);

    ai->TellPlayerNoFacing(requester, BOT_TEXT("guarding"));
    return true;
}

/// 执行动作主逻辑（自由活动指令快捷动作）
bool FreeChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+free,-passive", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+free,-passive", BotState::BOT_STATE_COMBAT);

    PrintStrategies(ai, event);

    ai->TellPlayerNoFacing(requester, BOT_TEXT("free_moving"));
    return true;
}

/// 执行动作主逻辑（漫步游荡指令快捷动作）
bool WanderChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+wander,-follow,-guard,-stay,-passive", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-follow,-guard,-stay,-passive", BotState::BOT_STATE_COMBAT);

    PrintStrategies(ai, event);

    ai->TellPlayerNoFacing(requester, BOT_TEXT("wandering"));
    return true;
}

/// 执行动作主逻辑（撤退指令快捷动作）
bool FleeChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    std::string movement = ai->GetDefaultMovementStrategy();
    ai->ChangeStrategy("+" + movement + ",+passive", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+" + movement + ",+passive", BotState::BOT_STATE_COMBAT);
    ResetPosition();

    PrintStrategies(ai, event);

    if (bot->GetMapId() != requester->GetMapId() || sServerFacade.GetDistance2d(bot, requester) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellPlayerNoFacing(requester, BOT_TEXT("fleeing_far"));
        return true;
    }
    ai->TellPlayerNoFacing(requester, BOT_TEXT("fleeing"));
    return true;
}

/// 执行动作主逻辑（解散/避开指令快捷动作）
bool GoawayChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+runaway", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+runaway", BotState::BOT_STATE_COMBAT);
    ResetPosition();

    PrintStrategies(ai, event);

    ai->TellPlayerNoFacing(requester, "Running away");
    return true;
}

/// 执行动作主逻辑（刷怪指令快捷动作）
bool GrindChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+grind,-passive", BotState::BOT_STATE_NON_COMBAT);
    ResetPosition();
    ai->TellPlayerNoFacing(requester, BOT_TEXT("grinding"));
    return true;
}

/// 执行动作主逻辑（坦克开怪指令快捷动作）
bool TankAttackChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    if (!ai->IsTank(bot))
        return false;

    ai->Reset();
    ai->ChangeStrategy("-passive", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-passive", BotState::BOT_STATE_COMBAT);
    ResetPosition();
    ai->TellPlayerNoFacing(requester, BOT_TEXT("attacking"));
    return true;
}

/// 执行动作主逻辑（全力输出指令快捷动作）
bool MaxDpsChatShortcutAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    if (!ai->ContainsStrategy(STRATEGY_TYPE_DPS))
        return false;

    ai->Reset();
    ai->ChangeStrategy("-threat,-conserve mana,-cast time,+dps debuff,+boost", BotState::BOT_STATE_COMBAT);
    ai->TellPlayerNoFacing(requester, "Max DPS!");
    return true;
}
