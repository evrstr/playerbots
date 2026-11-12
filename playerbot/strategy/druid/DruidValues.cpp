// 德鲁伊 - 数值计算实现文件 (DruidValues.cpp)：定义德鲁伊专用状态评估值

#include "playerbot/playerbot.h"
#include "DruidValues.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

// 条件谓词 (TankWithoutLifebloomPredicate)：用于筛选符合特定条件的目标单位
class TankWithoutLifebloomPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    explicit TankWithoutLifebloomPredicate(PlayerbotAI* ai) :
        FindPlayerPredicate(), PlayerbotAIAware(ai)  {}

    bool Check(Unit* unit) override
    {
        if (unit && unit->IsPlayer() && sServerFacade.IsAlive(unit) && ai->IsTank((Player*)unit))
        {
            return !ai->HasAura("lifebloom", unit, true, true, -1, false, 2000, 8);
        }

        return false;
    }

private:
    std::vector<std::string> auras;
};

// 计算评估值结果 (PartyTankWithoutLifebloomValue)
ObjectGuid PartyTankWithoutLifebloomValue::Calculate()
{
    TankWithoutLifebloomPredicate predicate(ai);
    Unit* tank = FindPartyMember(predicate);
    return tank ? tank->GetObjectGuid() : ObjectGuid();
}
