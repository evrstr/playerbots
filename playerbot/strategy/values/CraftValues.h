// 策略值头文件：CraftValues（制造数据、可用制造/附魔技能及材料需求检查）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/NamedObjectContext.h"

namespace ai
{
    // 制造任务数据结构：记录制造所需材料及已收集材料数量
    class CraftData
    {
    public:
        CraftData() : itemId(0) {}

        CraftData(const CraftData& other) : itemId(other.itemId)
        {
            required.insert(other.required.begin(), other.required.end());
            obtained.insert(other.obtained.begin(), other.obtained.end());
        }

        bool IsEmpty() { return itemId == 0; }
        void Reset() { itemId = 0; }
        bool IsRequired(uint32 item) { return required.find(item) != required.end(); }

        bool IsFulfilled()
        {
            for (std::map<uint32, int>::iterator i = required.begin(); i != required.end(); ++i)
            {
                uint32 item = i->first;
                if (obtained[item] < i->second)
                    return false;
            }

            return true;
        }

        void AddObtained(uint32 itemId, uint32 count)
        {
            if (IsRequired(itemId))
            {
                obtained[itemId] += count;
            }
        }

        void Crafted(uint32 count)
        {
            for (std::map<uint32, int>::iterator i = required.begin(); i != required.end(); ++i)
            {
                uint32 item = i->first;
                if (obtained[item] >= required[item] * (int)count)
                {
                    obtained[item] -= required[item] * (int)count;
                }
            }
        }

    public:
        uint32 itemId;
        std::map<uint32, int> required, obtained;
    };

    // 手动设置值：存储机器人当前正在进行的制造任务数据
    class CraftValue : public ManualSetValue<CraftData&>
    {
    public:
        CraftValue(PlayerbotAI* ai, std::string name = "craft") : ManualSetValue<CraftData&>(ai, data, name) {}

    private:
        CraftData data;
    };

    // 值计算器：列出机器人已学会的所有商业技能制造法术 ID
    class CraftSpellsValue : public CalculatedValue<std::vector<uint32>> //All crafting spells | 所有制造类法术
    {
    public:
        CraftSpellsValue(PlayerbotAI* ai, std::string name = "craft spells", int checkInterval = 10) : CalculatedValue<std::vector<uint32>>(ai, name, checkInterval) {}
        virtual std::vector<uint32> Calculate() override;
    };

    // 值计算器：列出机器人已学会的所有附魔技能法术 ID
    class EnchantSpellsValue : public CalculatedValue<std::vector<uint32>> //All enchanting spells | 所有附魔类法术
    {
    public:
        EnchantSpellsValue(PlayerbotAI* ai, std::string name = "enchant spells", int checkInterval = 10) : CalculatedValue<std::vector<uint32>>(ai, name, checkInterval) {}
        virtual std::vector<uint32> Calculate() override;
    };

    // 值计算器：计算机器人当前材料可支持施放指定制造法术的次数
    class HasReagentsForValue : public Uint32CalculatedValue, public Qualified //Does the bot have reagents to cast this craft spell? | 检查机器人是否拥有施放该制造法术所需的材料
    {
    public:
        HasReagentsForValue(PlayerbotAI* ai, std::string name = "has reagents for", int checkInterval = 1) : Uint32CalculatedValue(ai, name, checkInterval), Qualified() {}
        virtual uint32 Calculate() override;
    };

    // 布尔值计算器：判断机器人当前是否具备材料、技能和工具以施放指定制造法术
    class CanCraftSpellValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CanCraftSpellValue(PlayerbotAI* ai, std::string name = "can craft spell", int checkInterval = 10) : BoolCalculatedValue(ai, name, checkInterval), Qualified() {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：评估施放指定制造法术是否能涨点或产生物品价值
    class ShouldCraftSpellValue : public BoolCalculatedValue, public Qualified
    {
    public:
        ShouldCraftSpellValue(PlayerbotAI* ai, std::string name = "should craft spell", int checkInterval = 10) : BoolCalculatedValue(ai, name, checkInterval), Qualified() {}
        virtual bool Calculate() override;
        static bool SpellGivesSkillUp(uint32 spellId, Player* bot);
    };
}