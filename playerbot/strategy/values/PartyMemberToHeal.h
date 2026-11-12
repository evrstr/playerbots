// 策略值头文件：PartyMemberToHeal（需治疗/保护/解定身的队友选择）
#pragma once
#include "playerbot/strategy/Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    // 目标值计算器：按紧急血线、坦克优先与预读治疗策略挑选最需要治疗的队友或宠物
    class PartyMemberToHeal : public PartyMemberValue
    {
    public:
        PartyMemberToHeal(PlayerbotAI* ai, std::string name = "party member to heal") :
          PartyMemberValue(ai, name) {}
    
    protected:
        virtual ObjectGuid Calculate() override;
        bool CanHealPet(Pet* pet);
        virtual bool Check(Unit* player);

    private:
        std::vector<Player*> GetPartyMembers();
    };

    // 目标值计算器：查找当前正在被敌人近战/直接攻击且需保护技能援护的队友
    class PartyMemberToProtect : public PartyMemberValue
    {
    public:
        PartyMemberToProtect(PlayerbotAI* ai, std::string name = "party member to protect") :
            PartyMemberValue(ai, name) {}

    protected:
        virtual ObjectGuid Calculate() override;
    };

    // 目标值计算器：查找被定身或诱捕（如自由祝福可解状态）的队友
    class PartyMemberToRemoveRoots : public PartyMemberValue
    {
    public:
        PartyMemberToRemoveRoots(PlayerbotAI* ai, std::string name = "party member to remove roots") :
            PartyMemberValue(ai, name) {}

    protected:
        virtual ObjectGuid Calculate() override;
    };
}
