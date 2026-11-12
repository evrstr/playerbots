// 策略值头文件：MoveStyleValue（移动风格开关：等待敌人/防坠崖边缘检测）
#pragma once
#include "playerbot/LootObjectStack.h"
#include "playerbot/strategy/Value.h"
#include "SubStrategyValue.h"

namespace ai
{
    // 子策略值：控制机器人的移动行为风格（wait：等待敌人接近；noedge：规避悬崖边缘）
    class MoveStyleValue : public SubStrategyValue
    {
    public:
        MoveStyleValue(PlayerbotAI* ai, const std::string& defaultValue = "", const std::string& name = "move style", const std::string& allowedValues = "wait,noedge") : SubStrategyValue(ai, defaultValue, name, allowedValues) {}

        static bool WaitForEnemy(PlayerbotAI* ai) { return HasValue(ai, "wait"); }
        static bool CheckForEdges(PlayerbotAI* ai) { return HasValue(ai, "noedge"); }
        
    private:
        static bool HasValue(PlayerbotAI* ai, const std::string& value);
    };
}
