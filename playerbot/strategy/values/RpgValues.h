// 策略值头文件：RpgValues（下一个计划执行的 RPG 交互动作名称）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：保存机器人下一步将对目标 NPC/对象执行的 RPG 动作名称
    class NextRpgActionValue : public ManualSetValue<std::string>
    {
    public:
        NextRpgActionValue(PlayerbotAI* ai, std::string defaultValue = "", std::string name = "next rpg action") : ManualSetValue(ai, defaultValue, name) {};
    };
}
