// 策略值实现：AoeValues（AOE 密集点查找与区域减益判断）

#include "playerbot/playerbot.h"
#include "AoeValues.h"

#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
using namespace ai;

// 在指定距离内按两倍 AOE 半径聚类，返回敌人数最多的目标群组
std::list<ObjectGuid> AoeCountValue::FindMaxDensity(Player* bot, float range)
{
    int maxCount = 0;
    ObjectGuid maxGroup;
    std::map<ObjectGuid, std::list<ObjectGuid> > groups;
    if (bot)
    {
        std::list<ObjectGuid> units = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<std::list<ObjectGuid>>("possible attack targets");
        
        for (std::list<ObjectGuid>::iterator i = units.begin(); i != units.end(); ++i)
        {
            Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
            if (unit)
            {
                float distanceToPlayer = sServerFacade.GetDistance2d(unit, bot);
                if (sServerFacade.IsDistanceLessOrEqualThan(distanceToPlayer, range))
                {
                    for (std::list<ObjectGuid>::iterator j = units.begin(); j != units.end(); ++j)
                    {
                        Unit* other = bot->GetPlayerbotAI()->GetUnit(*j);
                        if (other)
                        {
                            float d = sServerFacade.GetDistance2d(unit, other);
                            if (sServerFacade.IsDistanceLessOrEqualThan(d, sPlayerbotAIConfig.aoeRadius * 2.0f))
                            {
                                groups[*i].push_back(*j);
                            }
                        }
                    }

                    if (maxCount < groups[*i].size())
                    {
                        maxCount = groups[*i].size();
                        maxGroup = *i;
                    }
                }
            }
        }
    }

    if (!maxCount)
    {
        return std::list<ObjectGuid>();
    }

    return groups[maxGroup];
}

// 根据最大密集敌群的包围盒中心计算 AOE 释放坐标
WorldLocation AoePositionValue::Calculate()
{
    std::list<ObjectGuid> group = AoeCountValue::FindMaxDensity(bot);
    if (group.empty())
        return WorldLocation();

    // Note: don't know where these values come from or even used. | 注：暂不确定这些坐标数值的来源及具体用途
    float x1, y1, x2, y2;
    for (std::list<ObjectGuid>::iterator i = group.begin(); i != group.end(); ++i)
    {
        Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
        if (!unit)
            continue;

        if (i == group.begin() || x1 > unit->GetPositionX())
            x1 = unit->GetPositionX();
        if (i == group.begin() || x2 < unit->GetPositionX())
            x2 = unit->GetPositionX();
        if (i == group.begin() || y1 > unit->GetPositionY())
            y1 = unit->GetPositionY();
        if (i == group.begin() || y2 < unit->GetPositionY())
            y2 = unit->GetPositionY();
    }
    float x = (x1 + x2) / 2;
    float y = (y1 + y2) / 2;
    float z = bot->GetPositionZ() + CONTACT_DISTANCE;;
    bot->UpdateAllowedPositionZ(x, y, z);
    return WorldLocation(bot->GetMapId(), x, y, z, 0);
}

// 返回当前最大密集敌群的目标数量
uint8 AoeCountValue::Calculate()
{
    return FindMaxDensity(bot).size();
}

// 遍历附近忽略视线的动态法术对象，检查目标是否处于非正向区域法术影响中
bool HasAreaDebuffValue::Calculate()
{
    if (!GetTarget())
        return false;

    Unit* checkTarget = GetTarget();
    if (!checkTarget)
        return false;

    std::list<ObjectGuid> nearestDynObjects = *context->GetValue<std::list<ObjectGuid> >("nearest dynamic objects no los");
    if (nearestDynObjects.empty())
        return false;

    for (std::list<ObjectGuid>::iterator i = nearestDynObjects.begin(); i != nearestDynObjects.end(); ++i)
    {
        DynamicObject* go = checkTarget->GetMap()->GetDynamicObject(*i);
        if (!go)
            continue;

        SpellEntry const* spellProto = sSpellTemplate.LookupEntry<SpellEntry>(go->GetSpellId());
        if (!spellProto)
            continue;
        
        // I will not move when flame wreath is cast or the raid blows up | 遇到火圈（烈焰花环 29946）时不躲避，否则会导致灭团
        if (spellProto->Id == 29946)
            continue;

        if (IsPositiveEffect(spellProto, go->GetEffIndex()))
            continue;

        if (go->IsAffecting(checkTarget))
            return true;
    }

    return false;
}
