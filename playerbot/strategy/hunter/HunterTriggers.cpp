// 猎人 - 触发器实现文件 (HunterTriggers.cpp)：定义猎人增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

// 检查触发条件是否激活 (HunterNoStingsActiveTrigger)
bool HunterNoStingsActiveTrigger::IsActive()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    return target && AI_VALUE2(uint8, "health", "current target") > 40 &&
        !ai->HasAura("serpent sting", target) &&
        !ai->HasAura("scorpid sting", target) &&
        !ai->HasAura("viper sting", target);
}

// 检查触发条件是否激活 (HuntersPetDeadTrigger)
bool HuntersPetDeadTrigger::IsActive()
{
    return AI_VALUE(bool, "pet dead") && !AI_VALUE2(bool, "mounted", "self target");
}

// 检查触发条件是否激活 (HuntersPetLowHealthTrigger)
bool HuntersPetLowHealthTrigger::IsActive()
{
    Unit* pet = ai->GetUnit(AI_VALUE(ObjectGuid, "pet target"));
    return pet && AI_VALUE2(uint8, "health", "pet target") < 40 &&
        !AI_VALUE2(bool, "dead", "pet target") && !AI_VALUE2(bool, "mounted", "self target");
}

// 检查触发条件是否激活 (HunterPetNotHappy)
bool HunterPetNotHappy::IsActive()
{
    return !AI_VALUE(bool, "pet happy") && !AI_VALUE2(bool, "mounted", "self target");
}

// 检查触发条件是否激活 (ViperStingOnAttackerTrigger)
bool ViperStingOnAttackerTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (target)
    {
        const bool noStings = !ai->HasAura("serpent sting", target) &&
                              !ai->HasAura("scorpid sting", target) &&
                              !ai->HasAura("viper sting", target);
        if (noStings)
        {
            if (target->GetPower(POWER_MANA) >= 10)
            {
                return DebuffOnAttackerTrigger::IsActive();
            }
        }
    }

    return false;
}

// 检查触发条件是否激活 (SerpentStingOnAttackerTrigger)
bool SerpentStingOnAttackerTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (target)
    {
        const bool noStings = !ai->HasAura("serpent sting", target) &&
                              !ai->HasAura("scorpid sting", target) &&
                              !ai->HasAura("viper sting", target);
        if (noStings)
        {
            if (target->GetPower(POWER_MANA) < 10 || ai->HasStrategy("sting serpent", BotState::BOT_STATE_COMBAT))
            {
                return DebuffOnAttackerTrigger::IsActive();
            }
        }
    }

    return false;
}
