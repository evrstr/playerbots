/// 卡拉赞（Karazhan）团队副本触发器实现

#include "playerbot/playerbot.h"
#include "KarazhanDungeonTriggers.h"
#include "playerbot/strategy/generic/KarazhanDungeonStrategies.h"
#include "GenericTriggers.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;

/// 检测虚空幽龙传送门阶段非主坦机器人是否需要调整射线吸收
bool NetherspiteBeamsCheatNeedRefreshTrigger::IsActive()
{
    //Checking that is portal phase | 检查是否处于传送门阶段
    NetherspiteFightStrategy* strategy = NetherspiteFightStrategy::Get(ai);
    std::list<Unit*> creatures;
    MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(bot, 17369, 100);
    MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(creatures, u_check);
    Cell::VisitAllObjects(bot, searcher, 100);

    if (creatures.empty())
        return false;
    if (!strategy)
        return false;
    Unit* boss = ai->GetUnit(strategy->GetBossGuid());
    if (!boss)
        return false;

    //Checking that this bot is not Netherspite target to prevent overloading tank trigger | 确认当前机器人并非 Boss 的目标，避免干扰坦克触发器
    return boss->GetVictim() != bot && (ai->HasAura(30468, boss) || ai->HasAura(30467, boss) || ai->HasAura(30466, boss));
}

/// 检测虚空幽龙传送门阶段坦克是否需要刷新射线位置
bool NetherspiteBeamsPlayerCheatNeedRefreshTrigger::IsActive()
{
    //Checking that is portal phase | 检查是否处于传送门阶段
    NetherspiteFightStrategy* strategy = NetherspiteFightStrategy::Get(ai);
    std::list<Unit*> creatures;
    MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(bot, 17369, 100);
    MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(creatures, u_check);
    Cell::VisitAllObjects(bot, searcher, 100);

    if (creatures.empty())
        return false;
    if (!strategy || !strategy->GetBossGuid())
        return false;
    Unit* boss = ai->GetUnit(strategy->GetBossGuid());
    if (!boss)
        return false;

    //Checking that this bot is Netherspite target | 确认当前机器人是正在抗怪的坦克
    return ai->IsTank(bot) && boss->GetVictim() == bot;
}

/// 检测埃兰之影是否正在施放魔爆术（29973）
bool ShadeOfAranCastingArcaneExplosionTrigger::IsActive()
{
    //Checking that Shade of Aran is casting arcane explosion | 检查埃兰之影是否正在施放奥术爆炸（魔爆术）
    ShadeOfAranFightStrategy* strategy = ShadeOfAranFightStrategy::Get(ai);

    if (strategy)
    {
        // No need to check if we are on arcane currently | 若已处于奥术阶段则无需重复检查
        if (strategy->GetPhase() == AranPhase::PHASE_ARCANE)
            return true;
            
        Unit* aran = ai->GetUnit(strategy->GetBossGuid());
        if (aran)
        {
            if (Spell const* genericSpell = aran->GetCurrentSpell(CURRENT_GENERIC_SPELL))
            {
                if (genericSpell->m_spellInfo->Id == 29973 && genericSpell->getState() != SPELL_STATE_FINISHED)
                    return true;
            } 
        }
    }

    return false;
}

/// 检测埃兰之影的魔爆术是否已施放完毕
bool ShadeOfAranDoneCastingArcaneExplosionTrigger::IsActive()
{
    //Checking that Shade of Aran is done casting arcane explosion | 检查埃兰之影魔爆术是否结束
    ShadeOfAranFightStrategy* strategy = ShadeOfAranFightStrategy::Get(ai);

    if (strategy)
    {
        Unit* aran = ai->GetUnit(strategy->GetBossGuid());
        if (aran && strategy->GetPhase() == AranPhase::PHASE_ARCANE)
        {
            if (Spell const* genericSpell = aran->GetCurrentSpell(CURRENT_GENERIC_SPELL))
            {
                if (genericSpell->m_spellInfo->Id == 29973 && genericSpell->getState() == SPELL_STATE_FINISHED)
                    return true;
                else
                    return false;
            }
            else
                return true;
        }
    }

    return false;
}

/// 检测埃兰之影是否正在施放烈焰花环（30004）
bool ShadeOfAranCastingFlameWreathTrigger::IsActive()
{
    //Checking that Shade of Aran is casting flame wreath | 检查埃兰之影是否正在施放烈焰花环
    ShadeOfAranFightStrategy* strategy = ShadeOfAranFightStrategy::Get(ai);

    if (strategy)
    {
        // No need to check if we are on fire currently | 若已处于火焰阶段则无需重复检查
        if (strategy->GetPhase() == AranPhase::PHASE_FIRE)
            return false;

        Unit* aran = ai->GetUnit(strategy->GetBossGuid());
        if (aran)
        {
            if (Spell const* genericSpell = aran->GetCurrentSpell(CURRENT_GENERIC_SPELL))
            {
                if (genericSpell->m_spellInfo->Id == 30004)
                    return true;
            } 
        }
    }

    return false;
}

/// 检测埃兰之影是否正在施放暴风雪（29969）
bool ShadeOfAranCastingBlizzardTrigger::IsActive()
{
    //Checking that Shade of Aran is casting blizzard | 检查埃兰之影是否正在施放暴风雪
    ShadeOfAranFightStrategy* strategy = ShadeOfAranFightStrategy::Get(ai);

    if (strategy)
    {
        // No need to check if we are on frost currently | 若已处于冰霜阶段则无需重复检查
        if (strategy->GetPhase() == AranPhase::PHASE_FROST)
            return false;

        Unit* aran = ai->GetUnit(strategy->GetBossGuid());
        if (aran)
        {
            if (Spell const* genericSpell = aran->GetCurrentSpell(CURRENT_GENERIC_SPELL))
            {
                if (genericSpell->m_spellInfo->Id == 29969)
                    return true;
            } 
        }
    }

    return false;
}

/// 检测埃兰之影生命值是否降至 40% 以下召唤水元素
bool ShadeOfAranElementalsTrigger::IsActive()
{
    //Checking that the water elementals are out | 检查水元素是否已召唤
    ShadeOfAranFightStrategy* strategy = ShadeOfAranFightStrategy::Get(ai);

    if (strategy && !strategy->GetElementals())
    {
        Unit* aran = ai->GetUnit(strategy->GetBossGuid());
        if (aran)
        {
            if (aran->GetHealthPercent() <= 40.0f)
                return true;
        }
    }

    return false;
}

/// 检测玛克扎尔王子战中是否因虚弱（30843）、暗影新星或距离过近需躲避
bool PrinceMalchezaarTooCloseTrigger::IsActive()
{
    PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy && strategy->HasPullStarted())
        return false;
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "tank target"));
    if (!target) target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (bot->HasAura(30843) || (EnfeeblePart() && target && target->GetVictim() != bot) || MeleeWaitCheck(target)) 
        return true;
    if (ai->IsRanged(bot, true))
        return CloseToCreatureTrigger::IsActive();
    return false;
}

/// 检测近战职业是否需要在王子施放暗影新星（30852）时后撤躲避
bool PrinceMalchezaarTooCloseTrigger::MeleeWaitCheck(Unit* target)
{
    // Check if we should be someone staying out of Shadow Nova blast | 检查近战是否需要退出暗影新星爆炸范围
    if (target && target->GetHealthPercent() > 30.0f && target->IsCreature())
    {
        if (ai->IsMelee(bot, true) && target->GetVictim() != bot && target->GetDistance(bot) > 8.0f)
        {
            if (Spell const* genericSpell = target->GetCurrentSpell(CURRENT_GENERIC_SPELL))
            {
                if (genericSpell->m_spellInfo->Id == 30852 && genericSpell->getState() != SPELL_STATE_FINISHED)
                    return true;
            }
        }
    }

    return false;
}

/// 检测队伍中是否有人身中虚弱（30843）减益效果
bool PrinceMalchezaarTooCloseTrigger::EnfeeblePart()
{
    Group* group = bot->GetGroup();
    if (!group)
        return ai->GetUnit(AI_VALUE(ObjectGuid, "master target"));

    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->getSource();
        if (!member || !sServerFacade.IsAlive(member))
            continue;

        if (member->HasAura(30843))
            return true;
    }
    return false;
}