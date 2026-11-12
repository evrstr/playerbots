// 萨满祭司 - 触发器实现文件 (ShamanTriggers.cpp)：定义萨满祭司增益、减益、冷却及状态检查触发条件

#include "playerbot/playerbot.h"
#include "ShamanTriggers.h"
#include "ShamanActions.h"

using namespace ai;

std::list<std::string> ShamanWeaponTrigger::spells;

// 检查触发条件是否激活 (ShamanWeaponTrigger)
bool ShamanWeaponTrigger::IsActive()
{
    if (spells.empty())
    {
        spells.push_back("frostbrand weapon");
        spells.push_back("rockbiter weapon");
        spells.push_back("flametongue weapon");
        spells.push_back("earthliving weapon");
        spells.push_back("windfury weapon");
    }

    for (std::list<std::string>::iterator i = spells.begin(); i != spells.end(); ++i)
    {
        uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
        if (!spellId)
            continue;

        if (AI_VALUE2(Item*, "item for spell", spellId))
            return true;
    }

    return false;
}

// 检查触发条件是否激活 (ShockTrigger)
bool ShockTrigger::IsActive()
{
    return SpellTrigger::IsActive() && !ai->HasAnyAuraOf(GetTarget(), "frost shock", "earth shock", "flame shock", NULL) && !HasMaxDebuffs();
}

// 检查触发条件是否激活 (FlameShockTrigger)
bool FlameShockTrigger::IsActive()
{
    return SpellTrigger::IsActive() && !ai->HasAnyAuraOf(GetTarget(), "flame shock", NULL) && !HasMaxDebuffs();
}
