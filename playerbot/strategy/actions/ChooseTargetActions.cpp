#include "playerbot/strategy/Action.h"
#include "ChooseTargetActions.h"
#include "MotionGenerators/MovementGenerator.h"
#include "AI/BaseAI/CreatureAI.h"
#include "playerbot/TravelMgr.h"
#include "playerbot/strategy/generic/PullStrategy.h"
#include "playerbot/strategy/values/FreeMoveValues.h"

/// 判断当前状态下该动作是否可用/有效（输出集火协助动作）
bool DpsAssistAction::isUseful()
{
    // if carry flag, do not start fight
    if (bot->HasAura(23333) || bot->HasAura(23335) || bot->HasAura(34976))
        return false;

    return true;
}

/// 判断当前状态下该动作是否可用/有效（攻击任意敌对目标动作）
bool AttackAnythingAction::isUseful() 
{
    if (!ai->AllowActivity(GRIND_ACTIVITY)) // Bot not allowed to be active (机器人当前不被允许处于活跃状态)
        return false;

    if (!AI_VALUE(bool, "can move around"))
        return false;

    Unit* target = GetTarget();

    if (!target || !ai->IsSafe(target))
        return false;

    bool pinnedByOrder = ai->HasStrategy("stay", BotState::BOT_STATE_NON_COMBAT) || ai->HasStrategy("guard", BotState::BOT_STATE_NON_COMBAT);
    if (pinnedByOrder && target->GetDistance(bot) >= ai->GetRange("spell"))
        return false;

    if (ai->ContainsStrategy(STRATEGY_TYPE_HEAL) && !ai->HasStrategy("offdps", BotState::BOT_STATE_COMBAT))
        return false;

    if(!target->IsPlayer() && bot->isInFront(target,target->GetAttackDistance(bot)*1.5f, M_PI_F*0.5f) && target->CanAttackOnSight(bot) && target->GetLevel() < bot->GetLevel() + 3.0) // Attack before being attacked. (先发制人主动攻击。)
        return true;

    if (AI_VALUE(bool, "travel target traveling") && CanFreeMoveValue::CanFreeMoveTo(ai, *AI_VALUE(TravelTarget*,"travel target")->GetPosition()) &&
        sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "travel target"), sPlayerbotAIConfig.sightDistance)) 
        return false;

    return true;
}

/// 判断执行该动作的前置条件是否满足（攻击任意敌对目标动作）
bool ai::AttackAnythingAction::isPossible()
{
    return AttackAction::isPossible() && GetTarget();
}

/// 执行动作主逻辑（攻击任意敌对目标动作）
bool ai::AttackAnythingAction::Execute(Event& event)
{
    bool result = AttackAction::Execute(event);
    if (result)
    {
        Unit* grindTarget = GetTarget();
        if (grindTarget)
        {
            std::string grindName = grindTarget->GetName();
            if (!grindName.empty())
            {
                sPlayerbotAIConfig.logEvent(ai, "AttackAnythingAction", grindName, std::to_string(grindTarget->GetEntry()));

                if (ai->HasStrategy("pull", BotState::BOT_STATE_COMBAT))
                {
                    if (PullStrategy* strategy = PullStrategy::Get(ai))
                    {
                        if (strategy->CanDoPullAction(grindTarget) && (ai->GetBot()->getClass() == CLASS_DRUID || ai->GetBot()->getClass() == CLASS_PALADIN || AI_VALUE2(uint32, "item count", "ammo")))
                        {
                            Event pullEvent("attack anything", grindTarget->GetObjectGuid());
                            bool doAction = ai->DoSpecificAction("pull my target", pullEvent, true);

                            if (doAction)
                            {
                                return true;
                            }
                        }
                    }
                }

                context->GetValue<ObjectGuid>("attack target")->Set(grindTarget->GetObjectGuid());
                ai->StopMoving();
            }
        }
    }

    return result;
}

/// 判断当前状态下该动作是否可用/有效（攻击敌对玩家动作）
bool AttackEnemyPlayerAction::isUseful()
{
    return !sPlayerbotAIConfig.IsInPvpProhibitedZone(sServerFacade.GetAreaId(bot));
}

/// 判断当前状态下该动作是否可用/有效（攻击敌方扛旗手动作）
bool AttackEnemyFlagCarrierAction::isUseful()
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    Unit* target = ai->GetUnit(context->GetValue<ObjectGuid>("enemy flag carrier")->Get());
    return target && sServerFacade.IsDistanceLessOrEqualThan(sServerFacade.GetDistance2d(bot, target), 75.0f) && (bot->HasAura(23333) || bot->HasAura(23335) || bot->HasAura(34976));
}

/// 执行动作主逻辑（选择新目标动作）
bool SelectNewTargetAction::Execute(Event& event)
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (target && sServerFacade.UnitIsDead(target))
    {
        // Save the dead target for later looting (记录已死亡目标以便稍后拾取战利品)
        ObjectGuid guid = target->GetObjectGuid();
        if (guid)
        {
            AI_VALUE(LootObjectStack*, "available loot")->Add(guid);
        }
    }

    // Clear the target variables (清除目标相关黑板变量)
    ObjectGuid attackTarget = AI_VALUE(ObjectGuid, "attack target");
    std::list<ObjectGuid> possible = AI_VALUE(std::list<ObjectGuid>, "possible targets no los");
    if (attackTarget && find(possible.begin(), possible.end(), attackTarget) == possible.end())
    {
        SET_AI_VALUE(ObjectGuid, "attack target", ObjectGuid());
    }

    // Save the old target and clear the current target (保存旧目标并清空当前目标)
    if(target)
    {
        SET_AI_VALUE(ObjectGuid, "old target", target->GetObjectGuid());
        SET_AI_VALUE(ObjectGuid, "current target", ObjectGuid());
    }
    
    // Stop attacking (停止攻击)
    bot->SetSelectionGuid(ObjectGuid());
    ai->InterruptSpell();
    bot->AttackStop();
    // Stop pet attacking (命令宠物停止攻击)
    Pet* pet = bot->GetPet();
    if (pet)
    {
        UnitAI* creatureAI = ((Creature*)pet)->AI();
        if (creatureAI)
        {
            // Send pet action packet (发送宠物动作控制封包)
            const ObjectGuid& petGuid = pet->GetObjectGuid();
            const ObjectGuid& targetGuid = ObjectGuid();
            const uint8 flag = ACT_COMMAND;
            const uint32 spellId = COMMAND_FOLLOW;
            const uint32 command = (flag << 24) | spellId;

            WorldPacket data(CMSG_PET_ACTION);
            data << petGuid;
            data << command;
            data << targetGuid;
            bot->GetSession()->HandlePetAction(data);
        }
    }

    bool moreAttackers = false;
    // Check if there is any enemy targets available to attack (检查是否存在任何可攻击的敌对目标)
    if (AI_VALUE(bool, "has attackers"))
    {
        if (ai->HasStrategy("pvp", BotState::BOT_STATE_COMBAT) ||
            ai->HasStrategy("duel", BotState::BOT_STATE_COMBAT))
        {
            // Check if there is an enemy player nearby (检查附近是否存在敌对玩家)
            if (AI_VALUE(bool, "has enemy player targets"))
            {
                moreAttackers = true;
                return ai->DoSpecificAction("attack enemy player", event, true);
            }
        }

        // Let the dps/tank assist pick a target to attack (交由输出/坦克协助策略来挑选攻击目标)
        if (ai->HasStrategy("dps assist", BotState::BOT_STATE_NON_COMBAT))
        {
            moreAttackers = true;
            return ai->DoSpecificAction("dps assist", event, true);
        }
        else if (ai->HasStrategy("tank assist", BotState::BOT_STATE_NON_COMBAT))
        {
            moreAttackers = true;
            return ai->DoSpecificAction("tank assist", event, true);
        }
    }

    return false;
}
