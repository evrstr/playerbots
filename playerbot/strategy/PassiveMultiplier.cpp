
#include "playerbot/playerbot.h"
#include "PassiveMultiplier.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/actions/GenericSpellActions.h"

using namespace ai;

std::list<std::string> PassiveMultiplier::allowedActions;
std::list<std::string> PassiveMultiplier::allowedParts;

// 初始化被动模式下仍允许放行的管理命令与移动动作白名单
PassiveMultiplier::PassiveMultiplier(PlayerbotAI* ai) : Multiplier(ai, "passive")
{
    if (allowedActions.empty())
    {
        allowedActions.push_back("co");
        allowedActions.push_back("nc");
        allowedActions.push_back("load ai");
        allowedActions.push_back("save ai");
        allowedActions.push_back("list ai");
        allowedActions.push_back("reset ai");
        allowedActions.push_back("reset strats");
        allowedActions.push_back("reset values");
        allowedActions.push_back("check mount state");
        allowedActions.push_back("accept invitation");
        allowedActions.push_back("join");
        allowedActions.push_back("lfg");
        allowedActions.push_back("area trigger");
        allowedActions.push_back("reach area trigger");
    }

    if (allowedParts.empty())
    {
        allowedParts.push_back("follow");
        allowedParts.push_back("stay");
        allowedParts.push_back("chat shortcut");
    }
}

// 判断动作是否在白名单内或为瞬发法术，否则返回 0 予以抑制
float PassiveMultiplier::GetValue(Action* action) 
{
    if (!action)
        return 1.0f;

    std::string name = action->getName();

    for (std::list<std::string>::iterator i = allowedActions.begin(); i != allowedActions.end(); i++)
    {
        if (name == *i)
            return 1.0f;
    }

    for (std::list<std::string>::iterator i = allowedParts.begin(); i != allowedParts.end(); i++)
    {
        if (name.find(*i) != std::string::npos)
            return 1.0f;
    }

    // Instant cast actions should be allowed while passive | 被动状态下允许瞬发非引导法术
    CastSpellAction* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (spellAction)
    {
        uint32 spellId = spellAction->GetSpellID();
        const SpellEntry* pSpellInfo = spellId ? sServerFacade.LookupSpellInfo(spellId) : nullptr;
        if (pSpellInfo && GetSpellCastTime(pSpellInfo, bot) == 0 && !IsChanneledSpell(pSpellInfo))
            return 1.0f;
    }

    return 0;
}
