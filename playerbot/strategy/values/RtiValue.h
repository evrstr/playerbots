// 策略值头文件：RtiValue（团队目标标记 RTI、控场标记与战斗指令目标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 手动设置值：保存机器人主要集火的团队目标标记名称（默认 skull 骷髅）
    class RtiValue : public ManualSetValue<std::string>
    {
    public:
        RtiValue(PlayerbotAI* ai);
        virtual std::string Save() override { return value; }
        virtual bool Load(std::string text) override { value = text; return true; }
    };

    // 手动设置值：保存机器人负责控场的团队目标标记名称（默认 none）
    class RtiCcValue : public ManualSetValue<std::string>
    {
    public:
        RtiCcValue(PlayerbotAI* ai);

        virtual std::string Save() override { return value; }
        virtual bool Load(std::string text) override { value = text; return true; }
    };

    // 手动设置值：保存通过战斗指令指定的攻击目标策略配置，支持按玩家名或 GUID 查找目标
    class CombatOrderTargetValue : public ManualSetValue<std::string>
    {
    public:
        CombatOrderTargetValue(PlayerbotAI* ai);

        virtual std::string Save() override { return value; }
        virtual bool Load(std::string text) override { value = text; return true; }

        static Player* FindGroupMember(Player* bot, const std::string& name);
        static ObjectGuid FindTarget(PlayerbotAI* ai, bool lowestThreat);
    };
}
