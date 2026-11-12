#include "ActionBasket.h"

#pragma once
namespace ai
{
/// 动作优先级队列，按相关性权重选取最佳待执行动作并去重、清理过期条目
class Queue
{
public:
    Queue(void) {}
public:
    ~Queue(void) {}
public:
    void Push(ActionBasket *action);
    ActionNode* Pop(ActionBasket* action = nullptr);
    ActionBasket* Peek();
    int Size();
    void RemoveExpired();
private:
    std::list<ActionBasket*> actions;
};
}
