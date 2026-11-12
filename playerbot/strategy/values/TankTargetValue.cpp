// 策略值实现：TankTargetValue（坦克低仇恨/未拉稳目标筛选）

#include "playerbot/playerbot.h"
#include "TankTargetValue.h"
#include "PossibleAttackTargetsValue.h"
#include "RtiValue.h"

using namespace ai;

// 坦克目标查找策略：筛选非控场且在攻击列表中的目标，优先拉取当前最高仇恨过低或尚未盯住坦克的敌人
class FindTargetForTankStrategy : public FindNonCcTargetStrategy
{
public:
    FindTargetForTankStrategy(PlayerbotAI* ai) : FindNonCcTargetStrategy(ai)
    {
        minThreat = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager) override
    {
        Player* bot = ai->GetBot();
        AiObjectContext* context = ai->GetAiObjectContext();

        if (IsCcTarget(creature)) return;

        if (!PossibleAttackTargetsValue::IsValid(creature, bot))
        {
            std::list<ObjectGuid> attackers = AI_VALUE(std::list<ObjectGuid>, "possible attack targets");
            if (std::find(attackers.begin(), attackers.end(), creature->GetObjectGuid()) == attackers.end())
                return;
        }

        float threat = threatManager->getThreat(bot);
        if (!result || (minThreat - threat) > 0.1f)
        {
            minThreat = threat;
            result = creature;
        }
    }

protected:
    float minThreat;
};


// 依次检查战斗指令、RTI 标记目标，否则通过 FindTargetForTankStrategy 选出最需要建立仇恨的怪
ObjectGuid TankTargetValue::Calculate()
{
    ObjectGuid ordered = CombatOrderTargetValue::FindTarget(ai, true);
    if (ordered) return ordered;

    ObjectGuid rti = RtiTargetValue::Calculate();
    if (rti) return rti;

    FindTargetForTankStrategy strategy(ai);
    Unit* target = FindTarget(&strategy);
    return target ? target->GetObjectGuid() : ObjectGuid();
}
