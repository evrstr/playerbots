// 策略值头文件：ItemForSpellValue（查找可作为指定法术施法目标的物品）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 值计算器：为需要选择物品目标的法术（如磨刀石、附魔、开锁等）匹配合适物品
    class ItemForSpellValue : public CalculatedValue<Item*>, public Qualified
    {
    public:
        ItemForSpellValue(PlayerbotAI* ai, std::string name = "item for spell") : CalculatedValue<Item*>(ai, name), Qualified() {}
        virtual Item* Calculate() override;

    private:
        Item* GetItemFitsToSpellRequirements(Item* itemForSpell, SpellEntry const* spellInfo);
        Item* GetItemFitsToSpellRequirements(uint8 slot, SpellEntry const *spellInfo);
    };
}
