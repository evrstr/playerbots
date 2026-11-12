// 策略值实现：PartyMemberWithoutItemValue（缺少补给品的队友筛选）

#include "playerbot/playerbot.h"
#include "PartyMemberWithoutItemValue.h"

#include "playerbot/ServerFacade.h"
using namespace ai;

// 队友筛选谓词：检查远距内的机器人队友背包里是否缺少指定物品
class PlayerWithoutItemPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutItemPredicate(PlayerbotAI* ai, std::string item) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), item(item) {}

public:
    virtual bool Check(Unit* unit) override
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        if (!sServerFacade.IsAlive(unit))
            return false;

        Player* member = dynamic_cast<Player*>(unit);
        if (!member)
            return false;

#ifdef MANGOS
        if (!(member->IsInSameGroupWith(ai->GetBot()) || member->IsInSameRaidWith(ai->GetBot())))
#endif
#ifdef CMANGOS
        if (!member->IsInGroup(ai->GetBot()))
#endif
            return false;

        PlayerbotAI *botAi = member->GetPlayerbotAI();
        if (!botAi)
            return false;

        return !botAi->GetAiObjectContext()->GetValue<uint32>("item count", item)->Get();
    }

private:
    std::string item;
};

// 调用派生谓词查找需要发放物品的队友 GUID
ObjectGuid PartyMemberWithoutItemValue::Calculate()
{
    FindPlayerPredicate *predicate = CreatePredicate();
    Unit *unit = FindPartyMember(*predicate);
    delete predicate;
    return unit ? unit->GetObjectGuid() : ObjectGuid();
}

// 创建默认的缺少指定物品筛选谓词
FindPlayerPredicate* PartyMemberWithoutItemValue::CreatePredicate()
{
    return new PlayerWithoutItemPredicate(ai, qualifier);
}

// 队友筛选谓词：检查队友是否缺少任何同等级段可用食物
class PlayerWithoutFoodPredicate : public PlayerWithoutItemPredicate
{
public:
    PlayerWithoutFoodPredicate(PlayerbotAI* ai) : PlayerWithoutItemPredicate(ai, "conjured food") {}

public:
    virtual bool Check(Unit* unit) override
    {
        if (!PlayerWithoutItemPredicate::Check(unit))
            return false;

        Player* member = dynamic_cast<Player*>(unit);
        if (!member)
            return false;

        return member->getClass() != CLASS_MAGE;
    }

};

// 队友筛选谓词：检查使用法力值的队友是否缺少同等级段可用饮水
class PlayerWithoutWaterPredicate : public PlayerWithoutItemPredicate
{
public:
    PlayerWithoutWaterPredicate(PlayerbotAI* ai) : PlayerWithoutItemPredicate(ai, "conjured water") {}

public:
    virtual bool Check(Unit* unit) override
    {
        if (!PlayerWithoutItemPredicate::Check(unit))
            return false;

        Player* member = dynamic_cast<Player*>(unit);
        if (!member)
            return false;

        uint8 cls = member->getClass();
        return cls == CLASS_DRUID ||
                cls == CLASS_HUNTER ||
                cls == CLASS_PALADIN ||
                cls == CLASS_PRIEST ||
                cls == CLASS_SHAMAN ||
                cls == CLASS_WARLOCK;
    }

};

// 创建缺少食物的队友筛选谓词
FindPlayerPredicate* PartyMemberWithoutFoodValue::CreatePredicate()
{
    return new PlayerWithoutFoodPredicate(ai);
}

// 创建缺少饮水的队友筛选谓词
FindPlayerPredicate* PartyMemberWithoutWaterValue::CreatePredicate()
{
    return new PlayerWithoutWaterPredicate(ai);
}