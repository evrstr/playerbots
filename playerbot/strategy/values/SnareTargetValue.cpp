// 策略值实现：SnareTargetValue（减速目标筛选逻辑）

#include "playerbot/playerbot.h"
#include "SnareTargetValue.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "MotionGenerators/TargetedMovementGenerator.h"

using namespace ai;

// 遍历可能攻击目标，筛选出非当前目标或正试图脱离/逃跑且尚未受到减速法术影响的目标
ObjectGuid SnareTargetValue::Calculate()
{
    std::string spell = qualifier;

    Unit* enemy = ai->GetUnit(AI_VALUE(ObjectGuid, "enemy player target"));
    if (enemy)
    {
        Player* plr = dynamic_cast<Player*>(enemy);
        if (plr && !(plr->HasAuraType(SPELL_AURA_MOD_ROOT) || plr->HasAuraType(SPELL_AURA_MOD_STUN)) && (!plr->IsStopped() || plr->IsNonMeleeSpellCasted(false) || (plr->GetVictim() && plr->GetVictim()->GetObjectGuid() == bot->GetObjectGuid())))
            return enemy ? enemy->GetObjectGuid() : ObjectGuid();
    }

    std::list<ObjectGuid> attackers = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get();
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    Unit* target = ai->GetUnit(ai->GetAiObjectContext()->GetValue<ObjectGuid>("current target")->Get());
    for (std::list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = ai->GetUnit(*i);
        if (!unit)
            continue;

        if (sServerFacade.GetDistance2d(bot, unit) > ai->GetRange("spell"))
            continue;

        // case real player or bot not moving | 处理真人玩家或未移动机器人的追击目标检查
        if (unit->IsPlayer() && unit->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
        {
            if (Unit* victim = unit->GetVictim())
            {
                // check if need to snare | 检查是否需要对目标施加减速
                bool shouldSnare = true;

                // do not slow down if bot is melee and mob/bot attack each other | 若己方为近战且双方正在对砍，则无需浪费技能减速
                if (victim == bot || victim->IsPlayer())
                    shouldSnare = true;

                if (unit->HasAuraType(SPELL_AURA_MOD_ROOT) || unit->HasAuraType(SPELL_AURA_MOD_STUN))
                    shouldSnare = false;

                if (victim && shouldSnare)
                    return unit ? unit->GetObjectGuid() : ObjectGuid();
            }
        }

        Unit* chaseTarget;
        switch (unit->GetMotionMaster()->GetCurrentMovementGeneratorType())
        {
        case FLEEING_MOTION_TYPE:
            return unit ? unit->GetObjectGuid() : ObjectGuid();
        case CHASE_MOTION_TYPE:
            chaseTarget = sServerFacade.GetChaseTarget(unit);
            if (!chaseTarget) continue;
            Player* chaseTargetPlayer = sObjectMgr.GetPlayer(chaseTarget->GetObjectGuid());
            
            // check if need to snare | 检查是否需要对怪物施加减速（正在逃跑或与目标拉扯）
            bool shouldSnare = true;

            // do not slow down if bot is melee and mob/bot attack each other | 若己方为近战且双方正面对战，则无需施加减速
            if (chaseTargetPlayer && !ai->IsRanged(bot) && chaseTargetPlayer == bot)
                shouldSnare = false;

            if (!sServerFacade.isMoving(unit))
                shouldSnare = false;

            if (unit->HasAuraType(SPELL_AURA_MOD_ROOT) || unit->HasAuraType(SPELL_AURA_MOD_STUN))
                shouldSnare = false;

            if (chaseTargetPlayer && shouldSnare && !ai->IsTank(chaseTargetPlayer))
                return unit ? unit->GetObjectGuid() : ObjectGuid();
        }
    }

    return ObjectGuid();
}
