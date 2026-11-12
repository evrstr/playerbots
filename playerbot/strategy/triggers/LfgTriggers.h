/// 地下城查找器（LFG）触发器定义
#pragma once

#include "playerbot/strategy/Trigger.h"

namespace ai
{
/// 触发器：存在激活状态的 LFG 副本排队确认弹窗
class LfgProposalActiveTrigger : public Trigger
{
public:
    LfgProposalActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "lfg proposal active", 5) {}

    virtual bool IsActive() override;
};

/// 触发器：跟随主人处于未知副本中
class UnknownDungeonTrigger : public Trigger
{
public:
    UnknownDungeonTrigger(PlayerbotAI* ai) : Trigger(ai, "unknown dungeon", 20) {}

    virtual bool IsActive() override;
};
}
