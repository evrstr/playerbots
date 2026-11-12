// 策略值实现：PartyMemberToDispel（查找带有可驱散光环的队伍成员）

#include "playerbot/playerbot.h"
#include "PartyMemberToDispel.h"

#include "playerbot/ServerFacade.h"
using namespace ai;

// 队友筛选谓词：排除小宠物/召唤物，检查存活、施法距离及可驱散光环类型
class PartyMemberToDispelPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberToDispelPredicate(PlayerbotAI* ai, uint32 dispelType) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), dispelType(dispelType) {}

public:
    virtual bool Check(Unit* unit) override
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        return sServerFacade.IsAlive(unit) && sServerFacade.GetDistance2d(ai->GetBot(), unit) <= ai->GetRange("spell") && ai->HasAuraToDispel(unit, dispelType);
    }

private:
    uint32 dispelType;
};

// 解析驱散类型掩码并查找符合条件的队友 GUID
ObjectGuid PartyMemberToDispel::Calculate()
{
    uint32 dispelType = atoi(qualifier.c_str());

    PartyMemberToDispelPredicate predicate(ai, dispelType);
    Unit* target = FindPartyMember(predicate);
    return target ? target->GetObjectGuid() : ObjectGuid();
}
