// 策略值头文件：AvailableLootValue（可用战利品栈、拾取目标与可拾取判断）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/LootObjectStack.h"
#include "playerbot/ServerFacade.h"

namespace ai
{

    // 手动设置值：管理机器人当前可用的战利品对象栈
    class AvailableLootValue : public ManualSetValue<LootObjectStack*>
    {
    public:
        AvailableLootValue(PlayerbotAI* ai, std::string name = "available loot") : ManualSetValue<LootObjectStack*>(ai, NULL, name)
        {
            value = new LootObjectStack(bot);
        }

        virtual ~AvailableLootValue() override
        {
            if (value)
                delete value;
        }
    };

    // 手动设置值：存储当前选定的拾取目标对象
    class LootTargetValue : public ManualSetValue<LootObject>
    {
    public:
        LootTargetValue(PlayerbotAI* ai, std::string name = "loot target") : ManualSetValue<LootObject>(ai, LootObject(), name) {}
    };

    // 布尔值计算器：判断当前拾取目标是否有效、可拾取且处于交互距离内
    class CanLootValue : public BoolCalculatedValue
    {
    public:
        CanLootValue(PlayerbotAI* ai, std::string name = "can loot") : BoolCalculatedValue(ai, name) {}

        virtual bool Calculate() override
        {
            LootObject loot = AI_VALUE(LootObject, "loot target");

            return !loot.IsEmpty() &&
                    loot.GetWorldObject(bot) &&    
                    loot.IsLootPossible(bot) &&
                    sServerFacade.IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "loot target"), INTERACTION_DISTANCE);
        }
    };
}
