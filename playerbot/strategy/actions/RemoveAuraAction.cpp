
#include "playerbot/playerbot.h"
#include "RemoveAuraAction.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

/// 执行动作主逻辑（移除指定光环动作）
bool RemoveAuraAction::Execute(Event& event)
{
    std::string spell = aura;
    if (spell.empty())
    {
        spell = event.getParam();
    }
    
    return ai->RemoveAura(spell);
}
