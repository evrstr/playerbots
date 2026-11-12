/// 省蓝（Conserve / Save Mana）策略与乘数实现

#include "playerbot/playerbot.h"
#include "ConserveManaStrategy.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/actions/GenericSpellActions.h"
#include "playerbot/strategy/values/LastSpellCastValue.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

/// 乘数判定：法力值偏低时在战斗中抑制消耗法力的额外增益法术施放
float ConserveManaMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    uint8 health = AI_VALUE2(uint8, "health", "self target");
    uint8 targetHealth = AI_VALUE2(uint8, "health", "current target");
    uint8 mana = AI_VALUE2(uint8, "mana", "self target");
    bool hasMana = AI_VALUE2(bool, "has mana", "self target");
    bool mediumMana = hasMana && mana < sPlayerbotAIConfig.mediumMana;

    std::string name = action->getName();

    if (health < sPlayerbotAIConfig.lowHealth)
        return 1.0f;

    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
    if (action->GetTarget() != target)
        return 1.0f;

    CastSpellAction* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (!spellAction)
        return 1.0f;

    std::string spell = spellAction->getName();
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (!spellInfo || spellInfo->powerType != POWER_MANA)
        return 1.0f;

    if (mediumMana && dynamic_cast<CastBuffSpellAction*>(action))
        return 0.0f;

    if (target)
    {
        if (((int)target->GetLevel() - (int)bot->GetLevel()) >= 0)
            return 1.0f;
    }

    return 1.0f;
}

/// 乘数判定：根据 mana save level 限制同一耗蓝法术的连续施放间隔
float SaveManaMultiplier::GetValue(Action* action)
{
    if (action == NULL)
        return 1.0f;

    if (action->GetTarget() != ai->GetUnit(AI_VALUE(ObjectGuid, "current target")))
        return 1.0f;

    double saveLevel = AI_VALUE(double, "mana save level");
    if (saveLevel <= 1.0)
        return 1.0f;

    CastSpellAction* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (!spellAction)
        return 1.0f;

    std::string spell = spellAction->getName();
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (!spellInfo || spellInfo->powerType != POWER_MANA)
        return 1.0f;

    int32 cost = spellInfo->manaCost;
    if (!cost)
        return 1.0f;

    time_t lastCastTime = AI_VALUE2(time_t, "last spell cast time", spell);
    if (!lastCastTime)
        return 1.0f;

    time_t elapsed = time(0) - lastCastTime;
    if ((double)elapsed < 10 * saveLevel)
        return 0.0f;

    return 1.0f;
}

/// 初始化省蓝策略战斗乘数
void ConserveManaStrategy::InitCombatMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new ConserveManaMultiplier(ai));
}
