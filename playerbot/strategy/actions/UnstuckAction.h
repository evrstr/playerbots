#ifndef _PLAYERBOT_UNSTUCKACTION_H
#define _PLAYERBOT_UNSTUCKACTION_H

#include "GenericActions.h"

class PlayerbotAI;

/// 卡死脱困动作：检测机器人卡在地形中并尝试跳跃、寻路重置或传送脱困
class UnstuckAction : public Action
{
public:
    /// 构造函数：初始化卡死脱困动作
    UnstuckAction(PlayerbotAI* ai) : Action(ai, "unstuck") {}
    /// 执行动作主逻辑（卡死脱困动作）
    virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
    virtual std::string GetHelpName() { return "unstuck"; }
    virtual std::string GetHelpDescription()
    {
        return "This action attempts to unstuck the bot by choosing an appropriate method based on the event source.\n"
               "Methods include resetting position, using hearthstone, or repopping at the spirit healer.";
    }
    virtual std::vector<std::string> GetUsedActions() { return {"reset", "hearthstone", "repop"}; }
    virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif
};

/// 解除僵持状态动作：当机器人与目标陷入长时间僵持无动作时重置目标与路径
class DropStandoffAction : public Action
{
public:
    /// 构造函数：初始化解除僵持状态动作
    DropStandoffAction(PlayerbotAI* ai) : Action(ai, "drop standoff") {}
    /// 执行动作主逻辑（解除僵持状态动作）
    virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
    virtual std::string GetHelpName() { return "drop standoff"; }
    virtual std::string GetHelpDescription()
    {
        return "Drops a frozen combat stand-off: nobody exchanged damage while the bot stood still, so combat is stopped\n"
               "and targets cleared, letting the state machine re-decide (fresh engagement or non-combat agenda).";
    }
    virtual std::vector<std::string> GetUsedActions() { return {}; }
    virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif
};

/// 释放卡死移动状态动作：在移动长时间无位移时清除当前移动生成器并复位
class ReleaseStuckMovementAction : public Action
{
public:
    /// 构造函数：初始化释放卡死移动状态动作
    ReleaseStuckMovementAction(PlayerbotAI* ai) : Action(ai, "release stuck movement") {}
    /// 执行动作主逻辑（释放卡死移动状态动作）
    virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
    virtual std::string GetHelpName() { return "release stuck movement"; }
    virtual std::string GetHelpDescription()
    {
        return "Drops the current target when a movement action has been looping without the bot actually moving,\n"
               "losing health or changing target - the strategy machine then re-decides.";
    }
    virtual std::vector<std::string> GetUsedActions() { return {}; }
    virtual std::vector<std::string> GetUsedValues() { return { "movement loop age" }; }
#endif
};

#endif
