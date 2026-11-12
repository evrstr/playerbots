
#include "Category.h"
#include "ItemBag.h"
#include "ahbot/AhBot.h"
#include "World/World.h"
#include "Config/Config.h"
#include "Chat/Chat.h"
#include "AhBotConfig.h"
#include "AuctionHouse/AuctionHouseMgr.h"
#include "Server/WorldSession.h"
#include "Entities/Player.h"
#include "Globals/ObjectAccessor.h"
#include "Entities/ObjectGuid.h"
#include "Globals/ObjectMgr.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "Accounts/AccountMgr.h"
#include "playerbot/playerbot.h"
#include "Mails/Mail.h"
#include "Util/Util.h"

#ifdef CMANGOS
#include <boost/thread/thread.hpp>
#endif

using namespace ahbot;

// 处理游戏内或控制台输入的 ahbot 管理指令
bool AhBot::HandleAhBotCommand(ChatHandler* handler, char const* args)
{
    auctionbot.HandleCommand(args);
    return true;
}

uint32 AhBot::auctionIds[MAX_AUCTIONS] = {1,6,7};
uint32 AhBot::auctioneers[MAX_AUCTIONS] = {79707,4656,23442};
std::map<uint32, uint32> AhBot::factions;

// 初始化拍卖行机器人配置、阵营映射及可拍卖物品列表
void AhBot::Init()
{
    sLog.outString("Initializing AhBot by ike3");

    if (!sAhBotConfig.Initialize())
        return;

    factions[1] = 1;
    factions[2] = 1;
    factions[3] = 1;
    factions[4] = 2;
    factions[5] = 2;
    factions[6] = 2;
    factions[7] = 3;

    availableItems.Init();

    sLog.outString("AhBot configuration loaded");
}

AhBot::~AhBot()
{
}

ObjectGuid AhBot::GetAHBplayerGUID()
{
    return ObjectGuid(sAhBotConfig.guid);
}

#ifdef MANGOS
class AhbotThread: public ACE_Task <ACE_MT_SYNCH>
{
public:
    int svc(void) { auctionbot.ForceUpdate(); return 0; }
};
#endif
#ifdef CMANGOS
void AhbotThread()
{
    auctionbot.ForceUpdate();
}
#endif

// 启动异步线程执行拍卖行后台扫描更新
void activateAhbotThread()
{
#ifdef MANGOS
    AhbotThread *thread = new AhbotThread();
    thread->activate();
#endif
#ifdef CMANGOS
    boost::thread t(AhbotThread);
    t.detach();
#endif
}

// 世界主循环调用：检查开关、停服状态及冷却时间后触发后台更新并清理过期议价邮件
void AhBot::Update()
{
    if (!sAhBotConfig.enabled)
        return;

    if (sWorld.IsShutdowning())
        return;

    if (sWorld.IsStopped())
        return;

    time_t now = time(0);

    if (now < nextAICheckTime)
        return;

    if (updating)
        return;

    nextAICheckTime = time(0) + sAhBotConfig.updateInterval;
    activateAhbotThread();
    CleanupPropositions();
}

// 后台线程主任务：加载机器人竞拍者、刷新分类倍率、逐拍卖行应答玩家拍卖并补货上架
void AhBot::ForceUpdate()
{
    if (!sAhBotConfig.enabled)
        return;

    if (updating)
        return;

    std::string msg = "AhBot is now checking auctions in the background";
    sLog.outString("%s", msg.c_str());
    //ostringstream out1; out1 << "|c070cc700 " << msg << " |r"; (已禁用世界频道广播)
    //sWorld.SendWorldText(3, out1.str().c_str());
    updating = true;

    if (!allBidders.size())
        LoadRandomBots();

    if (!allBidders.size())
    {
        sLog.outError("Ahbot is enabled but there are no bidders available");
        return;
    }

    CheckCategoryMultipliers();

    int answered = 0, added = 0;
    for (int i = 0; i < MAX_AUCTIONS; i++)
    {
        InAuctionItemsBag inAuctionItems(auctionIds[i]);
        inAuctionItems.Init(true);

        for (int j = 0; j < CategoryList::instance.size(); j++)
        {
            Category* category = CategoryList::instance[j];
            answered += Answer(i, category, &inAuctionItems);
            added += AddAuctions(i, category, &inAuctionItems);
        }
    }

    CleanupHistory();

    sLog.outString("AhBot auction check finished. %d auctions answered, %d new auctions added. Next check in %d seconds",
        answered, added, sAhBotConfig.updateInterval);
    /*ostringstream out; out << "|c070cc700 AhBot auction check finished. Next check in " << sAhBotConfig.updateInterval << " seconds |r";
    sWorld.SendWorldText(3, out.str().c_str());
    if (added > 0)
    {
        ostringstream out; out << "|c070cc700 There " << (added == 1 ? "is " : "are ") << added << (added == 1 ? " new item" : " new items") << " in the auction. |r";
        sWorld.SendWorldText(3, out.str().c_str());
    }
    if (answered > 0)
    {
        ostringstream out; out << "|c070cc700 "  << answered << (answered == 1 ? " auction has been" : " auctions have been") << " answered.|r";
        sWorld.SendWorldText(3, out.str().c_str());
    }*/ // disable in game ahbot spam (屏蔽游戏内拍卖行机器人刷屏广播)
    updating = false;
}

// 按起拍价升序（起拍价相同时按一口价升序）排列拍卖条目的比较谓词
struct SortByPricePredicate
{
    bool operator()(AuctionEntry* const & a, AuctionEntry* const & b) const
    {
        if (a->startbid == b->startbid)
            return a->buyout < b->buyout;

        return a->startbid < b->startbid;
    }
};

// 读取指定拍卖行中玩家挂出的指定分类拍卖并按价格排序
std::vector<AuctionEntry*> AhBot::LoadAuctions(const AuctionHouseObject::AuctionEntryMap& auctionEntryMap,
        Category*& category, int& auction)
{
    std::vector<AuctionEntry*> entries;
    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap.begin();
            itr != auctionEntryMap.end(); ++itr)
    {
        AuctionEntry *entry = itr->second;
        if (IsBotAuction(entry->owner) || IsBotAuction(entry->bidder))
            continue;

        Item *item = sAuctionMgr.GetAItem(entry->itemGuidLow);
        if (!item)
            continue;

        if (!category->Contains(item->GetProto()))
            continue;

        uint32 price = category->GetPricingStrategy()->GetBuyPrice(item->GetProto(), auctionIds[auction]);
        if (!price || !item->GetCount())
        {
            sLog.outDetail("%s (x%d) in auction %d: price cannot be determined",
                    item->GetProto()->Name1, item->GetCount(), auctionIds[auction]);
            continue;
        }

        entries.push_back(entry);
    }
    std::sort(entries.begin(), entries.end(), SortByPricePredicate());
    return entries;
}

// 检索拍卖行中同模板物品其他卖家的最低竞标价与最低一口价
void AhBot::FindMinPrice(const AuctionHouseObject::AuctionEntryMap& auctionEntryMap, AuctionEntry*& entry, Item*& item, uint32* minBid,
        uint32* minBuyout)
{
    *minBid = 0;
    *minBuyout = 0;
    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap.begin();
            itr != auctionEntryMap.end(); ++itr)
    {
        AuctionEntry *other = itr->second;
        if (other->owner == entry->owner)
            continue;

        Item *otherItem = sAuctionMgr.GetAItem(other->itemGuidLow);
        if (!otherItem || !otherItem->GetCount() || !otherItem->GetProto() || otherItem->GetProto()->ItemId != item->GetProto()->ItemId)
            continue;

        uint32 startbid = other->startbid / otherItem->GetCount() * item->GetCount();
        uint32 bid = other->bid / otherItem->GetCount() * item->GetCount();
        uint32 buyout = other->buyout / otherItem->GetCount() * item->GetCount();

        if (!bid && startbid && (!*minBid || *minBid > startbid))
            *minBid = startbid;

        if (bid && (*minBid || *minBid > bid))
            *minBid = bid;

        if (buyout && (!*minBuyout || *minBuyout > buyout))
            *minBuyout = buyout;
    }
}

// 评估玩家挂出的拍卖：校验等级/数量/预算/最低价/延时后执行竞标或一口价拍下，高价物品则发送议价邮件
int AhBot::Answer(int auction, Category* category, ItemBag* inAuctionItems)
{
    const AuctionHouseEntry* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
    if (!ahEntry)
        return 0;

    int answered = 0;
    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);
    const AuctionHouseObject::AuctionEntryMap& auctionEntryMap = auctionHouse->GetAuctions();
    int64 availableMoney = GetAvailableMoney(auctionIds[auction]);

    std::vector<AuctionEntry*> entries = LoadAuctions(auctionEntryMap, category, auction);
    for (std::vector<AuctionEntry*>::iterator itr = entries.begin(); itr != entries.end(); ++itr)
    {
        AuctionEntry *entry = *itr;
        uint32 owner = entry->owner;
        if (owner == sAhBotConfig.guid)
            continue;

        uint32 account = sObjectMgr.GetPlayerAccountIdByGUID(ObjectGuid(HIGHGUID_PLAYER, owner));
        if (!account || sPlayerbotAIConfig.IsInRandomAccountList(account))
            continue;

        Item *item = sAuctionMgr.GetAItem(entry->itemGuidLow);
        if (!item || !item->GetCount())
            continue;

        const ItemPrototype* proto = item->GetProto();
        std::vector<uint32> items = availableItems.Get(category);
        if (std::find(items.begin(), items.end(), proto->ItemId) == items.end())
        {
            sLog.outDetail( "%s (x%d) in auction %d: unavailable item",
                    item->GetProto()->Name1, item->GetCount(), auctionIds[auction]);
            continue;
        }

        uint32 answerCount = GetAnswerCount(proto->ItemId, auctionIds[auction], sAhBotConfig.itemBuyMaxInterval);
        uint32 maxAnswerCount = category->GetMaxAllowedItemAuctionCount(proto);
        if (maxAnswerCount && answerCount > maxAnswerCount)
        {
            sLog.outDetail( "%s (x%d) in auction %d: answer count %d > %d (max)",
                    item->GetProto()->Name1, item->GetCount(), auctionIds[auction], answerCount, maxAnswerCount);
            continue;
        }

        if (proto->RequiredLevel > sAhBotConfig.maxRequiredLevel || proto->ItemLevel > sAhBotConfig.maxItemLevel)
        {
            sLog.outDetail( "%s (x%d) in auction %d: above max required or item level",
                    item->GetProto()->Name1, item->GetCount(), auctionIds[auction]);
            continue;
        }

        uint32 price = category->GetPricingStrategy()->GetBuyPrice(proto, auctionIds[auction]);
        if (!price)
        {
            sLog.outDetail( "%s (x%d) in auction %d: cannot determine price",
                    item->GetProto()->Name1, item->GetCount(), auctionIds[auction]);
            continue;
        }

        uint32 bidPrice = item->GetCount() * price;
        uint32 buyoutPrice = item->GetCount() * urand(price, 4 * price / 3);

        uint32 curPrice = entry->bid;
        if (!curPrice) curPrice = entry->startbid;
        if (!curPrice) curPrice = entry->buyout;

        uint32 bidder = GetRandomBidder(auctionIds[auction]);
        if (!bidder)
        {
            sLog.outError( "No bidders for auction %d", auctionIds[auction]);
            break;
        }

        if (curPrice > buyoutPrice)
        {
            sLog.outDetail( "%s (x%d) in auction %d: price %d > %d (buyout price)",
                    proto->Name1, item->GetCount(), auctionIds[auction], curPrice, buyoutPrice);
            CheckSendMail(bidder, buyoutPrice, entry);
            continue;
        }

        if (availableMoney < curPrice)
        {
            sLog.outDetail( "%s (x%d) in auction %d: price %d > %ld (available money)",
                    proto->Name1, item->GetCount(), auctionIds[auction], curPrice, availableMoney);
            continue;
        }

        uint32 minBid = 0, minBuyout = 0;
        FindMinPrice(auctionEntryMap, entry, item, &minBid, &minBuyout);

        if (minBid && entry->bid && minBid < entry->bid)
        {
            sLog.outDetail( "%s (x%d) in auction %d: %d (bid) > %d (minBid)",
                    proto->Name1, item->GetCount(), auctionIds[auction], entry->bid, minBid);
            continue;
        }

        if (minBid && entry->startbid && minBid < entry->startbid)
        {
            sLog.outDetail( "%s (x%d) in auction %d: %d (startbid) > %d (minBid)",
                    proto->Name1, item->GetCount(), auctionIds[auction], entry->startbid, minBid);
            CheckSendMail(bidder, minBid, entry);
            continue;
        }

        double priceLevel = (double)curPrice / (double)buyoutPrice;
        uint32 buytime = GetBuyTime(entry->Id, proto->ItemId, auctionIds[auction], category, priceLevel);
        if (time(0) < buytime)
        {
            sLog.outDetail( "%s (x%d) in auction %d: will buy/bid in %ld seconds",
                    proto->Name1, item->GetCount(), auctionIds[auction], buytime - time(0));
            continue;
        }

        entry->bidder = bidder;
        entry->bid = curPrice + urand(1, 1 + bidPrice / 10);
        availableMoney -= curPrice;

        updateMarketPrice(item->GetProto()->ItemId, entry->buyout / item->GetCount(), auctionIds[auction]);

        if ((entry->buyout && (entry->bid >= entry->buyout || 100 * (entry->buyout - entry->bid) / price < 25)) &&
                !(minBuyout && entry->buyout && minBuyout < entry->buyout))
        {
            sLog.outDetail( "AhBot %d won %s (x%d) in auction %d for %d",
                    bidder, item->GetProto()->Name1, item->GetCount(), auctionIds[auction], entry->buyout);

            entry->bid = entry->buyout;
            entry->AuctionBidWinning(NULL);
        }
        else
        {
            sLog.outDetail( "AhBot %d placed bid %d for %s (x%d) in auction %d",
                    bidder, entry->bid, item->GetProto()->Name1, item->GetCount(), auctionIds[auction]);

            CharacterDatabase.PExecute("UPDATE auction SET buyguid = '%u',lastbid = '%u' WHERE id = '%u'",
                entry->bidder, entry->bid, entry->Id);
            AddToHistory(entry, AHBOT_WON_BID);
        }

        CharacterDatabase.PExecute("DELETE FROM ahbot_history WHERE item = '%u' AND won = 4 AND auction_house = '%u' ",
                proto->ItemId, factions[auctionIds[auction]]);

        answered++;
    }

    return answered;
}

uint32 AhBot::GetTime(std::string category, uint32 id, uint32 auctionHouse, uint32 type)
{
    auto results = CharacterDatabase.PQuery("SELECT MAX(buytime) FROM ahbot_history WHERE item = '%u' AND won = '%u' AND auction_house = '%u' AND category = '%s'",
        id, type, factions[auctionHouse], category.c_str());

    if (!results)
        return 0;

    Field* fields = results->Fetch();
    uint32 result = fields[0].GetUInt32();

    return result;
}

void AhBot::SetTime(std::string category, uint32 id, uint32 auctionHouse, uint32 type, uint32 value)
{
    CharacterDatabase.PExecute("DELETE FROM ahbot_history WHERE item = '%u' AND won = '%u' AND auction_house = '%u' AND category = '%s'",
        id, type, factions[auctionHouse], category.c_str());

    CharacterDatabase.PExecute("INSERT INTO ahbot_history (buytime, item, bid, buyout, category, won, auction_house) "
        "VALUES ('%u', '%u', '%u', '%u', '%s', '%u', '%u')",
        value, id, 0, 0,
        category.c_str(), type, factions[auctionHouse]);
}

// 基于分类与单品冷却及价格水平计算随机延迟竞拍时间戳
uint32 AhBot::GetBuyTime(uint32 entry, uint32 itemId, uint32 auctionHouse, Category*& category, double priceLevel)
{
    uint32 entryTime = GetTime("entry", entry, auctionHouse, AHBOT_WON_DELAY);
    if (entryTime > time(0))
        return entryTime;

    uint32 result = entryTime;

    std::string categoryName = category->GetName();
    uint32 categoryTime = GetTime(categoryName, 0, auctionHouse, AHBOT_WON_DELAY);
    uint32 itemTime = GetTime("item", itemId, auctionHouse, AHBOT_WON_DELAY);

    if (categoryTime < time(0)) categoryTime = time(0);
    if (itemTime < time(0)) itemTime = time(0);

    double rarity = category->GetPricingStrategy()->GetRarityPriceMultiplier(itemId);
    categoryTime += urand(sAhBotConfig.itemBuyMinInterval, sAhBotConfig.itemBuyMaxInterval) * priceLevel;
    itemTime += urand(sAhBotConfig.itemBuyMinInterval, sAhBotConfig.itemBuyMaxInterval) * priceLevel / rarity;
    entryTime = std::max(categoryTime, itemTime);

    SetTime(categoryName, 0, auctionHouse, AHBOT_WON_DELAY, categoryTime);
    SetTime("item", itemId, auctionHouse, AHBOT_WON_DELAY, itemTime);
    SetTime("entry", entry, auctionHouse, AHBOT_WON_DELAY, entryTime);

    return result ? result : entryTime;
}

// 计算机器人允许再次上架指定物品的目标时间戳
uint32 AhBot::GetSellTime(uint32 itemId, uint32 auctionHouse, Category*& category)
{
    uint32 itemSellTime = GetTime("item", itemId, auctionHouse, AHBOT_SELL_DELAY);
    uint32 itemBuyTime = GetTime("item", itemId, auctionHouse, AHBOT_WON_DELAY);
    uint32 itemTime = std::max(itemSellTime, itemBuyTime);

    if (itemTime > time(0))
        return itemTime;

    uint32 result = itemTime;

    std::string categoryName = category->GetDisplayName();
    uint32 categorySellTime = GetTime(categoryName, 0, auctionHouse, AHBOT_SELL_DELAY);
    uint32 categoryBuyTime = GetTime(categoryName, 0, auctionHouse, AHBOT_WON_DELAY);
    uint32 categoryTime = std::max(categorySellTime, categoryBuyTime);

    if (categoryTime < time(0)) categoryTime = time(0);
    if (itemTime < time(0)) itemTime = time(0);

    double rarity = category->GetPricingStrategy()->GetRarityPriceMultiplier(itemId);
    categoryTime += urand(sAhBotConfig.itemSellMinInterval, sAhBotConfig.itemSellMaxInterval);
    itemTime += urand(sAhBotConfig.itemSellMinInterval, sAhBotConfig.itemSellMaxInterval) * rarity;
    itemTime = std::max(itemTime, categoryTime);

    SetTime(categoryName, 0, auctionHouse, AHBOT_SELL_DELAY, categoryTime);
    SetTime("item", itemId, auctionHouse, AHBOT_SELL_DELAY, itemTime);

    return result ? result : itemTime;
}

// 检查分类上架配额并在可用物品池中随机抽取符合冷却条件的物品上架
int AhBot::AddAuctions(int auction, Category* category, ItemBag* inAuctionItems)
{
    std::vector<uint32>& inAuction = inAuctionItems->Get(category);

    int32 maxAllowedAuctionCount = categoryMaxAuctionCount[category->GetDisplayName()];
    if (inAuctionItems->GetCount(category) >= maxAllowedAuctionCount)
        return 0;

    int added = 0;
    int ladded = 0;
    std::vector<uint32> available = availableItems.Get(category);
    for (int32 i = 0; i <= maxAllowedAuctionCount && available.size() > 0 && inAuctionItems->GetCount(category) < maxAllowedAuctionCount; ++i)
    {
        uint32 index = urand(0, available.size() - 1);
        uint32 itemId = available[index];

        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        if (!proto)
            continue;

        int32 maxAllowedItems = category->GetMaxAllowedItemAuctionCount(proto);
        if (maxAllowedItems && inAuctionItems->GetCount(category, proto->ItemId) >= maxAllowedItems)
        {
            sLog.outDetail("%s in auction %d: has reached max %d/%d",
                proto->Name1, auctionIds[auction], inAuctionItems->GetCount(category, proto->ItemId), maxAllowedItems);
            continue;
        }

        uint32 sellTime = GetSellTime(proto->ItemId, auctionIds[auction], category);
        if (time(0) - sellTime < 0)
        {
            ladded += 1;
            sLog.outDetail( "%s in auction %d: will add in %ld seconds",
                    proto->Name1, auctionIds[auction], sellTime - time(0));
            continue;
        }
        else if (time(0) - sellTime > sAhBotConfig.maxSellInterval)
        {
            sLog.outDetail( "%s in auction %d: too old (%ld secs)",
                    proto->Name1, auctionIds[auction], time(0) - sellTime);
            continue;
        }
        inAuctionItems->Add(proto);
        added += AddAuction(auction, category, proto);
    }

    sLog.outDetail("%s has %d upcomming and %d new auctions.",
        category->GetDisplayName().c_str(), ladded , added);


    return added;
}

// 构造单条新拍卖记录（计算定价、堆叠数、随机附魔及有效时间）并存入数据库与拍卖行
int AhBot::AddAuction(int auction, Category* category, ItemPrototype const* proto)
{
    uint32 owner = GetRandomBidder(auctionIds[auction]);
    if (!owner)
    {
        sLog.outError("No bidders for auction %d", auctionIds[auction]);
        return 0;
    }

    std::string name;
    if (!sObjectMgr.GetPlayerNameByGUID(ObjectGuid(HIGHGUID_PLAYER, owner), name))
        return 0;


    uint32 price = category->GetPricingStrategy()->GetSellPrice(proto, auctionIds[auction]);

    sLog.outDetail( "AddAuction: market price adjust");
    updateMarketPrice(proto->ItemId, price, auctionIds[auction]);

    price = category->GetPricingStrategy()->GetSellPrice(proto, auctionIds[auction]);

    uint32 stackCount = urand(1, category->GetStackCount(proto));
    if (!price || !stackCount)
        return 0;

    if (price > sAhBotConfig.stackReducePrice)
        stackCount /= (price / sAhBotConfig.stackReducePrice);

    if (!stackCount)
        stackCount = 1;

    if (urand(1, 100) <= sAhBotConfig.underPriceProbability * 100)
        price = price * 100 / urand(100, 200);

    uint32 bidPrice = PricingStrategy::RoundPrice(stackCount * price);
    uint32 buyoutPrice = PricingStrategy::RoundPrice(stackCount * urand(price, 4 * price / 3));

    Item* item = Item::CreateItem(proto->ItemId, stackCount);
    if (!item)
        return 0;

    uint32 randomPropertyId = Item::GenerateItemRandomPropertyId(proto->ItemId);
    if (randomPropertyId)
        item->SetItemRandomProperties(randomPropertyId);

    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
    if (!ahEntry)
        return 0;

    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);

    uint32 auction_time = uint32(urand(8, 24) * HOUR * sWorld.getConfig(CONFIG_FLOAT_RATE_AUCTION_TIME));

    AuctionEntry* auctionEntry = new AuctionEntry;
    auctionEntry->Id = sObjectMgr.GenerateAuctionID();
    auctionEntry->itemGuidLow = item->GetObjectGuid().GetCounter();
    auctionEntry->itemTemplate = item->GetEntry();
    auctionEntry->itemCount = item->GetCount();
    auctionEntry->itemRandomPropertyId = item->GetItemRandomPropertyId();
    auctionEntry->owner = owner;
    auctionEntry->startbid = bidPrice;
    auctionEntry->bidder = 0;
    auctionEntry->bid = 0;
    auctionEntry->buyout = buyoutPrice;
    auctionEntry->expireTime = time(nullptr) + auction_time;
    //auctionEntry->moneyDeliveryTime = 0;
    auctionEntry->deposit = 0;
    auctionEntry->auctionHouseEntry = ahEntry;

    auctionHouse->AddAuction(auctionEntry);


    sAuctionMgr.AddAItem(item);

    item->SaveToDB();
    auctionEntry->SaveToDB();

    sLog.outDetail( "AhBot %d added %d of %s to auction %d for %d..%d", owner, stackCount, proto->Name1, auctionIds[auction], bidPrice, buyoutPrice);
    return 1;
}

// 执行 ahbot 控制台命令（expire/stats/update/dump 或查询指定物品 ID 价格明细）
void AhBot::HandleCommand(std::string command)
{
    if (!sAhBotConfig.enabled)
        return;

    if (command == "expire")
    {
        for (int i = 0; i < MAX_AUCTIONS; i++)
            Expire(i);
        CharacterDatabase.PExecute("DELETE FROM ahbot_category");
        CharacterDatabase.PExecute("UPDATE ahbot_history SET buytime = buytime - 3600 * 24;");

        return;
    }

    if (command == "stats")
    {
        for (int i = 0; i < MAX_AUCTIONS; i++)
            PrintStats(i);

        return;
    }

    if (command == "update")
    {
        activateAhbotThread();
        return;
    }

    if (command == "dump")
    {
        Dump();
        return;
    }

    uint32 itemId = atoi(command.c_str());
    if (!itemId)
    {
        sLog.outString("ahbot stats - show short summary");
        sLog.outString("ahbot expire - expire all auctions");
        sLog.outString("ahbot update - update all auctions");
        sLog.outString("ahbot <itemId> - show item price");
        return;
    }

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
    if (!proto)
        return;

    for (int i=0; i<CategoryList::instance.size(); i++)
    {
        Category* category = CategoryList::instance[i];
        if (category->Contains(proto))
        {
            std::vector<uint32> items = availableItems.Get(category);
            if (std::find(items.begin(), items.end(), proto->ItemId) == items.end())
                continue;

            std::ostringstream out;
            out << proto->Name1 << " (" << category->GetDisplayName() << "), "
                    << category->GetMaxAllowedAuctionCount() << "x" << category->GetMaxAllowedItemAuctionCount(proto)
                    << "x" << category->GetStackCount(proto) << " max"
                    << "\n";
            for (int auction = 0; auction < MAX_AUCTIONS; auction++)
            {
                const AuctionHouseEntry* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
                out << "--- auction house " << auctionIds[auction] << "(faction: " << factions[auctionIds[auction]] << ", money: "
                    << GetAvailableMoney(auctionIds[auction])
                    << ") ---\n";

                std::ostringstream exp1;
                out << "sell: " << ChatHelper::formatMoney(category->GetPricingStrategy()->GetSellPrice(proto, auctionIds[auction], true, &exp1));
                out << " ("  << exp1.str().c_str() << ")\n";

                std::ostringstream exp2;
                out << "buy: " << ChatHelper::formatMoney(category->GetPricingStrategy()->GetBuyPrice(proto, auctionIds[auction], &exp2));
                out << " ("  << exp2.str().c_str() << ")\n";

                out << "market: " << ChatHelper::formatMoney(category->GetPricingStrategy()->GetMarketPrice(proto->ItemId, auctionIds[auction]))
                    << "\n";
            }
            sLog.outString("%s",out.str().c_str());
        }
    }
}

// 强制使指定拍卖行中机器人名下的在售物品立即到期
void AhBot::Expire(int auction)
{
    if (!sAhBotConfig.enabled)
        return;

    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
    if(!ahEntry)
        return;

    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);

    AuctionHouseObject::AuctionEntryMap const& auctions = auctionHouse->GetAuctions();
    AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctions.begin();

    int count = 0;
    while (itr != auctions.end())
    {
        if (IsBotAuction(itr->second->owner))
        {
            itr->second->expireTime = sWorld.GetGameTime();
            count++;
        }

        ++itr;
    }

    sLog.outString("%d auctions marked as expired in auction %d", count, auctionIds[auction]);
}

// 打印指定拍卖行当前在售物品总数
void AhBot::PrintStats(int auction)
{
    if (!sAhBotConfig.enabled)
        return;

    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
    if(!ahEntry)
        return;

    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);
    AuctionHouseObject::AuctionEntryMap const& auctions = auctionHouse->GetAuctions();

    sLog.outString("%lu auctions available on auction house %d", auctions.size(), auctionIds[auction]);
}

// 将成交或竞价事件记录到 ahbot_history 并更新市场参考价格
void AhBot::AddToHistory(AuctionEntry* entry, uint32 won)
{
    if (!sAhBotConfig.enabled || !entry)
        return;

    if (!IsBotAuction(entry->owner) && !IsBotAuction(entry->bidder))
        return;

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(entry->itemTemplate);
    if (!proto)
        return;

    std::string category = "";
    for (int i = 0; i < CategoryList::instance.size(); i++)
    {
        if (CategoryList::instance[i]->Contains(proto))
        {
            category = CategoryList::instance[i]->GetName();
            break;
        }
    }

    if (!won)
    {
        won = AHBOT_WON_PLAYER;
        if (IsBotAuction(entry->bidder))
            won = AHBOT_WON_SELF;
    }

    sLog.outDetail( "AddToHistory: market price adjust");
    int count = entry->itemCount ? entry->itemCount : 1;
    updateMarketPrice(proto->ItemId, entry->buyout / count, entry->auctionHouseEntry->houseId);

    uint32 now = time(0);
    CharacterDatabase.PExecute("INSERT INTO ahbot_history (buytime, item, bid, buyout, category, won, auction_house) "
        "VALUES ('%u', '%u', '%u', '%u', '%s', '%u', '%u')",
        now, entry->itemTemplate, entry->bid ? entry->bid : entry->startbid, entry->buyout,
        category.c_str(), won, factions[entry->auctionHouseEntry->houseId]);
}

// 查询指定时间段内机器人对该物品的应答竞拍次数
uint32 AhBot::GetAnswerCount(uint32 itemId, uint32 auctionHouse, uint32 withinTime)
{
    uint32 count = 0;

    auto results = CharacterDatabase.PQuery("SELECT COUNT(*) FROM ahbot_history WHERE "
        "item = '%u' AND won in (2, 3) AND auction_house = '%u' AND buytime > '%lu'",
        itemId, factions[auctionHouse], time(0) - withinTime);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            count = fields[0].GetUInt32();
        } while (results->NextRow());
    }

    return count;
}

// 删除超出配置保留天数的旧拍卖历史记录
void AhBot::CleanupHistory()
{
    uint32 when = time(0) - 3600 * 24 * sAhBotConfig.historyDays;
    CharacterDatabase.PExecute("DELETE FROM ahbot_history WHERE buytime < '%u'", when);
}

// 汇总每日基础预算、历史盈亏及当前挂单占用资金，计算可用收购余额
uint32 AhBot::GetAvailableMoney(uint32 auctionHouse)
{
    int64 result = sAhBotConfig.alwaysAvailableMoney;

    std::map<uint32, uint32> data;
    data[AHBOT_WON_PLAYER] = 0;
    data[AHBOT_WON_SELF] = 0;

    const AuctionHouseEntry* ahEntry = sAuctionHouseStore.LookupEntry(auctionHouse);
    auto results = CharacterDatabase.PQuery(
        "SELECT won, SUM(bid) FROM ahbot_history WHERE auction_house = '%u' GROUP BY won HAVING won > 0 ORDER BY won",
        factions[auctionHouse]);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            data[fields[0].GetUInt32()] = fields[1].GetUInt32();

        } while (results->NextRow());
    }

    results = CharacterDatabase.PQuery(
        "SELECT max(buytime) FROM ahbot_history WHERE auction_house = '%u' AND won = '2'",
        factions[auctionHouse]);
    if (results)
    {
        Field* fields = results->Fetch();
        uint32 lastBuyTime = fields[0].GetUInt32();
        uint32 now = time(0);
        if (lastBuyTime && now > lastBuyTime)
        result += (now - lastBuyTime) / 3600 / 24 * sAhBotConfig.alwaysAvailableMoney;
    }

    AuctionHouseObject::AuctionEntryMap const& auctionEntryMap = sAuctionMgr.GetAuctionsMap(ahEntry)->GetAuctions();
    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap.begin(); itr != auctionEntryMap.end(); ++itr)
    {
        AuctionEntry *entry = itr->second;
        if (!IsBotAuction(entry->bidder))
            continue;

        result -= entry->bid;
    }

    result += (data[AHBOT_WON_PLAYER] - data[AHBOT_WON_SELF]);
    return result < 0 ? 0 : (uint32)result;
}

// 从数据库读取或周期性随机刷新各分类的价格倍率与上架上限
void AhBot::CheckCategoryMultipliers()
{
    auto results = CharacterDatabase.PQuery("SELECT category, multiplier, max_auction_count, expire_time FROM ahbot_category");
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            categoryMultipliers[fields[0].GetString()] = fields[1].GetFloat();
            categoryMaxAuctionCount[fields[0].GetString()] = fields[2].GetInt32();
            categoryMultiplierExpireTimes[fields[0].GetString()] = fields[3].GetUInt64();

        } while (results->NextRow());
    }

    CharacterDatabase.PExecute("DELETE FROM ahbot_category");

    std::set<std::string> tmp;
    for (int i = 0; i < CategoryList::instance.size(); i++)
    {
        std::string name = CategoryList::instance[i]->GetDisplayName();

        if (tmp.find(name) != tmp.end())
            continue;

        tmp.insert(name);
        if (categoryMultiplierExpireTimes[name] <= (uint64)time(0) || categoryMultipliers[name] <= 0)
        {
            uint32 k = urand(1, 100);
            double m = 1.0;
            double r = (double)urand(100, 200) / 100.0;
            if (k < 50) m = r; // 1..2 (约50%概率落在1~2倍)
            else if (k < 80) m = 1 + r; // 2..3 (约30%概率落在2~3倍)
            else if (k < 90) m = 2 + r; // 3..4 (约10%概率落在3~4倍)
            else m = 3 + r; // 4..5 (约10%概率落在4~5倍)
            categoryMultipliers[name] = m;
            categoryMultiplierExpireTimes[name] = time(0) + urand(4, 7) * 3600 * 24;
        }

        categoryMaxAuctionCount[name] = CategoryList::instance[i]->GetMaxAllowedAuctionCount();

        CharacterDatabase.PExecute("INSERT INTO ahbot_category (category, multiplier, max_auction_count, expire_time) "
                "VALUES ('%s', '%f', '%u', '%zu')",
                name.c_str(), categoryMultipliers[name], categoryMaxAuctionCount[name], categoryMultiplierExpireTimes[name]);
    }
}


// 采用算术平均平滑更新物品在特定拍卖行的市场价格
void AhBot::updateMarketPrice(uint32 itemId, double price, uint32 auctionHouse)
{
    double marketPrice = 0;

    auto results = CharacterDatabase.PQuery("SELECT price FROM ahbot_price WHERE item = '%u' AND auction_house = '%u'", itemId, auctionHouse);
    if (results)
    {
        marketPrice = results->Fetch()[0].GetFloat();
    }

    if (marketPrice > 0)
        marketPrice = (marketPrice + price) / 2;
    else
        marketPrice = price;

    CharacterDatabase.PExecute("DELETE FROM ahbot_price WHERE item = '%u' AND auction_house = '%u'", itemId, auctionHouse);
    CharacterDatabase.PExecute("INSERT INTO ahbot_price (item, price, auction_house) VALUES ('%u', '%lf', '%u')", itemId, marketPrice, auctionHouse);
}

// 判断 GUID 是否属于已加载的拍卖行机器人账号角色
bool AhBot::IsBotAuction(uint32 bidder)
{
    return allBidders.find(bidder) != allBidders.end();
}

// 从指定阵营的有效机器人角色中随机抽取一名竞拍者/卖家
uint32 AhBot::GetRandomBidder(uint32 auctionHouse)
{
    std::vector<uint32> guids = bidders[factions[auctionHouse]];
    if (guids.empty())
        return 0;

    std::vector<uint32> online;
    for (std::vector<uint32>::iterator i = guids.begin(); i != guids.end(); ++i)
    {
        uint32 guid = *i;
        std::string name;
        if (!sObjectMgr.GetPlayerNameByGUID(ObjectGuid(HIGHGUID_PLAYER, guid), name))
            continue;

        online.push_back(guid);
    }

    if (online.empty())
        return 0;

    int index = urand(0, online.size() - 1);
    return online[index];
}

// 从随机机器人账号加载角色 GUID 并按阵营分配到联盟/部落/中立拍卖行池
void AhBot::LoadRandomBots()
{
    for (std::list<uint32>::iterator i = sPlayerbotAIConfig.randomBotAccounts.begin(); i != sPlayerbotAIConfig.randomBotAccounts.end(); i++)
    {
        uint32 accountId = *i;
        if (!sAccountMgr.GetCharactersCount(accountId))
            continue;

        auto result = CharacterDatabase.PQuery("SELECT guid, race FROM characters WHERE account = '%u'", accountId);
        if (!result)
            continue;

        do
        {
            Field* fields = result->Fetch();
            uint32 guid = fields[0].GetUInt32();
            uint8 race = fields[1].GetUInt8();
            uint32 auctionHouse = PlayerbotAI::IsOpposing(race, RACE_HUMAN) ? 2 : 1;
            bidders[auctionHouse].push_back(guid);
            bidders[3].push_back(guid);
            allBidders.insert(guid);
        } while (result->NextRow());
    }


    if (allBidders.empty() && sAhBotConfig.guid)
    {
        uint32 guid = sAhBotConfig.guid;
        allBidders.insert(guid);
        for (int i = 1; i <= 3; i++)
        {
            bidders[i].push_back(guid);
        }
    }

    sLog.outDetail( "{A=%zu,H=%zu,N=%zu} bidders loaded", bidders[1].size(), bidders[2].size(), bidders[3].size());
}

// 计算并返回物品在各拍卖行中的最高建议出售价
int32 AhBot::GetSellPrice(ItemPrototype const* proto)
{
    if (!sAhBotConfig.enabled)
        return 0;

    int32 maxPrice = 0;
    for (int i=0; i<CategoryList::instance.size(); i++)
    {
        Category* category = CategoryList::instance[i];
        if (!category->Contains(proto))
            continue;

        std::vector<uint32> items = availableItems.Get(category);
        if (std::find(items.begin(), items.end(), proto->ItemId) == items.end())
            continue;

        for (int auction = 0; auction < MAX_AUCTIONS; auction++)
        {
            int32 price = (int32)category->GetPricingStrategy()->GetSellPrice(proto, auctionIds[auction]);
            if (!price)
                price = (int32)category->GetPricingStrategy()->GetBuyPrice(proto, auctionIds[auction]);

            if (price > maxPrice)
                maxPrice = price;
        }
    }

    return maxPrice;
}

// 计算并返回物品在各拍卖行中的最高建议收购价
int32 AhBot::GetBuyPrice(ItemPrototype const* proto)
{
    if (!sAhBotConfig.enabled)
        return 0;

    int32 maxPrice = 0;
    for (int i=0; i<CategoryList::instance.size(); i++)
    {
        Category* category = CategoryList::instance[i];
        if (!category->Contains(proto))
            continue;

        std::vector<uint32> items = availableItems.Get(category);
        if (std::find(items.begin(), items.end(), proto->ItemId) == items.end())
            continue;

        for (int auction = 0; auction < MAX_AUCTIONS; auction++)
        {
            int32 price = (int32)category->GetPricingStrategy()->GetBuyPrice(proto, auctionIds[auction]);
            if (!price)
                continue;

            if (price > maxPrice)
                maxPrice = price;
        }
    }

    return maxPrice;
}

// 获取指定物品的稀有度价格乘数
double AhBot::GetRarityPriceMultiplier(const ItemPrototype* proto)
{
    if (!sAhBotConfig.enabled)
        return 1.0;

    for (int i=0; i<CategoryList::instance.size(); i++)
    {
        Category* category = CategoryList::instance[i];
        if (!category->Contains(proto))
            continue;

        return category->GetPricingStrategy()->GetRarityPriceMultiplier(proto->ItemId);
    }

    return 1.0;

}

// 检查物品是否归属于指定商业技能 ID
bool AhBot::IsUsedBySkill(const ItemPrototype* proto, uint32 skillId)
{
    if (!sAhBotConfig.enabled)
        return false;

    for (int i=0; i<CategoryList::instance.size(); i++)
    {
        Category* category = CategoryList::instance[i];
        if (category->GetSkillId() == skillId && category->Contains(proto))
            return true;
    }

    return false;
}

// 对价格高于心理上限的玩家拍卖发送友好议价邮件（含防重复发送冷却）
void AhBot::CheckSendMail(uint32 bidder, uint32 price, AuctionEntry *entry)
{
    if (!sAhBotConfig.sendmail)
        return;

    time_t entryTime = GetTime("entry", entry->Id, entry->auctionHouseEntry->houseId, AHBOT_SENDMAIL);
    if (entryTime > time(0))
        return;

    const AuctionHouseEntry* ahEntry = sAuctionHouseStore.LookupEntry(entry->auctionHouseEntry->houseId);
    if (!ahEntry)
        return;

    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);
    const AuctionHouseObject::AuctionEntryMap& auctionEntryMap = auctionHouse->GetAuctions();
    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap.begin(); itr != auctionEntryMap.end(); ++itr)
    {
        AuctionEntry *otherEntry = itr->second;
        if (otherEntry->owner == entry->owner && otherEntry->Id != entry->Id && otherEntry->itemTemplate == entry->itemTemplate)
        {
            time_t otherEntryTime = GetTime("entry", otherEntry->Id, entry->auctionHouseEntry->houseId, AHBOT_SENDMAIL);
            if (otherEntryTime > time(0))
                return;
        }
    }

    std::ostringstream body;
    body << "Hello,\n";
    body << "\n";
    Item *item = sAuctionMgr.GetAItem(entry->itemGuidLow);
    if (!item)
        return;
    body << "I see you posted " << ChatHelper::formatItem(item, item->GetCount());
    body << " to the AH and I really need that at the moment. Could you lower your price at least to ";
    body << ChatHelper::formatMoney(PricingStrategy::RoundPrice(price)) << "? I'll buy it then.\n";
    body << "\n";
    body << "Regards,\n";

    std::string name;
    if (!sObjectMgr.GetPlayerNameByGUID(ObjectGuid(HIGHGUID_PLAYER, bidder), name))
        return;

    body << name << "\n";

    std::ostringstream title; title << "AH Proposition: " << item->GetProto()->Name1;
    MailDraft draft(title.str(), body.str());
    ObjectGuid receiverGuid(HIGHGUID_PLAYER, entry->owner);
    draft.SendMailTo(MailReceiver(receiverGuid), MailSender(MAIL_NORMAL, bidder));

    SetTime("entry", entry->Id, entry->auctionHouseEntry->houseId, AHBOT_SENDMAIL, entry->expireTime);
}

// 遍历全物品表并将可拍卖物品的估算买卖价格输出到日志
void AhBot::Dump()
{
    for (uint32 itemId = 0; itemId < sItemStorage.GetMaxEntry(); ++itemId)
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        if (!proto)
            continue;

        bool first = true;
        for (int i=0; i<CategoryList::instance.size(); i++)
        {
            Category* category = CategoryList::instance[i];
            if (category->Contains(proto))
            {
                std::vector<uint32> items = availableItems.Get(category);
                if (find(items.begin(), items.end(), proto->ItemId) == items.end())
                    continue;

                std::ostringstream out;
                if (first)
                {
                    out << proto->ItemId << " (" << proto->Name1 << ") x" << category->GetStackCount(proto) << " - ";
                    first = false;
                }

                int auction = 0;
                const AuctionHouseEntry* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
                out << "SELL: "
                    << ChatHelper::formatMoney(category->GetPricingStrategy()->GetSellPrice(proto, auctionIds[auction], true))
                    << ", BUY: "
                    << ChatHelper::formatMoney(category->GetPricingStrategy()->GetBuyPrice(proto, auctionIds[auction]))
                    << " (" << category->GetDisplayName() << ")";
                sLog.outString("%s",out.str().c_str());
            }
        }
    }
}

// 清理投递超过 2 天的过期 AH Proposition 议价邮件
void AhBot::CleanupPropositions()
{
    uint32 deliverTime = time(0) - 3600 * 24 * 2;
    auto result = CharacterDatabase.PQuery("select id, receiver from mail where subject like 'AH Proposition%%' and deliver_time <= '%u'", deliverTime);
    if (!result)
        return;

    int count = 0;
    do
    {
        Field* fields = result->Fetch();
        uint32 id = fields[0].GetUInt32();
        uint32 receiver = fields[1].GetUInt32();
        Player *player = sObjectMgr.GetPlayer(ObjectGuid(HIGHGUID_PLAYER, receiver));
        if (player) player->RemoveMail(id);
        count++;
    } while (result->NextRow());

    if (count > 0)
    {
        CharacterDatabase.PExecute("delete from mail where subject like 'AH Proposition%%' and deliver_time <= '%u'", deliverTime);
        sLog.outBasic("%d old AH propositions removed", count);
    }
}

// 构造 SQL IN 语句批量删除指定 ID 列表的邮件
void AhBot::DeleteMail(std::list<uint32> buffer)
{
    std::ostringstream sql;
    sql << "delete from mail where id in ( ";
    bool first = true;
    for (std::list<uint32>::iterator j = buffer.begin(); j != buffer.end(); ++j)
    {
        if (first) first = false; else sql << ",";
        sql << "'" << *j << "'";
    }
    sql << ")";
    CharacterDatabase.Execute(sql.str().c_str());
}

INSTANTIATE_SINGLETON_1( ahbot::AhBot );
