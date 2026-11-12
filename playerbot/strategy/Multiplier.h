#pragma once

#include "AiObject.h"

class PlayerbotAI;

namespace ai
{
    class Action;
}

namespace ai
{
    /// 动作相关性权重乘数基类，用于在决策阶段动态缩放特定动作的优先级
    class Multiplier : public AiNamedObject
    {
    public:
        Multiplier(PlayerbotAI* ai, std::string name) : AiNamedObject(ai, name) {}
        virtual ~Multiplier() {}

    public:
        virtual float GetValue(Action* action) { return 1.0f; }
    };

}
