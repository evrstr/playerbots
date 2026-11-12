// 策略值头文件：PartyMemberToDispel（需要驱散减益的队友）
#pragma once
#include "playerbot/strategy/Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    // 目标值计算器：根据指定驱散类型查找施法范围内需要驱散的存活队友
    class PartyMemberToDispel : public PartyMemberValue, public Qualified
    {
    public:
        PartyMemberToDispel(PlayerbotAI* ai, std::string name = "party member to dispel") :
          PartyMemberValue(ai, name), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };
}
