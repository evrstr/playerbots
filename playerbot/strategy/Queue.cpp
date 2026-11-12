
#include "playerbot/playerbot.h"
#include "Action.h"
#include "Queue.h"

#include "playerbot/PlayerbotAIConfig.h"
using namespace ai;


// 推入动作条目：若同名动作已存在则保留较高权重并释放新传入的重复条目
void Queue::Push(ActionBasket *action)
{
    if (action)
    {
        for (std::list<ActionBasket*>::iterator iter = actions.begin(); iter != actions.end(); iter++)
        {
            ActionBasket* basket = *iter;
            if (action->getAction()->getName() == basket->getAction()->getName())
            {
                if (basket->getRelevance() < action->getRelevance())
                {
                    basket->setRelevance(action->getRelevance());
                    basket->setEvent(action->getEvent());
                }
                ActionNode *actionNode = action->getAction();
                if (actionNode)
                    delete actionNode;
                delete action;
                return;
            }
        }
        actions.push_back(action);
    }
}

// 弹出指定条目或当前权重最高的动作节点并释放 ActionBasket
ActionNode* Queue::Pop(ActionBasket* action)
{
    ActionBasket* selection = action;
    if (selection == nullptr)
    {
        float max = -400;
        for (std::list<ActionBasket*>::iterator iter = actions.begin(); iter != actions.end(); iter++)
        {
            ActionBasket* basket = *iter;
            if (basket->getRelevance() > max)
            {
                max = basket->getRelevance();
                selection = basket;
            }
        }
    }

    if (selection != nullptr)
    {
        ActionNode* action = selection->getAction();
        actions.remove(selection);
        delete selection;
        return action;
    }

    return nullptr;
}

// 查看当前队列中相关性权重最高的动作条目（不移除）
ActionBasket* Queue::Peek()
{
    float max = -400;
    ActionBasket* selection = NULL;
    for (std::list<ActionBasket*>::iterator iter = actions.begin(); iter != actions.end(); iter++)
    {
        ActionBasket* basket = *iter;
        if (basket->getRelevance() > max)
        {
            max = basket->getRelevance();
            selection = basket;
        }
    }
    return selection;
}

// 返回当前队列中的动作数量
int Queue::Size()
{
    return actions.size();
}

// 清理超过生存时限的过期动作条目
void Queue::RemoveExpired()
{
    std::list<ActionBasket*> expired;
    for (std::list<ActionBasket*>::iterator iter = actions.begin(); iter != actions.end(); iter++)
    {
        ActionBasket* basket = *iter;
        if (sPlayerbotAIConfig.expireActionTime && basket->isExpired(sPlayerbotAIConfig.expireActionTime / 1000))
            expired.push_back(basket);
    }

    for (std::list<ActionBasket*>::iterator iter = expired.begin(); iter != expired.end(); iter++)
    {
        ActionBasket* basket = *iter;
        actions.remove(basket);
        ActionNode* action = basket->getAction();
        if (action)
        {
            sLog.outDebug("Action %s is expired", action->getName().c_str());
            delete action;
        }
        delete basket;
    }
}
