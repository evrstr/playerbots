// 策略值头文件：PossibleRpgTargetsValue（附近可进行角色扮演交互的 NPC 目标）
#pragma once
#include "playerbot/strategy/Value.h"
#include "NearestUnitsValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 单位列表计算器：筛选 RPG 距离内带任务/商人/训练师/银行等交互标志的非敌对 NPC
    class PossibleRpgTargetsValue : public NearestUnitsValue
    {
    public:
        PossibleRpgTargetsValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.rpgDistance);

    protected:
        void FindUnits(std::list<Unit*> &targets) override;
        bool AcceptUnit(Unit* unit) override;

    public:
        static std::vector<uint32> allowedNpcFlags;
    };
}
