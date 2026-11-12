// 策略值头文件：SpellIdValue（按名称或物品解析最高/合适等级法术 ID 及载具技能 ID）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
    // 值计算器：根据法术名称或物品链接从机器人和宠物法术书中解析最匹配的法术 ID
    class SpellIdValue : public CalculatedValue<uint32>, public Qualified
    {
    public:
        SpellIdValue(PlayerbotAI* ai);
        virtual uint32 Calculate() override;
    };

    // 值计算器：从当前控制载具的技能栏中按名称匹配对应的法术 ID
    class VehicleSpellIdValue : public CalculatedValue<uint32>, public Qualified
    {
    public:
        VehicleSpellIdValue(PlayerbotAI* ai);
        virtual uint32 Calculate() override;
    };
}
