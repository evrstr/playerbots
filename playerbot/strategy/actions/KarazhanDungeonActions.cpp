
#include "playerbot/playerbot.h"
#include "KarazhanDungeonActions.h"
#include "playerbot/strategy/generic/KarazhanDungeonStrategies.h"
#include "playerbot/strategy/Action.h"

using namespace ai;

/// 执行动作主逻辑（清除虚空幽龙门射线状态动作）
bool RemoveNetherPortalBuffsFromNetherspiteAction::Execute(Event& event)
{
    NetherspiteFightStrategy* strategy = NetherspiteFightStrategy::Get(ai);
    if (strategy)
    {
        Unit* target = ai->GetUnit(strategy->GetBossGuid());
        if (target && ai->HasAura(30466, target))
            target->RemoveAurasDueToSpell(30466);

        if (target && ai->HasAura(30467, target))
            target->RemoveAurasDueToSpell(30467);

        if (target && ai->HasAura(30468, target))
            target->RemoveAurasDueToSpell(30468);
    }


    return true;
}

/// 执行动作主逻辑（埃兰之影烈焰花环阶段开始动作）
bool ShadeOfAranFirePhaseStartedAction::Execute(Event& event)
{
    ShadeOfAranFightStrategy* aranStrategy = ShadeOfAranFightStrategy::Get(ai);
    if (aranStrategy && aranStrategy->GetPhase() != AranPhase::PHASE_FIRE)
    {
        aranStrategy->SetPhase(AranPhase::PHASE_FIRE);
        Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
        ai->Reset();
        ai->ChangeStrategy("+stay", BotState::BOT_STATE_COMBAT);
        if (aranStrategy->GetRangedBot())
        {
            ai->ChangeStrategy("+ranged,-close", BotState::BOT_STATE_COMBAT);
        }
        ai->TellPlayerNoFacing(requester, "Fire phase", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }
    else
        return false;
}

/// 执行动作主逻辑（埃兰之影暴风雪阶段开始动作）
bool ShadeOfAranFrostPhaseStartedAction::Execute(Event& event)
{
    ShadeOfAranFightStrategy* aranStrategy = ShadeOfAranFightStrategy::Get(ai);
    if (aranStrategy && aranStrategy->GetPhase() != AranPhase::PHASE_FROST)
    {
        aranStrategy->SetPhase(AranPhase::PHASE_FROST);
        Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
        ai->Reset();
        ai->ChangeStrategy("-stay", BotState::BOT_STATE_COMBAT);
        if (aranStrategy->GetRangedBot())
        {
            ai->ChangeStrategy("-ranged,+close", BotState::BOT_STATE_COMBAT);
        }
        ai->TellPlayerNoFacing(requester, "Blizzard phase", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }
    else
        return false;
}

/// 执行动作主逻辑（埃兰之影奥术阶段开始动作）
bool ShadeOfAranArcanePhaseStartedAction::Execute(Event& event)
{
    ShadeOfAranFightStrategy* aranStrategy = ShadeOfAranFightStrategy::Get(ai);
    if (aranStrategy && aranStrategy->GetPhase() != AranPhase::PHASE_ARCANE)
    {
        aranStrategy->SetPhase(AranPhase::PHASE_ARCANE);
        Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
        ai->Reset();
        ai->ChangeStrategy("-stay", BotState::BOT_STATE_COMBAT);
        if (aranStrategy->GetRangedBot())
        {
            ai->ChangeStrategy("+ranged,-close", BotState::BOT_STATE_COMBAT);
        }
        ai->TellPlayerNoFacing(requester, "Arcane phase", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }
    else
        return false;
}

/// 执行动作主逻辑（埃兰之影奥术阶段结束动作）
bool ShadeOfAranArcanePhaseEndedAction::Execute(Event& event)
{
    ShadeOfAranFightStrategy* aranStrategy = ShadeOfAranFightStrategy::Get(ai);
    if (aranStrategy && aranStrategy->GetPhase() == AranPhase::PHASE_ARCANE)
    {
        aranStrategy->SetPhase(AranPhase::PHASE_NONE);
        Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
        ai->Reset();
        ai->ChangeStrategy("-stay", BotState::BOT_STATE_COMBAT);
        if (aranStrategy->GetRangedBot())
        {
            ai->ChangeStrategy("+ranged,-close", BotState::BOT_STATE_COMBAT);
        }
        ai->TellPlayerNoFacing(requester, "Arcane phase ended", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }
    else
        return false;
}

/// 执行动作主逻辑（埃兰之影水元素应对动作）
bool ShadeOfAranElementalsAction::Execute(Event& event)
{
    ShadeOfAranFightStrategy* aranStrategy = ShadeOfAranFightStrategy::Get(ai);
    if (aranStrategy && !aranStrategy->GetElementals())
    {
        aranStrategy->SetElementals(true);
        Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
        ai->Reset();
        SET_AI_VALUE2(float,"range", "flee", 4.0f);
        if (aranStrategy->GetPhase() != AranPhase::PHASE_FIRE)
            ai->ChangeStrategy("-stay", BotState::BOT_STATE_COMBAT);
        if (aranStrategy->GetRangedBot())
        {
            ai->ChangeStrategy("+ranged,-close", BotState::BOT_STATE_COMBAT);
        }
        ai->TellPlayerNoFacing(requester, "Elementals are out", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }
    else
        return false;
}

/// 执行动作主逻辑（远离玛克扎尔地狱火动作）
bool NetherspiteInfernalMoveAwayAction::Execute(Event& event)
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (target && target->GetEntry() == 15690)
    {
        Unit* tot = target->GetVictim();
        if (tot && tot == bot)
        {
            healersSafe = false;
        }
    }

    return MoveAwayFromCreature::Execute(event);
}
