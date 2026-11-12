/// 测试执行上下文（TestContext）状态数据结构头文件
#pragma once

#include <vector>
#include <string>
#include <set>
#include <cstdint>
#include <mutex>
#include "Globals/ObjectMgr.h"
#include "playerbot/GuidPosition.h"
#include "playerbot/WorldPosition.h"

class ObjectGuid;

namespace ai
{
    /// 单条测试命令或测试运行的最终判定结果枚举
    enum class TestResult
    {
        PENDING,
        IMPOSSIBLE,
        PASS,
        FAIL,
        ABORT
    };

    /// 保存单次集成测试运行期的全部脚本进度、监听器、生成实体及统计状态
    struct TestContext
    {
        std::vector<std::string> script;        
        int pc;                                 
        bool observing;                         
        uint32 testStartTime;                   
        uint32 monitorTime;
        uint32 waitTime;                        
        uint32 undergroundCount;

        // Consecutive ticks the "can not reach nodes" monitor saw no pathable node. Right after | 连续检测到不可达节点的 tick 计数（传送后给予网格/寻路加载宽限期）
        // a teleport the target grid/mmaps may not be loaded yet, so the monitor only fails after
        // a grace period instead of on the first tick (same pattern as undergroundCount).
        uint32 cannotReachCount;
        bool combatSeen;
        uint32 focusMobEntry;                   
        ObjectGuid focusMobGuid;                
        bool focusMobKilled;                    
        bool focusMobPassive;                   
        std::vector<ObjectGuid> spawnedBots;    
        std::vector<std::string> monitors;      
        std::vector<std::string> deferredCleanups;
        size_t cleanupPc;
        bool cleanupPrepared;
        bool whoResponded;
        TestResult result;                       
        std::string resultMessage;
        std::string testName;                    
        WorldPosition testStartPosition;
        GuidPosition destinationPosition;

        // Party XP total (all group members) captured when the test starts. The "party xp" monitor | 测试开始时捕获的小队总经验基线，用于断言队伍清理杂兵进度
        // measures the gain against this baseline: kill/loot-driven corpses near the host are too
        // transient (bots loot instantly) for sparse-start instances, so "party cleared trash" is
        // asserted on accumulated party XP instead.
        uint32 partyXpStart = 0;
        bool partyXpCaptured = false;

        // Every dead creature GUID the "dead mobs" monitor has ever observed this run. Counted | 观测期内累计记录的所有死亡怪物 GUID（防止尸体被秒拾取后消失导致漏计）
        // cumulatively per unique GUID because corpses despawn on loot - a "6 corpses at once"
        // snapshot rarely happens in sparse-start instances even under heavy killing.
        std::set<ObjectGuid> observedDeadMobs;

        // Where the most recent resurrect request told its target to land, and on which map. Monitors | 最近一次复活请求指定的目标地图与落点坐标，作为复活距离断言基准
        // must measure against this rather than the acting bot: the caller is a random bot that can
        // random-teleport thousands of yards (or into a battleground) while the observe window runs,
        // which made a proximity check against it report a false failure.
        uint32 resurrectMapId = 0;
        float resurrectX = 0.0f;
        float resurrectY = 0.0f;
        float resurrectZ = 0.0f;
        bool hasResurrectRequest = false;

        // Latched by the "group on map" monitor: each member is recorded the first time it is observed on | 锁存已出现在当前地图上的队友 GUID（兼容随机传送/漫游机器人异步抵达）
        // the bot's map. Per member rather than a single snapshot, because group members are roamed random
        // bots and are rarely all settled on the same map on the same tick - the monitor asserts that the
        // delivery happened, not that it held.
        std::set<ObjectGuid> groupMembersSeenOnMap;

        // BL-44: thread-safe record of the members the "teleport group" helper ACTUALLY delivered | BL-44：线程安全记录通过 teleport group 实际投递到位的成员列表
        // (moved=true inside the RunOnOwningThread callback, which runs on the world thread). Written
        // from the callback, read by the "group on map" monitor on the bot's update thread - hence the
        // mutex. Non-empty switches the monitor to causal mode: only delivered members count toward the
        // pass, so roaming a member to the host's map by coincidence can no longer satisfy it.
        std::mutex groupDeliveryMutex;
        std::set<ObjectGuid> deliveredGroupMembers;
        void RecordDeliveredGroupMember(ObjectGuid guid);
        std::set<ObjectGuid> GetDeliveredGroupMembers();

        bool lootStackSeen = false;
        bool actionSpamArmed = false;

        // BL-44: snapshot of the expected group-member count, taken at the monitor's first tick. The | BL-44：在监听首帧快照的期望小队人数，防止中途退队降低断言标准
        // live group can shrink mid-window (a member leaves), which would silently lower the bar; the
        // snapshot keeps the original assertion strength for the whole observe window.
        uint32 groupOnMapExpected = 0;

        bool debug = false; // enable extra logging for debugging | 启用额外调试日志输出

        TestContext() : pc(0), observing(false), testStartTime(0), monitorTime(0), waitTime(0), undergroundCount(0), cannotReachCount(0), combatSeen(false), focusMobEntry(0), focusMobKilled(false), focusMobPassive(false), cleanupPc(0), cleanupPrepared(false), whoResponded(false), result(TestResult::PENDING) {}

        void Reset();
    };
}
