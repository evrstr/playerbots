#pragma once
#include "Config/Config.h"
#include "Entities/ItemPrototype.h"

namespace ahbot
{
    class Category;

    /// 拍卖行物品定价策略基类，综合市场均价、稀有度、等级、品质与历史成交计算买卖价格
    class PricingStrategy
    {
    public:
        PricingStrategy(Category* category) : category(category) {}
        virtual ~PricingStrategy() {}

    public:
        virtual uint32 GetSellPrice(ItemPrototype const* proto, uint32 auctionHouse, bool ignoreMarket = false, std::ostringstream *explain = NULL);
        virtual uint32 GetBuyPrice(ItemPrototype const* proto, uint32 auctionHouse, std::ostringstream *explain = NULL);
        double GetMarketPrice(uint32 itemId, uint32 auctionHouse);
        virtual double GetRarityPriceMultiplier(uint32 itemId);
        virtual double GetLevelPriceMultiplier(ItemPrototype const* proto);
        static uint32 RoundPrice(double price);

    protected:
        virtual uint32 GetDefaultBuyPrice(ItemPrototype const* proto);
        virtual uint32 GetDefaultSellPrice(ItemPrototype const* proto);
        virtual double GetQualityMultiplier(ItemPrototype const* proto);
        virtual double GetCategoryPriceMultiplier(uint32 untilTime, uint32 auctionHouse);
        virtual double GetItemPriceMultiplier(ItemPrototype const* proto, uint32 untilTime, uint32 auctionHouse);
        double GetMultiplier(double count, double firstBuyTime, double lastBuyTime);
        double CalculatePrice(std::ostringstream *explain, ...);

    protected:
        Category* category;
    };

    /// 仅收购稀有及以上品质物品的定价策略子类
    class BuyOnlyRarePricingStrategy : public PricingStrategy
    {
    public:
        BuyOnlyRarePricingStrategy(Category* category) : PricingStrategy(category) {}

    public:
        virtual uint32 GetBuyPrice(ItemPrototype const* proto, uint32 auctionHouse, std::ostringstream *explain = NULL) override;
        virtual uint32 GetSellPrice(ItemPrototype const* proto, uint32 auctionHouse, bool ignoreMarket = false, std::ostringstream *explain = NULL) override;
    };

    /// 定价策略工厂类，根据配置名称实例化对应策略
    class PricingStrategyFactory
    {
    public:
        static PricingStrategy* Create(std::string name, Category* category)
        {
            if (name == "buyOnlyRare")
                return new BuyOnlyRarePricingStrategy(category);

            return new PricingStrategy(category);
        }
    };
};
