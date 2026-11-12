// 策略值头文件：AlwaysLootListValue（强制拾取物品列表）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：保存机器人始终拾取的物品 ID 集合，支持序列化存档与读取
    class AlwaysLootListValue : public ManualSetValue<std::set<uint32>&>
    {
    public:
        AlwaysLootListValue(PlayerbotAI* ai, std::string name = "always loot list") : ManualSetValue<std::set<uint32>&>(ai, list, name) {}

        // 将物品 ID 集合序列化为逗号分隔的字符串
        virtual std::string Save() override;
        // 从逗号分隔的字符串反序列化加载物品 ID 集合
        virtual bool Load(std::string value) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "always loot list"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "loot"; }
        virtual std::string GetHelpDescription() { return "This value contains a list of item ids that should always be looted."; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 

    private:
        std::set<uint32> list;
    };
}
