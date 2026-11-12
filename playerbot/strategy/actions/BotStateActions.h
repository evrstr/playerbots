#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 设置战斗状态动作：将机器人 AI 状态切换为战斗状态（COMBAT）
    class SetCombatStateAction : public Action 
    {
    public:
        /// 构造函数：初始化设置战斗状态动作
        SetCombatStateAction(PlayerbotAI* ai, std::string name = "set combat state") : Action(ai, name) {}
        /// 执行动作主逻辑（设置战斗状态动作）
        bool Execute(Event& event) override;
    };

    /// 设置非战斗状态动作：将机器人 AI 状态切换为非战斗状态（NON_COMBAT）
    class SetNonCombatStateAction : public Action
    {
    public:
        /// 构造函数：初始化设置非战斗状态动作
        SetNonCombatStateAction(PlayerbotAI* ai, std::string name = "set non combat state") : Action(ai, name) {}
        /// 执行动作主逻辑（设置非战斗状态动作）
        bool Execute(Event& event) override;
    };

    /// 设置死亡状态动作：将机器人 AI 状态切换为死亡状态（DEAD）
    class SetDeadStateAction : public Action
    {
    public:
        /// 构造函数：初始化设置死亡状态动作
        SetDeadStateAction(PlayerbotAI* ai, std::string name = "set dead state") : Action(ai, name) {}
        /// 执行动作主逻辑（设置死亡状态动作）
        bool Execute(Event& event) override;
    };
}
