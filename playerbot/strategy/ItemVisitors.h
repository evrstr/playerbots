#pragma once
#include "playerbot/ServerFacade.h"
#include "values/ItemUsageValue.h"

char * strstri (const char* str1, const char* str2);

namespace ai
{
    /// 背包/装备物品遍历访问者基类
    class IterateItemsVisitor
    {
    public:
        IterateItemsVisitor() {}

        virtual bool Visit(Item* item) = 0;
    };

    /// 通用物品查找访问者基类，按 Accept 条件收集匹配物品
    class FindItemVisitor : public IterateItemsVisitor {
    public:
        FindItemVisitor() : IterateItemsVisitor(), result(0) {}

        virtual bool Visit(Item* item) override
        {
            if (!Accept(item->GetProto()) && !Accept(item))
                return true;

            result.push_back(item);
            return true;
        }

        std::list<Item*>& GetResult() { return result; }

    protected:
        virtual bool Accept(const ItemPrototype* proto) = 0;
        virtual bool Accept(Item* item) { return false; };

    private:
        std::list<Item*> result;
    };

    /// 收集所有遍历到的物品
    class FindAllItemVisitor : public FindItemVisitor {
    public:
        FindAllItemVisitor() : FindItemVisitor() {}

        virtual bool Accept(const ItemPrototype* proto) override { return true; };
    };

    /// 仅收集机器人当前满足使用条件的物品
    class FindUsableItemVisitor : public FindItemVisitor {
    public:
        FindUsableItemVisitor(Player* bot) : FindItemVisitor()
        {
            this->bot = bot;
        }

        virtual bool Visit(Item* item) override
        {
            if (bot->CanUseItem(item->GetProto()) == EQUIP_ERR_OK)
                return FindItemVisitor::Visit(item);

            return true;
        }

    protected:
        Player* bot;
    };


    /// 按指定物品品质收集最多 count 个物品
    class FindItemsByQualityVisitor : public IterateItemsVisitor
    {
    public:
        FindItemsByQualityVisitor(uint32 quality, int count) : IterateItemsVisitor()
        {
            this->quality = quality;
            this->count = count;
        }

        virtual bool Visit(Item* item) override
        {
            if (item->GetProto()->Quality != quality)
                return true;

            if (result.size() >= (size_t)count)
                return false;

            result.push_back(item);
            return true;
        }

        std::list<Item*>& GetResult()
        {
            return result;
        }

    private:
        uint32 quality;
        int count;
        std::list<Item*> result;
    };

    /// 按指定品质收集可交易（非灵魂绑定）物品
    class FindItemsToTradeByQualityVisitor : public FindItemsByQualityVisitor
    {
    public:
        FindItemsToTradeByQualityVisitor(uint32 quality, int count) : FindItemsByQualityVisitor(quality, count) {}

        virtual bool Visit(Item* item) override
        {
            if (item->IsSoulBound())
                return true;

            return FindItemsByQualityVisitor::Visit(item);
        }
    };

    /// 按物品主分类与子分类收集物品
    class FindItemsByClassVisitor : public IterateItemsVisitor
    {
    public:
        FindItemsByClassVisitor(uint32 itemClass, uint32 itemSubClass)
            : IterateItemsVisitor(), itemClass(itemClass), itemSubClass(itemSubClass) {}

        virtual bool Visit(Item* item) override
        {
            if (item->GetProto()->Class != itemClass || item->GetProto()->SubClass != itemSubClass)
                return true;

            result.push_back(item);
            return true;
        }

        std::list<Item*>& GetResult()
        {
            return result;
        }

    private:
        uint32 itemClass;
        uint32 itemSubClass;
        std::list<Item*> result;
    };

    /// 按分类收集可交易（非灵魂绑定）物品
    class FindItemsToTradeByClassVisitor : public IterateItemsVisitor
    {
    public:
        FindItemsToTradeByClassVisitor(uint32 itemClass, uint32 itemSubClass, int count)
            : IterateItemsVisitor(), count(count), itemClass(itemClass), itemSubClass(itemSubClass) {}

        virtual bool Visit(Item* item) override
        {
            if (item->IsSoulBound())
                return true;

            if (item->GetProto()->Class != itemClass || item->GetProto()->SubClass != itemSubClass)
                return true;

            if (result.size() >= (size_t)count)
                return false;

            result.push_back(item);
            return true;
        }

        std::list<Item*>& GetResult()
        {
            return result;
        }

    private:
        uint32 itemClass;
        uint32 itemSubClass;
        int count;
        std::list<Item*> result;
    };

    /// 统计指定物品 ID 的总数量
    class QueryItemCountVisitor : public IterateItemsVisitor
    {
    public:
        QueryItemCountVisitor(uint32 itemId)
        {
            count = 0;
            this->itemId = itemId;
        }

        virtual bool Visit(Item* item) override
        {
            if (item->GetProto()->ItemId == itemId)
                count += item->GetCount();

            return true;
        }

        int GetCount() { return count; }

    protected:
        int count;
        uint32 itemId;
    };


    /// 按名称子串统计物品总数量
    class QueryNamedItemCountVisitor : public QueryItemCountVisitor
    {
    public:
        QueryNamedItemCountVisitor(std::string name) : QueryItemCountVisitor(0)
        {
            this->name = name;
        }

        virtual bool Visit(Item* item) override
        {
            const ItemPrototype* proto = item->GetProto();
            if (proto && !proto->Name1 && strstri(proto->Name1, name.c_str()))
                count += item->GetCount();

            return true;
        }

    private:
        std::string name;
    };

    /// 按名称子串查找物品
    class FindNamedItemVisitor : public FindItemVisitor {
    public:
        FindNamedItemVisitor(Player* bot, std::string name) : FindItemVisitor()
        {
            this->name = name;
        }

        virtual bool Accept(const ItemPrototype* proto) override
        {
            return proto && proto->Name1 && strstri(proto->Name1, name.c_str());
        }

    private:
        std::string name;
    };

    /// 按精确物品 ID 查找物品
    class FindItemByIdVisitor : public FindItemVisitor {
    public:
        FindItemByIdVisitor(uint32 id) : FindItemVisitor()
        {
            this->id = id;
        }

        virtual bool Accept(const ItemPrototype* proto) override
        {
            return proto->ItemId == id;
        }

    private:
        uint32 id;
    };

    /// 按物品 ID 集合查找物品
    class FindItemByIdsVisitor : public FindItemVisitor {
    public:
        FindItemByIdsVisitor(ItemIds ids) : FindItemVisitor()
        {
            this->ids = ids;
        }

        virtual bool Accept(const ItemPrototype* proto) override
        {
            return ids.find(proto->ItemId) != ids.end();
        }

    private:
        ItemIds ids;
    };

    /// 查找可装备至指定装备槽位的物品
    class FindItemBySlotVisitor : public FindItemVisitor {
    public:
        FindItemBySlotVisitor(Player* bot, uint32 slot) : FindItemVisitor()
        {
            this->bot = bot;
            this->slot = slot;
        }

        virtual bool Accept(const ItemPrototype* proto) override
        {
            uint8 eslot = bot->FindEquipSlot(proto, NULL_SLOT, true);
            return slot == eslot;
        }

    private:
        uint32 slot;
        Player* bot;
    };

    /// 汇总所有物品 ID 的堆叠总数及绑定状态
    class ListItemsVisitor : public IterateItemsVisitor
    {
    public:
        ListItemsVisitor() : IterateItemsVisitor() {}

        std::map<uint32, int> items;
        std::map<uint32, bool> soulbound;

        virtual bool Visit(Item* item) override
        {
            uint32 id = item->GetProto()->ItemId;

            if (items.find(id) == items.end())
                items[id] = 0;

            items[id] += item->GetCount();
            soulbound[id] = item->IsSoulBound();
            return true;
        }
    };

    /// 按品质统计物品件数分布
    class ItemCountByQuality : public IterateItemsVisitor
    {
    public:
        ItemCountByQuality() : IterateItemsVisitor()
        {
            for (uint32 i = 0; i < MAX_ITEM_QUALITY; ++i)
                count[i] = 0;
        }

        virtual bool Visit(Item* item) override
        {
            count[item->GetProto()->Quality]++;
            return true;
        }

    public:
        std::map<uint32, int> count;
    };


    /// 查找具有指定法术效果（如回血/回蓝）的可使用药水或合剂
    class FindPotionVisitor : public FindUsableItemVisitor
    {
    public:
        FindPotionVisitor(Player* bot, uint32 effectId) : FindUsableItemVisitor(bot), effectId(effectId) {}

        virtual bool Accept(const ItemPrototype* proto) override
        {
            if (proto->Class == ITEM_CLASS_CONSUMABLE && (proto->SubClass == ITEM_SUBCLASS_POTION || proto->SubClass == ITEM_SUBCLASS_FLASK))
            {
                for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
                {
                    const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(proto->Spells[j].SpellId);
                    if (!spellInfo)
                        continue;

                    for (int i = 0 ; i < 3; i++)
                    {
                        // Energize also covers rage and energy potions, which are not mana potions. | 回能效果也包含怒气和能量药水，需限定 POWER_MANA
                        if (spellInfo->Effect[i] == effectId &&
                            (effectId != SPELL_EFFECT_ENERGIZE || spellInfo->EffectMiscValue[i] == POWER_MANA))
                            return true;
                    }
                }
            }
            return false;
        }

    private:
        uint32 effectId;
    };

    /// 查找指定法术分类的食物或饮料（可选仅限造物）
    class FindFoodVisitor : public FindUsableItemVisitor
    {
    public:
        FindFoodVisitor(Player* bot, uint32 spellCategory, bool conjured = false) : FindUsableItemVisitor(bot)
        {
            this->spellCategory = spellCategory;
            this->conjured = conjured;
        }

        virtual bool Accept(const ItemPrototype* proto) override
        {
            return proto->Class == ITEM_CLASS_CONSUMABLE &&
                (proto->SubClass == ITEM_SUBCLASS_CONSUMABLE || proto->SubClass == ITEM_SUBCLASS_FOOD) &&
                proto->Spells[0].SpellCategory == spellCategory &&
                (!conjured || proto->IsConjuredConsumable());
        }

    private:
        uint32 spellCategory;
        bool conjured;
    };

    /// 查找可召唤坐骑的物品
    class FindMountVisitor : public FindUsableItemVisitor
    {
    public:
        FindMountVisitor(Player* bot) : FindUsableItemVisitor(bot) {}

        virtual bool Accept(const ItemPrototype* proto) override
        {

#ifdef MANGOSBOT_TWO
            if (proto->Spells[0].SpellId == SPELL_ID_GENERIC_LEARN_PET && bot->HasSpell(proto->Spells[1].SpellId))
                return false; //Do not include mount items the bot already learned. (跳过已学会的坐骑物品)
#endif

            for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
            {
                if (proto->Spells[j].SpellId == 26656)
                    return true;

                const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(proto->Spells[j].SpellId);
                if (!spellInfo)
                    return false;

                for (int i = 0 ; i < 3; i++)
                {
                    if (spellInfo->EffectApplyAuraName[i] == SPELL_AURA_MOUNTED)
                        return true;
                }
            }

            return false;
        }

    private:
        uint32 effectId;
    };

    /// 查找可召唤小宠物的物品
    class FindPetVisitor : public FindUsableItemVisitor
    {
    public:
        FindPetVisitor(Player* bot) : FindUsableItemVisitor(bot) {}

        virtual bool Accept(const ItemPrototype* proto) override
        {
            if (proto->Class == ITEM_CLASS_MISC)
            {
                for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
                {
                    const SpellEntry* const spellInfo = sServerFacade.LookupSpellInfo(proto->Spells[j].SpellId);
                    if (!spellInfo)
                        return false;

                    for (int i = 0 ; i < 3; i++)
                    {
#ifdef MANGOSBOT_ZERO
                        if (spellInfo->Effect[i] == SPELL_EFFECT_SUMMON_CRITTER)
#else
#ifdef MANGOSBOT_ONE
                        if (spellInfo->Effect[i] == SPELL_EFFECT_97)
#else
                        if (spellInfo->Effect[i] == SPELL_EFFECT_SUMMON_PET)
#endif
#endif
                            return true;
                    }
                }
            }
            return false;
        }

    };

    /// 查找匹配远程武器类型的可用弹药（箭矢/子弹/投掷武器）
    class FindAmmoVisitor : public FindUsableItemVisitor
    {
    public:
        FindAmmoVisitor(Player* bot, uint32 weaponType) : FindUsableItemVisitor(bot)
        {
            this->weaponType = weaponType;
        }

        virtual bool Accept(const ItemPrototype* proto) override
        {
            if (proto->Class == ITEM_CLASS_PROJECTILE)
            {
                uint32 subClass = 0;
                switch (weaponType)
                {
                case ITEM_SUBCLASS_WEAPON_GUN:
                    subClass = ITEM_SUBCLASS_BULLET;
                    break;
                case ITEM_SUBCLASS_WEAPON_BOW:
                case ITEM_SUBCLASS_WEAPON_CROSSBOW:
                    subClass = ITEM_SUBCLASS_ARROW;
                    break;
                }

                if (!subClass)
                    return false;

                if (proto->SubClass == subClass)
                    return true;
            }

            if (weaponType == ITEM_SUBCLASS_WEAPON_THROWN && proto->SubClass == ITEM_SUBCLASS_WEAPON_THROWN)
                return true;

            return false;
        }
    private:
        uint32 weaponType;
    };

    /// 查找可使用的任务物品
    class FindQuestItemVisitor : public FindUsableItemVisitor
    {
    public:
        FindQuestItemVisitor(Player* bot) : FindUsableItemVisitor(bot) {}

        virtual bool Accept(const ItemPrototype* proto) override
        {
            if (proto->Class == ITEM_CLASS_QUEST)
            {
                return true;
            }
            return false;
        }
    };

    /// 查找可直接打开拾取且未上锁的容器类物品（如蚌壳、箱子）
    class FindOpenItemVisitor : public FindUsableItemVisitor
    {
    public:
        FindOpenItemVisitor(Player* bot) : FindUsableItemVisitor(bot) {}

        virtual bool Accept(const ItemPrototype* proto) override { return false; }

        virtual bool Accept(Item* item) override
        {
            const ItemPrototype* proto = item->GetProto();

            if(!(proto->Flags& ITEM_FLAG_HAS_LOOT))
                return false;

            uint32 spellId = 0;
            for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
            {
                if (proto->Spells[i].SpellId > 0)
                    return false;
            }

            if (proto->LockID
#ifdef MANGOSBOT_TWO                
                && !item->IsUnlocked()
#endif
                )
                return false;

            return true;
        }
    };

    /// 查找可学习的商业技能配方或图纸
    class FindRecipeVisitor : public FindUsableItemVisitor
    {
    public:
        FindRecipeVisitor(Player* bot, SkillType skill = SKILL_NONE) : FindUsableItemVisitor(bot), skill(skill) {};

        virtual bool Accept(const ItemPrototype* proto) override
        {
            if (proto->Class == ITEM_CLASS_RECIPE)
            {
                if (skill == SKILL_NONE)
                    return true;

                switch (proto->SubClass)
                {
                case ITEM_SUBCLASS_LEATHERWORKING_PATTERN:
                    return skill == SKILL_LEATHERWORKING;
                case ITEM_SUBCLASS_TAILORING_PATTERN:
                    return skill == SKILL_TAILORING;
                case ITEM_SUBCLASS_ENGINEERING_SCHEMATIC:
                    return skill == SKILL_ENGINEERING;
                case ITEM_SUBCLASS_BLACKSMITHING:
                    return skill == SKILL_BLACKSMITHING;
                case ITEM_SUBCLASS_COOKING_RECIPE:
                    return skill == SKILL_COOKING;
                case ITEM_SUBCLASS_ALCHEMY_RECIPE:
                    return skill == SKILL_ALCHEMY;
                case ITEM_SUBCLASS_FIRST_AID_MANUAL:
                    return skill == SKILL_FIRST_AID;
                case ITEM_SUBCLASS_ENCHANTING_FORMULA:
                    return skill == SKILL_ENCHANTING;
                case ITEM_SUBCLASS_FISHING_MANUAL:
                    return skill == SKILL_FISHING;
                }
            }
            return false;
        }
    private:
        SkillType skill;
    };

    /// 按 AI 计算出的物品用途(ItemUsage)筛选物品
    class FindItemUsageVisitor : public FindItemVisitor
    {
    public:
        FindItemUsageVisitor(Player* bot, ItemUsage usage = ItemUsage::ITEM_USAGE_NONE) : FindItemVisitor(), bot(bot), usage(usage) { context = bot->GetPlayerbotAI()->GetAiObjectContext();};

        void SetUsage(ItemUsage newUsage = ItemUsage::ITEM_USAGE_NONE) { usage = newUsage; }

        virtual bool Accept(const ItemPrototype* proto) override { return false; }

        virtual bool Accept(Item* item) override
        {
            if (AI_VALUE2_LAZY(ItemUsage, "item usage", ItemQualifier(item).GetQualifier()) == usage)
                return true;

            return false;
        }
    private:
        Player* bot;
        AiObjectContext* context;
        ItemUsage usage;
    };

    /// 查找应出售给 NPC 商人（或拍卖行）的物品
    class FindVendorItemsVisitor : public FindItemVisitor
    {
    public:
        FindVendorItemsVisitor(Player* bot, bool includeAH) : FindItemVisitor(), bot(bot), includeAH(includeAH) { context = bot->GetPlayerbotAI()->GetAiObjectContext(); };

        virtual bool Accept(const ItemPrototype* proto) override { return false; }

        virtual bool Accept(Item* item) override
        {
            ItemUsage usage = AI_VALUE2_LAZY(ItemUsage, "item usage", ItemQualifier(item).GetQualifier());
            if (usage == ItemUsage::ITEM_USAGE_VENDOR)
                return true;

            if (includeAH && (usage == ItemUsage::ITEM_USAGE_AH || usage == ItemUsage::ITEM_USAGE_BROKEN_AH))
                return true;

            if (usage == ItemUsage::ITEM_USAGE_NONE && item->GetProto()->SellPrice)
                return true;

            return false;
        }
    private:
        Player* bot;
        AiObjectContext* context;
        bool includeAH;
    };
}
