/// 测试命令：清理测试小队与生成机器人实现
#include "playerbot/playerbot.h"
#include "CleanupParty.h"

using namespace ai;

// =====================================================
// CleanupParty implementation | CleanupParty 实现
// =====================================================
/// 执行清理：下线所有在 TestContext 中登记的生成机器人并清空列表
TestResult CleanupParty::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    // Default cleanup: despawn all spawned bots | 默认清理行为：销毁所有已生成的测试机器人
    for (auto& guid : ctx.spawnedBots)
    {
        if (guid.IsPlayer())
        {
            if (ai->GetHolder())
                ai->GetHolder()->DeleteBot(guid, false);
        }
        else if (Creature* creature = ai->GetCreature(guid))
        {
            creature->ForcedDespawn();
        }
    }
    ctx.spawnedBots.clear();
    ctx.observing = false;
    return TestResult::PASS;
}