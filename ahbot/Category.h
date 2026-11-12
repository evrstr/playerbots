#pragma once
#include "Config/Config.h"
#include "AhBotConfig.h"
#include "PricingStrategy.h"
#include "Entities/ItemPrototype.h"
#include "Globals/SharedDefines.h"

namespace ahbot
{
    /// 拍卖行物品分类基类，定义分类匹配、堆叠数量及定价策略接口
    class Category
    {
    public:
        Category() : pricingStrategy(NULL) {}
        virtual ~Category() { if (pricingStrategy) delete pricingStrategy; }

    public:
        /// 判断给定物品原型是否属于当前分类
        virtual bool Contains(ItemPrototype const* proto) { return false; }
        /// 获取分类内部配置键名
        virtual std::string GetName() { return typeName; }
        virtual std::string GetDisplayName() { return GetName(); }
        virtual std::string GetLabel() { return GetName(); }

        /// 根据物品品质与稀有度计算推荐上架堆叠数
        virtual uint32 GetStackCount(ItemPrototype const* proto);
        virtual uint32 GetSkillId() { return 0; }

        /// 获取或延迟创建当前分类对应的定价策略实例
        virtual PricingStrategy* GetPricingStrategy();

        virtual uint32 GetMaxAllowedAuctionCount()
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }
    protected:
        std::string typeName = "default";
        int32 defaultMaxType = 1;
    private:
        PricingStrategy *pricingStrategy;
    };

    /// 消耗品分类（药水、食物、卷轴、绷带等）
    class Consumable : public Category
    {
    public:
        Consumable() : Category() {}
    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_CONSUMABLE;
        }

        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "consumables"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }
    protected:
        std::string typeName = "consumable";
        int32 defaultMaxType = 10;
    };

    /// 任务物品分类
    class Quest : public Category
    {
    public:
        Quest() : Category() {}
    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_QUEST;
        }
        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "quest items"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }
    protected:
        std::string typeName = "quest";
        int32 defaultMaxType = 5;
    };

    /// 商业制造与杂项材料分类（商业材料、杂项、施法材料、宝石）
    class Trade : public Category
    {
    public:
        Trade() : Category() {}
    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_TRADE_GOODS ||
                    proto->Class == ITEM_CLASS_MISC ||
                    proto->Class == ITEM_CLASS_REAGENT
#ifndef MANGOSBOT_ZERO
                ||
                    proto->Class == ITEM_CLASS_GEM
#endif
                ;
        }

        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }
    protected:
        std::string typeName = "trade";
        int32 defaultMaxType = 5;
    };

    /// 施法材料分类
    class Reagent : public Category
    {
    public:
        Reagent() : Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_REAGENT;
        }
        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "reagents"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }
    protected:
        std::string typeName = "reagent";
        int32 defaultMaxType = 1;
    };

    /// 配方与图纸分类
    class Recipe : public Category
    {
    public:
        Recipe() : Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_RECIPE;
        }
        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "recipes and patterns"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }

        virtual uint32 GetStackCount(ItemPrototype const* proto) override
        {
            return 1;
        }
    protected:
        std::string typeName = "recipe";
        int32 defaultMaxType = 1;
    };

    /// 武器与护甲装备分类（物品等级 > 1）
    class Equip : public Category
    {
    public:
        Equip() : Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return (proto->Class == ITEM_CLASS_WEAPON ||
                proto->Class == ITEM_CLASS_ARMOR) && proto->ItemLevel > 1;
        }
        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "armor and weapons"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }

        virtual uint32 GetStackCount(ItemPrototype const* proto) override
        {
            return 1;
        }
    protected:
        std::string typeName = "equip";
        int32 defaultMaxType = 1;
    };

    /// 箭袋与弹药袋分类
    class Quiver : public Category
    {
    public:
        Quiver() : Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_QUIVER && proto->ItemLevel > 1;
        }

        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "quivers and ammo poaches"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }

        virtual uint32 GetStackCount(ItemPrototype const* proto) override
        {
            return 1;
        }

    protected:
        std::string typeName = "quiver";
        int32 defaultMaxType = 1;
    };

    /// 箭矢与子弹消耗品分类
    class Projectile : public Category
    {
    public:
        Projectile() : Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_PROJECTILE;
        }

        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "projectiles"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }

        virtual uint32 GetStackCount(ItemPrototype const* proto) override
        {
            return proto->GetMaxStackSize();
        }

    protected:
        std::string typeName = "projectile";
        int32 defaultMaxType = 5;
    };

    /// 背包容器分类
    class Container : public Category
    {
    public:
        Container() : Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_CONTAINER;
        }

        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "containers"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }

        virtual uint32 GetStackCount(ItemPrototype const* proto) override
        {
            return 1;
        }

    protected:
        std::string typeName = "container";
        int32 defaultMaxType = 1;
    };

    /// 工程零件、装置与爆炸物分类
    class DevicesAndParts : public Category
    {
    public:
        DevicesAndParts() : Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) override
        {
            return proto->Class == ITEM_CLASS_TRADE_GOODS &&
                    (proto->SubClass == ITEM_SUBCLASS_PARTS ||
                    proto->SubClass == ITEM_SUBCLASS_DEVICES ||
                    proto->SubClass == ITEM_SUBCLASS_EXPLOSIVES);
        }

        virtual std::string GetName() override { return typeName; }
        virtual std::string GetDisplayName() override { return GetName(); }
        virtual std::string GetLabel() override { return "devices and explosives"; }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedAuctionCount(typeName, 5));
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(GetName(), sAhBotConfig.GetMaxAllowedItemAuctionCount(typeName, defaultMaxType));
        }

    protected:
        std::string typeName = "devices";
        int32 defaultMaxType = 1;
    };

    /// 物品品质分类包装器，将基础分类与特定物品品质（白/绿/蓝/紫等）组合
    class QualityCategoryWrapper : public Category
    {
    public:
        QualityCategoryWrapper(Category* category, uint32 quality);

    public:
        virtual bool Contains(ItemPrototype const* proto) override;
        virtual std::string GetName() override { return category->GetName(); }
        virtual std::string GetDisplayName() override { return combinedName; }
        virtual std::string GetLabel() override { return category->GetLabel(); }
        virtual uint32 GetStackCount(ItemPrototype const* proto) override { return category->GetStackCount(proto); }
        virtual PricingStrategy* GetPricingStrategy() { return category->GetPricingStrategy(); }
        virtual uint32 GetSkillId() { return category->GetSkillId(); }

        virtual uint32 GetMaxAllowedAuctionCount() override
        {
            return sAhBotConfig.GetMaxAllowedAuctionCount(combinedName, category->GetMaxAllowedAuctionCount());
        }

        virtual uint32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto) override
        {
            return sAhBotConfig.GetMaxAllowedItemAuctionCount(combinedName, category->GetMaxAllowedItemAuctionCount(proto));
        }

    private:
        uint32 quality;
        Category* category;
        std::string combinedName;
    };
};
