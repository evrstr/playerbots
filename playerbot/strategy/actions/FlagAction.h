#pragma once
#include "playerbot/LootObjectStack.h"
#include "GenericActions.h"

namespace ai
{
    /// PvP/状态标记指令动作：查询或切换机器人的 PvP 标记或特定状态旗标
    class FlagAction : public ChatCommandAction, public Qualified
    {
    public:
        /// 构造函数：初始化PvP/状态标记指令动作
        FlagAction(PlayerbotAI* ai) : ChatCommandAction(ai, "flag") {}
        /// 执行动作主逻辑（PvP/状态标记指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（PvP/状态标记指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "flag"; }
        virtual std::string GetHelpDescription()
        {
            return "This command allows the bot to set or manage flags.\n"
                   "Usage: flag [flag_type] [action]\n"
                   "Flag types: pvp, sheathe, cloak, helm\n"
                   "Actions: on/set, off/clear, toggle\n"
                   "Examples:\n"
                   "  flag pvp on - Sets the PVP flag\n"
                   "  flag cloak toggle - Toggles the cloak visibility\n"
                   "  flag sheathe off - Unequips weapons (sheathes)\n"
                   "  flag helm set - Shows the helm\n"
                   "  flag pvp ? - Shows current PVP state";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
