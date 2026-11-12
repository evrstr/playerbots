#pragma once
#include "MovementActions.h"
#include "playerbot/strategy/values/HazardsValue.h"


namespace ai
{
    /// 远离地面危险区域动作：检测到脚下或附近存在火焰、毒圈等危险区域时迅速跑开
    class MoveAwayFromHazard : public MovementAction
    {
    public:
        /// 构造函数：初始化远离地面危险区域动作
        MoveAwayFromHazard(PlayerbotAI* ai, std::string name = "move away from hazard") : MovementAction(ai, name) {}
        /// 执行动作主逻辑（远离地面危险区域动作）
        bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（远离地面危险区域动作）
        bool isPossible() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "move away from hazard"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot move away from hazardous areas in dungeons.\n"
                   "It identifies dangerous positions and navigates to a safer location.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"hazards"}; }
#endif 

    private:
        /// 检查机器人当前周围是否存在需要规避的危险区域
        bool IsHazardNearby(const WorldPosition& point, const std::list<HazardPosition>& hazards) const;
    };

    /// 远离特定生物动作：与需要保持距离的危险首领或爆炸怪物拉开安全间距
    class MoveAwayFromCreature : public MovementAction
    {
    public:
        /// 构造函数：初始化远离特定生物动作
        MoveAwayFromCreature(PlayerbotAI* ai, std::string name, uint32 creatureID, float range, bool ignoreVictim = false, bool healersSafe = false) : MovementAction(ai, name), creatureID(creatureID), range(range), ignoreVictim(ignoreVictim), healersSafe(healersSafe) {}
        /// 执行动作主逻辑（远离特定生物动作）
        bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（远离特定生物动作）
        bool isPossible() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "move away from creature"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot move away from a specific creature in dungeons.\n"
                   "It maintains a safe distance from the specified creature ID within a defined range.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"hazards"}; }
#endif 

    protected:
        /// 验证三维坐标点是否处于合法地图边界与有效地形内
        bool IsValidPoint(const WorldPosition& point, const std::list<Creature*>& creatures, const std::list<HazardPosition>& hazards);
        /// 检查周围指定范围内是否存在生物单位
        bool HasCreaturesNearby(const WorldPosition& point, const std::list<Creature*>& creatures) const;
        /// 检查机器人当前周围是否存在需要规避的危险区域
        bool IsHazardNearby(const WorldPosition& point, const std::list<HazardPosition>& hazards) const;
        /// 遍历并筛选符合条件的附近生物辅助函数
        bool CreatureSearchHelperFunction(Event& event, uint32 creatureId);

    protected:
        uint32 creatureID;
        float range;
        bool ignoreVictim;
        bool healersSafe;
    };

    /// 远离指定生物列表动作：避开黑名单或配置中指定的高危生物
    class MoveAwayFromSpecificCreatures : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离指定生物列表动作
        MoveAwayFromSpecificCreatures(PlayerbotAI* ai, bool ignoreVictim = true, std::string name = "move away from specific creatures") : MoveAwayFromCreature(ai, name, 0, 10.0f , ignoreVictim) {}
        /// 执行动作主逻辑（远离指定生物列表动作）
        bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "move away from specific creatures"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot move away from specific creatures defined by the avoid creature list.\n"
                   "It maintains a safe distance from the specified creature IDs within a defined range.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"hazards"}; }
#endif 
    };
}
