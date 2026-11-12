/// 死亡状态恢复（释放灵魂/跑尸/复活）策略实现

#include "playerbot/playerbot.h"
#include "playerbot/strategy/Strategy.h"
#include "playerbot/strategy/values/DeadValues.h"
#include "DeadStrategy.h"

using namespace ai;

/// 初始化死亡状态触发器：处理自动释放、灵魂医者、跑尸、接受复活及卡死重置
void DeadStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PassTroughStrategy::InitDeadTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("auto release", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "val::gt32::{death count," + std::to_string(DeadValueConstants::DEATH_COUNT_BEFORE_EVAC) + "}",
        NextAction::array(0, new NextAction("repop", relevance + 4.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("self resurrect", relevance + 3.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "val::should spirit healer",
        NextAction::array(0, new NextAction("spirit healer", relevance + 2.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "dead",
       NextAction::array(0, new NextAction("find corpse", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "corpse near",
        NextAction::array(0, new NextAction("revive from corpse", relevance-1.0f), NULL)));

    // The bot's own recovery (auto release / spirit healer / repop, relevance 100-104) must not win | 接受他人复活请求的优先级必须高于机器人自身的自动释放/灵魂医者复活，
    // the tick over an offered resurrection: the engine runs one action per tick, and a request that | 防止引擎每帧只执行最高优先动作导致复活请求一直得不到响应。
    // keeps losing is never answered.
    triggers.push_back(new TriggerNode(
        "resurrect request",
        NextAction::array(0, new NextAction("accept resurrect", relevance + 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "falling far",
        NextAction::array(0, new NextAction("repop", relevance+1), NULL)));

    triggers.push_back(new TriggerNode(
        "move long stuck",
        NextAction::array(0, new NextAction("repop", relevance+1), NULL)));
}
