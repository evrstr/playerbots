#pragma once

#include "Config/Config.h"

/// 拍卖行机器人配置管理类，负责读取 ahbot.conf 并缓存分类与价格倍率参数
class AhBotConfig
{
public:
    AhBotConfig();
    /// 获取 AhBotConfig 单例引用
    static AhBotConfig& instance()
    {
        static AhBotConfig instance;
        return instance;
    }

public:
    /// 从 ahbot.conf 加载所有全局及默认配置项
    bool Initialize();

    bool enabled;
    uint64 guid;
    uint32 updateInterval;
    uint32 historyDays, maxSellInterval;
    uint32 itemBuyMinInterval, itemBuyMaxInterval;
    uint32 itemSellMinInterval, itemSellMaxInterval;
    uint32 alwaysAvailableMoney;
    float priceMultiplier, priceQualityMultiplier;
    uint32 defaultMinPrice, stackReducePrice;
    uint32 maxItemLevel, maxRequiredLevel;
    float underPriceProbability;
    std::set<uint32> ignoreItemIds;
    std::set<uint32> ignoreVendorItemIds;
    bool sendmail;

    /// 获取指定分类的出售价格倍率
    float GetSellPriceMultiplier(std::string category)
    {
        return GetCategoryParameter(sellPriceMultipliers, "PriceMultiplier.Sell", category, 1.0f);
    }

    /// 获取指定分类的收购价格倍率
    float GetBuyPriceMultiplier(std::string category)
    {
        return GetCategoryParameter(buyPriceMultipliers, "PriceMultiplier.Buy", category, 1.0f);
    }

    /// 获取指定物品名称的价格倍率
    float GetItemPriceMultiplier(std::string name)
    {
        return GetCategoryParameter(itemPriceMultipliers, "PriceMultiplier.Item", name, 1.0f);
    }

    /// 获取指定分类在拍卖行允许的最大总上架数量
    int32 GetMaxAllowedAuctionCount(std::string category, int32 default_value)
    {
        return (int32)GetCategoryParameter(maxAuctionCount, "MaxAuctionCount", category, default_value);
    }

    /// 获取指定分类下单个物品允许的最大同时上架数量
    int32 GetMaxAllowedItemAuctionCount(std::string category, int32 default_value)
    {
        return (int32)GetCategoryParameter(maxItemAuctionCount, "MaxItemTypeCount", category, default_value);
    }    

    std::string GetStringDefault(const char* name, const char* def)
    {
        return config.GetStringDefault(name, def);
    }

    bool GetBoolDefault(const char* name, const bool def = false)
    {
        return config.GetBoolDefault(name, def);
    }

    int32 GetIntDefault(const char* name, const int32 def)
    {
        return config.GetIntDefault(name, def);
    }

    float GetFloatDefault(const char* name, const float def)
    {
        return config.GetFloatDefault(name, def);
    }

private:
    /// 读取并缓存基于分类名动态拼接的配置项浮点值
    float GetCategoryParameter(std::map<std::string, float>& cache, std::string type, std::string category, float defaultValue)
    {
        if (cache.find(category) == cache.end())
        {
            std::ostringstream out; out << "AhBot."<< type << "." << category;
            cache[category] = config.GetFloatDefault(out.str().c_str(), defaultValue);
        }

        return cache[category];
    }

private:
    Config config;
    std::map<std::string, float> sellPriceMultipliers;
    std::map<std::string, float> buyPriceMultipliers;
    std::map<std::string, float> itemPriceMultipliers;
    std::map<std::string, float> maxAuctionCount;
    std::map<std::string, float> maxItemAuctionCount;
};

#define sAhBotConfig MaNGOS::Singleton<AhBotConfig>::Instance()

