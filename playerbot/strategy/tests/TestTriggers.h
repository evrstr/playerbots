/// 集成测试触发器头文件
#pragma once

#include "playerbot/playerbot.h"
#include "../Trigger.h"

namespace ai
{
    // Trigger that fires when test strategy is active and test hasn't started | 当激活了测试策略且测试尚未启动时触发
    /// 触发器：当非战斗策略中激活了 test 或 test::<name> 时触发 TestAction 启动测试
    class TestReadyTrigger : public Trigger
    {
    public:
        TestReadyTrigger(PlayerbotAI* ai) : Trigger(ai, "test ready") {}
        
        virtual Event Check() override
        {
            // Get test name from strategy - look for "test" prefix (could be "test" or "test:something") | 从非战斗策略列表中提取测试名称（格式为 "test" 或 "test::<名称>"）
            auto strategies = ai->GetStrategies(BotState::BOT_STATE_NON_COMBAT);
            for (const auto& strat : strategies)
            {
                std::string stratStr(strat);
                // Match "test" or "test:*" | 匹配 "test" 或 "test::*"
                if (stratStr == "test" || (stratStr.size() > 6 && stratStr.substr(0, 6) == "test::"))
                {
                    std::string testName = "";
                    if (stratStr.size() > 6)
                        testName = stratStr.substr(6); // Extract name after "test:" | 提取 "test::" 之后的测试脚本名称
                    
                    // Fire the trigger when test strategy is active | 触发测试就绪事件
                    return Event("test ready", testName);
                }
            }
            return Event();
        }
    };
}
