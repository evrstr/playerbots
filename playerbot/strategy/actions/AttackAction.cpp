
#include "playerbot/playerbot.h"
#include "AttackAction.h"
#include "MotionGenerators/MovementGenerator.h"
#include "AI/BaseAI/CreatureAI.h"
#include "playerbot/LootObjectStack.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/generic/CombatStrategy.h"

using namespace ai;

/// 执行动作主逻辑（攻击动作基类）
bool AttackAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    Unit* target = GetTarget();
    if (target && target->IsInWorld() && target->GetMapId() == bot->GetMapId())
    {
        return Attack(requester, target);
    }

    return false;
}

/// 执行动作主逻辑（攻击主人目标动作）
bool AttackMyTargetAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if(requester)
    {
        const ObjectGuid guid = requester->GetSelectionGuid();
        if (guid)
        {
            if (Attack(requester, ai->GetUnit(guid)))
            {
                SET_AI_VALUE(ObjectGuid, "attack target", guid);
                return true;
            }
        }
        else if (verbose)
        {
            ai->TellError(requester, "You have no target");
        }
    }

    return false;
}

/// 执行动作主逻辑（攻击团队标记目标动作）
bool AttackRTITargetAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    Unit* rtiTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "rti target"));

    if (rtiTarget && rtiTarget->IsInWorld() && rtiTarget->GetMapId() == bot->GetMapId())
    {
        if (Attack(requester, rtiTarget))
        {
            SET_AI_VALUE(ObjectGuid, "attack target", rtiTarget->GetObjectGuid());
            return true;
        }
    }
    else
    {
        ai->TellError(requester, "I dont see my rti attack target");
    }

    return false;
}

/// 判断当前状态下该动作是否可用/有效（攻击主人目标动作）
bool AttackMyTargetAction::isUseful()
{
    return !ai->ContainsStrategy(STRATEGY_TYPE_HEAL) || ai->HasStrategy("offdps", BotState::BOT_STATE_COMBAT);
}

/// 判断当前状态下该动作是否可用/有效（攻击团队标记目标动作）
bool AttackRTITargetAction::isUseful()
{
    return !ai->ContainsStrategy(STRATEGY_TYPE_HEAL) || ai->HasStrategy("offdps", BotState::BOT_STATE_COMBAT);
}

/// 启动或切换至指定目标的近战/远程攻击流程
bool AttackAction::Attack(Player* requester, Unit* target)
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm.GetCurrentMovementGeneratorType() == TAXI_MOTION_TYPE || (bot->IsFlying() && WorldPosition(bot).currentHeight() > 10.0f))
    {
        if (verbose)
        {
            ai->TellPlayerNoFacing(requester, "I cannot attack in flight");
        }

        return false;
    }

    if (IsTargetValid(requester, target))
    {
        if (bot->IsMounted() && (sServerFacade.GetDistance2d(bot, target) < 40.0f || bot->IsFlying()))
        {
            ai->Unmount();
            
            if (bot->IsFlying())
            {
                return true;
            }
        }

        ObjectGuid guid = target->GetObjectGuid();
        bot->SetSelectionGuid(target->GetObjectGuid());

        Unit* oldTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
        if(oldTarget)
        {
            SET_AI_VALUE(ObjectGuid, "old target", oldTarget->GetObjectGuid());
        }

        SET_AI_VALUE(ObjectGuid, "current target", target->GetObjectGuid());
        AI_VALUE(LootObjectStack*, "available loot")->Add(guid);

        WaitForAttackStrategy* strategy = WaitForAttackStrategy::Get(ai);
        bool isWaitingForAttack = false;
        Pet* pet = bot->GetPet();
        if (strategy)
        {
            isWaitingForAttack = strategy->ShouldWait(ai);
            if (pet)
            {
                UnitAI* creatureAI = ((Creature*)pet)->AI();
                if (creatureAI)
                {
                    // Don't send the pet to attack if the bot is waiting for attack (机器人等待开怪期间不要派宠物提前攻击)
                    if (!isWaitingForAttack && (!ai->HasStrategy("stay", BotState::BOT_STATE_COMBAT) || AI_VALUE2(float, "distance", "current target") < ai->GetRange("spell")))
                    {
                        // Reset the pet state if no master (若无主人则重置宠物状态)
                        if (creatureAI->GetReactState() == REACT_PASSIVE && !ai->GetMaster())
                            creatureAI->SetReactState(REACT_DEFENSIVE);
                        else 
                            PetAttack(requester, target);
                    }
                    else
                    {
                        if (!isWaitingForAttack)
                            PetAttack(requester, target);
                        else
                        {
                            strategy->SetPetReactState(creatureAI->GetReactState() != REACT_PASSIVE ? creatureAI->GetReactState() : REACT_PASSIVE);
                            creatureAI->SetReactState(REACT_PASSIVE);

                            // Send pet action packet (发送宠物动作控制封包)
                            const ObjectGuid& petGuid = pet->GetObjectGuid();
                            const uint8 flag = ACT_REACTION;
                            const uint32 spellId = REACT_PASSIVE;
                            const uint32 data = (flag << 24) | spellId;

                            WorldPacket packet(CMSG_PET_ACTION);
                            packet << petGuid;
                            packet << data;
                            packet << uint64(0);
                            bot->GetSession()->HandlePetAction(packet);
                            bot->PetSpellInitialize();
                        }
                    }
                }
            }
        }
        else
            PetAttack(requester, target);

        if (ai->CanMove() && !sServerFacade.IsInFront(bot, target, sPlayerbotAIConfig.sightDistance, CAST_ANGLE_IN_FRONT))
        {
            sServerFacade.SetFacingTo(bot, target);
        }

        bool result = true;

        // Don't attack target if it is waiting for attack or in stealth (若目标正处于等待开怪或潜行状态，暂不发起攻击)
        if (!ai->HasStrategy("stealthed", BotState::BOT_STATE_COMBAT) && !isWaitingForAttack)
        {
            // Don't attack a target that has a high damage shield in melee (不要近战攻击带有高额伤害反射护盾的目标)
            if (!ai->IsRanged(bot) || (sServerFacade.GetDistance2d(bot, target) < 5.0f))
            {
                std::set<Aura*> alreadyDone;
                Unit::AuraList const& vDamageShields = target->GetAurasByType(SPELL_AURA_DAMAGE_SHIELD);
                for (Unit::AuraList::const_iterator i = vDamageShields.begin(); i != vDamageShields.end();)
                {
                    if (alreadyDone.find(*i) == alreadyDone.end())
                    {
                        alreadyDone.insert(*i);
                        uint32 damage = (*i)->GetModifier()->m_amount;

                        // If the damage shield does at least 10% of our max hp on each hit we do, we shouldn't attack (若反伤护盾每次攻击反弹超过自身最大生命值的 10%，则停止攻击)
                        if (damage >= bot->GetMaxHealth() * 0.10f)
                        {
                            bot->AttackStop();
                            return false;
                        }

                        i = vDamageShields.begin();
                    }
                    else
                        ++i;
                }
            }

            ai->PlayAttackEmote(1);
            result = bot->Attack(target, !ai->IsRanged(bot) || (sServerFacade.GetDistance2d(bot, target) < 5.0f));
        }

        if (result)
        {
            // Force change combat state to have a faster reaction time (强制切换至战斗状态以提高反应速度)
            ai->OnCombatStarted();
        }

        return result;
    }

    return false;
}

/// 命令机器人召唤的宠物主动攻击指定目标
bool AttackAction::PetAttack(Player* requester, Unit* target)
{
    // If we're done waiting to attack and there's mobs to cc, we can't use defensive/aggressive (若等待开怪结束且存在需控场怪物，则不能使用防御/主动宠物姿态)
    // because non passive pets will ignore our cc (因为非被动姿态的宠物会攻击并打破我方控场)
    // Therefore, we'll keep passive so we can only attack the current target specifically (因此保持宠物被动姿态，使其仅攻击指定的当前目标)
    // In other words, pet only attacks what owner can attack (换言之，宠物只攻击主人能够攻击的目标)
    Pet* pet = bot->GetPet();
    Unit* ccTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "rti cc target"));
    if (pet && (!ccTarget || (ccTarget && target->GetObjectGuid() != ccTarget->GetObjectGuid())))
    {
        constexpr uint32 PET_IMP = 416;
        constexpr uint32 PHASE_SHIFT = 4511;
        if (!(bot->getClass() == CLASS_WARLOCK &&
            pet->AI() && pet->AI()->HasReactState(REACT_PASSIVE) &&
            pet->GetEntry() == PET_IMP && pet->HasAura(PHASE_SHIFT)))
        {
            // Send pet action packet (发送宠物动作控制封包)
            const ObjectGuid& petGuid = pet->GetObjectGuid();
            const ObjectGuid& targetGuid = target->GetObjectGuid();
            const uint8 flag = ACT_COMMAND;
            const uint32 spellId = COMMAND_ATTACK;
            const uint32 command = (flag << 24) | spellId;

            WorldPacket data(CMSG_PET_ACTION);
            data << petGuid;
            data << command;
            data << targetGuid;
            bot->GetSession()->HandlePetAction(data);
        }

        return true;
    }

    return false;
    
}

/// 检查目标单位是否存活、在视野内且满足攻击/施法合法性
bool AttackAction::IsTargetValid(Player* requester, Unit* target)
{
    if (!target)
    {
        if (verbose) 
        {
            ai->TellPlayerNoFacing(requester, "I have no target");
        }

        return false;
    }
    else if (sServerFacade.IsFriendlyTo(bot, target))
    {
        if (verbose)
        {
            std::ostringstream msg;
            msg << target->GetName();
            msg << " is friendly to me";
            ai->TellPlayerNoFacing(requester, msg.str());
        }

        return false;
    }
    else if (sServerFacade.UnitIsDead(target))
    {
        if (verbose)
        {
            std::ostringstream msg;
            msg << target->GetName();
            msg << " is dead";
            ai->TellPlayerNoFacing(requester, msg.str());
        }

        return false;
    }
    else if (sServerFacade.GetDistance2d(bot, target) > sPlayerbotAIConfig.sightDistance)
    {
        if (verbose)
        {
            std::ostringstream msg;
            msg << target->GetName();
            msg << " is too far away";
            ai->TellPlayerNoFacing(requester, msg.str());
        }

        return false;
    }

    return true;
}

/// 判断当前状态下该动作是否可用/有效（攻击决斗对手动作）
bool AttackDuelOpponentAction::isUseful()
{
    return ai->GetUnit(AI_VALUE(ObjectGuid, "duel target"));
}

/// 执行动作主逻辑（攻击决斗对手动作）
bool AttackDuelOpponentAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    return Attack(requester, ai->GetUnit(AI_VALUE(ObjectGuid, "duel target")));
}
