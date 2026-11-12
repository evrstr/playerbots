// 策略值头文件：BudgetValues（修理费用与各类金币预算评估）
#pragma once

#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/NamedObjectContext.h"
#include "playerbot/playerbot.h"

namespace ai
{
    // 资金用途枚举：修理、弹药、学技能、旅行、装备、消耗品、公会、专业、拍卖行、坐骑等
    enum class NeedMoneyFor : uint32
    {
        none = 0,
        repair = 1,
        ammo = 2,
        spells = 3,
        travel = 4,
        consumables = 5,
        gear = 6,
        guild = 7,
        skilltraining = 8,
        tradeskill = 9,
        ah = 10,
        mount = 11,
        anything = 12
    };

    // 值计算器：计算当前已损坏装备与背包物品的实际修理费用（铜币）
    class RepairCostValue : public Uint32CalculatedValue
    {
    public:
        RepairCostValue(PlayerbotAI* ai, std::string name = "repair cost", int checkInterval = 60) : Uint32CalculatedValue(ai, name, checkInterval) {}

        static uint32 RepairCost(const Item* item, bool fullCost = false);

        virtual uint32 Calculate() override;
    };

    // 值计算器：计算全身装备及已损坏物品在满耐久损失时的最大潜在修理费用
    class MaxGearRepairCostValue : public RepairCostValue
    {
    public:
        MaxGearRepairCostValue(PlayerbotAI* ai) : RepairCostValue(ai,"max repair cost",checkInterval) {}

        virtual uint32 Calculate() override;
    };

    // 值计算器：计算关键武器/远程槽位损坏物品的最低必要修理费用
    class MinRepairCostValue : public RepairCostValue
    {
    public:
        MinRepairCostValue(PlayerbotAI* ai) : RepairCostValue(ai, "min repair cost", checkInterval) {}

        virtual uint32 Calculate() override;
    };

    // 值计算器：根据限定符计算特定用途所需的预留金币数额
    class MoneyNeededForValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        MoneyNeededForValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "money needed for", 60), Qualified() {}
        virtual uint32 Calculate() override;
    };

    // 值计算器：累计当前用途及更高优先级用途所需的总预留资金
    class TotalMoneyNeededForValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        TotalMoneyNeededForValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "total money needed for", 60), Qualified() {}
        virtual uint32 Calculate() override;
    private:
        std::vector<NeedMoneyFor> saveMoneyFor = { NeedMoneyFor::repair,NeedMoneyFor::ammo, NeedMoneyFor::ah, NeedMoneyFor::guild, NeedMoneyFor::spells, NeedMoneyFor::travel };
    };

    // 值计算器：计算扣除所有高优先级预留资金后可用于指定用途的自由金币
    class FreeMoneyForValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        FreeMoneyForValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai, "free money for"), Qualified() {}
        virtual uint32 Calculate() override;
    };

    // 布尔值计算器：判断机器人当前持有的金币是否足以覆盖指定用途需求
    class HasAllMoneyForValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasAllMoneyForValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "has all money for"), Qualified() {}
        virtual bool Calculate() override;
    };
    
    // 布尔值计算器：判断是否需要向主控/机制获取额外金币（例如弹药资金不足）
    class ShouldGetMoneyValue : public BoolCalculatedValue
    {
    public:
        ShouldGetMoneyValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should get money",2) {}
        virtual bool Calculate() override { return bot->GetLevel() > 6 && !AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::ammo); };
    };
}

