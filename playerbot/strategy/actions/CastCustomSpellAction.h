#pragma once
#include "ListSpellsAction.h"
#include "playerbot/strategy/values/CraftValues.h"
#include "playerbot/strategy/values/ItemUsageValue.h"
#include "GenericActions.h"
#include "playerbot/RandomItemMgr.h"

namespace ai
{
    /// 自定义施法指令动作：通过聊天命令让机器人对目标施放指定法术
    class CastCustomSpellAction : public ChatCommandAction, public Qualified
    {
    public:
        /// 构造函数：初始化自定义施法指令动作
        CastCustomSpellAction(PlayerbotAI* ai, std::string name = "cast") : ChatCommandAction(ai, name), Qualified() {}
        /// 执行动作主逻辑（自定义施法指令动作）
        virtual bool Execute(Event& event) override;
        /// 将文本格式的目标或参数转换为具体数值类型
        virtual std::string castString(WorldObject* target) { return "cast"; }
        /// 获取动作或延迟的持续时间（毫秒）
        virtual uint32 getDuration() const { return 3000U; }
        /// 获取当前动作的目标名称标识（自定义施法指令动作）
        virtual std::string GetTargetName() override { return "current target"; }
    private:

        /// 对目标队友施放术士召唤仪式法术
        bool CastSummonPlayer(Player* requester, std::string command);

    protected:
        bool ncCast = false;
    };

    /// 非战斗自定义施法动作：在非战斗状态下施放指定的自定义法术
    class CastCustomNcSpellAction : public CastCustomSpellAction
    {
    public:
        /// 构造函数：初始化非战斗自定义施法动作
        CastCustomNcSpellAction(PlayerbotAI* ai, std::string name = "cast custom nc spell") : CastCustomSpellAction(ai, name) {}
        /// 判断当前状态下该动作是否可用/有效（非战斗自定义施法动作）
        virtual bool isUseful() override { return !bot->IsMoving(); }
        /// 将文本格式的目标或参数转换为具体数值类型
        virtual std::string castString(WorldObject* target) override { return "castnc" +(target ? " "+ chat->formatWorldobject(target):""); }
    };

    /// 随机施法动作：从已学法术或配方中随机挑选并施放一个法术
    class CastRandomSpellAction : public ListSpellsAction
    {
    public:
        /// 构造函数：初始化随机施法动作
        CastRandomSpellAction(PlayerbotAI* ai, std::string name = "cast random spell") : ListSpellsAction(ai, name) {}

        /// 判断是否接受指定的职业或训练法术学习
        virtual bool AcceptSpell(const SpellEntry* pSpellInfo)
        {
            bool isTradeSkill = pSpellInfo->Effect[0] == SPELL_EFFECT_CREATE_ITEM && pSpellInfo->ReagentCount[0] > 0 &&
#ifdef MANGOSBOT_ZERO
                pSpellInfo->School == 0;
#else
                pSpellInfo->SchoolMask == 1;
#endif

            bool hasCost = pSpellInfo->manaCost > 0;

            return hasCost && !isTradeSkill && (GetSpellRecoveryTime(pSpellInfo) < MINUTE * IN_MILLISECONDS || !ai->HasActivePlayerMaster());
        }

        /// 计算并返回法术或目标的施放优先级
        virtual uint32 GetSpellPriority(const SpellEntry* pSpellInfo) { return 1; }
        /// 执行动作主逻辑（随机施法动作）
        virtual bool Execute(Event& event) override;

        /// 调用底层施法接口对目标单位或坐标施放指定法术
        virtual bool castSpell(uint32 spellId, WorldObject* wo, Player* requester);
    };
       
    /// 随机制作物品动作：从专业技能配方中随机挑选并制作物品
    class CraftRandomItemAction : public CastRandomSpellAction
    {
    public:
        /// 构造函数：初始化随机制作物品动作
        CraftRandomItemAction(PlayerbotAI* ai) : CastRandomSpellAction(ai, "craft random item") {}
    public:
        /// 执行动作主逻辑（随机制作物品动作）
        virtual bool Execute(Event& event) override;
    };

    /// 随机分解物品动作：查找背包内可分解的绿色及以上装备并施放分解
    class DisenchantRandomItemAction : public CastCustomSpellAction
    {
    public:
        /// 构造函数：初始化随机分解物品动作
        DisenchantRandomItemAction(PlayerbotAI* ai) : CastCustomSpellAction(ai, "disenchant random item")  {}
        /// 判断当前状态下该动作是否可用/有效（随机分解物品动作）
        virtual bool isUseful() override { return ai->HasSkill(SKILL_ENCHANTING) && !bot->IsInCombat() && AI_VALUE2(uint32, "item count", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_DISENCHANT)) > 0; }
        /// 执行动作主逻辑（随机分解物品动作）
        virtual bool Execute(Event& event) override;
    };

    /// 处理物品动作基类：封装研磨、选矿等针对背包物品施放专业技能的通用逻辑
    class ProcessItemAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化处理物品动作基类
        ProcessItemAction(PlayerbotAI* ai, std::string name) : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（处理物品动作基类）
        virtual bool Execute(Event& event) override;
    };

    /// 研磨草药动作：对背包中满足条件的草药施放铭文研磨技能
    class MillItemAction : public ProcessItemAction
    {
    public:
        /// 构造函数：初始化研磨草药动作
        MillItemAction(PlayerbotAI* ai) : ProcessItemAction(ai, "mill") {}
    };

    /// 选矿动作：对背包中满足条件的矿石施放珠宝加工选矿技能
    class ProspectItemAction : public ProcessItemAction
    {
    public:
        /// 构造函数：初始化选矿动作
        ProspectItemAction(PlayerbotAI* ai) : ProcessItemAction(ai, "prospect") {}
    };

    /// 随机附魔动作：为当前装备或背包物品随机施放可用的附魔配方
    class EnchantRandomItemAction : public CastRandomSpellAction
    {
    public:
        /// 构造函数：初始化随机附魔动作
        EnchantRandomItemAction(PlayerbotAI* ai) : CastRandomSpellAction(ai, "enchant random item") {}
        /// 判断当前状态下该动作是否可用/有效（随机附魔动作）
        virtual bool isUseful() override { return ai->HasSkill(SKILL_ENCHANTING); }

        /// 判断是否接受指定的职业或训练法术学习
        virtual bool AcceptSpell(const SpellEntry* pSpellInfo) override
        {
            return pSpellInfo->Effect[0] == SPELL_EFFECT_ENCHANT_ITEM && pSpellInfo->ReagentCount[0] > 0;
        }

        /// 计算并返回法术或目标的施放优先级
        virtual uint32 GetSpellPriority(const SpellEntry* pSpellInfo) override
        {
            if (pSpellInfo->Effect[0] != SPELL_EFFECT_ENCHANT_ITEM)
                return 0;

            uint32 enchant_id = pSpellInfo->EffectMiscValue[0];

            Item* item = AI_VALUE2(Item*, "item for spell", pSpellInfo->Id);

            if (!item)
                return 0;

            uint32 castCount = AI_VALUE2(uint32, "has reagents for", pSpellInfo->Id);

            if (!castCount)
                return 0;

            ItemPrototype const* proto = item->GetProto();

            // Upgrade current equiped item enchantment. (升级当前已穿戴装备的附魔效果。)
            if (item->GetBagSlot() == INVENTORY_SLOT_BAG_0) 
            {
                if (HAS_AI_VALUE2("force item usage", proto->ItemId))
                    return 0;

                uint32 currentEnchnatWeight = 0;
                if (item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT))
                    currentEnchnatWeight = sRandomItemMgr.CalculateEnchantWeight(bot->getClass(), sRandomItemMgr.GetPlayerSpecId(bot), item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT));

                uint32 newEnchantWeight = sRandomItemMgr.CalculateEnchantWeight(bot->getClass(), sRandomItemMgr.GetPlayerSpecId(bot), enchant_id);

                if (currentEnchnatWeight > newEnchantWeight) // Do not replace better enchants. (不要覆盖已有的更高等级附魔。)
                    return 0;

                if (currentEnchnatWeight < newEnchantWeight) // Place better enchants. (施放更好的附魔效果。)
                    return 100;
            }

            ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", proto->ItemId);

            if (usage != ItemUsage::ITEM_USAGE_AH && usage != ItemUsage::ITEM_USAGE_BROKEN_AH && usage != ItemUsage::ITEM_USAGE_VENDOR && usage != ItemUsage::ITEM_USAGE_DISENCHANT && usage != ItemUsage::ITEM_USAGE_NONE)
                return 0;

            // Enchant for skillup (通过附魔提升专业技能点数)
            if (ShouldCraftSpellValue::SpellGivesSkillUp(pSpellInfo->Id, bot))
                return 10;

            return 0;
        }
    };
}
