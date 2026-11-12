// 策略值头文件：DeadValues（墓地选择与灵魂医者复活决策）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 死亡复活阈值常量：撤离/切换墓地/直接虚弱复活的死亡次数上限
    enum DeadValueConstants
    {
        DEATH_COUNT_BEFORE_EVAC = 15,
        DEATH_COUNT_BEFORE_TRYING_ANOTHER_GRAVEYARD = 10,
        DEATH_COUNT_BEFORE_REVIVING_AT_SPIRIT_HEALER = 8
    };

    // 坐标值计算器：计算当前或备用最近合适复活墓地的位置
    class GraveyardValue : public GuidPositionCalculatedValue, public Qualified
    {
    public:
        GraveyardValue(PlayerbotAI* ai, std::string name = "graveyard", int checkInterval = 10) : GuidPositionCalculatedValue(ai, name, checkInterval), Qualified() {}

    public:
        GuidPosition Calculate() override;
        WorldSafeLocsEntry const* GetAnotherAppropriateClosestGraveyard() const;
    };

    // 坐标值计算器：综合死亡次数、主控与旅行目标选择最佳复活墓地
    class BestGraveyardValue : public GuidPositionCalculatedValue
    {
    public:
        BestGraveyardValue(PlayerbotAI* ai, std::string name = "best graveyard", int checkInterval = 10) : GuidPositionCalculatedValue(ai, name, checkInterval) {}

    public:
        GuidPosition Calculate() override;
    };

    // 布尔值计算器：判断机器人是否应当放弃跑尸、直接在灵魂医者处复活
    class ShouldSpiritHealerValue : public BoolCalculatedValue
    {
    public:
        ShouldSpiritHealerValue(PlayerbotAI* ai, std::string name = "should spirit healer") : BoolCalculatedValue(ai, name) {}

    public:
        bool Calculate() override;
    };
}
