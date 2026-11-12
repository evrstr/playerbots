// 策略值实现：Arrow（箭头阵型构建与成员站位计算）
#include "playerbot/playerbot.h"
#include "Formations.h"
#include "Arrow.h"

using namespace ai;

// 计算并返回当前机器人在箭头阵型中的目标世界坐标
WorldLocation ArrowFormation::GetLocationInternal()
{
    if (!bot->GetGroup()) return Formation::NullLocation;

    Build();

    int tankLines = 1 + tanks.Size() / 6;
    int meleeLines = 1 + melee.Size() / 6;
    int rangedLines = 1 + ranged.Size() / 6;
    int healerLines = 1 + healers.Size() / 6;
    float offset = 0;
    float range = ai->GetRange("follow");

    Unit* followTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "follow target"));
    if (!ai->IsSafe(followTarget))
        return Formation::NullLocation;

    float orientation = followTarget->GetOrientation();
    MultiLineUnitPlacer placer(orientation, range);

    tanks.PlaceUnits(&placer);
    tanks.Move(-cos(orientation) * offset, -sin(orientation) * offset);

    offset += tankLines * range;
    melee.PlaceUnits(&placer);
    melee.Move(-cos(orientation) * offset, -sin(orientation) * offset);

    offset += meleeLines * range;
    ranged.PlaceUnits(&placer);
    ranged.Move(-cos(orientation) * offset, -sin(orientation) * offset);

    offset += rangedLines * range;
    healers.PlaceUnits(&placer);
    healers.Move(-cos(orientation) * offset, -sin(orientation) * offset);

    if (!masterUnit || !botUnit)
        return Formation::NullLocation;

    float x = followTarget->GetPositionX() - masterUnit->GetX() + botUnit->GetX();
    float y = followTarget->GetPositionY() - masterUnit->GetY() + botUnit->GetY();
    float z = followTarget->GetPositionZ();

    float ox, oy, oz;
    followTarget->GetPosition(ox, oy, oz);
    if (std::isfinite(ox) && std::isfinite(oy) && std::isfinite(oz) && std::isfinite(x) && std::isfinite(y) && std::isfinite(z))
    {
#ifdef MANGOSBOT_TWO
        followTarget->GetMap()->GetHitPosition(ox, oy, oz + bot->GetCollisionHeight(), x, y, z, bot->GetPhaseMask(), -0.5f);
#else
        followTarget->GetMap()->GetHitPosition(ox, oy, oz + bot->GetCollisionHeight(), x, y, z, -0.5f);
#endif
    }
    else
        WorldPosition::logNonFinite("Arrow::GetHitPosition", WorldPosition(followTarget->GetMapId(), ox, oy, oz), nullptr);

    if (!bot->IsFlying() && !bot->IsFreeFlying() && !bot->IsSwimming())
    {
        z += CONTACT_DISTANCE;
        bot->UpdateAllowedPositionZ(x, y, z);
    }

    return WorldLocation(followTarget->GetMapId(), x, y, z);
}

// 初始化阵型，将所有队员和主控玩家分别填充到对应职责槽位
void ArrowFormation::Build()
{
    if (built)
        return;

    FillSlotsExceptMaster();
    AddMasterToSlot();

    built = true;
}

// 根据队员职责（坦克/治疗/远程/近战）查找对应的阵型槽位
FormationSlot* ArrowFormation::FindSlot(Player* member)
{
    if (ai->IsTank(member))
        return &tanks;
    else if (ai->IsHeal(member))
        return &healers;
    else if (ai->IsRanged(member))
        return &ranged;
    else
        return &melee;
}

// 将除主控外的其余队伍成员加入各自职责槽位
void ArrowFormation::FillSlotsExceptMaster()
{
    Unit* followTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "follow target"));
    Group* group = bot->GetGroup();
    GroupReference *gref = group->GetFirstMember();
    uint32 index = 0;
    while (gref)
    {
        Player* member = gref->getSource();
        if (ai->IsSafe(member))
        {
            if (member == bot)
                FindSlot(member)->AddLast(botUnit = new FormationUnit(index, false));
            else if (member != followTarget)
                FindSlot(member)->AddLast(new FormationUnit(index, false));
            index++;
        }
        gref = gref->next();
    }
}

// 将主控玩家插入其所属槽位的中心位置
void ArrowFormation::AddMasterToSlot()
{
    Unit* followTarget = ai->GetUnit(AI_VALUE(ObjectGuid, "follow target"));
    Group* group = bot->GetGroup();
    GroupReference *gref = group->GetFirstMember();
    uint32 index = 0;
    while (gref)
    {
        Player* member = gref->getSource();

        if (member == followTarget)
        {
            FindSlot(member)->InsertAtCenter(masterUnit = new FormationUnit(index, true));
            break;
        }

        gref = gref->next();
        index++;
    }
}

// 调用指定的布局器依次计算槽位内所有成员的坐标
void FormationSlot::PlaceUnits(UnitPlacer* placer)
{
    uint32 index = 0;
    uint32 count = units.size();
    for (std::vector<FormationUnit*>::iterator i = units.begin(); i != units.end(); ++i)
    {
        FormationUnit* unit = *i;
        unit->SetLocation(placer->Place(unit, index, count));
        index++;
    }
}

// 按多行队列方式计算指定索引成员的偏移坐标
UnitPosition MultiLineUnitPlacer::Place(FormationUnit *unit, uint32 index, uint32 count)
{
    SingleLineUnitPlacer placer(orientation, range);
    if (count <= 6)
        return placer.Place(unit, index, count);

    int lineNo = index / 6;
    int indexInLine = index % 6;
    int lineSize = std::max(count - lineNo * 6, uint32(6));
    float x = cos(orientation) * range * lineNo;
    float y = sin(orientation) * range * lineNo;
    return placer.Place(unit, indexInLine, lineSize);
}

// 按单行展开方式计算指定索引成员的偏移坐标
UnitPosition SingleLineUnitPlacer::Place(FormationUnit *unit, uint32 index, uint32 count)
{
    float angle = orientation - M_PI / 2.0f;
    float x = cos(angle) * range * ((float)index - (float)count / 2);
    float y = sin(angle) * range * ((float)index - (float)count / 2);
    return UnitPosition(x, y);
}

// 整体平移该槽位内所有成员的平面坐标
void FormationSlot::Move(float dx, float dy)
{
    for (std::vector<FormationUnit*>::iterator i = units.begin(); i != units.end(); ++i)
    {
        FormationUnit* unit = *i;
        unit->SetLocation(unit->GetX() + dx, unit->GetY() + dy);
    }
}

// 析构释放槽位内的所有 FormationUnit 对象
FormationSlot::~FormationSlot()
{
    for (std::vector<FormationUnit*>::iterator i = units.begin(); i != units.end(); ++i)
    {
        FormationUnit* unit = *i;
        delete unit;
    }
    units.clear();
}
