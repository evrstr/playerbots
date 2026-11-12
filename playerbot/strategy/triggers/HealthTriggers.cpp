/// 生命值区间与治疗状态触发器实现

#include "playerbot/playerbot.h"
#include "HealthTriggers.h"

using namespace ai;

/// 获取目标当前生命值百分比
float HealthInRangeTrigger::GetValue()
{
    return AI_VALUE2(uint8, "health", GetTargetName());
}

/// 检测目标生命值是否满足区间条件（若启用 preheal 策略则扣除即将到来的伤害）
bool HealthInRangeTrigger::IsActive()
{
    bool healthCheck = false;
    if (ai->HasStrategy("preheal", BotState::BOT_STATE_COMBAT))
    {
        Unit* target = GetTarget();
        if (target)
        {
            uint32 incDmg = AI_VALUE2(uint32, "incoming damage", GetTargetName());
            if (incDmg)
            {
                float healthPercent = GetValue();
                float incDmgPercent = float(float(incDmg) / float(target->GetMaxHealth())) * 100;
                float healthPredict = healthPercent;
                if (incDmgPercent >= healthPercent)
                    healthPredict = 0.f;
                else
                    healthPredict = healthPercent - incDmgPercent;

                healthCheck = healthPredict < maxValue && healthPredict >= minValue;
                if (healthCheck && ai->HasStrategy("debug", BotState::BOT_STATE_NON_COMBAT))
                {
                    std::string msg = GetTargetName() + " hp: " + std::to_string(healthPercent) + ", predicted: " + std::to_string(healthPredict);
                    ai->TellPlayerNoFacing(GetMaster(), msg);
                }
            }
            else
                healthCheck = ValueInRangeTrigger::IsActive();
        }
    }
    else
        healthCheck = ValueInRangeTrigger::IsActive();

    return healthCheck
        && !AI_VALUE2(bool, "dead", GetTargetName())
        && (!isTankRequired || (GetTarget()->IsPlayer() && ai->IsTank((Player*)GetTarget(), false)));
}

/// 检测是否存在需要复活的死亡队友
bool PartyMemberDeadTrigger::IsActive()
{
    return GetTarget();
}

/// 检测自身是否处于死亡状态
bool DeadTrigger::IsActive()
{
    return AI_VALUE2(bool, "dead", GetTargetName());
}

/// 检测受伤人数是否达到群体治疗触发数量
bool AoeHealTrigger::IsActive()
{
    return AI_VALUE2(uint8, "aoe heal", type) >= count;
}

/// 检测正在施放的治疗法术目标是否已接近满血（节省法力值并打断过量预读）
bool HealTargetFullHealthTrigger::IsActive()
{
    Spell* currentSpell = bot->GetCurrentSpell(CURRENT_GENERIC_SPELL);
    if (currentSpell && (currentSpell->getState() == SPELL_STATE_CASTING) && (currentSpell->GetCastedTime() > 0U))
    {
        // Interrupt pre casted heals if target is not injured. | 若目标并未受伤，则打断预先读条的治疗法术
        if (PlayerbotAI::IsHealSpell(currentSpell->m_spellInfo))
        {
            std::string status = "fullhp";
            if (Unit* pTarget = currentSpell->m_targets.getUnitTarget())
            {
                bool hpFull = pTarget->GetHealth() == pTarget->GetMaxHealth();
                if (!hpFull && (pTarget->GetHealthPercent() > 90.f))
                {
                    uint32 healValue = currentSpell->GetDamage();
                    uint32 needHeal = pTarget->GetMaxHealth() - pTarget->GetHealth();
                    if (healValue > needHeal && float((needHeal * 100.0f) / healValue) < 50.0f)
                    {
                        status = "almost fullhp";
                        hpFull = true;
                    }
                }
                if (hpFull)
                {
                    uint32 manaCost = currentSpell->GetPowerCost();
                    if (ai->HasStrategy("debug", BotState::BOT_STATE_NON_COMBAT))
                    {
                        std::string msg = "target " + status + ", can save " + std::to_string(manaCost) + " mana, cast left : " + std::to_string(currentSpell->GetCastedTime()) + "ms";
                        ai->TellPlayerNoFacing(GetMaster(), msg);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
