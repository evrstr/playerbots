// 策略值头文件：FishValues（钓鱼条件、浮漂收杆与结束钓鱼状态判断）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/values/LootValues.h"
#include "playerbot/WorldSquare.h"

namespace ai
{    
    // 注释：保留的钓鱼区域战利品模板参考代码
    /*                uint32 zone, subzone;
    gameObject->GetZoneAndAreaId(zone, subzone);
    // if subzone loot exist use it
    if (!FillLoot(subzone, LootTemplates_Fishing, player, true, (subzone != zone)) && subzone != zone)
        // else use zone loot (if zone diff. from subzone, must exist in like case)
        FillLoot(zone, LootTemplates_Fishing, player, true);
        */

    //LootTemplate const* tab = LootTemplates_Fishing.GetLootFor(loot_id);

    // 注释：保留的未启用钓鱼点及区域结构体设计
    /*
    class FishLocation
    public:

    private:
        WorldPosition waterPos, landPos;
    };

    class FishZone : public MapWpSquare
    {
    public:
    private:
        uint32 zone;
        uint32 reqSkill;
        std::vector<uint32> loot;
        //LootTemplate const* tab;
    };

    class FishLocationMapValue : public CalculatedValue<FishZone>
    {
    public:
        FishLocationMapValue(PlayerbotAI* ai) : GuidPositionCalculatedValue(ai, "fish location map", 5) {};
        virtual GuidPosition Calculate() override;
    };   
    */

    // 布尔值计算器：判断机器人是否学会钓鱼技能且背包/装备中有鱼竿
    class CanFishValue : public BoolCalculatedValue
    {
    public:
        CanFishValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can fish", 60) {};
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断当前是否正在引导“钓鱼”法术以便点击浮漂
    class CanOpenFishingDobberValue : public BoolCalculatedValue
    {
    public:
        CanOpenFishingDobberValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can open fishing dobber") {};
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断机器人已装备鱼竿且不再处于钓鱼引导状态（已完成一轮钓鱼）
    class DoneFishingValue : public BoolCalculatedValue
    {
    public:
        DoneFishingValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "done fishing") {};
        virtual bool Calculate() override;
    };
};

