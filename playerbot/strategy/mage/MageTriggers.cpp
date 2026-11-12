// 法师 - 触发器实现文件 (MageTriggers.cpp)：定义法师增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "MageTriggers.h"
#include "MageActions.h"

using namespace ai;

// 检查触发条件是否激活 (AnyMageArmorTrigger)
bool AnyMageArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("ice armor", target) &&
           !ai->HasAura("frost armor", target) &&
           !ai->HasAura("molten armor", target) &&
           !ai->HasAura("mage armor", target);
}

// 检查触发条件是否激活 (MageArmorTrigger)
bool MageArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("mage armor", target);
}

// 检查触发条件是否激活 (IceArmorTrigger)
bool IceArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("ice armor", target) &&
           !ai->HasAura("frost armor", target);
}

// 检查触发条件是否激活 (MoltenArmorTrigger)
bool MoltenArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("molten armor", target);
}

// 检查触发条件是否激活 (ManaShieldTrigger)
bool ManaShieldTrigger::IsActive()
{
    return !ai->HasAura("mana shield", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.mediumMana;
}

// 检查触发条件是否激活 (IceLanceTrigger)
bool IceLanceTrigger::IsActive()
{
    Unit* target = GetTarget();
    return target && ai->HasAnyAuraOf(target, "frost nova", "frostbite", NULL);
}

// 检查触发条件是否激活 (HotStreakTrigger)
bool HotStreakTrigger::IsActive()
{
    //Usage by id. By name hot streak aura doesn't work.
    return ai->HasAura(48108, bot);
}

// 检查触发条件是否激活 (FireballOrFrostfireBoltFreeTrigger)
bool FireballOrFrostfireBoltFreeTrigger::IsActive()
{
    return ai->HasAura("fireball!", bot);
}

// 检查触发条件是否激活 (NoImprovedScorchDebuffTrigger)
bool NoImprovedScorchDebuffTrigger::IsActive()
{
    if (bot->HasSpell(11095) || bot->HasSpell(12872) || bot->HasSpell(12873))
    {
        return DebuffTrigger::IsActive();
    }

    return false;
}

// 检查触发条件是否激活 (ArcaneBlastTrigger)
bool ArcaneBlastTrigger::IsActive()
{
    // when not max stacks of arcane blast, this is true
    Unit* target = GetTarget();
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
    return target && !ai->HasAura(spell, target, true, checkIsOwner) && target->IsAlive();
#else
    return target && (!ai->HasAura(spell, target, true, checkIsOwner) || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.mediumMana) && target->IsAlive();
#endif
}

// 检查触发条件是否激活 (ArcaneBlastFullTrigger)
bool ArcaneBlastFullTrigger::IsActive()
{
    // when max stacks of arcane blast, this is true
    Unit* target = GetTarget();
    return target && (ai->HasAura(spell, target, true, checkIsOwner) && AI_VALUE2(uint8, "mana", "self target") <= sPlayerbotAIConfig.mediumMana) && target->IsAlive();
}
