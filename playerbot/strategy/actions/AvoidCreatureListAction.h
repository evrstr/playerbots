#pragma once
#include "playerbot/LootObjectStack.h"
#include "GenericActions.h"

namespace ai
{
    /// 避开生物列表指令动作：管理机器人应主动绕行避开的特定生物列表
    class AvoidCreatureListAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化避开生物列表指令动作
        AvoidCreatureListAction(PlayerbotAI* ai) : ChatCommandAction(ai, "avoid creature list") {}
        /// 执行动作主逻辑（避开生物列表指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（避开生物列表指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "avoid creature list"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This chat command gives control over the list of creatures a bot should stay away from.\n"
                "Examples:\n"
                "avoid creature ? : List the creatures to avoid.\n"
                "avoid creature [creature id] : Stay away from this creature.\n"
                "avoid creature -[creature id] : Remove this creature id from the list.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "avoid creature list" }; }
#endif 

    private:
        /// 从指令参数中解析生物名称或 Entry ID 列表
        std::vector<std::string> ParseCreatures(const std::string& text);
    };
}
