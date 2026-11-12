// 策略值头文件：RtiTargetValue（根据团队标记图标 RTI 查找对应目标）
#pragma once
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/Value.h"
#include "Groups/Group.h"
#include "TargetValue.h"

namespace ai
{
    // 目标值计算器：读取队伍为指定标记类型（攻击/控场）分配的团队标记图标并返回匹配单位 GUID
    class RtiTargetValue : public TargetValue
    {
    public:
        RtiTargetValue(PlayerbotAI* ai, std::string type = "rti", std::string name = "rti target") : type(type), TargetValue(ai,name)
        {}

    public:
        static int GetRtiIndex(std::string rti)
        {
            int index = -1;
            if(rti == "star") index = 0;
            else if(rti == "circle") index = 1;
            else if(rti == "diamond") index = 2;
            else if(rti == "triangle") index = 3;
            else if(rti == "moon") index = 4;
            else if(rti == "square") index = 5;
            else if(rti == "cross") index = 6;
            else if(rti == "skull") index = 7;
            return index;
        }

        ObjectGuid Calculate() override
        {
            Group *group = bot->GetGroup();
            if(!group)
                return ObjectGuid();

            std::string rti = AI_VALUE(std::string, type);
            int index = GetRtiIndex(rti);

            if (index == -1)
                return ObjectGuid();

            ObjectGuid guid = group->GetTargetIcon(index);
            if (!guid)
                return ObjectGuid();

            std::list<ObjectGuid> attackers = context->GetValue<std::list<ObjectGuid>>("possible targets no los")->Get();
            if (std::find(attackers.begin(), attackers.end(), guid) == attackers.end()) return ObjectGuid();

            Unit* unit = ai->GetUnit(ObjectGuid(guid));
            if (!unit || sServerFacade.UnitIsDead(unit) ||
                !bot->IsWithinDistInMap(unit, sPlayerbotAIConfig.sightDistance, false))
                return ObjectGuid();

            return unit ? unit->GetObjectGuid() : ObjectGuid();
        }

    private:
    std::string type;
    };

    // 目标值计算器：专用于查找被团队标记为控场（rti cc）的目标 GUID
    class RtiCcTargetValue : public RtiTargetValue
    {
    public:
        RtiCcTargetValue(PlayerbotAI* ai, std::string name = "rti cc target") : RtiTargetValue(ai, "rti cc", name) {}
    };
}
