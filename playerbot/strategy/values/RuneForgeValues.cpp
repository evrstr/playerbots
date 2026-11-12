// 策略值实现：RuneForgeValues（死亡骑士符文附魔列表、天赋优先级匹配与状态校验）
#include "RuneForgeValues.h"
#include "playerbot/PlayerbotAI.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/values/ValueContext.h"
#include "Globals/SharedDefines.h"
#include "Server/DBCStructure.h"
#include "Spells/SpellMgr.h"

using namespace ai;

// 遍历已学法术筛选带有符文附魔效果（SPELL_EFFECT_ENCHANT_ITEM_PERMANENT）的法术
std::vector<uint32> RuneForgeSpellsValue::Calculate() {
    std::vector<uint32> spellIds;

    PlayerSpellMap const& spellMap = bot->GetSpellMap();

    for (auto& spell : spellMap) {
        uint32 spellId = spell.first;

        if (spell.second.state == PLAYERSPELL_REMOVED || spell.second.disabled || IsPassiveSpell(spellId))
            continue;

        SkillLineAbilityMapBounds bounds = sSpellMgr.GetSkillLineAbilityMapBoundsBySpellId(spellId);

        for (auto& bound = bounds.first; bound != bounds.second; ++bound) {
            SkillLineAbilityEntry const* skillLine = bound->second;

            if (!skillLine)
                continue;
#ifdef MANGOSBOT_TWO
            if (skillLine->skillId != SKILL_RUNEFORGING)
#endif
                continue;


            spellIds.push_back(spellId);
        }
    }
    return spellIds;
}

// 按邪恶/冰霜/鲜血天赋与坦克/PvP 优先级列表匹配已学会的最优符文熔铸法术
uint32 BestRuneForgeSpellValue::Calculate() {
    std::vector<uint32> available = AI_VALUE(std::vector<uint32>, "runeforge spells");

    if (available.empty()) return 0;

    //Todo add 1-handed versions | 待办：补充单手武器专用的双持符文配置
    const uint32 runeFallenCrusader = 53344;
    const uint32 runeRazorice = 53343;
    const uint32 runeCinderglacier = 53331;
    const uint32 runeStoneskinGargoyle = 62158;
    const uint32 runeSwordshattering = 53323;
    const uint32 runeSpellshattering = 53342;

    PlayerTalentSpec spec = ai->GetTalentSpec();

    if (AI_VALUE2(bool, "need quest objective", 12842))
    {
        if (ShouldRuneForgeValue::RuneForgeEnchantFromSpell(runeRazorice) == ShouldRuneForgeValue::CurrentRuneForgeEnchant(bot))
            return runeCinderglacier;
        return runeRazorice;            
    }

    bool isPvp = true;
    int32 rpgStyle = AI_VALUE2(int32, "manual saved int", "rpg style override");

    if (rpgStyle < 0)
        rpgStyle = ai->GetFixedBotNumber(BotTypeNumber::RPG_STYLE_NUMBER, 100);

    if (rpgStyle > 20) //20% of the bots use pvp runeforge. | 20% 的死亡骑士机器人选用 PvP 符文配置
        isPvp = false;

    bool isTank = ai->HasStrategy("tank", ai->GetState()) || spec == PlayerTalentSpec::TALENT_SPEC_DEATH_KNIGHT_BLOOD;

    std::vector<uint32> runeforgePriorityList;
    
    if (isPvp) {
        runeforgePriorityList.push_back(runeSwordshattering);
        runeforgePriorityList.push_back(runeSpellshattering);
    }
    if (isTank) {
        runeforgePriorityList.push_back(runeStoneskinGargoyle);
        runeforgePriorityList.push_back(runeFallenCrusader);
    }

    switch (spec) {
        case PlayerTalentSpec::TALENT_SPEC_DEATH_KNIGHT_UNHOLY:
            runeforgePriorityList.push_back(runeFallenCrusader);
            break;
        case PlayerTalentSpec::TALENT_SPEC_DEATH_KNIGHT_FROST:
            runeforgePriorityList.push_back(runeRazorice);
            runeforgePriorityList.push_back(runeCinderglacier);
            runeforgePriorityList.push_back(runeFallenCrusader);
            break;
        case PlayerTalentSpec::TALENT_SPEC_DEATH_KNIGHT_BLOOD:
            runeforgePriorityList.push_back(runeStoneskinGargoyle);
            runeforgePriorityList.push_back(runeFallenCrusader);
            break;
        default:
            break;
    }
    // General DPS fallback | 通用 DPS 符文兜底顺序
    runeforgePriorityList.push_back(runeFallenCrusader);
    runeforgePriorityList.push_back(runeRazorice);
    runeforgePriorityList.push_back(runeCinderglacier);
    runeforgePriorityList.push_back(runeStoneskinGargoyle);
    runeforgePriorityList.push_back(runeSwordshattering);
    runeforgePriorityList.push_back(runeSpellshattering);
    
    for (auto& wantRune : runeforgePriorityList)
    {
        if (std::find(available.begin(), available.end(), wantRune) == available.end())
            continue;

        return wantRune;
    }

    return available.front();
}

// 比较当前主手武器符文附魔 ID 与推荐最佳符文附魔 ID 是否一致
bool ShouldRuneForgeValue::Calculate() {
    uint32 bestSpell = AI_VALUE(uint32, "best runeforge spell");

    if (!bestSpell) 
        return false;

    uint32 bestEnchantId = RuneForgeEnchantFromSpell(bestSpell);

    MANGOS_ASSERT(bestEnchantId); //Runeforge spell does not have enchant id. | 断言：符文熔铸法术必须包含有效附魔 ID

    int32 currentEnchantId = CurrentRuneForgeEnchant(bot);

    if (currentEnchantId < 0) //No (correct) weapon. | 未装备合适的主手武器
        return false;

    return currentEnchantId != bestEnchantId;
} 

// 从符文熔铸法术信息中提取对应的永久附魔 ID
uint32 ShouldRuneForgeValue::RuneForgeEnchantFromSpell(uint32 spellId)
{
    const SpellEntry* pSpellInfo = sServerFacade.LookupSpellInfo(spellId);

    if (!pSpellInfo)
        return 0;

    return pSpellInfo->EffectMiscValue[0];
}

// 读取机器人当前主手武器上的永久附魔 ID（无主手武器返回 -1）
int32 ShouldRuneForgeValue::CurrentRuneForgeEnchant(Player* bot)
{
    Item* weapon = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
    if (!weapon)
        return -1;

    if (weapon->GetProto()->ItemLevel < 40)
        return -1;

    if (weapon->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 && weapon->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 && weapon->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM)
        return -1;

    return weapon->GetEnchantmentId(PERM_ENCHANTMENT_SLOT);
}