// 策略值头文件：EntryValues（副本特定交互对象 Entry 常量列表）
#pragma once

#include "playerbot/playerbot.h"
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 字符串值计算器：提供熔火之心（MC）灭火符文的 GameObject Entry 列表
    class MCRunesValue : public StringCalculatedValue, public Qualified
    {
    public:
        MCRunesValue(PlayerbotAI* ai, std::string name = "mc runes") : StringCalculatedValue(ai, name, 1), Qualified() {}

        virtual std::string Calculate() override { return "176951,176952,176953,176954,176955,176956,176957"; };

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "mc runes"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "entry"; }
        virtual std::string GetHelpDescription()
        {
            return "This value contains the entries of the Molten Core runes.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };
}

// 字符串值计算器：提供黑翼之巢（BWL）压制装置的 GameObject Entry 编号
class SuppressionDevicesValue : public StringCalculatedValue, public Qualified
{
public:
    SuppressionDevicesValue(PlayerbotAI* ai, std::string name = "suppression devices") : StringCalculatedValue(ai, name, 1), Qualified() {}

    virtual std::string Calculate() override { return "179784"; }

#ifdef GenerateBotHelp
    virtual std::string GetHelpName() { return "suppression devices"; }
    virtual std::string GetHelpTypeName() { return "entry"; }
    virtual std::string GetHelpDescription()
    {
        return "This value contains the entries of the Blackwing Lair Suppression Devices.";
    }
    virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
};