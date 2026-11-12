// 策略值头文件：QuestValues（全服任务关联映射、可接/可交/任务目标追踪与对话状态）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/TravelMgr.h"

namespace ai
{          
    class GuidPosition;

    // ObjectMgr 镜像访问类：暴露保护的任务关系与对话状态查询方法
    class QuestObjectMgr : ObjectMgr
    {
    public:
        QuestRelationsMap& GetCreatureQuestRelationsMap() { return m_CreatureQuestRelations; }
        QuestRelationsMap& GetCreatureQuestInvolvedRelationsMap() { return m_CreatureQuestInvolvedRelations; }
        QuestRelationsMap& GetGOQuestRelationsMap() { return m_GOQuestRelations; }
        QuestRelationsMap& GetGOQuestInvolvedRelationsMap() { return m_GOQuestInvolvedRelations; }
    };

    // 任务奖励选择策略枚举（配置驱动/最高价值/护甲专精/询问）
    enum class QuestRewardOptionType : uint8
    {
        QUEST_REWARD_CONFIG_DRIVEN = 0x00,
        QUEST_REWARD_OPTION_AUTO = 0x01,
        QUEST_REWARD_OPTION_LIST = 0x02,
        QUEST_REWARD_OPTION_ASK = 0x03,
    };

    //EntryQuestRelationMap[entry][questId] = QuestRelationFlag | Entry 到任务关系掩码的映射表
    typedef std::unordered_map<uint32, uint32> questRelationMap;
    typedef std::unordered_map<int32, questRelationMap> EntryQuestRelationMap;

    //questGuidpMap[questId][QuestRelationFlag][entry] = {GuidPosition} | 任务 ID -> 关系标志 -> Entry -> 世界坐标列表映射
    typedef std::unordered_map<int32, std::list<GuidPosition>> questEntryGuidps;
    typedef std::unordered_map<uint32, questEntryGuidps> questRelationGuidps;
    typedef std::unordered_map<uint32, questRelationGuidps> questGuidpMap;    

    //questGiverMap[questId] = {GuidPosition} | 任务 ID -> 发布者坐标列表映射
    typedef std::unordered_map<uint32, std::list<GuidPosition>> questGiverMap;
    
    
    //Returns the quest relation Flags for all entries and quests | 返回所有实体与各任务间的关系标志映射
    // 单例值计算器：构建“生物/游戏对象 Entry -> 任务 ID 与任务用途（接取/提交/击杀/掉落/购买）”全映射
    class EntryQuestRelationMapValue : public SingleCalculatedValue<EntryQuestRelationMap>
    {
    public:
        EntryQuestRelationMapValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "entry quest relation map") {}

        virtual EntryQuestRelationMap Calculate() override;
    };
        
    //Generic quest object finder | 通用任务对象搜索器
    // 网格遍历数据工作器：遍历全服生成生物与游戏对象，填充各任务对应的世界坐标集合
    class FindQuestObjectData
    {
    public:
        FindQuestObjectData() { GetObjectiveEntries(); }

        void GetObjectiveEntries();
        bool operator()(CreatureDataPair const& dataPair);
        bool operator()(GameObjectDataPair const& dataPair);
        questGuidpMap GetResult() const { return data; };
    private:
        std::unordered_map<int32, std::vector<std::pair<uint32, TravelDestinationPurpose>>> entryMap;
        std::unordered_map<uint32, std::vector<std::pair<uint32, TravelDestinationPurpose>>> itemMap;

        EntryQuestRelationMap relationMap;

        questGuidpMap data;
    };
   
    //All objects to start, do or finish a quest. | 包含所有接取、执行和交付任务所需对象的全量映射
    // 单例值计算器：生成完整的“任务 ID -> 任务用途 -> Entry -> GuidPosition 列表”全局缓存
    class QuestGuidpMapValue : public SingleCalculatedValue<questGuidpMap>
    {
    public:
        QuestGuidpMapValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "quest guidp map") {}

        virtual questGuidpMap Calculate() override;
    };       
    
    //All questgivers and their quests that are useful for a specific level | 按等级筛选的所有可用任务发布者映射
    // 单例值计算器：按等级区间缓存所有可提供任务的任务发布者位置表
    class QuestGiversValue : public SingleCalculatedValue<questGiverMap>, public Qualified
    {
    public:
        QuestGiversValue(PlayerbotAI* ai) : SingleCalculatedValue(ai, "quest givers"), Qualified() {}
        virtual questGiverMap Calculate() override;
    };
    
    //All questgivers that have a quest for the bot. | 当前对机器人有可接任务的所有任务发布者
    // 位置列表计算器：获取当前适合机器人接取且等级符合的任务发布者坐标列表
    class ActiveQuestGiversValue : public CalculatedValue<std::list<GuidPosition>>
    {
    public:
        ActiveQuestGiversValue(PlayerbotAI* ai) : CalculatedValue(ai, "active quest givers", 5) {}
        virtual std::list<GuidPosition> Calculate() override;
    };    
    
    //All quest takers that the bot has a quest for. | 当前对机器人有可交付任务的所有任务接收者
    // 位置列表计算器：获取机器人已完成任务可前往交付的任务接收者坐标列表
    class ActiveQuestTakersValue : public CalculatedValue<std::list<GuidPosition>>
    {
    public:
        ActiveQuestTakersValue(PlayerbotAI* ai) : CalculatedValue(ai, "active quest takers", 5) {}
        virtual std::list<GuidPosition> Calculate() override;
    };

    //All objectives that the bot still has to complete. | 机器人尚未完成的任务目标对象列表
    // 位置列表计算器：获取机器人当前未完成任务仍需前往击杀/收集/交互的目标坐标列表
    class ActiveQuestObjectivesValue : public CalculatedValue<std::list<GuidPosition>>
    {
    public:
        ActiveQuestObjectivesValue(PlayerbotAI* ai) : CalculatedValue(ai, "active quest objectives", 5) {}
        virtual std::list<GuidPosition> Calculate() override;
    };

    //Check if a specific entry is a quest objective that the bot has to complete. | 检查特定实体 Entry 是否为当前尚未完成的任务目标
    // 布尔值计算器：判断指定生物或游戏对象 Entry 是否为机器人当前未完成任务所需目标
    class NeedForQuestValue : public BoolCalculatedValue, public Qualified
    {
    public:
        NeedForQuestValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "need for quest", 5), Qualified() {}
        virtual bool Calculate() override;
    };

    //Free quest log slots | 剩余可用任务日志空位数
    // 值计算器：统计机器人任务日志中当前剩余的可用任务栏位数量
    class FreeQuestLogSlotValue : public Uint8CalculatedValue
    {
    public:
        FreeQuestLogSlotValue(PlayerbotAI* ai) : Uint8CalculatedValue(ai, "free quest log slots", 2) {}
        virtual uint8 Calculate() override;
    };
    
    //Dialog status npc  | NPC 任务对话状态值
    // 值计算器：查询机器人与指定任务 NPC/对象交互时应显示的任务状态图标
    class DialogStatusValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        DialogStatusValue(PlayerbotAI* ai, std::string name = "dialog status") : Uint32CalculatedValue(ai, name , 2), Qualified() {}
        static uint32 getDialogStatus(Player* bot, int32 questgiver, uint32 questId = 0);
        virtual uint32 Calculate() override  { return getDialogStatus(bot, stoi(getQualifier())); }
    };

    //Dialog status npc quest | 针对单个任务查询 NPC 对话状态
    // 值计算器：查询指定 NPC 上某个特定任务的交互状态
    class DialogStatusQuestValue : public DialogStatusValue
    {
    public:
        DialogStatusQuestValue(PlayerbotAI* ai) : DialogStatusValue(ai, "dialog status quest") {}
        virtual uint32 Calculate() override { return getDialogStatus(bot, getMultiQualifierInt(getQualifier(), 0, " "), getMultiQualifierInt(getQualifier(), 1, " ")); }
    };

    //Can accept quest from npc | 是否可从该 NPC 接取任务
    // 布尔值计算器：判断是否可以从指定对象处接取新任务（含自动完成任务）
    class CanAcceptQuestValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CanAcceptQuestValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can accept quest npc"), Qualified() {}
        static bool CanAcceptAutoCompleteQuest(Player* bot, int32 questgiver);
        virtual bool Calculate() override  { return AI_VALUE2(uint32, "dialog status", getQualifier()) == DIALOG_STATUS_AVAILABLE || CanAcceptAutoCompleteQuest(bot, stoi(getQualifier()));};
    };

    //Can accept low level quest from npc | 是否可从该 NPC 接取低等级任务
    // 布尔值计算器：判断是否可以从指定对象处接取低等级灰色任务
    class CanAcceptQuestLowLevelValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CanAcceptQuestLowLevelValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can accept quest low level npc"), Qualified() {}

        virtual bool Calculate() override
        {
            uint32 dialogStatus = AI_VALUE2(uint32, "dialog status", getQualifier());
            bool autoComplete = CanAcceptQuestValue::CanAcceptAutoCompleteQuest(bot, stoi(getQualifier()));
#ifndef MANGOSBOT_TWO
            return dialogStatus == DIALOG_STATUS_CHAT || autoComplete;
#else
            return dialogStatus == DIALOG_STATUS_LOW_LEVEL_AVAILABLE || autoComplete;
#endif   
        };
    };

    //Has good reward | 任务是否提供值得获取的奖励装备
    // 布尔值计算器：判断指定任务的奖励物品中是否包含职业专属或装备升级品
    class NeedQuestRewardValue : public BoolCalculatedValue, public Qualified
    {
    public:
        NeedQuestRewardValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "need quest reward"), Qualified() {}
        virtual bool Calculate() override;
    };

    //Can hand in quest to npc | 是否可向该 NPC 交回已完成任务
    // 布尔值计算器：判断指定对象处是否有当前机器人已完成且可交付的任务
    class CanTurnInQuestValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CanTurnInQuestValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can turn in quest npc"), Qualified() {}

        virtual bool Calculate() override
        {
            uint32 dialogStatus = AI_VALUE2(uint32, "dialog status", getQualifier());
#ifdef MANGOSBOT_ZERO  
            return dialogStatus == DIALOG_STATUS_REWARD2;
#else
            return dialogStatus == DIALOG_STATUS_REWARD2 || dialogStatus == DIALOG_STATUS_REWARD;
#endif  
        };
    };

    //Repeatable in quest to npc | 是否可在该 NPC 处重复提交任务
    // 布尔值计算器：判断指定对象处是否存在可重复交付的任务
    class CanRepeatQuestValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CanRepeatQuestValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can repeat quest npc"), Qualified() {}

        virtual bool Calculate() override
        {
            return AI_VALUE2(uint32, "dialog status", getQualifier()) == DIALOG_STATUS_REWARD_REP;
        };
    };

    //Need objective | 是否仍需完成对应任务目标
    // 布尔值计算器：检查特定任务或具体任务目标（击杀/收集/探索）是否仍需完成
    class NeedQuestObjectiveValue : public BoolCalculatedValue, public Qualified
    {
    public:
        NeedQuestObjectiveValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "need quest objective"), Qualified() {}
        static bool CanGetItemSomewhere(const uint32 itemId, const uint32 reqCount, Player* bot);
        static bool IsNeeded(PlayerbotAI* ai, uint32 questId, uint32 objective, int32 entry);
        static bool HasIncompleteObjective(PlayerbotAI* ai);
        virtual bool Calculate() override;
    };

    //Can use item on | 是否可对目标使用指定物品
    // 布尔值计算器：判断指定物品是否可对指定世界对象使用以推进任务或触发特效
    class CanUseItemOn : public BoolCalculatedValue, public Qualified
    {
    public:
        CanUseItemOn(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can use item on"), Qualified() {}
        static bool IsQuestItemForEntry(PlayerbotAI* ai, uint32 itemId, int32 entry);
        static bool HasQuestItemForEntry(PlayerbotAI* ai, int32 entry);
        virtual bool Calculate() override;
    };

    // quest reward | 任务奖励挑选策略设置
    // 手动设置值：控制机器人挑选任务奖励物品的策略选项
    class QuestRewardValue : public ManualSetValue<uint8>, public Qualified
    {
    public:
        QuestRewardValue(PlayerbotAI* ai) :
            ManualSetValue<uint8>(ai, static_cast<uint8>(QuestRewardOptionType::QUEST_REWARD_CONFIG_DRIVEN), "quest reward"),
            Qualified() {}
    };

    // 布尔值计算器：检测附近可交互 NPC 或游戏对象中是否存在可交付或可接取任务的对象
    class HasNearbyQuestTakerValue : public BoolCalculatedValue
    {
    public:
        HasNearbyQuestTakerValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "has nearby quest taker", 30) {}

        virtual bool Calculate() override; // 检测周围是否有可交互的任务发布或交付对象
    };
}
