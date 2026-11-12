/// 焦点目标（治疗与团队标记）策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：使治疗机器人优先且集中治疗由指令指定的焦点友方目标
    class FocusHealTargetsStrategy : public Strategy
    {
    public:
        FocusHealTargetsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "focus heal targets"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "focus heal targets"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription()
        {
            return "This strategy will make the bot focus heal the specified target using the 'set focus heal <targetname>' command";
        }
#endif
    };

    /// 策略：使输出机器人忽略其他目标，专注攻击指定的团队标记（RTI）目标
    class FocusRtiTargetsStrategy : public Strategy
    {
    public:
        FocusRtiTargetsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "focus rti targets"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "focus rti targets"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription()
        {
            return "This strategy will make the bot ignore all targets except it's current rti target.";
        }
#endif
    };    
}