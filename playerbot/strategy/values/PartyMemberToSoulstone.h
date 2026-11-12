// 策略值头文件：PartyMemberToSoulstone（适合绑定灵魂石的队友）
#pragma once
#include "playerbot/strategy/Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    // 目标值计算器：为术士挑选尚未拥有灵魂石效果的坦克或治疗队友
    class PartyMemberToSoulstone : public PartyMemberValue
    {
    public:
        PartyMemberToSoulstone(PlayerbotAI* ai, std::string name = "party member to soulstone") : PartyMemberValue(ai,name) {}

    protected:
        virtual ObjectGuid Calculate() override;
    };
}
