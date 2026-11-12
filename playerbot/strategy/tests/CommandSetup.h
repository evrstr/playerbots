/// 测试命令：测试环境初始化与场景布置命令头文件
#pragma once

#include "TestComponent.h"

namespace ai
{
    // =====================================================
    // CommandSetup - setup commands (teleport, gm, item, etc.) | 环境布置命令（传送、GM、物品等）
    // =====================================================
    /// 测试组件：将机器人传送至指定命名地点或坐标
    class CommandSetupTeleport : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "teleport"; }
    };

    /// 测试组件：开关测试机器人的 GM 模式或可见性
    class CommandSetupGM : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "gm"; }
    };

    /// 测试组件：向机器人背包发放指定物品
    class CommandSetupGiveItem : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "give"; }
    };

    /// 测试组件：为机器人穿戴指定装备或预设套装
    class CommandSetupEquipItem : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "equip"; }
    };

    /// 测试组件：清理测试点周围的无关敌对怪物
    class CommandSetupClearMobs : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "clear"; }
    };

    /// 测试组件：设定机器人旅行或移动的目标位置
    class CommandSetupSetDestination : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "set destination"; }
    };

    // BL-47(a) follow-up (five_signets): verify that the creature behind a named location is actually | 验证命名地点背后的生物是否在机器人附近存活：
    // ALIVE in the world near the bot. A dead/despawned giver turned into a 900 s accept-timeout FAIL; | 避免因任务 NPC 死亡导致测试空等 900 秒超时 FAIL，
    // this turns the same condition into an honest ABORT at setup. Usage: | 改为在初始化阶段直接诚实中止（ABORT）。用法：
    //   "require creature alive <location> [yd]"  (yd defaults to 300) | "require creature alive <location> [yd]"（yd 默认 300 码）
    /// 测试组件：校验指定命名地点对应的世界生物当前是否存活（否则在初始化阶段直接 ABORT）
    class CommandRequireCreatureAlive : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "require creature alive"; }
    };

    // BL-46: aim the bot's rpg machinery at a specific world object (e.g. quest_<id>_giver). | 将机器人的 RPG 机制指向特定世界对象（如 quest_<id>_giver），
    // The rest of the chain (arrival -> rpg trigger -> accept) runs normally afterwards. | 随后正常执行到达 -> RPG 触发器 -> 接任务的完整链路。
    /// 测试组件：手动设定机器人的 RPG 交互目标对象
    class CommandSetupRpgTarget : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "set rpg target"; }
    };

    /// 测试组件：将整个测试小队传送至指定位置
    class CommandSetupTeleportGroup : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "teleport group"; }
    };

    /// 测试组件：指示机器人对指定目标执行拉怪操作
    class CommandSetupPull : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "pull"; }
    };

    /// 测试组件：在测试位置生成指定 Entry 的生物
    class CommandSpawnMob : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "spawn mob"; }
    };

    /// 测试组件：设定测试脚本中的焦点怪物并开始追踪
    class CommandFollowFocus : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "follow focus"; }
    };

    /// 测试组件：直接击杀当前焦点怪物
    class CommandKillFocus : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "kill focus"; }
    };

    /// 测试组件：等待当前焦点怪物死亡变为尸体状态
    class CommandAwaitFocusCorpse : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "await focus corpse"; }
    };

    /// 测试组件：在脚本中直接修改指定 AI Value 状态值
    class CommandSetValue : public TestCommand
    {
    public:
        TestResult Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message) override;
    protected:
        std::string GetName() const override { return "set value"; }
    };
}