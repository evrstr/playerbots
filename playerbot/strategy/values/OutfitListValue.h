// 策略值头文件：OutfitListValue（配装方案名称列表与抗性顺序配置）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    typedef std::list<std::string> Outfit;
    // 手动设置值：保存机器人自定义套装配置字符串列表，支持 ^ 分隔存取
    class OutfitListValue : public ManualSetValue<Outfit&>
    {
    public:
        OutfitListValue(PlayerbotAI* ai, std::string name = "outfit list") : ManualSetValue<Outfit&>(ai, list, name) {}

        virtual std::string Save() override;
        virtual bool Load(std::string value) override;

    private:
        Outfit list;
    };

    // 手动设置值：保存抗性装备穿戴优先级顺序配置字符串
    class ResistOrderValue : public ManualSetValue<std::string>
    {
    public:
        ResistOrderValue(PlayerbotAI* ai, std::string name = "resist order") : ManualSetValue<std::string>(ai, "", name) {}

        virtual std::string Save() override { return value; }
        virtual bool Load(std::string text) override { value = text; return true; }
    };
}
