// 策略值实现：PartyMemberWithoutAuraValue（缺失光环/Buff 队友筛选）

#include "playerbot/playerbot.h"
#include "PartyMemberWithoutAuraValue.h"

#include "playerbot/ServerFacade.h"
using namespace ai;

extern std::vector<std::string> split(const std::string &s, char delim);

// 队友筛选谓词：检查目标是否存活、在视距内且未同时拥有候选光环列表中的任意光环
class PlayerWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutAuraPredicate(PlayerbotAI* ai, std::string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), auras(split(aura, ',')) {}

public:
    virtual bool Check(Unit* unit) override
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        if (!sServerFacade.IsAlive(unit)) return false;

        for (std::vector<std::string>::iterator i = auras.begin(); i != auras.end(); ++i)
        {
#ifdef MANGOSBOT_ZERO
            // Ignore mana buff spells for non mana users | 对非蓝条职业（如战士/盗贼）忽略法力类增益光环
            if (*i == "arcane intellect" || *i == "arcane brilliance" || *i == "divine spirit" || *i == "prayer of spirit")
            {
                if (unit->GetPowerType() != POWER_MANA)
                {
                    return false;
                }
            }
#endif

            if (ai->HasAura(*i, unit))
                return false;
        }

        return true;
    }

private:
    std::vector<std::string> auras;
};

// 查找包含队外友军在内的缺少指定光环单位 GUID
ObjectGuid FriendlyUnitWithoutAuraValue::Calculate()
{
    bool ignoreTank = false;
    std::string auras = qualifier;
    
    size_t paramPos = qualifier.find("-");
    if (paramPos != std::string::npos)
    {
        auras = qualifier.substr(0, paramPos);
        ignoreTank = std::stoi(qualifier.substr(paramPos + 1, paramPos + 2));
    }

    PlayerWithoutAuraPredicate predicate(ai, auras);
    Unit* target = FindPartyMember(predicate, false, ignoreTank);
    return target ? target->GetObjectGuid() : ObjectGuid();
}

// 查找队伍中缺少指定光环的队友 GUID（支持 "-1" 参数忽略坦克）
ObjectGuid PartyMemberWithoutAuraValue::Calculate()
{
    bool ignoreTank = false;
    std::string auras = qualifier;

    size_t paramPos = qualifier.find("-");
    if (paramPos != std::string::npos)
    {
        auras = qualifier.substr(0, paramPos);
        ignoreTank = std::stoi(qualifier.substr(paramPos + 1, paramPos + 2));
    }

    PlayerWithoutAuraPredicate predicate(ai, auras);
    Unit* target = FindPartyMember(predicate, true, ignoreTank);
    return target ? target->GetObjectGuid() : ObjectGuid();
}

// 队友筛选谓词：检查目标身上是否缺少由当前机器人施放的指定光环
class PlayerWithoutMyAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutMyAuraPredicate(PlayerbotAI* ai, std::string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), auras(split(aura, ',')) {}

public:
    virtual bool Check(Unit* unit) override
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        if (!sServerFacade.IsAlive(unit)) return false;
        if (sServerFacade.GetDistance2d(unit, ai->GetBot()) > 30.0f) return false;

        for (std::vector<std::string>::iterator i = auras.begin(); i != auras.end(); ++i)
        {
            if (ai->HasMyAura(*i, unit))
                return false;
        }

        return true;
    }

private:
    std::vector<std::string> auras;
};

// 查找队伍中缺少机器人自身施加的指定光环的队友 GUID
ObjectGuid PartyMemberWithoutMyAuraValue::Calculate()
{
    bool ignoreTank = false;
    std::string auras = qualifier;

    size_t paramPos = qualifier.find("-");
    if (paramPos != std::string::npos)
    {
        auras = qualifier.substr(0, paramPos);
        ignoreTank = std::stoi(qualifier.substr(paramPos + 1, paramPos + 2));
    }

    PlayerWithoutMyAuraPredicate predicate(ai, auras);
    Unit* target = FindPartyMember(predicate, false, ignoreTank);
    return target ? target->GetObjectGuid() : ObjectGuid();
}

// 队友筛选谓词：仅匹配队伍坦克并检查是否缺少指定光环
class TankWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    TankWithoutAuraPredicate(PlayerbotAI* ai, std::string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), auras(split(aura, ',')) {}

public:
    virtual bool Check(Unit* unit) override
    {
        if (unit && unit->IsPlayer() && sServerFacade.IsAlive(unit))
        {
            if (ai->IsTank((Player*)unit))
            {
                bool missingAura = false;
                for (std::vector<std::string>::iterator i = auras.begin(); i != auras.end(); ++i)
                {
                    if (!ai->HasAura(*i, unit))
                    {
                        missingAura = true;
                        break;
                    }
                }

                return missingAura;
            }
        }

        return false;
    }

private:
    std::vector<std::string> auras;
};

// 查找缺少指定光环的队伍坦克 GUID
ObjectGuid PartyTankWithoutAuraValue::Calculate()
{
    TankWithoutAuraPredicate predicate(ai, qualifier);
    Unit* target = FindPartyMember(predicate);
    return target ? target->GetObjectGuid() : ObjectGuid();
}
