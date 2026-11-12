#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 前往 RPG 目标动作：控制机器人向选定的 RPG 交互对象移动
    class MoveToRpgTargetAction : public MovementAction {
    public:
        /// 构造函数：初始化前往 RPG 目标动作
        MoveToRpgTargetAction(PlayerbotAI* ai) : MovementAction(ai, "move to rpg target") {}

        /// 执行动作主逻辑（前往 RPG 目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（前往 RPG 目标动作）
        virtual bool isUseful() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "move to rpg target"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This will make the bot move towards the current rpg target.\n"
                "When near the target the bot will move to a spot around the target\n"
                "45 degrees closest to the bot or 45 infront if the target is moving.\n"
                "This action will only execute if the bot is not moving or traveling.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "rpg target" , "ignore rpg target" ,  "travel target" , "can move around" }; }
#endif 
    };

}
