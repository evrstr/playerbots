// 策略值头文件：CollisionValue（单位体积碰撞检测）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 布尔值计算器：检测机器人当前是否与附近可见单位发生碰撞体积重叠
    class CollisionValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CollisionValue(PlayerbotAI* ai, std::string name = "collision") : BoolCalculatedValue(ai, name), Qualified() {}

        virtual bool Calculate() override;
    };
}
