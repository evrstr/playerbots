#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/generic/PullStrategy.h"
#include "playerbot/strategy/NamedObjectContext.h"
#include "playerbot/strategy/values/MoveStyleValue.h"
#include "GenericSpellActions.h"
#include "playerbot/PlayerbotFactory.h"

namespace ai
{
    /// 接近目标基类动作：根据所需施法或交互距离向目标移动
    class ReachTargetAction : public MovementAction, public Qualified
    {
    public:
        /// 构造函数：初始化接近目标基类动作
        ReachTargetAction(PlayerbotAI* ai, std::string name, float range = 0.0f) : MovementAction(ai, name), Qualified(), range(range), spellName("") {}

        /// 校验目标或限定符是否满足匹配条件
        virtual void Qualify(const std::string& qualifier) override
        {
            Qualified::Qualify(qualifier);

            // Get the distance from the qualified spell given (计算给定限定法术的有效施法距离)
            if (!qualifier.empty())
            {
                spellName = Qualified::getMultiQualifierStr(qualifier, 0, "::");

                float maxSpellRange;
                if (ai->GetSpellRange(spellName, &maxSpellRange))
                {
                    range = maxSpellRange;
                }
            }
        }

        /// 执行动作主逻辑（接近目标基类动作）
        virtual bool Execute(Event& event) override
        {
            Unit* target = GetTarget();
            if (target)
            {
                UpdateMovementState();

                // Ignore movement if too far (距离过远时忽略该移动请求)
                const float distanceToTarget = bot->GetDistance(target, false, DIST_CALC_COMBAT_REACH);
                float chaseDist = range;
                const bool inLos = bot->IsWithinLOSInMap(target, true);
                const bool isFriend = sServerFacade.IsFriendlyTo(bot, target);

                if (range > 0.0f)
                {
                    chaseDist = inLos ? range : (isFriend ? std::min(distanceToTarget * 0.9f, range) : range);
                    chaseDist = (chaseDist - sPlayerbotAIConfig.contactDistance);
                }

                if (MoveStyleValue::WaitForEnemy(ai) && !ai->GetUnit(AI_VALUE(ObjectGuid, "rti cc target")) && target->m_movementInfo.HasMovementFlag(movementFlagsMask) &&
                        sServerFacade.IsInFront(target, bot, sPlayerbotAIConfig.sightDistance, CAST_ANGLE_IN_FRONT) &&
                        sServerFacade.IsDistanceGreaterThan(distanceToTarget, sPlayerbotAIConfig.tooCloseDistance))
                {
                    return true;
                }                 

                if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
                {
                    std::ostringstream out;
                    out << "Moving to reach " << ChatHelper::formatWorldobject(target);
                    ai->TellPlayerNoFacing(GetMaster(), out);
                }
                
                bool moved;
                if (inLos && isFriend && (range <= ai->GetRange("follow")))
                {
                    moved = MoveNear(target, chaseDist);
                }
                else
                {
                    moved = ChaseTo(target, chaseDist, bot->GetAngle(target));
                }

                if (!moved)
                {
                    if (++reachFails >= 15)
                    {
                        reachFails = 0;

                        SET_AI_VALUE(ObjectGuid, "old target", target->GetObjectGuid());
                        SET_AI_VALUE(ObjectGuid, "current target", ObjectGuid());
                        if (AI_VALUE(ObjectGuid, "attack target") == target->GetObjectGuid())
                            SET_AI_VALUE(ObjectGuid, "attack target", ObjectGuid());

                        bot->SetSelectionGuid(ObjectGuid());
                        bot->AttackStop();

                        if (verbose)
                        {
                            std::ostringstream out;
                            out << "Dropping unreachable target: " << ChatHelper::formatWorldobject(target);
                            ai->TellPlayerNoFacing(GetMaster(), out);
                        }
                    }
                }
                else
                    reachFails = 0;

                return moved;
            }

            return false;
        }

        uint32 reachFails = 0;

        /// 判断当前状态下该动作是否可用/有效（接近目标基类动作）
        virtual bool isUseful() override
        {
            // Do not move if stay strategy is set (若已启用原地停留（stay）策略则不要移动)
            if (!ai->HasStrategy("stay", ai->GetState()))
            {
                Unit* target = GetTarget();
                if (target)
                {
                    // Do not move while casting (施法读条期间不要移动)
                    if (!bot->IsNonMeleeSpellCasted(true, false, true))
                    {
                        // Check if the spell for which the reach action is used for can be casted (检查触发接近动作的目标法术是否可以施放)
                        if (!spellName.empty() && !ai->CanCastSpell(spellName, target, true, nullptr, true, true, true))
                        {
                            return false;
                        }

                        // Force move if not in los (不在视野内时强制移动调整站位)
                        if (bot->IsWithinLOSInMap(target, true))
                        {
                            // Check if the bot is already on the range required (检查机器人是否已处于要求的距离范围内)
                            return bot->GetDistance(target, true, DIST_CALC_COMBAT_REACH) > range;
                        }

                        return true;
                    }
                }
            }

            return false;
        }

        /// 获取当前动作的目标名称标识（接近目标基类动作）
        virtual std::string GetTargetName() override { return "current target"; }
        /// 获取当前绑定的法术名称
        std::string GetSpellName() const { return spellName; }

        /// 获取当前动作的目标单位（接近目标基类动作）
        virtual Unit* GetTarget() override
        {
            // Get the target from the qualifiers (从限定符参数中解析目标单位)
            if (!qualifier.empty())
            {
                std::string targetQualifier;
                const std::string targetName = Qualified::getMultiQualifierStr(qualifier, 1, "::");
                if (targetName != "current target")
                {
                    targetQualifier = Qualified::getMultiQualifierStr(qualifier, 2, "::");
                }

                return targetQualifier.empty() ? ai->GetUnit(AI_VALUE(ObjectGuid, targetName)) : ai->GetUnit(AI_VALUE2(ObjectGuid, targetName, targetQualifier));
            }
            else
            {
                return ai->GetUnit(AI_VALUE(ObjectGuid, GetTargetName()));
            }
        }

    protected:
        float range;
        std::string spellName;
    };

    /// 接近并施放法术动作：进入目标射程后施放对应法术
    class CastReachTargetSpellAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化接近并施放法术动作
        CastReachTargetSpellAction(PlayerbotAI* ai, std::string spell, float distance) : CastSpellAction(ai, spell), distance(distance) {}

        /// 判断当前状态下该动作是否可用/有效（接近并施放法术动作）
        virtual bool isUseful() override
        {
            // Do not move if stay strategy is set (若已启用原地停留（stay）策略则不要移动)
            if (ai->HasStrategy("stay", ai->GetState()))
                return false;

            return sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "current target"), (distance + sPlayerbotAIConfig.contactDistance));
        }

    protected:
        float distance;
    };

    /// 进入近战范围动作：向攻击目标移动直至进入近战攻击距离
    class ReachMeleeAction : public ReachTargetAction
    {
    public:
        /// 构造函数：初始化进入近战范围动作
        ReachMeleeAction(PlayerbotAI* ai) : ReachTargetAction(ai, "reach melee") {}
    };

    /// 进入法术射程动作：向目标移动直至进入法术施放距离与视野
    class ReachSpellAction : public ReachTargetAction
    {
    public:
        /// 构造函数：初始化进入法术射程动作
        ReachSpellAction(PlayerbotAI* ai) : ReachTargetAction(ai, "reach spell", ai->GetRange("spell")) {}
    };

    /// 进入拉怪射程动作：向待拉目标移动直至满足拉怪技能射程要求
    class ReachPullAction : public ReachTargetAction
    {
    public:
        /// 构造函数：初始化进入拉怪射程动作
        ReachPullAction(PlayerbotAI* ai) : ReachTargetAction(ai, "reach pull")
        {
            PullStrategy* strategy = PullStrategy::Get(ai);
            if (strategy)
            {
                range = strategy->GetRange();
            }
        }

        /// 校验目标或限定符是否满足匹配条件
        void Qualify(const std::string& qualifier) override
        {
            ReachTargetAction::Qualify(qualifier);

            // Reduce the range slightly for a more accurate pull (moving targets can get out of reach) (略微缩减距离以确保拉怪准确（防止移动目标脱离射程）)
            const float threshold = 5.0f;
            range = range > threshold ? range - threshold : range;
        }

        /// 获取当前动作的目标名称标识（进入拉怪射程动作）
        std::string GetTargetName() override { return "pull target"; }
    };

    /// 接近待治疗队友动作：向血量不足的队友移动直至进入治疗法术射程
    class ReachPartyMemberToHealAction : public ReachTargetAction
    {
    public:
        /// 构造函数：初始化接近待治疗队友动作
        ReachPartyMemberToHealAction(PlayerbotAI* ai) : ReachTargetAction(ai, "reach party member to heal", ai->GetRange("heal")) {}
        /// 获取当前动作的目标名称标识（接近待治疗队友动作）
        virtual std::string GetTargetName() override { return "party member to heal"; }
    };

    /// 接近队友插图腾动作：向队伍集中区域移动以便队友覆盖图腾效果
    class ReachPartyMemberForTotemAction : public ReachTargetAction
    {
    public:
        /// 构造函数：初始化接近队友插图腾动作
        ReachPartyMemberForTotemAction(PlayerbotAI* ai)
            /// 构造函数：初始化接近目标动作基类
            : ReachTargetAction(ai, "reach party member for totem", 20.0f) {}

        /// 校验目标或限定符是否满足匹配条件
        void Qualify(const std::string& qualifier) override
        {
            ReachTargetAction::Qualify(qualifier);
            range = 20.0f;
        }

        /// 获取当前动作的目标单位（接近队友插图腾动作）
        Unit* GetTarget() override
        {
            std::string totemSpell = spellName;
            if (totemSpell.empty() && !qualifier.empty())
                totemSpell = Qualified::getMultiQualifierStr(qualifier, 0, "::");

            Group* group = bot->GetGroup();
            if (!group || totemSpell.empty())
                return ai->GetUnit(AI_VALUE(ObjectGuid, "master target"));

            for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
            {
                Player* member = ref->getSource();
                if (!member || !sServerFacade.IsAlive(member))
                    continue;

                if (member == bot)
                    continue;

                if (!member->IsInWorld() || member->GetMapId() != bot->GetMapId())
                    continue;

                if (!bot->IsWithinDistInMap(member, 100.0f, false))
                    continue;

                if (!bot->IsWithinDistInMap(member, range, false) || !AI_VALUE2(bool, "has totem", name))
                    return member; 
            }

            return nullptr;
        }
    };
}
