// 策略值头文件：PossibleTargetsValue（周围潜在敌对与中立目标列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "NearestUnitsValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // List of hostile and neutral targets in a range around the bot | 机器人周围一定范围内的敌对和中立目标列表
    // 单位列表计算器：查找指定范围内满足视线与自由移动攻击条件的可攻击单位
    class PossibleTargetsValue : public NearestUnitsValue, public Qualified
    {
    public:
        PossibleTargetsValue(PlayerbotAI* ai, std::string name = "possible targets", float range = sPlayerbotAIConfig.sightDistance, bool ignoreLos = false) :
          NearestUnitsValue(ai, name, range, ignoreLos), Qualified() {}

        std::list<ObjectGuid> Calculate() override;
        static bool IsValid(Unit* target, Player* player, bool ignoreLos = false);

    protected:
        virtual void FindUnits(std::list<Unit*> &targets) override;
        virtual bool AcceptUnit(Unit* unit) override;

        static void FindPossibleTargets(Player* player, std::list<Unit*>& targets, float range);
        static bool IsFriendly(Unit* target, Player* player);
        static bool IsAttackable(Unit* target, Player* player);
    };

    // 单位列表计算器：忽略视线限制扫描视距内所有潜在目标
    class AllTargetsValue : public PossibleTargetsValue
    {
    public:
        AllTargetsValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
        PossibleTargetsValue(ai, "all targets", range, true) {}
    };
}
