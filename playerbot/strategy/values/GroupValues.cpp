// 策略值实现：GroupValues（队伍成员聚合及全队状态就绪检查）

#include "playerbot/playerbot.h"
#include "GroupValues.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/TravelMgr.h"

using namespace ai;

// 收集所在队伍全部成员 GUID，若未组队则仅返回自身
std::list<ObjectGuid> GroupMembersValue::Calculate()
{
    std::list<ObjectGuid> members;

    Group* group = bot->GetGroup();
    if (group)
    {
        for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
        {
            members.push_back(ref->getSource()->GetObjectGuid());
        }
    }
    else
        members.push_back(bot->GetObjectGuid());

    return members;
}


// 检查当前是否拥有活跃主控且处于 follow 或 wander 策略
bool IsFollowingPartyValue::Calculate()
{
    if (ai->GetGroupMaster() == bot)
        return true;

    if (ai->HasStrategy("follow", BotState::BOT_STATE_NON_COMBAT) ||
        ai->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT))
        return true;

    return false;
}

// 判断自身是否处于队长安全范围内（或未组队/自身即为队长）
bool IsNearLeaderValue::Calculate()
{
    Player* groupMaster = ai->GetGroupMaster();

    if (!groupMaster)
        return false;

    if (groupMaster == bot)
        return true;

    return sServerFacade.GetDistance2d(bot, ai->GetGroupMaster()) < sPlayerbotAIConfig.reactDistance;
}

// 遍历队伍成员并累加指定布尔值为 true 的成员数量
uint32 GroupBoolCountValue::Calculate()
{
    uint32 count = 0;

    for (ObjectGuid guid : AI_VALUE(std::list<ObjectGuid>, "group members"))
    {
        Player* player = sObjectMgr.GetPlayer(guid);

        if (!player)
            continue;

        if (!ai->IsSafe(player))
            continue;

        if (!player->GetPlayerbotAI())
            continue;

        if (PAI_VALUE2(bool, "and", getQualifier()))
            return count++;
    }

    return count;
};

// 遍历队伍成员，若任一成员不满足指定布尔值则返回 false
bool GroupBoolANDValue::Calculate()
{
    for (ObjectGuid guid : AI_VALUE(std::list<ObjectGuid>, "group members"))
    {
        Player* player = sObjectMgr.GetPlayer(guid);

        if (!player)
            continue;

        if (!ai->IsSafe(player))
            continue;

        if (!player->GetPlayerbotAI())
            continue;

        if (!PAI_VALUE2(bool,"and", getQualifier()))
            return false;
    }

    return true;
};

// 遍历队伍成员，若任一成员满足指定布尔值则返回 true
bool GroupBoolORValue::Calculate()
{
    for (ObjectGuid guid : AI_VALUE(std::list<ObjectGuid>, "group members"))
    {
        Player* player = sObjectMgr.GetPlayer(guid);

        if (!player)
            continue;

        if (!ai->IsSafe(player))
            continue;

        if (!player->GetPlayerbotAI())
            continue;

        if (PAI_VALUE2(bool, "and", getQualifier()))
            return true;
    }

    return false;
};

// 检查附近跟随状态的机器人队友是否存活且血量/法力高于低阈值
bool GroupReadyValue::Calculate()
{
    bool inDungeon = !WorldPosition(bot).isOverworld();

    for (ObjectGuid guid : AI_VALUE(std::list<ObjectGuid>, "group members"))
    {
        Player* member = sObjectMgr.GetPlayer(guid);

        if (!member)
            continue;

        if (inDungeon) // In dungeons all following members need to be alive before continuing. | 在地下城中，所有跟随状态的队友必须存活才能继续推进
        {
            PlayerbotAI* memberAi = member->GetPlayerbotAI();

            bool isFollowing = memberAi
                ? (memberAi->HasStrategy("follow", BotState::BOT_STATE_NON_COMBAT) ||
                    memberAi->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT))
                : true;

            if (!member->IsAlive() && isFollowing)
                return false;
        }
        //We only wait for members that are in range otherwise we might be waiting for bots stuck in dead loops forever. | 仅等待视距范围内的队友，避免因卡死在远处的机器人导致无限等待
        if (ai->GetGroupMaster() && sServerFacade.GetDistance2d(member, ai->GetGroupMaster()) > sPlayerbotAIConfig.sightDistance)
            continue;        

        bool hasAttackers = AI_VALUE_LAZY(bool, "has attackers") || AI_VALUE_LAZY(bool, "has enemy player targets") || ai->GetUnit(AI_VALUE_LAZY(ObjectGuid, "dps target"));

        //Wait for members to recover health/mana. | 等待队友恢复生命值与法力值
        if (hasAttackers && member->GetHealthPercent() < sPlayerbotAIConfig.almostFullHealth && !member->IsInCombat())
            return false;

        if (!member->GetPower(POWER_MANA))
            continue;

        float mana = (static_cast<float> (member->GetPower(POWER_MANA)) / member->GetMaxPower(POWER_MANA)) * 100;

        if (mana < sPlayerbotAIConfig.mediumMana && !member->IsInCombat())
            return false;
    }

    return true;
};