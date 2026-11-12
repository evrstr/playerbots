#pragma once
#include "playerbot/LootObjectStack.h"
#include "GenericActions.h"

namespace ai
{
    /// 忽略法术列表指令动作：管理机器人施法逻辑中应跳过的法术清单
    class SkipSpellsListAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化忽略法术列表指令动作
        SkipSpellsListAction(PlayerbotAI* ai) : ChatCommandAction(ai, "skip spells list") {}
        /// 执行动作主逻辑（忽略法术列表指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（忽略法术列表指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "skip spells list"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This chat command gives control over the list of spells bots aren't allowed to cast.\n"
                "Examples:\n"
                "ss ? : List the ignored spells.\n"
                "ss [spell name] : Never cast this spell.\n"
                "ss -[spell name] : Remove this spell from the ignored spell list.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "skip spells list" }; }
#endif 

    private:
        /// 从指令参数中解析法术名称或法术 ID 列表
        std::vector<std::string> ParseSpells(const std::string& text);
    };
}
