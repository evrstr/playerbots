/// 集成测试 AI 策略实现
#include "playerbot/playerbot.h"
#include "TestStrategy.h"
#include "TestAction.h"
#include "TestTriggers.h"

using namespace ai;

/// 初始化非战斗触发器：绑定 test ready 触发器至高优先级 test 动作
void TestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "test ready",
        NextAction::array(0, new NextAction("test", 100.0f), NULL)));
}

/// 策略被移除时重置 TestAction 测试上下文
void TestStrategy::OnStrategyRemoved(BotState state)
{
    AiObjectContext* context = ai->GetAiObjectContext();
    Action* action = context->GetAction("test");

    if (action)
    {
        action->Reset();
    };
}
