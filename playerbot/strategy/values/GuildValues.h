// 策略值头文件：GuildValues（公会指令解析、公会共享清单、制造/采集/任务订单与建会战袍）
#pragma once
#include "playerbot/strategy/Value.h"
#include "Guilds/Guild.h"

namespace ai
{
#ifndef MANGOSBOT_ZERO
    // 公会访问辅助类：继承 Guild 以读取银行物品槽位（仅非经典旧世版本）
    class GuildAccess : public Guild
    {
    public:
        Item* GetGuildItem(uint8 TabId, uint8 SlotId);
    };
#endif

    // 公会订单类型枚举（采集、击杀、探索、制造、拍卖行、任务奖励）
    enum class GuildOrderType : uint8
    {
        None = 0,
        Farm,
        Kill,
        Explore,
        Craft,
        AuctionHouse,
        QuestReward
    };

    // 公会订单数据结构：记录订单类型、目标名称、需求数量及奖励物品 ID
    struct GuildOrder
    {
        GuildOrderType type = GuildOrderType::None;
        std::string target;
        uint32 amount = 0; // Used for Craft and Farm orders | 用于制造和采集订单的数量要求
        uint32 questId = 0;
        uint32 rewardItemId = 0;

        bool IsValid() const { return type != GuildOrderType::None && !target.empty(); }
        bool IsTravelOrder() const { return type == GuildOrderType::Farm || type == GuildOrderType::Kill || type == GuildOrderType::Explore || type == GuildOrderType::AuctionHouse || type == GuildOrderType::QuestReward; }
        bool IsCraftOrder() const { return type == GuildOrderType::Craft; }
        bool IsQuestRewardOrder() const { return type == GuildOrderType::QuestReward; }

        std::string GetTypeName() const
        {
            switch (type)
            {
            case GuildOrderType::Farm:         return "Farm";
            case GuildOrderType::Kill:         return "Kill";
            case GuildOrderType::Explore:      return "Explore";
            case GuildOrderType::Craft:        return "Craft";
            case GuildOrderType::AuctionHouse: return "AuctionHouse";
            case GuildOrderType::QuestReward:  return "QuestReward";
            default:                           return "None";
            }
        }
    };

    // 值计算器：解析玩家官员备注或共享列表生成机器人当前的公会订单
    class GuildOrderValue : public CalculatedValue<GuildOrder>
    {
    public:
        GuildOrderValue(PlayerbotAI* ai) : CalculatedValue<GuildOrder>(ai, "guild order", 60) {}

        GuildOrder Calculate() override;

        static uint32 FindItemByName(const std::string& name);
    private:
        static std::string TrimWhitespace(const std::string& str);
        static bool ParseOrderPrefix(const std::string& note, const std::string& prefix, std::string& outBody);
    };

    // 布尔值计算器：判断机器人当前是否存在有效的公会订单
    class HasGuildOrderValue : public BoolCalculatedValue
    {
    public:
        HasGuildOrderValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "has guild order", 10) {}

        bool Calculate() override { return AI_VALUE(GuildOrder, "guild order").IsValid(); }
    };

    // 布尔值计算器：判断当前是否有需要外出移动执行的公会订单
    class HasGuildTravelOrderValue : public BoolCalculatedValue
    {
    public:
        HasGuildTravelOrderValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "has guild travel order", 10) {}

        bool Calculate() override
        {
            GuildOrder order = AI_VALUE(GuildOrder, "guild order");
            if (!order.IsTravelOrder())
                return false;

            // If a Farm order has an amount, check inventory count. | 若采集订单指定数量，则检查背包内持有量是否达标
            if (order.type == GuildOrderType::Farm && order.amount > 0)
            {
                uint32 itemId = GuildOrderValue::FindItemByName(order.target);
                if (itemId)
                {
                    uint32 currentCount = ai->GetInventoryItemsCountWithId(itemId);
                    if (currentCount >= order.amount)
                        return false;
                }
            }

            if (order.type == GuildOrderType::QuestReward && order.amount > 0 && order.rewardItemId)
            {
                uint32 currentCount = ai->GetInventoryItemsCountWithId(order.rewardItemId);
                if (currentCount >= order.amount)
                    return false;
            }

            return true;
        }
    };

    // 布尔值计算器：判断当前公会订单是否为制造类订单
    class HasGuildCraftOrderValue : public BoolCalculatedValue
    {
    public:
        HasGuildCraftOrderValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "has guild craft order", 10) {}

        bool Calculate() override { return AI_VALUE(GuildOrder, "guild order").IsCraftOrder(); }
    };

    // Returns true if the bot has a QuestReward guild order whose quest is not yet in the quest log. | 若机器人有任务奖励类公会订单且任务尚未在日志中则返回 true
    // 布尔值计算器：判断是否有奖励类公会订单且尚未接取对应可重复任务
    class NeedsGuildQuestOrderAcceptValue : public BoolCalculatedValue
    {
    public:
        NeedsGuildQuestOrderAcceptValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "needs guild quest order accept", 5) {}

        bool Calculate() override
        {
            GuildOrder order = AI_VALUE(GuildOrder, "guild order");
            if (!order.IsQuestRewardOrder() || !order.questId)
                return false;

            // Already have enough of the reward item. | 已拥有足够数量的奖励物品
            if (order.amount > 0 && order.rewardItemId)
            {
                uint32 currentCount = ai->GetInventoryItemsCountWithId(order.rewardItemId);
                if (currentCount >= order.amount)
                    return false;
            }

            QuestStatus status = bot->GetQuestStatus(order.questId);
            // Quest already in log (incomplete or complete) no need to accept. | 任务已在任务日志中（无论是否完成）则无需再次接取
            if (status == QUEST_STATUS_INCOMPLETE || status == QUEST_STATUS_COMPLETE)
                return false;

            Quest const* quest = sObjectMgr.GetQuestTemplate(order.questId);
            if (!quest)
                return false;

            if (!bot->CanTakeQuest(quest, false))
                return false;

            if (!bot->SatisfyQuestLog(false))
                return false;

            return true;
        }
    };

    // 布尔值计算器：判断机器人是否缺少执行公会制造订单所需的专业材料
    class NeedsProfessionReagentsValue : public BoolCalculatedValue
    {
    public:
        NeedsProfessionReagentsValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "needs profession reagents", 120) {}

        bool Calculate() override;

        static std::vector<uint32> GetMissingReagents(PlayerbotAI* ai);
    };

    // 公会共享物品过滤类型枚举（按职业或全团/近战/远程/坦克/输出/治疗职责）
    enum class GuildShareFilter : uint8
    {
        FILTER_CLASS = 0,
        FILTER_ALL,
        FILTER_MELEE,
        FILTER_RANGED,
        FILTER_TANK,
        FILTER_DPS,
        FILTER_HEAL,
    };

    // 公会共享物品配置条目：绑定目标过滤条件、物品 ID 与每名在线成员期望数量
    struct GuildShareItemEntry
    {
        GuildShareFilter filter = GuildShareFilter::FILTER_CLASS;
        uint8 playerClass = 0;
        uint32 itemId = 0;
        uint32 amount = 0;

        bool MatchesPlayer(Player* player) const;
    };

    uint32 CountGuildFinishedItemDeficit(Player* bot, uint32 itemId, const std::vector<GuildShareItemEntry>& shareList);

    std::vector<std::pair<uint32, int8>> FindRepeatableQuestsRewardingItem(uint32 itemId);

    // 值计算器：解析公会信息页（GINFO）中的 Share 共享物资清单
    class GuildShareListValue : public CalculatedValue<std::vector<GuildShareItemEntry>>
    {
    public:
        GuildShareListValue(PlayerbotAI* ai) : CalculatedValue<std::vector<GuildShareItemEntry>>(ai, "guild share list", 30) {}

        std::vector<GuildShareItemEntry> Calculate() override;

        static uint8 ParseClassName(const std::string& name);
        static GuildShareFilter ParseRoleFilter(const std::string& name);
    };

    // Represents an item a nearby guild member needs, paired with the receiver. | 表示附近公会成员需要接收的物品及接收人信息
    // 公会物资分发目标结构：记录需要接收物品的附近公会成员与物品信息
    struct GuildShareTarget
    {
        Player* receiver = nullptr;
        uint32 itemId = 0;
        uint32 amount = 0;

        bool IsValid() const { return receiver && itemId; }
    };

    // 值计算器：寻找附近缺少公会共享清单物品的可交易公会成员
    class GuildShareTargetValue : public CalculatedValue<GuildShareTarget>
    {
    public:
        GuildShareTargetValue(PlayerbotAI* ai) : CalculatedValue<GuildShareTarget>(ai, "guild share target", 5) {}

        GuildShareTarget Calculate() override;
    };

    // Returns true if there is a valid guild share target nearby. | 附近存在有效的公会物资共享接收对象时返回 true
    // 布尔值计算器：判断附近是否存在需要分发公会共享物品的目标成员
    class HasGuildShareTargetValue : public BoolCalculatedValue
    {
    public:
        HasGuildShareTargetValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "has guild share target", 5) {}

        bool Calculate() override { return AI_VALUE(GuildShareTarget, "guild share target").IsValid(); }
    };

    // 值计算器：根据公会共享物资缺口自动生成制造订单
    class GuildShareCraftOrderValue : public CalculatedValue<GuildOrder>
    {
    public:
        GuildShareCraftOrderValue(PlayerbotAI* ai) : CalculatedValue<GuildOrder>(ai, "guild share craft order", 60) {}

        GuildOrder Calculate() override;
    };

    // 值计算器：根据共享成品与制造材料缺口自动生成采集或拍卖行采购订单
    class GuildShareFarmOrderValue : public CalculatedValue<GuildOrder>
    {
    public:
        GuildShareFarmOrderValue(PlayerbotAI* ai) : CalculatedValue<GuildOrder>(ai, "guild share farm order", 60) {}

        GuildOrder Calculate() override;
    };

    // 值计算器：自动筛选可通过可重复任务获取共享物资的任务订单
    class GuildShareQuestRewardOrderValue : public CalculatedValue<GuildOrder>
    {
    public:
        GuildShareQuestRewardOrderValue(PlayerbotAI* ai) : CalculatedValue<GuildOrder>(ai, "guild share quest reward order", 60) {}

        GuildOrder Calculate() override;
    };

    // 值计算器：返回当前最紧缺且可通过任务奖励提供的共享物品 ID
    class GuildShareQuestRewardItemValue : public CalculatedValue<uint32>
    {
    public:
        GuildShareQuestRewardItemValue(PlayerbotAI* ai) : CalculatedValue<uint32>(ai, "guild share quest reward item", 5) {}

        uint32 Calculate() override;
    };

    // 值计算器：读取公会注册表已收集的签名数量
    class PetitionSignsValue : public SingleCalculatedValue<uint8>
    {
    public:
        PetitionSignsValue(PlayerbotAI* ai) : SingleCalculatedValue<uint8>(ai, "petition signs") {}

        uint8 Calculate() override;
    };

    // 布尔值计算器：判断机器人是否未入会且公会注册表签名已达提交要求
    class CanHandInPetitionValue : public CalculatedValue<bool>
    {
    public:
        CanHandInPetitionValue(PlayerbotAI* ai) : CalculatedValue<bool>(ai, "can hand in guild petition") {}

        bool Calculate() override { return !bot->GetGuildId() && AI_VALUE2(uint32, "item count", chat->formatQItem(5863)) && AI_VALUE(uint8, "petition signs") >= sWorld.getConfig(CONFIG_UINT32_MIN_PETITION_SIGNS); };
    };

    // 布尔值计算器：判断是否已加入公会、未拥有战袍且携带足够购袍资金
    class CanBuyTabard : public CalculatedValue<bool>
    {
    public:
        CanBuyTabard(PlayerbotAI* ai) : CalculatedValue<bool>(ai, "can buy tabard") {}

        bool Calculate() override;
    };
}