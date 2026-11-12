#pragma once
#include "MovementActions.h"

namespace ai
{
    class TravelDestination;

    /// 前往指定位置指令动作：解析坐标、玩家、NPC 或区域名称并控制机器人移动或传送前往
    class GoAction : public MovementAction, Qualified
    {
    public:
        /// 构造函数：初始化前往指定位置指令动作
        GoAction(PlayerbotAI* ai, std::string name = "go") : MovementAction(ai, name), Qualified() {}
        /// 执行动作主逻辑（前往指定位置指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（前往指定位置指令动作）
        virtual bool isPossible() override { return true; }
        /// 判断当前状态下该动作是否可用/有效（前往指定位置指令动作）
        virtual bool isUseful() override { return true; }
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（前往指定位置指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "go"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This will make the bot move to a specific location.\n"
                "Examples:\n"
                "go [game object] : Move to the specified game object.\n"
                "go <player or npc name> : Move to specified player or npc.\n"
                "go x;y : Move to gps location.\n"
                "go where : Ask the bot where it wants to go.\n"
                "go to <npc, zone or creature name> : Travel up to specified object\n or while following explain how to get there.\n"
                "go travel <npc, zone or creature name> : Set the bots current travel destination\n to specified object and travel (up to) that location.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "travel target" ,  "nearest npcs" ,  "nearest friendly players" , "position" }; }
#endif 

    private:
        /// 告知主人或队友目标任务/地点的大致方位
        bool TellWhereToGo(std::string& param, Player* requester) const;
        /// 检查队长是否已经处于前往同一旅行目标的途中
        bool LeaderAlreadyTraveling(TravelDestination* dest) const;
        /// 说明前往指定目的地所需的交通路线或坐标指引
        bool TellHowToGo(TravelDestination* dest, Player* requester) const;
        /// 设置旅行目标并启动前往指定目的地的长途移动
        bool TravelTo(TravelDestination* dest, Player* requester) const;
        /// 移动至指定游戏对象所在位置
        bool MoveToGo(std::string& param, Player* requester);
        /// 移动至目标单位附近（动态追踪其位置）
        bool MoveToUnit(std::string& param, Player* requester);
        /// 移动至指定 GPS 坐标位置
        bool MoveToGps(std::string& param, Player* requester);
        /// 跨地图或指定地图 ID 移动至目标 GPS 坐标
        bool MoveToMapGps(std::string& param, Player* requester);
        /// 移动至保存的命名坐标位置
        bool MoveToPosition(std::string& param, Player* requester);

        /// 更新与移动策略（如停留/警戒）关联的基准坐标
        void UpdateStrategyPosition(const WorldPosition& position);
    };
}
