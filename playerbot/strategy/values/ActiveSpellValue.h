// 策略值头文件：ActiveSpellValue（当前正在施放的法术 ID）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 值计算器：获取机器人当前正在施放的法术 ID（未施法时返回 0）
    class ActiveSpellValue : public CalculatedValue<uint32>
    {
    public:
        ActiveSpellValue(PlayerbotAI* ai, std::string name = "active spell") : CalculatedValue<uint32>(ai, name) {}

        // 计算并返回当前正在施放的法术 ID
        virtual uint32 Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "active spell"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "spell"; }
        virtual std::string GetHelpDescription() { return "This value contains the spell id of the spell that the bot is currently casting."; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
