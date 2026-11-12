// 策略值头文件：NearestNpcsValue（附近非敌对 NPC 与可搭乘载具列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "NearestUnitsValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 单位列表计算器：查找视距内的所有非敌对非玩家 NPC
    class NearestNpcsValue : public NearestUnitsValue
    {
    public:
        NearestNpcsValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance, bool ignoreLos = false) :
          NearestUnitsValue(ai, "nearest npcs", range, ignoreLos) {}

    protected:
        void FindUnits(std::list<Unit*> &targets) override;
        bool AcceptUnit(Unit* unit) override;
    };

    // 单位列表计算器：查找视距内可登乘的存活载具单位（WLK 版本）
    class NearestVehiclesValue : public NearestUnitsValue
    {
    public:
        NearestVehiclesValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
            NearestUnitsValue(ai, "nearest vehicles", range) {}

    protected:
        void FindUnits(std::list<Unit*>& targets) override;
        bool AcceptUnit(Unit* unit) override;
    };
}
