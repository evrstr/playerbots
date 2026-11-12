// 策略值头文件：FreeMoveValues（自由移动中心点、范围与可自由移动判定）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{    
    // 位置计算器：确定机器人自由移动的锚点中心（主控、阵型点或自身）
    class FreeMoveCenterValue : public GuidPositionCalculatedValue
    {
    public:
        FreeMoveCenterValue(PlayerbotAI* ai) : GuidPositionCalculatedValue(ai, "free move center", 5) {};
        virtual GuidPosition Calculate() override;
    };   

    // 浮点值计算器：计算机器人允许自由移动的最大半径范围
    class FreeMoveRangeValue : public FloatCalculatedValue
    {
    public:
        FreeMoveRangeValue(PlayerbotAI* ai) : FloatCalculatedValue(ai, "free move range", 2) {};
        virtual float Calculate() override;
    };

    // 布尔值计算器：判断目标点是否在机器人当前允许自由移动的安全范围内
    class CanFreeMoveValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CanFreeMoveValue(PlayerbotAI* ai, std::string name = "can free move", int checkInterval = 2) : BoolCalculatedValue(ai, name, checkInterval), Qualified() {};
        static bool CanFreeMoveTo(PlayerbotAI* ai, WorldPosition dest);
        static bool CanFreeTarget(PlayerbotAI* ai, WorldPosition dest);
        static bool CanFreeAttack(PlayerbotAI* ai, WorldPosition dest);

        bool Calculate() override;
    private:
        //Actual caculation functions used. | 实际执行自由移动距离判定的内部函数
        static bool CanFreeMove(PlayerbotAI* ai, WorldPosition dest, float range);
    }; 
};

