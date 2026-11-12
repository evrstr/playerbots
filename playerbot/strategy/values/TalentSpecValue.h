// 策略值头文件：TalentSpecValue（机器人当前天赋专精枚举值）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/PlayerTalentSpec.h"

namespace ai
{
    // 手动设置值：保存机器人当前识别或配置的天赋专精类型
    class TalentSpecValue : public ManualSetValue<PlayerTalentSpec>
    {
    public:
        TalentSpecValue(PlayerbotAI* ai, std::string name = "talent spec") : ManualSetValue<PlayerTalentSpec>(ai, PlayerTalentSpec::TALENT_SPEC_INVALID, name) {}
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "talent spec"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "talent spec"; }
        virtual std::string GetHelpDescription() { return "This value stores the current talent spec for the bot."; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
