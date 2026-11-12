/// 施法时间控制策略与乘数实现

#include "playerbot/playerbot.h"
#include "CastTimeStrategy.h"

#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/actions/GenericSpellActions.h"

using namespace ai;

/// 乘数判定：当当前目标处于濒危血量时，压低或禁用长读条法术优先级以防溢出与浪费
float CastTimeMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    uint8 targetHealth = AI_VALUE2(uint8, "health", "current target");
    std::string name = action->getName();

    if (action->GetTarget() != ai->GetUnit(AI_VALUE(ObjectGuid, "current target")))
        return 1.0f;

    if (targetHealth < sPlayerbotAIConfig.criticalHealth && dynamic_cast<CastSpellAction*>(action))
    {
        uint32 spellId = AI_VALUE2(uint32, "spell id", name);
        const SpellEntry* const pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
        if (!pSpellInfo) return 1.0f;

        if (spellId && pSpellInfo->Targets & TARGET_FLAG_DEST_LOCATION)
            return 1.0f;
        else if (spellId && pSpellInfo->Targets & TARGET_FLAG_SOURCE_LOCATION)
            return 1.0f;

        uint32 castTime = GetSpellCastTime(pSpellInfo, bot);
        if (spellId && castTime >= 3000)
            return 0.0f;

        if (spellId && castTime >= 1500)
            return 0.5f;

        if (spellId && castTime >= 1000)
            return 0.25f;
    }

    return 1.0f;
}

/// 初始化战斗乘数：挂载 CastTimeMultiplier
void CastTimeStrategy::InitCombatMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new CastTimeMultiplier(ai));
}
