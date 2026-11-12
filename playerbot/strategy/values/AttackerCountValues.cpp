// 策略值实现：AttackerCountValues（攻击者计数、仇恨判定与战力平衡计算）

#include "playerbot/playerbot.h"
#include "AttackerCountValues.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

// 返回当前直接以机器人为攻击目标的单位数量
uint8 MyAttackerCountValue::Calculate()
{
    return bot->getAttackers().size();
}

// 检查目标的仇恨列表及当前第一目标是否为机器人本体
bool HasAggroValue::Calculate()
{
    Unit* target = GetTarget();

    // Player targets don't have aggro | 玩家目标没有仇恨机制
    if (target && !target->IsPlayer())
    {
        // Shade of Aran has a threat table but he casts randomly anyway, so don't worry about aggro | 埃兰之影虽有仇恨表但随机施法，无需关注仇恨
        if (target->GetEntry() == 16524)
            return false;
        HostileReference* ref = sServerFacade.GetHostileRefManager(bot).getFirst();
        if (ref)
        {
            while (ref)
            {
                ThreatManager* threatManager = ref->getSource();
                Unit* attacker = threatManager->getOwner();
                Unit* victim = attacker->GetVictim();

                if ((victim == bot) && (target == attacker))
                {
                    return true;
                }
                else
                {
                    ref = ref->next();
                }
            }

            ref = sServerFacade.GetThreatManager(target).getCurrentVictim();
            if (ref)
            {
                Unit* victim = ref->getTarget();
                return victim && (victim == bot);

                // 注释：以下为保留的历史调试代码
                /*
                // What is the purpose of this?
                if (victim)
                {
                    Player* pl = dynamic_cast<Player*>(victim);
                    if (pl && ai->IsTank(pl)) return true;
                }
                */
            }
        }
    }

    return false;
}

// 获取 attackers 列表并返回数量
uint8 AttackersCountValue::Calculate()
{
    return context->GetValue<std::list<ObjectGuid>>("attackers")->Get().size();
}

// 获取 possible attack targets 列表并返回数量
uint8 PossibleAttackTargetsCountValue::Calculate()
{
    return context->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get().size();
}

// 判断 attackers 列表是否非空
bool HasAttackersValue::Calculate()
{
    return !context->GetValue<std::list<ObjectGuid>>("attackers", 1)->Get().empty();
}

// 判断 possible attack targets 列表是否非空
bool HasPossibleAttackTargetsValue::Calculate()
{
    return !context->GetValue<std::list<ObjectGuid>>("possible attack targets", 1)->Get().empty();
}

// 汇总范围内友方等级与敌方加权等级（精英/首领/玩家按倍数折算），返回友方战力占比
uint8 BalancePercentValue::Calculate()
{
    float playerLevel = 0,
        attackerLevel = 0;

    playerLevel += bot->GetLevel();

    if (!bot->InBattleGround())
    {
        Group* group = bot->GetGroup();
        if (group)
        {
            Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
            for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
            {
                Player* player = sObjectMgr.GetPlayer(itr->guid);
                if (!player || !sServerFacade.IsAlive(player) || !player->IsInWorld() || player->GetMapId() != bot->GetMapId() || sServerFacade.GetDistance2d(bot, player) > 30.0f)
                    continue;

                playerLevel += player->GetLevel();
            }
        }
    }

    std::list<ObjectGuid> v = context->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get();
    for (std::list<ObjectGuid>::iterator i = v.begin(); i!=v.end(); i++)
    {
        Unit* unit = ai->GetUnit(*i);
        if (!unit || !sServerFacade.IsAlive(unit))
            continue;

        if (unit->IsPlayer())
        {
            attackerLevel += unit->GetLevel() * 3;
        }
        else
        {
            Creature* creature = ai->GetCreature((*i));
            if (!creature || !sServerFacade.IsAlive(creature))
                continue;

            uint32 level = creature->GetLevel();
            switch (creature->GetCreatureInfo()->Rank) 
            {
                case CREATURE_ELITE_RARE:
                {
                    level *= 2;
                    break;
                }

                case CREATURE_ELITE_ELITE:
                {
                    level *= 3;
                    break;
                }

                case CREATURE_ELITE_RAREELITE:
                {
                    level *= 3;
                    break;
                }

                case CREATURE_ELITE_WORLDBOSS:
                {
                    level *= 5;
                    break;
                }
            }

            attackerLevel += level;
        }
    }

    Unit* enemy = ai->GetUnit(AI_VALUE(ObjectGuid, "enemy player target"));
    if (enemy)
        attackerLevel += enemy->GetLevel() * 3;

    if (!attackerLevel)
        return 100;

    float percent = playerLevel * 100 / attackerLevel;
    return percent <= 200 ? (uint8)percent : 200;
}