/// 奥妮克希亚的巢穴副本触发器定义
#pragma once
#include "DungeonTriggers.h"

namespace ai
{
    /// 触发器：进入奥妮克希亚的巢穴
    class OnyxiasLairEnterDungeonTrigger : public EnterDungeonTrigger
    {
    public:
        OnyxiasLairEnterDungeonTrigger(PlayerbotAI* ai) : EnterDungeonTrigger(ai, "enter onyxias lair", "onyxias lair", 249) {}
    };

    /// 触发器：离开奥妮克希亚的巢穴
    class OnyxiasLairLeaveDungeonTrigger : public LeaveDungeonTrigger
    {
    public:
        OnyxiasLairLeaveDungeonTrigger(PlayerbotAI* ai) : LeaveDungeonTrigger(ai, "leave onyxias lair", "onyxias lair", 249) {}
    };

    /// 触发器：开始奥妮克希亚战斗
    class OnyxiaStartFightTrigger : public StartBossFightTrigger
    {
    public:
        OnyxiaStartFightTrigger(PlayerbotAI* ai) : StartBossFightTrigger(ai, "start onyxia fight", "onyxia", 10184) {}
    };

    /// 触发器：结束奥妮克希亚战斗
    class OnyxiaEndFightTrigger : public EndBossFightTrigger
    {
    public:
        OnyxiaEndFightTrigger(PlayerbotAI* ai) : EndBossFightTrigger(ai, "end onyxia fight", "onyxia", 10184) {}
    };
}