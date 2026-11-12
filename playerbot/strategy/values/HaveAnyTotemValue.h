// 策略值头文件：HaveAnyTotemValue（检测附近是否存在任意图腾）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"
#include "playerbot/LootObjectStack.h"

namespace ai
{
    // 布尔值计算器：检查附近 NPC 列表中是否存在任意图腾单位
    class HaveAnyTotemValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HaveAnyTotemValue(PlayerbotAI* ai, std::string name = "have any totem") : BoolCalculatedValue(ai, name), Qualified() {}

        bool Calculate() override
        {
            std::list<ObjectGuid> units = *context->GetValue<std::list<ObjectGuid> >("nearest npcs");
            for (std::list<ObjectGuid>::iterator i = units.begin(); i != units.end(); i++)
            {
                Unit* unit = ai->GetUnit(*i);
                if (!unit)
                    continue;

                Creature* creature = dynamic_cast<Creature*>(unit);
                if (creature && creature->IsTotem()) 
                {
                    return true;
                }
            }

            return false;
        }
    };
}
