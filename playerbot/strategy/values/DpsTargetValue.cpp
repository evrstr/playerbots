// 策略值实现：DpsTargetValue（单体集火与 AOE 输出目标选择）

#include "playerbot/playerbot.h"
#include "DpsTargetValue.h"
#include "LeastHpTargetValue.h"
#include "RtiValue.h"

using namespace ai;


// 依次检查战斗指令目标、RTI 标记目标，否则选择血量最少的敌人
ObjectGuid DpsTargetValue::Calculate()
{
    ObjectGuid ordered = CombatOrderTargetValue::FindTarget(ai, false);
    if (ordered) return ordered;

    ObjectGuid rti = RtiTargetValue::Calculate();
    if (rti) return rti;

    FindLeastHpTargetStrategy strategy(ai);
    Unit* target = TargetValue::FindTarget(&strategy);
    return target ? target->GetObjectGuid() : ObjectGuid();
}

// 目标查找策略：筛选当前生命值最高的敌对单位（适合作为 AOE 锚点）
class FindMaxHpTargetStrategy : public FindTargetStrategy
{
public:
    FindMaxHpTargetStrategy(PlayerbotAI* ai) : FindTargetStrategy(ai)
    {
        maxHealth = 0;
    }

public:
    virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager) override
    {
        if (!result || result->GetHealth() < attacker->GetHealth())
            result = attacker;
    }

protected:
    float maxHealth;
};

// 优先选择 RTI 标记目标，否则选择血量最多的敌人作为 AOE 目标
ObjectGuid DpsAoeTargetValue::Calculate()
{
    ObjectGuid rti = RtiTargetValue::Calculate();
    if (rti) return rti;

    FindMaxHpTargetStrategy strategy(ai);
    Unit* target = TargetValue::FindTarget(&strategy);
    return target ? target->GetObjectGuid() : ObjectGuid();
}
