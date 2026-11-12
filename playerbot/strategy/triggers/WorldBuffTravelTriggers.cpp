/// 世界增益自动旅行（World Buff Travel）触发器实现
#include "playerbot/playerbot.h"
#include "WorldBuffTravelTriggers.h"
#include "playerbot/ServerFacade.h"
#include "Server/DBCStores.h"

using namespace ai;

/// 检查指定 Entry 的 NPC 是否位于机器人交互距离内
static bool IsNpcNearby(Player* bot, uint32 npcEntry)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    if (!ai)
        return false;

    std::list<ObjectGuid> npcs = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("nearest npcs no los")->Get();
    for (auto& guid : npcs)
    {
        Unit* unit = ai->GetUnit(guid);
        if (!unit || !unit->IsCreature())
            continue;

        if (unit->GetEntry() == npcEntry &&
            bot->GetDistance(unit) <= INTERACTION_DISTANCE)
            return true;
    }
    return false;
}

/// 检查是否靠近厄运之槌北门
static bool IsNearDMNorthDoor(Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    if (!ai)
        return false;

    std::list<ObjectGuid> gos = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("nearest game objects no los")->Get();
    for (auto& guid : gos)
    {
        GameObject* go = ai->GetGameObject(guid);
        if (!go)
            continue;

        if (go->GetEntry() == GO_DM_NORTH_DOOR &&
            bot->GetDistance(go) <= INTERACTION_DISTANCE)
            return true;
    }
    return false;
}

/// 检查附近是否有名称包含目标关键字的传送门游戏对象
static bool IsPortalNearby(Player* bot, const char* destKeyword)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    if (!ai)
        return false;

    std::list<ObjectGuid> gos = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("nearest game objects no los")->Get();
    for (auto& guid : gos)
    {
        GameObject* go = ai->GetGameObject(guid);
        if (!go)
            continue;

        GameObjectInfo const* goInfo = go->GetGOInfo();
        if (!goInfo || goInfo->type != GAMEOBJECT_TYPE_SPELLCASTER)
            continue;

        uint32 spellId = goInfo->spellcaster.spellId;
        const SpellEntry* const pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
        if (!pSpellInfo)
            continue;

        if (pSpellInfo->Effect[0] != SPELL_EFFECT_TELEPORT_UNITS &&
            pSpellInfo->Effect[1] != SPELL_EFFECT_TELEPORT_UNITS &&
            pSpellInfo->Effect[2] != SPELL_EFFECT_TELEPORT_UNITS)
            continue;

        std::string name = goInfo->name;
        if (name.find(destKeyword) != std::string::npos)
            return true;
    }
    return false;
}

/// 检查是否靠近费伍德森林轻歌花游戏对象
static bool IsNearSongflower(Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    if (!ai)
        return false;

    std::list<ObjectGuid> gos = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("nearest game objects no los")->Get();
    for (auto& guid : gos)
    {
        GameObject* go = ai->GetGameObject(guid);
        if (!go || !IsSongflowerEntry(go->GetEntry()))
            continue;

        if (bot->GetDistance(go) <= INTERACTION_DISTANCE)
            return true;
    }
    return false;
}

/// 检查是否靠近菲拉斯篝火（部落步骤）
static bool IsNearBonfire(Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    if (!ai)
        return false;

    std::list<ObjectGuid> gos = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("nearest game objects no los")->Get();
    for (auto& guid : gos)
    {
        GameObject* go = ai->GetGameObject(guid);
        if (!go)
            continue;

        if (go->GetEntry() == GO_BONFIRE_FERALAS &&
            bot->GetDistance(go) <= INTERACTION_DISTANCE)
            return true;
    }
    return false;
}

/// 检查所有小队成员是否已抵达厄运传送门目标区域
static bool AreAllGroupMembersInPortalDestZone(Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    if (!ai)
        return false;

    uint32 destZone = GetDMPortalDestZone(bot);

    std::vector<Player*> members = ai->GetPlayersInGroup();
    for (Player* member : members)
    {
        if (!member)
            continue;

        uint32 zoneId = member->GetZoneId();
        if (zoneId != destZone)
            return false;
    }
    return true;
}

/// 遍历队伍中除机器人外的其他成员执行回调
static uint32 ForEachGroupMember(Player* bot, std::function<void(Player*)> callback)
{
    Group* group = bot->GetGroup();
    if (!group)
        return 0;

    uint32 count = 0;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->getSource();
        if (!member || member == bot)
            continue;

        ++count;
        callback(member);
    }
    return count;
}

/// 检查队伍中所有其他成员是否均已获得厄运之槌贡品 Buff
static bool DoAllGroupMembersHaveDMTBuffs(Player* bot)
{
    Group* group = bot->GetGroup();
    if (!group)
        return true;

    uint32 checkedCount = 0;
    uint32 passedCount = 0;

    ForEachGroupMember(bot, [&](Player* member)
        {
            ++checkedCount;
            if (HasAllDMTributeBuffs(member))
                ++passedCount;
        });

    uint32 totalMembers = 0;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        if (ref->getSource() && ref->getSource() != bot)
            ++totalMembers;
    }

    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->getSource();
        if (member == bot)
            continue;

        if (!member)
            return false;

        if (!HasAllDMTributeBuffs(member))
            return false;
    }

    return true;
}

/// 检查队伍中所有其他成员是否均已获得轻歌花风歌夜曲 Buff
static bool DoAllGroupMembersHaveSongflower(Player* bot)
{
    Group* group = bot->GetGroup();
    if (!group)
        return true;

    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->getSource();
        if (member == bot)
            continue;

        if (!member)
            return false;

        if (!member->HasAura(SPELL_SONGFLOWER))
            return false;
    }

    return true;
}

/// 判断机器人当前是否处于指定世界增益旅行步骤的目标区域或NPC旁
static bool IsInStepZone(Player* bot, WorldBuffTravelStep step)
{
    uint32 zoneId = 0;
    uint32 areaId = 0;
    bot->GetZoneAndAreaId(zoneId, areaId);

    bool horde = IsHordeFaction(bot);

    switch (step)
    {
    case WorldBuffTravelStep::STEP_STORMWIND:
        return zoneId == GetHomeZone(bot);
    case WorldBuffTravelStep::STEP_GRYPHON_MASTER:
        // Alliance only — Horde skips this step entirely | 仅限联盟，部落完全跳过此步骤
        return horde ? false : IsNpcNearby(bot, NPC_DUNGAR_LONGDRINK);
    case WorldBuffTravelStep::STEP_BOOTY_BAY:
        return areaId == AREA_BOOTY_BAY;
    case WorldBuffTravelStep::STEP_BRAGOK:
        return IsNpcNearby(bot, NPC_BRAGOK);
    case WorldBuffTravelStep::STEP_THYSSIANA:
        return horde ? IsNpcNearby(bot, NPC_SHYN) : IsNpcNearby(bot, NPC_THYSSIANA);
    case WorldBuffTravelStep::STEP_FEATHERMOON:
        // Alliance only — Horde skips this step entirely | 仅限联盟，部落完全跳过此步骤
        return horde ? false : (zoneId == ZONE_FERALAS);
    case WorldBuffTravelStep::STEP_FORGOTTEN_COAST:
        return horde ? IsNearBonfire(bot) : IsNpcNearby(bot, NPC_ZORBIN_FANDAZZLE);
    case WorldBuffTravelStep::STEP_DM_TRAVEL:
        return IsNearDMNorthDoor(bot);
    case WorldBuffTravelStep::STEP_FELWOOD:
        return horde ? IsNpcNearby(bot, NPC_BRAKKAR) : IsNpcNearby(bot, NPC_MISHELLENA);
    case WorldBuffTravelStep::STEP_SONGFLOWER:
    {
        if (bot->HasAura(SPELL_SONGFLOWER))
            return true;

        return IsNearSongflower(bot);
    }
    default:
        return false;
    }
}

/// 检测当前步骤的目标区域/交互点是否已到达
bool WorldBuffTravelZoneReachedTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    WorldBuffTravelStep s = static_cast<WorldBuffTravelStep>(step);

    // Horde skips Alliance-only steps | 部落跳过仅限联盟的步骤
    if (IsHordeFaction(bot) && IsAllianceOnlyStep(s))
        return false;

    if (s != WorldBuffTravelStep::STEP_STORMWIND &&
        s != WorldBuffTravelStep::STEP_GRYPHON_MASTER &&
        s != WorldBuffTravelStep::STEP_BOOTY_BAY &&
        s != WorldBuffTravelStep::STEP_BRAGOK &&
        s != WorldBuffTravelStep::STEP_THYSSIANA &&
        s != WorldBuffTravelStep::STEP_FEATHERMOON &&
        s != WorldBuffTravelStep::STEP_FORGOTTEN_COAST &&
        s != WorldBuffTravelStep::STEP_DM_TRAVEL &&
        s != WorldBuffTravelStep::STEP_FELWOOD &&
        s != WorldBuffTravelStep::STEP_SONGFLOWER)
        return false;

    return IsInStepZone(bot, s);
}

/// 检测当前步骤是否需要执行长途移动（非飞行途中且未到达目标点）
bool WorldBuffTravelNeedMoveTrigger::IsActive()
{
    if (bot->IsTaxiFlying())
        return false;

    uint8 step = AI_VALUE(uint8, "world buff travel step");
    WorldBuffTravelStep s = static_cast<WorldBuffTravelStep>(step);

    if (IsHordeFaction(bot) && IsAllianceOnlyStep(s))
        return false;

    if (s != WorldBuffTravelStep::STEP_STORMWIND &&
        s != WorldBuffTravelStep::STEP_GRYPHON_MASTER &&
        s != WorldBuffTravelStep::STEP_BOOTY_BAY &&
        s != WorldBuffTravelStep::STEP_BRAGOK &&
        s != WorldBuffTravelStep::STEP_THYSSIANA &&
        s != WorldBuffTravelStep::STEP_FEATHERMOON &&
        s != WorldBuffTravelStep::STEP_FORGOTTEN_COAST &&
        s != WorldBuffTravelStep::STEP_DM_TRAVEL &&
        s != WorldBuffTravelStep::STEP_DM_PORTAL &&
        s != WorldBuffTravelStep::STEP_FELWOOD &&
        s != WorldBuffTravelStep::STEP_SONGFLOWER &&
        s != WorldBuffTravelStep::STEP_PORTAL_HOME)
        return false;

    if (s == WorldBuffTravelStep::STEP_DM_PORTAL)
    {
        uint32 destZone = GetDMPortalDestZone(bot);
        if (bot->GetZoneId() == destZone)
            return false;

        return !IsInStepZone(bot, WorldBuffTravelStep::STEP_DM_TRAVEL);
    }

    if (s == WorldBuffTravelStep::STEP_PORTAL_HOME)
    {
        uint32 homeZone = GetHomeZone(bot);
        if (bot->GetZoneId() == homeZone)
            return false;

        if (bot->IsBeingTeleported())
            return false;

        return !IsNearSongflower(bot);
    }

    return !IsInStepZone(bot, s);
}

/// 检测是否已在厄运副本内拿满全部厄运 Buff
bool WorldBuffTravelDMBuffedTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    if (step != static_cast<uint8>(WorldBuffTravelStep::STEP_DM_INSIDE))
        return false;

    return HasAllDMTributeBuffs(bot);
}

/// 检测是否在离开厄运之槌后仍保有全部厄运 Buff
bool WorldBuffTravelDMExitedTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    if (step != static_cast<uint8>(WorldBuffTravelStep::STEP_DM_EXIT))
        return false;

    return HasAllDMTributeBuffs(bot);
}

/// 检测法师机器人是否应施放离开厄运区域的传送门
bool WorldBuffTravelDMPortalCastTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    if (step != static_cast<uint8>(WorldBuffTravelStep::STEP_DM_PORTAL))
        return false;

    if (bot->getClass() != CLASS_MAGE)
        return false;

    if (!HasAllDMTributeBuffs(bot))
        return false;

    if (!DoAllGroupMembersHaveDMTBuffs(bot))
        return false;

    if (!AreAllGroupMembersNearby(bot))
        return false;

    if (IsPortalNearby(bot, GetDMPortalKeyword(bot)))
        return false;

    return true;
}

/// 检测附近是否已出现目标传送门供队友点击使用
bool WorldBuffTravelDMPortalUseTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    if (step != static_cast<uint8>(WorldBuffTravelStep::STEP_DM_PORTAL))
        return false;

    if (!HasAllDMTributeBuffs(bot))
        return false;

    return IsPortalNearby(bot, GetDMPortalKeyword(bot));
}

/// 检测法师机器人是否应施放回主城的传送门
bool WorldBuffTravelPortalStepTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    if (step != static_cast<uint8>(WorldBuffTravelStep::STEP_PORTAL_HOME))
        return false;

    if (bot->getClass() != CLASS_MAGE)
        return false;

    if (!DoAllGroupMembersHaveSongflower(bot))
        return false;

    if (!AreAllGroupMembersNearby(bot))
        return false;

    if (IsPortalNearby(bot, GetHomePortalKeyword(bot)))
        return false;

    return true;
}

/// 检测附近是否已出现回城传送门供点击
bool WorldBuffTravelUsePortalTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    if (step != static_cast<uint8>(WorldBuffTravelStep::STEP_PORTAL_HOME))
        return false;

    return IsPortalNearby(bot, GetHomePortalKeyword(bot));
}

/// 检测世界增益旅行流程是否已全部完成
bool WorldBuffTravelDoneTrigger::IsActive()
{
    uint8 step = AI_VALUE(uint8, "world buff travel step");
    return step >= static_cast<uint8>(WorldBuffTravelStep::STEP_DONE);
}