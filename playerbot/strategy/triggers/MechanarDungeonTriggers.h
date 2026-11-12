/// 能源舰（The Mechanar）副本触发器定义
#pragma once
#include "DungeonTriggers.h"
#include "GenericTriggers.h"

namespace ai
{
    /// 触发器：进入能源舰副本
    class MechanarEnterDungeonTrigger : public EnterDungeonTrigger
    {
    public:
        MechanarEnterDungeonTrigger(PlayerbotAI* ai) : EnterDungeonTrigger(ai, "enter mechanar", "mechanar", 554) {}
    };

    /// 触发器：离开能源舰副本
    class MechanarLeaveDungeonTrigger : public LeaveDungeonTrigger
    {
    public:
        MechanarLeaveDungeonTrigger(PlayerbotAI* ai) : LeaveDungeonTrigger(ai, "leave mechanar", "mechanar", 554) {}
    };

    /// 触发器：开始灵术师塞佩丝蕾战斗
    class NethermancerSepethreaStartFightTrigger : public StartBossFightTrigger
    {
    public:
        NethermancerSepethreaStartFightTrigger(PlayerbotAI* ai) : StartBossFightTrigger(ai, "start nethermancer sepethrea fight", "nethermancer sepethrea", 19221) {}
    };

    /// 触发器：结束灵术师塞佩丝蕾战斗
    class NethermancerSepethreaEndFightTrigger : public EndBossFightTrigger
    {
    public:
        NethermancerSepethreaEndFightTrigger(PlayerbotAI* ai) : EndBossFightTrigger(ai, "end nethermancer sepethrea fight", "nethermancer sepethrea", 19221) {}
    };

    /// 触发器：狂怒烈焰（20481）距离过近需躲避
    class RagingFlamesTooCloseTrigger : public CloseToCreatureTrigger
    {
    public:
        RagingFlamesTooCloseTrigger(PlayerbotAI* ai) : CloseToCreatureTrigger(ai, "raging flames too close", 20481, 12.0f, true) {}
    };
}