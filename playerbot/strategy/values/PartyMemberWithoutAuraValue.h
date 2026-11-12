// 策略值头文件：PartyMemberWithoutAuraValue（缺少指定光环的友方单位或队友选择）
#pragma once
#include "playerbot/strategy/Value.h"
#include "PartyMemberValue.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // 目标值计算器：查找附近（含队外）缺少指定光环的友好玩家或宠物
    class FriendlyUnitWithoutAuraValue : public PartyMemberValue, public Qualified
    {
    public:
        FriendlyUnitWithoutAuraValue(PlayerbotAI* ai, std::string name = "friendly unit without aura", float range = sPlayerbotAIConfig.sightDistance) :
            PartyMemberValue(ai, name), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };

    // 目标值计算器：查找队伍中缺少指定光环的存活队友（可选忽略坦克）
    class PartyMemberWithoutAuraValue : public PartyMemberValue, public Qualified
    {
    public:
        PartyMemberWithoutAuraValue(PlayerbotAI* ai, std::string name = "party member without aura", float range = sPlayerbotAIConfig.sightDistance) :
          PartyMemberValue(ai, name), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };

    // 目标值计算器：查找队伍中缺少由机器人本人施加的指定光环（如回春/恢复/王者）的队友
    class PartyMemberWithoutMyAuraValue : public PartyMemberValue, public Qualified
    {
    public:
        PartyMemberWithoutMyAuraValue(PlayerbotAI* ai, std::string name = "party member without my aura", float range = 30.0f) :
            PartyMemberValue(ai, name), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };

    // 目标值计算器：查找队伍中缺少指定光环的坦克队友（如大地之盾/误导/圣光道标）
    class PartyTankWithoutAuraValue : public PartyMemberValue, public Qualified
    {
    public:
        PartyTankWithoutAuraValue(PlayerbotAI* ai, std::string name = "party tank without aura", float range = 30.0f) :
            PartyMemberValue(ai, name), Qualified() {}

    protected:
        virtual ObjectGuid Calculate() override;
    };
}
