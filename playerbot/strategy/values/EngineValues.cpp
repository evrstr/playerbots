// 策略值实现：EngineValues（AI 引擎动作、触发器与策略状态查询）

#include "EngineValues.h"
#include "playerbot/strategy/AiObjectContext.h"
#include "playerbot/PlayerbotAI.h"

using namespace ai;

// 获取限定符对应的 Action 并检查 isPossible()
bool ActionPossibleValue::Calculate()
{
    Action* action = context->GetAction(getQualifier());

    if (!action)
        return false;

    return action->isPossible();
}

// 获取限定符对应的 Action 并检查 isUseful()
bool ActionUsefulValue::Calculate()
{
    Action* action = context->GetAction(getQualifier());

    if (!action)
        return false;

    return action->isUseful();
}

// 获取限定符对应的 Trigger 并同时校验 Check() 与 IsActive()
bool TriggerActiveValue::Calculate()
{
    Trigger* trigger = context->GetTrigger(getQualifier());

    if (!trigger)
        return false;

    if (!trigger->Check() || !trigger->IsActive())
        return false;

    return true;
}

// 解析可选状态前缀（co/de/react）并检查机器人是否启用对应策略
bool HasStrategyValue::Calculate()
{
    std::vector<std::string> tokens = Qualified::getMultiQualifiers(getQualifier(), ",");

    BotState state = BotState::BOT_STATE_NON_COMBAT;

    if (tokens.size() == 2)
    {
        if (tokens[0] == "co")
            state = BotState::BOT_STATE_COMBAT;
        if (tokens[0] == "de")
            state = BotState::BOT_STATE_DEAD;
        if (tokens[0] == "react")
            state = BotState::BOT_STATE_REACTION;
    }

    return ai->HasStrategy(tokens.back(), state);
}

