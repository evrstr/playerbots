#pragma once
#include "MovementActions.h"
#include "playerbot/AiFactory.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/ItemVisitors.h"
#include "playerbot/RandomPlayerbotMgr.h"
#ifdef MANGOSBOT_ZERO
#include "LFG/LFGMgr.h"
#include "LFG/LFGDefines.h"
#include "LFG/LFGQueue.h"
#endif
#ifdef MANGOSBOT_TWO
#include "LFG/LFGMgr.h"
#include "LFG/LFG.h"
#endif
#include "BattleGround/BattleGround.h"
#include "BattleGround/BattleGroundMgr.h"
#include "BattleGround/BattleGroundWS.h"
#include "ChooseTargetActions.h"
#include "CheckMountStateAction.h"
#include "G3D/Vector3.h"

namespace ai
{
    /// 加入地下城查找器排队动作：根据职业职责与副本需求排队加入 LFG
    class LfgJoinAction : public Action
    {
    public:
        /// 构造函数：初始化加入地下城查找器排队动作
        LfgJoinAction(PlayerbotAI* ai, std::string name = "lfg join") : Action(ai, name) {}
        /// 执行动作主逻辑（加入地下城查找器排队动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（加入地下城查找器排队动作）
        virtual bool isUseful() override;

    protected:
        /// 向地下城查找器提交排队请求
        bool JoinLFG();
        /// 根据职业与天赋设置机器人在 LFG 中的职责标识
        bool SetRoles();
#ifdef MANGOSBOT_TWO
        /// 获取机器人当前的地下城查找器职责标识
        LfgRoles GetRoles();
#endif
    };

    /// 接受地下城查找器邀请动作：收到 LFG 副本就绪确认框时自动接受进入
    class LfgAcceptAction : public LfgJoinAction
    {
    public:
        /// 构造函数：初始化接受地下城查找器邀请动作
        LfgAcceptAction(PlayerbotAI* ai) : LfgJoinAction(ai, "lfg accept") {}
        /// 执行动作主逻辑（接受地下城查找器邀请动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（接受地下城查找器邀请动作）
        virtual bool isUseful() override { return true; }
    };

    /// LFG 职责确认动作：收到队伍职责检查请求时自动确认自身坦克/治疗/输出职责
    class LfgRoleCheckAction : public LfgJoinAction
    {
    public:
        /// 构造函数：初始化LFG 职责确认动作
        LfgRoleCheckAction(PlayerbotAI* ai) : LfgJoinAction(ai, "lfg role check") {}
        /// 执行动作主逻辑（LFG 职责确认动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（LFG 职责确认动作）
        virtual bool isUseful() override { return true; }
    };

    /// 离开 LFG 队列动作：退出当前的地下城查找器排队状态
    class LfgLeaveAction : public Action
    {
    public:
        /// 构造函数：初始化离开 LFG 队列动作
        LfgLeaveAction(PlayerbotAI* ai) : Action(ai, "lfg leave") {}
        /// 执行动作主逻辑（离开 LFG 队列动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（离开 LFG 队列动作）
        virtual bool isUseful() override;
    };

    /// LFG 副本传送动作：执行传入或传出地下城查找器副本的传送操作
    class LfgTeleportAction : public Action
    {
    public:
        /// 构造函数：初始化LFG 副本传送动作
        LfgTeleportAction(PlayerbotAI* ai) : Action(ai, "lfg teleport") {}
        /// 执行动作主逻辑（LFG 副本传送动作）
        virtual bool Execute(Event& event) override;
    };
}
