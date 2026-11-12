
#include "playerbot/playerbot.h"
#include "playerbot/PlayerbotAIConfig.h"

using namespace ai;

PlayerbotAIBase::PlayerbotAIBase() : aiInternalUpdateDelay(0)
{
}

void PlayerbotAIBase::UpdateAIInternal(uint32 elapsed, bool minimal)
{
}

// 主更新入口：扣减更新延迟并在满足条件时驱动 UpdateAIInternal
void PlayerbotAIBase::UpdateAI(uint32 elapsed)
{
    totalPmo.reset();
    totalPmo = sPerformanceMonitor.start(PERF_MON_TOTAL, "PlayerbotAIBase::FullTick");
    
    if (aiInternalUpdateDelay > elapsed)
        aiInternalUpdateDelay -= elapsed;
    else
        aiInternalUpdateDelay = 0;

    if (!CanUpdateAIInternal())
        return;

    UpdateAIInternal(elapsed);
    YieldAIInternalThread();
}

// 设置内部 AI 下次更新延迟时间（毫秒）
void PlayerbotAIBase::SetAIInternalUpdateDelay(const uint32 delay)
{
    if (aiInternalUpdateDelay < delay)
        sLog.outDebug("Setting lesser ai internal update delay %d -> %d", aiInternalUpdateDelay, delay);

    aiInternalUpdateDelay = delay;

    if (aiInternalUpdateDelay > sPlayerbotAIConfig.globalCoolDown)
        sLog.outDebug( "Set ai internal update delay: %d", aiInternalUpdateDelay);
}

void PlayerbotAIBase::IncreaseAIInternalUpdateDelay(uint32 delay)
{
    aiInternalUpdateDelay += delay;

    if (aiInternalUpdateDelay > sPlayerbotAIConfig.globalCoolDown)
        sLog.outDebug( "Increase ai internal update delay: %d", aiInternalUpdateDelay);
}

// 动作执行后让出本轮调度，保证不低于最小反应延迟
void PlayerbotAIBase::YieldAIInternalThread(bool minimal)
{
    if (aiInternalUpdateDelay < sPlayerbotAIConfig.reactDelay)
        aiInternalUpdateDelay = minimal ? sPlayerbotAIConfig.reactDelay * 10 : sPlayerbotAIConfig.reactDelay;
}

// 判断当前 AI 是否处于活跃调度窗口内
bool PlayerbotAIBase::IsActive() const
{
    return (int)aiInternalUpdateDelay < (int)sPlayerbotAIConfig.maxWaitForMove;
}
