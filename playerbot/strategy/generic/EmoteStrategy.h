/// 表情动作与社交互动策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：使机器人随机发送表情动画、响应他人表情或进行简单社交互动
    class EmoteStrategy : public Strategy
    {
    public:
        EmoteStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "emote"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "emote"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make the bot react to or randomly send emotes.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
