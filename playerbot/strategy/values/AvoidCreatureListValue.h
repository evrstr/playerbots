// 策略值头文件：AvoidCreatureListValue（需规避生物 Entry 列表）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：维护需要规避的生物模板 Entry 集合，支持存取序列化
    class AvoidCreatureListValue : public ManualSetValue<std::set<uint32>&>
    {
    public:
        AvoidCreatureListValue(PlayerbotAI* ai, std::string name = "avoid creature list") : ManualSetValue<std::set<uint32>&>(ai, list, name) {}

        // 将规避生物列表序列化为逗号分隔字符串
        virtual std::string Save() override;
        // 从逗号分隔字符串加载规避生物列表
        virtual bool Load(std::string value) override;

    private:
        std::set<uint32> list;
    };
}