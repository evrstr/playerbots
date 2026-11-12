// 策略值实现：PossibleTargetsValue（潜在目标网格搜索及敌我/可攻击校验）

#include "playerbot/playerbot.h"
#include "PossibleTargetsValue.h"
#include "PossibleAttackTargetsValue.h"
#include "FreeMoveValues.h"

#include "playerbot/ServerFacade.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;
using namespace MaNGOS;

// 解析可选范围和忽略校验参数，收集周围合法的潜在目标 GUID
std::list<ObjectGuid> PossibleTargetsValue::Calculate()
{
    float rangeCheck = range;
    bool shouldIgnoreValidate = false;
    if (!qualifier.empty())
    {
        rangeCheck = Qualified::getMultiQualifierInt(qualifier, 0, ":");
        shouldIgnoreValidate = Qualified::getMultiQualifierInt(qualifier, 1, ":");
    }

    std::list<Unit*> targets;
    FindPossibleTargets(bot, targets, rangeCheck);

    std::list<ObjectGuid> results;
    for (std::list<Unit*>::iterator i = targets.begin(); i != targets.end(); ++i)
    {
        Unit* unit = *i;
        if (unit && (shouldIgnoreValidate || AcceptUnit(unit)))
        {
            results.push_back(unit->GetObjectGuid());
        }
    }

    return results;
}

// 调用 FindPossibleTargets 搜索周围单位
void PossibleTargetsValue::FindUnits(std::list<Unit*> &targets)
{
    FindPossibleTargets(bot, targets, range);
}

// 使用 IsValid 判定单个单位是否为可攻击目标
bool PossibleTargetsValue::AcceptUnit(Unit* unit)
{
    return IsValid(unit, bot, ignoreLos);
}

// 使用 AnyUnitInObjectRangeCheck 网格搜索器查找范围内单位
void PossibleTargetsValue::FindPossibleTargets(Player* player, std::list<Unit*>& targets, float range)
{
    MaNGOS::AnyUnitInObjectRangeCheck u_check(player, range);
    MaNGOS::UnitListSearcher<MaNGOS::AnyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(player, searcher, range);
}

// 判断目标对玩家是否友好（综合决斗与竞技场队伍敌对判定）
bool PossibleTargetsValue::IsFriendly(Unit* target, Player* player)
{
    bool friendly = false;
    if (sServerFacade.IsFriendlyTo(target, player))
    {
        friendly = true;

#ifndef MANGOSBOT_ZERO
        // Check if the target is another player in a duel/arena | 检查目标是否为处于决斗或竞技场中的其他玩家
        Player* targetPlayer = dynamic_cast<Player*>(target);
        if (targetPlayer)
        {
            // If the target is in an arena with the player and is not on the same team | 若在竞技场且不属于同一队伍，则视为敌对
            if (targetPlayer->InArena() && player->InArena() && (targetPlayer->GetBGTeam() != player->GetBGTeam()))
            {
                friendly = false;
            }
        }
#endif
    }

    return friendly;
}

// 判断目标是否处于可被玩家攻击且非不可选中/非战斗状态
bool PossibleTargetsValue::IsAttackable(Unit* target, Player* player)
{
    const bool inVehicle = player->GetPlayerbotAI() && player->GetPlayerbotAI()->IsInVehicle();
    return !target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1) &&
           !target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNTARGETABLE) &&
           (inVehicle || !target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE)) &&
           !target->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION) &&
           player->CanAttack(target);
}

// 综合检查目标存活、同地图、视线、友好度、可攻击性及自由移动限制
bool PossibleTargetsValue::IsValid(Unit* target, Player* player, bool ignoreLos)
{
    // If the target is available | 若目标单位在世界中且与玩家同地图
    if (target && target->IsInWorld() && (target->GetMapId() == player->GetMapId()))
    {
        // If the target is dead | 排除已死亡目标
        if (sServerFacade.UnitIsDead(target))
        {
            return false;
        }

        // If the target is friendly | 排除友方目标
        if (IsFriendly(target, player))
        {
            return false;
        }

        // If the target can't be attacked | 排除不可攻击目标
        if (!IsAttackable(target, player))
        {
            return false;
        }

        bool isInCombatWithTarget = target->GetVictim() == player || 
                                     target->getThreatManager().getThreat(player) > 0.0f ||
                                     player->IsInCombat();

        if (!ignoreLos && !isInCombatWithTarget)
        {
            if (!target->IsVisibleForOrDetect(player, player->GetCamera().GetBody(), true))
            {
                return false;
            }
        }
        // 校验目标是否在机器人自由移动攻击范围限制内
        if (!CanFreeMoveValue::CanFreeAttack(player->GetPlayerbotAI(), target))
            return false;

        return true;
    }

    return false;
}