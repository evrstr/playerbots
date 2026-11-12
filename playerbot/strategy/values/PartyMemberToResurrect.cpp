// 策略值实现：PartyMemberToResurrect（筛选待复活的死亡队友）

#include "playerbot/playerbot.h"
#include "PartyMemberToResurrect.h"

#include "playerbot/ServerFacade.h"
using namespace ai;

// 法术谓词：识别法术效果是否包含复活类效果
class IsTargetOfResurrectSpell : public SpellEntryPredicate
{
public:
    virtual bool Check(SpellEntry const* spell) override
    {
        for (int i=0; i<3; i++)
        {
            if (spell->Effect[i] == SPELL_EFFECT_RESURRECT ||
                spell->Effect[i] == SPELL_EFFECT_RESURRECT_NEW ||
                spell->Effect[i] == SPELL_EFFECT_SELF_RESURRECT)
                return true;
        }
        return false;
    }

};

// 队友筛选谓词：匹配在施法距离内处于尸体状态、未收到复活请求且无人正在对其读条复活的队友
class FindDeadPlayer : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    FindDeadPlayer(PlayerbotAI* ai, PartyMemberValue* value) : PlayerbotAIAware(ai), value(value) {}

    virtual bool Check(Unit* unit) override
    {
        Player* player = dynamic_cast<Player*>(unit);

        if (player)
        {
            if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST) && player->InBattleGround())
                return false;
        }

        return player && !player->isRessurectRequested() && sServerFacade.GetDistance2d(ai->GetBot(), player) <= ai->GetRange("spell") && sServerFacade.GetDeathState(player) == CORPSE && !value->IsTargetOfSpellCast(player, predicate);
    }

private:
    PartyMemberValue* value;
    IsTargetOfResurrectSpell predicate;
};

// 执行查找并返回需要复活的队友 GUID
ObjectGuid PartyMemberToResurrect::Calculate()
{
    FindDeadPlayer finder(ai, this);
    Unit* target = FindPartyMember(finder);
    return target ? target->GetObjectGuid() : ObjectGuid();
}
