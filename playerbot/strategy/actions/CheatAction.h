#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 作弊调试指令动作：执行测试与作弊辅助指令（如加金币、学技能、刷物品等）
    class CheatAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化作弊调试指令动作
        CheatAction(PlayerbotAI* ai) : ChatCommandAction(ai, "cheat") {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "cheat"; }
        virtual std::string GetHelpDescription()
        {
            return "This command enables/disables various cheats for testing (GM only).\n"
                   "Usage: cheat [+/-][cheatname]\n"
                   "+ to enable, - to disable\n"
                   "Example: cheat +attackspeed (enables attack speed cheat)\n"
                   "Example: cheat ? (lists active cheats)";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
        /// 执行动作主逻辑（作弊调试指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（作弊调试指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

        /// 根据作弊名称获取对应的位掩码标志
        static BotCheatMask GetCheatMask(std::string cheat);
        /// 根据作弊位掩码获取可读名称
        static std::string GetCheatName(BotCheatMask cheatMask);
    public:
        /// 列出机器人当前已开启的所有作弊功能
        void ListCheats(Player* requester);
        /// 为机器人启用指定的作弊调试标志
        void AddCheat(BotCheatMask cheatMask);
        /// 移除机器人指定的作弊调试标志
        void RemCheat(BotCheatMask cheatMask);
    };
}
