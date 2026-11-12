#pragma once

class Player;
class PlayerbotMgr;
class ChatHandler;
class PerformanceMonitorOperation;

#include <memory>

/// 机器人 AI 与管理器共用基类，提供更新延迟控制与主 Tick 调度框架
class PlayerbotAIBase
{
public:
    PlayerbotAIBase();

public:
    bool IsActive() const;
    virtual void UpdateAI(uint32 elapsed);
    
    uint32 GetAIInternalUpdateDelay() const { return aiInternalUpdateDelay; }

protected:
    virtual void UpdateAIInternal(uint32 elapsed, bool minimal = false);
    bool CanUpdateAIInternal() const { return aiInternalUpdateDelay < 100U; }
    void SetAIInternalUpdateDelay(const uint32 delay);
    void ResetAIInternalUpdateDelay() { aiInternalUpdateDelay = 0U; }
    void IncreaseAIInternalUpdateDelay(uint32 delay);
    void YieldAIInternalThread(bool minimal = false);
    
protected:
    uint32 aiInternalUpdateDelay;

    std::unique_ptr<PerformanceMonitorOperation> totalPmo;
};
