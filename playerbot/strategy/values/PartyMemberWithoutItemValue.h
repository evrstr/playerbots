// 策略值头文件：PartyMemberWithoutItemValue（缺少指定物品/食物/饮水的队友）
#pragma once
#include "playerbot/strategy/Value.h"
#include "PartyMemberValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 目标值计算器：查找队伍中未持有指定物品且距离在交互范围内的机器人队友
    class PartyMemberWithoutItemValue : public PartyMemberValue, public Qualified
    {
    public:
        PartyMemberWithoutItemValue(PlayerbotAI* ai, std::string name = "party member without item", float range = sPlayerbotAIConfig.farDistance) :
          PartyMemberValue(ai, name), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
        virtual FindPlayerPredicate* CreatePredicate();
    };

    // 目标值计算器：查找队伍中缺少合适等级恢复食物的机器人队友
    class PartyMemberWithoutFoodValue : public PartyMemberWithoutItemValue
    {
    public:
        PartyMemberWithoutFoodValue(PlayerbotAI* ai, std::string name = "party member without food") : PartyMemberWithoutItemValue(ai, name) {}

    protected:
        virtual FindPlayerPredicate* CreatePredicate() override;
    };

    // 目标值计算器：查找队伍中缺少合适等级恢复饮水的有蓝职业机器人队友
    class PartyMemberWithoutWaterValue : public PartyMemberWithoutItemValue
    {
    public:
        PartyMemberWithoutWaterValue(PlayerbotAI* ai, std::string name = "party member without water") : PartyMemberWithoutItemValue(ai, name) {}

    protected:
        virtual FindPlayerPredicate* CreatePredicate() override;
    };
}
