// 策略值头文件：NearestNonBotPlayersValue（附近的真实玩家列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "NearestUnitsValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 单位列表计算器：查找反应距离内非 Playerbot 控制的真实玩家（过滤隐身 GM）
    class NearestNonBotPlayersValue : public NearestUnitsValue
    {
    public:
        NearestNonBotPlayersValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.reactDistance) :
          NearestUnitsValue(ai, "nearest non bot players", range, true) {}

    protected:
        void FindUnits(std::list<Unit*> &targets) override;
        bool AcceptUnit(Unit* unit) override;
    };
}
