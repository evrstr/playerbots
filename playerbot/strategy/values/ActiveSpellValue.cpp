// 策略值实现：ActiveSpellValue（当前正在施放的法术 ID 计算）

#include "ActiveSpellValue.h"
#include "playerbot/playerbot.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

// 遍历近战、通用、自动射击及引导法术槽位，返回当前施放法术的 ID
uint32 ActiveSpellValue::Calculate()
{
    Player* bot = ai->GetBot();
    for (int type = CURRENT_MELEE_SPELL; type <= CURRENT_CHANNELED_SPELL; ++type)
    {
        Spell *spell = bot->GetCurrentSpell((CurrentSpellTypes)type);
        if (spell && spell->m_spellInfo) return spell->m_spellInfo->Id;
    }

    return 0;
}

