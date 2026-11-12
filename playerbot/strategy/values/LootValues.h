// 策略值头文件：LootValues（全服掉落表缓存、掉落率查询、背包可叠加空间与拾取/Roll 点管理）
#pragma once
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include "ItemUsageValue.h"

namespace ai
{ 
    //Cheat class copy to hack into the loot system | 通过结构体镜像访问核心战利品系统内部成员
    // 掉落组内存访问镜像类：用于读取受保护的掉落组列表字段
    class LootLootGroupAccess                               // A set of loot definitions for items (refs are not allowed)
    {
    public:
        LootStoreItemList ExplicitlyChanced;                // Entries with chances defined in DB | 在数据库中定义了固定掉落概率的条目
        LootStoreItemList EqualChanced;                     // Zero chances - every entry takes the same chance | 零概率条目（同组内均等几率分配）
    };

    // 掉落模板内存访问镜像类：用于访问非分组及分组掉落条目
    class LootTemplateAccess
    {
    public:
        typedef std::vector<LootLootGroupAccess> LootGroups;
        LootStoreItemList Entries;                          // not grouped only | 仅未分组条目
        LootGroups        Groups;                           // groups have own (optimized) processing, grouped entries go there | 分组条目由各自掉落组独立优化处理
    };

    // 战利品实例内存访问镜像类：读取当前尸体/宝箱内的掉落物品及分配状态
    class LootAccess
    {
    public:
        friend struct LootItem;
        friend class GroupLootRoll;
        friend class LootMgr;

        std::vector<LootItem*> GetLootContentFor(Player* player) const;
        uint32 GetLootStatusFor(Player const* player) const;
        bool IsLootedFor(Player const* player) const;
        bool IsLootedForAll() const;

        // What is looted | 战利品核心数据成员
        WorldObject* m_lootTarget;
        Item* m_itemTarget;
        ObjectGuid       m_guidTarget;

        LootItemList     m_lootItems;                     // store of the items contained in loot | 战利品包含的物品列表
        uint32           m_gold;                          // amount of money contained in loot | 战利品包含的金钱数量
        uint32           m_maxSlot;                       // used to increment slot index and get total items count | 最大物品槽位计数
        LootType         m_lootType;                      // internal loot type | 内部掉落类型
        ClientLootType   m_clientLootType;                // client loot type | 客户端显示的掉落类型
        LootMethod       m_lootMethod;                    // used to know what kind of check must be done at loot time | 队伍分配方式（决定拾取检查规则）
        ItemQualities    m_threshold;                     // group threshold for items | 队伍分配品质阈值
        ObjectGuid       m_masterOwnerGuid;               // master loot player or round robin owner | 队长分配或轮流拾取的当前归属玩家
        ObjectGuid       m_currentLooterGuid;             // current player for under threshold items (Round Robin) | 低于品质阈值时的轮流拾取者
        GuidSet          m_ownerSet;                      // set of all player who have right to the loot | 拥有该战利品拾取权的玩家集合
        uint32           m_maxEnchantSkill;               // used to know group right to use disenchant option | 用于判断队伍分解权限的最大附魔技能等级
        bool             m_haveItemOverThreshold;         // if at least one item in the loot is over threshold | 是否至少有一件物品达到分配阈值
        bool             m_isChecked;                     // true if at least one player received the loot content | 是否已有玩家接收了战利品内容
        bool             m_isChest;                       // chest type object have special loot right | 宝箱类对象具有特殊的拾取权限逻辑
        bool             m_isChanged;                     // true if at least one item is looted | 是否已有物品被拾取
        bool             m_isFakeLoot;                    // nothing to loot but will sparkle for empty windows | 空掉落但保留闪光提示
        GroupLootRollMap m_roll;                          // used if an item is under rolling | 当前正在 Roll 点的物品映射
        GuidSet          m_playersLooting;                // player who opened loot windows | 正在打开拾取窗口的玩家集合
        GuidSet          m_playersOpened;                 // players that have released the corpse | 已释放拾取窗口的玩家集合
        TimePoint        m_createTime;                    // create time (used to refill loot if need) | 战利品创建时间（用于按需重新填充）
    };

    //DropMap[itemId] = {entry} | 掉落映射：物品 ID 映射到来源 Entry 列表
    typedef std::unordered_multimap<uint32, int32> DropMap;    

    // 单例值计算器：构建“物品 ID -> 可由哪些容器物品开出”的反向映射表
    class ItemDropMapValue : public SingleCalculatedValue<DropMap*>
    {
    public:
        ItemDropMapValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "item drop map") {}

        virtual DropMap* Calculate() override;
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "item drop map"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns all items and the items they contain as loot.";
        }
        virtual std::vector<std::string> GetUsedValues() { return {  }; }
#endif 
    };

     //Returns the loot map of all entries | 返回所有实体的全局掉落反向映射表
    // 单例值计算器：构建“物品 ID -> 掉落生物/游戏对象/物品来源 Entry”全局映射表
    class DropMapValue : public SingleCalculatedValue<DropMap*>
    {
    public:
        DropMapValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "drop map") {}

        virtual ~DropMapValue() { delete value; }

        static LootTemplateAccess const* GetLootTemplate(ObjectGuid guid, LootType type = LOOT_CORPSE);

        virtual DropMap* Calculate() override;
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "drop map"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns all creatures and game objects and the items they drop.";
        }
        virtual std::vector<std::string> GetUsedValues() { return {  }; }
#endif 
    };

    //Returns the entries that drop a specific item | 返回会掉落指定物品的所有生物/物件 Entry 列表
    // 值计算器：查询掉落指定物品的所有生物和游戏对象 Entry 列表
    class ItemDropListValue : public SingleCalculatedValue<std::list<int32>>, public Qualified
    {
    public:
        ItemDropListValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "item drop list"), Qualified() {}

        virtual std::list<int32> Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "item drop list"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns all creatures or game objects that drop a specific item.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "drop map" }; }
#endif 
    };

    //Returns the items a specific entry can drop | 返回指定生物/物件 Entry 可掉落的全部物品列表
    // 值计算器：查询指定生物或游戏对象 Entry 可能掉落的所有物品 ID 列表
    class EntryLootListValue : public SingleCalculatedValue<std::list<uint32>>, public Qualified
    {
    public:
        EntryLootListValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "entry loot list"), Qualified() {}
        virtual std::list<uint32> Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "entry loot list"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns all the items dropped by a specific creature or game object.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    // 值计算器：计算指定实体掉落指定物品的概率百分比
    class LootChanceValue : public SingleCalculatedValue<float>, public Qualified
    {
    public:
        LootChanceValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "loot chance"), Qualified() {}
        virtual float Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "loot chance"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns the chance a specific creature or game object will drop a certain item.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    typedef std::unordered_map<ItemUsage, std::vector<uint32>> itemUsageMap;

    // 值计算器：按 ItemUsage 分类汇总指定实体的掉落物列表
    class EntryLootUsageValue : public CalculatedValue<itemUsageMap>, public Qualified
    {
    public:
        EntryLootUsageValue(PlayerbotAI* ai) : CalculatedValue(ai, "entry loot usage",2), Qualified() {}
        virtual itemUsageMap Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "entry loot usage" ; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns all the items a creature or game object drops and if the bot thinks this item is useful somehow.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "entry loot list", "item usage" }; }
#endif 
    };

    // 布尔值计算器：判断指定实体掉落物中是否包含能提升机器人装备的物品
    class HasUpgradeValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasUpgradeValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "has upgrade", 2), Qualified() {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "has upgrade"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value checks if a specific creature or game object drops an item that is an equipment upgrade for the bot.";
        }
        virtual std::vector<std::string> GetUsedValues() { return {"entry loot list"}; }
#endif 
    };


    //Move to inventoryValues.h at some point | 待办：未来移至 inventoryValues.h
    // 值计算器：计算在不消耗新背包格的情况下，背包还能容纳指定物品的叠加数量
    class StackSpaceForItem : public Uint32CalculatedValue, public Qualified
    {
    public:
        StackSpaceForItem(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "stack space for item", 2), Qualified() {}
        virtual uint32 Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "stack space for item"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "item"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns the number of items of a specific type it can store.\n"
                "Without a player bots are limited to 80% bag space and will only have space for items in existing stacks";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "bag space" , "inventory items" }; }
#endif 
    };

    // 布尔值计算器：判断指定战利品对象中是否存在机器人需要且有空间拾取的物品
    class ShouldLootObject : public BoolCalculatedValue, public Qualified
    {
    public:
        ShouldLootObject(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should loot object"), Qualified() {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "should loot object"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value checks if an lootable object might hold something the bot can loot.\n"
                "It returns true if the object has unknown loot, gold or an item it is allowed to loot and can store in an empty space or a stack of similar items.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "stack space for item" }; }
#endif 
    };

    typedef std::unordered_multimap<ObjectGuid, uint32> LootRollMap;

    // 手动设置值：跟踪机器人当前正在参与但尚未结束的组队战利品 Roll 点记录
    class ActiveRolls : public ManualSetValue<LootRollMap>
    {
    public:
        ActiveRolls(PlayerbotAI* ai) : ManualSetValue(ai, {}, "active rolls") {}
        static void CleanUp(Player* bot, LootRollMap& value, ObjectGuid guid = ObjectGuid(), uint32 slot = 0);
        virtual std::string Format() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "active rolls"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription()
        {
            return "This value contains the active rolls a bot has.\n"
                "This value is filled and emptied when bots see and do rolls.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };
}

