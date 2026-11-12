// 策略值实现：Stances（贴近/坦克/背对/绕背战斗姿态实现及命令切换）

#include "playerbot/playerbot.h"
#include "Stances.h"

#include "playerbot/ServerFacade.h"
#include "Arrow.h"

using namespace ai;

// 获取攻击目标或当前目标作为站位参照单位
Unit* Stance::GetTarget()
{
    Unit *target = ai->GetUnit(AI_VALUE(ObjectGuid, GetTargetName()));
    if (target) return target;

    ObjectGuid attackTarget = context->GetValue<ObjectGuid>("attack target")->Get();
    if (attackTarget) ai->GetUnit(attackTarget);

    return NULL;
}

// 在非战斗或无目标时返回空坐标，否则调用子类计算目标周围站位
WorldLocation Stance::GetLocation()
{
    Unit* target = GetTarget();
    if (!target)
        return Formation::NullLocation;

    return GetLocationInternal();
}

// 以目标为中心、按指定角度和距离计算可达地形坐标
WorldLocation Stance::GetNearLocation(float angle, float distance)
{
    Unit* target = GetTarget();

    float x = target->GetPositionX() + cos(angle) * distance,
         y = target->GetPositionY()+ sin(angle) * distance,
         z = target->GetPositionZ();

    if (bot->IsWithinLOS(x, y, z + bot->GetCollisionHeight(), true))
        return WorldLocation(bot->GetMapId(), x, y, z);

    return Formation::NullLocation;
}

// 根据近战范围和目标碰撞半径计算具体角度站位
WorldLocation MoveStance::GetLocationInternal()
{
    Unit* target = GetTarget();
    float distance = std::max(sPlayerbotAIConfig.meleeDistance, target->GetObjectBoundingRadius());

    float angle = GetAngle();
    return GetNearLocation(angle, distance);
}

namespace ai
{
    // 近身姿态：贴近目标并在启用 behind 策略时优先绕背
    class NearStance : public MoveStance
    {
    public:
        NearStance(PlayerbotAI* ai) : MoveStance(ai, "near") {}

        virtual float GetAngle() override
        {
            Unit* target = GetTarget();

#ifdef MANGOS
            if (target->getVictim() && target->getVictim()->GetObjectGuid() == bot->GetObjectGuid())
                return target->GetOrientation();
#endif
#ifdef CMANGOS
            if (target->GetVictim() && target->GetVictim()->GetObjectGuid() == bot->GetObjectGuid())
                return target->GetOrientation();
#endif

            if (ai->HasStrategy("behind", BotState::BOT_STATE_COMBAT))
            {
                Unit* target = GetTarget();
                Group* group = bot->GetGroup();
                int index = 0, count = 0;
                if (group)
                {
                    for (GroupReference *ref = group->GetFirstMember(); ref; ref = ref->next())
                    {
                        Player* member = ref->getSource();
                        if (!ai->IsSafe(member))
                            continue;

                        if (member == bot) index = count;
                        if (member && !ai->IsRanged(member) && !ai->IsTank(member)) count++;
                    }
                }

                float angle = target->GetOrientation() + M_PI;
                if (!count) return angle;

                float increment = M_PI / 4 / count;
                return round((angle + index * increment - M_PI / 4) * 10.0f) / 10.0f;
            }

            float angle = GetFollowAngle() + target->GetOrientation();

            Player* master = GetMaster();
            if (master)
                angle -= master->GetOrientation();

            return angle;
        }
    };

    // 坦克姿态：与目标保持固定坦克朝向站位
    class TankStance : public MoveStance
    {
    public:
        TankStance(PlayerbotAI* ai) : MoveStance(ai, "tank") {}

        virtual float GetAngle() override
        {
            Unit* target = GetTarget();
            return target->GetOrientation();
        }
    };

    // 背对姿态：使机器人站到背对目标一侧并调整面向
    class TurnBackStance : public MoveStance
    {
    public:
        TurnBackStance(PlayerbotAI* ai) : MoveStance(ai, "turnback") {}

        virtual float GetAngle() override
        {
            Unit* target = GetTarget();
            Group* group = bot->GetGroup();
            int count = 0;
            float angle = 0.0f;
            if (group)
            {
                for (GroupReference *ref = group->GetFirstMember(); ref; ref = ref->next())
                {
                    Player* member = ref->getSource();
                    if (member && ai->IsSafe(member) && member != bot && ai->IsRanged(member))
                    {
                        angle += target->GetAngle(member);
                        count++;
                    }
                }
            }

            if (!count) return target->GetOrientation();
            return round((angle / count) * 10.0f) / 10.0f + M_PI;
        }
    };

    // 绕背姿态：绕至目标背后位置（适用于盗贼背刺、防止招架）
    class BehindStance : public MoveStance
    {
    public:
        BehindStance(PlayerbotAI* ai) : MoveStance(ai, "behind") {}

        virtual float GetAngle() override
        {
            Unit* target = GetTarget();
            Group* group = bot->GetGroup();
            int index = 0, count = 0;
            if (group)
            {
                for (GroupReference *ref = group->GetFirstMember(); ref; ref = ref->next())
                {
                    Player* member = ref->getSource();
                    if (!ai->IsSafe(member))
                        continue;
                    if (member == bot) index = count;
                    if (member && !ai->IsRanged(member) && !ai->IsTank(member)) count++;
                }
            }

            float angle = target->GetOrientation() + M_PI;
            if (!count) return angle;

            float increment = M_PI / 4 / count;
            return round((angle + index * increment - M_PI / 4) * 10.0f) / 10.0f;
        }
    };
};

// 构造函数：默认使用 NearStance 近身姿态
StanceValue::StanceValue(PlayerbotAI* ai) : ManualSetValue<Stance*>(ai, new NearStance(ai), "stance")
{
}

// 释放并重置当前姿态指针
void StanceValue::Reset()
{
    if (value) delete value;
    value = new NearStance(ai);
}

// 返回当前姿态名称以便保存
std::string StanceValue::Save()
{
    return value ? value->getName() : "?";
}

// 按名称实例化对应的战斗站位姿态（near/tank/turnback/behind）
bool StanceValue::Load(std::string name)
{
    if (name == "behind")
    {
        if (value) delete value;
        value = new BehindStance(ai);
    }
    else if (name == "near" || name == "default")
    {
        if (value) delete value;
        value = new NearStance(ai);
    }
    else if (name == "tank")
    {
        if (value) delete value;
        value = new TankStance(ai);
    }
    else if (name == "turnback" || name == "turn")
    {
        if (value) delete value;
        value = new TurnBackStance(ai);
    }
    else return false;

    return true;
}

// 执行聊天指令设置、重置或查询当前战斗站位姿态
bool SetStanceAction::Execute(Event& event)
{
    std::string stance = event.getParam();
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    StanceValue* value = (StanceValue*)context->GetValue<Stance*>("stance");
    if (stance == "?" || stance.empty())
    {
        std::ostringstream str; str << "Stance: |cff00ff00" << value->Get()->getName();
        ai->TellPlayer(requester, str);
        return true;
    }

    if (stance == "show")
    {
        WorldLocation loc = value->Get()->GetLocation();
        if (!Formation::IsNullLocation(loc))
            ai->Ping(loc.coord_x, loc.coord_y);

        return true;
    }

    if (!value->Load(stance))
    {
        std::ostringstream str; str << "Invalid stance: |cffff0000" << stance;
        ai->TellPlayer(requester, str);
        ai->TellPlayer(requester, "Please set to any of:|cffffffff near (default), tank, turnback, behind");
        return false;
    }

    std::ostringstream str; str << "Stance set to: " << stance;
    ai->TellPlayer(requester, str);
    return true;
}
