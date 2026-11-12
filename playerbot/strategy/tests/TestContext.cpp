/// 测试执行上下文（TestContext）状态管理实现
#include "TestContext.h"
#include "playerbot/PlayerbotMgr.h"

using namespace ai;

/// 重置上下文全部运行状态、计数器、焦点记录及清理队列
void TestContext::Reset()
{
    script.clear();
    pc = 0;
    observing = false;
    testStartTime = 0;
    monitorTime = 0;
    waitTime = 0;
    monitors.clear();
    deferredCleanups.clear();
    cleanupPc = 0;
    cleanupPrepared = false;
    combatSeen = false;
    whoResponded = false;
    result = TestResult::PENDING;
    resultMessage.clear();
    testName.clear();
    testStartPosition = WorldPosition();
    destinationPosition = GuidPosition();
    partyXpStart = 0;
    partyXpCaptured = false;
    observedDeadMobs.clear();
    resurrectMapId = 0;
    resurrectX = resurrectY = resurrectZ = 0.0f;
    hasResurrectRequest = false;
    groupMembersSeenOnMap.clear();

    for (ObjectGuid const& guid : spawnedBots)
    {
        if (guid && guid.IsPlayer())
        {
            sRandomPlayerbotMgr.DeleteBot(guid, true);
        }
    }
    spawnedBots.clear();
    deliveredGroupMembers.clear();
    groupOnMapExpected = 0;
    lootStackSeen = false;
    actionSpamArmed = false;
}

/// 线程安全记录已成功传送到位的队友 GUID
void TestContext::RecordDeliveredGroupMember(ObjectGuid guid)
{
    std::lock_guard<std::mutex> lock(groupDeliveryMutex);
    deliveredGroupMembers.insert(guid);
}

/// 线程安全获取已成功传送到位的队友 GUID 集合
std::set<ObjectGuid> TestContext::GetDeliveredGroupMembers()
{
    std::lock_guard<std::mutex> lock(groupDeliveryMutex);
    return deliveredGroupMembers;
}