#pragma once
#include "MovementActions.h"
#include "playerbot/AiFactory.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/ItemVisitors.h"
#include "playerbot/RandomPlayerbotMgr.h"
#include "BattleGround/BattleGround.h"
#include "BattleGround/BattleGroundMgr.h"
#include "BattleGround/BattleGroundWS.h"
#include "ChooseTargetActions.h"
#include "CheckMountStateAction.h"
#include "G3D/Vector3.h"
#include "Entities/GameObject.h"

using namespace ai;


/// 加入战场动作：寻找附近战场军官或响应真实玩家队列加入战场排队
class BGJoinAction : public Action
{
public:
    /// 构造函数：初始化加入战场动作
    BGJoinAction(PlayerbotAI* ai, std::string name = "bg join") : Action(ai, name) {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bg join"; }
        virtual std::string GetHelpDescription()
        {
            return "This action will make bots join a bg queue that has a player waiting to join.\n"
                   "Bots will automatically fill up the bg to make sure the player has enough opponents.\n"
                   "Bots are able to join from anywhere in the world.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    /// 执行动作主逻辑（加入战场动作）
    virtual bool Execute(Event& event) override;
    /// 判断当前状态下该动作是否可用/有效（加入战场动作）
    virtual bool isUseful() override;
    /// 检查机器人等级、逃亡者减益与队列槽位是否允许加入战场
    virtual bool canJoinBg(Player* player, BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId);
    /// 判断当前队列是否有真实玩家或满足自由机器人参战条件
    virtual bool shouldJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId);
#ifndef MANGOSBOT_ZERO
    /// 检查并确保竞技场战队成员在线且组队完毕
    virtual bool gatherArenaTeam(ArenaType type);
#endif
protected:
    /// 向战场军官发送加入指定战场队列的网络封包
    bool JoinQueue(uint32 type);
    std::vector<uint32> bgList;
    std::vector<uint32> ratedList;
};

/// 自由加入战场动作：随机/自由机器人在战场军官处主动排队加入战场
class FreeBGJoinAction : public BGJoinAction
{
public:
    /// 构造函数：初始化自由加入战场动作
    FreeBGJoinAction(PlayerbotAI* ai, std::string name = "free bg join") : BGJoinAction(ai, name) {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "free bg join"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot join the battlegroun queue of the battlemaster it was just talking to.\n"
                   "This action results from a rpg action with an actual npc.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    /// 判断当前队列是否有真实玩家或满足自由机器人参战条件
    virtual bool shouldJoinBg(BattleGroundQueueTypeId queueTypeId, BattleGroundBracketId bracketId);
};

/// 离开战场动作：战场结束或满足离开条件时退出当前战场
class BGLeaveAction : public Action
{
public:
    /// 构造函数：初始化离开战场动作
    BGLeaveAction(PlayerbotAI* ai, std::string name = "bg leave") : Action(ai) {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bg leave"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot leave the current battleground.\n"
                   "This action is normally used after the battleground ends.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    /// 执行动作主逻辑（离开战场动作）
    virtual bool Execute(Event& event) override;
};

/// 战场状态处理动作：处理战场队列状态更新并在就绪时传送进入战场
class BGStatusAction : public Action
{
public:
    /// 构造函数：初始化战场状态处理动作
    BGStatusAction(PlayerbotAI* ai) : Action(ai, "bg status") {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bg status"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot check the battleground queue status.\n"
                   "It will make the bot teleport to the battleground when it is ready.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    /// 执行动作主逻辑（战场状态处理动作）
    virtual bool Execute(Event& event) override;
    /// 判断当前状态下该动作是否可用/有效（战场状态处理动作）
    virtual bool isUseful() override;
};

/// 战场状态检查动作：主动向服务端请求查询当前战场队列状态
class BGStatusCheckAction : public Action
{
public:
    /// 构造函数：初始化战场状态检查动作
    BGStatusCheckAction(PlayerbotAI* ai, std::string name = "bg status check") : Action(ai, name) {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bg status check"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot ask for the current battleground queue status.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    /// 执行动作主逻辑（战场状态检查动作）
    virtual bool Execute(Event& event) override;
    /// 判断当前状态下该动作是否可用/有效（战场状态检查动作）
    virtual bool isUseful() override;
};
