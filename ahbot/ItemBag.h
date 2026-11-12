#pragma once
#include "Category.h"
#if defined(MANGOSBOT_TWO) || MAX_EXPANSION == 2
#include "Util/Util.h"
#else
#include "Util/Util.h"
#endif

namespace ahbot
{
    /// 所有受支持拍卖物品分类的全局注册列表
    class CategoryList
    {
    public:
        CategoryList();
        virtual ~CategoryList();

        Category* operator[](int index) { return categories[index]; }
        int32 size() { return categories.size(); }
        static CategoryList instance;

    private:
        void Add(Category* category);

    private:
        std::vector<Category*> categories;
    };

    /// 对物品 ID 容器执行随机洗牌
    template<class T>
    void Shuffle(std::vector<T>& items) 
    {
        uint32 count = items.size();
        for (uint32 i = 0; i < count * 5; i++)
        {
            int i1 = urand(0, count - 1);
            int i2 = urand(0, count - 1);

            T item = items[i1];
            items[i1] = items[i2];
            items[i2] = item;
        }
    }

    /// 按分类组织的物品集合容器基类
    class ItemBag 
    {
    public:
        ItemBag();

    public:
        void Init(bool silent = false);
        std::vector<uint32>& Get(Category* category) { return content[category]; }
        int32 GetCount(Category* category) { return content[category].size(); }
        int32 GetCount(Category* category, uint32 item);
        bool Add(ItemPrototype const* proto);

    protected:
        virtual void Load() = 0;
        virtual std::string GetName() = 0;

    protected:
        std::map<Category*, std::vector<uint32> > content;
    };

    /// 可由机器人上架拍卖的物品集合（排除普通无限量NPC商人出售物品等）
    class AvailableItemsBag : public ItemBag
    {
    public:
        AvailableItemsBag() {}

    protected:
        virtual void Load() override;
        virtual std::string GetName() override { return "available"; }
    };

    /// 统计指定拍卖行当前已在架物品的容器
    class InAuctionItemsBag : public ItemBag
    {
    public:
        InAuctionItemsBag(uint32 auctionId) : auctionId(auctionId) {}

    protected:
        virtual void Load() override;
        virtual std::string GetName() override;

    private:
        uint32 auctionId;
    };
};
