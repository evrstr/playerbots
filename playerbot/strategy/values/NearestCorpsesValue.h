// 策略值头文件：NearestCorpsesValue（附近死亡单位尸体列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "NearestUnitsValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 单位列表计算器：搜索视距内所有已死亡生物或玩家的尸体
    class NearestCorpsesValue : public NearestUnitsValue
    {
    public:
        NearestCorpsesValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          NearestUnitsValue(ai, "nearest corpses", range) {}

    protected:
        void FindUnits(std::list<Unit*> &targets) override;
        bool AcceptUnit(Unit* unit) override;

    };
}
