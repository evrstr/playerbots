// 策略值实现：AttackerWithoutAuraTargetValue（查找未携带指定光环的攻击者）

#include "playerbot/playerbot.h"
#include "AttackerWithoutAuraTargetValue.h"
#include "playerbot/PlayerbotAIConfig.h"

using namespace ai;

// 遍历可能攻击目标，排除当前目标和超距目标，返回第一个缺少指定光环的单位 GUID
ObjectGuid AttackerWithoutAuraTargetValue::Calculate()
{
    std::list<ObjectGuid> attackers = ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("possible attack targets")->Get();
    PlayerbotAI* ai = bot->GetPlayerbotAI();
    Unit* target = ai->GetUnit(ai->GetAiObjectContext()->GetValue<ObjectGuid>("current target")->Get());
    for (std::list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = ai->GetUnit(*i);
        if (!unit || unit == target)
            continue;

        if (bot->GetDistance(unit) > ai->GetRange("spell"))
            continue;

        if (!ai->HasAura(qualifier, unit))
            return unit->GetObjectGuid();
    }

    return ObjectGuid();
}
