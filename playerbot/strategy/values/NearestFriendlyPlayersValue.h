// 策略值头文件：NearestFriendlyPlayersValue（附近友方玩家列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "NearestUnitsValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 单位列表计算器：查找视距内所有友方玩家（排除机器人自身）
    class NearestFriendlyPlayersValue : public NearestUnitsValue
    {
    public:
        NearestFriendlyPlayersValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
            NearestUnitsValue(ai, "nearest friendly players", range) {}

    protected:
        void FindUnits(std::list<Unit*> &targets) override;
        virtual bool AcceptUnit(Unit* unit) override;
    };
}
