
#include "playerbot/playerbot.h"
#include <stdarg.h>
#include "AiObjectContext.h"
#include "Action.h"
#include "Entities/Unit.h"

using namespace ai;

// 计算以 NULL 结尾的 NextAction 指针数组长度
int NextAction::size(NextAction** actions)
{
    if (!actions)
        return 0;

    int size;
    for (size=0; actions[size]; )
        size++;
    return size;
}

// 深拷贝 NextAction 指针数组
NextAction** NextAction::clone(NextAction** actions)
{
    if (!actions)
        return NULL;

    int iSize = NextAction::size(actions);

    NextAction** res = new NextAction*[iSize + 1];
    for (int i=0; i<iSize; i++)
        res[i] = new NextAction(*actions[i]);
    res[iSize] = NULL;
    return res;
}

// 合并两个 NextAction 数组并释放原数组内存
NextAction** NextAction::merge(NextAction** left, NextAction** right)
{
    int leftSize = NextAction::size(left);
    int rightSize = NextAction::size(right);

    NextAction** res = new NextAction*[leftSize + rightSize + 1];
    for (int i=0; i<leftSize; i++)
        res[i] = new NextAction(*left[i]);
    for (int i=0; i<rightSize; i++)
        res[leftSize + i] = new NextAction(*right[i]);
    res[leftSize + rightSize] = NULL;

    NextAction::destroy(left);
    NextAction::destroy(right);

    return res;
}

//NextAction** NextAction::array(uint8 nil, ...)
// 从可变参数构造以 NULL 结尾的 NextAction 指针数组
NextAction** NextAction::array(uint32 n, ...)
{
    va_list vl;
    va_start(vl, n);

    int iSize = 0;
    NextAction* cur = NULL;
    do
    {
        cur = va_arg(vl, NextAction*);
        iSize++;
    }
    while (cur);

    va_end(vl);

    NextAction** res = new NextAction*[iSize];
    va_start(vl, n);
    for (int i=0; i<iSize; i++)
        res[i] = va_arg(vl, NextAction*);
    va_end(vl);

    return res;
}

// 释放 NextAction 数组中所有对象及数组本身
void NextAction::destroy(NextAction** actions)
{
    if (!actions)
        return;

    for (int i=0; actions[i]; i++)
        delete actions[i];

    delete[] actions;
}

// 从 AI 上下文获取动作默认目标 GUID 的 Value 对象
Value<ObjectGuid>* Action::GetTargetValue()
{
    return context->GetValue<ObjectGuid>(GetTargetName());
}

// 解析动作默认目标 GUID 为 Unit 指针
Unit* Action::GetTarget()
{
    return bot->GetPlayerbotAI()->GetUnit(GetTargetValue()->Get());
}
