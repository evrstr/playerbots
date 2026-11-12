#pragma once

#include "MovementActions.h"
#include "BattleGround/BattleGround.h"
#include "BattleGround/BattleGroundMgr.h"
#include "BattleGround/BattleGroundWS.h"
#include "BattleGround/BattleGroundAB.h"
#ifndef MANGOSBOT_ZERO
#include "BattleGround/BattleGroundEY.h"
#endif
#ifdef MANGOSBOT_TWO
#include "BattleGround/BattleGroundIC.h"
#include "BattleGround/BattleGroundSA.h"
#endif
#include "CheckMountStateAction.h"

using namespace ai;

#define SPELL_CAPTURE_BANNER 21651

typedef void(*BattleBotWaypointFunc) ();

// from vmangos (参考自 vmangos)
struct BattleBotWaypoint
{
    /// 构造函数：初始化战场路径点结构体
    BattleBotWaypoint(float x_, float y_, float z_, BattleBotWaypointFunc func) :
        x(x_), y(y_), z(z_), pFunc(func) {};
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    BattleBotWaypointFunc pFunc = nullptr;
};

typedef std::vector<BattleBotWaypoint> BattleBotPath;

extern std::vector<BattleBotPath*> const vPaths_WS;
extern std::vector<BattleBotPath*> const vPaths_AB;
extern std::vector<BattleBotPath*> const vPaths_AV;
extern std::vector<BattleBotPath*> const vPaths_EY;
extern std::vector<BattleBotPath*> const vPaths_IC;

/// 战场战术动作：管理机器人在各类战场中的目标选择、路径行进与旗帜攻防
class BGTactics : public MovementAction
{
public:
    /// 构造函数：初始化战场战术动作
    BGTactics(PlayerbotAI* ai, std::string name = "bg tactics") : MovementAction(ai, name) {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bg tactics"; }
        virtual std::string GetHelpDescription()
        {
            return "This action handles the bot's tactical movement in battlegrounds.\n"
                   "It includes pathfinding for objectives, flag handling, and strategic positioning.\n"
                   "Supports WSG, AB, AV, EY, and IC battlegrounds with specialized waypoints.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    /// 执行动作主逻辑（战场战术动作）
    virtual bool Execute(Event& event) override;
private:
    /// 为联盟方机器人挑选奥特兰克山谷当前最优先的战术目标
    bool SelectAvObjectiveAlliance(WorldLocation& objectiveLocation);
    /// 为部落方机器人挑选奥特兰克山谷当前最优先的战术目标
    bool SelectAvObjectiveHorde(WorldLocation& objectiveLocation);
    /// 控制机器人移动至战场或竞技场开局等待位置
    bool moveToStart(bool force = false);
    /// 根据战场实时战况与角色分工选择新的进攻或防守目标
    bool selectObjective(bool reset = false);
    /// 控制机器人向当前选定的战场战术目标点移动
    bool moveToObjective();
    /// 为当前战场目标选定合适的路径点引导序列
    bool selectObjectiveWp(std::vector<BattleBotPath*> const& vPaths);
    /// 沿着通往当前战场目标的预设路径点序列逐步推进
    bool moveToObjectiveWp(BattleBotPath* const& currentPath, uint32 currentPoint, bool reverse = false);
    /// 从起点的第一个路径点开始沿预设战场路径行进
    bool startNewPathBegin(std::vector<BattleBotPath*> const& vPaths);
    /// 脱离预设路径，直接使用通用寻路前往战场目标
    bool startNewPathFree(std::vector<BattleBotPath*> const& vPaths);
    /// 清除当前战场战术目标以便重新分配
    bool resetObjective();
    /// 初始化并处理战歌峡谷各据点之间的自定义战术路径
    bool wsgPaths();
    /// 执行战歌峡谷旗帜房顶跳下隧道或墓地的快捷跳跃动作
    bool wsgRoofJump();
    /// 处理风暴之眼战场中央平台与边缘的跳跃快捷路径
    bool eotsJump();
    /// 判断机器人当前是否正位于旗帜交互点附近
    bool atFlag(std::vector<BattleBotPath*> const& vPaths, std::vector<uint32> const& vFlagIds);
    /// 处理奥特兰克山谷战场中的墓地与哨塔旗帜夺取/防守逻辑
    bool CheckFlagAv();
    /// 判断指定阵营战歌/风暴旗帜当前是否已被夺走
    bool flagTaken();
    /// 判断己方队伍的旗帜是否正被敌方扛走
    bool teamFlagTaken();
    /// 在战歌峡谷等模式中靠近并护卫己方扛旗手
    bool protectFC();
    /// 检查并尝试使用指定的增益消耗品或法术
    bool useBuff();
    /// 统计指定战场据点周围正在防守的己方机器人数量
    uint32 getDefendersCount(Position point, float range, bool combat = true);
    /// 判断机器人在征服之岛等战场中是否被困在未破门的城堡内
    bool IsLockedInsideKeep();
};

/// 竞技场战术动作：管理机器人在竞技场中的站位控制与集火机动策略
class ArenaTactics : public MovementAction
{
public:
    /// 构造函数：初始化竞技场战术动作
    ArenaTactics(PlayerbotAI* ai, std::string name = "arena tactics") : MovementAction(ai, name) {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "arena tactics"; }
        virtual std::string GetHelpDescription()
        {
            return "This action handles the bot's movement strategy in arenas.\n"
                   "Focuses on controlling the center of the arena and maintaining optimal positioning.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    /// 执行动作主逻辑（竞技场战术动作）
    virtual bool Execute(Event& event) override;
private:
    /// 引导机器人向战场或竞技场中央区域移动
    bool moveToCenter(BattleGround *bg);
};
