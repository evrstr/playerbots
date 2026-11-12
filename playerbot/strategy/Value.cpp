
#include "playerbot/playerbot.h"
#include "Value.h"
#include "playerbot/PerformanceMonitor.h"
#include "playerbot/ChatHelper.h"

using namespace ai;

// 格式化单个 ObjectGuid 位置为可读聊天字符串
std::string ObjectGuidCalculatedValue::Format()
{
    GuidPosition guid = GuidPosition(this->Calculate(), bot);
    return guid ? chat->formatGuidPosition(guid, bot) : "<none>";
}

// 格式化 ObjectGuid 列表为 "{...}" 调试字符串
std::string ObjectGuidListCalculatedValue::Format()
{
    std::ostringstream out; out << "{";
    std::list<ObjectGuid> guids = this->Calculate();
    for (std::list<ObjectGuid>::iterator i = guids.begin(); i != guids.end(); ++i)
    {
        GuidPosition guid = GuidPosition(*i, bot);
        out << chat->formatGuidPosition(guid,bot) << ",";
    }
    out << "}";
    return out.str();
}

// 格式化单个 GuidPosition 坐标与目标信息
std::string GuidPositionCalculatedValue::Format()
{
    std::ostringstream out;
    GuidPosition guidP = this->Calculate();
    return chat->formatGuidPosition(guidP,bot);
}

// 格式化 GuidPosition 列表为 "{...}" 调试字符串
std::string GuidPositionListCalculatedValue::Format()
{
    std::ostringstream out; out << "{";
    std::list<GuidPosition> guids = this->Calculate();
    for (std::list<GuidPosition>::iterator i = guids.begin(); i != guids.end(); ++i)
    {
        GuidPosition guidP = *i;
        out << chat->formatGuidPosition(guidP,bot) << ",";
    }
    out << "}";
    return out.str();
}

// 格式化手动设置的 GuidPosition 状态值
std::string GuidPositionManualSetValue::Format()
{
    return chat->formatGuidPosition(value,bot);
}

// 格式化计算得到的目标单位名称
std::string UnitCalculatedValue::Format()
{
    Unit* unit = ai->GetUnit(Calculate());
    return unit ? unit->GetName() : "<none>";
}

// 格式化手动设置的目标单位名称
std::string UnitManualSetValue::Format()
{
    Unit* unit = ai->GetUnit(Get());
    return unit ? unit->GetName() : "<none>";
}
