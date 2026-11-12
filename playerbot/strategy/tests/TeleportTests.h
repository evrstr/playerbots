/// 测试套件：跨地图召唤与复活（BL-14 ~ BL-25）测试组件头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // TeleportTests - cross-map summon / resurrect coverage (BL-14 .. BL-25) | 跨地图召唤/复活覆盖测试（BL-14 .. BL-25）
    //
    // These drive the same server-side request paths the real callers use | 复现真实调用方的服务端请求路径（集合石/自定义法术/世界增益旅行），
    // (UseMeetingStoneAction / CastCustomSpellAction / WorldBuffTravelActions), without needing an | 无需实际在场的旅店老板、集合石或术士宠物即可脚本化压测跨图/多线程行为。
    // innkeeper, meeting stone or warlock pet in range, so the map/thread behaviour can be
    // exercised from a scripted test.
    // =====================================================

    // Sends SMSG_SUMMON_REQUEST asking the test's spawned bot to come to the acting bot. | 发送召唤请求使生成机器人传送至当前机器人身边
    //   "summon request"                 - expects the request to be sent
    //   "summon request expect rejected" - expects it to be refused (target dead / in combat)
    /// 测试组件：向生成的目标机器人发送召唤请求（SMSG_SUMMON_REQUEST）
    class CommandSummonRequest : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "summon request"; }
    };

    // The dead-target equivalent - sends the resurrect request the caller would send for a corpse. | 针对死亡目标的等价路径：发送尸体复活请求
    /// 测试组件：向生成的死亡目标机器人发送复活请求
    class CommandResurrectRequest : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "resurrect request"; }
    };

    // Kills the test's spawned bot so the dead-target paths can be exercised. Decisive: it never | 击杀生成机器人；直接返回确定结果（非 PENDING）以免阻塞脚本执行
    // returns PENDING, because a PENDING command outside "observe" has no timeout to break out of.
    /// 测试组件：立即击杀生成的测试机器人以验证死亡分支逻辑
    class CommandKillSpawn : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "kill spawn"; }
    };

    // Moves the test's spawned bot to a named location ("move spawn <name>"). Routed through | 将生成机器人移动至命名位置，经由 RunOnOwningThread 保证跨地图线程安全
    // RunOnOwningThread so a cross-map move never touches another map from our own thread.
    /// 测试组件：通过所属地图线程安全移动已生成的测试机器人
    class CommandMoveSpawn : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "move spawn"; }
    };

    // Puts the test's spawned bot into combat ("engage spawn <creatureEntry>") by summoning a | 在生成机器人位置刷怪开战，用于覆盖目标战斗中分支（BL-20, BL-22）
    // creature on top of it and attacking. Needed to force the in-combat branches (BL-20, BL-22).
    /// 测试组件：在生成机器人处刷怪使其进入战斗状态
    class CommandEngageSpawn : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "engage spawn"; }
    };

    // Gives the test's spawned bot the same protection the acting bot already has. The host runs | 为生成机器人附加 GM 隐身保护，防止敌对阵营主城卫兵干扰测试目标
    // with "gm visible off", and Player::SetGMVisible(false) sets GM mode as well as hiding the
    // player. A spawned bot does not get that, and it inherits the host's team while being placed
    // where the host stands - so in a hostile capital the guards engage it. The summon is then
    // either refused (target dead) or silently dropped (HandleSummonResponseOpcode returns early
    // when the target is in combat). Tests that need a live, unharassed target use "hide spawn".
    /// 测试组件：为生成的机器人开启 GM 隐身保护以避免主城卫兵干扰
    class CommandHideSpawn : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "hide spawn"; }
    };

    // =====================================================
    // Monitors - these assert on the *spawned* bot, not on the acting bot. | 以下监听器均针对*生成*的辅助机器人而非主控测试机器人进行断言
    // Every other monitor in the framework looks at the acting bot, which cannot express
    // "the bot I summoned actually arrived / actually got resurrected".
    // =====================================================

    // "spawn on map" -> the first spawned bot is in world on the acting bot's map and instance | 验证第一个生成机器人处于当前机器人的地图和副本中
    /// 测试组件：断言生成的机器人已到达执行机器人的地图与副本
    class MonitorSpawnOnMap : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "spawn on map"; }
    };

    // "spawn alive" -> the first spawned bot is alive (proves a self-resurrect happened) | 验证第一个生成机器人已存活
    /// 测试组件：断言生成的机器人当前处于存活状态
    class MonitorSpawnAlive : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "spawn alive"; }
    };

    // "spawn resurrected <N>" -> the first spawned bot is alive AND the core is still carrying OUR | 验证第一个生成机器人已存活、携带本次复活请求坐标且在其 N 码范围内
    // resurrect request for it AND it is standing within N yards of the acting bot.
    // "spawn alive" alone is not proof: a dead bot's own AI releases spirit and gets raised at a
    // spirit healer, so the bot can be alive without our request ever having been accepted - which
    // silently turns a failed summon into a pass. The resurrect request is the only route that
    // moves the corpse to the caller before reviving it, so the distance check is what actually
    // proves the request was accepted and applied.
    /// 测试组件：断言生成的机器人已接受复活请求并在预设落点附近复活
    class MonitorSpawnResurrected : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "spawn resurrected"; }
    };

    // "spawn dead" -> the first spawned bot is dead. Pair with a time monitor to assert it STAYS | 验证第一个生成机器人仍处于死亡状态（BL-22：召唤不得复活尸体）
    // dead (BL-22: a summon must not resurrect a corpse).
    // Note: a resurrect request remains recorded on the player until it next dies, so "spawn dead"
    // is the only way to assert a corpse was NOT resurrected by us.
    /// 测试组件：断言生成的机器人保持死亡状态（未被错误召唤复活）
    class MonitorSpawnDead : public TestMonitor
    {
    private:
        bool IsConditionMet(const std::string& monitorStr, Player* bot, TestContext& ctx) const override;
        std::string GetName() const override { return "spawn dead"; }
    };
}
