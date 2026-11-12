// 德鲁伊 - 动作实现文件 (DruidActions.cpp)：定义德鲁伊专用技能施放与战斗动作

#include "playerbot/playerbot.h"
#include "DruidActions.h"

using namespace ai;

// 执行动作逻辑 (CastCasterFormAction)
bool CastCasterFormAction::Execute(Event& event)
{
    ai->RemoveShapeshift();
    return true;
}
