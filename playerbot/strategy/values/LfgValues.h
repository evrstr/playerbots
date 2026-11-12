// 策略值头文件：LfgValues（随机副本匹配提议与机器人职责掩码）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/AiFactory.h"

namespace ai
{
    // 手动设置值：保存当前待响应的随机地下城/查找器（LFG）提议 ID
    class LfgProposalValue : public ManualSetValue<uint32>
    {
    public:
        LfgProposalValue(PlayerbotAI* ai) : ManualSetValue<uint32>(ai, 0, "lfg proposal") {}
    };

    // 值计算器：读取并返回机器人在队伍中承担的角色职责（坦克/治疗/输出）
    class BotRolesValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        BotRolesValue(PlayerbotAI* ai, std::string name = "bot roles") : Uint8CalculatedValue(ai, name, 10), Qualified() {}
        virtual uint8 Calculate() override
        {
            return AiFactory::GetPlayerRoles(bot);
        }
    };
}
