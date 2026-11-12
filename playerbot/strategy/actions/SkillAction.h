#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 专业技能指令动作：查看、学习或调整机器人的生活与辅助专业技能
    class SkillAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化专业技能指令动作
        SkillAction(PlayerbotAI* ai) : ChatCommandAction(ai, "skill") {}
        /// 执行动作主逻辑（专业技能指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（专业技能指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "skill"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This chat command gives information about a bot\'s skills.\n"
                "Examples:\n"
                "skill : List all skills and their current level.\n"
                "skill [name] : List the skill level of a current skill.\n"
                "skill unlearn [name] : Unlearns a primary profession.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
