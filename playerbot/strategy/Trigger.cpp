
#include "playerbot/playerbot.h"
#include "Trigger.h"
#include "Action.h"
#include "Entities/Unit.h"
#include "Value.h"

using namespace ai;

// 检查触发器是否已被外部触发或满足激活条件，并返回对应 Event
Event Trigger::Check()
{
    if (triggered)
    {
        if (owner)
            return Event(getName(), param, owner);
        else
            return Event(getName());
    }

    if (IsActive())
    {
        triggered = true;
        Event event(getName());
        return event;
    }
    Event event;
    return event;
}

// 从上下文获取触发器关联的目标 GUID Value
Value<ObjectGuid>* Trigger::GetTargetValue()
{
    return context->GetValue<ObjectGuid>(GetTargetName());
}

// 获取触发器关联的目标 Unit 指针
Unit* Trigger::GetTarget()
{
    return ai->GetUnit(GetTargetValue()->Get());
}

TriggerNode::~TriggerNode()
{
    NextAction::destroy(handlers);
}

// 合并节点配置的处理动作与触发器自身的默认处理动作
NextAction** TriggerNode::getHandlers()
{
    return NextAction::merge(NextAction::clone(handlers), trigger->getHandlers());
}

// 获取首个处理动作的相关性权重
float TriggerNode::getFirstRelevance()
{
    return handlers[0] ? handlers[0]->getRelevance() : -1;
}
