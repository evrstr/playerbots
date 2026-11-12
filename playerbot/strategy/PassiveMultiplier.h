#pragma once
#include "Action.h"
#include "Multiplier.h"

namespace ai
{
    /// 被动模式权重乘数，在 passive 策略下屏蔽除跟随/待命/指令及瞬发法术外的其他动作
    class PassiveMultiplier : public Multiplier
    {
    public:
        PassiveMultiplier(PlayerbotAI* ai);

    public:
        virtual float GetValue(Action* action) override;

    private:
        static std::list<std::string> allowedActions;
        static std::list<std::string> allowedParts;
    };
}
