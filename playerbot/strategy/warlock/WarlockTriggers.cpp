// 术士 - 触发器实现文件 (WarlockTriggers.cpp)：定义术士增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockActions.h"

using namespace ai;

// 检查触发条件是否激活 (DemonArmorTrigger)
bool DemonArmorTrigger::IsActive() 
{
    Unit* target = GetTarget();
    return !ai->HasAura("demon skin", target) &&
           !ai->HasAura("demon armor", target) &&
           !ai->HasAura("fel armor", target);
}

// 检查触发条件是否激活 (SpellstoneTrigger)
bool SpellstoneTrigger::IsActive() 
{
    return BuffTrigger::IsActive() && AI_VALUE2(uint32, "item count", getName()) > 0;
}

// 检查触发条件是否激活 (InfernoTrigger)
bool InfernoTrigger::IsActive()
{
    return AI_VALUE(uint8, "possible attack targets count") > 1 && bot->HasSpell(1122) && bot->HasItemCount(5565, 1) && !urand(0, 2);
}

// 检查触发条件是否激活 (CorruptionTrigger)
bool CorruptionTrigger::IsActive()
{
    Unit* target = GetTarget();
    return target && !ai->HasAura("corruption", target) && !ai->HasAura("seed of corruption", target) && !HasMaxDebuffs();
}

// 检查触发条件是否激活 (LifeTapTrigger)
bool LifeTapTrigger::IsActive()
{
    const uint32 mana = AI_VALUE2(uint8, "mana", "self target");
    if (mana <= sPlayerbotAIConfig.lowMana)
    {
        const uint32 health = AI_VALUE2(uint8, "health", "self target");
        if (health >= sPlayerbotAIConfig.lowHealth)
        {
            return true;
        }
    }

    return false;
}

// 检查触发条件是否激活 (DrainSoulTrigger)
bool DrainSoulTrigger::IsActive()
{
    // If no item cheats enabled
    if (!ai->HasCheat(BotCheatMask::item))
    {
        // Check if it has less than 5 soul shards
        if (!bot->HasItemCount(6265, 5))
        {
            // Check if it has enough bag space
            if (AI_VALUE(uint8, "bag space") > 0)
            {
                // Check if target health is less than 15%
                const uint32 targetHealth = AI_VALUE2(uint8, "health", "current target");
                if (targetHealth <= 15)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// 检查触发条件是否激活 (CorruptionOnAttackerTrigger)
bool CorruptionOnAttackerTrigger::IsActive()
{
    if (DebuffOnAttackerTrigger::IsActive())
    {
        return !ai->HasAura("seed of corruption", GetTarget(), false, true);
    }

    return false;
}

// 检查触发条件是否激活 (SeedOfCorruptionOnAttackerTrigger)
bool SeedOfCorruptionOnAttackerTrigger::IsActive()
{
    if (DebuffOnAttackerTrigger::IsActive())
    {
        return AI_VALUE(uint8, "possible attack targets count") >= 3;
    }

    return false;
}

// 检查触发条件是否激活 (NoCurseTrigger)
bool NoCurseTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (target)
    {
        return !ai->HasAura("curse of agony", target, false, true) &&
               !ai->HasAura("curse of doom", target, false, true) &&
               !ai->HasAura("curse of recklessness", target, false, true) &&
               !ai->HasAura("curse of shadow", target, false, true) &&
               !ai->HasAura("curse of the elements", target, false, true) &&
               !ai->HasAura("curse of weakness", target, false, true) &&
               !ai->HasAura("curse of tongues", target, false, true);
    }

    return false;
}

// 检查触发条件是否激活 (NoCurseOnAttackerTrigger)
bool NoCurseOnAttackerTrigger::IsActive()
{
    std::list<ObjectGuid> attackers = AI_VALUE(std::list<ObjectGuid>, "possible attack targets");
    Unit* currentTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    for (std::list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* attacker = ai->GetUnit(*i);
        if (attacker && attacker != currentTarget)
        {
            if (!ai->HasAura("curse of agony", attacker, false, true) &&
                !ai->HasAura("curse of doom", attacker, false, true) &&
                !ai->HasAura("curse of recklessness", attacker, false, true) &&
                !ai->HasAura("curse of shadow", attacker, false, true) &&
                !ai->HasAura("curse of the elements", attacker, false, true) &&
                !ai->HasAura("curse of weakness", attacker, false, true) &&
                !ai->HasAura("curse of tongues", attacker, false, true))
            {
                return true;
            }
        }
    }

    return false;
}

// 检查触发条件是否激活 (FearPvpTrigger)
bool FearPvpTrigger::IsActive()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (target && target->IsPlayer())
    {
        // Check if low health
        const uint8 health = AI_VALUE2(uint8, "health", "self target");
        if (health <= sPlayerbotAIConfig.lowHealth)
        {
            // Check if targeting bot
            if (target->GetSelectionGuid() == bot->GetObjectGuid())
            {
                // Check if the bot has feared anyone
                bool alreadyFeared = false;
                std::list<ObjectGuid> attackers = AI_VALUE(std::list<ObjectGuid>, "attackers");
                for (std::list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
                {
                    Unit* attacker = ai->GetUnit(*i);
                    if (ai->HasAura("fear", attacker, false, true))
                    {
                        alreadyFeared = true;
                        break;
                    }
                }

                if (!alreadyFeared)
                {
                    const float distance = target->GetDistance(bot);
                    return distance <= 10.0f;
                }
            }
        }
    }

    return false;
}

// 检查触发条件是否激活 (ConflagrateTrigger)
bool ConflagrateTrigger::IsActive()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (target)
    {
        // Check if immolate in target
        Aura* aura = ai->GetAura("immolate", target, true);
        if (aura)
        {
            // Check if immolate is about to expire
            if (aura->GetAuraDuration() <= 7000)
            {
                return true;
            }
        }
    }

    return false;
}

// 检查触发条件是否激活 (DemonicSacrificeTrigger)
bool DemonicSacrificeTrigger::IsActive()
{
    if (ai->HasStrategy("pet", BotState::BOT_STATE_COMBAT))
    {
        return ai->HasSpell(18788) &&
               !ai->HasAura(18789, bot) && // Burning Wish (Imp)
               !ai->HasAura(18790, bot) && // Fel Stamina (Voidwalker)
               !ai->HasAura(18791, bot) && // Touch of Shadow (Succubus)
               !ai->HasAura(18792, bot) && // Fel Energy (Felhunter)
               !ai->HasAura(35701, bot);   // Touch of Shadow (Felguard)
    }

    return false;
}

// 检查触发条件是否激活 (SoulLinkTrigger)
bool SoulLinkTrigger::IsActive()
{
    return ai->HasSpell(19028) && !ai->HasAura(19028, bot) && ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
}

// 检查触发条件是否激活 (NoSpecificPetTrigger)
bool NoSpecificPetTrigger::IsActive()
{
    Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
    if (pet)
    {
        return pet->GetEntry() != entry;
    }

    return true;
}

// SoulstoneTrigger::GetItemId 获取相关配置或目标
uint32 SoulstoneTrigger::GetItemId()
{
    uint32 itemId = 0;
    const uint32 level = bot->GetLevel();
    if (level >= 18 && level < 30)
    {
        itemId = 5232;
    }
    else if (level >= 30 && level < 40)
    {
        itemId = 16892;
    }
    else if (level >= 40 && level < 50)
    {
        itemId = 16893;
    }
    else if (level >= 50 && level < 60)
    {
        itemId = 16895;
    }
    else if (level >= 60 && level < 70)
    {
        itemId = 16896;
    }
    else if (level >= 70 && level < 76)
    {
        itemId = 22116;
    }
    else if (level >= 76)
    {
        itemId = 36895;
    }

    return itemId;
}
