
#include "playerbot/playerbot.h"

#include "ReactionEngine.h"
#include <iomanip>

using namespace ai;

// 绑定反应动作并初始化持续时间
void Reaction::SetAction(Action* inAction)
{
    if (inAction)
    {
        SetDuration(inAction->GetDuration());
        action = inAction;
    }
}

// 扣减反应剩余持续时间，结束时返回 true
bool Reaction::Update(uint32 elapsed)
{
    // Update remaining duration
    duration = duration > elapsed ? duration - elapsed : 0;

    // TO DO: Check if the reaction got interrupted (stun, knockback, ...)
    // ...

    // Return true when the reaction has finished
    return !IsActive();
}

// 构造反应引擎实例
ReactionEngine::ReactionEngine(PlayerbotAI* ai, AiObjectContext* factory, BotState engineState) 
: Engine(ai, factory, engineState)
, aiReactionUpdateDelay(0U)
{
    
}

// 当没有进行中的反应时，轮询触发器与队列选出最佳可用反应动作
bool ReactionEngine::FindReaction(bool isStunned)
{
    // Don't find a new reaction if the previous reaction is still running
    if(!IsReacting())
    {
        aiObjectContext->Update();

        ai->HandleCommands();

        // This will populate the queue to be processed with the reactions that can be triggered
        ProcessTriggers(false);

        ActionBasket* reactionItem = NULL;

        // Look for the best reaction (if any available)
        int iterations = 0;
        int iterationsPerTick = queue.Size() *  sPlayerbotAIConfig.iterationsPerTick;
        do 
        {
            // Get the best reaction in the queue (sorted by relevance)
            reactionItem = queue.Peek();
            if (reactionItem)
            {
                const bool skipReactionPrerequisites = reactionItem->isSkipPrerequisites();
                float reactionRelevance = reactionItem->getRelevance();
                const Event& reactionEvent = reactionItem->getEvent();

                // Extract the reaction from the queue (removed)
                ActionNode* reactionNode = queue.Pop(reactionItem);

                // Pairs with Engine::ProcessTriggers(): a reaction that consumed an external packet
                // event must hand its trigger back, or the armed trigger would suppress every later
                // packet of the same opcode (there is no other release path on this engine).
                ReleaseExternalEvent(reactionEvent.getSource());
                if (reactionNode)
                {
                    Action* reaction = InitializeAction(reactionNode);
                    if (reaction)
                    {
                        // Update the reaction relevance
                        reaction->setRelevance(reactionRelevance);

                        // Check if the reaction is useful
                        if (reaction->isUseful() && (!isStunned || reaction->isUsefulWhenStunned()))
                        {
                            // Process the multipliers
                            for (std::list<Multiplier*>::iterator i = multipliers.begin(); i != multipliers.end(); i++)
                            {
                                reactionRelevance *= (*i)->GetValue(reaction);
                                reaction->setRelevance(reactionRelevance);
                                if (reactionRelevance <= 0.0f)
                                {
                                    // Multiplier made reaction useless
                                    break;
                                }
                            }

                            // Process prerequisites
                            if (!skipReactionPrerequisites)
                            {
                                // Add the prerequisites to the queue with a slight higher relevance than this action to be processed in the next iteration
                                if (MultiplyAndPush(reactionNode->getPrerequisites(), reactionRelevance + 0.02, false, reactionEvent, "prereq"))
                                {
                                    // Add this reaction to the queue again to be processed after the prerequisite
                                    PushAgain(reactionNode, reactionRelevance + 0.01, reactionEvent);
                                    continue;
                                }
                            }

                            // Check if the reaction is possible
                            if ((reactionRelevance > 0.0f) && reaction->isPossible())
                            {
                                // Reaction found
                                incomingReaction.SetAction(reaction);
                                incomingReaction.SetEvent(reactionEvent);
                                delete reactionNode;
                                break;
                            }
                            else
                            {
                                // Add the alternative reactions to the queue
                                MultiplyAndPush(reactionNode->getAlternatives(), reactionRelevance + 0.03, false, reactionEvent, "alt");
                            }
                        }
                    }

                    // Delete the reaction node
                    delete reactionNode;
                }
            }
        }
        while (reactionItem && ++iterations <= iterationsPerTick);

        // Remove the expired reactions
        queue.RemoveExpired();

        return incomingReaction.IsValid();
    }

    return false;
}

// 执行已选定的待触发反应动作并转入 ongoingReaction
bool ReactionEngine::StartReaction()
{
    bool reactionExecuted = false;
    if (incomingReaction.IsValid())
    {
        // Execute the incoming reaction
        reactionExecuted = ListenAndExecute(incomingReaction.GetAction(), incomingReaction.GetEvent());
        if (reactionExecuted)
        {
            // Move the incoming reaction to the ongoing reaction
            ongoingReaction = incomingReaction;
        }

        // Remove the incoming reaction
        incomingReaction.Reset();
    }

    return reactionExecuted;
}

// 结束当前进行中的反应并重置延迟
void ReactionEngine::StopReaction()
{
    ongoingReaction.Reset();
    aiReactionUpdateDelay = 0U;

    // TO DO: Interrupt if the action is still running
    // ...
}

// 反应引擎周期更新：推进当前反应计时、启动待执行反应或搜索新反应
bool ReactionEngine::Update(uint32 elapsed, bool minimal, bool isStunned, bool& reactionFound)
{
    aiReactionUpdateDelay = aiReactionUpdateDelay > elapsed ? aiReactionUpdateDelay - elapsed : 0U;

    reactionFound = false;
    bool reactionFinished = false;

    // Can update reaction?
    if (CanUpdateAIReaction())
    {
        if (IsReacting())
        {
            if (ongoingReaction.Update(elapsed))
            {
                StopReaction();
                reactionFinished = true;
            }
        }
        else
            reactionFinished = true;

        if(reactionFinished)
        {
            if (HasIncomingReaction())
            {
                // Start the incoming reaction
                StartReaction();
            }
            else
            {
                // Look for an available reaction
                if (FindReaction(isStunned))
                {
                    reactionFound = true;
                }
            }
        }

        // Only add a reaction update delay if no reaction is pending or currently running
        if (!HasIncomingReaction() && !IsReacting())
        {
            if (aiReactionUpdateDelay < sPlayerbotAIConfig.reactDelay)
                aiReactionUpdateDelay = minimal ? sPlayerbotAIConfig.reactDelay * 10 : sPlayerbotAIConfig.reactDelay;
        }
    }

    // Return true if a reaction is pending or currently running
    return HasIncomingReaction() || IsReacting();
}

// 执行反应动作并向监听器及调试者汇报持续时间
bool ReactionEngine::ListenAndExecute(Action* action, Event& event)
{
    bool actionExecuted = false;
    if (actionExecutionListeners.Before(action, event))
    {
        actionExecuted = actionExecutionListeners.AllowExecution(action, event) ? action->Execute(event) : true;
        if (actionExecuted)
        {
            if (!incomingReaction.GetAction()) //Prevent reset during action.
                incomingReaction.SetAction(action);
            ai->SetActionDuration(action);
        }
    }

    if (ai->HasStrategy("debug", BotState::BOT_STATE_NON_COMBAT))
    {
        std::ostringstream out;
        out << "do: ";
        out << action->getName();
        if (actionExecuted)
            out << " 1 (";
        else
            out << " 0 (";

        out << std::fixed << std::setprecision(2);
        out << action->getRelevance() << ")";

        if (!event.getSource().empty())
            out << " [" << event.getSource() << "]";

        out << " [reaction]";

        if(actionExecuted)
            out << " (duration: " << ((float)incomingReaction.GetDuration() / static_cast<float>(IN_MILLISECONDS)) << "s)";

        ai->TellPlayerNoFacing(ai->GetMaster(), out);
    }

    actionExecuted = actionExecutionListeners.OverrideResult(action, actionExecuted, event);
    actionExecutionListeners.After(action, actionExecuted, event);
    return actionExecuted;
}

// 初始化动作并标记为反应模式
ai::Action* ReactionEngine::InitializeAction(ActionNode* actionNode)
{
    Action* action = actionNode->getAction();
    if (!action)
    {
        action = aiObjectContext->GetAction(actionNode->getName());
        actionNode->setAction(action);
    }

    if (action)
    {
        action->SetReaction(true);
    }

    return action;
}

// 同步更新当前或待启动反应的持续时间
void ReactionEngine::SetReactionDuration(const Action* action)
{
    if (action && (IsReacting() || HasIncomingReaction()))
    {
        if (ongoingReaction.GetAction() == action)
        {
            ongoingReaction.SetDuration(action->GetDuration());
        }
        else if (incomingReaction.GetAction() == action)
        {
            incomingReaction.SetDuration(action->GetDuration());
        }
    }
}

// 重置进行中与待启动的反应状态
void ReactionEngine::Reset()
{
    ongoingReaction.Reset();
    incomingReaction.Reset();
    aiReactionUpdateDelay = 0U;
}

// 检查冷却延迟、在世界状态及非传送状态以判断是否可更新反应
bool ReactionEngine::CanUpdateAIReaction() const
{
    Player* bot = ai->GetBot();
    return (aiReactionUpdateDelay < 100U) && 
            bot->IsInWorld() &&
           !bot->IsBeingTeleported();
}

// 获取当前活跃（进行中或即将执行）的反应对象指针
const Reaction* ReactionEngine::GetReaction() const
{
    const Reaction* reaction = nullptr;
    if (ongoingReaction.IsValid())
    {
        reaction = &ongoingReaction;
    }
    else if (incomingReaction.IsValid())
    {
        reaction = &incomingReaction;
    }

    return reaction;
}
