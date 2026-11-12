#pragma once
#include "Category.h"
#include <map>
#include <mutex>

struct ItemPrototype;
struct SpellEntry;

namespace ahbot
{
    /// 商业技能关联物品分类，按技能 ID 区分制造材料（reagent=true）与成品（reagent=false）
    class TradeSkill : public Trade
    {
    public:
        TradeSkill(uint32 skill, bool reagent) : Trade(), skill(skill), reagent(reagent) {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override;
        virtual std::string GetName() override;
        virtual std::string GetMainName();
        virtual std::string GetLabel() override;
        virtual uint32 GetSkillId() override { return skill; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(GetMainName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5)));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(GetMainName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType)));
        }
    protected:
        std::string typeName = "trade";
        int32 defaultMaxType = 5;

    private:
        bool ContainsInternal(ItemPrototype const* proto);
        bool IsCraftedBySpell(ItemPrototype const* proto, uint32 spellId);
        bool IsCraftedBy(ItemPrototype const* proto, uint32 craftId);
        bool IsCraftedBySpell(ItemPrototype const* proto, SpellEntry const *entry);
        uint32 skill;
        // Result per item id, hits and misses, so the scan runs once per item. | 按物品 ID 缓存命中与未命中结果，确保全表扫描对每个物品只执行一次。
        // Contains runs on the world thread at startup and on the AhBot update thread later. | Contains 启动时在世界线程调用，之后在 AhBot 更新线程调用，需加锁保护。
        std::map<uint32, bool> itemCache;
        std::mutex itemCacheMutex;
        bool reagent;
    };

};
