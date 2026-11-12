// 策略值头文件：EnemyPlayerValue（附近敌对玩家列表、存在判断及最佳敌对玩家目标）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"
#include "PossibleTargetsValue.h"

namespace ai
{
    // List of enemy player targets that are near the bot (or bot group) | 靠近机器人（或其队伍）的敌对玩家目标列表
    // 目标列表计算器：收集附近有效的敌对玩家目标并过滤不可达者
    class EnemyPlayersValue : public ObjectGuidListCalculatedValue, public Qualified
    {
    public:
        EnemyPlayersValue(PlayerbotAI* ai) : ObjectGuidListCalculatedValue(ai, "enemy players"), Qualified() {}
        std::list<ObjectGuid> Calculate() override;

        static bool IsValid(Unit* target, Player* player);
        static bool IsReachable(Unit* target, Player* player);

    private:
        void ApplyFilter(std::list<ObjectGuid>& targets, bool getOne);
    };

    // 布尔值计算器：判断附近是否存在敌对玩家目标
    class HasEnemyPlayersValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasEnemyPlayersValue(PlayerbotAI* ai, std::string name = "has enemy players") : BoolCalculatedValue(ai, name, 3), Qualified() {}
        virtual bool Calculate() override;
    };

    // 目标值计算器：综合旗帜、距离与血量优先级选取最值得攻击的敌对玩家
    class EnemyPlayerValue : public UnitCalculatedValue
    {
    public:
        EnemyPlayerValue(PlayerbotAI* ai, std::string name = "enemy player") : UnitCalculatedValue(ai, name) {}
        virtual ObjectGuid Calculate() override;

        static float GetMaxAttackDistance(Player* bot);
    };
}
