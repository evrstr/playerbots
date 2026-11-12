#pragma once
#include "playerbot/strategy/Action.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/PlayerbotFactory.h"

namespace ai
{
    /// 自动更新装备动作：随机机器人升级或重置时按阶段自动生成并穿戴对应装等装备
    class UpdateGearAction : public Action
    {
    public:
        /// 构造函数：初始化自动更新装备动作
        UpdateGearAction(PlayerbotAI* ai);
        /// 执行动作主逻辑（自动更新装备动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（自动更新装备动作）
        virtual bool isUseful() override;

    private:
        /// 获取机器人当前等级对应的装备进度阶段
        uint8 GetProgressionLevel(uint32 itemLevel);
        /// 获取主人全身装备的平均装等或进度等级
        uint8 GetMasterAverageProgressionLevel();
        /// 获取主人指定槽位装备的进度等级
        uint8 GetMasterItemProgressionLevel(uint8 slot, uint8 avgProgressionLevel);
       
        /// 为指定装备或背包物品施放附魔配方
        void EnchantItem(Item* item);

    private:
        std::vector<EnchantTemplate> enchants;
    };
}
