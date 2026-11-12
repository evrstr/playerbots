// 策略值头文件：LeastHpTargetValue（生命值最低的敌人目标选择器）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"

namespace ai
{
    // 目标查找策略：筛选非玩家且未被控场的敌人中当前生命值最低的目标
    class FindLeastHpTargetStrategy : public FindNonCcTargetStrategy
    {
    public:
        FindLeastHpTargetStrategy(PlayerbotAI* ai) : FindNonCcTargetStrategy(ai)
        {
            minHealth = 0;
        }
    public:
        virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager) override
        {
            // do not use this logic for pvp | PvP 场景不使用此最低血量筛选逻辑
            if (attacker->IsPlayer())
                return;

            if (IsCcTarget(attacker))
                return;

            if (!result || result->GetHealth() > attacker->GetHealth())
                result = attacker;
        }
    protected:
        float minHealth;
    };

    // 目标值计算器：返回当前战场上生命值最少的优先击杀目标 GUID
    class LeastHpTargetValue : public TargetValue
    {
    public:
        LeastHpTargetValue(PlayerbotAI* ai, std::string name = "least hp target") : TargetValue(ai, name) {}

    public:
        ObjectGuid Calculate() override;
    };
}
