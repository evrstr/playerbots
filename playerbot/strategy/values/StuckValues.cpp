// 策略值实现：StuckValues（状态停滞时间与位置变化距离计算）

#include "playerbot/playerbot.h"
#include "StuckValues.h"

using namespace ai;

// 查询指定 AI 值的 LastChangeDelay()
uint32 TimeSinceLastChangeValue::Calculate()
{
    UntypedValue* val = context->GetUntypedValue(qualifier);

    if (!val)
        return 0;

    return val->LastChangeDelay();
}

// 遍历 current position 历史轨迹记录，返回超出时间窗口后的最大位移距离
uint32 DistanceMovedSinceValue::Calculate()
{
    uint32 minTimePassed = stoi(getQualifier());

    LogCalculatedValue<WorldPosition>* posVal = dynamic_cast<LogCalculatedValue<WorldPosition>*>(context->GetUntypedValue("current position"));

    bool hasEnoughData = false;
    uint32 maxSqDistance = 0.0;

    for (auto tPos : posVal->ValueLog())
    {
        uint32 timePassed = time(0) - tPos.second;

        if (timePassed > minTimePassed)
            hasEnoughData = true;

        uint32 distance = tPos.first.sqDistance(bot);

        if (distance > maxSqDistance)
            maxSqDistance = distance;
    }

    if (!hasEnoughData)
        return 0;

    return sqrt(maxSqDistance);
}
