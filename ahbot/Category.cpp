
#include "Category.h"
#include "playerbot/RandomItemMgr.h"
#include "ItemBag.h"
#include "AhBotConfig.h"
#include "PricingStrategy.h"
#include "playerbot/ServerFacade.h"

using namespace ahbot;

// 计算上架堆叠数：精良及以上固定为 1，其余按最大堆叠与稀有度折算
uint32 Category::GetStackCount(ItemPrototype const* proto)
{
    if (proto->Quality > ITEM_QUALITY_UNCOMMON)
        return 1;

    double rarity = GetPricingStrategy()->GetRarityPriceMultiplier(proto->ItemId);
    return (uint32)std::max(1.0, proto->GetMaxStackSize() / rarity);
}

// 延迟加载并返回当前分类配置的定价策略
PricingStrategy* Category::GetPricingStrategy()
{
    if (pricingStrategy)
        return pricingStrategy;

    std::ostringstream out; out << "AhBot.PricingStrategy." << GetName();
    std::string name = sAhBotConfig.GetStringDefault(out.str().c_str(), "default");
    return pricingStrategy = PricingStrategyFactory::Create(name, this);
}

// 构造带品质后缀（gray/white/green/blue/epic）的组合分类名称
QualityCategoryWrapper::QualityCategoryWrapper(Category* category, uint32 quality) : Category(), quality(quality), category(category)
{
    std::ostringstream out; out << category->GetName() << ".";
    switch (quality)
    {
    case ITEM_QUALITY_POOR:
        out << "gray";
        break;
    case ITEM_QUALITY_NORMAL:
        out << "white";
        break;
    case ITEM_QUALITY_UNCOMMON:
        out << "green";
        break;
    case ITEM_QUALITY_RARE:
        out << "blue";
        break;
    default:
        out << "epic";
        break;
    }

    combinedName = out.str();
}

// 检查物品是否同时满足目标品质与底层分类条件
bool QualityCategoryWrapper::Contains(ItemPrototype const* proto)
{
    return proto->Quality == quality && category->Contains(proto);
}


