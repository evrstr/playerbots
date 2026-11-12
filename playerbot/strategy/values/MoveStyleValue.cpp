// 策略值实现：MoveStyleValue（移动风格标志位查询）

#include "playerbot/playerbot.h"
#include "MoveStyleValue.h"
#include "playerbot/strategy/values/ItemUsageValue.h"

using namespace ai;

// 检查当前 move style 配置字符串中是否包含指定子策略关键字
bool MoveStyleValue::HasValue(PlayerbotAI* ai, const std::string& value)
{
    std::string styles = ai->GetAiObjectContext()->GetValue<std::string>("move style")->Get();
    return styles.find(value) != std::string::npos;
}