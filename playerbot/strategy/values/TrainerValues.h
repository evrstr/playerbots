// 策略值头文件：TrainerValues（全服训练师可学法术表、当前可学技能、可用训练师与学习花费）
#pragma once
#include "playerbot/ServerFacade.h"

namespace ai
{
    // trainableSpellMap[TrainerType][required class/race/skill][TrainerSpell] = {trainer entry}; | 全局可学法术映射：[训练师类型][职业/种族/技能需求][法术] = 训练师 Entry 列表
    typedef std::unordered_map<TrainerSpell const*, std::vector<int32>>  spellTrainerMap;
    typedef std::unordered_map<uint32, spellTrainerMap>          trainableSpellList;
    typedef std::unordered_map<TrainerType, trainableSpellList>         trainableSpellMap;

    // 单例值计算器：构建“训练师类型 -> 职业/种族/专业要求 -> 训练法术 -> 训练师列表”全局索引
    class TrainableSpellMapValue : public SingleCalculatedValue<trainableSpellMap*>
    {
    public:
        TrainableSpellMapValue(PlayerbotAI* ai) : SingleCalculatedValue<trainableSpellMap*>(ai, "trainable spell map") {}

        virtual trainableSpellMap* Calculate() override;
        virtual ~TrainableSpellMapValue() override { delete value; }
    };

    // 值计算器：筛选当前机器人满足等级、种族/职业与前置条件且尚未学会的可训练法术列表
    class TrainableSpellsValue : public CalculatedValue<std::vector< TrainerSpell const*>>, public Qualified
    {
    public:
        TrainableSpellsValue(PlayerbotAI* ai, std::string name = "trainable spells", int checkInterval = 5) : CalculatedValue<std::vector<TrainerSpell const*>>(ai, name, checkInterval), Qualified(){}

        virtual std::vector<TrainerSpell const*> Calculate() override;

        virtual std::string Format() override;
    };

    // 值计算器：汇总教授当前所有可学法术的可用训练师 NPC Entry 列表
    class AvailableTrainersValue : public CalculatedValue<std::vector<int32>>, public Qualified
    {
    public:
        AvailableTrainersValue(PlayerbotAI* ai, std::string name = "available trainers", int checkInterval = 5) : CalculatedValue<std::vector<int32>>(ai, name, checkInterval), Qualified() {}

        virtual std::vector<int32> Calculate() override;
    };

    // 值计算器：累计当前机器人学习所有可学法术所需的总金币花费（铜币）
    class TrainCostValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        TrainCostValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "train cost", 60), Qualified() {}

        virtual uint32 Calculate() override;
    };
}

