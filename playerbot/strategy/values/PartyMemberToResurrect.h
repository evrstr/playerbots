// 策略值头文件：PartyMemberToResurrect（需要复活的死亡队友）
#pragma once
#include "playerbot/strategy/Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    // 目标值计算器：查找施法范围内尚未被其他治疗者施放复活术的死亡队友尸体
    class PartyMemberToResurrect : public PartyMemberValue
    {
    public:
        PartyMemberToResurrect(PlayerbotAI* ai, std::string name = "party member to resurrect") :
          PartyMemberValue(ai,name) {}
    
    protected:
        virtual ObjectGuid Calculate() override;
    };
}
