// 策略值实现：CurrentCcTargetValue（查找已受指定控场效果影响的敌人）

#include "playerbot/playerbot.h"
#include "CurrentCcTargetValue.h"

using namespace ai;

// 目标查找策略：匹配身上已存在指定控场法术光环的攻击者
class FindCurrentCcTargetStrategy : public FindTargetStrategy
{
public:
    FindCurrentCcTargetStrategy(PlayerbotAI* ai, std::string spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
    }

public:
    virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager) override
    {
        if (ai->HasAura(spell, attacker))
            result = attacker;
    }

private:
    std::string spell;
};


// 搜索携带指定控场光环的敌人并返回其 GUID
ObjectGuid CurrentCcTargetValue::Calculate()
{
    FindCurrentCcTargetStrategy strategy(ai, qualifier);
    Unit* target = FindTarget(&strategy);
    return target ? target->GetObjectGuid() : ObjectGuid();
}
