// 策略值实现：PossibleAttackTargetsValue（控场/免疫/灰名抢怪过滤与增援判定）

#include "playerbot/playerbot.h"
#include "PossibleAttackTargetsValue.h"
#include "PossibleTargetsValue.h"

#include "playerbot/ServerFacade.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"
#include "AttackersValue.h"
#include "RtiTargetValue.h"
#include "EnemyPlayerValue.h"

using namespace ai;
using namespace MaNGOS;

// 从 attackers 获取战斗目标并移除非威胁或无法直接攻击的目标
std::list<ObjectGuid> PossibleAttackTargetsValue::Calculate()
{
    std::list<ObjectGuid> result;
    if (ai->AllowActivity(ALL_ACTIVITY))
    {
        if (bot->IsInWorld() && !bot->IsBeingTeleported())
        {
            // Check if we only need one possible attack target | 检查是否只需获取单个可攻击目标
            bool getOne = false;
            if (!qualifier.empty())
            {
                getOne = stoi(qualifier);
            }

            if (getOne)
            {
                // Try to get one possible attack target | 尝试仅获取一个可攻击目标
                result = AI_VALUE2(std::list<ObjectGuid>, "attackers", 1);
                RemoveNonThreating(result, getOne);
            }

            // If the one possible attack target failed, retry with multiple attackers | 若单个目标筛选失败，则回退获取完整列表
            if (result.empty())
            {
                result = AI_VALUE(std::list<ObjectGuid>, "attackers");
                RemoveNonThreating(result, getOne);
            }
        }
    }

    return result;
}

// 清理无威胁目标：尽量保留可交战目标，仅在全员被控场时按优先级回退
void PossibleAttackTargetsValue::RemoveNonThreating(std::list<ObjectGuid>& targets, bool getOne)
{
    std::list<ObjectGuid> breakableCC;
    std::list<ObjectGuid> unBreakableCC;

    for(std::list<ObjectGuid>::iterator tIter = targets.begin(); tIter != targets.end();)
    {
        Unit* target = ai->GetUnit(*tIter);
        if (!IsValid(target, bot, sPlayerbotAIConfig.sightDistance, true, false))
        {
            std::list<ObjectGuid>::iterator tIter2 = tIter;
            ++tIter;
            targets.erase(tIter2);
        }
        else if (!HasIgnoreCCRti(target, bot) && HasBreakableCC(target, bot))
        {
            breakableCC.push_back(*tIter);
            std::list<ObjectGuid>::iterator tIter2 = tIter;
            ++tIter;
            targets.erase(tIter2);
        }
        else if (!HasIgnoreCCRti(target, bot) && HasUnBreakableCC(target, bot))
        {
            unBreakableCC.push_back(*tIter);
            std::list<ObjectGuid>::iterator tIter2 = tIter;
            ++tIter;
            targets.erase(tIter2);
        }
        else
        {
            if (getOne)
            {
                // If the target is valid return it straight away | 若只需一个目标且当前目标有效则立即返回
                std::list<ObjectGuid> result = { *tIter };
                targets = result;
                break;
            }
            else
            {
                ++tIter;
            }
        }
    }

    if (targets.empty())
    {
        if (!unBreakableCC.empty())
        {
            targets = unBreakableCC;
        }
        else if(!breakableCC.empty())
        {
            targets = breakableCC;
        }
    }
}

// 检查目标的团队标记是否为当前应忽略控场的集火标记
bool PossibleAttackTargetsValue::HasIgnoreCCRti(Unit* target, Player* player)
{
    Group* group = player->GetGroup();
    return group && (group->GetTargetIcon(7) == target->GetObjectGuid());
}

// 判断目标身上是否带有受击会打破的控场效果（变形、致盲、闷棍等）
bool PossibleAttackTargetsValue::HasBreakableCC(Unit* target, Player* player)
{
    if (target->IsPolymorphed())
    {
        return true;
    }

    if (sServerFacade.IsFrozen(target))
    {
        return true;
    }

    PlayerbotAI* ai = player->GetPlayerbotAI();
    if (ai)
    {
        if (ai->HasAura("sap", target))
        {
            return true;
        }

        if (ai->HasAura("gouge", target))
        {
            return true;
        }

        if (ai->HasAura("shackle undead", target))
        {
            return true;
        }
    }

    return false;
}

// 判断目标是否处于不可打破的无敌或强控制状态（放逐、冰箱等）
bool PossibleAttackTargetsValue::HasUnBreakableCC(Unit* target, Player* player)
{
    if (target->IsStunned())
    {
        return true;
    }

    if (sServerFacade.IsFeared(target))
    {
        return true;
    }

    if (sServerFacade.IsInRoots(target))
    {
        return true;
    }

    return false;
}

// 判断目标是否已被队友或机器人选为控场（RTI CC）目标
bool PossibleAttackTargetsValue::IsCcTarget(Unit* attacker, Player* player)
{
    PlayerbotAI* ai = player->GetPlayerbotAI();
    if (ai)
    {
        Group* group = ai->GetBot()->GetGroup();
        if (group)
        {
            Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
            for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
            {
                Player *player = sObjectMgr.GetPlayer(itr->guid);
                if (!player || !sServerFacade.IsAlive(player) || !ai->IsSafe(player))
                    continue;

                if (player->GetPlayerbotAI())
                {
                    if (PAI_VALUE(ObjectGuid,"rti cc target") == attacker->GetObjectGuid())
                        return true;

                    std::string rti = PAI_VALUE(std::string,"rti cc");
                    int index = RtiTargetValue::GetRtiIndex(rti);
                    if (index != -1)
                    {
                        uint64 guid = group->GetTargetIcon(index);
                        if (guid && attacker->GetObjectGuid() == ObjectGuid(guid))
                            return true;
                    }
                }
            }
        }
    }

    return false;
}

// 判断目标是否对物理或全部法术系免疫伤害
bool PossibleAttackTargetsValue::IsImmuneToDamage(Unit* target, Player* player)
{
    // Charmed | 被魅惑控制时跳过常规免疫检测
    if (sServerFacade.IsCharmed(target) && target->IsInTeam(player, true))
    {
        return true;
    }

    // Immune to damage | 检查是否具有伤害免疫光环或状态
    // Before we check auras, check school derived immunity for creatures | 在检查光环前先校验生物自带的法术系免疫掩码
    if (target->IsCreature())
    {
        if(((Creature*)target)->GetCreatureInfo()->SchoolImmuneMask == SPELL_SCHOOL_MASK_ALL)
            return true;
    }


    PlayerbotAI* ai = player->GetPlayerbotAI();
    if (!ai)
        return false;

    for (const Aura* aura : ai->GetAuras(target))
    {
        const SpellEntry* spellInfo = aura->GetSpellProto();
        if (!spellInfo)
            continue;

        if (spellInfo->Mechanic == MECHANIC_BANISH)
            return true;

        if (!aura->IsPositive())
            continue;

        if (spellInfo->Mechanic == MECHANIC_INVULNERABILITY ||
            spellInfo->Mechanic == MECHANIC_IMMUNE_SHIELD)
        {
            return true;
        }
    }

    return false;
}

// 将当前可攻击目标列表格式化为可读名称字符串
std::string PossibleAttackTargetsValue::Format()
{
    std::ostringstream out;

    for (auto& target : value)
    {
        if (target != value.front())
            out << ",";

        WorldObject* wo = ai->GetWorldObject(target);

        if (wo)
            out << wo->GetName();
        else
            out << target;
    }

    return out.str();
}

// 检查 NPC 怪物归属权（是否已被其他非队友玩家占怪灰名）
bool PossibleAttackTargetsValue::IsTapped(Unit* target, Player* player)
{
    if (player)
    {
        PlayerbotAI* ai = player->GetPlayerbotAI();

        if (ai && ai->HasAura("tame beast", target))
            return false;

        const Creature* creature = dynamic_cast<Creature*>(target);
        if (creature)
        {
            Unit* victim = creature->GetVictim();
            Player* master = ai ? ai->GetMaster() : nullptr;
            PlayerbotAI* ai = player->GetPlayerbotAI();

             if (!victim) //Target is not attacking anything. | 目标当前未攻击任何单位
                return true;

            if (master && victim == master) //Target is attacking master. | 目标正在攻击主控玩家
                return true;

            if (player->IsInGroup(victim)) //Target is attacking groupmember. | 目标正在攻击队伍成员
                return true;

            if (!creature->HasLootRecipient()) //Target is untapped. | 目标尚未被任何玩家占怪（非灰名）
                return true;

            if (creature->IsTappedBy(player)) //Target is tapped by player. | 目标已被己方玩家占有归属权
                return true;

            if (master && target->getThreatManager().getThreat(master)) //Master as threat | 主控对该目标拥有仇恨
                return true;

            if (ai && ai->HasStrategy("attack tagged", BotState::BOT_STATE_NON_COMBAT)) //Can attack tagged. | 已开启 attack tagged 策略允许攻击被占怪
                if(ai->HasActivePlayerMaster() || !player->GetGroup() || player->GetGroup()->IsLeader(player->GetObjectGuid())) //Playing with a player or not in a group or master of group. | 当前跟随真人玩家或独立/作为队长时生效
                    return true;
        }
    }

    return false;
}

// 综合验证目标是否处于合法战斗可攻击状态
bool PossibleAttackTargetsValue::IsValid(Unit* target, Player* player, float range, bool ignoreCC, bool checkAttackerValid)
{
    // Check for the valid attackers value | 先通过 attackers 合法性校验
    if (checkAttackerValid && !AttackersValue::IsValid(target, player))
    {
        return false;
    }

    if (!IsPossibleTarget(target, player, range, ignoreCC))
        return false;

    if (sServerFacade.GetThreatManager(target).getCurrentVictim())
        return true;

    if (target->GetGuidValue(UNIT_FIELD_TARGET))
        return true;

    if (target->GetObjectGuid().IsPlayer())
        return true;

    if (player->GetPlayerbotAI() && (target->GetObjectGuid() == PAI_VALUE(ObjectGuid, "attack target")))
        return true;

    if(!HasIgnoreCCRti(target, player) && (HasBreakableCC(target, player) || HasUnBreakableCC(target, player)))
        return true;

    if (player->GetPlayerbotAI() && !player->GetPlayerbotAI()->HasActivePlayerMaster()&& PAI_VALUE(ObjectGuid, "rti target") == target->GetObjectGuid())
        return true;

    return false;
}

// 校验目标的距离、伤害免疫、控场状态与归属权
bool PossibleAttackTargetsValue::IsPossibleTarget(Unit* target, Player* player, float range, bool ignoreCC)
{
    if(target)
    {
        // If the target is in an attackable distance | 检查目标是否在可攻击距离内
        if(!player->IsWithinDistInMap(target, range))
        {
            return false;
        }

        // If the target is immune to any damage | 排除伤害免疫的目标
        if (IsImmuneToDamage(target, player))
        {
            return false;
        }

        // If the target is CC'ed or is a CC target (don't place a dot before we recast cc...) | 排除已受控或被指定为控场目标的单位
        if(!ignoreCC && !HasIgnoreCCRti(target, player) && (HasBreakableCC(target, player) || HasUnBreakableCC(target, player)) || IsCcTarget(target, player))
        {
            return false;
        }

        // If the target is a NPC | 目标为 NPC 时的额外归属检查
        Player* enemyPlayer = dynamic_cast<Player*>(target);
        if (!enemyPlayer)
        {
            // If the target is not tapped (the player doesn't have the loot rights (gray name)) | 若怪物已被他人占怪（灰名且无拾取权）则排除
            if (!IsTapped(target, player))
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

// 检查无视线潜在目标中是否有靠近当前攻击目标且尚未参战的怪物
bool PossibleAddsValue::Calculate()
{
    PlayerbotAI *ai = bot->GetPlayerbotAI();
    std::list<ObjectGuid> possible = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("possible targets no los")->Get();
    std::list<ObjectGuid> attackers = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get();

    for (std::list<ObjectGuid>::iterator i = possible.begin(); i != possible.end(); ++i)
    {
        ObjectGuid guid = *i;
        if (find(attackers.begin(), attackers.end(), guid) != attackers.end()) continue;

        Unit* add = ai->GetUnit(guid);
        if (add && !add->GetGuidValue(UNIT_FIELD_TARGET) && !sServerFacade.GetThreatManager(add).getCurrentVictim() && sServerFacade.IsHostileTo(add, bot))
        {
            for (std::list<ObjectGuid>::iterator j = attackers.begin(); j != attackers.end(); ++j)
            {
                Unit* attacker = ai->GetUnit(*j);
                if (!attacker) continue;

                float dist = sServerFacade.GetDistance2d(attacker, add);
                if (sServerFacade.IsDistanceLessOrEqualThan(dist, sPlayerbotAIConfig.aoeRadius * 1.5f)) continue;
                if (sServerFacade.IsDistanceLessOrEqualThan(dist, sPlayerbotAIConfig.aggroDistance)) return true;
            }
        }
    }
    return false;
}