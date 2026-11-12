// 策略值实现：GlyphValues（雕文查询、天赋配置匹配与升级比较）
#include "GlyphValues.h"
#include "playerbot/RandomPlayerbotMgr.h"
#include "playerbot/RandomItemMgr.h"

using namespace ai;

// 遍历物品模板中的雕文物品，筛选符合职业且背包中拥有（或开启雕文作弊）的列表
std::vector<uint32> AvailableGlyphsValue::Calculate()
{
    std::vector<uint32> glyphList;
    for (auto& itemId : sRandomItemMgr.GetGlyphs(bot->getClassMask()))
    {
        const ItemPrototype* glyphProto = sObjectMgr.GetItemPrototype(itemId);

        if (glyphProto->RequiredLevel > bot->GetLevel())
            continue;

        if (!ai->HasCheat(BotCheatMask::glyph) && AI_VALUE2(uint32, "item count", ChatHelper::formatQItem(itemId)) == 0)
            continue;

        glyphList.push_back(itemId);
    }

    return glyphList;
}

// 从雕文物品原型的触发法术属性中解析对应的 Glyph ID
uint32 AvailableGlyphsValue::GetGlyphIdFromProto(const ItemPrototype* glyphProto)
{
    if (glyphProto->Class != 16)
        return 0;

    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(glyphProto->Spells[0].SpellId);

    if (!spellInfo)
        return 0;

    return spellInfo->EffectMiscValue[0];
}

// 根据 Glyph ID 与职业掩码反查对应的雕文物品原型
const ItemPrototype* AvailableGlyphsValue::GetGlyphProtoFromGlyphId(uint32 glyphId, uint32 classMask)
{
    for (auto& itemId : sRandomItemMgr.GetGlyphs(classMask))
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);

        if (!proto)
            continue;

        if (GetGlyphIdFromProto(proto) == glyphId)
            return proto;
    }

    return nullptr;
}

// 根据雕文物品 ID 判断其属于大雕文还是小雕文槽位
GlyphSlotType AvailableGlyphsValue::GetGlyphSlotTypeFromItemId(uint32 itemId)
{
#ifdef MANGOSBOT_TWO
    const ItemPrototype* glyphProto = sObjectMgr.GetItemPrototype(itemId);

    if (!glyphProto)
        return GlyphSlotType::NO_SLOT;

    uint32 glyphId = GetGlyphIdFromProto(glyphProto);

    if(!glyphId)
        return GlyphSlotType::NO_SLOT;

    GlyphPropertiesEntry const* gp = sGlyphPropertiesStore.LookupEntry(glyphId);

    if (!gp)
        return GlyphSlotType::NO_SLOT;

    if (gp->TypeFlags == 0)
        return GlyphSlotType::MAJOR_SLOT;
    
    if(gp->TypeFlags == 1)
       return GlyphSlotType::MINOR_SLOT;
#endif
    return GlyphSlotType::NO_SLOT;
}

// 根据插槽编号与角色等级判断该雕文槽位的类型及解锁状态
GlyphSlotType AvailableGlyphsValue::GetGlyphSlotTypeFromSlot(uint8 slotId, uint32 level)
{
#ifdef MANGOSBOT_TWO
    for (uint32 i = 0; i < sGlyphSlotStore.GetNumRows(); ++i)
    {
        GlyphSlotEntry const* gs = sGlyphSlotStore.LookupEntry(i);

        if (!gs)
            continue;
        
        if (!gs->Order)
            continue;

        if (gs->Order - 1 != slotId)
            continue;

        if (level < 15 && (slotId == 0 || slotId == 1))
            continue;
        else if (level < 30 && slotId == 3)
            continue;
        else if (level < 50 && slotId == 2)
            continue;
        else if (level < 70 && slotId == 4)
            continue;
        else if (level < 80 && slotId == 5)
            continue;

        return gs->TypeFlags == 0 ? GlyphSlotType::MAJOR_SLOT : GlyphSlotType::MINOR_SLOT;
    }
#endif
    return GlyphSlotType::LOCKED_SLOT;
}

// 匹配机器人当前主天赋树和等级对应的预设雕文列表
std::vector<uint32> WantedGlyphsValue::Calculate()
{
    uint32 specNo = sRandomPlayerbotMgr.GetValue(bot->GetGUIDLow(), "specNo");

    if (!specNo)
    {
        //Pick the premade spec of the same tree as the bot's tree. | 选择与机器人当前主天赋树一致的预设雕文配置
        TalentSpec oldSpec(bot);
        int currentTree = oldSpec.highestTree();
        for (auto& path : sPlayerbotAIConfig.classSpecs[bot->getClass()].talentPath)
        {
            if (path.talentSpec.back().highestTree() != currentTree)
                continue;

            specNo = path.id + 1;
            break;
        }

        if(!specNo)
            return {};
    }

    uint32 specId = specNo ? specNo - 1 : 0;

    GlyphPriorityList glyphPriorityList;
    uint32 listLevel = 999;

    for (auto& [level, glyphList] : sPlayerbotAIConfig.glyphPriorityMap[bot->getClass()][specId])
    {
        if (level < listLevel && level >= bot->GetLevel()) //Find the lowest level list that is above the bots current level. | 查找大于等于机器人当前等级的最低等级预设配置
        {
            glyphPriorityList = glyphList;
            listLevel = level;
        }
    }

    std::vector<uint32> glyphList;

    for (auto& [itemId, reqTalentSpellId] : glyphPriorityList)
    {
        if (reqTalentSpellId && !bot->HasSpell(reqTalentSpellId))
            continue;

        glyphList.push_back(itemId);
    }

    return glyphList;
}

// 读取机器人各雕文槽位当前已安装的雕文物品 ID
std::vector<uint32> EquipedGlyphsValue::Calculate()
{
    std::vector<uint32> glyphList;

    for (uint8 glyphSlot = 0; glyphSlot < 6; glyphSlot++)
    {
        uint32 glyphItemId = 0;
#ifdef MANGOSBOT_TWO
        if (uint32 glyphId = bot->GetGlyph(glyphSlot))
        {
            if (const ItemPrototype* glyphProto = GetGlyphProtoFromGlyphId(glyphId, bot->getClassMask()))
                glyphItemId = glyphProto->ItemId;
        }
#endif
        glyphList.push_back(glyphItemId);
    }

    return glyphList;
}

// 比较待评估雕文在期望列表中的顺位是否高于空槽或当前已装同类型雕文
bool GlyphIsUpgradeValue::Calculate()
{
    uint32 itemId = stoi(qualifier);

    std::vector<uint32> wantedGlyphs = AI_VALUE(std::vector<uint32>, "wanted glyphs");

    size_t wantedRank = GetWantedRank(itemId, wantedGlyphs);

    if (wantedRank == wantedGlyphs.size())
        return false;

    GlyphSlotType slotType = AvailableGlyphsValue::GetGlyphSlotTypeFromItemId(itemId);

    std::vector<uint32> equipedGlyphs = AI_VALUE(std::vector<uint32>, "equiped glyphs");

    for (uint32 slotId = 0; slotId < equipedGlyphs.size(); slotId++)
    {
        if (equipedGlyphs[slotId] == itemId)
            return false;

        if (AvailableGlyphsValue::GetGlyphSlotTypeFromSlot(slotId, bot->GetLevel()) != slotType)
            continue;

        size_t currentWantedRank = GetWantedRank(equipedGlyphs[slotId], wantedGlyphs);

        if (currentWantedRank < wantedGlyphs.size() && currentWantedRank > wantedRank)
            continue;

        return true;
    }

    return false;
}

// 获取指定雕文在期望雕文列表中的优先级下标
size_t GlyphIsUpgradeValue::GetWantedRank(uint32 itemId, const std::vector<uint32>& wantedGlyphs)
{
    auto it = std::find(wantedGlyphs.begin(), wantedGlyphs.end(), itemId);

    if (it == wantedGlyphs.end())
        return wantedGlyphs.size();

    size_t index = std::distance(wantedGlyphs.begin(), it);

    return index;
}
