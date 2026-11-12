// 策略值头文件：TravelValues（旅行目的地类型、实体坐标缓存、旅行目标状态与目的判定）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/AiObjectContext.h"

namespace ai
{
    //Definition | 旅行基础类型与全局缓存定义
    using DestinationEntry = int32;
    using EntryGuidps = std::unordered_map<DestinationEntry, std::vector<AsyncGuidPosition>>;

    //All creature and gameobject entries and reason a bot might want to travel to them. | 所有生物和游戏对象 Entry 及其对应的坐标点集合
    // 单例值计算器：收集全服各生物和游戏对象 Entry 对应的世界坐标集合（用于长途旅行导航）
    class EntryGuidpsValue : public SingleCalculatedValue<EntryGuidps>
    {
    public:
        EntryGuidpsValue(PlayerbotAI* ai, std::string name = "entry guidps") : SingleCalculatedValue(ai, name) {};

        virtual EntryGuidps Calculate() override;
    };

    using DestinationPurose = uint32;

    using EntryTravelPurposeMap = std::unordered_map<DestinationEntry, DestinationPurose>;

    //All creature and gameobject entries and reason a bot might want to travel to them. | 所有生物和游戏对象 Entry 及其对应的旅行用途掩码
    // 单例值计算器：预先计算每个生物和游戏对象 Entry 可承担的旅行目的掩码（如商人/修理/采集/刷怪等）
    class EntryTravelPurposeMapValue : public SingleCalculatedValue<EntryTravelPurposeMap>
    {
    public:
        EntryTravelPurposeMapValue(PlayerbotAI* ai, std::string name = "entry travel purpose") : SingleCalculatedValue(ai, name) {};

        virtual EntryTravelPurposeMap Calculate() override;

        static uint32 SkillIdToGatherEntry(int32 entry);
    };

    // 旅行目的地用途位掩码枚举（任务、RPG、训练、修理、商人、拍卖、邮箱、刷怪、首领、采集、探索、银行）
    enum class TravelDestinationPurpose : uint32
    {
        None = 0,
        QuestGiver = 1 << 0,
        QuestObjective1 = 1 << 1,
        QuestObjective2 = 1 << 2,
        QuestObjective3 = 1 << 3,
        QuestObjective4 = 1 << 4,
        QuestAllObjective = QuestObjective1 | QuestObjective2 | QuestObjective3 | QuestObjective4,
        QuestTaker = 1 << 5,
        GenericRpg = 1 << 6,
        Trainer = 1 << 7,
        Repair = 1 << 8,
        Vendor = 1 << 9,
        AH = 1 << 10,
        Mail = 1 << 11,
        Grind = 1 << 12,
        Boss = 1 << 13,
        GatherSkinning = 1 << 14,
        GatherMining = 1 << 15,
        GatherHerbalism = 1 << 16,
        GatherFishing = 1 << 17,
        Bank = 1 << 18,
        Explore = 1 << 19,
        MaxFlag = 1 << 20
    };

    // 用途枚举到可读字符串名称的静态映射表
    const std::unordered_map<TravelDestinationPurpose, std::string> TravelDestinationPurposeName =
    {
        {TravelDestinationPurpose::None, "None"},
        {TravelDestinationPurpose::QuestGiver, "QuestGiver"},
        {TravelDestinationPurpose::QuestObjective1, "QuestObjective1"},
        {TravelDestinationPurpose::QuestObjective2, "QuestObjective2"},
        {TravelDestinationPurpose::QuestObjective3 , "QuestObjective3"},
        {TravelDestinationPurpose::QuestObjective4, "QuestObjective4"},
        {TravelDestinationPurpose::QuestTaker, "QuestTaker"},
        {TravelDestinationPurpose::GenericRpg , "GenericRpg"},
        {TravelDestinationPurpose::Trainer, "Trainer"},
        {TravelDestinationPurpose::Repair, "Repair"},
        {TravelDestinationPurpose::Vendor, "Vendor"},
        {TravelDestinationPurpose::AH , "AH"},
        {TravelDestinationPurpose::Mail , "Mail"},
        {TravelDestinationPurpose::Grind , "Grind"},
        {TravelDestinationPurpose::Boss, "Boss"},
        {TravelDestinationPurpose::GatherSkinning , "GatherSkinning"},
        {TravelDestinationPurpose::GatherMining, "GatherMining"},
        {TravelDestinationPurpose::GatherHerbalism, "GatherHerbalism"},
        {TravelDestinationPurpose::GatherFishing, "GatherFishing"},
        {TravelDestinationPurpose::Explore, "Explore"},
        {TravelDestinationPurpose::Bank, "Bank"},
        {TravelDestinationPurpose::MaxFlag, "MaxFlag"}
    };

    class TravelDestination;

    using DestinationList = std::vector<TravelDestination*>;

    //TypedDestinationMap[Purpose][QuestId/Entry]={TravelDestination} | 按用途与任务/Entry 索引的旅行目的地映射表
    using EntryDestinationMap = std::unordered_map<int32, DestinationList>;
    using PurposeDestinationMap = std::unordered_map<TravelDestinationPurpose, EntryDestinationMap>;

    //Usage | 旅行查询及异步结果容器定义

    //TravelPoint[point, destination, distance] | 旅行点元组：(目的地指针, 世界坐标, 距离)
    using TravelPoint = std::tuple<TravelDestination*, WorldPosition*, float>;
    using TravelPointList = std::vector<TravelPoint>;
    using PartitionedTravelList = std::map<uint32, TravelPointList>;
    using FutureDestinations = std::future<PartitionedTravelList>;

    typedef std::set<uint32> focusQuestTravelList;

    // 手动设置值：保存主控或任务系统指定的重点追踪任务 ID 集合
    class FocusTravelTargetValue : public ManualSetValue<focusQuestTravelList>
    {
    public:
        FocusTravelTargetValue(PlayerbotAI* ai, focusQuestTravelList defaultValue = {}, std::string name = "focus travel target") : ManualSetValue<focusQuestTravelList>(ai, defaultValue, name) {};
    };

    // 布尔值计算器：判断当前是否设置了重点追踪的旅行任务
    class HasFocusTravelTargetValue : public BoolCalculatedValue
    {
    public:
        HasFocusTravelTargetValue(PlayerbotAI* ai, std::string name = "has focus travel target", int checkInterval = 10) : BoolCalculatedValue(ai, name, checkInterval) {}

        virtual bool Calculate() override { return !AI_VALUE(focusQuestTravelList, "focus travel target").empty(); };
    };

    //Target fetching | 旅行目标异步获取与状态值

    // 手动设置值：持有异步后台线程正在计算的候选旅行目的地结果 Future
    class FutureTravelDestinationsValue : public ManualSetValue<FutureDestinations*>
    {
    public:
        FutureTravelDestinationsValue(PlayerbotAI* ai, std::string name = "future travel destinations") : ManualSetValue<FutureDestinations*>(ai, new FutureDestinations, name) {}

        ~FutureTravelDestinationsValue() override { delete value; }
    };

    // 手动设置值：按限定符标记当前是否已无可用的旅行目的地（避免重复无效搜索）
    class NoActiveTravelDestinationsValue : public ManualSetValue<bool>, public Qualified
    {
    public:
        NoActiveTravelDestinationsValue(PlayerbotAI* ai, std::string name = "no active travel destinations") : ManualSetValue<bool>(ai, {}, name), Qualified() {}
    };

    // 布尔值计算器：判断队长或自身的旅行目标当前是否处于有效激活状态
    class TravelTargetActiveValue : public BoolCalculatedValue
    {
    public:
        TravelTargetActiveValue(PlayerbotAI* ai, std::string name = "travel target active", int checkInterval = 5) : BoolCalculatedValue(ai, name, checkInterval) {};

        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断队长或自身的旅行目标是否处于就绪待出发状态
    class TravelTargetReadyValue : public BoolCalculatedValue
    {
    public:
        TravelTargetReadyValue(PlayerbotAI* ai, std::string name = "travel target ready", int checkInterval = 5) : BoolCalculatedValue(ai, name, checkInterval) {};

        virtual bool Calculate() override;
    };    

    // 布尔值计算器：判断队长或自身的旅行目标是否正处于赶路状态
    class TravelTargetTravelingValue : public BoolCalculatedValue
    {
    public:
        TravelTargetTravelingValue(PlayerbotAI* ai, std::string name = "travel target traveling", int checkInterval = 5) : BoolCalculatedValue(ai, name, checkInterval){};

        virtual bool Calculate() override;
    };    

    // 布尔值计算器：判断队长或自身的旅行目标是否已抵达并处于执行状态
    class TravelTargetWorkingValue : public BoolCalculatedValue
    {
    public:
        TravelTargetWorkingValue(PlayerbotAI* ai, std::string name = "travel target working", int checkInterval = 5) : BoolCalculatedValue(ai, name, checkInterval) {};

        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断机器人当前是否真正需要前往执行指定类型的旅行目的（如修理/卖物/采集等）
    class NeedTravelPurposeValue : public BoolCalculatedValue, public Qualified
    {
    public:
        NeedTravelPurposeValue(PlayerbotAI* ai, std::string name = "need travel purpose", int checkInterval = 5) : BoolCalculatedValue(ai, name, checkInterval), Qualified() {};

        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断机器人当前是否应该前往特定名称的地点（如主城战场/野外PvP/公会集会）
    class ShouldTravelNamedValue : public BoolCalculatedValue, public Qualified
    {
    public:
        ShouldTravelNamedValue(PlayerbotAI* ai, std::string name = "should travel named", int checkInterval = 5) : BoolCalculatedValue(ai, name, checkInterval), Qualified() {};

        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断机器人当前是否处于主世界大地图（非副本/非特殊位面）
    class InOverworldValue : public BoolCalculatedValue
    {
    public:
        InOverworldValue(PlayerbotAI* ai, std::string name = "in overworld", int checkInterval = 10) : BoolCalculatedValue(ai, name, checkInterval) {};

        virtual bool Calculate() override {return WorldPosition(bot).isOverworld();}
    };

    //Keep using this target | 用于判断当前任务目标阶段是否依然有效需要继续前往

    // 布尔值计算器：判断指定任务在特定阶段（接取/交付/目标1-4）是否仍处于需要执行状态
    class QuestStageActiveValue : public BoolCalculatedValue, public Qualified
    {
    public:
        QuestStageActiveValue(PlayerbotAI* ai, std::string name = "quest stage active", int checkInterval = 1) : BoolCalculatedValue(ai, name, checkInterval), Qualified() {};

        virtual bool Calculate() override;
    };
}