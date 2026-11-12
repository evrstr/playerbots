/// 距离与位置范围检测触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/generic/CombatStrategy.h"
#include "playerbot/strategy/values/PossibleAttackTargetsValue.h"
#include "playerbot/strategy/values/Formations.h"

namespace ai
{
    /// 触发器：敌人距离过近不利于施放法术（风筝/拉开距离）
    class EnemyTooCloseForSpellTrigger : public Trigger 
    {
    public:
        EnemyTooCloseForSpellTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close for spell") {}
        
        virtual bool IsActive() override
        {
            if (ai->HasStrategy("follow", BotState::BOT_STATE_COMBAT) ||
                ai->HasStrategy("guard", BotState::BOT_STATE_COMBAT) ||
                ai->HasStrategy("stay", BotState::BOT_STATE_COMBAT) ||
                ai->HasStrategy("wander", BotState::BOT_STATE_COMBAT))
                        return false; 
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if (target)
            {
                const bool canMove = !PossibleAttackTargetsValue::HasBreakableCC(target, bot) && !PossibleAttackTargetsValue::HasUnBreakableCC(target, bot);

                // Don't move if the target is targeting you and you can't add distance between you and the target (how fast bot runs) | 若目标正在追击你且移速差无法拉开距离，则不移动
                if (target->GetTarget() == bot && canMove && target->GetSpeedInMotion() > (bot->GetSpeedInMotion() * 0.65))
                {
                    return false;
                }

                // Don't move if our flee range (how far bot runs) is too low to escape attack distance | 若配置的逃跑距离不足以脱离近战攻击距离，则不移动
                // This is good if you don't want a bot to run away from an enemy that can't be cc or tanked | 适用于不希望机器人盲目逃离无法被控制或坦克拉住的敌人
                if (ai->GetRange("flee") <= ATTACK_DISTANCE)
                    return false;

                float const combatReach = bot->GetCombinedCombatReach(target, false);
                float const minDistance = ai->GetRange("spell") + combatReach;
                float const targetDistance = sServerFacade.GetDistance2d(bot, target) + combatReach;

                // No need to move if the target is rooted and you can shoot | 若目标已被定身且当前可以远程施法，则无需移动
                if (!canMove && (targetDistance > minDistance))
                {
                    return false;
                }

                bool isBoss = false;
                bool isRaid = false;
                bool isVictim = target->GetVictim() && target->GetVictim()->GetObjectGuid() == bot->GetObjectGuid();

                if (target->IsCreature())
                {
                    Creature* creature = ai->GetCreature(target->GetObjectGuid());
                    if (creature)
                    {
                        isBoss = creature->IsWorldBoss();
                    }
                }

                if (bot->GetMap()->IsRaid())
                    isRaid = true;

                //if (isBoss || isRaid)
                //    return sServerFacade.IsDistanceLessThan(targetDistance, (ai->GetRange("spell") + combatReach) / 2);

                float coeff = 0.5f;
                if (target->IsPlayer())
                {
                    if (!isVictim)
                        coeff = 0.4f;
                    else
                        coeff = 0.6f;
                }
                else
                {
                    if (!isVictim)
                        coeff = 0.4f;
                    else
                        coeff = 0.6f;
                }

                if (isRaid)
                    coeff = 0.7f;

                return sServerFacade.IsDistanceLessOrEqualThan(targetDistance, minDistance * coeff);
            }
            return false;
        }
    };

    /// 触发器：敌人距离过近不利于远程射击
    class EnemyTooCloseForShootTrigger : public Trigger 
    {
    public:
        EnemyTooCloseForShootTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close for shoot") {}
        
        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if (target)
            {
                // Don't move if the target is targeting you and you can't add distance between you and the target | 若目标正在追击你且无法拉开距离，则不移动
                if (target->GetTarget() == bot && !target->IsRooted() && target->GetSpeedInMotion() > (bot->GetSpeedInMotion() * 0.65))
                {
                    return false;
                }

                float const combatReach = bot->GetCombinedCombatReach(target, false);
                float const minShootDistance = ai->GetRange("shoot") + combatReach;
                float const targetDistance = sServerFacade.GetDistance2d(bot, target) + combatReach;

                // No need to move if the target is rooted and you can shoot | 若目标已被定身且当前可以射击，则无需移动
                if (target->IsRooted() && (targetDistance > minShootDistance))
                {
                    return false;
                }

                bool isBoss = false;
                bool isRaid = false;
                bool isVictim = target->GetVictim() && target->GetVictim()->GetObjectGuid() == bot->GetObjectGuid();

                if (target->IsCreature())
                {
                    Creature* creature = ai->GetCreature(target->GetObjectGuid());
                    if (creature)
                    {
                        isBoss = creature->IsWorldBoss();
                    }
                }

                if (bot->GetMap()->IsRaid())
                    isRaid = true;

                //if (isBoss || isRaid)
                //    return sServerFacade.IsDistanceLessThan(targetDistance, (ai->GetRange("spell") + combatReach));

                float coeff = 0.5f;
                if (target->IsPlayer())
                {
                    if (!isVictim)
                        coeff = 0.7f;
                    else
                        coeff = 1.0f;
                }
                else
                {
                    if (!isVictim)
                        coeff = 0.4f;
                    else
                        coeff = 0.6f;
                }

                if (isRaid)
                    coeff = 1.0f;

                return sServerFacade.IsDistanceLessOrEqualThan(targetDistance, minShootDistance * coeff);
            }

            return false;
        }
    };

    /// 触发器：敌人距离近战攻击位置过近（模型重叠/处于目标体内）
    class EnemyTooCloseForMeleeTrigger : public Trigger 
    {
    public:
        EnemyTooCloseForMeleeTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close for melee", 3) {}
        
        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if (target && target->IsPlayer())
                return false;

            return target && AI_VALUE2(bool, "inside target", "current target");
        }
    };

    /// 触发器基类：检测当前目标是否在指定距离内（可限制仅玩家或以机器人为目标）
    class EnemyInRangeTrigger : public Trigger 
    {
    public:
        EnemyInRangeTrigger(PlayerbotAI* ai, std::string name, float distance, bool enemyMustBePlayer = false, bool enemyTargetsBot = false)
        : Trigger(ai, name)
        , distance(distance)
        , enemyMustBePlayer(enemyMustBePlayer)
        , enemyTargetsBot(enemyTargetsBot) {}
        
        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if (target)
            {
                if (enemyMustBePlayer && !target->IsPlayer())
                {
                    return false;
                }

                if (enemyTargetsBot && target->GetTarget() != bot)
                {
                    return false;
                }

                return sServerFacade.IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "current target"), distance);
            }

            return false;
        }

    protected:
        float distance;
        bool enemyMustBePlayer;
        bool enemyTargetsBot;
    };

    /// 触发器：敌人处于近距离警戒范围内
    class EnemyIsCloseTrigger : public EnemyInRangeTrigger
    {
    public:
        EnemyIsCloseTrigger(PlayerbotAI* ai) : EnemyInRangeTrigger(ai, "enemy is close", sPlayerbotAIConfig.tooCloseDistance) {}
    };

    /// 触发器基类：检测目标是否超出指定距离范围
    class OutOfRangeTrigger : public Trigger 
    {
    public:
        OutOfRangeTrigger(PlayerbotAI* ai, std::string name, float distance) : Trigger(ai, name)
        {
            this->distance = distance;
        }

        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, GetTargetName()));
            return target &&
                sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", GetTargetName()), distance);
        }

        virtual std::string GetTargetName() override { return "current target"; }

    protected:
        float distance;
    };

    /// 触发器：敌人超出近战攻击范围或不在视野内
    class EnemyOutOfMeleeTrigger : public OutOfRangeTrigger
    {
    public:
        EnemyOutOfMeleeTrigger(PlayerbotAI* ai) : OutOfRangeTrigger(ai, "enemy out of melee range", sPlayerbotAIConfig.meleeDistance) {}
        
        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, GetTargetName()));
            if (!target)
                return false;

            return !bot->CanReachWithMeleeAttack(target) || !bot->IsWithinLOSInMap(target, true);
        }
    };

    /// 触发器：敌人超出法术施放范围或不在视野内
    class EnemyOutOfSpellRangeTrigger : public OutOfRangeTrigger
    {
    public:
        EnemyOutOfSpellRangeTrigger(PlayerbotAI* ai) : OutOfRangeTrigger(ai, "enemy out of spell range", ai->GetRange("spell")) {}
        
        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, GetTargetName()));
            if (!target)
                return false;

            return target && (bot->GetDistance(target, true, DIST_CALC_COMBAT_REACH) > (distance - sPlayerbotAIConfig.contactDistance)) || !bot->IsWithinLOSInMap(target, true);
        }
    };

    /// 触发器：需要治疗的小队成员超出治疗法术范围或不在视野内
    class PartyMemberToHealOutOfSpellRangeTrigger : public OutOfRangeTrigger
    {
    public:
        PartyMemberToHealOutOfSpellRangeTrigger(PlayerbotAI* ai) : OutOfRangeTrigger(ai, "party member to heal out of spell range", ai->GetRange("heal")) {}
        virtual std::string GetTargetName() override { return "party member to heal"; }
        
        virtual bool IsActive() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, GetTargetName()));
            if (!target)
                return false;

            return target && (bot->GetDistance(target, true, DIST_CALC_COMBAT_REACH) > (distance - sPlayerbotAIConfig.contactDistance)) || !bot->IsWithinLOSInMap(target, true);
        }
    };

    /// 触发器：距离主人过远（乘同一交通工具时除外）
    class FarFromMasterTrigger : public Trigger 
    {
    public:
        FarFromMasterTrigger(PlayerbotAI* ai, std::string name = "far from master", float distance = 12.0f, int checkInterval = 50) : Trigger(ai, name, checkInterval), distance(distance) {}

        virtual bool IsActive() override
        {
            Unit* master = ai->GetUnit(AI_VALUE(ObjectGuid, "master target"));
            if (master && sServerFacade.IsFriendlyTo(bot, master))
            {
                if (master->GetTransport() && master->GetTransport() == bot->GetTransport())
                    return false;

                return sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), distance);
            }

            return false;
        }

    private:
        float distance;
    };

    /// 触发器：超出主人最大反应距离
    class OutOfReactRangeTrigger : public FarFromMasterTrigger
    {
    public:
        OutOfReactRangeTrigger(PlayerbotAI* ai, std::string name = "out of react range", float distance = sPlayerbotAIConfig.reactDistance, int checkInterval = 2) : FarFromMasterTrigger(ai, name, distance, checkInterval) {}
    };

    /// 触发器：未靠近主人（处于跟随距离与反应距离之间）
    class NotNearMasterTrigger : public OutOfReactRangeTrigger
    {
    public:
        NotNearMasterTrigger(PlayerbotAI* ai, std::string name = "not near master", int checkInterval = 2) : OutOfReactRangeTrigger(ai, name, 5.0f, checkInterval) {}

        virtual bool IsActive() override
        {
            return FarFromMasterTrigger::IsActive() && !sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.reactDistance);
        }
    };

    /// 触发器：需要更新跟随状态或重新调整队形位置
    class UpdateFollowTrigger : public NotNearMasterTrigger
    {
    public:
        UpdateFollowTrigger(PlayerbotAI* ai) : NotNearMasterTrigger(ai, "update follow", 3) {}

        virtual bool IsActive() override
        {
            Unit* followTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "follow target"));

            if (!followTarget || !ai->IsSafe(followTarget))
                return false;

            //We need to land or liftoff. | 需要降落或起飞以匹配跟随目标的飞行状态
            if (followTarget->IsFlying() != bot->IsFlying() || followTarget->IsTaxiFlying())
                return true;

            Formation* formation = AI_VALUE(Formation*, "formation");

            //Already using proper formation. | 当前已处于正确的追随队形位置
            if (sServerFacade.GetChaseTarget(bot) && sServerFacade.GetChaseTarget(bot)->GetObjectGuid() == followTarget->GetObjectGuid() && formation->GetAngle() == sServerFacade.GetChaseAngle(bot) && formation->GetOffset() == sServerFacade.GetChaseOffset(bot))
                return false;

            if (!ai->IsStateActive(BotState::BOT_STATE_COMBAT))
                return true;

            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));

            if (!target)
                return true;

            if (target->GetTarget() == bot) //Try pulling target to follow position | 尝试将当前仇恨目标拉回跟随位置
                return true;

            if (!ai->IsRanged(bot)) //Melee bots stay in melee. | 近战机器人保持近战贴身位置
                return false;

            WorldPosition formationPosition = AI_VALUE(WorldPosition, "formation position");

            if (formationPosition.sqDistance2d(target) > ai->GetRange("spell")) //Do not move to follow if we can't attack from that position. | 若队形位置超出施法射程无法攻击，则暂不跟随移动
                return false;

            return true;
        }
    };

    /// 触发器：满足条件时停止跟随（目标消失、不同乘具或处于飞行航线中）
    class StopFollowTrigger : public Trigger
    {
    public:
        StopFollowTrigger(PlayerbotAI* ai, std::string name = "stop follow", int checkInterval = 2) : Trigger(ai, name, checkInterval) {}

        virtual bool IsActive() override
        {
            Unit* followTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "follow target"));

            if (!followTarget)
                return true;

            if (bot->GetTransport() != followTarget->GetTransport())
                return true;

            //We need to land or liftoff. | 若目标在飞行中则需停下等待或调整
            if (followTarget->IsTaxiFlying())
                return true;

            return false;
        }
    };

    /// 触发器：游荡超出最大自由移动范围
    class WanderFarTrigger : public Trigger
    {
    public:
        WanderFarTrigger(PlayerbotAI * ai, std::string name = "wander far", int checkInterval = 2)
            : Trigger(ai, name, checkInterval) {
        }

        bool IsActive() override
        {
            return !AI_VALUE2(bool, "can free move", "wandermax");
        }
    };

    /// 触发器：游荡处于中等距离范围内
    class WanderMediumTrigger : public Trigger
    {
    public:
        WanderMediumTrigger(PlayerbotAI* ai, std::string name = "wander medium", int checkInterval = 2) : Trigger(ai, name, checkInterval) {}

        bool IsActive() override
        {
            return !AI_VALUE2(bool, "can free move", "wandermin") && AI_VALUE2(bool, "can free move", "wandermax");
        }
    };

    /// 触发器：游荡距离较近或已停止跟随
    class WanderNearTrigger : public StopFollowTrigger
    {
    public:
        WanderNearTrigger(PlayerbotAI* ai, std::string name = "wander near", int checkInterval = 2) : StopFollowTrigger(ai, name, checkInterval) {}

        bool IsActive() override
        {
            if (StopFollowTrigger::IsActive())
                return true;

            return AI_VALUE2(bool, "can free move", "wandermin");
        }
    };

    /// 触发器：等待攻击策略下调整与目标的安全距离
    class WaitForAttackSafeDistanceTrigger : public Trigger
    {
    public:
        WaitForAttackSafeDistanceTrigger(PlayerbotAI* ai, std::string name = "wait for attack safe distance") : Trigger(ai, name) {}

        virtual bool IsActive() override
        {
            // we can't let them run away from the targets we need to cc at the start | 开战前需要控制目标，不能让队友提前跑离控制位置
            if (WaitForAttackStrategy::ShouldWait(ai) && !ai->GetUnit(AI_VALUE(ObjectGuid, "rti cc target")))
            {
                // Do not move if stay strategy is set | 若已开启原地停留策略则不移动
                if (!ai->HasStrategy("stay", ai->GetState()))
                {
                    // Do not move if currently being targeted | 若当前正在被敌人攻击则不移动
                    const bool isBeingTargeted = !bot->getAttackers().empty();
                    if (!isBeingTargeted)
                    {
                        Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
                        if (target)
                        {
                            const float safeDistance = WaitForAttackStrategy::GetSafeDistance();
                            const float safeDistanceThreshold = WaitForAttackStrategy::GetSafeDistanceThreshold();
                            const float distanceToTarget = sServerFacade.GetDistance2d(bot, target);
                            return (distanceToTarget > (safeDistance + safeDistanceThreshold)) ||
                                   (distanceToTarget < (safeDistance - safeDistanceThreshold));
                        }
                    }
                }
            }

            return false;
        }
    };

    /// 触发器：超出自由移动允许范围
    class OutOfFreeMoveRangeTrigger : public Trigger
    {
    public:
        OutOfFreeMoveRangeTrigger(PlayerbotAI* ai, std::string name = "out of free move range") : Trigger(ai, name) {}

        virtual bool IsActive() override
        {
            return !AI_VALUE(bool, "can free move");
        };
    };
}