/// 通用核心触发器实现

#include "playerbot/playerbot.h"
#include "GenericTriggers.h"
#include "playerbot/LootObjectStack.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/generic/CombatStrategy.h"
#include "playerbot/strategy/generic/PullStrategy.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "playerbot/strategy/values/AoeValues.h"
#include "Tools/Formulas.h"

#include <regex>

using namespace ai;

/// 检测法力值是否低于 5%
bool NoManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < 5;
}

/// 检测法力值是否低于低蓝线配置
bool LowManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana;
}

/// 检测法力值是否低于中蓝线配置
bool MediumManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.mediumMana;
}

/// 检测法力值是否低于 65%
bool HighManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < 65;
}

/// 检测法力值是否高于 85%
bool AlmostFullManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") > 85;
}

/// 检测怒气是否达到指定值
bool RageAvailable::IsActive()
{
    return AI_VALUE2(uint8, "rage", "self target") >= amount;
}

/// 检测能量是否达到指定值
bool EnergyAvailable::IsActive()
{
    return AI_VALUE2(uint8, "energy", "self target") >= amount;
}

/// 检测目标连击点是否达到指定数量
bool ComboPointsAvailableTrigger::IsActive()
{
    return AI_VALUE2(uint8, "combo", "current target") >= amount;
}

/// 检测坦克或成员是否对当前目标失去仇恨（排除被另一名坦克接手的情况）
bool LoseAggroTrigger::IsActive()
{
    if(!AI_VALUE2(bool, "has aggro", "current target"))
    {
        // Check if the aggro has been taken by another tank | 检查仇恨是否被另一名坦克接管
        if(ai->IsTank(bot))
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
            if(target && !target->IsPlayer())
            {
                Unit* targetsTarget = target->GetVictim();
                if(targetsTarget && targetsTarget->IsPlayer())
                {
                    Player* targetsPlayerTarget = (Player*)targetsTarget;
                    return !ai->IsTank(targetsPlayerTarget);
                }
            }
        }

        return true;
    }

    return false;
}

/// 检测自身是否持有当前目标仇恨
bool HasAggroTrigger::IsActive()
{
    return AI_VALUE2(bool, "has aggro", "current target");
}

/// 检测非 PvP 环境下血量与法力是否同时处于危险线以下
bool PanicTrigger::IsActive()
{
    return !ai->IsInPvp() &&
           AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.criticalHealth &&
           (!AI_VALUE2(bool, "has mana", "self target") || 
            AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana);
}

/// 评估敌我双方战力权重，判断野外是否遭遇以寡敌众的危局
bool OutNumberedTrigger::IsActive()
{
    // Don't trigger if the bot is a dungeon or raid | 若位于地下城或团队副本中则不触发
    if (!bot->IsInWorld() || bot->IsBeingTeleported() || bot->GetMap()->IsDungeon() || bot->GetMap()->IsRaid())
        return false;

    // Don't trigger if the bot is in a raid group | 若处于团队中则不触发
    if (bot->GetGroup() && bot->GetGroup()->IsRaidGroup())
        return false;

    // Don't trigger if the bot is in a group with a real player | 若与真人玩家组队则不触发
    if (bot->GetGroup() && ai->HasRealPlayerMaster())
        return false;

    int32 botLevel = bot->GetLevel();
    float healthMod = bot->GetHealthPercent() / 100.0f;
    uint32 friendPower = 100 + 100 * healthMod, foePower = 0;
    uint32 grayCount = 0;
    for (auto &attacker : ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid> >("attackers")->Get())
    {
        Creature* creature = ai->GetCreature(attacker);
        if (!creature)
            continue;

        if (!creature->CanAttackOnSight(bot))
            continue;

        int32 dLevel = creature->GetLevel() - botLevel;

        if (int32(creature->GetLevel()) <= int32(MaNGOS::XP::GetGrayLevel(botLevel)))
        {
            grayCount++;
            continue;
        }

        healthMod = creature->GetHealthPercent() / 100.0f;

        uint32 weight = dLevel > 3 ? 100 + (dLevel - 3) * 100 : 100;
        foePower += weight * healthMod;
    }

    if (grayCount > 10)
        foePower += 50 * grayCount;

    if (!foePower)
        return false;

    for (auto & helper : ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid> >("nearest friendly players")->Get())
    {
        Unit* player = ai->GetUnit(helper);

        if (!player || player == bot)
            continue;

        int32 dLevel = player->GetLevel() - botLevel;

        healthMod = player->GetHealthPercent() / 100.0f;

        if (dLevel > -10 && sServerFacade.GetDistance2d(bot, player) < 10.0f)
            friendPower += std::max(200 + 20 * dLevel, dLevel * 200)* healthMod;
    }

    return foePower > 2 * friendPower;
}

/// 检测目标是否存活且缺少指定增益光环
bool BuffTrigger::IsActive()
{
    Unit* target = GetTarget();
    return target && !ai->HasAura(spell, target, false, checkIsOwner) && target->IsAlive();
}

/// 检测目标是否缺少由本机器人自身施加的光环
bool MyBuffTrigger::IsActive()
{
    Unit* target = GetTarget();
    return target && !ai->HasMyAura(spell, target);
}

/// 查找缺少指定光环的友方目标
Value<ObjectGuid>* BuffOnPartyTrigger::GetTargetValue()
{
    const std::string qualifier = spell + "-" + (ignoreTanks ? "1" : "0");
    return context->GetValue<ObjectGuid>("friendly unit without aura", qualifier);
}

/// 查找缺少强效或低阶增益的小队成员
Value<ObjectGuid>* GreaterBuffOnPartyTrigger::GetTargetValue()
{
    const std::string spells = !lowerSpell.empty() ? spell + "," + lowerSpell : spell;
    const std::string qualifier = spells + "-" + (ignoreTanks ? "1" : "0");
    return context->GetValue<ObjectGuid>("party member without aura", qualifier);
}

/// 查找缺少由本机器人施加光环的小队成员
Value<ObjectGuid>* MyBuffOnPartyTrigger::GetTargetValue()
{
    const std::string qualifier = spell + "-" + (ignoreTanks ? "1" : "0");
    return context->GetValue<ObjectGuid>("party member without my aura", qualifier);
}

/// 查找缺少指定光环的小队坦克
ai::Value<ObjectGuid>* BuffOnTankTrigger::GetTargetValue()
{
    return context->GetValue<ObjectGuid>("party tank without aura", spell);
}

/// 查找缺少指定减益光环的攻击者
Value<ObjectGuid>* DebuffOnAttackerTrigger::GetTargetValue()
{
    return context->GetValue<ObjectGuid>("attacker without aura", spell);
}

/// 检测无当前目标但被敌人攻击的情况
bool NoAttackersTrigger::IsActive()
{
    return !ai->GetUnit(AI_VALUE(ObjectGuid, "current target")) && AI_VALUE(uint8, "my attacker count") > 0;
}

/// 检测当前目标是否无效
bool InvalidTargetTrigger::IsActive()
{
    return AI_VALUE2(bool, "invalid target", "current target");
}

/// 检测当前是否没有目标或处于可重新寻敌的空闲状态
bool NoTargetTrigger::IsActive()
{
    if (!ai->GetUnit(AI_VALUE(ObjectGuid, "current target")) || AI_VALUE2(bool, "invalid target", "current target"))
        return true;

    if (!sServerFacade.IsInCombat(bot) && bot->IsAlive() &&
        (bot->IsStopped() || AI_VALUE2(uint32, "time since last change", "current position") > 60) &&
        !WaitForAttackStrategy::ShouldWait(ai) &&
        !(PullStrategy::Get(ai) && PullStrategy::Get(ai)->HasPullStarted() &&
            time(0) - PullStrategy::Get(ai)->GetPullStartTime() < PullStrategy::GetMaxPullTime()) &&
        !bot->GetLootGuid() && !AI_VALUE(bool, "has available loot"))
        return true;

    return false;
}

/// 检测战斗中攻击本机器人的敌人数量是否达标
bool MyAttackerCountTrigger::IsActive()
{
    return AI_VALUE2(bool, "combat", "self target") && AI_VALUE(uint8, "my attacker count") >= amount;
}

/// 检测当前目标威胁值是否 >= 80%，并结合未来 5 秒威胁增量预测是否即将 OT
bool HighThreatTrigger::IsActive()
{
    uint8 relativeThreat = AI_VALUE2(uint8, "threat", "current target");

    if (relativeThreat >= 80)
    {
        //Watch delta. | 监控威胁值变化增量
        uint32 lastTime = MEM_AI_VALUE(float, "my threat::current target")->GetLastTime();

        if (lastTime < time(0))
        {
            float deltaThreat = LOG_AI_VALUE(float, "my threat::current target")->GetDelta(5.0f);
            float currentThreat = AI_VALUE2(float, "my threat", "current target");

            if (deltaThreat > 0)
            {
                float tankThreat = AI_VALUE2(float, "tank threat", "current target");

                float newThreat = currentThreat + deltaThreat * 5.0f; //No agro in 5 seconds. | 预估 5 秒内不会 OT

                if (newThreat < tankThreat)
                    return false;
            }
        }

        return true;
    }

    return false;
}

/// 检测当前目标威胁值是否 >= 60%
bool MediumThreatTrigger::IsActive()
{
    if (AI_VALUE2(uint8, "threat", "current target") >= 60)
        return true;

    return false;
}

/// 检测当前目标威胁值是否 >= 25%
bool SomeThreatTrigger::IsActive()
{
    if (AI_VALUE2(uint8, "threat", "current target") >= 25)
        return true;

    return false;
}

/// 检测当前目标是否基本无威胁值
bool NoThreatTrigger::IsActive()
{
    if (SomeThreatTrigger::IsActive())
        return false;

    return true;
}

/// 检测指定半径内密集分布的敌人数量是否满足 AoE 条件
bool AoeTrigger::IsActive()
{
    std::list<ObjectGuid> aoeEnemies = AoeCountValue::FindMaxDensity(bot, range);
    return aoeEnemies.size() >= amount;
}

/// 检测目标是否存活、缺少指定减益且目标减益栏未满
bool DebuffTrigger::IsActive()
{
    Unit* target = GetTarget();
    if(target && target->IsAlive())
    {
        if (!ai->HasAura(spell, target, false, checkIsOwner))
        {
            return !HasMaxDebuffs();
        }
    }

    return false;
}

/// 检查目标身上的减益数量是否已达到当前版本（60/70级）上限
bool DebuffTrigger::HasMaxDebuffs()
{
#ifdef MANGOSBOT_TWO
    return false;
#else
    Unit* target = GetTarget();
    if(target)
    {
#ifdef MANGOSBOT_ONE
        constexpr uint32 debuffLimit = 40;
#else
        constexpr uint32 debuffLimit = 16;
#endif

        return ai->GetAuras(target, false, false).size() >= debuffLimit;
    }
#endif

    return false;
}

/// 检测法术默认目标是否存在
bool SpellTrigger::IsActive()
{
    return GetTarget();
}

/// 检测法术是否可对当前目标施放
bool SpellCanBeCastedTrigger::IsActive()
{
    Unit* target = GetTarget();
    return target && ai->CanCastSpell(spell, target, true);
}

/// 检测法术是否冷却完成
bool SpellNoCooldownTrigger::IsActive()
{
    uint32 spellId = AI_VALUE2(uint32, "spell id", name);
    if (!spellId)
        return false;

    return bot->IsSpellReady(spellId);
}

/// 按配置随机倍率计算概率并在间隔后触发
bool RandomTrigger::IsActive()
{
    if (time(0) - lastCheck < sPlayerbotAIConfig.repeatDelay / 1000)
        return false;

    lastCheck = time(0);
    int k = (int)(probability / sPlayerbotAIConfig.randomChangeMultiplier);
    if (k < 1) k = 1;
    return (rand() % k) == 0;
}

/// 按逗号依次检查所有子触发器，全部激活返回 true
bool AndTrigger::IsActive()
{
    std::vector<std::string> tnames = getMultiQualifiers(getQualifier(), ",");

    for (auto tname : tnames)
    {
        Trigger* trigger1 = ai->GetAiObjectContext()->GetTrigger(tname);
        if (!trigger1 || !trigger1->IsActive())
            return false;
    }

    return true;
}

/// 返回逻辑与组合后的触发器名称
std::string AndTrigger::getName()
{
    std::string name;
    std::vector<std::string> tnames = getMultiQualifiers(getQualifier(), ",");

    for (auto tname : tnames)
    {
        if (!name.empty())
            name += " and ";
        name += tname;
    }

    return name;
}

/// 按逗号依次检查所有子触发器，任一激活返回 true
bool OrTrigger::IsActive()
{
    std::vector<std::string> tnames = getMultiQualifiers(getQualifier(), ",");

    for (auto tname : tnames)
    {
        Trigger* trigger1 = ai->GetAiObjectContext()->GetTrigger(tname);
        if (trigger1 && trigger1->IsActive())
            return true;
    }

    return false;
}

/// 返回逻辑或组合后的触发器名称
std::string OrTrigger::getName()
{
    std::string name;
    std::vector<std::string> tnames = getMultiQualifiers(getQualifier(), ",");

    for (auto tname : tnames)
    {
        if (!name.empty())
            name += " or ";
        name += tname;
    }

    return name;
}

/// 同时评估两个指定触发器
bool TwoTriggers::IsActive()
{
    if (name1.empty() || name2.empty())
        return false;

    Trigger* trigger1 = ai->GetAiObjectContext()->GetTrigger(name1);
    Trigger* trigger2 = ai->GetAiObjectContext()->GetTrigger(name2);

    if (!trigger1 || !trigger2)
        return false;

    return trigger1->IsActive() && trigger2->IsActive();
}

/// 返回双触发器组合名称
std::string TwoTriggers::getName()
{
    std::string name;
    name = name1 + " and " + name2;
    return name;
}

/// 战斗中检测是否应开启长冷却爆发技能（副本长CD保留至Boss战）
bool BoostTrigger::IsActive()
{
    if (ai->IsStateActive(BotState::BOT_STATE_COMBAT) && BuffTrigger::IsActive())
    {
        if (!ai->HasRealPlayerMaster())
        {
            return AI_VALUE(uint8, "balance") <= balance;
        }
        else
        {
            uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
            SpellEntry const* spellInfo = sServerFacade.LookupSpellInfo(spellId);
            // in instances, save long cd boosts for bosses | 在副本中保留长冷却爆发技能用于 Boss 战
            if ((bot->GetMap()->IsRaid() || bot->GetMap()->IsDungeon()) && spellInfo && spellInfo->RecoveryTime >= 5 * MINUTE * IN_MILLISECONDS)
            {
                std::list<ObjectGuid> v = context->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get();
                for (std::list<ObjectGuid>::iterator i = v.begin(); i!=v.end(); i++)
                {
                    Unit* unit = ai->GetUnit(*i);
                    if (!unit || !sServerFacade.IsAlive(unit) || unit->IsPlayer())
                        continue;

                    if (sObjectMgr.IsEncounter(unit->GetEntry(), unit->GetMapId()))
                        return true;
                }
            }
            else
                return true;
        }
    }

    return false;
}

/// 检测指定物品数量是否少于目标数量
bool ItemCountTrigger::IsActive()
{
    return AI_VALUE2(uint32, "item count", item) < uint32(count);
}

/// 检测目标正在施放的可打断法术
bool InterruptSpellTrigger::IsActive()
{
    return SpellTrigger::IsActive() && ai->IsInterruptableSpellCasting(GetTarget(), getName());
}

/// 检测敌方以自身为目标读条时是否可用法术反射/防护法术抵御
bool DeflectSpellTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    if (!target->IsNonMeleeSpellCasted(true))
        return false;

    if (!target->HasTarget(bot->GetObjectGuid()))
        return false;

    uint32 spellid = context->GetValue<uint32>("spell id", spell)->Get();
    if (!spellid)
        return false;

    SpellEntry const *deflectSpell = sServerFacade.LookupSpellInfo(spellid);
    if (!deflectSpell)
        return false;

    // warrior deflects all | 战士法术反射可反射所有法术
    if (spell == "spell reflection")
        return true;

    // human priest feedback | 人类牧师回馈
    if (spell == "feedback")
        return true;

    SpellSchoolMask deflectSchool = SpellSchoolMask(deflectSpell->EffectMiscValue[0]);
    SpellSchoolMask attackSchool = SPELL_SCHOOL_MASK_NONE;

    Spell* spell = target->GetCurrentSpell(CURRENT_GENERIC_SPELL);
    if (spell)
    {
        SpellEntry const* tarSpellInfo = spell->m_spellInfo;
        if (tarSpellInfo)
        {
            attackSchool = GetSpellSchoolMask(tarSpellInfo);
            if (deflectSchool == attackSchool)
                return true;
        }
    }
    return false;
}

/// 检测目标是否持有指定光环（支持通过正则匹配 spellid 与层数比较）
bool HasAuraTrigger::IsActive()
{
   if (!name.empty())
    {
      return ai->HasAura(name, GetTarget(), false, false, -1, false, 0, auraTypeId);
   }

   std::string str = getQualifier();
   std::regex pattern(R"(spellid::(\d+)::([^:]*)::(\d+))");
   std::smatch match;

   if (std::regex_search(str, match, pattern) && match.size() == 4)
   {
      uint32 spell_id = atoi(match[1].str().c_str());

      if (Aura* aura = ai->GetAura(spell_id, GetTarget()))
      {
         uint32 count = atoi(match[3].str().c_str());
         uint32 stack_size = aura->GetStackAmount();
         std::string comp_symb = match[2].str();

         if (comp_symb == "equal")
         {
            return stack_size == count;
         }
         else if (comp_symb == "greater or equal")
         {
            return stack_size >= count;
         }
         else if (comp_symb == "lesser or equal")
         {
            return stack_size <= count;
         }
         else if (comp_symb == "greater")
         {
            return stack_size > count;
         }
         else if (comp_symb == "lesser")
         {
            return stack_size < count;
         }
         else
         {
            return false;
         }
      }
   };

   pattern = R"(spellid::(\d+))";

   if (std::regex_search(str, match, pattern) && match.size() == 2)
   {

      uint32 spell_id = atoi(match[1].str().c_str());
      return ai->HasAura(spell_id, GetTarget());
   }

   return false;
}

/// 返回光环触发器的描述名称
std::string HasAuraTrigger::getName()
{
   if (!name.empty())
   {
      return name;
   }

   std::ostringstream ss;
   ss << "has aura with " << getQualifier();
   return ss.str();
}


/// 检测目标是否不带有指定光环
bool HasNoAuraTrigger::IsActive()
{
    return !ai->HasAura(getName(), GetTarget());
}

/// 检测是否需要切换至当前坦克的攻击目标
bool TankAssistTrigger::IsActive()
{
    if (!AI_VALUE(bool, "has attackers"))
        return false;

    Unit* currentTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (!currentTarget)
        return true;

    // do not switch if enemy target | 若存在敌对玩家目标则不切换
    Unit* enemy = ai->GetUnit(AI_VALUE(ObjectGuid, "enemy player target"));
    if (enemy)
    {
        return currentTarget != enemy;
    }

    Unit* tankTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "tank target"));
    if (!tankTarget || currentTarget == tankTarget)
        return false;
#ifdef CMANGOS
    return tankTarget->GetVictim() != ai->GetUnit(AI_VALUE(ObjectGuid, "self target"));
#endif
#ifdef MANGOS
    return tankTarget->getVictim() != ai->GetUnit(AI_VALUE(ObjectGuid, "self target"));
#endif
}

/// 检测是否触发 DPS 协助（若处于开怪等待且带有宠物则延后）
bool DpsAssistTrigger::IsActive()
{
    if (!AI_VALUE(bool, "has attackers"))
        return false;

    Unit* currentTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (!currentTarget)
        return false;

    // If owner is waiting this will trigger attack again to call for pet | 若主人正在等待开怪，则触发再次攻击逻辑以召回/同步宠物
    WaitForAttackStrategy* strategy = WaitForAttackStrategy::Get(ai);
    bool isWaitingForAttack = false;
    if (strategy)
        isWaitingForAttack = strategy->ShouldWait(ai); 
        
    Pet* pet = bot->GetPet();
    if (pet)
    {
        UnitAI* creatureAI = ((Creature*)pet)->AI();
        if (creatureAI)
        {
            if (isWaitingForAttack)
                return false;
        }
    }

    return true;
}

/// 检测是否位于当前目标身后
bool IsBehindTargetTrigger::IsActive()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    return target && AI_VALUE2(bool, "behind", "current target");
}

/// 检测是否未位于当前目标身后
bool IsNotBehindTargetTrigger::IsActive()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    return target && !AI_VALUE2(bool, "behind", "current target");
}

/// 检测是否未面向当前目标
bool IsNotFacingTargetTrigger::IsActive()
{
    return !AI_VALUE2(bool, "facing", "current target");
}

/// 检测是否需要并可以对目标施放控制（CC）技能
bool HasCcTargetTrigger::IsActive()
{
    uint32 spellid = AI_VALUE2(uint32, "spell id", getName());
    if (spellid && sServerFacade.IsSpellReady(bot, spellid))
    {
        return ai->GetUnit(AI_VALUE(ObjectGuid,"rti cc target"))  || (ai->GetUnit(AI_VALUE2(ObjectGuid, "cc target", getName())) && !ai->GetUnit(AI_VALUE2(ObjectGuid, "current cc target", getName())));
    }

    return false;
}

/// 检测机器人当前是否处于静止未移动状态
bool NoMovementTrigger::IsActive()
{
    return !AI_VALUE2(bool, "moving", "self target");
}

/// 检测附近是否不存在任何潜在可攻击目标
bool NoPossibleTargetsTrigger::IsActive()
{
    std::list<ObjectGuid> targets = AI_VALUE(std::list<ObjectGuid>, "possible targets");
    return !targets.size();
}

/// 检测当前无攻击目标但附近存在可能引到的怪物
bool PossibleAddsTrigger::IsActive()
{
    return AI_VALUE(bool, "possible adds") && !AI_VALUE(ObjectGuid, "attack target");
}

/// 检测当前目标是否偏离指定的单体 DPS 优先目标
bool NotDpsTargetActiveTrigger::IsActive()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (target)
    {
        if (target->IsPlayer())
        {
            return false;
        }

        if(sServerFacade.IsAlive(target))
        {
            // do not switch if enemy target | 若存在敌对玩家目标则不切换
            Unit* enemy = ai->GetUnit(AI_VALUE(ObjectGuid, "enemy player target"));
            if (enemy)
            {
                return target != enemy;
            }

            Unit* dps = ai->GetUnit(AI_VALUE(ObjectGuid, "dps target"));
            if (dps)
            {
                return target != dps;
            }
        }
    }

    return false;
}

/// 检测当前目标是否偏离指定的 AoE 优先目标
bool NotDpsAoeTargetActiveTrigger::IsActive()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (target)
    {
        if (target->IsPlayer())
        {
            return false;
        }

        if (sServerFacade.IsAlive(target))
        {
            // do not switch if enemy target | 若存在敌对玩家目标则不切换
            Unit* enemy = ai->GetUnit(AI_VALUE(ObjectGuid, "enemy player target"));
            if (enemy)
            {
                return target != enemy;
            }

            Unit* dps = ai->GetUnit(AI_VALUE(ObjectGuid, "dps aoe target"));
            if (dps)
            {
                return target != dps;
            }
        }
    }

    return false;
}

/// 检测是否正在游泳
bool IsSwimmingTrigger::IsActive()
{
    return AI_VALUE2(bool, "swimming", "self target");
}

/// 检测最近处是否存在额外小怪（Adds）
bool HasNearestAddsTrigger::IsActive()
{
    std::list<ObjectGuid> targets = AI_VALUE(std::list<ObjectGuid>, "nearest adds");
    return targets.size();
}

/// 检测是否持有施放对应法术所需的物品
bool HasItemForSpellTrigger::IsActive()
{
    std::string spell = getName();
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    return spellId && AI_VALUE2(Item*, "item for spell", spellId);
}


/// 检测当前目标是否与上一帧记录的旧目标不同
bool TargetChangedTrigger::IsActive()
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    Unit* oldTarget = ai->GetUnit(context->GetValue<ObjectGuid>("old target")->Get());
    Unit* target = ai->GetUnit(context->GetValue<ObjectGuid>("current target")->Get());
    return target && oldTarget != target;
}

/// 获取需要打断的敌方治疗目标
Value<ObjectGuid>* InterruptEnemyHealerTrigger::GetTargetValue()
{
    return context->GetValue<ObjectGuid>("enemy healer target", spell);
}

/// 获取需要施放减速的目标
Value<ObjectGuid>* SnareTargetTrigger::GetTargetValue()
{
    return context->GetValue<ObjectGuid>("snare target", spell);
}

/// 检测原地停留时长是否超过延迟阈值
bool StayTimeTrigger::IsActive()
{
    time_t stayTime = AI_VALUE(time_t, "stay time");
    time_t now = time(0);
    return delay && stayTime && now > stayTime + 2 * delay / 1000;
}

/// 检测当前是否处于骑乘状态
bool IsMountedTrigger::IsActive()
{
    return AI_VALUE2(bool, "mounted", "self target");
}

/// 检测是否足够靠近自身尸体以便复活
bool CorpseNearTrigger::IsActive()
{
    return bot->GetCorpse() && bot->GetCorpse()->IsWithinDistInMap(bot, CORPSE_RECLAIM_RADIUS, true);
}

/// 检测是否处于坠落/跳跃状态
bool IsFallingTrigger::IsActive()
{
#ifdef MANGOSBOT_ZERO
    return bot->HasMovementFlag(MOVEFLAG_JUMPING);
#else
    return bot->HasMovementFlag(MOVEFLAG_FALLING);
#endif
}

/// 检测是否处于高空坠落状态
bool IsFallingFarTrigger::IsActive()
{
    return bot->HasMovementFlag(MOVEFLAG_FALLINGFAR);
}

/// 检测是否受到区域性环境减益影响
bool HasAreaDebuffTrigger::IsActive()
{
    return AI_VALUE2(bool, "has area debuff", "self target");
}

/// 检测是否距离预设 Stay 停留点过远
bool ReturnToStayPositionTrigger::IsActive()
{
    PositionEntry stayPosition = AI_VALUE(PositionMap&, "position")["stay"];
    if (stayPosition.isSet())
    {
        const float distance = bot->GetDistance(stayPosition.x, stayPosition.y, stayPosition.z);
        return distance > ai->GetRange("follow");
    }

    return false;
}

/// 检测是否距离预设 Pull 拉怪点过远
bool ReturnToPullPositionTrigger::IsActive()
{
    PositionEntry pullPosition = AI_VALUE(PositionMap&, "position")["pull"];
    if (pullPosition.isSet())
    {
        const float distance = bot->GetDistance(pullPosition.x, pullPosition.y, pullPosition.z);
        return distance > ai->GetRange("follow");
    }

    return false;
}

/// 检测缺少指定增益且连击点达标
bool NoBuffAndComboPointsAvailableTrigger::IsActive()
{
    if (BuffTrigger::IsActive())
    {
        return AI_VALUE2(uint8, "combo", GetComboPointsTargetName()) >= comboPoints;
    }

    return false;
}

/// 检测是否处于 PvP 环境
bool InPvpTrigger::IsActive()
{
    return ai->IsInPvp();
}

/// 检测是否处于 PvE 环境
bool InPveTrigger::IsActive()
{
    return ai->IsInPve();
}

/// 检测是否处于团队副本中
bool InRaidFightTrigger::IsActive()
{
    return ai->IsInRaid();
}

/// 检测强效祝福目标是否有效且在同队中
bool GreaterBuffOnPartyTrigger::IsActive()
{
    Unit* target = GetTarget();
    return target && bot->IsInGroup(target);
}

/// 检测是否有敌人正以机器人为目标
bool TargetOfAttacker::IsActive()
{
    return !AI_VALUE(std::list<ObjectGuid>, "attackers targeting me").empty();
}

/// 检测距离最近的追击者是否进入指定半径
bool TargetOfAttackerInRange::IsActive()
{
    const Unit* closestAttacker = ai->GetUnit(AI_VALUE(ObjectGuid, "closest attacker targeting me"));
    return closestAttacker && bot->GetDistance(closestAttacker, true, DIST_CALC_COMBAT_REACH) <= (distance - sPlayerbotAIConfig.contactDistance);
}

/// 检测攻击者是否正在对机器人读条或引导指定类型的光环法术
bool TargetOfCastedAuraTypeTrigger::IsActive()
{
    const std::list<ObjectGuid>& attackers = AI_VALUE(std::list<ObjectGuid>, "attackers");
    for (const ObjectGuid& attackerGuid : attackers)
    {
        // Check against the given creature id | 遍历当前攻击者检查其施法
        Unit* attacker = ai->GetUnit(attackerGuid);
        if (attacker)
        {
            const Spell* auraTypeSpell = nullptr;
            const Spell* genericSpell = attacker->GetCurrentSpell(CurrentSpellTypes::CURRENT_GENERIC_SPELL);
            if (genericSpell)
            {
                const SpellEntry* spellInfo = genericSpell->m_spellInfo;
                if (spellInfo)
                {
                    for (int32 i = SpellEffectIndex::EFFECT_INDEX_0; i <= SpellEffectIndex::EFFECT_INDEX_2; i++)
                    {
                        if ((spellInfo->Effect[i] == SPELL_EFFECT_APPLY_AURA) && (spellInfo->EffectApplyAuraName[i] == auraType))
                        {
                            auraTypeSpell = genericSpell;
                            break;
                        }
                    }
                }
            }

            if (!auraTypeSpell)
            {
                const Spell* channeledSpell = attacker->GetCurrentSpell(CurrentSpellTypes::CURRENT_CHANNELED_SPELL);
                if (channeledSpell)
                {
                    const SpellEntry* spellInfo = channeledSpell->m_spellInfo;
                    if (spellInfo)
                    {
                        for (int32 i = SpellEffectIndex::EFFECT_INDEX_0; i <= SpellEffectIndex::EFFECT_INDEX_2; i++)
                        {
                            if ((spellInfo->Effect[i] == SPELL_EFFECT_APPLY_AURA) && (spellInfo->EffectApplyAuraName[i] == auraType))
                            {
                                auraTypeSpell = channeledSpell;
                                break;
                            }
                        }
                    }
                }
            }

            if (auraTypeSpell)
            {
                Unit* spellTarget = auraTypeSpell->m_targets.getUnitTarget();
                if (spellTarget == bot)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

/// 检测当前目标是否拥有指定的增益 ID
bool BuffOnTargetTrigger::IsActive()
{
    const Unit* target = GetTarget();
    return target && target->HasAura(buffID);
}

/// 检测当前目标是否存在符合指定驱散类型的光环
bool DispelOnTargetTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (target)
    {
        const uint32 dispelMask = GetDispellMask(dispelType);
        const std::vector<Aura*> auras = ai->GetAuras(target);
        for (const Aura* aura : auras)
        {
            const SpellEntry* spellInfo = aura->GetSpellProto();
            if (spellInfo && ((1 << spellInfo->Dispel) & dispelMask))
            {
                return true;
            }
        }
    }

    return false;
}

/// 检测 RTSC 模式下是否设置了跳跃位置
bool RtscJumpTrigger::IsActive()
{
    return AI_VALUE2(WorldPosition, "RTSC saved location", "jump point") && AI_VALUE2(WorldPosition, "RTSC saved location", "jump");
}

/// 检测预设目标列表或默认目标是否就绪且合法以施放法术
bool SpellTargetTrigger::IsActive()
{
    if (IsSpellReady())
    {
        // Check for assigned targets | 优先检查指定目标列表
        const std::list<ObjectGuid>& possibleTargets = AI_VALUE(std::list<ObjectGuid>, targetsValue);
        if (!possibleTargets.empty())
        {
            for (const ObjectGuid& possibleTargetGuid : possibleTargets)
            {
                if (IsTargetValid(ai->GetUnit(possibleTargetGuid)))
                {
                    return true;
                }
            }
        }
        else
        {
            // Check for the default target | 回退检查默认目标
            if (IsTargetValid(GetTarget()))
            {
                return true;
            }
        }
    }

    return false;
}

/// 检验目标单位是否在安全、视野及存活状态上有效
bool SpellTargetTrigger::IsTargetValid(Unit* target)
{
    return target &&
           ai->IsSafe(target) &&
           (bot == target || sServerFacade.GetDistance2d(bot, target) < sPlayerbotAIConfig.sightDistance) &&
           (bot->IsInGroup(target)) &&
           (!aliveCheck || !target->IsDead()) &&
           (!auraCheck || !ai->HasAura(spell, target));
}

/// 检验法术是否已学习且不在冷却中
bool SpellTargetTrigger::IsSpellReady()
{
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    return spellId && bot->IsSpellReady(spellId);
}

/// 检验目标单位是否适合使用物品（含现有光环去重检查）
bool ItemTargetTrigger::IsTargetValid(Unit* target)
{
    if (SpellTargetTrigger::IsTargetValid(target))
    {
        if (itemAuraCheck)
        {
            const uint32 itemId = GetItemId();
            const ItemPrototype* proto = sObjectMgr.GetItemPrototype(itemId);
            if (proto)
            {
                for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
                {
#ifdef MANGOSBOT_ZERO
                    if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_USE || proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_NO_DELAY_USE)
#else
                    if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_USE)
#endif
                    {
                        if (proto->Spells[i].SpellId > 0 && ai->HasAura(proto->Spells[i].SpellId, target))
                        {
                            return false;
                        }
                    }
                }

                return true;
            }
        }
        else
        {
            return true;
        }
    }

    return false;
}

/// 检验背包中目标物品是否可用且不在冷却中
bool ItemTargetTrigger::IsSpellReady()
{
    const uint32 itemId = GetItemId();
    if (!ai->HasCheat(BotCheatMask::item) && !bot->HasItemCount(itemId, 1))
        return false;

    const ItemPrototype* proto = sObjectMgr.GetItemPrototype(itemId);
    if (proto)
    {
        for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
#ifdef MANGOSBOT_ZERO
            if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_USE || proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_NO_DELAY_USE)
#else
            if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_USE)
#endif
            {
                if (proto->Spells[i].SpellId > 0)
                {
                    if (!sServerFacade.IsSpellReady(bot, proto->Spells[i].SpellId) ||
                        !sServerFacade.IsSpellReady(bot, proto->Spells[i].SpellId, itemId))
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    return false;
}

/// 遍历声望状态检查是否存在被设为“交战中”的非敌对阵营
bool AtWarTrigger::IsActive()
{
    ReputationMgr& mgr = bot->GetReputationMgr();

#ifndef MANGOSBOT_ONE
    for (uint32 id = 0; id < sFactionStore.GetNumRows(); ++id)
#else
    for (uint32 id = 0; id < sFactionStore.GetMaxEntry(); ++id)
#endif
    {
#ifndef MANGOSBOT_ONE
        const FactionEntry* factionEntry = sFactionStore.LookupEntry(id);
#else
        const FactionEntry* factionEntry = sFactionStore.LookupEntry<FactionEntry>(id);
#endif

        if (!factionEntry)
            continue;

        FactionState const* repState = mgr.GetState(factionEntry);

        if (!repState)
            continue;

        if (!(repState->Flags & FACTION_FLAG_VISIBLE))
            continue;

        if (repState->Flags & FACTION_FLAG_HIDDEN)
            continue;

        if (repState->Flags & FACTION_FLAG_INVISIBLE_FORCED)
            continue;

        if (repState->Flags & FACTION_FLAG_PEACE_FORCED)
            continue;

        if (!(repState->Flags & FACTION_FLAG_AT_WAR))
            continue;

        if (mgr.GetRank(factionEntry) < REP_HOSTILE)
            continue;

        return true;
    }

    return false;
}