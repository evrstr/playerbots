// 策略值实现：ThreatValues（仇恨值读取与 OT 风险分级计算）

#include "playerbot/playerbot.h"
#include "ThreatValues.h"

#include "playerbot/ServerFacade.h"
#include "Combat/ThreatManager.h"

using namespace ai;

// 计算机器人对目标的当前仇恨值（切换目标时重置变化日志）
float MyThreatValue::Calculate()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));
    
    if (target->GetObjectGuid() != lastTarget) //Reset history if we switched target. | 切换目标时重置仇恨变化历史记录
        LogCalculatedValue::Reset();

    lastTarget = target->GetObjectGuid();
      
    return ThreatValue::GetThreat(bot, target);
}

// 查询队伍成员中对目标拥有最高仇恨的值作为参考坦克仇恨
float TankThreatValue::Calculate()
{
    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));

    return ThreatValue::GetTankThreat(ai, target);
}

// 当限定符为 "aoe" 时返回所有可攻击目标中的最高威胁级别，否则计算指定目标的威胁级别
uint8 ThreatValue::Calculate()
{
    if (qualifier == "aoe")
    {
        uint8 maxThreat = 0;
        std::list<ObjectGuid> attackers = context->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get();
        for (std::list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); i++)
        {
            Unit* unit = ai->GetUnit(*i);
            if (!unit || !sServerFacade.IsAlive(unit))
                continue;

            uint8 threat = Calculate(unit);
            if (!maxThreat || threat > maxThreat)
                maxThreat = threat;
        }

        return maxThreat;
    }

    Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));

    if (target && target->IsFriend(bot))
        target = target->GetTarget();

    return Calculate(target);
}

// 通过 ThreatManager 读取指定玩家对目标的实际仇恨数值
float ThreatValue::GetThreat(Player* player, Unit* target)
{
    if (!target || target->GetMapId() != player->GetMapId())
        return 0;

    if (dynamic_cast<Player*>(target) && (dynamic_cast<Player*>(target))->IsBeingTeleported())
        return 0;

    if (target->IsFriend(player))
        target = target->GetTarget();

    if (target->GetObjectGuid().IsPlayer())
        return 0;

    float botThreat = sServerFacade.GetThreatManager(target).getThreat(player);

    return botThreat;
}

// 从目标仇恨列表中提取队内主坦或最高仇恨队友的仇恨值
float ThreatValue::GetTankThreat(PlayerbotAI* ai, Unit* target)
{
    if (!target)
        return 0;

    if (target->IsFriend(ai->GetBot()))
        target = target->GetTarget();

    if (target->GetObjectGuid().IsPlayer())
        return 0;

    Group* group = ai->GetBot()->GetGroup();
    if (!group)
        return 0;

    float maxThreat = -1.0f;

    for (GroupReference* gref = group->GetFirstMember(); gref; gref = gref->next())
    {
        Player* player = gref->getSource();
        if (!player || !sServerFacade.IsAlive(player) || !ai->IsSafe(player) || player == ai->GetBot())
            continue;

        if (ai->IsTank(player))
        {
            float threat = sServerFacade.GetThreatManager(target).getThreat(player);
            if (maxThreat < threat)
                maxThreat = threat;
        }
    }

    return maxThreat;
}

// 根据机器人与坦克的仇恨比例及当前最高目标归属计算 0-100 威胁级别
uint8 ThreatValue::Calculate(Unit* target)
{
    if (!target)
        return 0;

    if (target->IsFriend(bot))
        target = target->GetTarget();

    if (!target)
        return 0;

    if (target->GetObjectGuid().IsPlayer())
        return 0;

    Group* group = bot->GetGroup();
    if (!group)
        return 0;

    float botThreat, maxThreat;
    if (qualifier == "aoe")
    {
        botThreat = GetThreat(bot, target);
        maxThreat = GetTankThreat(ai, target);
    }
    else
    {
        botThreat = AI_VALUE2(float, "my threat", qualifier);
        maxThreat = AI_VALUE2(float, "tank threat", qualifier);
    }

    if (maxThreat < 0)
        return 0;

    // calculate normal threat for fleeing targets | 对逃跑中的怪物按常规比例计算威胁值
    bool fleeing = target->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLEEING_MOTION_TYPE ||
        target->GetMotionMaster()->GetCurrentMovementGeneratorType() == TIMED_FLEEING_MOTION_TYPE;

    // return high threat if tank has no threat | 若坦克毫无仇恨或目标尚未锁定坦克则返回高威胁提示（100）
    if (target->IsInCombat() && maxThreat == 0 && !fleeing)
        return 100;

    // return low threat if mob if fleeing | 怪物正在逃跑时返回低威胁等级（0）
    if (maxThreat > 0 && fleeing)
        return 0;

    return botThreat * 100 / maxThreat;
}