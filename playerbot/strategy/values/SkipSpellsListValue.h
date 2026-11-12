// 策略值头文件：SkipSpellsListValue（屏蔽施放的法术 ID 列表）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：保存机器人禁止自动施放的法术 ID 集合，支持序列化存档与加载
    class SkipSpellsListValue : public ManualSetValue<std::set<uint32>&>
    {
    public:
        SkipSpellsListValue(PlayerbotAI* ai, std::string name = "skip spells list") : ManualSetValue<std::set<uint32>&>(ai, list, name) {}

        virtual std::string Save() override;
        virtual bool Load(std::string value) override;

    private:
        std::set<uint32> list;
    };
}
