#pragma once

#include "Category.h"
#include "ItemBag.h"
#include "playerbot/PlayerbotAIBase.h"
#include "AuctionHouse/AuctionHouseMgr.h"
#include "Entities/ObjectGuid.h"
#include "Server/WorldSession.h"


/// 拍卖行数量上限（联盟、部落、中立）
#define MAX_AUCTIONS 3
/// 拍卖行历史记录状态类型定义：过期、玩家拍得、机器人自拍、出价、买入延迟、上架延迟、发送邮件
#define AHBOT_WON_EXPIRE 0
#define AHBOT_WON_PLAYER 1
#define AHBOT_WON_SELF 2
#define AHBOT_WON_BID 3
#define AHBOT_WON_DELAY 4
#define AHBOT_SELL_DELAY 5
#define AHBOT_SENDMAIL 6

namespace ahbot
{
    /// 拍卖行机器人核心管理类，负责定时扫描拍卖行、自动竞拍/一口价购买及自动上架物品
    class AhBot
    {
    public:
        AhBot() : nextAICheckTime(0), updating(false) {}
        virtual ~AhBot();
        /// 获取 AhBot 单例引用
        static AhBot& instance()
        {
            static AhBot instance;
            return instance;
        }

    public:
        /// 处理 GM 命令行/控制台的 ahbot 指令
        static bool HandleAhBotCommand(ChatHandler* handler, char const* args);
        /// 获取配置中指定的拍卖行机器人玩家 GUID
        ObjectGuid GetAHBplayerGUID();
        /// 初始化配置、阵营映射及可用物品列表
        void Init();
        /// 世界主循环周期更新，到达间隔后启动后台线程检查拍卖行
        void Update();
        /// 在后台线程中执行一次完整的拍卖行竞拍与补货扫描
        void ForceUpdate();
        /// 解析并执行 ahbot 子命令（expire/stats/update/dump/物品ID）
        void HandleCommand(std::string command);
        /// 拍卖成交回调，记录交易历史并更新市场价格
        void Won(AuctionEntry* entry) { AddToHistory(entry); }
        /// 拍卖过期回调
        void Expired(AuctionEntry* entry) {}

        /// 获取指定分类的当前动态价格倍率
        double GetCategoryMultiplier(std::string category)
        {
            return categoryMultipliers[category] ? categoryMultipliers[category] : 1;
        }

        /// 查询物品在拍卖行中的最高参考售价
        int32 GetSellPrice(const ItemPrototype* proto);
        /// 查询物品在拍卖行中的最高参考收购价
        int32 GetBuyPrice(const ItemPrototype* proto);
        /// 根据物品稀有度获取价格倍率
        double GetRarityPriceMultiplier(const ItemPrototype* proto);
        /// 判断指定物品是否被特定商业技能使用或制作
        bool IsUsedBySkill(const ItemPrototype* proto, uint32 skillId);

    private:
        /// 扫描并回应玩家挂出的拍卖（竞拍或一口价）
        int Answer(int auction, Category* category, ItemBag* inAuctionItems);
        /// 按分类配额向指定拍卖行补充新的拍卖品
        int AddAuctions(int auction, Category* category, ItemBag* inAuctionItems);
        /// 创建并上架单个指定物品的拍卖记录
        int AddAuction(int auction, Category* category, const ItemPrototype* proto);
        /// 将机器人上架的拍卖全部标记为立即过期
        void Expire(int auction);
        /// 输出指定拍卖行当前在售数量统计
        void PrintStats(int auction);
        /// 将竞拍或成交记录写入数据库历史表
        void AddToHistory(AuctionEntry* entry, uint32 won = 0);
        /// 清理超过保留天数的历史记录
        void CleanupHistory();
        /// 计算指定阵营拍卖行机器人当前可用于收购的资金余额
        uint32 GetAvailableMoney(uint32 auctionHouse);
        /// 检查并刷新各物品分类的价格波动倍率与最大上架配额
        void CheckCategoryMultipliers();
        /// 使用移动平均更新物品在指定拍卖行的市场基准价格
        void updateMarketPrice(uint32 itemId, double price, uint32 auctionHouse);
        /// 判断指定玩家 GUID 是否属于拍卖行机器人账号角色
        bool IsBotAuction(uint32 bidder);
        /// 从对应阵营中随机选取一名机器人作为卖家或买家
        uint32 GetRandomBidder(uint32 auctionHouse);
        /// 从数据库加载随机机器人角色作为拍卖行参与者
        void LoadRandomBots();
        /// 查询指定时间窗口内机器人已应答/购买某物品的次数
        uint32 GetAnswerCount(uint32 itemId, uint32 auctionHouse, uint32 withinTime);
        /// 加载并按价格排序当前拍卖行中非机器人挂出的指定分类拍卖
        std::vector<AuctionEntry*> LoadAuctions(const AuctionHouseObject::AuctionEntryMap& auctionEntryMap, Category*& category,
                int& auction);
        /// 查找同物品其他卖家的最低竞标价与最低一口价
        void FindMinPrice(const AuctionHouseObject::AuctionEntryMap& auctionEntryMap, AuctionEntry*& entry, Item*& item, uint32* minBid,
                uint32* minBuyout);
        /// 计算或读取机器人计划对某拍卖出价的时间戳
        uint32 GetBuyTime(uint32 entry, uint32 itemId, uint32 auctionHouse, Category*& category, double priceLevel);
        /// 从历史表读取指定分类/物品的操作时间戳
        uint32 GetTime(std::string category, uint32 id, uint32 auctionHouse, uint32 type);
        /// 更新历史表中的操作调度时间戳
        void SetTime(std::string category, uint32 id, uint32 auctionHouse, uint32 type, uint32 value);
        /// 计算或读取机器人下次上架指定物品的时间戳
        uint32 GetSellTime(uint32 itemId, uint32 auctionHouse, Category*& category);
        /// 当玩家挂价过高时发送议价提醒邮件建议降价
        void CheckSendMail(uint32 bidder, uint32 price, AuctionEntry *entry);
        /// 导出所有可用物品的分类与买卖价格估算到日志
        void Dump();
        /// 清理已过期的议价邮件
        void CleanupPropositions();
        /// 批量从数据库删除指定 ID 的邮件
        void DeleteMail(std::list<uint32> buffer);

    public:
        static uint32 auctionIds[MAX_AUCTIONS];
        static uint32 auctioneers[MAX_AUCTIONS];
        static std::map<uint32, uint32> factions;

    private:
        AvailableItemsBag availableItems;
        time_t nextAICheckTime;
        std::map<std::string, double> categoryMultipliers;
        std::map<std::string, uint32> categoryMaxAuctionCount;
        std::map<std::string, uint32> categoryMaxItemAuctionCount;
        std::map<std::string, uint64> categoryMultiplierExpireTimes;
        std::map<uint32, std::vector<uint32>> bidders;
        std::set<uint32> allBidders;
        bool updating;
    };
};

#define auctionbot MaNGOS::Singleton<ahbot::AhBot>::Instance()

