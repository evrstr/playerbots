// 策略值实现：PartyMemberToSoulstone（灵魂石目标筛选与多术士错峰防撞）
#include "playerbot/playerbot.h"
#include "PartyMemberToSoulstone.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

// 法术谓词：判断法术是否为灵魂石复活效果
class IsTargetOfSoulstoneSpell : public SpellEntryPredicate
{
public:
    virtual bool Check(SpellEntry const* spell) override
    {
        for (int i = 0; i < 3; i++)
        {
            if(spell->Effect[i] == SPELL_EFFECT_SELF_RESURRECT)
                return true;
        }
        return false;
    }
};

// Finds a healer or tank in range without an active soulstone buff | 在施法范围内查找没有灵魂石光环
// and not already being targeted by another warlock's cast | 且未被其他术士同时施法锁定的治疗或坦克
// 队友筛选谓词：筛选射程内无灵魂石且未被其他术士施法锁定的治疗或坦克
class FindSoulstoneTarget : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    FindSoulstoneTarget(PlayerbotAI* ai, PartyMemberValue* value) : PlayerbotAIAware(ai), value(value) {}

    virtual bool Check(Unit* unit) override
    {
        Player* player = dynamic_cast<Player*>(unit);
        if (!player || !player->IsAlive() || player->InBattleGround())
            return false;

        if (sServerFacade.GetDistance2d(ai->GetBot(), player) > ai->GetRange("spell"))
            return false;

        // Skip DPS — only healers and tanks are worth stoning | 跳过输出职业——只给治疗和坦克绑定灵魂石
        if (!ai->IsHeal(player) && !ai->IsTank(player))
            return false;

        // Skip players who already have a soulstone buff | 跳过已经拥有灵魂石或自身已施放冷却的玩家
        if (ai->HasAura("soulstone resurrection", player))
            return false;

        // Skip players another warlock is already mid-cast on | 跳过正被其他术士施放灵魂石的目标
        return !value->IsTargetOfSpellCast(player, predicate);
    }

private:
    PartyMemberValue* value;
    IsTargetOfSoulstoneSpell predicate;
};

static bool HasOtherWarlockInGroup(Player* bot, Group* group)
{
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->getSource();
        if (!member || member == bot)
            continue;
        if (member->getClass() == CLASS_WARLOCK)
            return true;
    }
    return false;
}

static bool BotIsAlreadySoulstoned(Player* bot)
{
    Unit::SpellAuraHolderMap const& auras = bot->GetSpellAuraHolderMap();
    for (auto const& pair : auras)
    {
        SpellEntry const* spellInfo = pair.second->GetSpellProto();
        for (int i = 0; i < 3; i++)
        {
            if (spellInfo->Effect[i] == SPELL_EFFECT_SELF_RESURRECT)
                return true;
        }
    }
    return false;
}

// 优先遵从主控指定复活名单，否则查找治疗/坦克并使用 D20 随机退避避免多术士重复上石
ObjectGuid PartyMemberToSoulstone::Calculate()
{
    // If a master player has manually assigned revive targets, defer to that | 若主控玩家已手动指定复活目标，则优先服从该列表
    if (!AI_VALUE(std::list<ObjectGuid>, "revive targets").empty())
        return ObjectGuid();

    Group* group = bot->GetGroup();

    if (group)
    {
        // FindPartyMember automatically prioritizes healers over tanks | FindPartyMember 会自动优先于坦克返回治疗职业
        FindSoulstoneTarget finder(ai, this);
        Unit* target = FindPartyMember(finder);

        if (!target)
            return ObjectGuid();

        // Multiple warlocks in group may target same player. Each roll D20 to stagger casts. | 队伍存在多名术士时，通过掷骰退避错开施法以免冲突
        if (HasOtherWarlockInGroup(bot, group))
        {
            if (urand(1, 20) != 20)
                return ObjectGuid();
        }

        return target ? target->GetObjectGuid() : ObjectGuid();
    }
    else
    {
        if (BotIsAlreadySoulstoned(bot))
            return ObjectGuid();

        return ai->GetBot() ? ai->GetBot()->GetObjectGuid() : ObjectGuid();
    }
}
